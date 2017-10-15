--- vtysh/vtysh.c.orig	2017-10-13 23:17:26 UTC
+++ vtysh/vtysh.c
@@ -249,7 +249,7 @@ void vtysh_pager_init(void)
 	if (pager_defined)
 		vtysh_pager_name = strdup(pager_defined);
 	else
-		vtysh_pager_name = strdup("more");
+		vtysh_pager_name = strdup("cat");
 }
 
 /* Command execution over the vty interface. */
