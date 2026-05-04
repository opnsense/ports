--- chrome/browser/ui/browser_commands.cc.orig	2026-04-15 12:07:04 UTC
+++ chrome/browser/ui/browser_commands.cc
@@ -2382,7 +2382,7 @@ void OpenUpdateChromeDialog(Browser* browser) {
   } else if (detector->is_outdated_install_no_au()) {
     ShowOutdatedUpgradeBubble(browser, browser, /*auto_update_enabled=*/false);
   } else {
-#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
+#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
     if (base::FeatureList::IsEnabled(features::kFewerUpdateConfirmations)) {
       chrome::AttemptRelaunch();
       return;
