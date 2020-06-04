--- libpkg/utils.c.orig	2020-04-29 07:28:26 UTC
+++ libpkg/utils.c
@@ -351,7 +351,7 @@ is_valid_abi(const char *arch, bool emit
 bool
 is_valid_os_version(struct pkg *pkg)
 {
-#ifdef __FreeBSD__
+#ifdef __FreeBSD__XXX
 	const char *fbsd_version;
 	const char *errstr = NULL;
 	int fbsdver;
