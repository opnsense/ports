--- rate.c.orig	2010-05-13 19:13:12.000000000 +0000
+++ rate.c	2010-05-13 19:13:16.000000000 +0000
@@ -311,7 +311,7 @@
 		}
 	}
 
-	if((handle = pcap_open_live(interface, 2048, -1, 50, ebuff))==NULL)
+	if((handle = pcap_open_live(interface, 2048, 0, 50, ebuff))==NULL)
 	{
 		fprintf(stderr, "pcap_open_live(): %s\n", ebuff);
 		return(0);
