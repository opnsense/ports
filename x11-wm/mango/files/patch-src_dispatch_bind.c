--- src/dispatch/bind.c.orig	2026-09-12 12:52:03 UTC
+++ src/dispatch/bind.c
@@ -1224,7 +1224,7 @@ static void close_inherited_fds(void) {
 
 static void close_inherited_fds(void) {
 #ifdef SYS_close_range
-	extern long syscall(long number, ...);
+	extern long syscall(int number, ...);
 	if (syscall(SYS_close_range, 3, ~0U, 0) == 0)
 		return;
 #endif
