--- src/Mayaqua/Encrypt.h.orig	2020-08-06 09:09:01 UTC
+++ src/Mayaqua/Encrypt.h
@@ -105,7 +105,7 @@
 #ifndef	ENCRYPT_H
 #define	ENCRYPT_H
 
-#if OPENSSL_VERSION_NUMBER >= 0x10100000L
+#if OPENSSL_VERSION_NUMBER >= 0x10100000L && !defined(LIBRESSL_VERSION_NUMBER)
 #define USE_OPENSSL_AEAD_CHACHA20POLY1305
 #endif
 
--- src/Mayaqua/Network.c.orig	2020-08-07 06:16:19 UTC
+++ src/Mayaqua/Network.c
@@ -18172,7 +18172,7 @@ struct ssl_ctx_st *NewSSLCtx(bool server_mode)
 	SSL_CTX_set_ecdh_auto(ctx, 1);
 #endif	// SSL_CTX_set_ecdh_auto
 
-#if OPENSSL_VERSION_NUMBER >= 0x1010100fL
+#if OPENSSL_VERSION_NUMBER >= 0x1010100fL && !defined(LIBRESSL_VERSION_NUMBER)
 	// For compatibility with VPN 3.0 or older
 	SSL_CTX_set_security_level(ctx, 0);
 #endif
