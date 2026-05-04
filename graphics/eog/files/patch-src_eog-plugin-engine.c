--- src/eog-plugin-engine.c.orig	2026-04-11 19:58:53 UTC
+++ src/eog-plugin-engine.c
@@ -85,7 +85,7 @@ eog_plugin_engine_new (void)
 	const gchar * const * system_data_dirs;
 	GError *error = NULL;
 
-	private_path = g_build_filename (LIBDIR, "eog",
+	private_path = g_build_filename (LIBDIR,
 					"girepository-1.0", NULL);
 
 	/* This should be moved to libpeas */
