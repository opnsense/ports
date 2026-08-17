--- libddr_null.c.orig	2025-01-19 17:00:21 UTC
+++ libddr_null.c
@@ -8,9 +8,11 @@
 
 #include "ddr_plugin.h"
 #include "ddr_ctrl.h"
+#include "ffs.h"
 #include <string.h>
 #include <stdlib.h>
 #include <assert.h>
+#include <stdint.h>
 
 /* fwd decl */
 extern ddr_plugin_t ddr_plug;
