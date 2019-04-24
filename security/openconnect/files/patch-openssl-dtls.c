--- openssl-dtls.c.orig	2019-01-05 09:31:02 UTC
+++ openssl-dtls.c
@@ -315,7 +315,7 @@ static unsigned int psk_callback(SSL *ss
 
 #endif
 
-#if OPENSSL_VERSION_NUMBER < 0x10002000L
+#if OPENSSL_VERSION_NUMBER < 0x10002000L || defined(LIBRESSL_VERSION_NUMBER)
 static const SSL_CIPHER *SSL_CIPHER_find(SSL *ssl, const unsigned char *ptr)
 {
     return ssl->method->get_cipher_by_char(ptr);
