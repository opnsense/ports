--- src/network/ssl/qsslsocket_openssl11_symbols_p.h.orig	2018-02-08 18:24:48 UTC
+++ src/network/ssl/qsslsocket_openssl11_symbols_p.h
@@ -75,6 +75,15 @@
 #error "You are not supposed to use this header file, include qsslsocket_openssl_symbols_p.h instead"
 #endif
 
+#if defined(LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER >= 0x20700000L
+// LibreSSL 2.7 has stack_st but not OPENSSL_STACK
+typedef struct stack_st OPENSSL_STACK; /* Use STACK_OF(...) instead */
+// From the signature in LibreSSL
+#define OPENSSL_INIT_SETTINGS void
+// https://github.com/openssl/openssl/blob/master/include/openssl/x509_vfy.h#L63
+typedef int (*X509_STORE_CTX_verify_cb)(int, X509_STORE_CTX *);
+#endif
+
 const unsigned char * q_ASN1_STRING_get0_data(const ASN1_STRING *x);
 
 Q_AUTOTEST_EXPORT BIO *q_BIO_new(const BIO_METHOD *a);
