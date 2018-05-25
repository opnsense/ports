--- src/vendor/openssl-sys/src/ossl10x.rs.orig	2018-05-07 18:50:12 UTC
+++ src/vendor/openssl-sys/src/ossl10x.rs
@@ -129,6 +129,12 @@ pub struct DSA {
 }
 
 #[repr(C)]
+pub struct ECDSA_SIG {
+    pub r: *mut BIGNUM,
+    pub s: *mut BIGNUM
+}
+
+#[repr(C)]
 pub struct EVP_PKEY {
     pub type_: c_int,
     pub save_type: c_int,
@@ -969,4 +975,7 @@ extern "C" {
 
     pub fn SSLeay() -> c_ulong;
     pub fn SSLeay_version(key: c_int) -> *const c_char;
+
+    #[cfg(ossl102)]
+    pub fn SSL_extension_supported(ext_type: c_uint) -> c_int;
 }
