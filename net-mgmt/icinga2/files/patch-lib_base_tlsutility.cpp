--- lib/base/tlsutility.cpp.orig	2021-08-19 09:17:45 UTC
+++ lib/base/tlsutility.cpp
@@ -248,7 +248,7 @@ int ResolveTlsProtocolVersion(const std::string& versi
 	if (version == "TLSv1.2") {
 		return TLS1_2_VERSION;
 	} else if (version == "TLSv1.3") {
-#if OPENSSL_VERSION_NUMBER >= 0x10101000L
+#if OPENSSL_VERSION_NUMBER >= 0x10101000L && !defined(LIBRESSL_VERSION_NUMBER)
 		return TLS1_3_VERSION;
 #else /* OPENSSL_VERSION_NUMBER >= 0x10101000L */
 		throw std::runtime_error("'" + version + "' is only supported with OpenSSL 1.1.1 or newer");
