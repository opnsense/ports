--- config.tests/unix/openssl11/openssl.cpp.orig	2018-09-12 10:47:06 UTC
+++ config.tests/unix/openssl11/openssl.cpp
@@ -39,7 +39,7 @@
 
 #include <openssl/opensslv.h>
 
-#if !defined(OPENSSL_VERSION_NUMBER) || OPENSSL_VERSION_NUMBER-0 < 0x10100000L
+#if !defined(OPENSSL_VERSION_NUMBER) || OPENSSL_VERSION_NUMBER-0 < 0x10100000L || defined(LIBRESSL_VERSION_NUMBER)
 #  error "OpenSSL >= 1.1 is required"
 #endif
 
