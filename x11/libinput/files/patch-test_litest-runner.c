--- test/litest-runner.c.orig	2025-04-01 02:46:07 UTC
+++ test/litest-runner.c
@@ -26,7 +26,6 @@
 #include <errno.h>
 #include <sys/epoll.h>
 #include <sys/timerfd.h>
-#include <sys/sysinfo.h>
 #include <sys/wait.h>
 #ifdef HAVE_PIDFD_OPEN
 #include <sys/syscall.h>
