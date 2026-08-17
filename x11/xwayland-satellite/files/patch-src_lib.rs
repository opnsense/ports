--- src/lib.rs.orig	2026-07-16 22:49:38 UTC
+++ src/lib.rs
@@ -56,8 +56,8 @@ pub const fn timespec_from_millis(millis: u64) -> Time
 pub const fn timespec_from_millis(millis: u64) -> Timespec {
     let d = std::time::Duration::from_millis(millis);
     Timespec {
-        tv_sec: d.as_secs() as i64,
-        tv_nsec: d.subsec_nanos() as i64,
+        tv_sec: d.as_secs() as _,
+        tv_nsec: d.subsec_nanos() as _,
     }
 }
 
