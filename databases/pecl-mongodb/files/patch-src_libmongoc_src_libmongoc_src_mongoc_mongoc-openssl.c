--- src/libmongoc/src/libmongoc/src/mongoc/mongoc-openssl.c.orig	2020-02-15 08:36:36 UTC
+++ src/libmongoc/src/libmongoc/src/mongoc/mongoc-openssl.c
@@ -494,7 +494,7 @@ _mongoc_openssl_ctx_new (mongoc_ssl_opt_
 #endif
 
 /* man SSL_get_options says: "SSL_OP_NO_RENEGOTIATION options were added in OpenSSL 1.1.1" */
-#if OPENSSL_VERSION_NUMBER >= 0x10101000L
+#if OPENSSL_VERSION_NUMBER >= 0x10101000L && !defined(LIBRESSL_VERSION_NUMBER)
    ssl_ctx_options |= SSL_OP_NO_RENEGOTIATION;
 #endif
 
