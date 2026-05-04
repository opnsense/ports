--- crates/extension_host/src/wasm_host/wit/since_v0_8_0.rs.orig	2026-04-10 01:17:11 UTC
+++ crates/extension_host/src/wasm_host/wit/since_v0_8_0.rs
@@ -843,7 +843,7 @@ impl platform::Host for WasmState {
         Ok((
             match env::consts::OS {
                 "macos" => platform::Os::Mac,
-                "linux" => platform::Os::Linux,
+                "linux" | "freebsd" => platform::Os::Linux,
                 "windows" => platform::Os::Windows,
                 _ => panic!("unsupported os"),
             },
