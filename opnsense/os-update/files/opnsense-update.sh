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
RELEASE="15.1.7"
ARCH=$(uname -m)

if [ ${ARCH} = "amd64" ]; then
	OBSOLETESHA="053d1d0fcc6b7cb135f512f438f00119a7c073a2d9e97372972d782ae4c0e820"
	KERNELSHA="5d1c24196ee05c927e084b3188d1b49663083c550148da561ee82886dd414318"
	BASESHA="982f838e375287f1df64945c2c1e6d5ffd96cd53e64b765224f2e9e89797e7f0"
elif [ ${ARCH} = "i386" ]; then
	OBSOLETESHA="7e6044cfcdb4ac03309974e08a6f6a83bda0359944e78e4d09b10a5849986d3c"
	KERNELSHA="bffbf3485eb69817ea2001767cc400775cd000d5d059276f0e2ae26224ae3556"
	BASESHA="e7cee8909d946af804afa428e4640af65d61f9394cdd27ae864d3a2ff5a0f5dc"
else
	echo "Unknown architecture ${ARCH}" >&2
	exit 1
fi

if [ -f ${MARKER} ]; then
	INSTALLED=$(cat ${MARKER})
fi

while getopts cfm:r:v OPT; do
	case ${OPT} in
	c)
		if [ ${RELEASE} = "${INSTALLED}" ]; then
			exit 1
		fi
		exit 0
		;;
	f)
		FORCE=1
		;;
	m)
		MIRROR=${OPTARG}
		;;
	r)
		RELEASE=${OPTARG}
		# switches off checksumming!!
		OBSOLETESHA=""
		KERNELSHA=""
		BASESHA=""
		;;
	v)
		echo ${RELEASE}-${ARCH}
		exit 0
		;;
	*)
		echo "Usage: opnsense-update [-cfv] [-m mirror] [-r release]" >&2
		exit 1
		;;
	esac
done

if [ ${RELEASE} = "${INSTALLED}" -a -z "${FORCE}" ]; then
	echo "You are up to date."
	exit 0
fi

WORKDIR=/tmp/opnsense-update.${$}
KERNELSET=kernel-${RELEASE}-${ARCH}.txz
BASESET=base-${RELEASE}-${ARCH}.txz
OBSOLETESET=base-${RELEASE}-${ARCH}.obsolete
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

fetch_set ${KERNELSET} ${KERNELSHA}
fetch_set ${BASESET} ${BASESHA}
fetch_set ${OBSOLETESET} ${OBSOLETESHA}

apply_kernel
apply_base
apply_obsolete

mkdir -p $(dirname ${MARKER})
echo ${RELEASE}-${ARCH} > ${MARKER}

rm -r ${WORKDIR}

echo "Please reboot."
