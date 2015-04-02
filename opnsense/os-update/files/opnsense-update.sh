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
MY_RELEASE="15.1.8"
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
		OBSOLETESHA="053d1d0fcc6b7cb135f512f438f00119a7c073a2d9e97372972d782ae4c0e820"
		KERNELSHA="dfc6adb05eff81f44d2d68a88e81bd79d7c93130ef390953a96b3c91e60f3a8e"
		BASESHA="1fb4214f242818cc05baf4e06fd917a40310e732ab491044f56303664bc3e021"
	elif [ ${ARCH} = "i386" ]; then
		OBSOLETESHA="7e6044cfcdb4ac03309974e08a6f6a83bda0359944e78e4d09b10a5849986d3c"
		KERNELSHA="0be79f961cffc82d0f274a3c87db45c804e4c4801a63efee49e9637ed05a4e03"
		BASESHA="5cf49ac9edb0c6d34fd310138c4f09d4e57eb62b3d9924ee8046a0074479ecec"
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
