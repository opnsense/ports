--- src/spice-channel.c.orig	2018-06-15 16:59:48 UTC
+++ src/spice-channel.c
@@ -55,7 +55,7 @@ static void spice_channel_reset_capabili
 static void spice_channel_send_migration_handshake(SpiceChannel *channel);
 static gboolean channel_connect(SpiceChannel *channel, gboolean tls);
 
-#if OPENSSL_VERSION_NUMBER < 0x10100000 || defined(LIBRESSL_VERSION_NUMBER)
+#if OPENSSL_VERSION_NUMBER < 0x10100000 || (defined(LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER < 0x20700000)
 static RSA *EVP_PKEY_get0_RSA(EVP_PKEY *pkey)
 {
     if (pkey->type != EVP_PKEY_RSA) {
