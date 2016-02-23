--- src/auth.c.orig	2016-02-23 07:59:28 UTC
+++ src/auth.c
@@ -848,27 +848,24 @@ AuthAccount(void *arg)
     RadiusAccount(auth);
 
   if (Enabled(&auth->conf.options, AUTH_CONF_UTMP_WTMP)) {
-    struct utmp	ut;
+    struct utmpx	ut;
 
     memset(&ut, 0, sizeof(ut));
     strlcpy(ut.ut_line, auth->info.lnkname, sizeof(ut.ut_line));
 
     if (auth->acct_type == AUTH_ACCT_START) {
-      time_t	t;
-
       strlcpy(ut.ut_host, auth->params.peeraddr, sizeof(ut.ut_host));
-      strlcpy(ut.ut_name, auth->params.authname, sizeof(ut.ut_name));
-      time(&t);
-      ut.ut_time = t;
-      login(&ut);
+      strlcpy(ut.ut_user, auth->params.authname, sizeof(ut.ut_user));
+      gettimeofday(&ut.ut_tv, NULL);
+      pututxline(&ut);
       Log(LG_AUTH, ("[%s] AUTH: wtmp %s %s %s login", auth->info.lnkname, ut.ut_line, 
-        ut.ut_name, ut.ut_host));
+        ut.ut_user, ut.ut_host));
     }
   
     if (auth->acct_type == AUTH_ACCT_STOP) {
+      ut.ut_type = DEAD_PROCESS;
       Log(LG_AUTH, ("[%s] AUTH: wtmp %s logout", auth->info.lnkname, ut.ut_line));
-      logout(ut.ut_line);
-      logwtmp(ut.ut_line, "", "");
+      pututxline(&ut);
     }
   }
 
