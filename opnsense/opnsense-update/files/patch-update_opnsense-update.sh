--- update/opnsense-update.sh.orig	2016-07-01 07:43:26 UTC
+++ update/opnsense-update.sh
@@ -36,7 +36,7 @@ MARKER="/usr/local/opnsense/version/opns
 ORIGIN="/usr/local/etc/pkg/repos/origin.conf"
 WORKPREFIX="/var/cache/opnsense-update"
 URL_KEY="^[[:space:]]*url:[[:space:]]*"
-VERSION="16.1.18"
+VERSION="16.7.r"
 PKG="pkg-static"
 ARCH=$(uname -m)
 
