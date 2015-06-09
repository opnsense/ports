#!/bin/sh

# Copyright (c) 2015 Franco Fichtner <franco@opnsense.org>
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.

set -e

if [ "$(id -u)" != "0" ]; then
	echo "Must be root."
	exit 1
fi

# clean up old stale working directories
rm -rf /tmp/opnsense-update.*

MARKER="/usr/local/opnsense/version/os-update"
MIRROR="http://pkg.opnsense.org/sets"
MY_RELEASE="15.1.11"
ARCH=$(uname -m)

if [ -f ${MARKER} ]; then
	INSTALLED=$(cat ${MARKER})
fi

DO_RELEASE=
DO_MIRROR=
DO_KERNEL=
DO_FORCE=
DO_BASE=
DO_PKGS=
DIRTY=

while getopts bcfkm:pr:v OPT; do
	case ${OPT} in
	b)
		DO_BASE="-b"
		;;
	c)
		if [ "${MY_RELEASE}-${ARCH}" = "${INSTALLED}" ]; then
			exit 1
		fi
		exit 0
		;;
	f)
		DO_FORCE="-f"
		;;
	k)
		DO_KERNEL="-k"
		;;
	m)
		DO_MIRROR="-m ${OPTARG}"
		MIRROR=${OPTARG}
		;;
	p)
		DO_PKGS="-p"
		;;
	r)
		DO_RELEASE="-r ${OPTARG}"
		RELEASE=${OPTARG}
		DIRTY="dirty"
		;;
	v)
		echo ${MY_RELEASE}-${ARCH}
		exit 0
		;;
	*)
		echo "Usage: opnsense-update [-bcfkpv] [-m mirror] [-r release]" >&2
		exit 1
		;;
	esac
done

if [ -z "${DO_KERNEL}${DO_BASE}${DO_PKGS}" ]; then
	# default is enable all
	DO_KERNEL="-k"
	DO_BASE="-b"
	DO_PKGS="-p"
fi

if [ -n "${DO_PKGS}" ]; then
	pkg update ${DO_FORCE}
	pkg upgrade -y ${DO_FORCE}
	pkg autoremove -y
	pkg clean -y
	if [ -n "${DO_BASE}${DO_KERNEL}" ]; then
		# script may have changed, relaunch...
		opnsense-update ${DO_BASE} ${DO_KERNEL} \
		    ${DO_FORCE} ${DO_RELEASE} ${DO_MIRROR}
	fi
	# stop here to prevent the second pass
	exit 0
fi

# if no release was selected we use the embedded defaults
if [ -z "${RELEASE}" ]; then
	RELEASE=${MY_RELEASE}

	if [ ${ARCH} = "amd64" ]; then
		OBSOLETESHA="34f7479276c3b43c73468686dcf6f402c5be4f1d7c1d5761e22d6b52a3d4c174"
		KERNELSHA="eab75491a4857d6a7ea8e4dbd406a1c5da4765184d8709fb1113faa63e8fb5da"
		BASESHA="4d6182b090ca269f472e0aedc3bc3ae903b11eadbe15aa80f9d2370a934402b7"
	elif [ ${ARCH} = "i386" ]; then
		OBSOLETESHA="aefeb0f249ac98948dbaed1d8d4907987b9201f9268fb0498138e3bfe1142b65"
		KERNELSHA="b10e6ac3309446518ae9e413489fbe82c2e966b51cc8c47f6d19816e62e38607"
		BASESHA="83e2a5a1fff18e0f8e77ce7f4213569eaab149859b478cf7d5f95165c7a522e1"
	else
		echo "Unknown architecture ${ARCH}" >&2
		exit 1
	fi
fi

if [ "${RELEASE}-${ARCH}" = "${INSTALLED}" -a -z "${DO_FORCE}" ]; then
	echo "Your system is up to date."
	exit 0
fi

echo
echo "!!!!!!!!!!!! ATTENTION !!!!!!!!!!!!!!"
echo "A kernel/base upgrade is in progress."
echo "Please do not turn off the system."
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo

OBSOLETESET=base-${RELEASE}-${ARCH}.obsolete
KERNELSET=kernel-${RELEASE}-${ARCH}.txz
BASESET=base-${RELEASE}-${ARCH}.txz
WORKDIR=/tmp/opnsense-update.${$}
KERNELDIR=/boot/kernel

fetch_set()
{
	echo -n "Fetching ${1}... "

	mkdir -p ${WORKDIR} && \
	    fetch -q ${MIRROR}/${1} -o ${WORKDIR}/${1} && \
	    [ -z "${2}" -o "`sha256 -q ${WORKDIR}/${1}`" = "${2}" ] && \
	    echo "ok" && return

	echo "failed"
	exit 1
}

apply_kernel()
{
	echo -n "Applying ${KERNELSET}... "

	rm -rf ${KERNELDIR}.old && \
	    mv ${KERNELDIR} ${KERNELDIR}.old && \
	    tar -C/ -xjpf ${WORKDIR}/${KERNELSET} && \
	    kldxref ${KERNELDIR} && \
	    echo "ok" && return

	echo "failed"
	exit 1
}

apply_base()
{
	echo -n "Applying ${BASESET}... "

	# Ideally, we don't do any exlcude magic and simply
	# reapply all the packages on bootup and do another
	# reboot just to be safe...

	chflags -R noschg /bin /sbin /lib /libexec \
	    /usr/bin /usr/sbin /usr/lib && \
	    tar -C/ -xpf ${WORKDIR}/${BASESET} \
	    --exclude="./etc/group" \
	    --exclude="./etc/master.passwd" \
	    --exclude="./etc/passwd" \
	    --exclude="./etc/shells" \
	    --exclude="./etc/ttys" \
	    --exclude="./etc/rc" && \
	    kldxref ${KERNELDIR} && \
	    echo "ok" && return

	echo "failed"
	exit 1
}

apply_obsolete()
{
	echo -n "Applying ${OBSOLETESET}... "

	while read FILE; do
		rm -f ${FILE}
	done < ${WORKDIR}/${OBSOLETESET}

	echo "ok"
}

if [ -n "${DO_KERNEL}" ]; then
	fetch_set ${KERNELSET} ${KERNELSHA}
fi

if [ -n "${DO_BASE}" ]; then
	fetch_set ${BASESET} ${BASESHA}
	fetch_set ${OBSOLETESET} ${OBSOLETESHA}
fi

if [ -n "${DO_KERNEL}" ]; then
	apply_kernel
fi

if [ -n "${DO_BASE}" ]; then
	apply_base
	apply_obsolete
fi

mkdir -p $(dirname ${MARKER})
echo ${RELEASE}-${ARCH}${DIRTY} > ${MARKER}

rm -r ${WORKDIR}

echo "Please reboot."
