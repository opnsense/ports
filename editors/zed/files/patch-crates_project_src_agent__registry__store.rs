--- crates/project/src/agent_registry_store.rs.orig	2026-04-10 01:17:11 UTC
+++ crates/project/src/agent_registry_store.rs
@@ -524,6 +524,8 @@ fn current_platform_key() -> Option<&'static str> {
         "linux"
     } else if cfg!(target_os = "windows") {
         "windows"
+    } else if cfg!(target_os = "freebsd") {
+        "freebsd"
     } else {
         return None;
     };
@@ -550,6 +552,11 @@ fn current_platform_key() -> Option<&'static str> {
         "windows" => match arch {
             "aarch64" => "windows-aarch64",
             "x86_64" => "windows-x86_64",
+            _ => return None,
+        },
+        "freebsd" => match arch {
+            "aarch64" => "freebsd-aarch64",
+            "x86_64" => "freebsd-x86_64",
             _ => return None,
         },
         _ => return None,
