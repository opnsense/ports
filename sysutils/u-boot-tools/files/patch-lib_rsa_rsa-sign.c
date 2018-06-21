--- lib/rsa/rsa-sign.c.orig	2018-03-13 12:02:19 UTC
+++ lib/rsa/rsa-sign.c
@@ -21,7 +21,7 @@
 #define HAVE_ERR_REMOVE_THREAD_STATE
 #endif
 
-#if OPENSSL_VERSION_NUMBER < 0x10100000L
+#if OPENSSL_VERSION_NUMBER < 0x10100000L || (defined(LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER < 0x20700000L)
 static void RSA_get0_key(const RSA *r,
                  const BIGNUM **n, const BIGNUM **e, const BIGNUM **d)
 {
@@ -300,7 +300,7 @@ static int rsa_init(void)
 {
 	int ret;
 
-#if OPENSSL_VERSION_NUMBER < 0x10100000L
+#if OPENSSL_VERSION_NUMBER < 0x10100000L || (defined(LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER < 0x20700000L)
 	ret = SSL_library_init();
 #else
 	ret = OPENSSL_init_ssl(0, NULL);
@@ -433,7 +433,7 @@ static int rsa_sign_with_key(RSA *rsa, s
 		ret = rsa_err("Could not obtain signature");
 		goto err_sign;
 	}
-	#if OPENSSL_VERSION_NUMBER < 0x10100000L
+	#if OPENSSL_VERSION_NUMBER < 0x10100000L || (defined(LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER < 0x20700000L)
 		EVP_MD_CTX_cleanup(context);
 	#else
 		EVP_MD_CTX_reset(context);
