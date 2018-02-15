--- config.c.orig	2017-02-28 19:06:15 UTC
+++ config.c
@@ -106,6 +106,10 @@ struct dhcp6_ifconf {
 	int server_pref;	/* server preference (server only) */
 
 	char *scriptpath;	/* path to config script (client only) */
+	
+	/* XXX */
+	struct duid duid;	
+	struct rawop_list rawops;
 
 	struct dhcp6_list reqopt_list;
 	struct ia_conflist iaconf_list;
@@ -179,6 +183,10 @@ configure_interface(iflist)
 		TAILQ_INIT(&ifc->reqopt_list);
 		TAILQ_INIT(&ifc->iaconf_list);
 
+		/* XXX */
+		TAILQ_INIT(&ifc->rawops);
+	
+
 		for (cfl = ifp->params; cfl; cfl = cfl->next) {
 			switch(cfl->type) {
 			case DECL_REQUEST:
@@ -206,6 +214,22 @@ configure_interface(iflist)
 					goto bad;
 				}
 				break;
+			/* XXX */
+			case DECL_DUID:
+				if ((configure_duid((char *)cfl->ptr,
+						    &ifc->duid)) != 0) {
+					d_printf(LOG_ERR, FNAME, "%s:%d "
+					    "failed to configure "
+					    "DUID for %s",
+					    configfilename, cfl->line,
+					    ifc->ifname);
+					goto bad;
+				}
+				d_printf(LOG_DEBUG, FNAME,
+				    "configure DUID for %s: %s",
+				    ifc->ifname, duidstr(&ifc->duid));					
+				break;
+
 			case DECL_INFO_ONLY:
 				if (dhcp6_mode != DHCP6_MODE_CLIENT) {
 					d_printf(LOG_INFO, FNAME, "%s:%d "
@@ -1302,6 +1326,10 @@ configure_commit()
 	struct dhcp6_ifconf *ifc;
 	struct dhcp6_if *ifp;
 	struct ia_conf *iac;
+	/* XXX */
+	struct rawoption *rawop;
+
+	static int init = 1;	
 
 	/* commit interface configuration */
 	for (ifp = dhcp6_if; ifp; ifp = ifp->next) {
@@ -1310,6 +1338,15 @@ configure_commit()
 		ifp->allow_flags = 0;
 		dhcp6_clear_list(&ifp->reqopt_list);
 		clear_iaconf(&ifp->iaconf_list);
+
+		/* XXX */
+		if (init) {
+			TAILQ_INIT(&ifp->rawops);
+			init = 0;
+		} else {
+			rawop_clear_list(&ifp->rawops);			
+		}
+
 		ifp->server_pref = DH6OPT_PREF_UNDEF;
 		if (ifp->scriptpath != NULL)
 			free(ifp->scriptpath);
@@ -1345,7 +1382,27 @@ configure_commit()
 		}
 		ifp->pool = ifc->pool;
 		ifc->pool.name = NULL;
+
+		
+		/* XXX */
+		if (ifc->duid.duid_id != NULL) {
+			dprintf(LOG_INFO, FNAME, "copying duid");				
+			duidcpy(&ifp->duid, &ifc->duid);
+		}
+ 
+		dprintf(LOG_DEBUG,
+			"conf_commit: copying %d rawops from %p (ifc) to %p (ifp)",
+			rawop_count_list(&ifc->rawops), &ifc->rawops, &ifp->rawops);			
+		rawop_clear_list(&ifp->rawops);	
+		rawop_copy_list(&ifp->rawops, &ifc->rawops); // XXX: breaks if move instead of copy
+
+			
 	}
+	
+	/* XXX*/
+	rawop_clear_list(&ifc->rawops);		
+	duidfree(&ifc->duid);
+	
 
 	clear_ifconf(dhcp6_ifconflist);
 	dhcp6_ifconflist = NULL;
@@ -1545,6 +1602,9 @@ add_options(opcode, ifc, cfl0)
 	int opttype;
 	struct authinfo *ainfo;
 	struct ia_conf *iac;
+	/* XXX */
+	char *cp;
+	struct rawoption *rawopc;
 
 	for (cfl = cfl0; cfl; cfl = cfl->next) {
 		switch(cfl->type) {
@@ -1638,6 +1698,17 @@ add_options(opcode, ifc, cfl0)
 				break;
 			}
 			break;
+			
+		/* XXX */
+		case DHCPOPT_RAW:
+			opttype = DHCPOPT_RAW;
+			rawopc = (struct rawoption *) cfl->ptr;
+			dprintf(LOG_INFO, FNAME,
+				"add raw option: %d length: %d",
+				rawopc->opnum, rawopc->datalen);
+			TAILQ_INSERT_TAIL(&ifc->rawops, rawopc, link);	
+			break;
+	
 		case DHCPOPT_SIP:
 		case DHCPOPT_SIPNAME:
 		case DHCPOPT_DNS:
