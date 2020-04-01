--- php_openssl.h.orig	2020-03-17 10:18:41 UTC
+++ php_openssl.h
@@ -127,6 +127,7 @@ PHP_FUNCTION(openssl_x509_export);
 PHP_FUNCTION(openssl_x509_fingerprint);
 PHP_FUNCTION(openssl_x509_export_to_file);
 PHP_FUNCTION(openssl_x509_check_private_key);
+PHP_FUNCTION(openssl_x509_check);
 
 PHP_FUNCTION(openssl_pkcs12_export);
 PHP_FUNCTION(openssl_pkcs12_export_to_file);
@@ -139,6 +140,12 @@ PHP_FUNCTION(openssl_csr_sign);
 PHP_FUNCTION(openssl_csr_get_subject);
 PHP_FUNCTION(openssl_csr_get_public_key);
 
+PHP_FUNCTION(openssl_crl_new);
+PHP_FUNCTION(openssl_crl_revoke_cert);
+PHP_FUNCTION(openssl_crl_revoke_cert_by_serial);
+PHP_FUNCTION(openssl_crl_export);
+PHP_FUNCTION(openssl_crl_export_file);
+
 PHP_FUNCTION(openssl_spki_new);
 PHP_FUNCTION(openssl_spki_verify);
 PHP_FUNCTION(openssl_spki_export);
