--- libarchive/archive_write_set_format_v7tar.c.orig	2018-09-20 17:53:27 UTC
+++ libarchive/archive_write_set_format_v7tar.c
@@ -284,7 +284,7 @@ archive_write_v7tar_header(struct archiv
 		 * case getting WCS failed. On POSIX, this is a
 		 * normal operation.
 		 */
-		if (p != NULL && p[strlen(p) - 1] != '/') {
+		if (p != NULL && p[0] != '\0' && p[strlen(p) - 1] != '/') {
 			struct archive_string as;
 
 			archive_string_init(&as);
