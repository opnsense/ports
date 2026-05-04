--- zellij-client/src/lib.rs.orig	2026-03-23 08:03:25 UTC
+++ zellij-client/src/lib.rs
@@ -641,7 +641,7 @@ pub fn start_remote_client(
 
     let reset_controlling_terminal_state = |e: String, exit_status: i32| {
         os_input.disable_mouse().non_fatal();
-        os_input.unset_raw_mode().unwrap();
+        let _ = os_input.unset_raw_mode();
         os_input.restore_console_mode();
         let goto_start_of_last_line = format!("\u{1b}[{};{}H", full_screen_ws.rows, 1);
         let restore_alternate_screen = "\u{1b}[?1049l";
@@ -659,9 +659,8 @@ pub fn start_remote_client(
         );
         let _ = os_input
             .get_stdout_writer()
-            .write(error.as_bytes())
-            .unwrap();
-        let _ = os_input.get_stdout_writer().flush().unwrap();
+            .write(error.as_bytes());
+        let _ = os_input.get_stdout_writer().flush();
         if exit_status == 0 {
             log::info!("{}", e);
         } else {
@@ -1249,21 +1248,21 @@ pub fn start_client(
 
         os_input.disable_mouse().non_fatal();
         info!("{}", exit_msg);
-        os_input.unset_raw_mode().unwrap();
+        let _ = os_input.unset_raw_mode();
         os_input.restore_console_mode();
         let mut stdout = os_input.get_stdout_writer();
         let exit_kitty_keyboard_mode = "\u{1b}[<1u";
         if !explicitly_disable_kitty_keyboard_protocol {
-            let _ = stdout.write(exit_kitty_keyboard_mode.as_bytes()).unwrap();
-            stdout.flush().unwrap();
+            let _ = stdout.write(exit_kitty_keyboard_mode.as_bytes());
+            let _ = stdout.flush();
         }
-        let _ = stdout.write(goodbye_message.as_bytes()).unwrap();
-        stdout.flush().unwrap();
+        let _ = stdout.write(goodbye_message.as_bytes());
+        let _ = stdout.flush();
     } else {
         let clear_screen = "\u{1b}[2J";
         let mut stdout = os_input.get_stdout_writer();
-        let _ = stdout.write(clear_screen.as_bytes()).unwrap();
-        stdout.flush().unwrap();
+        let _ = stdout.write(clear_screen.as_bytes());
+        let _ = stdout.flush();
     }
 
     let _ = send_input_instructions.send(InputInstruction::Exit);
