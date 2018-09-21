--- src/vendor/openssl-sys/build/main.rs.orig	2018-09-11 04:49:55 UTC
+++ src/vendor/openssl-sys/build/main.rs
@@ -497,6 +497,7 @@ See rust-openssl README for more information:
             (6, 2) => ('6', '2'),
             (6, _) => ('6', 'x'),
             (7, _) => ('7', 'x'),
+            (8, 0) => ('8', 'x'),
             _ => version_error(),
         };
 
