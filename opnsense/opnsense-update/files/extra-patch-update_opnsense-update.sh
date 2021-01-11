--- update/opnsense-update.sh.orig	2021-01-11 09:57:26 UTC
+++ update/opnsense-update.sh
@@ -42,7 +42,7 @@ KERNELDIR="/boot/kernel"
 TEE="/usr/bin/tee -a"
 PRODUCT="OPNsense"
 PKG="pkg-static"
-VERSION="20.7.8"
+VERSION="21.1.r1"
 
 ORIGIN="/usr/local/etc/pkg/repos/${PRODUCT}.conf"
 PENDINGDIR="${WORKPREFIX}/.sets.pending"
