--- src/network/ssl/qsslkey_openssl.cpp.orig	2018-09-12 07:54:26 UTC
+++ src/network/ssl/qsslkey_openssl.cpp
@@ -305,7 +305,7 @@ static QByteArray doCrypt(QSslKeyPrivate::Cipher ciphe
     QByteArray output;
     output.resize(data.size() + EVP_MAX_BLOCK_LENGTH);
 
-#if QT_CONFIG(opensslv11)
+#if QT_CONFIG(opensslv11) && !defined(LIBRESSL_VERSION_NUMBER)
     EVP_CIPHER_CTX *ctx = q_EVP_CIPHER_CTX_new();
     q_EVP_CIPHER_CTX_reset(ctx);
 #else
@@ -319,7 +319,7 @@ static QByteArray doCrypt(QSslKeyPrivate::Cipher ciphe
     if (cipher == QSslKeyPrivate::Rc2Cbc)
         q_EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_SET_RC2_KEY_BITS, 8 * key.size(), NULL);
 
-#if QT_CONFIG(opensslv11)
+#if QT_CONFIG(opensslv11) && !defined(LIBRESSL_VERSION_NUMBER)
     // EVP_CipherInit in 1.1 resets the context thus making the calls above useless.
     // We call EVP_CipherInit_ex instead.
     q_EVP_CipherInit_ex(ctx, nullptr, nullptr,
