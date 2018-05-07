--- src/vendor/openssl-sys/src/ossl10x.rs.orig	2018-03-25 15:53:20 UTC
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
@@ -263,9 +269,12 @@ pub struct X509 {
     crldp: *mut c_void,
     altname: *mut c_void,
     nc: *mut c_void,
-    #[cfg(not(osslconf = "OPENSSL_NO_RFC3779"))] rfc3779_addr: *mut c_void,
-    #[cfg(not(osslconf = "OPENSSL_NO_RFC3779"))] rfc3779_asid: *mut c_void,
-    #[cfg(not(osslconf = "OPENSSL_NO_SHA"))] sha1_hash: [c_uchar; 20],
+    #[cfg(not(osslconf = "OPENSSL_NO_RFC3779"))]
+    rfc3779_addr: *mut c_void,
+    #[cfg(not(osslconf = "OPENSSL_NO_RFC3779"))]
+    rfc3779_asid: *mut c_void,
+    #[cfg(not(osslconf = "OPENSSL_NO_SHA"))]
+    sha1_hash: [c_uchar; 20],
     aux: *mut c_void,
 }
 
@@ -372,7 +381,8 @@ pub struct SSL {
     info_callback: Option<unsafe extern "C" fn(*mut SSL, c_int, c_int)>,
     error: c_int,
     error_code: c_int,
-    #[cfg(not(osslconf = "OPENSSL_NO_KRB5"))] kssl_ctx: *mut c_void,
+    #[cfg(not(osslconf = "OPENSSL_NO_KRB5"))]
+    kssl_ctx: *mut c_void,
     #[cfg(not(osslconf = "OPENSSL_NO_PSK"))]
     psk_client_callback: Option<
         unsafe extern "C" fn(*mut SSL, *const c_char, *mut c_char, c_uint, *mut c_uchar, c_uint)
@@ -396,16 +406,26 @@ pub struct SSL {
     #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
     tlsext_debug_cb:
         Option<unsafe extern "C" fn(*mut SSL, c_int, c_int, *mut c_uchar, c_int, *mut c_void)>,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tlsext_debug_arg: *mut c_void,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tlsext_hostname: *mut c_char,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] servername_done: c_int,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tlsext_status_type: c_int,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tlsext_status_expected: c_int,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tlsext_ocsp_ids: *mut c_void,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tlsext_ocsp_exts: *mut c_void,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tlsext_ocsp_resp: *mut c_uchar,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tlsext_ocsp_resplen: c_int,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tlsext_ticket_expected: c_int,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tlsext_debug_arg: *mut c_void,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tlsext_hostname: *mut c_char,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    servername_done: c_int,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tlsext_status_type: c_int,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tlsext_status_expected: c_int,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tlsext_ocsp_ids: *mut c_void,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tlsext_ocsp_exts: *mut c_void,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tlsext_ocsp_resp: *mut c_uchar,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tlsext_ocsp_resplen: c_int,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tlsext_ticket_expected: c_int,
     #[cfg(all(not(osslconf = "OPENSSL_NO_TLSEXT"), not(osslconf = "OPENSSL_NO_EC")))]
     tlsext_ecpointformatlist_length: size_t,
     #[cfg(all(not(osslconf = "OPENSSL_NO_TLSEXT"), not(osslconf = "OPENSSL_NO_EC")))]
@@ -414,28 +434,43 @@ pub struct SSL {
     tlsext_ellipticcurvelist_length: size_t,
     #[cfg(all(not(osslconf = "OPENSSL_NO_TLSEXT"), not(osslconf = "OPENSSL_NO_EC")))]
     tlsext_ellipticcurvelist: *mut c_uchar,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tlsext_opaque_prf_input: *mut c_void,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tlsext_opaque_prf_input_len: size_t,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tlsext_session_ticket: *mut c_void,
     #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tlsext_opaque_prf_input: *mut c_void,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tlsext_opaque_prf_input_len: size_t,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tlsext_session_ticket: *mut c_void,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
     tlsext_session_ticket_ext_cb: ::tls_session_ticket_ext_cb_fn,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tls_session_ticket_ext_cb_arg: *mut c_void,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tls_session_secret_cb: ::tls_session_secret_cb_fn,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tls_session_secret_cb_arg: *mut c_void,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] initial_ctx: *mut ::SSL_CTX,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tls_session_ticket_ext_cb_arg: *mut c_void,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tls_session_secret_cb: ::tls_session_secret_cb_fn,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tls_session_secret_cb_arg: *mut c_void,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    initial_ctx: *mut ::SSL_CTX,
     #[cfg(all(not(osslconf = "OPENSSL_NO_TLSEXT"), not(osslconf = "OPENSSL_NO_NEXTPROTONEG")))]
     next_proto_negotiated: *mut c_uchar,
     #[cfg(all(not(osslconf = "OPENSSL_NO_TLSEXT"), not(osslconf = "OPENSSL_NO_NEXTPROTONEG")))]
     next_proto_negotiated_len: c_uchar,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] srtp_profiles: *mut c_void,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] srtp_profile: *mut c_void,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tlsext_heartbeat: c_uint,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tlsext_hb_pending: c_uint,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tlsext_hb_seq: c_uint,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    srtp_profiles: *mut c_void,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    srtp_profile: *mut c_void,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tlsext_heartbeat: c_uint,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tlsext_hb_pending: c_uint,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tlsext_hb_seq: c_uint,
     renegotiate: c_int,
-    #[cfg(not(osslconf = "OPENSSL_NO_SRP"))] srp_ctx: ::SRP_CTX,
-    #[cfg(all(not(osslconf = "OPENSSL_NO_TLSEXT"), ossl102))] alpn_client_proto_list: *mut c_uchar,
-    #[cfg(all(not(osslconf = "OPENSSL_NO_TLSEXT"), ossl102))] alpn_client_proto_list_len: c_uint,
+    #[cfg(not(osslconf = "OPENSSL_NO_SRP"))]
+    srp_ctx: ::SRP_CTX,
+    #[cfg(all(not(osslconf = "OPENSSL_NO_TLSEXT"), ossl102))]
+    alpn_client_proto_list: *mut c_uchar,
+    #[cfg(all(not(osslconf = "OPENSSL_NO_TLSEXT"), ossl102))]
+    alpn_client_proto_list_len: c_uint,
 }
 
 #[repr(C)]
@@ -486,28 +521,46 @@ pub struct SSL_CTX {
     quiet_shutdown: c_int,
     max_send_fragment: c_uint,
 
-    #[cfg(not(osslconf = "OPENSSL_NO_ENGINE"))] client_cert_engine: *mut c_void,
+    #[cfg(not(osslconf = "OPENSSL_NO_ENGINE"))]
+    client_cert_engine: *mut c_void,
 
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tlsext_servername_callback: *mut c_void,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tlsect_servername_arg: *mut c_void,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tlsext_tick_key_name: [c_uchar; 16],
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tlsext_tick_hmac_key: [c_uchar; 16],
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tlsext_tick_aes_key: [c_uchar; 16],
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tlsext_ticket_key_cb: *mut c_void,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tlsext_status_cb: *mut c_void,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tlsext_status_arg: *mut c_void,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tlsext_opaque_prf_input_callback: *mut c_void,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tlsext_opaque_prf_input_callback_arg: *mut c_void,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tlsext_servername_callback: *mut c_void,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tlsect_servername_arg: *mut c_void,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tlsext_tick_key_name: [c_uchar; 16],
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tlsext_tick_hmac_key: [c_uchar; 16],
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tlsext_tick_aes_key: [c_uchar; 16],
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tlsext_ticket_key_cb: *mut c_void,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tlsext_status_cb: *mut c_void,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tlsext_status_arg: *mut c_void,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tlsext_opaque_prf_input_callback: *mut c_void,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tlsext_opaque_prf_input_callback_arg: *mut c_void,
 
-    #[cfg(not(osslconf = "OPENSSL_NO_PSK"))] psk_identity_hint: *mut c_void,
-    #[cfg(not(osslconf = "OPENSSL_NO_PSK"))] psk_client_callback: *mut c_void,
-    #[cfg(not(osslconf = "OPENSSL_NO_PSK"))] psk_server_callback: *mut c_void,
+    #[cfg(not(osslconf = "OPENSSL_NO_PSK"))]
+    psk_identity_hint: *mut c_void,
+    #[cfg(not(osslconf = "OPENSSL_NO_PSK"))]
+    psk_client_callback: *mut c_void,
+    #[cfg(not(osslconf = "OPENSSL_NO_PSK"))]
+    psk_server_callback: *mut c_void,
 
-    #[cfg(not(osslconf = "OPENSSL_NO_BUF_FREELISTS"))] freelist_max_len: c_uint,
-    #[cfg(not(osslconf = "OPENSSL_NO_BUF_FREELISTS"))] wbuf_freelist: *mut c_void,
-    #[cfg(not(osslconf = "OPENSSL_NO_BUF_FREELISTS"))] rbuf_freelist: *mut c_void,
+    #[cfg(not(osslconf = "OPENSSL_NO_BUF_FREELISTS"))]
+    freelist_max_len: c_uint,
+    #[cfg(not(osslconf = "OPENSSL_NO_BUF_FREELISTS"))]
+    wbuf_freelist: *mut c_void,
+    #[cfg(not(osslconf = "OPENSSL_NO_BUF_FREELISTS"))]
+    rbuf_freelist: *mut c_void,
 
-    #[cfg(not(osslconf = "OPENSSL_NO_SRP"))] srp_ctx: SRP_CTX,
+    #[cfg(not(osslconf = "OPENSSL_NO_SRP"))]
+    srp_ctx: SRP_CTX,
 
     #[cfg(all(not(osslconf = "OPENSSL_NO_TLSEXT"), not(osslconf = "OPENSSL_NO_NEXTPROTONEG")))]
     next_protos_advertised_cb: *mut c_void,
@@ -518,13 +571,19 @@ pub struct SSL_CTX {
     #[cfg(all(not(osslconf = "OPENSSL_NO_TLSEXT"), not(osslconf = "OPENSSL_NO_NEXTPROTONEG")))]
     next_proto_select_cb_arg: *mut c_void,
 
-    #[cfg(all(not(osslconf = "OPENSSL_NO_TLSEXT"), ossl101))] srtp_profiles: *mut c_void,
+    #[cfg(all(not(osslconf = "OPENSSL_NO_TLSEXT"), ossl101))]
+    srtp_profiles: *mut c_void,
 
-    #[cfg(all(not(osslconf = "OPENSSL_NO_TLSEXT"), ossl102))] srtp_profiles: *mut c_void,
-    #[cfg(all(not(osslconf = "OPENSSL_NO_TLSEXT"), ossl102))] alpn_select_cb: *mut c_void,
-    #[cfg(all(not(osslconf = "OPENSSL_NO_TLSEXT"), ossl102))] alpn_select_cb_arg: *mut c_void,
-    #[cfg(all(not(osslconf = "OPENSSL_NO_TLSEXT"), ossl102))] alpn_client_proto_list: *mut c_void,
-    #[cfg(all(not(osslconf = "OPENSSL_NO_TLSEXT"), ossl102))] alpn_client_proto_list_len: c_uint,
+    #[cfg(all(not(osslconf = "OPENSSL_NO_TLSEXT"), ossl102))]
+    srtp_profiles: *mut c_void,
+    #[cfg(all(not(osslconf = "OPENSSL_NO_TLSEXT"), ossl102))]
+    alpn_select_cb: *mut c_void,
+    #[cfg(all(not(osslconf = "OPENSSL_NO_TLSEXT"), ossl102))]
+    alpn_select_cb_arg: *mut c_void,
+    #[cfg(all(not(osslconf = "OPENSSL_NO_TLSEXT"), ossl102))]
+    alpn_client_proto_list: *mut c_void,
+    #[cfg(all(not(osslconf = "OPENSSL_NO_TLSEXT"), ossl102))]
+    alpn_client_proto_list_len: c_uint,
 
     #[cfg(all(not(osslconf = "OPENSSL_NO_TLSEXT"), not(osslconf = "OPENSSL_NO_EC"), ossl102))]
     tlsext_ecpointformatlist_length: size_t,
@@ -547,11 +606,14 @@ pub struct SSL_SESSION {
     session_id: [c_uchar; SSL_MAX_SSL_SESSION_ID_LENGTH as usize],
     sid_ctx_length: c_uint,
     sid_ctx: [c_uchar; SSL_MAX_SID_CTX_LENGTH as usize],
-    #[cfg(not(osslconf = "OPENSSL_NO_KRB5"))] krb5_client_princ_len: c_uint,
     #[cfg(not(osslconf = "OPENSSL_NO_KRB5"))]
+    krb5_client_princ_len: c_uint,
+    #[cfg(not(osslconf = "OPENSSL_NO_KRB5"))]
     krb5_client_princ: [c_uchar; SSL_MAX_KRB5_PRINCIPAL_LENGTH as usize],
-    #[cfg(not(osslconf = "OPENSSL_NO_PSK"))] psk_identity_hint: *mut c_char,
-    #[cfg(not(osslconf = "OPENSSL_NO_PSK"))] psk_identity: *mut c_char,
+    #[cfg(not(osslconf = "OPENSSL_NO_PSK"))]
+    psk_identity_hint: *mut c_char,
+    #[cfg(not(osslconf = "OPENSSL_NO_PSK"))]
+    psk_identity: *mut c_char,
     not_resumable: c_int,
     sess_cert: *mut c_void,
     peer: *mut X509,
@@ -566,7 +628,8 @@ pub struct SSL_SESSION {
     ex_data: ::CRYPTO_EX_DATA,
     prev: *mut c_void,
     next: *mut c_void,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tlsext_hostname: *mut c_char,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tlsext_hostname: *mut c_char,
     #[cfg(all(not(osslconf = "OPENSSL_NO_TLSEXT"), not(osslconf = "OPENSSL_NO_EC")))]
     tlsext_ecpointformatlist_length: size_t,
     #[cfg(all(not(osslconf = "OPENSSL_NO_TLSEXT"), not(osslconf = "OPENSSL_NO_EC")))]
@@ -575,10 +638,14 @@ pub struct SSL_SESSION {
     tlsext_ellipticcurvelist_length: size_t,
     #[cfg(all(not(osslconf = "OPENSSL_NO_TLSEXT"), not(osslconf = "OPENSSL_NO_EC")))]
     tlsext_ellipticcurvelist: *mut c_uchar,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tlsext_tick: *mut c_uchar,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tlsext_ticklen: size_t,
-    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))] tlsext_tick_lifetime_hint: c_long,
-    #[cfg(not(osslconf = "OPENSSL_NO_SRP"))] srp_username: *mut c_char,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tlsext_tick: *mut c_uchar,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tlsext_ticklen: size_t,
+    #[cfg(not(osslconf = "OPENSSL_NO_TLSEXT"))]
+    tlsext_tick_lifetime_hint: c_long,
+    #[cfg(not(osslconf = "OPENSSL_NO_SRP"))]
+    srp_username: *mut c_char,
 }
 
 #[repr(C)]
@@ -830,6 +897,12 @@ extern "C" {
         ecdh: unsafe extern "C" fn(ssl: *mut ::SSL, is_export: c_int, keylength: c_int)
             -> *mut ::EC_KEY,
     );
+    pub fn SSL_CTX_sess_set_get_cb(
+        ctx: *mut ::SSL_CTX,
+        get_session_cb: Option<
+            unsafe extern "C" fn(*mut ::SSL, *mut c_uchar, c_int, *mut c_int) -> *mut SSL_SESSION,
+        >,
+    );
     pub fn X509_get_subject_name(x: *mut ::X509) -> *mut ::X509_NAME;
     pub fn X509_get_issuer_name(x: *mut ::X509) -> *mut ::X509_NAME;
     pub fn X509_set_notAfter(x: *mut ::X509, tm: *const ::ASN1_TIME) -> c_int;
@@ -902,4 +975,7 @@ extern "C" {
 
     pub fn SSLeay() -> c_ulong;
     pub fn SSLeay_version(key: c_int) -> *const c_char;
+
+    #[cfg(ossl102)]
+    pub fn SSL_extension_supported(ext_type: c_uint) -> c_int;
 }
