--- update/opnsense-update.sh.orig	2019-07-02 19:17:39 UTC
+++ update/opnsense-update.sh
@@ -42,7 +42,7 @@ KERNELDIR="/boot/kernel"
 TEE="/usr/bin/tee -a"
 PRODUCT="OPNsense"
 PKG="pkg-static"
-VERSION="19.1.8"
+VERSION="19.7.r1"
 
 ORIGIN="/usr/local/etc/pkg/repos/${PRODUCT}.conf"
 PENDINGDIR="${WORKPREFIX}/.sets.pending"
