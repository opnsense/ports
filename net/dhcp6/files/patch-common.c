--- common.c.orig	2017-02-28 19:06:15 UTC
+++ common.c
@@ -114,6 +114,105 @@ static ssize_t gethwid __P((char *, int,
 static char *sprint_uint64 __P((char *, int, u_int64_t));
 static char *sprint_auth __P((struct dhcp6_optinfo *));
 
+/* XXX */
+int
+rawop_count_list(head)
+	struct rawop_list *head;
+{
+	struct rawoption *op;
+	int i;
+
+	//dprintf(LOG_INFO, FNAME, "counting list at %p", (void*)head);
+	
+	for (i = 0, op = TAILQ_FIRST(head); op; op = TAILQ_NEXT(op, link)) {
+		i++;
+	}
+
+	return (i);
+}
+
+void
+rawop_clear_list(head)
+	struct rawop_list *head;
+{
+	struct rawoption *op;
+	
+	//dprintf(LOG_INFO, FNAME, "clearing %d rawops at %p", rawop_count_list(head), (void*)head);
+	
+	while ((op = TAILQ_FIRST(head)) != NULL) {
+		
+		//dprintf(LOG_INFO, FNAME, "  current op: %p link: %p", (void*)op, op->link);
+		TAILQ_REMOVE(head, op, link);
+		
+		if (op->data != NULL) {
+			d_printf(LOG_INFO, FNAME, "    freeing op data at %p", (void*)op->data);
+			free(op->data);	
+		}
+		free(op);	// Needed?
+	}	
+	return;
+}
+
+int
+rawop_copy_list(dst, src)
+	struct rawop_list *dst, *src;
+{
+	struct rawoption *op, *newop;	
+	
+	/*
+	d_printf(LOG_INFO, FNAME,
+		"  copying rawop list %p to %p (%d ops)",
+		(void*)src, (void*)dst, rawop_count_list(src));
+	*/
+	
+	for (op = TAILQ_FIRST(src); op; op = TAILQ_NEXT(op, link)) {
+		newop = NULL;
+		if ((newop = malloc(sizeof(*newop))) == NULL) {
+			d_printf(LOG_ERR, FNAME,
+				"failed to allocate memory for a new raw option");
+			goto fail;
+		}
+		memset(newop, 0, sizeof(*newop));
+
+		newop->opnum = op->opnum;
+		newop->datalen = op->datalen;	
+		newop->data = NULL;
+		
+		/* copy data */
+		if ((newop->data = malloc(newop->datalen)) == NULL) {
+			d_printf(LOG_ERR, FNAME,
+				"failed to allocate memory for new raw option data");
+			goto fail;
+		}
+		memcpy(newop->data, op->data, newop->datalen);
+		//dprintf(LOG_INFO, FNAME, "    copied %d bytes of data at %p", newop->datalen, (void*)newop->data);		
+			
+		TAILQ_INSERT_TAIL(dst, newop, link);
+	}
+	return (0);
+	
+  fail:
+	rawop_clear_list(dst);
+	return (-1);	
+}
+
+void
+rawop_move_list(dst, src)
+	struct rawop_list *dst, *src;
+{
+	struct rawoption *op;
+	/*
+	d_printf(LOG_INFO, FNAME,
+		"  moving rawop list of %d from %p to %p",
+		rawop_count_list(src), (void*)src, (void*)dst);	
+	*/
+	while ((op = TAILQ_FIRST(src)) != NULL) {
+		TAILQ_REMOVE(src, op, link);
+		TAILQ_INSERT_TAIL(dst, op, link);
+	}
+}
+
+
 int
 dhcp6_copy_list(dst, src)
 	struct dhcp6_list *dst, *src;
@@ -1337,6 +1436,9 @@ dhcp6_init_options(optinfo)
 	TAILQ_INIT(&optinfo->bcmcs_list);
 	TAILQ_INIT(&optinfo->bcmcsname_list);
 
+	/* XXX */
+	TAILQ_INIT(&optinfo->rawops);
+
 	optinfo->authproto = DHCP6_AUTHPROTO_UNDEF;
 	optinfo->authalgorithm = DHCP6_AUTHALG_UNDEF;
 	optinfo->authrdm = DHCP6_AUTHRDM_UNDEF;
@@ -1380,6 +1482,9 @@ dhcp6_clear_options(optinfo)
 	if (optinfo->ifidopt_id != NULL)
 		free(optinfo->ifidopt_id);
 
+	/* XXX */
+	rawop_clear_list(&optinfo->rawops);
+
 	dhcp6_init_options(optinfo);
 }
 
@@ -1429,6 +1534,9 @@ dhcp6_copy_options(dst, src)
 	dst->refreshtime = src->refreshtime;
 	dst->pref = src->pref;
 
+	/* XXX */
+	rawop_copy_list(&dst->rawops, &src->rawops);
+
 	if (src->relaymsg_msg != NULL) {
 		if ((dst->relaymsg_msg = malloc(src->relaymsg_len)) == NULL)
 			goto fail;
@@ -1497,6 +1605,9 @@ dhcp6_get_options(p, ep, optinfo)
 	struct dhcp6_list sublist;
 	int authinfolen;
 
+	/* XXX */
+	struct rawoption *rawop;
+
 	bp = (char *)p;
 	for (; p + 1 <= ep; p = np) {
 		struct duid duid0;
@@ -1697,6 +1808,15 @@ dhcp6_get_options(p, ep, optinfo)
 			case DHCP6_AUTHPROTO_RECONFIG:
 				break;
 #endif
+			/* XXX */
+			case 0:
+				// Discard auth
+				d_printf(LOG_DEBUG, FNAME, "  Discarding null authentication");
+				optinfo->authproto = DHCP6_AUTHPROTO_UNDEF;
+				optinfo->authalgorithm = DHCP6_AUTHALG_UNDEF;
+				optinfo->authrdm = DHCP6_AUTHRDM_UNDEF;
+				break;
+
 			default:
 				d_printf(LOG_INFO, FNAME,
 				    "unsupported authentication protocol: %d",
@@ -1872,6 +1992,16 @@ dhcp6_get_options(p, ep, optinfo)
 			dhcp6_clear_list(&sublist);
 
 			break;
+			
+		/* XX */		
+		case DHCPOPT_RAW:
+			rawop = (struct rawoption *) cp;
+			d_printf(LOG_DEBUG, FNAME,
+				"raw option: %d",
+				rawop->opnum);				
+			TAILQ_INSERT_TAIL(&optinfo->rawops, rawop, link);			
+			break;			
+
 		default:
 			/* no option specific behavior */
 			d_printf(LOG_INFO, FNAME,
@@ -2248,6 +2378,8 @@ dhcp6_set_options(type, optbp, optep, op
 	struct dhcp6_listval *stcode, *op;
 	int len = 0, optlen;
 	char *tmpbuf = NULL;
+	/* XXX */
+	struct rawoption *rawop;
 
 	if (optinfo->clientID.duid_len) {
 		if (copy_option(DH6OPT_CLIENTID, optinfo->clientID.duid_len,
@@ -2471,6 +2603,21 @@ dhcp6_set_options(type, optbp, optep, op
 			goto fail;
 		}
 	}
+	/* XXX */
+	for (rawop = TAILQ_FIRST(&optinfo->rawops); rawop;
+	    rawop = TAILQ_NEXT(rawop, link)) {
+			
+		d_printf(LOG_DEBUG, FNAME,
+			"  raw option %d length %d at %p",
+			rawop->opnum, rawop->datalen, (void*)rawop);
+			
+		if (copy_option(rawop->opnum, rawop->datalen,
+			rawop->data, &p,
+		    optep, &len) != 0) {
+			goto fail;
+		}
+	}
+	
 
 	if (optinfo->authproto != DHCP6_AUTHPROTO_UNDEF) {
 		struct dhcp6opt_auth *auth;
@@ -3051,7 +3198,11 @@ dhcp6optstr(type)
 	case DH6OPT_SUBSCRIBER_ID:
 		return ("subscriber ID");
 	case DH6OPT_CLIENT_FQDN:
-		return ("client FQDN");
+		return ("client FQDN");		
+	/* XXX */
+	case DHCPOPT_RAW:
+		return ("raw");
+
 	default:
 		snprintf(genstr, sizeof(genstr), "opt_%d", type);
 		return (genstr);
