--- src/Mayaqua/Encrypt.h.orig	2020-08-06 09:09:01 UTC
+++ src/Mayaqua/Encrypt.h
@@ -105,7 +105,7 @@
 #ifndef	ENCRYPT_H
 #define	ENCRYPT_H
 
-#if OPENSSL_VERSION_NUMBER >= 0x10100000L
+#if OPENSSL_VERSION_NUMBER >= 0x10100000L && !defined(LIBRESSL_VERSION_NUMBER)
 #define USE_OPENSSL_AEAD_CHACHA20POLY1305
 #endif
 
