--- src/vendor/openssl-sys/src/lib.rs.orig	2018-03-25 15:53:20 UTC
+++ src/vendor/openssl-sys/src/lib.rs
@@ -18,6 +18,11 @@ mod ossl110;
 #[cfg(ossl110)]
 pub use ossl110::*;
 
+#[cfg(ossl111)]
+mod ossl111;
+#[cfg(ossl111)]
+pub use ossl111::*;
+
 #[cfg(libressl)]
 mod libressl;
 #[cfg(libressl)]
@@ -216,6 +221,7 @@ pub const PEM_R_NO_START_LINE: c_int = 108;
 pub const EVP_MAX_MD_SIZE: c_uint = 64;
 pub const EVP_PKEY_RSA: c_int = NID_rsaEncryption;
 pub const EVP_PKEY_HMAC: c_int = NID_hmac;
+pub const EVP_PKEY_CMAC: c_int = NID_cmac;
 pub const EVP_PKEY_DSA: c_int = NID_dsa;
 pub const EVP_PKEY_DH: c_int = NID_dhKeyAgreement;
 pub const EVP_PKEY_EC: c_int = NID_X9_62_id_ecPublicKey;
@@ -223,9 +229,29 @@ pub const EVP_PKEY_EC: c_int = NID_X9_62_id_ecPublicKe
 pub const EVP_PKEY_ALG_CTRL: c_int = 0x1000;
 
 pub const EVP_PKEY_CTRL_RSA_PADDING: c_int = EVP_PKEY_ALG_CTRL + 1;
+pub const EVP_PKEY_CTRL_RSA_PSS_SALTLEN: c_int = EVP_PKEY_ALG_CTRL + 2;
 
+pub const EVP_PKEY_CTRL_RSA_MGF1_MD: c_int = EVP_PKEY_ALG_CTRL + 5;
 pub const EVP_PKEY_CTRL_GET_RSA_PADDING: c_int = EVP_PKEY_ALG_CTRL + 6;
 
+pub const EVP_PKEY_CTRL_SET_MAC_KEY: c_int = 6;
+pub const EVP_PKEY_CTRL_CIPHER: c_int = 12;
+
+pub const EVP_PKEY_OP_KEYGEN: c_int = 1 << 2;
+pub const EVP_PKEY_OP_SIGN: c_int = 1 << 3;
+pub const EVP_PKEY_OP_VERIFY: c_int = 1 << 4;
+pub const EVP_PKEY_OP_VERIFYRECOVER: c_int = 1 << 5;
+pub const EVP_PKEY_OP_SIGNCTX: c_int = 1 << 6;
+pub const EVP_PKEY_OP_VERIFYCTX: c_int = 1 << 7;
+pub const EVP_PKEY_OP_ENCRYPT: c_int = 1 << 8;
+pub const EVP_PKEY_OP_DECRYPT: c_int = 1 << 9;
+
+pub const EVP_PKEY_OP_TYPE_SIG: c_int = EVP_PKEY_OP_SIGN | EVP_PKEY_OP_VERIFY
+    | EVP_PKEY_OP_VERIFYRECOVER | EVP_PKEY_OP_SIGNCTX
+    | EVP_PKEY_OP_VERIFYCTX;
+
+pub const EVP_PKEY_OP_TYPE_CRYPT: c_int = EVP_PKEY_OP_ENCRYPT | EVP_PKEY_OP_DECRYPT;
+
 pub const EVP_CTRL_GCM_SET_IVLEN: c_int = 0x9;
 pub const EVP_CTRL_GCM_GET_TAG: c_int = 0x10;
 pub const EVP_CTRL_GCM_SET_TAG: c_int = 0x11;
@@ -1195,9 +1221,16 @@ pub const RSA_SSLV23_PADDING: c_int = 2;
 pub const RSA_NO_PADDING: c_int = 3;
 pub const RSA_PKCS1_OAEP_PADDING: c_int = 4;
 pub const RSA_X931_PADDING: c_int = 5;
+pub const RSA_PKCS1_PSS_PADDING: c_int = 6;
 
 pub const SHA_LBLOCK: c_int = 16;
 
+pub const SSL3_AD_ILLEGAL_PARAMETER: c_int = 47;
+pub const SSL_AD_ILLEGAL_PARAMETER: c_int = SSL3_AD_ILLEGAL_PARAMETER;
+
+pub const TLS1_AD_DECODE_ERROR: c_int = 50;
+pub const SSL_AD_DECODE_ERROR: c_int = TLS1_AD_DECODE_ERROR;
+
 pub const TLS1_AD_UNRECOGNIZED_NAME: c_int = 112;
 pub const SSL_AD_UNRECOGNIZED_NAME: c_int = TLS1_AD_UNRECOGNIZED_NAME;
 
@@ -1206,6 +1239,7 @@ pub const SSL_CTRL_SET_TMP_ECDH: c_int = 4;
 pub const SSL_CTRL_EXTRA_CHAIN_CERT: c_int = 14;
 pub const SSL_CTRL_MODE: c_int = 33;
 pub const SSL_CTRL_SET_READ_AHEAD: c_int = 41;
+pub const SSL_CTRL_SET_SESS_CACHE_MODE: c_int = 44;
 pub const SSL_CTRL_SET_TLSEXT_SERVERNAME_CB: c_int = 53;
 pub const SSL_CTRL_SET_TLSEXT_SERVERNAME_ARG: c_int = 54;
 pub const SSL_CTRL_SET_TLSEXT_HOSTNAME: c_int = 55;
@@ -1243,21 +1277,21 @@ pub const SSL_VERIFY_NONE: c_int = 0;
 pub const SSL_VERIFY_PEER: c_int = 1;
 pub const SSL_VERIFY_FAIL_IF_NO_PEER_CERT: c_int = 2;
 
-#[cfg(not(any(libressl261, libressl262, libressl26x, ossl101)))]
+#[cfg(not(any(libressl261, libressl262, libressl26x, libressl27, ossl101)))]
 pub const SSL_OP_TLSEXT_PADDING: c_ulong = 0x00000010;
-#[cfg(any(libressl261, libressl262, libressl26x))]
+#[cfg(any(libressl261, libressl262, libressl26x, libressl27))]
 pub const SSL_OP_TLSEXT_PADDING: c_ulong = 0x0;
 pub const SSL_OP_DONT_INSERT_EMPTY_FRAGMENTS: c_ulong = 0x00000800;
-#[cfg(not(any(libressl261, libressl262, libressl26x)))]
+#[cfg(not(any(libressl261, libressl262, libressl26x, libressl27)))]
 pub const SSL_OP_CRYPTOPRO_TLSEXT_BUG: c_ulong = 0x80000000;
-#[cfg(any(libressl261, libressl262, libressl26x))]
+#[cfg(any(libressl261, libressl262, libressl26x, libressl27))]
 pub const SSL_OP_CRYPTOPRO_TLSEXT_BUG: c_ulong = 0x0;
 pub const SSL_OP_LEGACY_SERVER_CONNECT: c_ulong = 0x00000004;
 #[cfg(not(libressl))]
 pub const SSL_OP_SAFARI_ECDHE_ECDSA_BUG: c_ulong = 0x00000040;
-#[cfg(not(any(libressl, ossl110f)))]
+#[cfg(not(any(libressl, ossl110f, ossl111)))]
 pub const SSL_OP_ALL: c_ulong = 0x80000BFF;
-#[cfg(ossl110f)]
+#[cfg(any(ossl110f, ossl111))]
 pub const SSL_OP_ALL: c_ulong = SSL_OP_CRYPTOPRO_TLSEXT_BUG | SSL_OP_DONT_INSERT_EMPTY_FRAGMENTS
     | SSL_OP_LEGACY_SERVER_CONNECT | SSL_OP_TLSEXT_PADDING
     | SSL_OP_SAFARI_ECDHE_ECDSA_BUG;
@@ -1276,20 +1310,41 @@ pub const SSL_OP_TLS_ROLLBACK_BUG: c_ulong = 0x0080000
 #[cfg(not(libressl))]
 pub const SSL_OP_NO_SSLv3: c_ulong = 0x02000000;
 pub const SSL_OP_NO_TLSv1: c_ulong = 0x04000000;
-pub const SSL_OP_NO_TLSv1_2: c_ulong = 0x08000000;
 pub const SSL_OP_NO_TLSv1_1: c_ulong = 0x10000000;
+pub const SSL_OP_NO_TLSv1_2: c_ulong = 0x08000000;
+#[cfg(ossl111)]
+pub const SSL_OP_NO_TLSv1_3: c_ulong = 0x20000000;
 
 #[cfg(not(any(ossl101, libressl)))]
 pub const SSL_OP_NO_DTLSv1: c_ulong = 0x04000000;
 #[cfg(not(any(ossl101, libressl)))]
 pub const SSL_OP_NO_DTLSv1_2: c_ulong = 0x08000000;
-#[cfg(not(any(ossl101, libressl)))]
+#[cfg(not(any(ossl101, libressl, ossl111)))]
 pub const SSL_OP_NO_SSL_MASK: c_ulong =
     SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3 | SSL_OP_NO_TLSv1 | SSL_OP_NO_TLSv1_1 | SSL_OP_NO_TLSv1_2;
+#[cfg(ossl111)]
+pub const SSL_OP_NO_SSL_MASK: c_ulong = SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3 | SSL_OP_NO_TLSv1
+    | SSL_OP_NO_TLSv1_1 | SSL_OP_NO_TLSv1_2
+    | SSL_OP_NO_TLSv1_3;
 
 pub const SSL_FILETYPE_PEM: c_int = X509_FILETYPE_PEM;
 pub const SSL_FILETYPE_ASN1: c_int = X509_FILETYPE_ASN1;
 
+pub const SSL_SESS_CACHE_OFF: c_long = 0;
+pub const SSL_SESS_CACHE_CLIENT: c_long = 0x1;
+pub const SSL_SESS_CACHE_SERVER: c_long = 0x2;
+pub const SSL_SESS_CACHE_BOTH: c_long = SSL_SESS_CACHE_CLIENT | SSL_SESS_CACHE_SERVER;
+pub const SSL_SESS_CACHE_NO_AUTO_CLEAR: c_long = 0x80;
+pub const SSL_SESS_CACHE_NO_INTERNAL_LOOKUP: c_long = 0x100;
+pub const SSL_SESS_CACHE_NO_INTERNAL_STORE: c_long = 0x200;
+pub const SSL_SESS_CACHE_NO_INTERNAL: c_long =
+    SSL_SESS_CACHE_NO_INTERNAL_LOOKUP | SSL_SESS_CACHE_NO_INTERNAL_STORE;
+
+pub const SSL3_VERSION: c_int = 0x300;
+pub const TLS1_VERSION: c_int = 0x301;
+pub const TLS1_1_VERSION: c_int = 0x302;
+pub const TLS1_2_VERSION: c_int = 0x303;
+
 pub const TLSEXT_NAMETYPE_host_name: c_int = 0;
 
 pub const TLSEXT_STATUSTYPE_ocsp: c_int = 1;
@@ -1408,6 +1463,8 @@ pub const GEN_URI: c_int = 6;
 pub const GEN_IPADD: c_int = 7;
 pub const GEN_RID: c_int = 8;
 
+pub const DTLS1_COOKIE_LENGTH: c_uint = 256;
+
 // macros
 pub unsafe fn BIO_get_mem_data(b: *mut BIO, pp: *mut *mut c_char) -> c_long {
     BIO_ctrl(b, BIO_CTRL_INFO, 0, pp as *mut c_void)
@@ -1448,6 +1505,28 @@ pub unsafe fn EVP_PKEY_CTX_get_rsa_padding(ctx: *mut E
     )
 }
 
+pub unsafe fn EVP_PKEY_CTX_set_rsa_pss_saltlen(ctx: *mut EVP_PKEY_CTX, len: c_int) -> c_int {
+    EVP_PKEY_CTX_ctrl(
+        ctx,
+        EVP_PKEY_RSA,
+        EVP_PKEY_OP_SIGN | EVP_PKEY_OP_VERIFY,
+        EVP_PKEY_CTRL_RSA_PSS_SALTLEN,
+        len,
+        ptr::null_mut(),
+    )
+}
+
+pub unsafe fn EVP_PKEY_CTX_set_rsa_mgf1_md(ctx: *mut EVP_PKEY_CTX, md: *mut EVP_MD) -> c_int {
+    EVP_PKEY_CTX_ctrl(
+        ctx,
+        EVP_PKEY_RSA,
+        EVP_PKEY_OP_TYPE_SIG | EVP_PKEY_OP_TYPE_CRYPT,
+        EVP_PKEY_CTRL_RSA_MGF1_MD,
+        0,
+        md as *mut c_void,
+    )
+}
+
 pub unsafe fn SSL_CTX_set_mode(ctx: *mut SSL_CTX, op: c_long) -> c_long {
     SSL_CTX_ctrl(ctx, SSL_CTRL_MODE, op, ptr::null_mut())
 }
@@ -1524,6 +1603,10 @@ pub unsafe fn SSL_CTX_get_extra_chain_certs(
     SSL_CTX_ctrl(ctx, SSL_CTRL_GET_EXTRA_CHAIN_CERTS, 0, chain as *mut c_void)
 }
 
+pub unsafe fn SSL_CTX_set_session_cache_mode(ctx: *mut SSL_CTX, m: c_long) -> c_long {
+    SSL_CTX_ctrl(ctx, SSL_CTRL_SET_SESS_CACHE_MODE, m, ptr::null_mut())
+}
+
 pub unsafe fn SSL_get_tlsext_status_ocsp_resp(ssl: *mut SSL, resp: *mut *mut c_uchar) -> c_long {
     SSL_ctrl(
         ssl,
@@ -1572,6 +1655,7 @@ extern "C" {
 
     pub fn ASN1_INTEGER_get(dest: *const ASN1_INTEGER) -> c_long;
     pub fn ASN1_INTEGER_set(dest: *mut ASN1_INTEGER, value: c_long) -> c_int;
+    pub fn ASN1_INTEGER_to_BN(ai: *const ASN1_INTEGER, bn: *mut BIGNUM) -> *mut BIGNUM;
     pub fn ASN1_GENERALIZEDTIME_free(tm: *mut ASN1_GENERALIZEDTIME);
     pub fn ASN1_GENERALIZEDTIME_print(b: *mut BIO, tm: *const ASN1_GENERALIZEDTIME) -> c_int;
     pub fn ASN1_STRING_type_new(ty: c_int) -> *mut ASN1_STRING;
@@ -1843,6 +1927,20 @@ extern "C" {
         ctx: *mut BN_CTX,
     ) -> c_int;
 
+    pub fn ECDSA_SIG_new() -> *mut ECDSA_SIG;
+    pub fn ECDSA_SIG_free(sig: *mut ECDSA_SIG);
+    pub fn ECDSA_do_verify(
+        dgst: *const c_uchar,
+        dgst_len: c_int,
+        sig: *const ECDSA_SIG,
+        eckey: *mut EC_KEY,
+    ) -> c_int;
+    pub fn ECDSA_do_sign(
+        dgst: *const c_uchar,
+        dgst_len: c_int,
+        eckey: *mut EC_KEY,
+    ) -> *mut ECDSA_SIG;
+
     pub fn ERR_peek_last_error() -> c_ulong;
     pub fn ERR_get_error() -> c_ulong;
     pub fn ERR_get_error_line_data(
@@ -1855,6 +1953,8 @@ extern "C" {
     pub fn ERR_func_error_string(err: c_ulong) -> *const c_char;
     pub fn ERR_reason_error_string(err: c_ulong) -> *const c_char;
     pub fn ERR_clear_error();
+    pub fn ERR_put_error(lib: c_int, func: c_int, reason: c_int, file: *const c_char, line: c_int);
+    pub fn ERR_set_error_data(data: *mut c_char, flags: c_int);
 
     pub fn EVP_md5() -> *const EVP_MD;
     pub fn EVP_ripemd160() -> *const EVP_MD;
@@ -1869,6 +1969,7 @@ extern "C" {
     pub fn EVP_aes_128_xts() -> *const EVP_CIPHER;
     pub fn EVP_aes_128_ctr() -> *const EVP_CIPHER;
     pub fn EVP_aes_128_gcm() -> *const EVP_CIPHER;
+    pub fn EVP_aes_128_ccm() -> *const EVP_CIPHER;
     pub fn EVP_aes_128_cfb1() -> *const EVP_CIPHER;
     pub fn EVP_aes_128_cfb128() -> *const EVP_CIPHER;
     pub fn EVP_aes_128_cfb8() -> *const EVP_CIPHER;
@@ -1877,6 +1978,7 @@ extern "C" {
     pub fn EVP_aes_256_xts() -> *const EVP_CIPHER;
     pub fn EVP_aes_256_ctr() -> *const EVP_CIPHER;
     pub fn EVP_aes_256_gcm() -> *const EVP_CIPHER;
+    pub fn EVP_aes_256_ccm() -> *const EVP_CIPHER;
     pub fn EVP_aes_256_cfb1() -> *const EVP_CIPHER;
     pub fn EVP_aes_256_cfb128() -> *const EVP_CIPHER;
     pub fn EVP_aes_256_cfb8() -> *const EVP_CIPHER;
@@ -1888,6 +1990,8 @@ extern "C" {
 
     pub fn EVP_des_cbc() -> *const EVP_CIPHER;
     pub fn EVP_des_ecb() -> *const EVP_CIPHER;
+    pub fn EVP_des_ede3() -> *const EVP_CIPHER;
+    pub fn EVP_des_ede3_cbc() -> *const EVP_CIPHER;
 
     pub fn EVP_BytesToKey(
         typ: *const EVP_CIPHER,
@@ -1986,6 +2090,7 @@ extern "C" {
     pub fn EVP_PKEY_get1_DH(k: *mut EVP_PKEY) -> *mut DH;
     pub fn EVP_PKEY_get1_EC_KEY(k: *mut EVP_PKEY) -> *mut EC_KEY;
     pub fn EVP_PKEY_cmp(a: *const EVP_PKEY, b: *const EVP_PKEY) -> c_int;
+    pub fn EVP_PKEY_id(pkey: *const EVP_PKEY) -> c_int;
     pub fn EVP_PKEY_new_mac_key(
         type_: c_int,
         e: *mut ENGINE,
@@ -2003,6 +2108,7 @@ extern "C" {
     ) -> *mut EVP_PKEY;
 
     pub fn EVP_PKEY_CTX_new(k: *mut EVP_PKEY, e: *mut ENGINE) -> *mut EVP_PKEY_CTX;
+    pub fn EVP_PKEY_CTX_new_id(id: c_int, e: *mut ENGINE) -> *mut EVP_PKEY_CTX;
     pub fn EVP_PKEY_CTX_free(ctx: *mut EVP_PKEY_CTX);
     pub fn EVP_PKEY_CTX_ctrl(
         ctx: *mut EVP_PKEY_CTX,
@@ -2013,6 +2119,9 @@ extern "C" {
         p2: *mut c_void,
     ) -> c_int;
 
+    pub fn EVP_PKEY_keygen_init(ctx: *mut EVP_PKEY_CTX) -> c_int;
+    pub fn EVP_PKEY_keygen(ctx: *mut EVP_PKEY_CTX, key: *mut *mut EVP_PKEY) -> c_int;
+
     pub fn HMAC_CTX_copy(dst: *mut HMAC_CTX, src: *mut HMAC_CTX) -> c_int;
 
     pub fn OBJ_obj2nid(o: *const ASN1_OBJECT) -> c_int;
@@ -2022,6 +2131,7 @@ extern "C" {
         a: *const ASN1_OBJECT,
         no_name: c_int,
     ) -> c_int;
+    pub fn OBJ_nid2sn(nid: c_int) -> *const c_char;
 
     pub fn OCSP_BASICRESP_new() -> *mut OCSP_BASICRESP;
     pub fn OCSP_BASICRESP_free(r: *mut OCSP_BASICRESP);
@@ -2110,6 +2220,14 @@ extern "C" {
         callback: Option<PasswordCallback>,
         user_data: *mut c_void,
     ) -> *mut RSA;
+
+    pub fn PEM_read_bio_RSAPublicKey(
+        bio: *mut BIO,
+        rsa: *mut *mut RSA,
+        callback: Option<PasswordCallback>,
+        user_data: *mut c_void,
+    ) -> *mut RSA;
+
     pub fn PEM_read_bio_RSA_PUBKEY(
         bio: *mut BIO,
         rsa: *mut *mut RSA,
@@ -2344,6 +2462,7 @@ extern "C" {
     pub fn SSL_get_peer_cert_chain(ssl: *const SSL) -> *mut stack_st_X509;
     pub fn SSL_get_ssl_method(ssl: *mut SSL) -> *const SSL_METHOD;
     pub fn SSL_get_version(ssl: *const SSL) -> *const c_char;
+    pub fn SSL_version(ssl: *const SSL) -> c_int;
     pub fn SSL_state_string(ssl: *const SSL) -> *const c_char;
     pub fn SSL_state_string_long(ssl: *const SSL) -> *const c_char;
     pub fn SSL_set_verify(
@@ -2369,6 +2488,16 @@ extern "C" {
         ctx: *mut SSL,
         dh: unsafe extern "C" fn(ssl: *mut SSL, is_export: c_int, keylength: c_int) -> *mut DH,
     );
+    pub fn SSL_export_keying_material(
+        s: *mut SSL,
+        out: *mut c_uchar,
+        olen: size_t,
+        label: *const c_char,
+        llen: size_t,
+        context: *const c_uchar,
+        contextlen: size_t,
+        use_context: c_int,
+    ) -> c_int;
 
     #[cfg(not(any(osslconf = "OPENSSL_NO_COMP", libressl)))]
     pub fn SSL_COMP_get_name(comp: *const COMP_METHOD) -> *const c_char;
@@ -2436,6 +2565,14 @@ extern "C" {
         ctx: *mut SSL_CTX,
         dh: unsafe extern "C" fn(ssl: *mut SSL, is_export: c_int, keylength: c_int) -> *mut DH,
     );
+    pub fn SSL_CTX_sess_set_new_cb(
+        ctx: *mut SSL_CTX,
+        new_session_cb: Option<unsafe extern "C" fn(*mut SSL, *mut SSL_SESSION) -> c_int>,
+    );
+    pub fn SSL_CTX_sess_set_remove_cb(
+        ctx: *mut SSL_CTX,
+        remove_session_cb: Option<unsafe extern "C" fn(*mut SSL_CTX, *mut SSL_SESSION)>,
+    );
 
     #[cfg(not(any(ossl101, libressl)))]
     pub fn SSL_CTX_get0_certificate(ctx: *const SSL_CTX) -> *mut X509;
@@ -2474,6 +2611,7 @@ extern "C" {
                 -> c_uint,
         >,
     );
+
     pub fn SSL_select_next_proto(
         out: *mut *mut c_uchar,
         outlen: *mut c_uchar,
@@ -2489,9 +2627,9 @@ extern "C" {
     );
     pub fn SSL_get_session(s: *const SSL) -> *mut SSL_SESSION;
     pub fn SSL_set_session(ssl: *mut SSL, session: *mut SSL_SESSION) -> c_int;
-    #[cfg(not(any(ossl101, libressl, ossl110f)))]
+    #[cfg(not(any(ossl101, libressl, ossl110f, ossl111)))]
     pub fn SSL_is_server(s: *mut SSL) -> c_int;
-    #[cfg(ossl110f)]
+    #[cfg(any(ossl110f, ossl111))]
     pub fn SSL_is_server(s: *const SSL) -> c_int;
 
     pub fn SSL_SESSION_free(s: *mut SSL_SESSION);
@@ -2540,6 +2678,7 @@ extern "C" {
     pub fn X509_sign(x: *mut X509, pkey: *mut EVP_PKEY, md: *const EVP_MD) -> c_int;
     pub fn X509_get_pubkey(x: *mut X509) -> *mut EVP_PKEY;
     pub fn X509_to_X509_REQ(x: *mut X509, pkey: *mut EVP_PKEY, md: *const EVP_MD) -> *mut X509_REQ;
+    pub fn X509_verify_cert(ctx: *mut X509_STORE_CTX) -> c_int;
     pub fn X509_verify_cert_error_string(n: c_long) -> *const c_char;
     pub fn X509_get1_ocsp(x: *mut X509) -> *mut stack_st_OPENSSL_STRING;
     pub fn X509_check_issued(issuer: *mut X509, subject: *mut X509) -> c_int;
@@ -2573,6 +2712,14 @@ extern "C" {
     pub fn X509_STORE_add_cert(store: *mut X509_STORE, x: *mut X509) -> c_int;
     pub fn X509_STORE_set_default_paths(store: *mut X509_STORE) -> c_int;
 
+    pub fn X509_STORE_CTX_new() -> *mut X509_STORE_CTX;
+    pub fn X509_STORE_CTX_cleanup(ctx: *mut X509_STORE_CTX);
+    pub fn X509_STORE_CTX_init(
+        ctx: *mut X509_STORE_CTX,
+        store: *mut X509_STORE,
+        x509: *mut X509,
+        chain: *mut stack_st_X509,
+    ) -> c_int;
     pub fn X509_STORE_CTX_free(ctx: *mut X509_STORE_CTX);
     pub fn X509_STORE_CTX_get_current_cert(ctx: *mut X509_STORE_CTX) -> *mut X509;
     pub fn X509_STORE_CTX_get_error(ctx: *mut X509_STORE_CTX) -> c_int;
@@ -2704,4 +2851,28 @@ extern "C" {
     pub fn FIPS_mode_set(onoff: c_int) -> c_int;
     #[cfg(not(libressl))]
     pub fn FIPS_mode() -> c_int;
+
+    pub fn SSL_CTX_set_cookie_generate_cb(
+        s: *mut SSL_CTX,
+        cb: Option<
+            extern "C" fn(ssl: *mut SSL, cookie: *mut c_uchar, cookie_len: *mut c_uint) -> c_int,
+        >,
+    );
+
+    #[cfg(ossl110)]
+    pub fn SSL_CTX_set_cookie_verify_cb(
+        s: *mut SSL_CTX,
+        cb: Option<
+            extern "C" fn(ssl: *mut SSL, cookie: *const c_uchar, cookie_len: c_uint) -> c_int,
+        >,
+    );
+
+    #[cfg(not(ossl110))]
+    pub fn SSL_CTX_set_cookie_verify_cb(
+        s: *mut SSL_CTX,
+        cb: Option<extern "C" fn(ssl: *mut SSL, cookie: *mut c_uchar, cookie_len: c_uint) -> c_int>,
+    );
+
+    pub fn EVP_MD_size(md: *const EVP_MD) -> c_int;
+    pub fn EVP_get_cipherbyname(name: *const c_char) -> *const EVP_CIPHER;
 }
