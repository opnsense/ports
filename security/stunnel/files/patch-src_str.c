--- src/str.c.orig	2018-08-10 08:40:28 UTC
+++ src/str.c
@@ -456,18 +456,30 @@ NOEXPORT void str_leak_debug(const ALLOC
         entry->alloc_file!=alloc_list->alloc_file;
 
     if(new_entry) { /* the file:line pair was encountered for the first time */
+#ifndef LIBRESSL_VERSION_NUMBER
         CRYPTO_THREAD_write_lock(stunnel_locks[LOCK_LEAK_HASH]);
+#else
+	if(stunnel_locks[LOCK_LEAK_HASH]) CRYPTO_w_lock(stunnel_locks[LOCK_LEAK_HASH]);
+#endif
         entry=leak_search(alloc_list); /* the list may have changed */
         if(entry->alloc_line==0) {
             if(entries>LEAK_TABLE_SIZE-100) { /* this should never happen */
+#ifndef LIBRESSL_VERSION_NUMBER
                 CRYPTO_THREAD_unlock(stunnel_locks[LOCK_LEAK_HASH]);
+#else
+		if(stunnel_locks[LOCK_LEAK_HASH]) CRYPTO_w_unlock(stunnel_locks[LOCK_LEAK_HASH]);
+#endif
                 return;
             }
             entries++;
             entry->alloc_line=alloc_list->alloc_line;
             entry->alloc_file=alloc_list->alloc_file;
         }
+#ifndef LIBRESSL_VERSION_NUMBER
         CRYPTO_THREAD_unlock(stunnel_locks[LOCK_LEAK_HASH]);
+#else
+	if(stunnel_locks[LOCK_LEAK_HASH]) CRYPTO_w_unlock(stunnel_locks[LOCK_LEAK_HASH]);
+#endif
     }
 
     /* for performance we try to avoid calling CRYPTO_atomic_add() here */
@@ -498,7 +510,11 @@ NOEXPORT void str_leak_debug(const ALLOC
     }
     /* we *may* need to allocate a new leak_results entry */
     /* locking is slow, so we try to avoid it if possible */
+#ifndef LIBRESSL_VERSION_NUMBER
     CRYPTO_THREAD_write_lock(stunnel_locks[LOCK_LEAK_RESULTS]);
+#else
+	if(stunnel_locks[LOCK_LEAK_RESULTS]) CRYPTO_w_lock(stunnel_locks[LOCK_LEAK_RESULTS]);
+#endif
     if(entry->max==0) { /* the table may have changed */
         leak_results[leak_result_num]=entry;
         entry->max=allocations;
@@ -506,7 +522,11 @@ NOEXPORT void str_leak_debug(const ALLOC
     } else { /* gracefully handle the race condition */
         entry->max=allocations;
     }
+#ifndef LIBRESSL_VERSION_NUMBER
     CRYPTO_THREAD_unlock(stunnel_locks[LOCK_LEAK_RESULTS]);
+#else
+	if(stunnel_locks[LOCK_LEAK_HASH]) CRYPTO_w_unlock(stunnel_locks[LOCK_LEAK_HASH]);
+#endif
 }
 
 /* O(1) hash table lookup */
