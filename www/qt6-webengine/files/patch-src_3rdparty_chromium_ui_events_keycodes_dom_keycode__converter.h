--- src/3rdparty/chromium/ui/events/keycodes/dom/keycode_converter.h.orig	2024-06-17 12:56:06 UTC
+++ src/3rdparty/chromium/ui/events/keycodes/dom/keycode_converter.h
@@ -64,7 +64,7 @@ class KeycodeConverter {
   // Convert a DomCode into a native keycode.
   static int DomCodeToNativeKeycode(DomCode code);
 
-#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS)
+#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS) || BUILDFLAG(IS_FREEBSD)
   // Convert a XKB keycode into a DomCode.
   static DomCode XkbKeycodeToDomCode(uint32_t xkb_keycode);
 
