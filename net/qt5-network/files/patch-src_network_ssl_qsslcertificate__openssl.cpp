--- src/network/ssl/qsslcertificate_openssl.cpp.orig	2018-09-12 07:52:51 UTC
+++ src/network/ssl/qsslcertificate_openssl.cpp
@@ -607,7 +607,7 @@ static QMap<QByteArray, QString> _q_mapFromX509Name(X5
         unsigned char *data = 0;
         int size = q_ASN1_STRING_to_UTF8(&data, q_X509_NAME_ENTRY_get_data(e));
         info.insertMulti(name, QString::fromUtf8((char*)data, size));
-#if QT_CONFIG(opensslv11)
+#if QT_CONFIG(opensslv11) && !defined(LIBRESSL_VERSION_NUMBER)
         q_CRYPTO_free(data, 0, 0);
 #else
         q_CRYPTO_free(data);
