--- external/libfetch/common.c.orig	2023-06-29 13:25:53 UTC
+++ external/libfetch/common.c
@@ -1089,7 +1089,7 @@ fetch_ssl_setup_peer_verification(SSL_CTX *ctx, int ve
 {
 	X509_LOOKUP *crl_lookup;
 	X509_STORE *crl_store;
-	const char *ca_cert_file, *ca_cert_path, *crl_file;
+	const char *ca_cert_file, *ca_cert_path, *crl_file, *crl_verify;
 
 	if (getenv("SSL_NO_VERIFY_PEER") == NULL) {
 		ca_cert_file = getenv("SSL_CA_CERT_FILE");
@@ -1119,6 +1119,13 @@ fetch_ssl_setup_peer_verification(SSL_CTX *ctx, int ve
 			    ca_cert_path);
 		else
 			SSL_CTX_set_default_verify_paths(ctx);
+		if ((crl_verify = getenv("SSL_CRL_VERIFY")) != NULL) {
+			if (verbose)
+				fetch_info("Using CRL verify: yes");
+			X509_VERIFY_PARAM_set_flags(SSL_CTX_get0_param(ctx),
+			    X509_V_FLAG_CRL_CHECK |
+			    X509_V_FLAG_CRL_CHECK_ALL);
+		}
 		if ((crl_file = getenv("SSL_CRL_FILE")) != NULL) {
 			if (verbose)
 				fetch_info("Using CRL file: %s", crl_file);
@@ -1189,6 +1196,27 @@ fetch_ssl_cb_verify_crt(int verified, X509_STORE_CTX *
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
+		fetch_info("No CRL was provided for %s", str);
+		OPENSSL_free(str);
+
+		verified = 1;
+	}
+
 	if (!verified) {
 		if ((crt = X509_STORE_CTX_get_current_cert(ctx)) != NULL &&
 		    (name = X509_get_subject_name(crt)) != NULL)
@@ -1197,6 +1225,7 @@ fetch_ssl_cb_verify_crt(int verified, X509_STORE_CTX *
 		    str != NULL ? str : "no relevant certificate");
 		OPENSSL_free(str);
 	}
+
 	return (verified);
 }
 
