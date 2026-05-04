--- remoting/host/ipc_constants.h.orig	2026-04-15 11:25:12 UTC
+++ remoting/host/ipc_constants.h
@@ -39,7 +39,7 @@ extern const char kAgentProcessBrokerMessagePipeId[];
 const mojo::NamedPlatformChannel::ServerName& GetAgentProcessBrokerServerName();
 #endif
 
-#if BUILDFLAG(IS_LINUX)
+#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
 // Message pipe ID used for LoginSessionReporter.
 extern const char kLoginSessionReporterMessagePipeId[];
 
