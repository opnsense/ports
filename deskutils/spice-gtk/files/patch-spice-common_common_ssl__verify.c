--- spice-common/common/ssl_verify.c.orig	2018-05-18 12:28:10 UTC
+++ spice-common/common/ssl_verify.c
@@ -33,7 +33,7 @@
 #include <string.h>
 #include <gio/gio.h>
 
-#if OPENSSL_VERSION_NUMBER < 0x10100000 || defined (LIBRESSL_VERSION_NUMBER)
+#if OPENSSL_VERSION_NUMBER < 0x10100000 || (defined (LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER < 0x20700000)
 static const unsigned char *ASN1_STRING_get0_data(const ASN1_STRING *asn1)
 {
     return M_ASN1_STRING_data(asn1);
