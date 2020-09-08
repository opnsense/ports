--- libpkg/scripts.c.orig	2020-09-07 15:52:56 UTC
+++ libpkg/scripts.c
@@ -70,7 +70,7 @@ pkg_script_run(struct pkg * const pkg, pkg_script type
 	size_t script_cmd_len;
 	long argmax;
 	int cur_pipe[2];
-#ifdef PROC_REAP_KILL
+#ifdef PROC_REAP_KILL_XXX
 	bool do_reap;
 	pid_t mypid;
 	struct procctl_reaper_status info;
@@ -108,7 +108,7 @@ pkg_script_run(struct pkg * const pkg, pkg_script type
 
 	assert(i < sizeof(map) / sizeof(map[0]));
 
-#ifdef PROC_REAP_KILL
+#ifdef PROC_REAP_KILL_XXX
 	mypid = getpid();
 	do_reap = procctl(P_PID, mypid, PROC_REAP_ACQUIRE, NULL) == 0;
 #endif
@@ -303,7 +303,6 @@ pkg_script_run(struct pkg * const pkg, pkg_script type
 					exit(0);
 
 				pkg_emit_error("%s script failed", map[i].arg);
-				ret = EPKG_FATAL;
 				goto cleanup;
 			}
 		}
@@ -318,7 +317,7 @@ cleanup:
 	if (stdin_pipe[1] != -1)
 		close(stdin_pipe[1]);
 
-#ifdef PROC_REAP_KILL
+#ifdef PROC_REAP_KILL_XXX
 	/*
 	 * If the prior PROCCTL_REAP_ACQUIRE call failed, the kernel
 	 * probably doesn't support this, so don't try.
