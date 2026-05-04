--- remoting/host/ipc_desktop_environment.h.orig	2026-04-15 12:07:04 UTC
+++ remoting/host/ipc_desktop_environment.h
@@ -154,7 +154,7 @@ class IpcDesktopEnvironmentFactory : public DesktopEnv
   // the same email address reconnects, the desktop session will be reused and
   // the desktop process will be requested to send a new desktop pipe.
   // TODO: yuweih - see if it makes sense to enable it on Windows.
-#if BUILDFLAG(IS_LINUX)
+#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
   bool persist_desktop_sessions_ = true;
 #else
   bool persist_desktop_sessions_ = false;
