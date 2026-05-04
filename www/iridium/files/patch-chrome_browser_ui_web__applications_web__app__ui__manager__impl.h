--- chrome/browser/ui/web_applications/web_app_ui_manager_impl.h.orig	2026-04-15 12:07:04 UTC
+++ chrome/browser/ui/web_applications/web_app_ui_manager_impl.h
@@ -257,7 +257,7 @@ class WebAppUiManagerImpl : public BrowserCollectionOb
       UninstallCompleteCallback uninstall_complete_callback,
       webapps::UninstallResultCode uninstall_code);
 
-#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
+#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
   void ShowIPHPromoForAppsLaunchedViaLinkCapturing(Browser* browser,
                                                    const webapps::AppId& app_id,
                                                    bool is_activated);
