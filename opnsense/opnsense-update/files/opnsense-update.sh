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

if [ -z "${1}" ]; then
	echo "Usage: opnsense-update mirror [version]"
	exit 1
fi

SETSURL=${1}
VERSION="15.1.5"
ARCH=$(uname -m)

OBSOLETESHA=""
KERNELSHA=""
BASESHA=""

if [ -z "${2}" ]; then
	if [ ${ARCH} = "amd64" ]; then
		OBSOLETESHA="053d1d0fcc6b7cb135f512f438f00119a7c073a2d9e97372972d782ae4c0e820"
		KERNELSHA="d27439ee477a89ac6000e7b71253a9a9503c3bc0d35c6ac74be9932d0b91744e"
		BASESHA="dc4d7ac58fe5b41d376e95df6e65bf507765ddbf3a27659855234ffea028e393"
	elif [ ${ARCH} = "i386" ]; then
		OBSOLETESHA="XXX"
		KERNELSHA="c12b2a151da78e8d26274a8d46de3391b4d14d86253b3f72c786089c91fd1d19"
		BASESHA="1fcda86b81baca09a8b86b166ecb1ac3a2b07876774f004821e9345a8afde2c9"
	fi
else
	# switches off checksumming!!
	VERSION=${2}
fi


WORKDIR=/tmp/opnsense-update.${$}
KERNELSET=kernel-${VERSION}-${ARCH}.txz
BASESET=base-${VERSION}-${ARCH}.txz
OBSOLETESET=base-${VERSION}-${ARCH}.obsolete
KERNELDIR=/boot/kernel

fetch_set()
{
	echo -n "Fetching ${1}... "

	mkdir -p ${WORKDIR} && \
	    fetch -q ${SETSURL}/${1} -o ${WORKDIR}/${1} && \
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

rm -r ${WORKDIR}

echo "Please reboot."
