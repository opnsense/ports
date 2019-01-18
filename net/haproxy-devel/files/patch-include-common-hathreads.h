--- include/common/hathreads.h.orig	2019-01-16 17:18:07 UTC
+++ include/common/hathreads.h
@@ -196,7 +196,7 @@ static inline unsigned long thread_isolated()
 /* TODO: thread: For now, we rely on GCC builtins but it could be a good idea to
  * have a header file regrouping all functions dealing with threads. */
 
-#if defined(__GNUC__) && (__GNUC__ < 4 || __GNUC__ == 4 && __GNUC_MINOR__ < 7) && !defined(__clang__)
+#if (defined(__GNUC__) && (__GNUC__ < 4 || __GNUC__ == 4 && __GNUC_MINOR__ < 7) && !defined(__clang__)) || (defined(__clang__) && defined(__i386__))
 /* gcc < 4.7 */
 
 #define HA_ATOMIC_ADD(val, i)        __sync_add_and_fetch(val, i)
