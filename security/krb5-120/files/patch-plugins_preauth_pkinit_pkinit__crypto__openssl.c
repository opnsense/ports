--- plugins/preauth/pkinit/pkinit_crypto_openssl.c.orig	2022-05-26 01:35:20 UTC
+++ plugins/preauth/pkinit/pkinit_crypto_openssl.c
@@ -184,7 +184,8 @@ pkcs11err(int err);
     (*_x509_pp) = PKCS7_cert_from_signer_info(_p7,_si)
 #endif
 
-#if OPENSSL_VERSION_NUMBER < 0x10100000L
+#if (defined(OPENSSL_VERSION_NUMBER) && OPENSSL_VERSION_NUMBER < 0x10100000L) || \
+     defined(LIBRESSL_VERSION_NUMBER)
 
 /* 1.1 standardizes constructor and destructor names, renaming
  * EVP_MD_CTX_{create,destroy} and deprecating ASN1_STRING_data. */
@@ -320,7 +321,7 @@ decode_bn_der(const uint8_t *der, size_t len)
     return bn;
 }
 
-#if OPENSSL_VERSION_NUMBER >= 0x10100000L
+#if OPENSSL_VERSION_NUMBER >= 0x10100000L && !defined(LIBRESSL_VERSION_NUMBER)
 static int
 params_valid(EVP_PKEY *params)
 {
@@ -346,7 +347,7 @@ params_valid(EVP_PKEY *params)
 }
 #endif
 
-#if OPENSSL_VERSION_NUMBER >= 0x10100000L
+#if OPENSSL_VERSION_NUMBER >= 0x10100000L && !defined(LIBRESSL_VERSION_NUMBER)
 
 #if OPENSSL_VERSION_NUMBER >= 0x30000000L
 static EVP_PKEY *
@@ -588,7 +589,7 @@ set_padded_derivation(EVP_PKEY_CTX *ctx)
 {
     EVP_PKEY_CTX_set_dh_pad(ctx, 1);
 }
-#elif OPENSSL_VERSION_NUMBER >= 0x10100000L
+#elif OPENSSL_VERSION_NUMBER >= 0x10100000L && !defined(LIBRESSL_VERSION_NUMBER)
 static void
 set_padded_derivation(EVP_PKEY_CTX *ctx)
 {
@@ -731,6 +732,10 @@ cleanup:
     EVP_PKEY_CTX_free(ctx);
     return pkey;
 }
+
+#if defined(LIBRESSL_VERSION_NUMBER) && !defined(static_ASN1_SEQUENCE_END_name)
+#define static_ASN1_SEQUENCE_END_name	ASN1_SEQUENCE_END_name
+#endif
 
 #if OPENSSL_VERSION_NUMBER >= 0x30000000L
 
