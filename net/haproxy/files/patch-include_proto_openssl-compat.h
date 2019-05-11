--- include/proto/openssl-compat.h.orig	2019-05-11 04:00:55 UTC
+++ include/proto/openssl-compat.h
@@ -89,7 +89,7 @@ static inline int SSL_SESSION_set1_id_co
 }
 #endif
 
-#if (OPENSSL_VERSION_NUMBER < 0x1010000fL) || defined(LIBRESSL_VERSION_NUMBER)
+#if (OPENSSL_VERSION_NUMBER < 0x1010000fL)
 /*
  * Functions introduced in OpenSSL 1.1.0 and not yet present in LibreSSL
  */
