--- src/cron.c.orig	2018-08-10 09:00:24 UTC
+++ src/cron.c
@@ -190,10 +190,18 @@ NOEXPORT void cron_dh_param(void) {
 #endif
 
     /* update global dh_params for future configuration reloads */
+#ifndef LIBRESSL_VERSION_NUMBER
     CRYPTO_THREAD_write_lock(stunnel_locks[LOCK_DH]);
+#else
+	if(stunnel_locks[LOCK_DH]) CRYPTO_w_lock(stunnel_locks[LOCK_DH]);
+#endif
     DH_free(dh_params);
     dh_params=dh;
+#ifndef LIBRESSL_VERSION_NUMBER
     CRYPTO_THREAD_unlock(stunnel_locks[LOCK_DH]);
+#else
+	if(stunnel_locks[LOCK_DH]) CRYPTO_w_unlock(stunnel_locks[LOCK_DH]);
+#endif
 
     /* set for all sections that require it */
     for(opt=service_options.next; opt; opt=opt->next)
