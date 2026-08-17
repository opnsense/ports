--- adm/cmake/occt_csf.cmake.orig	2026-05-06 22:31:54 UTC
+++ adm/cmake/occt_csf.cmake
@@ -132,7 +132,6 @@ else()
       set (CSF_OpenGlLibs "GL EGL")
     endif()
     set (CSF_OpenGlesLibs "EGL GLESv2")
-    set (CSF_dl          "dl")
     if (USE_FREETYPE)
       set (CSF_fontconfig "fontconfig expat")
     endif()
