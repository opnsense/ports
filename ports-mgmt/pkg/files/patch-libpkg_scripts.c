--- libpkg/scripts.c.orig	2020-04-29 07:28:26 UTC
+++ libpkg/scripts.c
@@ -48,6 +48,8 @@
 #include "private/pkg.h"
 #include "private/event.h"
 
+#undef PROC_REAP_KILL	/* OPNsense patch */
+
 extern char **environ;
 
 int
@@ -277,7 +279,6 @@ pkg_script_run(struct pkg * const pkg, p
 					exit(0);
 
 				pkg_emit_error("%s script failed", map[i].arg);
-				ret = EPKG_FATAL;
 				goto cleanup;
 			}
 		}
