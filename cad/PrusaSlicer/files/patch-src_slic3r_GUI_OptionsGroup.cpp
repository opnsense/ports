--- src/slic3r/GUI/OptionsGroup.cpp.orig	2026-05-19 09:09:17 UTC
+++ src/slic3r/GUI/OptionsGroup.cpp
@@ -1265,7 +1265,7 @@ void ogStaticText::SetPathEnd(const std::string& link)
 
 void ogStaticText::SetPathEnd(const std::string& link)
 {
-#ifndef __linux__
+#if !defined(__linux__) && !defined(__FreeBSD__)
 
     Bind(wxEVT_ENTER_WINDOW, [this, link](wxMouseEvent& event) {
         SetToolTip(OptionsGroup::get_url(get_app_config()->get("suppress_hyperlinks") != "1" ? link : std::string()));
@@ -1318,7 +1318,7 @@ void ogStaticText::FocusText(bool focus)
 
     SetFont(focus ? Slic3r::GUI::wxGetApp().link_font() :
         Slic3r::GUI::wxGetApp().normal_font());
-#ifdef __linux__
+#if defined(__linux__) || defined(__FreeBSD__)
     this->GetContainingSizer()->Layout();
 #endif
     Refresh();
