--- libpkg/pkg_delete.c.orig	2016-12-28 12:09:51 UTC
+++ libpkg/pkg_delete.c
@@ -303,23 +303,6 @@ pkg_delete_file(struct pkg *pkg, struct 
 	while (len > 0 && prefix_rel[len - 1] == '/')
 		len--;
 
-	/* Regular files and links */
-	/* check checksum */
-	if (!force && file->sum != NULL) {
-		ret = pkg_checksum_validate_fileat(pkg->rootfd, path, file->sum);
-		if (ret == ENOENT) {
-			pkg_emit_file_missing(pkg, file);
-			return;
-		}
-		if (ret != 0) {
-			pkg_emit_error("%s%s%s different from original "
-			    "checksum, not removing", pkg->rootpath,
-			    pkg->rootpath[strlen(pkg->rootpath) - 1] == '/' ? "" : "/",
-			    path);
-			return;
-		}
-	}
-
 #ifdef HAVE_CHFLAGS
 	if (fstatat(pkg->rootfd, path, &st, AT_SYMLINK_NOFOLLOW) != -1) {
 		if (st.st_flags & NOCHANGESFLAGS) {
