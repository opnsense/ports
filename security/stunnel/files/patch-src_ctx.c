--- src/ctx.c.orig	2018-08-10 08:45:29 UTC
+++ src/ctx.c
@@ -353,9 +353,17 @@ NOEXPORT int dh_init(SERVICE_OPTIONS *se
         DH_free(dh);
         return 0; /* OK */
     }
+#ifndef LIBRESSL_VERSION_NUMBER
     CRYPTO_THREAD_read_lock(stunnel_locks[LOCK_DH]);
+#else
+	if(stunnel_locks[LOCK_DH]) CRYPTO_r_lock(stunnel_locks[LOCK_DH]);
+#endif
     SSL_CTX_set_tmp_dh(section->ctx, dh_params);
+#ifndef LIBRESSL_VERSION_NUMBER
     CRYPTO_THREAD_unlock(stunnel_locks[LOCK_DH]);
+#else
+	if(stunnel_locks[LOCK_DH]) CRYPTO_w_unlock(stunnel_locks[LOCK_DH]);
+#endif
     dh_needed=1; /* generate temporary DH parameters in cron */
     section->option.dh_needed=1; /* update this context */
     s_log(LOG_INFO, "Using dynamic DH parameters");
@@ -414,7 +422,7 @@ NOEXPORT int ecdh_init(SERVICE_OPTIONS *
 /**************************************** initialize OpenSSL CONF */
 
 NOEXPORT int conf_init(SERVICE_OPTIONS *section) {
-#if OPENSSL_VERSION_NUMBER>=0x10002000L
+#if (OPENSSL_VERSION_NUMBER>=0x10002000L) && !defined(LIBRESSL_VERSION_NUMBER)
     SSL_CONF_CTX *cctx;
     NAME_LIST *curr;
     char *cmd, *param;
@@ -983,7 +991,11 @@ NOEXPORT void session_cache_save(CLI *c,
     sess=SSL_get1_session(c->ssl);
 #endif
 
+#ifndef LIBRESSL_VERSION_NUMBER
     CRYPTO_THREAD_write_lock(stunnel_locks[LOCK_SESSION]);
+#else
+	if(stunnel_locks[LOCK_SESSION]) CRYPTO_w_lock(stunnel_locks[LOCK_SESSION]);
+#endif
     if(c->opt->option.delayed_lookup) {
         old=c->opt->session;
         c->opt->session=sess;
@@ -996,7 +1008,11 @@ NOEXPORT void session_cache_save(CLI *c,
             old=NULL;
         }
     }
+#ifndef LIBRESSL_VERSION_NUMBER
     CRYPTO_THREAD_unlock(stunnel_locks[LOCK_SESSION]);
+#else
+	if(stunnel_locks[LOCK_SESSION]) CRYPTO_w_unlock(stunnel_locks[LOCK_SESSION]);
+#endif
 
     if(old)
         SSL_SESSION_free(old);
@@ -1227,7 +1243,7 @@ NOEXPORT void info_callback(const SSL *s
 
     c=SSL_get_ex_data((SSL *)ssl, index_ssl_cli);
     if(c) {
-#if OPENSSL_VERSION_NUMBER>=0x10100000L
+#if (OPENSSL_VERSION_NUMBER>=0x10100000L) && !defined(LIBRESSL_VERSION_NUMBER)
         OSSL_HANDSHAKE_STATE state=SSL_get_state(ssl);
 #else
         int state=SSL_get_state((SSL *)ssl);
