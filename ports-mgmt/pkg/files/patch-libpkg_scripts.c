--- libpkg/scripts.c.orig	2016-02-01 16:10:07 UTC
+++ libpkg/scripts.c
@@ -65,7 +65,7 @@ pkg_script_run(struct pkg * const pkg, p
 	ssize_t bytes_written;
 	size_t script_cmd_len;
 	long argmax;
-#ifdef PROC_REAP_KILL
+#ifdef PROC_REAP_KILL_XXX
 	bool do_reap;
 	struct procctl_reaper_status info;
 	struct procctl_reaper_kill killemall;
@@ -95,7 +95,7 @@ pkg_script_run(struct pkg * const pkg, p
 
 	assert(i < sizeof(map) / sizeof(map[0]));
 
-#ifdef PROC_REAP_KILL
+#ifdef PROC_REAP_KILL_XXX
 	do_reap = procctl(P_PID, getpid(), PROC_REAP_ACQUIRE, NULL) == 0;
 #endif
 	for (j = 0; j < PKG_NUM_SCRIPTS; j++) {
@@ -208,7 +208,7 @@ cleanup:
 	if (stdin_pipe[1] != -1)
 		close(stdin_pipe[1]);
 
-#ifdef PROC_REAP_KILL
+#ifdef PROC_REAP_KILL_XXX
 	/*
 	 * If the prior PROCCTL_REAP_ACQUIRE call failed, the kernel
 	 * probably doesn't support this, so don't try.
