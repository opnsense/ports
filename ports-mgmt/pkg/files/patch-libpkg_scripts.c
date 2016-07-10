--- libpkg/scripts.c.orig	2016-07-05 15:06:13 UTC
+++ libpkg/scripts.c
@@ -65,7 +65,7 @@ pkg_script_run(struct pkg * const pkg, p
 	ssize_t bytes_written;
 	size_t script_cmd_len;
 	long argmax;
-#ifdef PROC_REAP_KILL
+#ifdef PROC_REAP_KILL_XXX
 	bool do_reap;
 	pid_t mypid;
 	struct procctl_reaper_status info;
@@ -98,7 +98,7 @@ pkg_script_run(struct pkg * const pkg, p
 
 	assert(i < sizeof(map) / sizeof(map[0]));
 
-#ifdef PROC_REAP_KILL
+#ifdef PROC_REAP_KILL_XXX
 	mypid = getpid();
 	do_reap = procctl(P_PID, mypid, PROC_REAP_ACQUIRE, NULL) == 0;
 #endif
@@ -199,7 +199,6 @@ pkg_script_run(struct pkg * const pkg, p
 
 			if (WEXITSTATUS(pstat) != 0) {
 				pkg_emit_error("%s script failed", map[i].arg);
-				ret = EPKG_FATAL;
 				goto cleanup;
 			}
 		}
@@ -213,7 +212,7 @@ cleanup:
 	if (stdin_pipe[1] != -1)
 		close(stdin_pipe[1]);
 
-#ifdef PROC_REAP_KILL
+#ifdef PROC_REAP_KILL_XXX
 	/*
 	 * If the prior PROCCTL_REAP_ACQUIRE call failed, the kernel
 	 * probably doesn't support this, so don't try.
