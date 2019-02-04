--- src/ssl/support.cc.orig	2019-02-04 17:47:17 UTC
+++ src/ssl/support.cc
@@ -2159,7 +2159,7 @@ remove_session_cb(SSL_CTX *, SSL_SESSION
 }
 
 static SSL_SESSION *
-get_session_cb(SSL *, unsigned char *sessionID, int len, int *copy)
+get_session_cb(SSL *, const unsigned char *sessionID, int len, int *copy)
 {
     if (!SslSessionCache)
         return NULL;
