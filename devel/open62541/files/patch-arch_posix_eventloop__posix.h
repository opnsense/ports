--- arch/posix/eventloop_posix.h.orig	2026-07-16 11:01:44 UTC
+++ arch/posix/eventloop_posix.h
@@ -277,7 +277,9 @@ typedef int SOCKET;
 
 #ifndef __ANDROID__
 #ifndef __APPLE__
+#ifndef __FreeBSD__
 #include <bits/stdio_lim.h>
+#endif /* !__FreeBSD__ */
 #endif /* !__APPLE__ */
 #endif /* !__ANDROID__ */
 
