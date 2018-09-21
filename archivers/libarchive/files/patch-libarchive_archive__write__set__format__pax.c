--- libarchive/archive_write_set_format_pax.c.orig	2018-09-20 17:51:37 UTC
+++ libarchive/archive_write_set_format_pax.c
@@ -660,7 +660,7 @@ archive_write_pax_header(struct archive_
 			 * case getting WCS failed. On POSIX, this is a
 			 * normal operation.
 			 */
-			if (p != NULL && p[strlen(p) - 1] != '/') {
+			if (p != NULL && p[0] != '\0' && p[strlen(p) - 1] != '/') {
 				struct archive_string as;
 
 				archive_string_init(&as);
