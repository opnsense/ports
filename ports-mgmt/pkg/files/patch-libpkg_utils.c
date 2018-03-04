--- libpkg/utils.c.orig	2018-03-04 08:35:35 UTC
+++ libpkg/utils.c
@@ -349,7 +349,7 @@ is_valid_abi(const char *arch, bool emit
 bool
 is_valid_os_version(struct pkg *pkg)
 {
-#ifdef __FreeBSD__
+#ifdef __FreeBSD__XXX
 	const char *fbsd_version;
 	const char *errstr = NULL;
 	int fbsdver;
