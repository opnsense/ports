--- libpkg/scripts.c.orig	2021-02-18 18:07:35 UTC
+++ libpkg/scripts.c
@@ -69,7 +69,7 @@ pkg_script_run(struct pkg * const pkg, pkg_script type
 	ssize_t bytes_written;
 	long argmax;
 	int cur_pipe[2] = {-1, -1};
-#ifdef PROC_REAP_KILL
+#ifdef PROC_REAP_KILL_XXX
 	bool do_reap;
 	pid_t mypid;
 	struct procctl_reaper_status info;
@@ -98,7 +98,7 @@ pkg_script_run(struct pkg * const pkg, pkg_script type
 
 	assert(i < sizeof(map) / sizeof(map[0]));
 
-#ifdef PROC_REAP_KILL
+#ifdef PROC_REAP_KILL_XXX
 	mypid = getpid();
 	do_reap = procctl(P_PID, mypid, PROC_REAP_ACQUIRE, NULL) == 0;
 #endif
@@ -250,7 +250,7 @@ cleanup:
 	if (cur_pipe[1] != -1)
 		close(cur_pipe[1]);
 
-#ifdef PROC_REAP_KILL
+#ifdef PROC_REAP_KILL_XXX
 	/*
 	 * If the prior PROCCTL_REAP_ACQUIRE call failed, the kernel
 	 * probably doesn't support this, so don't try.
@@ -338,7 +338,7 @@ pkg_script_run_child(int pid, int *pstat, int inputfd,
 			exit(0);
 
 		pkg_emit_error("%s script failed", script_name);
-		return (EPKG_FATAL);
+		/* return (EPKG_FATAL); */
 	}
 	return (EPKG_OK);
 }
