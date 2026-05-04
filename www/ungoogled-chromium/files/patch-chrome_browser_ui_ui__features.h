--- chrome/browser/ui/ui_features.h.orig	2026-04-15 11:25:12 UTC
+++ chrome/browser/ui/ui_features.h
@@ -25,7 +25,7 @@ BASE_DECLARE_FEATURE(kBrowserWidgetCacheThemeService);
 
 BASE_DECLARE_FEATURE(kCreateNewTabGroupAppMenuTopLevel);
 
-#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
+#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
 BASE_DECLARE_FEATURE(kDseIntegrity);
 BASE_DECLARE_FEATURE(kFewerUpdateConfirmations);
 #endif
@@ -66,7 +66,7 @@ BASE_DECLARE_FEATURE_PARAM(int,
 BASE_DECLARE_FEATURE_PARAM(int, kSeparateDefaultAndPinPromptMessageVersion);
 #endif  // BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC)
 
-#if BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN) || BUILDFLAG(IS_LINUX)
+#if BUILDFLAG(IS_MAC) || BUILDFLAG(IS_WIN) || BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
 // When enabled, user may see the session restore UI flow.
 BASE_DECLARE_FEATURE(kSessionRestoreInfobar);
 
@@ -285,7 +285,7 @@ BASE_DECLARE_FEATURE(kViewsFirstRunDialog);
 BASE_DECLARE_FEATURE(kViewsJSAppModalDialog);
 #endif
 
-#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS)
+#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS) || BUILDFLAG(IS_BSD)
 BASE_DECLARE_FEATURE(kUsePortalAccentColor);
 #endif
 
@@ -390,7 +390,7 @@ BASE_DECLARE_FEATURE(kTabGroupsFocusing);
 BASE_DECLARE_FEATURE_PARAM(bool, kTabGroupsFocusingPinnedTabs);
 BASE_DECLARE_FEATURE_PARAM(bool, kTabGroupsFocusingDefaultToFocused);
 
-#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
+#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
 BASE_DECLARE_FEATURE(kUpdaterUI);
 #endif
 
