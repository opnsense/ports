--- src/main/native/unix_jni_bsd.cc.orig	2026-04-05 00:58:10 UTC
+++ src/main/native/unix_jni_bsd.cc
@@ -67,7 +67,7 @@ uint64_t StatEpochMilliseconds(const portable_stat_str
       return statbuf.st_ctimespec.tv_sec * 1000L +
              statbuf.st_ctimespec.tv_nsec / 1000000;
     case STAT_MTIME:
-      return statbuf.st_mtime.tv_sec * 1000L +
+      return statbuf.st_mtimespec.tv_sec * 1000L +
              statbuf.st_mtimespec.tv_nsec / 1000000;
   }
 }
