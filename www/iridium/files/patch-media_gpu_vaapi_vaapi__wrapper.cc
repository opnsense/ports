--- media/gpu/vaapi/vaapi_wrapper.cc.orig	2025-02-22 18:06:53 UTC
+++ media/gpu/vaapi/vaapi_wrapper.cc
@@ -78,7 +78,7 @@
 using media_gpu_vaapi::kModuleVa_prot;
 #endif
 
-#if BUILDFLAG(IS_LINUX)
+#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
 #include "base/files/file_util.h"
 #include "base/strings/string_split.h"
 #endif
