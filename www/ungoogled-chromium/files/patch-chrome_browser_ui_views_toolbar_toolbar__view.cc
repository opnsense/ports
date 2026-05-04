--- chrome/browser/ui/views/toolbar/toolbar_view.cc.orig	2026-04-15 11:25:12 UTC
+++ chrome/browser/ui/views/toolbar/toolbar_view.cc
@@ -457,7 +457,7 @@ void ToolbarView::Init() {
   }
 
   std::unique_ptr<MediaToolbarButtonView> media_button;
-#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
+#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
   media_button = std::make_unique<MediaToolbarButtonView>(
       browser_view_,
       std::make_unique<MediaToolbarButtonContextualMenu>(browser_));
