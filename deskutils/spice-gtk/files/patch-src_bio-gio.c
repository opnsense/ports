--- src/bio-gio.c.orig	2018-06-15 16:59:02 UTC
+++ src/bio-gio.c
@@ -23,7 +23,7 @@
 #include "spice-util.h"
 #include "bio-gio.h"
 
-#if OPENSSL_VERSION_NUMBER < 0x10100000 || defined(LIBRESSL_VERSION_NUMBER)
+#if OPENSSL_VERSION_NUMBER < 0x10100000 || (defined(LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER < 0x20700000)
 static BIO_METHOD one_static_bio;
 
 static int BIO_meth_set_read(BIO_METHOD *biom,
