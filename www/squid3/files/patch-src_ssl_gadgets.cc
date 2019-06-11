--- src/ssl/gadgets.cc.orig	2019-06-11 04:16:21 UTC
+++ src/ssl/gadgets.cc
@@ -321,12 +321,20 @@ mimicExtensions(Ssl::X509_Pointer & cert
                                                 &ext_der,
                                                 (const ASN1_ITEM *)ASN1_ITEM_ptr(method->it));
 
+#if OPENSSL_VERSION_NUMBER < 0x10100000L
                     ASN1_OCTET_STRING *ext_oct = M_ASN1_OCTET_STRING_new();
+#else
+                    ASN1_OCTET_STRING *ext_oct = ASN1_OCTET_STRING_new();
+#endif
                     ext_oct->data = ext_der;
                     ext_oct->length = ext_len;
                     X509_EXTENSION_set_data(ext, ext_oct);
 
+#if OPENSSL_VERSION_NUMBER < 0x10100000L
                     M_ASN1_OCTET_STRING_free(ext_oct);
+#else
+                    ASN1_OCTET_STRING_free(ext_oct);
+#endif
                     ASN1_BIT_STRING_free(keyusage);
                 }
             }
