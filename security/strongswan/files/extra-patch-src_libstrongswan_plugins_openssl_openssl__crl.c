--- src/libstrongswan/plugins/openssl/openssl_crl.c.orig	2018-09-19 18:46:55 UTC
+++ src/libstrongswan/plugins/openssl/openssl_crl.c
@@ -50,6 +50,7 @@
 #include <credentials/certificates/x509.h>
 
 #if OPENSSL_VERSION_NUMBER < 0x10100000L
+#if !defined(LIBRESSL_VERSION_NUMBER) || LIBRESSL_VERSION_NUMBER < 0x20700000L
 static inline void X509_CRL_get0_signature(const X509_CRL *crl, ASN1_BIT_STRING **psig, X509_ALGOR **palg) {
 	if (psig) { *psig = crl->signature; }
 	if (palg) { *palg = crl->sig_alg; }
@@ -58,6 +59,7 @@ static inline void X509_CRL_get0_signatu
 #define X509_REVOKED_get0_revocationDate(r) ({ (r)->revocationDate; })
 #define X509_CRL_get0_extensions(c) ({ (c)->crl->extensions; })
 #endif
+#endif
 
 typedef struct private_openssl_crl_t private_openssl_crl_t;
 
