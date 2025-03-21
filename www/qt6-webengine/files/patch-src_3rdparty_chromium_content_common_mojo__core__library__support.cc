--- src/3rdparty/chromium/content/common/mojo_core_library_support.cc.orig	2024-02-23 21:04:38 UTC
+++ src/3rdparty/chromium/content/common/mojo_core_library_support.cc
@@ -15,7 +15,7 @@ bool IsMojoCoreSharedLibraryEnabled() {
 }
 
 std::optional<base::FilePath> GetMojoCoreSharedLibraryPath() {
-#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS)
+#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS) || BUILDFLAG(IS_BSD)
   const base::CommandLine& command_line =
       *base::CommandLine::ForCurrentProcess();
   if (!command_line.HasSwitch(switches::kMojoCoreLibraryPath))
