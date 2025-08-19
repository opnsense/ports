--- libpkg/lua_scripts.c.orig	2022-08-03 07:37:06 UTC
+++ libpkg/lua_scripts.c
@@ -51,7 +51,7 @@ pkg_lua_script_run(struct pkg * const pkg, pkg_lua_scr
 {
 	int ret = EPKG_OK;
 	int pstat;
-#ifdef PROC_REAP_KILL
+#ifdef PROC_REAP_KILL_XXX
 	bool do_reap;
 	pid_t mypid;
 	struct procctl_reaper_status info;
@@ -67,7 +67,7 @@ pkg_lua_script_run(struct pkg * const pkg, pkg_lua_scr
 		return (EPKG_OK);
 	}
 
-#ifdef PROC_REAP_KILL
+#ifdef PROC_REAP_KILL_XXX
 	mypid = getpid();
 	do_reap = procctl(P_PID, mypid, PROC_REAP_ACQUIRE, NULL) == 0;
 #endif
@@ -159,7 +159,7 @@ pkg_lua_script_run(struct pkg * const pkg, pkg_lua_scr
 
 
 cleanup:
-#ifdef PROC_REAP_KILL
+#ifdef PROC_REAP_KILL_XXX
 	/*
 	 * If the prior PROCCTL_REAP_ACQUIRE call failed, the kernel
 	 * probably doesn't support this, so don't try.
