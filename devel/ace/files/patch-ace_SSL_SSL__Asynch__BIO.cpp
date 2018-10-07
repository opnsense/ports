--- ace/SSL/SSL_Asynch_BIO.cpp.orig	2018-09-18 07:26:56 UTC
+++ ace/SSL/SSL_Asynch_BIO.cpp
@@ -41,7 +41,7 @@ extern "C"
 
 #define BIO_TYPE_ACE  ( 21 | BIO_TYPE_SOURCE_SINK )
 
-#if OPENSSL_VERSION_NUMBER < 0x10100000L
+#if OPENSSL_VERSION_NUMBER < 0x10100000L || defined(LIBRESSL_VERSION_NUMBER)
 static BIO_METHOD methods_ACE =
   {
     BIO_TYPE_ACE, // BIO_TYPE_PROXY_SERVER,
@@ -75,7 +75,7 @@ ACE_BEGIN_VERSIONED_NAMESPACE_DECL
 BIO *
 ACE_SSL_make_BIO (void * ssl_asynch_stream)
 {
-#if OPENSSL_VERSION_NUMBER < 0x10100000L
+#if OPENSSL_VERSION_NUMBER < 0x10100000L || defined(LIBRESSL_VERSION_NUMBER)
   BIO * const pBIO = BIO_new (&methods_ACE);
 #else
   if (!methods_ACE)
