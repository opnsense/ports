--- src/vendor/openssl-sys/build.rs.orig	2018-08-14 20:32:17 UTC
+++ src/vendor/openssl-sys/build.rs
@@ -323,9 +323,7 @@ fn validate_headers(include_dirs: &[PathBuf]) -> Versi
 #include <openssl/opensslv.h>
 #include <openssl/opensslconf.h>
 
-#if LIBRESSL_VERSION_NUMBER >= 0x20800000
-RUST_LIBRESSL_NEW
-#elif LIBRESSL_VERSION_NUMBER >= 0x20700000
+#if LIBRESSL_VERSION_NUMBER >= 0x20700000
 RUST_LIBRESSL_27X
 #elif LIBRESSL_VERSION_NUMBER >= 0x20603000
 RUST_LIBRESSL_26X
