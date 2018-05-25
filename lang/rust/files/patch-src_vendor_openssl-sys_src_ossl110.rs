--- src/vendor/openssl-sys/src/ossl110.rs.orig	2018-05-07 18:50:12 UTC
+++ src/vendor/openssl-sys/src/ossl110.rs
@@ -8,6 +8,7 @@ pub enum BIO_METHOD {}
 pub enum CRYPTO_EX_DATA {}
 pub enum DH {}
 pub enum DSA {}
+pub enum ECDSA_SIG {}
 pub enum EVP_CIPHER {}
 pub enum EVP_MD_CTX {}
 pub enum EVP_PKEY {}
@@ -363,4 +364,10 @@ extern "C" {
     ) -> *mut PKCS12;
     pub fn X509_REQ_get_version(req: *const X509_REQ) -> c_long;
     pub fn X509_REQ_get_subject_name(req: *const X509_REQ) -> *mut ::X509_NAME;
+    pub fn SSL_extension_supported(ext_type: c_uint) -> c_int;
+    pub fn ECDSA_SIG_get0(sig: *const ECDSA_SIG, pr: *mut *const BIGNUM, ps: *mut *const BIGNUM);
+    pub fn ECDSA_SIG_set0(sig: *mut ECDSA_SIG, pr: *mut BIGNUM, ps: *mut BIGNUM) -> c_int;
+
+    pub fn SSL_CIPHER_get_cipher_nid(c: *const ::SSL_CIPHER) -> c_int;
+    pub fn SSL_CIPHER_get_digest_nid(c: *const ::SSL_CIPHER) -> c_int;
 }
