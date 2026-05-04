--- third_party/blink/renderer/core/origin_trials/origin_trial_context.cc.orig	2026-04-15 11:25:12 UTC
+++ third_party/blink/renderer/core/origin_trials/origin_trial_context.cc
@@ -559,7 +559,7 @@ bool OriginTrialContext::CanEnableTrialFromName(const 
 
   if (trial_name == "WebAppInstallation") {
 #if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX) || \
-    BUILDFLAG(IS_CHROMEOS)
+    BUILDFLAG(IS_CHROMEOS) || BUILDFLAG(IS_BSD)
     return base::FeatureList::IsEnabled(blink::features::kWebAppInstallation);
 #else
     return false;
