--- src/tls_openssl.c.orig	2018-09-18 18:30:27 UTC
+++ src/tls_openssl.c
@@ -47,7 +47,7 @@ static void _tls_log_error(xmpp_ctx_t *c
 
 void tls_initialize(void)
 {
-#if OPENSSL_VERSION_NUMBER < 0x10100000L
+#if OPENSSL_VERSION_NUMBER < 0x10100000L || ( defined(LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER < 0x20700000L )
     SSL_library_init();
     SSL_load_error_strings();
 #else
@@ -191,7 +191,7 @@ static struct _tlscert_t *_x509_to_tlsce
 	}
 
     tlscert->keyalg = NULL;
-#if OPENSSL_VERSION_NUMBER < 0x10100000L
+#if OPENSSL_VERSION_NUMBER < 0x10100000L || ( defined(LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER < 0x20700000L )
     int alg_nid = OBJ_obj2nid(cert->cert_info->key->algor->algorithm);
 #else
     X509_PUBKEY *pubkey = X509_get_X509_PUBKEY(cert);
@@ -210,7 +210,7 @@ static struct _tlscert_t *_x509_to_tlsce
     }
 
     tlscert->sigalg = NULL;
-#if OPENSSL_VERSION_NUMBER < 0x10100000L
+#if OPENSSL_VERSION_NUMBER < 0x10100000L || ( defined(LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER < 0x20700000L )
     alg_nid = OBJ_obj2nid(cert->sig_alg->algorithm);
 #else
     const X509_ALGOR *palg;
@@ -330,7 +330,7 @@ tls_t *tls_new(xmpp_conn_t *conn)
         /* Trust server's certificate when user sets the flag explicitly. */
         mode = conn->tls_trust ? SSL_VERIFY_NONE : SSL_VERIFY_PEER;
         SSL_set_verify(tls->ssl, mode, 0);
-#if OPENSSL_VERSION_NUMBER >= 0x10002000L
+#if OPENSSL_VERSION_NUMBER >= 0x10002000L && !defined(LIBRESSL_VERSION_NUMBER)
         /* Hostname verification is supported in OpenSSL 1.0.2 and newer. */
         X509_VERIFY_PARAM *param = SSL_get0_param(tls->ssl);
 
