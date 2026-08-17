--- daemon/src/wallpaper.rs.orig	2026-04-25 17:08:32 UTC
+++ daemon/src/wallpaper.rs
@@ -312,25 +312,42 @@ impl Wallpaper {
                             cache.resize, cache.filter, cache.img_path
                         );
                         common::log::debug!("{}", cmd);
-                        match unsafe { rustix::runtime::kernel_fork() } {
-                            Ok(rustix::runtime::Fork::Child(_)) => {
-                                let args: [*const u8; 4] = [
-                                    c"sh".as_ptr().cast(),
-                                    c"-c".as_ptr().cast(),
-                                    cmd.as_ptr(),
-                                    core::ptr::null(),
-                                ];
-                                let err = unsafe {
-                                    rustix::runtime::execve(
-                                        c"/bin/sh",
-                                        args.as_ptr(),
-                                        environ as *const _,
-                                    )
-                                };
-                                panic!("execve failed: {err}");
+                        #[cfg(target_os = "linux")]
+                        {
+                            match unsafe { rustix::runtime::kernel_fork() } {
+                                Ok(rustix::runtime::Fork::Child(_)) => {
+                                    let args: [*const u8; 4] = [
+                                        c"sh".as_ptr().cast(),
+                                        c"-c".as_ptr().cast(),
+                                        cmd.as_ptr(),
+                                        core::ptr::null(),
+                                    ];
+                                    let err = unsafe {
+                                        rustix::runtime::execve(
+                                            c"/bin/sh",
+                                            args.as_ptr(),
+                                            environ as *const _,
+                                        )
+                                    };
+                                    panic!("execve failed: {err}");
+                                }
+                                Ok(rustix::runtime::Fork::ParentOf(_)) => (),
+                                Err(e) => error!("fork failed: {e}"),
                             }
-                            Ok(rustix::runtime::Fork::ParentOf(_)) => (),
-                            Err(e) => error!("fork failed: {e}"),
+                        }
+                        #[cfg(not(target_os = "linux"))]
+                        {
+                            use std::process::Command;
+
+                            let cmd_str = cmd.trim_end_matches('\0');
+                            match Command::new("/bin/sh")
+                                .arg("-c")
+                                .arg(cmd_str)
+                                .spawn()
+                            {
+                                Ok(_) => {}
+                                Err(e) => error!("fork/exec failed: {e}"),
+                            }
                         }
                     }
                     Ok(None) => break 'brk,
