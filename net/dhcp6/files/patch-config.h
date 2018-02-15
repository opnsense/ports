--- config.h.orig	2017-02-28 19:06:15 UTC
+++ config.h
@@ -80,6 +80,10 @@ struct dhcp6_if {
 	struct dhcp6_poolspec pool;	/* address pool (server only) */
 	char *scriptpath;	/* path to config script (client only) */
 
+	/* XXX */
+	struct duid duid;
+	struct rawop_list rawops;
+
 	struct dhcp6_list reqopt_list;
 	struct ia_conflist iaconf_list;
 
@@ -279,7 +283,10 @@ enum { DECL_SEND, DECL_ALLOW, DECL_INFO_
        IACONF_PIF, IACONF_PREFIX, IACONF_ADDR,
        DHCPOPT_SIP, DHCPOPT_SIPNAME,
        AUTHPARAM_PROTO, AUTHPARAM_ALG, AUTHPARAM_RDM, AUTHPARAM_KEY,
-       KEYPARAM_REALM, KEYPARAM_KEYID, KEYPARAM_SECRET, KEYPARAM_EXPIRE };
+      KEYPARAM_REALM, KEYPARAM_KEYID, KEYPARAM_SECRET, KEYPARAM_EXPIRE,
+       /* XXX */
+       DHCPOPT_RAW
+    };
 
 typedef enum {DHCP6_MODE_SERVER, DHCP6_MODE_CLIENT, DHCP6_MODE_RELAY }
 dhcp6_mode_t;
