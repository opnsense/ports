--- libpkg/lua_scripts.c.orig	2020-06-04 01:54:38 UTC
+++ libpkg/lua_scripts.c
@@ -51,6 +51,8 @@
 #include "private/pkg.h"
 #include "private/event.h"
 
+#undef PROC_REAP_KILL	/* OPNsense patch */
+
 extern char **environ;
 
 static lua_CFunction
