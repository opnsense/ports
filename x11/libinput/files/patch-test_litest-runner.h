--- test/litest-runner.h.orig	2025-04-01 02:46:07 UTC
+++ test/litest-runner.h
@@ -180,3 +180,8 @@ void litest_runner_abort(void);
  */
 __attribute__((noreturn))
 void litest_runner_abort(void);
+
+static int get_nprocs(void)
+{
+	return sysconf (_SC_NPROCESSORS_ONLN);
+}
