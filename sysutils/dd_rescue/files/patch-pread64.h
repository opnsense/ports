--- pread64.h.orig	2024-09-16 18:11:52 UTC
+++ pread64.h
@@ -18,11 +18,11 @@
 # include <sys/reg.h>
 #endif
 
-#if !defined(HAVE_PREAD64) && __WORDSIZE == 64 && !defined(TEST_SYSCALL) && defined(HAVE_PREAD)
+#if defined(__FreeBSD__) || !defined(HAVE_PREAD64) && __WORDSIZE == 64 && !defined(TEST_SYSCALL) && defined(HAVE_PREAD)
 # define pread64 pread
 # define HAVE_PREAD64 1
 #endif
-#if !defined(HAVE_PWRITE64) && __WORDSIZE == 64 && !defined(TEST_SYSCALL) && defined(HAVE_PWRITE)
+#if defined(__FreeBSD__) || !defined(HAVE_PWRITE64) && __WORDSIZE == 64 && !defined(TEST_SYSCALL) && defined(HAVE_PWRITE)
 # define pwrite64 pwrite
 # define HAVE_PWRITE64 1
 #endif
