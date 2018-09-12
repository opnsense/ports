--- src/network/ssl/qsslsocket_openssl_symbols.cpp.orig	2018-06-15 07:29:31 UTC
+++ src/network/ssl/qsslsocket_openssl_symbols.cpp
@@ -137,7 +137,7 @@ void qsslSocketCannotResolveSymbolWarning(const char *
 
 #endif // QT_LINKED_OPENSSL
 
-#if QT_CONFIG(opensslv11)
+#if QT_CONFIG(opensslv11) && !defined(LIBRESSL_VERSION_NUMBER)
 
 // Below are the functions first introduced in version 1.1:
 
@@ -150,6 +150,14 @@ DEFINEFUNC2(int, BN_is_word, BIGNUM *a, a, BN_ULONG w,
 DEFINEFUNC(int, EVP_CIPHER_CTX_reset, EVP_CIPHER_CTX *c, c, return 0, return)
 DEFINEFUNC(int, EVP_PKEY_base_id, EVP_PKEY *a, a, return NID_undef, return)
 DEFINEFUNC(int, RSA_bits, RSA *a, a, return 0, return)
+#ifdef LIBRESSL_VERSION_NUMBER
+DEFINEFUNC(int, sk_num, OPENSSL_STACK *a, a, return -1, return)
+DEFINEFUNC2(void, sk_pop_free, OPENSSL_STACK *a, a, void (*b)(void*), b, return, DUMMYARG)
+DEFINEFUNC(OPENSSL_STACK *, sk_new_null, DUMMYARG, DUMMYARG, return 0, return)
+DEFINEFUNC2(void, sk_push, OPENSSL_STACK *a, a, void *b, b, return, DUMMYARG)
+DEFINEFUNC(void, sk_free, OPENSSL_STACK *a, a, return, DUMMYARG)
+DEFINEFUNC2(void *, sk_value, OPENSSL_STACK *a, a, int b, b, return 0, return)
+#else
 DEFINEFUNC(int, DSA_bits, DSA *a, a, return 0, return)
 DEFINEFUNC(int, OPENSSL_sk_num, OPENSSL_STACK *a, a, return -1, return)
 DEFINEFUNC2(void, OPENSSL_sk_pop_free, OPENSSL_STACK *a, a, void (*b)(void*), b, return, DUMMYARG)
@@ -159,6 +167,7 @@ DEFINEFUNC(void, OPENSSL_sk_free, OPENSSL_STACK *a, a,
 DEFINEFUNC2(void *, OPENSSL_sk_value, OPENSSL_STACK *a, a, int b, b, return 0, return)
 DEFINEFUNC(int, SSL_session_reused, SSL *a, a, return 0, return)
 DEFINEFUNC2(unsigned long, SSL_CTX_set_options, SSL_CTX *ctx, ctx, unsigned long op, op, return 0, return)
+#endif
 DEFINEFUNC3(size_t, SSL_get_client_random, SSL *a, a, unsigned char *out, out, size_t outlen, outlen, return 0, return)
 DEFINEFUNC3(size_t, SSL_SESSION_get_master_key, const SSL_SESSION *ses, ses, unsigned char *out, out, size_t outlen, outlen, return 0, return)
 DEFINEFUNC6(int, CRYPTO_get_ex_new_index, int class_index, class_index, long argl, argl, void *argp, argp, CRYPTO_EX_new *new_func, new_func, CRYPTO_EX_dup *dup_func, dup_func, CRYPTO_EX_free *free_func, free_func, return -1, return)
@@ -168,7 +177,9 @@ DEFINEFUNC(const SSL_METHOD *, TLS_client_method, DUMM
 DEFINEFUNC(const SSL_METHOD *, TLS_server_method, DUMMYARG, DUMMYARG, return 0, return)
 DEFINEFUNC(ASN1_TIME *, X509_getm_notBefore, X509 *a, a, return 0, return)
 DEFINEFUNC(ASN1_TIME *, X509_getm_notAfter, X509 *a, a, return 0, return)
+#ifndef LIBRESSL_VERSION_NUMBER
 DEFINEFUNC(long, X509_get_version, X509 *a, a, return -1, return)
+#endif
 DEFINEFUNC(EVP_PKEY *, X509_get_pubkey, X509 *a, a, return 0, return)
 DEFINEFUNC2(void, X509_STORE_set_verify_cb, X509_STORE *a, a, X509_STORE_CTX_verify_cb verify_cb, verify_cb, return, DUMMYARG)
 DEFINEFUNC(STACK_OF(X509) *, X509_STORE_CTX_get0_chain, X509_STORE_CTX *a, a, return 0, return)
@@ -406,7 +417,7 @@ DEFINEFUNC2(int, SSL_CTX_use_PrivateKey, SSL_CTX *a, a
 DEFINEFUNC2(int, SSL_CTX_use_RSAPrivateKey, SSL_CTX *a, a, RSA *b, b, return -1, return)
 DEFINEFUNC3(int, SSL_CTX_use_PrivateKey_file, SSL_CTX *a, a, const char *b, b, int c, c, return -1, return)
 DEFINEFUNC(X509_STORE *, SSL_CTX_get_cert_store, const SSL_CTX *a, a, return 0, return)
-#if OPENSSL_VERSION_NUMBER >= 0x10002000L
+#if OPENSSL_VERSION_NUMBER >= 0x10002000L && !defined(LIBRESSL_VERSION_NUMBER)
 DEFINEFUNC(SSL_CONF_CTX *, SSL_CONF_CTX_new, DUMMYARG, DUMMYARG, return 0, return);
 DEFINEFUNC(void, SSL_CONF_CTX_free, SSL_CONF_CTX *a, a, return ,return);
 DEFINEFUNC2(void, SSL_CONF_CTX_set_ssl_ctx, SSL_CONF_CTX *a, a, SSL_CTX *b, b, return, return);
@@ -537,6 +548,9 @@ DEFINEFUNC(void, EC_KEY_free, EC_KEY *ecdh, ecdh, retu
 DEFINEFUNC2(size_t, EC_get_builtin_curves, EC_builtin_curve * r, r, size_t nitems, nitems, return 0, return)
 #if OPENSSL_VERSION_NUMBER >= 0x10002000L
 DEFINEFUNC(int, EC_curve_nist2nid, const char *name, name, return 0, return)
+#if defined(LIBRESSL_VERSION_NUMBER)
+DEFINEFUNC3(int, SSL_CTX_set1_groups, SSL_CTX *a, a, int *b, b, int c, c, return -1, return)
+#endif // defined(LIBRESSL_VERSION_NUMBER)
 #endif // OPENSSL_VERSION_NUMBER >= 0x10002000L
 #endif // OPENSSL_NO_EC
 
@@ -782,8 +796,8 @@ static QPair<QLibrary*, QLibrary*> loadOpenSsl()
 #endif
 #if defined(SHLIB_VERSION_NUMBER) && !defined(Q_OS_QNX) // on QNX, the libs are always libssl.so and libcrypto.so
     // first attempt: the canonical name is libssl.so.<SHLIB_VERSION_NUMBER>
-    libssl->setFileNameAndVersion(QLatin1String("ssl"), QLatin1String(SHLIB_VERSION_NUMBER));
-    libcrypto->setFileNameAndVersion(QLatin1String("crypto"), QLatin1String(SHLIB_VERSION_NUMBER));
+    libssl->setFileNameAndVersion(QLatin1String("/usr/local/lib/libssl"), QLatin1String(SHLIB_VERSION_NUMBER));
+    libcrypto->setFileNameAndVersion(QLatin1String("/usr/local/lib/libcrypto"), QLatin1String(SHLIB_VERSION_NUMBER));
     if (libcrypto->load() && libssl->load()) {
         // libssl.so.<SHLIB_VERSION_NUMBER> and libcrypto.so.<SHLIB_VERSION_NUMBER> found
         return pair;
@@ -800,8 +814,8 @@ static QPair<QLibrary*, QLibrary*> loadOpenSsl()
     //  macOS's /usr/lib/libssl.dylib, /usr/lib/libcrypto.dylib will be picked up in the third
     //    attempt, _after_ <bundle>/Contents/Frameworks has been searched.
     //  iOS does not ship a system libssl.dylib, libcrypto.dylib in the first place.
-    libssl->setFileNameAndVersion(QLatin1String("ssl"), -1);
-    libcrypto->setFileNameAndVersion(QLatin1String("crypto"), -1);
+    libssl->setFileNameAndVersion(QLatin1String("/usr/local/lib/libssl"), -1);
+    libcrypto->setFileNameAndVersion(QLatin1String("/usr/local/lib/libcrypto"), -1);
     if (libcrypto->load() && libssl->load()) {
         // libssl.so.0 and libcrypto.so.0 found
         return pair;
@@ -856,7 +870,7 @@ bool q_resolveOpenSslSymbols()
     static bool symbolsResolved = false;
     static bool triedToResolveSymbols = false;
 #ifndef QT_NO_THREAD
-#if QT_CONFIG(opensslv11)
+#if QT_CONFIG(opensslv11) && !defined(LIBRESSL_VERSION_NUMBER)
     QMutexLocker locker(QMutexPool::globalInstanceGet((void *)&q_OPENSSL_init_ssl));
 #else
     QMutexLocker locker(QMutexPool::globalInstanceGet((void *)&q_SSL_library_init));
@@ -877,7 +891,7 @@ bool q_resolveOpenSslSymbols()
         // failed to load them
         return false;
 
-#if QT_CONFIG(opensslv11)
+#if QT_CONFIG(opensslv11) && !defined(LIBRESSL_VERSION_NUMBER)
 
     RESOLVEFUNC(OPENSSL_init_ssl)
     RESOLVEFUNC(OPENSSL_init_crypto)
@@ -885,17 +899,30 @@ bool q_resolveOpenSslSymbols()
     RESOLVEFUNC(EVP_CIPHER_CTX_reset)
     RESOLVEFUNC(EVP_PKEY_base_id)
     RESOLVEFUNC(RSA_bits)
+#ifdef LIBRESSL_VERSION_NUMBER
+    RESOLVEFUNC(sk_new_null)
+    RESOLVEFUNC(sk_push)
+    RESOLVEFUNC(sk_free)
+    RESOLVEFUNC(sk_num)
+    RESOLVEFUNC(sk_pop_free)
+    RESOLVEFUNC(sk_value)
+#else
     RESOLVEFUNC(OPENSSL_sk_new_null)
     RESOLVEFUNC(OPENSSL_sk_push)
     RESOLVEFUNC(OPENSSL_sk_free)
     RESOLVEFUNC(OPENSSL_sk_num)
     RESOLVEFUNC(OPENSSL_sk_pop_free)
     RESOLVEFUNC(OPENSSL_sk_value)
+#endif
     RESOLVEFUNC(DH_get0_pqg)
+#ifdef LIBRESSL_VERSION_NUMBER
+    RESOLVEFUNC(SSL_ctrl)
+#else
     RESOLVEFUNC(SSL_CTX_set_options)
+    RESOLVEFUNC(SSL_session_reused)
+#endif
     RESOLVEFUNC(SSL_get_client_random)
     RESOLVEFUNC(SSL_SESSION_get_master_key)
-    RESOLVEFUNC(SSL_session_reused)
     RESOLVEFUNC(SSL_get_session)
     RESOLVEFUNC(CRYPTO_get_ex_new_index)
     RESOLVEFUNC(TLS_method)
@@ -904,7 +931,9 @@ bool q_resolveOpenSslSymbols()
     RESOLVEFUNC(X509_STORE_CTX_get0_chain)
     RESOLVEFUNC(X509_getm_notBefore)
     RESOLVEFUNC(X509_getm_notAfter)
+#ifndef LIBRESSL_VERSION_NUMBER
     RESOLVEFUNC(X509_get_version)
+#endif
     RESOLVEFUNC(X509_get_pubkey)
     RESOLVEFUNC(X509_STORE_set_verify_cb)
     RESOLVEFUNC(CRYPTO_free)
@@ -921,7 +950,9 @@ bool q_resolveOpenSslSymbols()
 
     RESOLVEFUNC(SSL_SESSION_get_ticket_lifetime_hint)
     RESOLVEFUNC(DH_bits)
+#ifndef LIBRESSL_VERSION_NUMBER
     RESOLVEFUNC(DSA_bits)
+#endif
 
 #else // !opensslv11
 
@@ -992,10 +1023,9 @@ bool q_resolveOpenSslSymbols()
     RESOLVEFUNC(OPENSSL_add_all_algorithms_conf)
     RESOLVEFUNC(SSLeay)
 
-    if (!_q_SSLeay || q_SSLeay() >= 0x10100000L) {
+    if (!_q_SSLeay) {
         // OpenSSL 1.1 has deprecated and removed SSLeay. We consider a failure to
         // resolve this symbol as a failure to resolve symbols.
-        // The right operand of '||' above is ... a bit of paranoia.
         delete libs.first;
         delete libs.second;
         qCWarning(lcSsl, "Incompatible version of OpenSSL");
@@ -1007,8 +1037,12 @@ bool q_resolveOpenSslSymbols()
 
 #ifndef OPENSSL_NO_EC
 #if OPENSSL_VERSION_NUMBER >= 0x10002000L
-    if (q_SSLeay() >= 0x10002000L)
+    if (q_SSLeay() >= 0x10002000L) {
         RESOLVEFUNC(EC_curve_nist2nid)
+#if defined(LIBRESSL_VERSION_NUMBER)
+        RESOLVEFUNC(SSL_CTX_set1_groups)
+#endif // defined(LIBRESSL_VERSION_NUMBER)
+    }
 #endif // OPENSSL_VERSION_NUMBER >= 0x10002000L
 #endif // OPENSSL_NO_EC
 
@@ -1030,7 +1064,7 @@ bool q_resolveOpenSslSymbols()
     RESOLVEFUNC(EC_GROUP_get_degree)
 #endif
     RESOLVEFUNC(BN_num_bits)
-#if QT_CONFIG(opensslv11)
+#if QT_CONFIG(opensslv11) && !defined(LIBRESSL_VERSION_NUMBER)
     RESOLVEFUNC(BN_is_word)
 #endif
     RESOLVEFUNC(BN_mod_word)
@@ -1122,7 +1156,7 @@ bool q_resolveOpenSslSymbols()
     RESOLVEFUNC(SSL_CTX_use_RSAPrivateKey)
     RESOLVEFUNC(SSL_CTX_use_PrivateKey_file)
     RESOLVEFUNC(SSL_CTX_get_cert_store);
-#if OPENSSL_VERSION_NUMBER >= 0x10002000L
+#if OPENSSL_VERSION_NUMBER >= 0x10002000L && !defined(LIBRESSL_VERSION_NUMBER)
     RESOLVEFUNC(SSL_CONF_CTX_new);
     RESOLVEFUNC(SSL_CONF_CTX_free);
     RESOLVEFUNC(SSL_CONF_CTX_set_ssl_ctx);
