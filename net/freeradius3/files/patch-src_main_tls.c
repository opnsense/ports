--- src/main/tls.c.orig	2019-04-15 07:00:13 UTC
+++ src/main/tls.c
@@ -3379,14 +3379,14 @@ post_ca:
 		 */
 		SSL_CTX_sess_set_cache_size(ctx, conf->session_cache_size);
 
-#if OPENSSL_VERSION_NUMBER >= 0x10101000L
+#if OPENSSL_VERSION_NUMBER >= 0x10101000L &&! defined(LIBRESSL_VERSION_NUMBER)
 		SSL_CTX_set_num_tickets(ctx, 1);
 #endif
 
 	} else {
 		SSL_CTX_set_session_cache_mode(ctx, SSL_SESS_CACHE_OFF);
 
-#if OPENSSL_VERSION_NUMBER >= 0x10101000L
+#if OPENSSL_VERSION_NUMBER >= 0x10101000L &&! defined(LIBRESSL_VERSION_NUMBER)
 		/*
 		 *	This controls the number of stateful or stateless tickets
 		 *	generated with TLS 1.3.  In OpenSSL 1.1.1 it's also
