--- src/libcharon/plugins/smp/smp.c.orig	2015-04-13 05:54:30.000000000 +0000
+++ src/libcharon/plugins/smp/smp.c	2015-04-13 05:56:27.000000000 +0000
@@ -737,7 +737,7 @@
  */
 plugin_t *smp_plugin_create()
 {
-	struct sockaddr_un unix_addr = { AF_UNIX, IPSEC_PIDDIR "/charon.xml"};
+	struct sockaddr_un unix_addr;
 	private_smp_t *this;
 	mode_t old;
 
@@ -766,6 +766,11 @@
 		return NULL;
 	}
 
+	strlcpy(unix_addr.sun_path, IPSEC_PIDDIR "/charon.xml",
+	    sizeof(unix_addr.sun_path));
+	unix_addr.sun_len = sizeof(unix_addr);
+ 	unix_addr.sun_family = PF_LOCAL;
+
 	unlink(unix_addr.sun_path);
 	old = umask(S_IRWXO);
 	if (bind(this->socket, (struct sockaddr *)&unix_addr, sizeof(unix_addr)) < 0)
