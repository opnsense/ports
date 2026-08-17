--- router/src/harness/src/stdx/filesystem.cc.orig	2026-06-03 12:21:17 UTC
+++ router/src/harness/src/stdx/filesystem.cc
@@ -35,6 +35,7 @@
 
 #include <array>
 #include <climits>
+#include <cstdlib>
 #include <system_error>
 
 #include "mysql/harness/stdx/expected.h"
