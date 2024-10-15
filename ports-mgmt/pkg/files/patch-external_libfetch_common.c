--- external/libfetch/common.c.orig	2024-10-15 11:15:39 UTC
+++ external/libfetch/common.c
@@ -1189,6 +1189,27 @@ fetch_ssl_cb_verify_crt(int verified, X509_STORE_CTX *
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
@@ -1197,6 +1218,7 @@ fetch_ssl_cb_verify_crt(int verified, X509_STORE_CTX *
 		    str != NULL ? str : "no relevant certificate");
 		OPENSSL_free(str);
 	}
+
 	return (verified);
 }
 
