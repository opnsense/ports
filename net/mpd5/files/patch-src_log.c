--- src/log.c.orig	2025-03-07 13:34:53 UTC
+++ src/log.c
@@ -257,7 +257,7 @@ vLogPrintf(const char *fmt, va_list args) NO_THREAD_SA
 
         vsnprintf(buf, sizeof(buf), fmt, args);
 #ifdef SYSLOG_FACILITY
-        syslog(LOG_INFO, "%s", buf);
+        syslog(LOG_NOTICE, "%s", buf);
 #endif
 	pthread_cleanup_push(ConsoleCancelCleanup, gConsole.lock);
 	RWLOCK_RDLOCK(gConsole.lock);
@@ -268,7 +268,7 @@ vLogPrintf(const char *fmt, va_list args) NO_THREAD_SA
 	pthread_cleanup_pop(1);
 #ifdef SYSLOG_FACILITY
     } else {
-        vsyslog(LOG_INFO, fmt, args);
+        vsyslog(LOG_NOTICE, fmt, args);
 #endif
     }
 }
@@ -286,7 +286,7 @@ LogPrintf2(const char *fmt, ...)
 
     va_start(args, fmt);
 #ifdef SYSLOG_FACILITY
-    vsyslog(LOG_INFO, fmt, args);
+    vsyslog(LOG_NOTICE, fmt, args);
 #endif
     va_end(args);
 }
