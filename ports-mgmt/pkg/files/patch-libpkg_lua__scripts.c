--- libpkg/lua_scripts.c.orig	2020-09-08 04:23:43 UTC
+++ libpkg/lua_scripts.c
@@ -410,7 +410,7 @@ pkg_lua_script_run(struct pkg * const pkg, pkg_lua_scr
 	int ret = EPKG_OK;
 	struct pkg_lua_script *lscript;
 	int pstat;
-#ifdef PROC_REAP_KILL
+#ifdef PROC_REAP_KILL_XXX
 	bool do_reap;
 	pid_t mypid;
 	struct procctl_reaper_status info;
@@ -430,7 +430,7 @@ pkg_lua_script_run(struct pkg * const pkg, pkg_lua_scr
 		return (EPKG_OK);
 	}
 
-#ifdef PROC_REAP_KILL
+#ifdef PROC_REAP_KILL_XXX
 	mypid = getpid();
 	do_reap = procctl(P_PID, mypid, PROC_REAP_ACQUIRE, NULL) == 0;
 #endif
@@ -559,7 +559,7 @@ pkg_lua_script_run(struct pkg * const pkg, pkg_lua_scr
 
 
 cleanup:
-#ifdef PROC_REAP_KILL
+#ifdef PROC_REAP_KILL_XXX
 	/*
 	 * If the prior PROCCTL_REAP_ACQUIRE call failed, the kernel
 	 * probably doesn't support this, so don't try.
