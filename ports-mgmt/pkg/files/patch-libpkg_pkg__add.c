--- libpkg/pkg_add.c.orig	2016-10-30 01:50:01 UTC
+++ libpkg/pkg_add.c
@@ -208,7 +208,7 @@ set_attrs(int fd, char *path, mode_t per
 
 	struct timeval tv[2];
 	int fdcwd;
-#ifdef HAVE_UTIMENSAT
+#ifdef HAVE_UTIMENSAT_XXX
 	struct timespec times[2];
 
 	times[0] = *ats;
@@ -248,7 +248,7 @@ set_attrs(int fd, char *path, mode_t per
 	}
 	fchdir(fdcwd);
 	close(fdcwd);
-#ifdef HAVE_UTIMENSAT
+#ifdef HAVE_UTIMENSAT_XXX
 	}
 #endif
 
