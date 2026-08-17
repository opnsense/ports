--- components/mysqlbackup/backup_page_tracker.cc.orig	2026-06-03 12:21:17 UTC
+++ components/mysqlbackup/backup_page_tracker.cc
@@ -28,6 +28,7 @@
 
 #include <algorithm>
 #include <cerrno>
+#include <cstdlib>
 #include <string>
 
 #if defined _MSC_VER
