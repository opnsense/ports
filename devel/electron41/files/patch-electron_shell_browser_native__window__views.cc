--- electron/shell/browser/native_window_views.cc.orig	2026-04-22 19:52:17 UTC
+++ electron/shell/browser/native_window_views.cc
@@ -58,7 +58,7 @@
 #include "ui/wm/core/shadow_types.h"
 #include "ui/wm/core/window_util.h"
 
-#if BUILDFLAG(IS_LINUX)
+#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
 #include "base/notimplemented.h"
 #include "shell/browser/browser.h"
 #include "shell/browser/linux/unity_service.h"
@@ -291,7 +291,7 @@ NativeWindowViews::NativeWindowViews(const gin_helper:
     params.parent = parent->GetNativeWindow();
 
   params.native_widget = new ElectronDesktopNativeWidgetAura{this, widget()};
-#elif BUILDFLAG(IS_LINUX)
+#elif BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
   std::string name = Browser::Get()->GetName();
   // Set WM_WINDOW_ROLE.
   params.wm_role_name = "browser-window";
@@ -318,7 +318,7 @@ NativeWindowViews::NativeWindowViews(const gin_helper:
   std::string window_type;
   options.Get(options::kType, &window_type);
 
-#if BUILDFLAG(IS_LINUX)
+#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
   // Set _GTK_THEME_VARIANT to dark if we have "dark-theme" option set.
   if (options.ValueOrDefault(options::kDarkTheme, false))
     SetGTKDarkThemeEnabled(true);
@@ -439,7 +439,7 @@ NativeWindowViews::NativeWindowViews(const gin_helper:
   if (window)
     window->AddPreTargetHandler(this);
 
-#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_WIN)
+#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_WIN) || BUILDFLAG(IS_BSD)
   // The initial params.bounds was applied before the frame view existed, so
   // non-client insets weren't accounted for and bounds need to be set again.
   if (!GetRestoredFrameBorderInsets().IsEmpty())
@@ -514,7 +514,7 @@ void NativeWindowViews::SetGTKDarkThemeEnabled(bool us
 }
 
 void NativeWindowViews::SetGTKDarkThemeEnabled(bool use_dark_theme) {
-#if BUILDFLAG(IS_LINUX)
+#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
   if (x11_util::IsX11()) {
     const std::string color = use_dark_theme ? "dark" : "light";
     auto* connection = x11::Connection::Get();
@@ -575,7 +575,7 @@ void NativeWindowViews::Show() {
 
   NotifyWindowShow();
 
-#if BUILDFLAG(IS_LINUX)
+#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
   if (global_menu_bar_)
     global_menu_bar_->OnWindowMapped();
 
@@ -591,7 +591,7 @@ void NativeWindowViews::ShowInactive() {
 
   NotifyWindowShow();
 
-#if BUILDFLAG(IS_LINUX)
+#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
   if (global_menu_bar_)
     global_menu_bar_->OnWindowMapped();
 
@@ -610,7 +610,7 @@ void NativeWindowViews::Hide() {
 
   NotifyWindowHide();
 
-#if BUILDFLAG(IS_LINUX)
+#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
   if (global_menu_bar_)
     global_menu_bar_->OnWindowUnmapped();
 #endif
@@ -641,7 +641,7 @@ bool NativeWindowViews::IsEnabled() const {
 bool NativeWindowViews::IsEnabled() const {
 #if BUILDFLAG(IS_WIN)
   return ::IsWindowEnabled(GetAcceleratedWidget());
-#elif BUILDFLAG(IS_LINUX)
+#elif BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
   if (x11_util::IsX11())
     return !event_disabler_.get();
   NOTIMPLEMENTED();
@@ -866,7 +866,7 @@ void NativeWindowViews::SetBounds(const gfx::Rect& bou
   }
 #endif
 
-#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_LINUX)
+#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
   // On Linux and Windows the minimum and maximum size should be updated with
   // window size when window is not resizable.
   if (!CanResize()) {
@@ -921,7 +921,7 @@ void NativeWindowViews::SetContentSizeConstraints(
   // of this to determine whether native widget has initialized.
   if (widget() && widget()->widget_delegate())
     widget()->OnSizeConstraintsChanged();
-#if BUILDFLAG(IS_LINUX)
+#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
   if (resizable_)
     old_size_constraints_ = GetSizeConstraints();
 #endif
@@ -1136,7 +1136,7 @@ bool NativeWindowViews::IsClosable() const {
     return false;
   }
   return !(info.fState & MFS_DISABLED);
-#elif BUILDFLAG(IS_LINUX)
+#elif BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
   return true;
 #endif
 }
@@ -1176,7 +1176,7 @@ void NativeWindowViews::Center() {
 // for now to avoid breaking API contract, but should consider the long
 // term plan for this aligning with upstream.
 void NativeWindowViews::Center() {
-#if BUILDFLAG(IS_LINUX)
+#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
   auto display =
       display::Screen::Get()->GetDisplayNearestWindow(GetNativeWindow());
   gfx::Rect window_bounds_in_screen = display.work_area();
@@ -1280,7 +1280,7 @@ void NativeWindowViews::SetBackgroundColor(SkColor bac
   InvalidateRect(GetAcceleratedWidget(), nullptr, 1);
 #endif
   SkColor compositor_color = background_color;
-#if BUILDFLAG(IS_LINUX)
+#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
   // Widget background needs to stay transparent for CSD shadow regions.
   LinuxFrameLayout* frame_layout = GetLinuxFrameLayout();
   const bool uses_csd =
@@ -1402,7 +1402,7 @@ void NativeWindowViews::SetMenu(ElectronMenuModel* men
 }
 
 void NativeWindowViews::SetMenu(ElectronMenuModel* menu_model) {
-#if BUILDFLAG(IS_LINUX)
+#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
   // Remove global menu bar.
   if (global_menu_bar_ && menu_model == nullptr) {
     global_menu_bar_.reset();
@@ -1458,7 +1458,7 @@ void NativeWindowViews::SetParentWindow(NativeWindow* 
 void NativeWindowViews::SetParentWindow(NativeWindow* parent) {
   NativeWindow::SetParentWindow(parent);
 
-#if BUILDFLAG(IS_LINUX)
+#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
   if (x11_util::IsX11()) {
     auto* connection = x11::Connection::Get();
     connection->SetProperty(
@@ -1520,7 +1520,7 @@ void NativeWindowViews::SetProgressBar(double progress
                                        NativeWindow::ProgressState state) {
 #if BUILDFLAG(IS_WIN)
   taskbar_host_.SetProgressBar(GetAcceleratedWidget(), progress, state);
-#elif BUILDFLAG(IS_LINUX)
+#elif BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
   if (unity::IsRunning()) {
     unity::SetProgressFraction(progress);
   }
@@ -1646,7 +1646,7 @@ content::DesktopMediaID NativeWindowViews::GetDesktopM
 #if BUILDFLAG(IS_WIN)
   window_handle =
       reinterpret_cast<content::DesktopMediaID::Id>(accelerated_widget);
-#elif BUILDFLAG(IS_LINUX)
+#elif BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
   window_handle = static_cast<uint32_t>(accelerated_widget);
 #endif
   aura::WindowTreeHost* const host =
@@ -1776,7 +1776,7 @@ void NativeWindowViews::SetIcon(HICON window_icon, HIC
   SendMessage(hwnd, WM_SETICON, ICON_BIG,
               reinterpret_cast<LPARAM>(app_icon_.get()));
 }
-#elif BUILDFLAG(IS_LINUX)
+#elif BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
 void NativeWindowViews::SetIcon(const gfx::ImageSkia& icon) {
   auto* tree_host = views::DesktopWindowTreeHostLinux::GetHostForWidget(
       GetAcceleratedWidget());
@@ -1897,7 +1897,7 @@ bool NativeWindowViews::CanMinimize() const {
 bool NativeWindowViews::CanMinimize() const {
 #if BUILDFLAG(IS_WIN)
   return minimizable_;
-#elif BUILDFLAG(IS_LINUX)
+#elif BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
   return true;
 #endif
 }
@@ -1939,7 +1939,7 @@ std::unique_ptr<views::FrameView> NativeWindowViews::C
 #endif
 }
 
-#if BUILDFLAG(IS_LINUX)
+#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
 LinuxFrameLayout* NativeWindowViews::GetLinuxFrameLayout() {
   auto* ncv = widget()->non_client_view();
   if (!ncv)
@@ -1959,7 +1959,7 @@ void NativeWindowViews::HandleKeyboardEvent(
   if (widget_destroyed_)
     return;
 
-#if BUILDFLAG(IS_LINUX)
+#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
   if (event.windows_key_code == ui::VKEY_BROWSER_BACK)
     NotifyWindowExecuteAppCommand(kBrowserBackward);
   else if (event.windows_key_code == ui::VKEY_BROWSER_FORWARD)
@@ -1978,7 +1978,7 @@ void NativeWindowViews::OnMouseEvent(ui::MouseEvent* e
   // Alt+Click should not toggle menu bar.
   root_view_.ResetAltState();
 
-#if BUILDFLAG(IS_LINUX)
+#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
   if (event->changed_button_flags() == ui::EF_BACK_MOUSE_BUTTON)
     NotifyWindowExecuteAppCommand(kBrowserBackward);
   else if (event->changed_button_flags() == ui::EF_FORWARD_MOUSE_BUTTON)
