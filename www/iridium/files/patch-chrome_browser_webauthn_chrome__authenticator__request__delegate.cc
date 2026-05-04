--- chrome/browser/webauthn/chrome_authenticator_request_delegate.cc.orig	2026-04-15 12:07:04 UTC
+++ chrome/browser/webauthn/chrome_authenticator_request_delegate.cc
@@ -543,7 +543,7 @@ void ChromeAuthenticatorRequestDelegate::ConfigureDisc
     g_observer->ConfiguringCable(request_type);
   }
 
-#if BUILDFLAG(IS_LINUX)
+#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
   // No caBLEv1 on Linux. It tends to crash bluez.
   if (std::ranges::contains(pairings_from_extension,
                             device::CableDiscoveryData::Version::V1,
