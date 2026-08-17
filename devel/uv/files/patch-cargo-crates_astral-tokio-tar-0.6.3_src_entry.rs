--- cargo-crates/astral-tokio-tar-0.6.3/src/entry.rs.orig	2026-07-08 23:41:21 UTC
+++ cargo-crates/astral-tokio-tar-0.6.3/src/entry.rs
@@ -64,7 +64,7 @@ fn set_symlink_file_times(dst: &Path, mtime: SystemTim
         .as_secs()
         .try_into()
         .map_err(|_| Error::new(ErrorKind::InvalidData, "mtime exceeds platform limits"))?;
-    let nanoseconds = duration.subsec_nanos().into();
+    let nanoseconds = (duration.subsec_nanos() as i32).into();
     let timestamps = Timestamps {
         last_access: Timespec {
             tv_sec: seconds,
