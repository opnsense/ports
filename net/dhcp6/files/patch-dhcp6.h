--- dhcp6.h.orig	2017-02-28 19:06:15 UTC
+++ dhcp6.h
@@ -108,6 +108,17 @@ typedef uint64_t u_int64_t;
 #define DHCP6_IRT_DEFAULT 86400	/* 1 day */
 #define DHCP6_IRT_MINIMUM 600
 
+/* XXX */
+TAILQ_HEAD(rawop_list, rawoption);
+struct rawoption {
+	TAILQ_ENTRY(rawoption) link;
+	
+	int opnum;
+	char *data;
+	int datalen;
+};
+
+
 /* DUID: DHCP unique Identifier */
 struct duid {
 	size_t duid_len;	/* length */
@@ -197,6 +208,9 @@ struct dhcp6_optinfo {
 	struct dhcp6_list nispname_list; /* NIS+ domain list */
 	struct dhcp6_list bcmcs_list; /* BCMC server list */
 	struct dhcp6_list bcmcsname_list; /* BCMC domain list */
+	/* XXX */
+	struct rawop_list rawops;
+	
 
 	struct dhcp6_vbuf relay_msg; /* relay message */
 #define relaymsg_len relay_msg.dv_len
