--- libpkg/pkg_add.c.orig	2020-12-23 20:07:25 UTC
+++ libpkg/pkg_add.c
@@ -1159,6 +1159,7 @@ pkg_add_common(struct pkgdb *db, const char *path, uns
 	}
 
 	if (local != NULL) {
+		pkg_open_root_fd(local);
 		pkg_debug(1, "Cleaning up old version");
 		if (pkg_add_cleanup_old(db, local, pkg, flags) != EPKG_OK) {
 			retcode = EPKG_FATAL;
