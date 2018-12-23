--- SSLeay.xs.orig	2018-12-24 08:02:32 UTC
+++ SSLeay.xs
@@ -5643,7 +5643,7 @@ int
 SSL_get_keyblock_size(s)
      SSL *   s
      CODE:
-#if OPENSSL_VERSION_NUMBER >= 0x10100000L && !defined(LIBRESSL_VERSION_NUMBER)
+#if OPENSSL_VERSION_NUMBER >= 0x10100000L && (!defined(LIBRESSL_VERSION_NUMBER) || (LIBRESSL_VERSION_NUMBER>=0x2090000fL))
         const SSL_CIPHER *ssl_cipher;
 	int cipher = NID_undef, digest = NID_undef, mac_secret_size = 0;
 	const EVP_CIPHER *c = NULL;
