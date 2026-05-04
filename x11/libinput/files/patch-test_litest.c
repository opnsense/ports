--- test/litest.c.orig	2025-04-01 02:46:07 UTC
+++ test/litest.c
@@ -44,13 +44,13 @@
 #include <sys/wait.h>
 #include <sys/stat.h>
 #include <sys/types.h>
-#include <sys/sysinfo.h>
 #include <libudev.h>
 #if HAVE_LIBSYSTEMD
 #include <systemd/sd-bus.h>
 #endif
 #ifdef __FreeBSD__
 #include <termios.h>
+#include <sys/kbio.h>
 #endif
 
 #include <valgrind/valgrind.h>
@@ -66,8 +66,6 @@
 #include "util-backtrace.h"
 #include "util-libinput.h"
 
-#include <linux/kd.h>
-
 #define evbit(t, c) ((t) << 16U | (c & 0xffff))
 
 #define UDEV_RULES_D "/run/udev/rules.d"
@@ -5322,8 +5320,8 @@ check_device_access(void)
 		return 77;
 	}
 
-	if (access("/dev/uinput", F_OK) == -1 &&
-	    access("/dev/input/uinput", F_OK) == -1) {
+	if (access("/dev/uinput_skip_our_libudev_isnt_ready", F_OK) == -1 &&
+	    access("/dev/input/uinput_skip_our_libudev_isnt_ready", F_OK) == -1) {
 		fprintf(stderr,
 			"uinput device is missing, skipping tests.\n");
 		return 77;
@@ -5365,7 +5363,7 @@ main(int argc, char **argv)
 	if (getenv("NO_COLOR"))
 		use_colors = false;
 
-	in_debugger = is_debugger_attached();
+	in_debugger = false;
 	if (in_debugger) {
 		jobs = 0;
 	} else if ((meson_testthreads = getenv("MESON_TESTTHREADS")) == NULL ||
