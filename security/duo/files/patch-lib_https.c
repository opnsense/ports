--- lib/https.c.orig	2017-08-15 14:53:34 UTC
+++ lib/https.c
@@ -353,7 +353,7 @@ _establish_connection(struct https_reque
  * building for OpenSSL versions older than 1.1.0
  * or any version of LibreSSL.
  */
-#if OPENSSL_VERSION_NUMBER < 0x10100000L || defined(LIBRESSL_VERSION_NUMBER)
+#if OPENSSL_VERSION_NUMBER < 0x10100000L || (defined(LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER < 0x20700000L)
 static HMAC_CTX *
 HMAC_CTX_new(void)
 {
