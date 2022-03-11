--- lib/tlscontext.c.orig	2022-03-11 07:45:38 UTC
+++ lib/tlscontext.c
@@ -1076,7 +1076,7 @@ tls_context_set_key_file(TLSContext *self, const gchar
 gboolean
 tls_context_set_keylog_file(TLSContext *self, gchar *keylog_file_path, GError **error)
 {
-#if OPENSSL_VERSION_NUMBER >= 0x10101000L
+#if OPENSSL_VERSION_NUMBER >= 0x10101000L && !defined(LIBRESSL_VERSION_NUMBER)
   g_free(self->keylog_file_path);
   msg_warning_once("WARNING: TLS keylog file has been set up, it should only be used during debugging sessions");
   self->keylog_file_path = g_strdup(keylog_file_path);
