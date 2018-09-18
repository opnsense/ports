--- tests/bad_dtls_test.c.orig	2018-09-18 13:30:43 UTC
+++ tests/bad_dtls_test.c
@@ -290,7 +290,7 @@ static unsigned char key_block[104];
 static EVP_MD_CTX *handshake_md5;
 static EVP_MD_CTX *handshake_sha1;
 
-#if OPENSSL_VERSION_NUMBER < 0x10100000L || defined(LIBRESSL_VERSION_NUMBER)
+#if OPENSSL_VERSION_NUMBER < 0x10100000L || ( defined(LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER < 0x20700000L )
 static inline HMAC_CTX *HMAC_CTX_new(void) {
     HMAC_CTX *ret = malloc(sizeof(*ret));
     HMAC_CTX_init(ret);
