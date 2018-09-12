--- src/network/ssl/qssldiffiehellmanparameters_openssl.cpp.orig	2018-09-12 07:50:27 UTC
+++ src/network/ssl/qssldiffiehellmanparameters_openssl.cpp
@@ -75,7 +75,7 @@ static bool isSafeDH(DH *dh)
     //     Without the test, the IETF parameters would
     //     fail validation. For details, see Diffie-Hellman
     //     Parameter Check (when g = 2, must p mod 24 == 11?).
-#if QT_CONFIG(opensslv11)
+#if QT_CONFIG(opensslv11) && !defined(LIBRESSL_VERSION_NUMBER)
     // Mark p < 1024 bits as unsafe.
     if (q_DH_bits(dh) < 1024)
         return false;
