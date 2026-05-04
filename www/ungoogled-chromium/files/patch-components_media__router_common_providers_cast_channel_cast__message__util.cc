--- components/media_router/common/providers/cast/channel/cast_message_util.cc.orig	2026-04-15 11:25:12 UTC
+++ components/media_router/common/providers/cast/channel/cast_message_util.cc
@@ -156,7 +156,7 @@ int GetVirtualConnectPlatformValue() {
   return 4;
 #elif BUILDFLAG(IS_CHROMEOS)
   return 5;
-#elif BUILDFLAG(IS_LINUX)
+#elif BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
   return 6;
 #else
   return 0;
