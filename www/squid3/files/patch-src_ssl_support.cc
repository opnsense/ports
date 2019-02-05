--- src/ssl/support.cc.orig	2018-07-15 20:46:55 UTC
+++ src/ssl/support.cc
@@ -2159,7 +2159,11 @@ remove_session_cb(SSL_CTX *, SSL_SESSION
 }
 
 static SSL_SESSION *
-get_session_cb(SSL *, unsigned char *sessionID, int len, int *copy)
+get_session_cb(SSL *,
+#if defined(LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER >= 0x20800000L
+const
+#endif
+unsigned char *sessionID, int len, int *copy)
 {
     if (!SslSessionCache)
         return NULL;
