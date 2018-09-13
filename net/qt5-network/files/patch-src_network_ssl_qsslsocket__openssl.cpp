--- src/network/ssl/qsslsocket_openssl.cpp.orig	2018-06-15 07:29:31 UTC
+++ src/network/ssl/qsslsocket_openssl.cpp
@@ -251,7 +251,7 @@ long QSslSocketBackendPrivate::setupOpenSslOptions(QSs
         options = SSL_OP_ALL|SSL_OP_NO_SSLv2|SSL_OP_NO_SSLv3;
     else if (protocol == QSsl::TlsV1_0OrLater)
         options = SSL_OP_ALL|SSL_OP_NO_SSLv2|SSL_OP_NO_SSLv3;
-#if OPENSSL_VERSION_NUMBER >= 0x10001000L
+#if OPENSSL_VERSION_NUMBER >= 0x10001000L && !defined(LIBRESSL_VERSION_NUMBER)
     // Choosing Tlsv1_1OrLater or TlsV1_2OrLater on OpenSSL < 1.0.1
     // will cause an error in QSslContext::fromConfiguration, meaning
     // we will never get here.
