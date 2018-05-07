--- src/vendor/openssl-sys/src/ossl110.rs.orig	2018-03-25 15:53:20 UTC
+++ src/vendor/openssl-sys/src/ossl110.rs
@@ -8,6 +8,7 @@ pub enum BIO_METHOD {}
 pub enum CRYPTO_EX_DATA {}
 pub enum DH {}
 pub enum DSA {}
+pub enum ECDSA_SIG {}
 pub enum EVP_CIPHER {}
 pub enum EVP_MD_CTX {}
 pub enum EVP_PKEY {}
@@ -33,6 +34,11 @@ pub enum X509_ALGOR {}
 pub enum X509_VERIFY_PARAM {}
 pub enum X509_REQ {}
 
+pub const SSL_CTRL_SET_MIN_PROTO_VERSION: c_int = 123;
+pub const SSL_CTRL_SET_MAX_PROTO_VERSION: c_int = 124;
+pub const SSL_CTRL_GET_MIN_PROTO_VERSION: c_int = 130;
+pub const SSL_CTRL_GET_MAX_PROTO_VERSION: c_int = 131;
+
 pub const SSL_OP_MICROSOFT_SESS_ID_BUG: c_ulong = 0x00000000;
 pub const SSL_OP_NETSCAPE_CHALLENGE_BUG: c_ulong = 0x00000000;
 pub const SSL_OP_NETSCAPE_REUSE_CIPHER_CHANGE_BUG: c_ulong = 0x00000000;
@@ -74,6 +80,58 @@ pub fn init() {
     })
 }
 
+pub unsafe fn SSL_CTX_set_min_proto_version(ctx: *mut ::SSL_CTX, version: c_int) -> c_int {
+    ::SSL_CTX_ctrl(
+        ctx,
+        SSL_CTRL_SET_MIN_PROTO_VERSION,
+        version as c_long,
+        ptr::null_mut(),
+    ) as c_int
+}
+
+pub unsafe fn SSL_CTX_set_max_proto_version(ctx: *mut ::SSL_CTX, version: c_int) -> c_int {
+    ::SSL_CTX_ctrl(
+        ctx,
+        SSL_CTRL_SET_MAX_PROTO_VERSION,
+        version as c_long,
+        ptr::null_mut(),
+    ) as c_int
+}
+
+pub unsafe fn SSL_CTX_get_min_proto_version(ctx: *mut ::SSL_CTX) -> c_int {
+    ::SSL_CTX_ctrl(ctx, SSL_CTRL_GET_MIN_PROTO_VERSION, 0, ptr::null_mut()) as c_int
+}
+
+pub unsafe fn SSL_CTX_get_max_proto_version(ctx: *mut ::SSL_CTX) -> c_int {
+    ::SSL_CTX_ctrl(ctx, SSL_CTRL_GET_MAX_PROTO_VERSION, 0, ptr::null_mut()) as c_int
+}
+
+pub unsafe fn SSL_set_min_proto_version(s: *mut ::SSL, version: c_int) -> c_int {
+    ::SSL_ctrl(
+        s,
+        SSL_CTRL_SET_MIN_PROTO_VERSION,
+        version as c_long,
+        ptr::null_mut(),
+    ) as c_int
+}
+
+pub unsafe fn SSL_set_max_proto_version(s: *mut ::SSL, version: c_int) -> c_int {
+    ::SSL_ctrl(
+        s,
+        SSL_CTRL_SET_MAX_PROTO_VERSION,
+        version as c_long,
+        ptr::null_mut(),
+    ) as c_int
+}
+
+pub unsafe fn SSL_get_min_proto_version(s: *mut ::SSL) -> c_int {
+    ::SSL_ctrl(s, SSL_CTRL_GET_MIN_PROTO_VERSION, 0, ptr::null_mut()) as c_int
+}
+
+pub unsafe fn SSL_get_max_proto_version(s: *mut ::SSL) -> c_int {
+    ::SSL_ctrl(s, SSL_CTRL_GET_MAX_PROTO_VERSION, 0, ptr::null_mut()) as c_int
+}
+
 extern "C" {
     pub fn BIO_new(type_: *const BIO_METHOD) -> *mut BIO;
     pub fn BIO_s_file() -> *const BIO_METHOD;
@@ -206,6 +264,14 @@ extern "C" {
     pub fn SSL_CTX_get_options(ctx: *const ::SSL_CTX) -> c_ulong;
     pub fn SSL_CTX_set_options(ctx: *mut ::SSL_CTX, op: c_ulong) -> c_ulong;
     pub fn SSL_CTX_clear_options(ctx: *mut ::SSL_CTX, op: c_ulong) -> c_ulong;
+    pub fn SSL_CTX_sess_set_get_cb(
+        ctx: *mut ::SSL_CTX,
+        get_session_cb: Option<
+            unsafe extern "C" fn(*mut ::SSL, *const c_uchar, c_int, *mut c_int) -> *mut SSL_SESSION,
+        >,
+    );
+    pub fn SSL_get_client_random(ssl: *const SSL, out: *mut c_uchar, len: size_t) -> size_t;
+    pub fn SSL_get_server_random(ssl: *const SSL, out: *mut c_uchar, len: size_t) -> size_t;
     pub fn X509_getm_notAfter(x: *const ::X509) -> *mut ::ASN1_TIME;
     pub fn X509_getm_notBefore(x: *const ::X509) -> *mut ::ASN1_TIME;
     pub fn X509_get0_signature(
@@ -224,6 +290,7 @@ extern "C" {
     pub fn BIO_get_data(a: *mut ::BIO) -> *mut c_void;
     pub fn BIO_meth_new(type_: c_int, name: *const c_char) -> *mut ::BIO_METHOD;
     pub fn BIO_meth_free(biom: *mut ::BIO_METHOD);
+    // FIXME should wrap in Option
     pub fn BIO_meth_set_write(
         biom: *mut ::BIO_METHOD,
         write: unsafe extern "C" fn(*mut ::BIO, *const c_char, c_int) -> c_int,
@@ -297,4 +364,10 @@ extern "C" {
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
