--- libarchive/archive_write_set_format_gnutar.c.orig	2018-09-20 17:52:06 UTC
+++ libarchive/archive_write_set_format_gnutar.c
@@ -339,7 +339,7 @@ archive_write_gnutar_header(struct archi
 		 * case getting WCS failed. On POSIX, this is a
 		 * normal operation.
 		 */
-		if (p != NULL && p[strlen(p) - 1] != '/') {
+		if (p != NULL && p[0] != '\0' && p[strlen(p) - 1] != '/') {
 			struct archive_string as;
 
 			archive_string_init(&as);
