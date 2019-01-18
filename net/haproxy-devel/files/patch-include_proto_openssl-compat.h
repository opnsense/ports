--- include/proto/openssl-compat.h.orig	2019-01-16 17:18:07 UTC
+++ include/proto/openssl-compat.h
@@ -89,7 +89,7 @@ static inline int SSL_SESSION_set1_id_context(SSL_SESS
 }
 #endif
 
-#if (OPENSSL_VERSION_NUMBER < 0x1010000fL) || defined(LIBRESSL_VERSION_NUMBER)
+#if (OPENSSL_VERSION_NUMBER < 0x1010000fL) || ( defined(LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER < 0x20700000L )
 /*
  * Functions introduced in OpenSSL 1.1.0 and not yet present in LibreSSL
  */
