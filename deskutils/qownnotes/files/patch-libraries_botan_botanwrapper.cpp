--- libraries/botan/botanwrapper.cpp.orig	2026-03-09 20:50:51 UTC
+++ libraries/botan/botanwrapper.cpp
@@ -5,6 +5,7 @@
 #ifdef USE_SYSTEM_BOTAN
 #include <botan/base64.h>
 #include <botan/cipher_mode.h>
+#include <botan/exceptn.h>
 #include <botan/hash.h>
 #include <botan/kdf.h>
 #include <botan/pbkdf.h>
