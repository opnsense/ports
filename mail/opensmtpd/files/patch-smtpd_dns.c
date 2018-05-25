--- smtpd/dns.c.orig	2016-05-12 16:56:04 UTC
+++ smtpd/dns.c
@@ -352,7 +352,8 @@ dns_dispatch_mx(struct asr_result *ar, void *arg)
 	char			 buf[512];
 	size_t			 found;
 
-	if (ar->ar_h_errno && ar->ar_h_errno != NO_DATA) {
+	if (ar->ar_h_errno && ar->ar_h_errno != NO_DATA &&
+	    ar->ar_rcode != NOTIMP) {
 
 		m_create(s->p,  IMSG_MTA_DNS_HOST_END, 0, 0, -1);
 		m_add_id(s->p, s->reqid);
