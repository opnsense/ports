--- src/vendor/openssl-sys/src/libressl/mod.rs.orig	2018-03-25 15:53:20 UTC
+++ src/vendor/openssl-sys/src/libressl/mod.rs
@@ -134,6 +134,12 @@ pub struct DSA {
 }
 
 #[repr(C)]
+pub struct ECDSA_SIG {
+    pub r: *mut ::BIGNUM,
+    pub s: *mut ::BIGNUM,
+}
+
+#[repr(C)]
 pub struct EVP_PKEY {
     pub type_: c_int,
     pub save_type: c_int,
@@ -267,7 +273,8 @@ pub struct X509 {
     crldp: *mut c_void,
     altname: *mut c_void,
     nc: *mut c_void,
-    #[cfg(not(osslconf = "OPENSSL_NO_SHA"))] sha1_hash: [c_uchar; 20],
+    #[cfg(not(osslconf = "OPENSSL_NO_SHA"))]
+    sha1_hash: [c_uchar; 20],
     aux: *mut c_void,
 }
 
@@ -330,9 +337,9 @@ pub const SSL_CTRL_OPTIONS: c_int = 32;
 pub const SSL_CTRL_CLEAR_OPTIONS: c_int = 77;
 pub const SSL_CTRL_SET_ECDH_AUTO: c_int = 94;
 
-#[cfg(any(libressl261, libressl262, libressl26x))]
+#[cfg(any(libressl261, libressl262, libressl26x, libressl27))]
 pub const SSL_OP_ALL: c_ulong = 0x4;
-#[cfg(not(any(libressl261, libressl262, libressl26x)))]
+#[cfg(not(any(libressl261, libressl262, libressl26x, libressl27)))]
 pub const SSL_OP_ALL: c_ulong = 0x80000014;
 pub const SSL_OP_CISCO_ANYCONNECT: c_ulong = 0x0;
 pub const SSL_OP_NO_COMPRESSION: c_ulong = 0x0;
@@ -345,9 +352,9 @@ pub const SSL_OP_MICROSOFT_BIG_SSLV3_BUFFER: c_ulong =
 pub const SSL_OP_SSLEAY_080_CLIENT_DH_BUG: c_ulong = 0x0;
 pub const SSL_OP_TLS_D5_BUG: c_ulong = 0x0;
 pub const SSL_OP_TLS_BLOCK_PADDING_BUG: c_ulong = 0x0;
-#[cfg(any(libressl261, libressl262, libressl26x))]
+#[cfg(any(libressl261, libressl262, libressl26x, libressl27))]
 pub const SSL_OP_SINGLE_ECDH_USE: c_ulong = 0x0;
-#[cfg(not(any(libressl261, libressl262, libressl26x)))]
+#[cfg(not(any(libressl261, libressl262, libressl26x, libressl27)))]
 pub const SSL_OP_SINGLE_ECDH_USE: c_ulong = 0x00080000;
 pub const SSL_OP_SINGLE_DH_USE: c_ulong = 0x00100000;
 pub const SSL_OP_NO_SSLv2: c_ulong = 0x0;
@@ -526,6 +533,12 @@ extern "C" {
         ctx: *mut ::SSL_CTX,
         ecdh: unsafe extern "C" fn(ssl: *mut ::SSL, is_export: c_int, keylength: c_int)
             -> *mut ::EC_KEY,
+    );
+    pub fn SSL_CTX_sess_set_get_cb(
+        ctx: *mut ::SSL_CTX,
+        get_session_cb: Option<
+            unsafe extern "C" fn(*mut ::SSL, *mut c_uchar, c_int, *mut c_int) -> *mut SSL_SESSION,
+        >,
     );
     pub fn X509_get_subject_name(x: *mut ::X509) -> *mut ::X509_NAME;
     pub fn X509_get_issuer_name(x: *mut ::X509) -> *mut ::X509_NAME;
