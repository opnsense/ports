--- src/network/ssl/qsslsocket_openssl_symbols_p.h.orig	2018-06-15 07:29:31 UTC
+++ src/network/ssl/qsslsocket_openssl_symbols_p.h
@@ -356,7 +356,7 @@ int q_SSL_CTX_use_PrivateKey(SSL_CTX *a, EVP_PKEY *b);
 int q_SSL_CTX_use_RSAPrivateKey(SSL_CTX *a, RSA *b);
 int q_SSL_CTX_use_PrivateKey_file(SSL_CTX *a, const char *b, int c);
 X509_STORE *q_SSL_CTX_get_cert_store(const SSL_CTX *a);
-#if OPENSSL_VERSION_NUMBER >= 0x10002000L
+#if (OPENSSL_VERSION_NUMBER >= 0x10002000L) && !defined(LIBRESSL_VERSION_NUMBER)
 SSL_CONF_CTX *q_SSL_CONF_CTX_new();
 void q_SSL_CONF_CTX_free(SSL_CONF_CTX *a);
 void q_SSL_CONF_CTX_set_ssl_ctx(SSL_CONF_CTX *a, SSL_CTX *b);
@@ -528,6 +528,8 @@ void q_SSL_get0_alpn_selected(const SSL *ssl, const un
                               unsigned *len);
 #endif
 #endif // OPENSSL_VERSION_NUMBER >= 0x1000100fL ...
+
+int q_SSL_CTX_set1_groups(SSL_CTX *ctx, const int *groups, size_t ngroups);
 
 // Helper function
 class QDateTime;
