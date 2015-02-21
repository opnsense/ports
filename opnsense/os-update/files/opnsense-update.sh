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

# Usage: opnsense-update [version] [mirror]

if [ "$(id -u)" != "0" ]; then
	echo "Must be root."
	exit 1
fi

# clean up old stale working directories
rm -rf /tmp/opnsense-update.*

SETSURL="http://pkg.opnsense.org/sets"
VERSION="15.1.6"
ARCH=$(uname -m)

OBSOLETESHA=""
KERNELSHA=""
BASESHA=""

if [ -n "${1}" ]; then
	# switches off checksumming!!
	VERSION="${1}"
elif [ ${ARCH} = "amd64" ]; then
	OBSOLETESHA="053d1d0fcc6b7cb135f512f438f00119a7c073a2d9e97372972d782ae4c0e820"
	KERNELSHA="d2743429b043a6f422e5eb1fafba6c4d635c4b46467d717d2890d50b0d8ec3ad"
	BASESHA="1afeb1796a0dc31be23d1ac7124e0d074c0fe33c2dd984e1918d58c2aa3314b3"
elif [ ${ARCH} = "i386" ]; then
	OBSOLETESHA="7e6044cfcdb4ac03309974e08a6f6a83bda0359944e78e4d09b10a5849986d3c"
	KERNELSHA="f664a40c722d2bc2179fd2342ee3edef0584b7687dc9796bf8be3a334001e557"
	BASESHA="ee1166892c36e44e8a284567028f3b7620c13a8e4e492cb3c05e14e809ca6a34"
fi

if [ -n "${2}" ]; then
	SETSURL="${2}"
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

rm -r ${WORKDIR}

echo "Please reboot."
