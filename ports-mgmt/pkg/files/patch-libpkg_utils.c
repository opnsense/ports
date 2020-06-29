--- libpkg/utils.c.orig	2019-09-18 07:11:10 UTC
+++ libpkg/utils.c
@@ -350,7 +350,7 @@ is_valid_abi(const char *arch, bool emit
 bool
 is_valid_os_version(struct pkg *pkg)
 {
-#ifdef __FreeBSD__
+#ifdef __FreeBSD__XXX
 	const char *fbsd_version;
 	const char *errstr = NULL;
 	int fbsdver;
