--- ace/SSL/SSL_Context.cpp.orig	2018-09-18 07:26:56 UTC
+++ ace/SSL/SSL_Context.cpp
@@ -356,7 +356,7 @@ ACE_SSL_Context::filter_versions (const 
 bool
 ACE_SSL_Context::check_host (const ACE_INET_Addr &host, SSL *peerssl)
 {
-#if defined (OPENSSL_VERSION_NUMBER) && (OPENSSL_VERSION_NUMBER >= 0x10002001L)
+#if defined (OPENSSL_VERSION_NUMBER) && (OPENSSL_VERSION_NUMBER >= 0x10002001L) && !defined(LIBRE_VERSION_NUMBER)
 
   this->check_context ();
 
