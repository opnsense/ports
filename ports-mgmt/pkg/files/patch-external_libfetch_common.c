--- external/libfetch/common.c.orig	2023-06-29 13:25:53 UTC
+++ external/libfetch/common.c
@@ -1082,8 +1082,6 @@ fetch_ssl_setup_transport_layer(SSL_CTX *ctx, int verb
 /*
  * Configure peer verification based on environment.
  */
-#define LOCAL_CERT_FILE	"/usr/local/etc/ssl/cert.pem"
-#define BASE_CERT_FILE	"/etc/ssl/cert.pem"
 static int
 fetch_ssl_setup_peer_verification(SSL_CTX *ctx, int verbose)
 {
@@ -1093,12 +1091,6 @@ fetch_ssl_setup_peer_verification(SSL_CTX *ctx, int ve
 
 	if (getenv("SSL_NO_VERIFY_PEER") == NULL) {
 		ca_cert_file = getenv("SSL_CA_CERT_FILE");
-		if (ca_cert_file == NULL &&
-		    access(LOCAL_CERT_FILE, R_OK) == 0)
-			ca_cert_file = LOCAL_CERT_FILE;
-		if (ca_cert_file == NULL &&
-		    access(BASE_CERT_FILE, R_OK) == 0)
-			ca_cert_file = BASE_CERT_FILE;
 		ca_cert_path = getenv("SSL_CA_CERT_PATH");
 		if (verbose) {
 			fetch_info("Peer verification enabled");
@@ -1119,6 +1111,13 @@ fetch_ssl_setup_peer_verification(SSL_CTX *ctx, int ve
 			    ca_cert_path);
 		else
 			SSL_CTX_set_default_verify_paths(ctx);
+		if (getenv("SSL_CRL_VERIFY") != NULL) {
+			if (verbose)
+				fetch_info("CRL verification enabled");
+			X509_VERIFY_PARAM_set_flags(SSL_CTX_get0_param(ctx),
+			    X509_V_FLAG_CRL_CHECK |
+			    X509_V_FLAG_CRL_CHECK_ALL);
+		}
 		if ((crl_file = getenv("SSL_CRL_FILE")) != NULL) {
 			if (verbose)
 				fetch_info("Using CRL file: %s", crl_file);
@@ -1189,6 +1188,27 @@ fetch_ssl_cb_verify_crt(int verified, X509_STORE_CTX *
 	char *str;
 
 	str = NULL;
+
+	/*
+	 * CLRs may be defined explictly but not always.  The absence of a
+	 * CRL distribution point is no indication that a CRL does not exist
+	 * which also means the CRL check being enforced will require to have
+	 * proper CRLs in place for the certificates to be checked which can
+	 * not be guaranteed for a random hostname on the Internet.  Disable
+	 * the specific OpenSSL error that deals with this case given that
+	 * we do make the utmost effort to supply a proper list of CRLs that
+	 * are required to verify the certificate(s) in question.
+	 */
+	if (!verified && X509_STORE_CTX_get_error(ctx) == X509_V_ERR_UNABLE_TO_GET_CRL) {
+		if ((crt = X509_STORE_CTX_get_current_cert(ctx)) != NULL &&
+		    (name = X509_get_subject_name(crt)) != NULL)
+			str = X509_NAME_oneline(name, 0, 0);
+		fprintf(stderr, "No CRL was provided for %s\n", str);
+		OPENSSL_free(str);
+
+		verified = 1;
+	}
+
 	if (!verified) {
 		if ((crt = X509_STORE_CTX_get_current_cert(ctx)) != NULL &&
 		    (name = X509_get_subject_name(crt)) != NULL)
@@ -1197,6 +1217,7 @@ fetch_ssl_cb_verify_crt(int verified, X509_STORE_CTX *
 		    str != NULL ? str : "no relevant certificate");
 		OPENSSL_free(str);
 	}
+
 	return (verified);
 }
 
