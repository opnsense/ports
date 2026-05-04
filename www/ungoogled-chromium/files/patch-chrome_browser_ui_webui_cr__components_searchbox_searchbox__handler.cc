--- chrome/browser/ui/webui/cr_components/searchbox/searchbox_handler.cc.orig	2026-04-15 11:25:12 UTC
+++ chrome/browser/ui/webui/cr_components/searchbox/searchbox_handler.cc
@@ -168,7 +168,7 @@ const char* kMacShareIconResourceName =
 #elif BUILDFLAG(IS_WIN)
 const char* kWinShareIconResourceName =
     "//resources/cr_components/searchbox/icons/win_share.svg";
-#elif BUILDFLAG(IS_LINUX)
+#elif BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
 const char* kLinuxShareIconResourceName =
     "//resources/cr_components/searchbox/icons/share.svg";
 #else
@@ -226,7 +226,7 @@ static void DefineChromeRefreshRealboxIcons() {
 #elif BUILDFLAG(IS_WIN)
   kWinShareIconResourceName =
       "//resources/cr_components/searchbox/icons/win_share_cr23.svg";
-#elif BUILDFLAG(IS_LINUX)
+#elif BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
   kLinuxShareIconResourceName =
       "//resources/cr_components/searchbox/icons/share_cr23.svg";
 #else
@@ -600,7 +600,7 @@ std::string SearchboxHandler::AutocompleteIconToResour
   if (icon.name == omnibox::kShareWinChromeRefreshIcon.name) {
     return kWinShareIconResourceName;
   }
-#elif BUILDFLAG(IS_LINUX)
+#elif BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
   if (icon.name == omnibox::kShareLinuxChromeRefreshIcon.name) {
     return kLinuxShareIconResourceName;
   }
