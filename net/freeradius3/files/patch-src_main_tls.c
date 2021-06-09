--- src/main/tls.c.orig	2021-06-09 07:14:06 UTC
+++ src/main/tls.c
@@ -1580,7 +1580,7 @@ static int load_dh_params(SSL_CTX *ctx, char *file)
 	 *
 	 * Change suggested by @t8m
 	 */
-#if OPENSSL_VERSION_NUMBER >= 0x10101000L
+#if OPENSSL_VERSION_NUMBER >= 0x10101000L && !defined(LIBRESSL_VERSION_NUMBER)
 	if (FIPS_mode() > 0) {
 		WARN(LOG_PREFIX ": Ignoring user-selected DH parameters in FIPS mode. Using defaults.");
 		return 0;
@@ -3987,7 +3987,7 @@ post_ca:
 	 *	disable early data.
 	 *
 	 */
-#if OPENSSL_VERSION_NUMBER >= 0x10101000L
+#if OPENSSL_VERSION_NUMBER >= 0x10101000L && !defined(LIBRESSL_VERSION_NUMBER)
 	SSL_CTX_set_max_early_data(ctx, 0);
 #endif
 
