$OpenBSD: patch-src_tls_tls_h,v 1.2 2017/03/04 22:09:43 sthen Exp $

Fix building with LibreSSL

--- src/tls/tls.h.orig	2018-11-05 00:04:05 UTC
+++ src/tls/tls.h
@@ -89,7 +89,7 @@ extern const char *str_tls_level(int);
 #endif
 
  /* Backwards compatibility with OpenSSL < 1.1.0 */
-#if OPENSSL_VERSION_NUMBER < 0x10100000L
+#if OPENSSL_VERSION_NUMBER < 0x10100000L || defined(LIBRESSL_VERSION_NUMBER)
 #define OpenSSL_version_num SSLeay
 #define OpenSSL_version SSLeay_version
 #define OPENSSL_VERSION SSLEAY_VERSION
@@ -104,13 +104,16 @@ extern const char *str_tls_level(int);
 #define ASN1_STRING_get0_data ASN1_STRING_data
 #define X509_getm_notBefore X509_get_notBefore
 #define X509_getm_notAfter X509_get_notAfter
+#endif
+
+#if OPENSSL_VERSION_NUMBER < 0x10100000L
 #define TLS_method SSLv23_method
 #define TLS_client_method SSLv23_client_method
 #define TLS_server_method SSLv23_server_method
 #endif
 
  /* Backwards compatibility with OpenSSL < 1.1.1 */
-#if OPENSSL_VERSION_NUMBER < 0x1010100fUL
+#if OPENSSL_VERSION_NUMBER < 0x1010100fUL || defined(LIBRESSL_VERSION_NUMBER)
 #define SSL_CTX_set_num_tickets(ctx, num) ((void)0)
 #endif
 
