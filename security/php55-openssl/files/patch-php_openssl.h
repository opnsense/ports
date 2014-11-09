--- php_openssl.h.orig	2012-03-03 15:31:33.629430400 +0100
+++ php_openssl.h	2012-03-03 15:34:43.078266300 +0100
@@ -63,6 +63,7 @@
 PHP_FUNCTION(openssl_x509_export);
 PHP_FUNCTION(openssl_x509_export_to_file);
 PHP_FUNCTION(openssl_x509_check_private_key);
+PHP_FUNCTION(openssl_x509_check);
 
 PHP_FUNCTION(openssl_pkcs12_export);
 PHP_FUNCTION(openssl_pkcs12_export_to_file);
@@ -74,6 +75,12 @@
 PHP_FUNCTION(openssl_csr_sign);
 PHP_FUNCTION(openssl_csr_get_subject);
 PHP_FUNCTION(openssl_csr_get_public_key);
+
+PHP_FUNCTION(openssl_crl_new);
+PHP_FUNCTION(openssl_crl_revoke_cert);
+PHP_FUNCTION(openssl_crl_revoke_cert_by_serial);
+PHP_FUNCTION(openssl_crl_export);
+PHP_FUNCTION(openssl_crl_export_file);
 #else
 
 #define phpext_openssl_ptr NULL
