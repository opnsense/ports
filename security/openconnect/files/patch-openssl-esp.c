--- openssl-esp.c.orig	2018-09-18 13:28:48 UTC
+++ openssl-esp.c
@@ -27,7 +27,7 @@
 #include <openssl/evp.h>
 #include <openssl/rand.h>
 
-#if OPENSSL_VERSION_NUMBER < 0x10100000L || defined(LIBRESSL_VERSION_NUMBER)
+#if OPENSSL_VERSION_NUMBER < 0x10100000L || ( defined(LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER < 0x20700000L )
 
 #define EVP_CIPHER_CTX_free(c) do {				\
 				    EVP_CIPHER_CTX_cleanup(c);	\
