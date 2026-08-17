--- libbase/GnashImageGif.cpp.orig	2019-01-30 23:45:03 UTC
+++ libbase/GnashImageGif.cpp
@@ -120,7 +120,7 @@ GifInput::~GifInput()
 GifInput::~GifInput()
 {
     // Clean up allocated data.
-#if GIFLIB_MAJOR==5 && GIFLIB_MINOR==1
+#if GIFLIB_MAJOR==5 && GIFLIB_MINOR>=1 || GIFLIB_MAJOR >= 6
 	DGifCloseFile(_gif, 0);
 #else
 	DGifCloseFile(_gif);
