--- components/password_manager/core/browser/features/password_features.h.orig	2026-04-15 11:25:12 UTC
+++ components/password_manager/core/browser/features/password_features.h
@@ -188,7 +188,7 @@ BASE_DECLARE_FEATURE(kReduceRequirementsForPasswordCha
 // Triggers password change glow invoking Glic from settings.
 BASE_DECLARE_FEATURE(kPasswordCheckup);
 
-#if BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
+#if BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
 // Enables "Needs access to keychain, restart chrome" bubble and banner.
 BASE_DECLARE_FEATURE(kRestartToGainAccessToKeychain);
 #endif  // BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
