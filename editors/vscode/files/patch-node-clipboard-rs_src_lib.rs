--- node-clipboard-rs/src/lib.rs.orig	2026-03-30 13:27:40 UTC
+++ node-clipboard-rs/src/lib.rs
@@ -12,11 +12,11 @@ use std::thread;
 use std::thread;
 
 // 仅在 Linux 下导入 Wayland 相关依赖
-#[cfg(target_os = "linux")]
+#[cfg(any(target_os = "linux", target_os = "freebsd"))]
 use wayland_clipboard_listener::{ClipBoardListenMessage, WlClipboardPasteStream, WlListenType};
 
 /// 检测当前环境是否为 Wayland
-#[cfg(target_os = "linux")]
+#[cfg(any(target_os = "linux", target_os = "freebsd"))]
 fn is_wayland_environment() -> bool {
   // 检查 WAYLAND_DISPLAY 环境变量
   if std::env::var("WAYLAND_DISPLAY").is_ok() {
@@ -34,7 +34,7 @@ fn is_wayland_environment() -> bool {
 }
 
 /// 非 Linux 平台的 Wayland 环境检测（总是返回 false）
-#[cfg(not(target_os = "linux"))]
+#[cfg(not(any(target_os = "linux", target_os = "freebsd")))]
 fn is_wayland_environment() -> bool {
   false
 }
@@ -44,7 +44,7 @@ pub fn is_wayland_clipboard_available() -> bool {
 /// 返回 true 表示当前环境支持 Wayland 剪贴板监听
 #[napi]
 pub fn is_wayland_clipboard_available() -> bool {
-  #[cfg(target_os = "linux")]
+  #[cfg(any(target_os = "linux", target_os = "freebsd"))]
   {
     if !is_wayland_environment() {
       return false;
@@ -54,7 +54,7 @@ pub fn is_wayland_clipboard_available() -> bool {
     WlClipboardPasteStream::init(WlListenType::ListenOnCopy).is_ok()
   }
 
-  #[cfg(not(target_os = "linux"))]
+  #[cfg(not(any(target_os = "linux", target_os = "freebsd")))]
   {
     false
   }
@@ -820,7 +820,7 @@ pub fn clear_clipboard() -> Result<()> {
 }
 
 /// 将 Wayland 剪贴板消息转换为我们的 ClipboardData 格式
-#[cfg(target_os = "linux")]
+#[cfg(any(target_os = "linux", target_os = "freebsd"))]
 fn wayland_context_to_clipboard_data(message: ClipBoardListenMessage) -> ClipboardData {
   let mut available_formats = Vec::new();
   let mut text = None;
@@ -942,7 +942,7 @@ enum ListenerType {
   /// 使用 clipboard_rs 监听器（X11/通用）
   ClipboardRs(clipboard_rs::WatcherShutdown),
   /// 使用 Wayland 专用监听器（仅 Linux）
-  #[cfg(target_os = "linux")]
+  #[cfg(any(target_os = "linux", target_os = "freebsd"))]
   Wayland(std::sync::mpsc::Sender<()>),
 }
 
@@ -1007,7 +1007,7 @@ impl ClipboardListener {
   }
 
   /// 使用 Wayland 专用监听器监听剪贴板变化
-  #[cfg(target_os = "linux")]
+  #[cfg(any(target_os = "linux", target_os = "freebsd"))]
   fn watch_wayland(
     &mut self,
     tsfn: ThreadsafeFunction<ClipboardData, (), ClipboardData, napi::Status, false>,
@@ -1053,7 +1053,7 @@ impl ClipboardListener {
   }
 
   /// 非 Linux 平台的 Wayland 监听器（空实现）
-  #[cfg(not(target_os = "linux"))]
+  #[cfg(not(any(target_os = "linux", target_os = "freebsd")))]
   fn watch_wayland(
     &mut self,
     _tsfn: ThreadsafeFunction<ClipboardData, (), ClipboardData, napi::Status, false>,
@@ -1132,7 +1132,7 @@ impl ClipboardListener {
         ListenerType::ClipboardRs(shutdown) => {
           shutdown.stop();
         }
-        #[cfg(target_os = "linux")]
+        #[cfg(any(target_os = "linux", target_os = "freebsd"))]
         ListenerType::Wayland(stop_tx) => {
           let _ = stop_tx.send(());
         }
