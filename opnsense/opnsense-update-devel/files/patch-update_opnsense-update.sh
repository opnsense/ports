--- update/opnsense-update.sh.orig	2020-03-16 05:47:51 UTC
+++ update/opnsense-update.sh
@@ -42,7 +42,7 @@ KERNELDIR="/boot/kernel"
 TEE="/usr/bin/tee -a"
 PRODUCT="OPNsense"
 PKG="pkg-static"
-VERSION="20.1.2"
+VERSION="20.7.b"
 
 ORIGIN="/usr/local/etc/pkg/repos/${PRODUCT}.conf"
 PENDINGDIR="${WORKPREFIX}/.sets.pending"
