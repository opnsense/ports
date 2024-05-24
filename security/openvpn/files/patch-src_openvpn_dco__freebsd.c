--- src/openvpn/dco_freebsd.c.orig	2024-03-19 21:19:35 UTC
+++ src/openvpn/dco_freebsd.c
@@ -219,6 +219,9 @@ create_interface(struct tuntap *tt, const char *dev)
     {
         ifr.ifr_data = (char *)dev;
     }
+
+    snprintf(tt->dco.ifname, IFNAMSIZ, "%s", ifr.ifr_data);
+
     ret = ioctl(tt->dco.fd, SIOCSIFNAME, &ifr);
     if (ret)
     {
@@ -229,16 +232,6 @@ create_interface(struct tuntap *tt, const char *dev)
         return ret;
     }
 
-    snprintf(tt->dco.ifname, IFNAMSIZ, "%s", ifr.ifr_data);
-
-    /* see "Interface Flags" in ifnet(9) */
-    int i = IFF_POINTOPOINT | IFF_MULTICAST;
-    if (tt->topology == TOP_SUBNET)
-    {
-        i = IFF_BROADCAST | IFF_MULTICAST;
-    }
-    dco_set_ifmode(&tt->dco, i);
-
     return 0;
 }
 
@@ -265,7 +258,20 @@ remove_interface(struct tuntap *tt)
 int
 open_tun_dco(struct tuntap *tt, openvpn_net_ctx_t *ctx, const char *dev)
 {
-    return create_interface(tt, dev);
+    int ret = create_interface(tt, dev);
+
+    if (ret >= 0 || ret == -EEXIST)
+    {
+        /* see "Interface Flags" in ifnet(9) */
+        int i = IFF_POINTOPOINT | IFF_MULTICAST;
+        if (tt->topology == TOP_SUBNET)
+        {
+            i = IFF_BROADCAST | IFF_MULTICAST;
+        }
+        dco_set_ifmode(&tt->dco, i);
+    }
+
+    return ret;
 }
 
 void
