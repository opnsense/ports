--- update/opnsense-update.sh.orig	2018-07-03 08:28:35 UTC
+++ update/opnsense-update.sh
@@ -50,7 +50,7 @@ DEBUGDIR="/usr/lib/debug"
 KERNELDIR="/boot/kernel"
 PKG="pkg-static"
 ARCH=$(uname -p)
-VERSION="18.1.11"
+VERSION="18.7.r1"
 
 if [ ! -f ${ORIGIN} ]; then
 	echo "Missing ${ORIGIN}" >&2
