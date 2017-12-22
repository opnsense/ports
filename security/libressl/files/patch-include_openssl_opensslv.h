--- include/openssl/opensslv.h.orig	2017-12-12 09:46:36 UTC
+++ include/openssl/opensslv.h
@@ -7,7 +7,11 @@
 #define LIBRESSL_VERSION_TEXT	"LibreSSL 2.6.4"
 
 /* These will never change */
+#ifndef OPENSSL_IS_LIBRESSL
 #define OPENSSL_VERSION_NUMBER	0x20000000L
+#else
+#define OPENSSL_VERSION_NUMBER	0x1000107fL
+#endif /* OPENSSL_IS_LIBRESSL */
 #define OPENSSL_VERSION_TEXT	LIBRESSL_VERSION_TEXT
 #define OPENSSL_VERSION_PTEXT	" part of " OPENSSL_VERSION_TEXT
 
