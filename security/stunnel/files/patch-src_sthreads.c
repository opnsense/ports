--- src/sthreads.c.orig	2018-08-10 09:03:02 UTC
+++ src/sthreads.c
@@ -115,7 +115,7 @@ void thread_id_init(void) {
 /**************************************** locking */
 
 /* we only need to initialize locking with OpenSSL older than 1.1.0 */
-#if OPENSSL_VERSION_NUMBER<0x10100004L
+#if (OPENSSL_VERSION_NUMBER<0x10100004L) || defined(LIBRESSL_VERSION_NUMBER)
 
 #ifdef USE_PTHREAD
 
@@ -224,7 +224,7 @@ NOEXPORT int s_atomic_add(int *val, int 
 
 CRYPTO_RWLOCK *stunnel_locks[STUNNEL_LOCKS];
 
-#if OPENSSL_VERSION_NUMBER<0x10100004L
+#if (OPENSSL_VERSION_NUMBER<0x10100004L) || defined(LIBRESSL_VERSION_NUMBER)
 
 #ifdef USE_OS_THREADS
 
