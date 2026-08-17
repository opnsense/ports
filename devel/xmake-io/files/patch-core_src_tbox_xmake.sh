--- core/src/tbox/xmake.sh.orig	2026-05-19 14:33:04 UTC
+++ core/src/tbox/xmake.sh
@@ -7,7 +7,7 @@ check_interfaces_enabled=false
 set_config "demo" false
 
 check_interfaces_enabled=false
-includes "tbox/src"
+#includes "tbox/src"
 
 hide_options() {
     local name=""
