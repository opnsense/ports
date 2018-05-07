--- src/vendor/openssl-sys/build.rs.orig	2018-03-25 15:53:20 UTC
+++ src/vendor/openssl-sys/build.rs
@@ -1,7 +1,7 @@
+extern crate cc;
 extern crate pkg_config;
 #[cfg(target_env = "msvc")]
 extern crate vcpkg;
-extern crate cc;
 
 use std::collections::HashSet;
 use std::env;
@@ -89,17 +89,15 @@ fn main() {
     let libs_env = env("OPENSSL_LIBS");
     let libs = match libs_env.as_ref().and_then(|s| s.to_str()) {
         Some(ref v) => v.split(":").collect(),
-        None => {
-            match version {
-                Version::Openssl101 |
-                Version::Openssl102 if target.contains("windows") => vec!["ssleay32", "libeay32"],
-                Version::Openssl110 if target.contains("windows") => vec!["libssl", "libcrypto"],
-                _ => vec!["ssl", "crypto"],
+        None => match version {
+            Version::Openssl101 | Version::Openssl102 if target.contains("windows") => {
+                vec!["ssleay32", "libeay32"]
             }
-        }
+            Version::Openssl110 if target.contains("windows") => vec!["libssl", "libcrypto"],
+            _ => vec!["ssl", "crypto"],
+        },
     };
 
-
     let kind = determine_mode(Path::new(&lib_dir), &libs);
     for lib in libs.into_iter() {
         println!("cargo:rustc-link-lib={}={}", kind, lib);
@@ -109,7 +107,7 @@ fn main() {
 fn find_openssl_dir(target: &str) -> OsString {
     let host = env::var("HOST").unwrap();
 
-    if host.contains("apple-darwin") && target.contains("apple-darwin") {
+    if host == target && target.contains("apple-darwin") {
         let homebrew = Path::new("/usr/local/opt/openssl@1.1");
         if homebrew.exists() {
             return homebrew.to_path_buf().into();
@@ -123,6 +121,11 @@ fn find_openssl_dir(target: &str) -> OsString {
     try_pkg_config();
     try_vcpkg();
 
+    // FreeBSD ships with OpenSSL but doesn't include a pkg-config file :(
+    if host == target && target.contains("freebsd") {
+        return OsString::from("/usr");
+    }
+
     let mut msg = format!(
         "
 
@@ -228,9 +231,10 @@ fn try_pkg_config() {
         return;
     }
 
-    let lib = match pkg_config::Config::new().print_system_libs(false).find(
-        "openssl",
-    ) {
+    let lib = match pkg_config::Config::new()
+        .print_system_libs(false)
+        .find("openssl")
+    {
         Ok(lib) => lib,
         Err(e) => {
             println!("run pkg_config fail: {:?}", e);
@@ -253,7 +257,6 @@ fn try_pkg_config() {
 /// should emit all of the cargo metadata that we need.
 #[cfg(target_env = "msvc")]
 fn try_vcpkg() {
-
     // vcpkg will not emit any metadata if it can not find libraries
     // appropriate for the target triple with the desired linkage.
 
@@ -264,8 +267,10 @@ fn try_vcpkg() {
         .probe("openssl");
 
     if let Err(e) = lib {
-        println!("note: vcpkg did not find openssl as libcrypto and libssl : {:?}",
-                 e);
+        println!(
+            "note: vcpkg did not find openssl as libcrypto and libssl : {:?}",
+            e
+        );
         lib = vcpkg::Config::new()
             .emit_includes(true)
             .lib_name("libeay32")
@@ -273,8 +278,10 @@ fn try_vcpkg() {
             .probe("openssl");
     }
     if let Err(e) = lib {
-        println!("note: vcpkg did not find openssl as ssleay32 and libeay32: {:?}",
-                 e);
+        println!(
+            "note: vcpkg did not find openssl as ssleay32 and libeay32: {:?}",
+            e
+        );
         return;
     }
 
@@ -316,8 +323,10 @@ fn validate_headers(include_dirs: &[PathBuf]) -> Versi
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
@@ -336,8 +345,10 @@ RUST_LIBRESSL_251
 RUST_LIBRESSL_250
 #elif defined (LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER < 0x20500000
 RUST_LIBRESSL_OLD
-#elif OPENSSL_VERSION_NUMBER >= 0x10101000
+#elif OPENSSL_VERSION_NUMBER >= 0x10102000
 RUST_OPENSSL_NEW
+#elif OPENSSL_VERSION_NUMBER >= 0x10101000
+RUST_OPENSSL_111
 #elif OPENSSL_VERSION_NUMBER >= 0x10100060
 RUST_OPENSSL_110F
 #elif OPENSSL_VERSION_NUMBER >= 0x10100000
@@ -464,6 +475,18 @@ See rust-openssl README for more information:
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
+    } else if expanded.contains("RUST_OPENSSL_111") {
+        println!("cargo:rustc-cfg=ossl111");
+        println!("cargo:rustc-cfg=ossl110");
+        println!("cargo:version=111");
+        Version::Openssl110
     } else if expanded.contains("RUST_OPENSSL_110F") {
         println!("cargo:rustc-cfg=ossl110");
         println!("cargo:rustc-cfg=ossl110f");
@@ -486,9 +509,9 @@ See rust-openssl README for more information:
         panic!(
             "
 
-This crate is only compatible with OpenSSL 1.0.1, 1.0.2, and 1.1.0, or LibreSSL
-2.5 and 2.6.0, but a different version of OpenSSL was found. The build is now
-aborting due to this version mismatch.
+This crate is only compatible with OpenSSL 1.0.1 through 1.1.1, or LibreSSL 2.5
+through 2.7, but a different version of OpenSSL was found. The build is now aborting
+due to this version mismatch.
 
 "
         );
@@ -516,12 +539,11 @@ fn determine_mode(libdir: &Path, libs: &[&str]) -> &'s
         .map(|e| e.file_name())
         .filter_map(|e| e.into_string().ok())
         .collect::<HashSet<_>>();
-    let can_static = libs.iter().all(|l| {
-        files.contains(&format!("lib{}.a", l)) || files.contains(&format!("{}.lib", l))
-    });
+    let can_static = libs.iter()
+        .all(|l| files.contains(&format!("lib{}.a", l)) || files.contains(&format!("{}.lib", l)));
     let can_dylib = libs.iter().all(|l| {
-        files.contains(&format!("lib{}.so", l)) || files.contains(&format!("{}.dll", l)) ||
-            files.contains(&format!("lib{}.dylib", l))
+        files.contains(&format!("lib{}.so", l)) || files.contains(&format!("{}.dll", l))
+            || files.contains(&format!("lib{}.dylib", l))
     });
     match (can_static, can_dylib) {
         (true, false) => return "static",
@@ -529,7 +551,7 @@ fn determine_mode(libdir: &Path, libs: &[&str]) -> &'s
         (false, false) => {
             panic!(
                 "OpenSSL libdir at `{}` does not contain the required files \
-                    to either statically or dynamically link OpenSSL",
+                 to either statically or dynamically link OpenSSL",
                 libdir.display()
             );
         }
