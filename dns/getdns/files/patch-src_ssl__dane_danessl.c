--- src/ssl_dane/danessl.c.orig	2019-04-19 16:45:15 UTC
+++ src/ssl_dane/danessl.c
@@ -20,7 +20,7 @@
 #error "OpenSSL 1.0.0 or higher required"
 #endif
 
-#if OPENSSL_VERSION_NUMBER < 0x10100000L
+#if OPENSSL_VERSION_NUMBER < 0x10100000L || defined(LIBRESSL_VERSION_NUMBER)
 #define X509_up_ref(x) CRYPTO_add(&((x)->references), 1, CRYPTO_LOCK_X509)
 #define X509_STORE_CTX_get0_cert(ctx) ((ctx)->cert)
 #define X509_STORE_CTX_get0_untrusted(ctx) ((ctx)->untrusted)
@@ -896,7 +896,7 @@ static int verify_chain(X509_STORE_CTX *
 	dane->match = top;
 	X509_up_ref(top);
 
-#if OPENSSL_VERSION_NUMBER < 0x10100000L
+#if OPENSSL_VERSION_NUMBER < 0x10100000L || defined(LIBRESSL_VERSION_NUMBER)
 	if (X509_check_issued(top, top) != X509_V_OK) {
 	    X509_STORE_CTX_set_error_depth(ctx, dane->depth);
 	    X509_STORE_CTX_set_current_cert(ctx, top);
@@ -1457,7 +1457,7 @@ static void dane_init(void)
     dane_idx = SSL_get_ex_new_index(0, 0, 0, 0, 0);
 }
 
-#if OPENSSL_VERSION_NUMBER < 0x10100000L
+#if OPENSSL_VERSION_NUMBER < 0x10100000L || defined(LIBRESSL_VERSION_NUMBER)
 static void run_once(volatile int *once, void (*init)(void))
 {
     int wlock = 0;
