--- libpkg/pkg_add.c.orig	2016-07-10 16:39:12 UTC
+++ libpkg/pkg_add.c
@@ -206,7 +206,7 @@ set_attrs(int fd, char *path, mode_t per
     const struct timespec *ats, const struct timespec *mts)
 {
 
-#ifdef HAVE_UTIMENSAT
+#ifdef HAVE_UTIMENSAT_XXX
 	struct timespec times[2];
 
 	times[0] = *ats;
