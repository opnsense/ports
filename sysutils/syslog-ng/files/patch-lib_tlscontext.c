--- lib/tlscontext.c.orig	2022-06-03 13:40:39 UTC
+++ lib/tlscontext.c
@@ -598,10 +598,12 @@ tls_context_setup_cipher_suite(TLSContext *self)
 static gboolean
 tls_context_setup_sigalgs(TLSContext *self)
 {
+#if !defined(LIBRESSL_VERSION_NUMBER)
   if (self->sigalgs && !SSL_CTX_set1_sigalgs_list(self->ssl_ctx, self->sigalgs))
     return FALSE;
 
   if (self->client_sigalgs && !SSL_CTX_set1_client_sigalgs_list(self->ssl_ctx, self->client_sigalgs))
+#endif
     return FALSE;
 
   return TRUE;
@@ -1025,7 +1027,7 @@ tls_context_set_key_file(TLSContext *self, const gchar
 gboolean
 tls_context_set_keylog_file(TLSContext *self, gchar *keylog_file_path, GError **error)
 {
-#if OPENSSL_VERSION_NUMBER >= 0x10101000L
+#if OPENSSL_VERSION_NUMBER >= 0x10101000L && !defined(LIBRESSL_VERSION_NUMBER)
   g_free(self->keylog_file_path);
   msg_warning_once("WARNING: TLS keylog file has been set up, it should only be used during debugging sessions");
   self->keylog_file_path = g_strdup(keylog_file_path);
