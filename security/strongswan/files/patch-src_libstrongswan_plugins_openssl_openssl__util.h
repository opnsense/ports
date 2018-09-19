--- src/libstrongswan/plugins/openssl/openssl_util.h.orig	2018-09-19 18:32:30 UTC
+++ src/libstrongswan/plugins/openssl/openssl_util.h
@@ -146,6 +146,7 @@ time_t openssl_asn1_to_time(ASN1_TIME *t
  * Macros to define fallback getters/setters to access keys (BIGNUM*) for types
  * that were made opaque with OpenSSL 1.1.0.
  */
+#if defined(LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER < 0x20700000L
 #define OPENSSL_KEY_FALLBACK(...) VA_ARGS_DISPATCH(OPENSSL_KEY_FALLBACK, __VA_ARGS__)(__VA_ARGS__)
 #define OPENSSL_KEY_FALLBACK3(type, k1, k2) \
 __attribute__((unused)) \
@@ -179,5 +180,8 @@ static inline int type##_set0_##name(typ
 	if (k2) { BN_clear_free(o->k2); o->k2 = k2; } \
 	if (k3) { BN_clear_free(o->k3); o->k3 = k3; } \
 	return 1; }
+#else
+#define OPENSSL_KEY_FALLBACK(...)
+#endif
 
 #endif /** OPENSSL_UTIL_H_ @}*/
