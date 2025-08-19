--- libpkg/utils.c.orig	2022-08-03 07:37:06 UTC
+++ libpkg/utils.c
@@ -355,7 +355,7 @@ is_valid_abi(const char *arch, bool emit_error) {
 bool
 is_valid_os_version(struct pkg *pkg)
 {
-#ifdef __FreeBSD__
+#ifdef __FreeBSD__XXX
 	const char *fbsd_version;
 	const char *errstr = NULL;
 	int fbsdver;
