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
MY_RELEASE="15.1.10"
ARCH=$(uname -m)

if [ -f ${MARKER} ]; then
	INSTALLED=$(cat ${MARKER})
fi

NOKERNEL=
NOBASE=
FORCE=
DIRTY=

while getopts bcfkm:r:v OPT; do
	case ${OPT} in
	b)
		DIRTY="-base"
		NOKERNEL=1
		NOBASE=
		;;
	c)
		if [ "${MY_RELEASE}-${ARCH}" = "${INSTALLED}" ]; then
			exit 1
		fi
		exit 0
		;;
	f)
		FORCE=1
		;;
	k)
		DIRTY="-kernel"
		NOKERNEL=
		NOBASE=1
		;;
	m)
		MIRROR=${OPTARG}
		;;
	r)
		RELEASE=${OPTARG}
		;;
	v)
		echo ${MY_RELEASE}-${ARCH}
		exit 0
		;;
	*)
		echo "Usage: opnsense-update [-bcfkv] [-m mirror] [-r release]" >&2
		exit 1
		;;
	esac
done

# if no release was selected we use the embedded defaults
if [ -z "${RELEASE}" ]; then
	RELEASE=${MY_RELEASE}

	if [ ${ARCH} = "amd64" ]; then
		OBSOLETESHA="34f7479276c3b43c73468686dcf6f402c5be4f1d7c1d5761e22d6b52a3d4c174"
		KERNELSHA="f0b240ac0e4335753c77d9cbb3911dadc4b245eb2ad466c9d53cf95c0311be14"
		BASESHA="8b7d4be02101163683d7ec2a28f415237a3a2e7c201c60c9778c1b2c784027d9"
	elif [ ${ARCH} = "i386" ]; then
		OBSOLETESHA="aefeb0f249ac98948dbaed1d8d4907987b9201f9268fb0498138e3bfe1142b65"
		KERNELSHA="464de9bff13d182fe38e40e97c651f593e0ae604218b87c2c1b2221ea21bc620"
		BASESHA="8c77f33ba0c6927da9f2f968625318b0ba214b0b16e4c5e4a1b307530ca17ff3"
	else
		echo "Unknown architecture ${ARCH}" >&2
		exit 1
	fi
fi

if [ "${RELEASE}-${ARCH}" = "${INSTALLED}" -a -z "${FORCE}" ]; then
	echo "Your system is up to date."
	exit 0
fi

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
	    tar -C/ -xjpf ${WORKDIR}/${BASESET} \
	    --exclude="./etc/pkg/FreeBSD.conf" \
	    --exclude="./etc/group" \
	    --exclude="./etc/master.passwd" \
	    --exclude="./etc/passwd" \
	    --exclude="./etc/shells" \
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

if [ -z "${NOKERNEL}" ]; then
	fetch_set ${KERNELSET} ${KERNELSHA}
fi

if [ -z "${NOBASE}" ]; then
	fetch_set ${BASESET} ${BASESHA}
	fetch_set ${OBSOLETESET} ${OBSOLETESHA}
fi

if [ -z "${NOKERNEL}" ]; then
	apply_kernel
fi

if [ -z "${NOBASE}" ]; then
	apply_base
	apply_obsolete
fi

mkdir -p $(dirname ${MARKER})
echo ${RELEASE}-${ARCH}${DIRTY} > ${MARKER}

rm -r ${WORKDIR}

echo "Please reboot."
