--- external/dmon/dmon.h.orig	2026-04-05 11:41:50 UTC
+++ external/dmon/dmon.h
@@ -143,7 +143,7 @@ DMON_API_DECL void dmon_unwatch(dmon_watch_id id);
 #if defined(_WIN32) || defined(_WIN64)
 #    undef DMON_OS_WINDOWS
 #    define DMON_OS_WINDOWS 1
-#elif defined(__linux__)
+#elif defined(__linux__) || defined(__FreeBSD__)
 #    undef DMON_OS_LINUX
 #    define DMON_OS_LINUX 1
 #elif defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__)
@@ -173,7 +173,7 @@ DMON_API_DECL void dmon_unwatch(dmon_watch_id id);
 #    include <dirent.h>
 #    include <errno.h>
 #    include <fcntl.h>
-#    include <linux/limits.h>
+//#    include <linux/limits.h>
 #    include <pthread.h>
 #    include <sys/inotify.h>
 #    include <sys/stat.h>
