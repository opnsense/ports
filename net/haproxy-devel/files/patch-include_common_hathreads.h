--- include/common/hathreads.h.orig	2018-02-09 07:39:50 UTC
+++ include/common/hathreads.h
@@ -104,7 +104,7 @@ extern THREAD_LOCAL unsigned long tid_bi
 /* TODO: thread: For now, we rely on GCC builtins but it could be a good idea to
  * have a header file regrouping all functions dealing with threads. */
 
-#if defined(__GNUC__) && (__GNUC__ < 4 || __GNUC__ == 4 && __GNUC_MINOR__ < 7) && !defined(__clang__)
+#ifdef __clang__
 /* gcc < 4.7 */
 
 #define HA_ATOMIC_ADD(val, i)        __sync_add_and_fetch(val, i)
