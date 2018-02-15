--- dhcp6c.c.orig	2017-02-28 19:06:15 UTC
+++ dhcp6c.c
@@ -521,6 +521,7 @@ process_signals()
 	if ((sig_flags & SIGF_HUP)) {
 		d_printf(LOG_INFO, FNAME, "restarting");
 		free_resources(NULL);
+		cfparse(conffile);
 		client6_startall(1);
 	}
 	if ((sig_flags & SIGF_USR1)) {
@@ -1192,6 +1193,8 @@ client6_send(ev)
 	struct dhcp6_optinfo optinfo;
 	ssize_t optlen, len;
 	struct dhcp6_eventdata *evd;
+	/* XXX */
+	struct rawoption *rawop;
 
 	ifp = ev->ifp;
 
@@ -1350,6 +1353,10 @@ client6_send(ev)
 		    "failed to set authentication option");
 		goto end;
 	}
+	/* XXX */
+	rawop_clear_list(&optinfo.rawops);
+	rawop_copy_list(&optinfo.rawops, &ifp->rawops);
+
 
 	/* set options in the message */
 	if ((optlen = dhcp6_set_options(dh6->dh6_msgtype,
