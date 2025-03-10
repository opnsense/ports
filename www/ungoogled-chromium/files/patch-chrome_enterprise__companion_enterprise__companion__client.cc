--- chrome/enterprise_companion/enterprise_companion_client.cc.orig	2025-02-20 09:59:21 UTC
+++ chrome/enterprise_companion/enterprise_companion_client.cc
@@ -37,7 +37,7 @@ namespace {
 
 #if BUILDFLAG(IS_MAC)
 constexpr char kServerName[] = MAC_BUNDLE_IDENTIFIER_STRING ".service";
-#elif BUILDFLAG(IS_LINUX)
+#elif BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
 constexpr char kServerName[] =
     "/run/" COMPANY_SHORTNAME_STRING "/" PRODUCT_FULLNAME_STRING "/service.sk";
 #elif BUILDFLAG(IS_WIN)
