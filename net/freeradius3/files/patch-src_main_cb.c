--- src/main/cb.c.orig	2021-06-09 07:00:13 UTC
+++ src/main/cb.c
@@ -63,7 +63,7 @@ void cbtls_info(SSL const *s, int where, int ret)
 			/*
 			 *	After a ClientHello, list all the proposed ciphers from the client
 			 */
-#if OPENSSL_VERSION_NUMBER >= 0x10100000L
+#if OPENSSL_VERSION_NUMBER >= 0x10100000L && !defined(LIBRESSL_VERSION_NUMBER)
 			if (SSL_get_state(s) == TLS_ST_SR_CLNT_HELLO) {
 				int i;
 				int num_ciphers;
@@ -174,7 +174,7 @@ void cbtls_msg(int write_p, int msg_version, int conte
 		state->info.alert_level = 0x00;
 		state->info.alert_description = 0x00;
 
-#if OPENSSL_VERSION_NUMBER >= 0x10101000L
+#if OPENSSL_VERSION_NUMBER >= 0x10100000L && !defined(LIBRESSL_VERSION_NUMBER)
 	} else if (content_type == SSL3_RT_INNER_CONTENT_TYPE && buf[0] == SSL3_RT_APPLICATION_DATA) {
 		/* let tls_ack_handler set application_data */
 		state->info.content_type = SSL3_RT_HANDSHAKE;
