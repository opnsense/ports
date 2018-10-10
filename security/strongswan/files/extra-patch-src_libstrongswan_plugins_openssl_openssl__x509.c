--- src/libstrongswan/plugins/openssl/openssl_x509.c.orig	2018-09-19 18:43:17 UTC
+++ src/libstrongswan/plugins/openssl/openssl_x509.c
@@ -62,11 +62,13 @@
 
 /* added with 1.0.2 */
 #if OPENSSL_VERSION_NUMBER < 0x10002000L
+#if !defined(LIBRESSL_VERSION_NUMBER) || LIBRESSL_VERSION_NUMBER < 0x20700000L
 static inline void X509_get0_signature(ASN1_BIT_STRING **psig, X509_ALGOR **palg, const X509 *x) {
 	if (psig) { *psig = x->signature; }
 	if (palg) { *palg = x->sig_alg; }
 }
 #endif
+#endif
 
 /* added with 1.1.0 when X509 etc. was made opaque */
 #if OPENSSL_VERSION_NUMBER < 0x10100000L
