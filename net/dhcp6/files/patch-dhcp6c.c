--- dhcp6c.c.orig	2017-02-28 19:06:15 UTC
+++ dhcp6c.c
@@ -521,6 +521,10 @@ process_signals()
 	if ((sig_flags & SIGF_HUP)) {
 		d_printf(LOG_INFO, FNAME, "restarting");
 		free_resources(NULL);
+		if (cfparse(conffile) != 0) {
+			d_printf(LOG_WARNING, FNAME,
+			    "failed to reload configuration file");
+		}
 		client6_startall(1);
 	}
 	if ((sig_flags & SIGF_USR1)) {
