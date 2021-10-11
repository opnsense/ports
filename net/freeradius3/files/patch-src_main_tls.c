--- src/main/tls.c.orig	2021-10-07 19:46:04 UTC
+++ src/main/tls.c
@@ -1697,7 +1697,7 @@ static int load_dh_params(SSL_CTX *ctx, char *file)
 	 *
 	 * Change suggested by @t8m
 	 */
-#if OPENSSL_VERSION_NUMBER >= 0x10101000L
+#if OPENSSL_VERSION_NUMBER >= 0x10101000L && !defined(LIBRESSL_VERSION_NUMBER)
 	if (FIPS_mode() > 0) {
 		WARN(LOG_PREFIX ": Ignoring user-selected DH parameters in FIPS mode. Using defaults.");
 		return 0;
@@ -3209,7 +3209,7 @@ int cbtls_verify(int ok, X509_STORE_CTX *ctx)
 
 		rad_assert(ssn != NULL);
 
-#if OPENSSL_VERSION_NUMBER >= 0x10100000L
+#if OPENSSL_VERSION_NUMBER >= 0x10100000L && !defined(LIBRESSL_VERSION_NUMBER)
 		/*
 		 *	See if there are any untrusted certificates.
 		 *	If so, complain about them.
@@ -4169,7 +4169,7 @@ post_ca:
 	 *	disable early data.
 	 *
 	 */
-#if OPENSSL_VERSION_NUMBER >= 0x10101000L
+#if OPENSSL_VERSION_NUMBER >= 0x10101000L && !defined(LIBRESSL_VERSION_NUMBER)
 	SSL_CTX_set_max_early_data(ctx, 0);
 #endif
 
