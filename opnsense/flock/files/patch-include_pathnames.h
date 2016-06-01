--- include/pathnames.h.orig	2016-06-01 04:01:08 UTC
+++ include/pathnames.h
@@ -46,7 +46,9 @@
 #define	_PATH_MAILDIR		"/var/spool/mail"
 #endif
 #define	_PATH_MOTDFILE		"/etc/motd"
+#ifndef _PATH_NOLOGIN
 #define	_PATH_NOLOGIN		"/etc/nologin"
+#endif
 #define	_PATH_VAR_NOLOGIN	"/var/run/nologin"
 
 #define _PATH_LOGIN		"/bin/login"
