--- src/prototypes.h.orig	2018-08-10 08:39:41 UTC
+++ src/prototypes.h
@@ -652,7 +652,7 @@ int getnameinfo(const struct sockaddr *,
 #define USE_OS_THREADS
 #endif
 
-#if OPENSSL_VERSION_NUMBER<0x10100004L
+#if (OPENSSL_VERSION_NUMBER<0x10100004L) || defined(LIBRESSL_VERSION_NUMBER)
 
 #ifdef USE_OS_THREADS
 
