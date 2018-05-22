--- src/vendor/openssl-sys/build.rs.orig	2018-05-07 18:50:12 UTC
+++ src/vendor/openssl-sys/build.rs
@@ -323,8 +323,10 @@ fn validate_headers(include_dirs: &[PathBuf]) -> Versi
 #include <openssl/opensslv.h>
 #include <openssl/opensslconf.h>
 
-#if LIBRESSL_VERSION_NUMBER >= 0x20700000
+#if LIBRESSL_VERSION_NUMBER >= 0x20800000
 RUST_LIBRESSL_NEW
+#elif LIBRESSL_VERSION_NUMBER >= 0x20700000
+RUST_LIBRESSL_27X
 #elif LIBRESSL_VERSION_NUMBER >= 0x20603000
 RUST_LIBRESSL_26X
 #elif LIBRESSL_VERSION_NUMBER >= 0x20602000
@@ -473,6 +475,13 @@ See rust-openssl README for more information:
         println!("cargo:libressl_version=26x");
         println!("cargo:version=101");
         Version::Libressl
+    } else if expanded.contains("RUST_LIBRESSL_27X") {
+        println!("cargo:rustc-cfg=libressl");
+        println!("cargo:rustc-cfg=libressl27");
+        println!("cargo:libressl=true");
+        println!("cargo:libressl_version=27x");
+        println!("cargo:version=101");
+        Version::Libressl
     } else if expanded.contains("RUST_OPENSSL_111") {
         println!("cargo:rustc-cfg=ossl111");
         println!("cargo:rustc-cfg=ossl110");
@@ -501,7 +510,7 @@ See rust-openssl README for more information:
             "
 
 This crate is only compatible with OpenSSL 1.0.1 through 1.1.1, or LibreSSL 2.5
-and 2.6, but a different version of OpenSSL was found. The build is now aborting
+through 2.7, but a different version of OpenSSL was found. The build is now aborting
 due to this version mismatch.
 
 "
