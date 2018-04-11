--- Modules/_ssl.c.orig	2018-03-28 09:19:31 UTC
+++ Modules/_ssl.c
@@ -104,7 +104,7 @@ struct py_ssl_library_code {
 /* Include generated data (error codes) */
 #include "_ssl_data.h"
 
-#if (OPENSSL_VERSION_NUMBER >= 0x10100000L) && !defined(LIBRESSL_VERSION_NUMBER)
+#if (OPENSSL_VERSION_NUMBER >= 0x10100000L) && !(defined(LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER < 0x20700000L)
 #  define OPENSSL_VERSION_1_1 1
 #endif
 
