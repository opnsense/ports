--- libpkg/utils.c.orig	2021-02-18 18:07:35 UTC
+++ libpkg/utils.c
@@ -401,7 +401,7 @@ is_valid_abi(const char *arch, bool emit_error) {
 bool
 is_valid_os_version(struct pkg *pkg)
 {
-#ifdef __FreeBSD__
+#ifdef __FreeBSD__XXX
 	const char *fbsd_version;
 	const char *errstr = NULL;
 	int fbsdver;
