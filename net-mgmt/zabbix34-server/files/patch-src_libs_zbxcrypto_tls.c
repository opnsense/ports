--- src/libs/zbxcrypto/tls.c.orig	2018-02-16 08:39:09 UTC
+++ src/libs/zbxcrypto/tls.c
@@ -155,6 +155,14 @@ static void	OPENSSL_cleanup(void)
 }
 #endif
 
+#ifdef LIBRESSL_VERSION_NUMBER
+static void     OPENSSL_cleanup(void)
+{
+        RAND_cleanup();
+        ERR_free_strings();
+}
+#endif
+
 struct zbx_tls_context
 {
 #if defined(HAVE_POLARSSL)
@@ -1363,6 +1371,7 @@ static int	zbx_psk_cb(gnutls_session_t s
 static unsigned int	zbx_psk_client_cb(SSL *ssl, const char *hint, char *identity,
 		unsigned int max_identity_len, unsigned char *psk, unsigned int max_psk_len)
 {
+#ifndef OPENSSL_NO_PSK
 	const char	*__function_name = "zbx_psk_client_cb";
 
 	ZBX_UNUSED(ssl);
@@ -1392,6 +1401,9 @@ static unsigned int	zbx_psk_client_cb(SS
 	memcpy(psk, psk_for_cb, psk_len_for_cb);
 
 	return (unsigned int)psk_len_for_cb;
+#else
+	return 0;
+#endif
 }
 
 /******************************************************************************
@@ -1419,6 +1431,7 @@ static unsigned int	zbx_psk_client_cb(SS
 static unsigned int	zbx_psk_server_cb(SSL *ssl, const char *identity, unsigned char *psk,
 		unsigned int max_psk_len)
 {
+#ifndef OPENSSL_NO_PSK
 	const char	*__function_name = "zbx_psk_server_cb";
 	char		*psk_loc;
 	size_t		psk_len = 0;
@@ -1481,7 +1494,7 @@ static unsigned int	zbx_psk_server_cb(SS
 
 		return (unsigned int)psk_len;	/* success */
 	}
-
+#endif
 	return 0;	/* PSK not found */
 }
 #endif
@@ -3385,6 +3398,7 @@ void	zbx_tls_init_child(void)
 		zbx_log_ciphersuites(__function_name, "certificate", ctx_cert);
 	}
 
+#ifndef OPENSSL_NO_PSK
 	if (NULL != ctx_psk)
 	{
 		const char	*ciphers;
@@ -3418,6 +3432,7 @@ void	zbx_tls_init_child(void)
 
 		zbx_log_ciphersuites(__function_name, "PSK", ctx_psk);
 	}
+#endif
 
 	if (NULL != ctx_all)
 	{
@@ -3425,8 +3440,10 @@ void	zbx_tls_init_child(void)
 
 		SSL_CTX_set_info_callback(ctx_all, zbx_openssl_info_cb);
 
+#ifndef OPENSSL_NO_PSK
 		if (0 != (program_type & (ZBX_PROGRAM_TYPE_SERVER | ZBX_PROGRAM_TYPE_PROXY | ZBX_PROGRAM_TYPE_AGENTD)))
 			SSL_CTX_set_psk_server_callback(ctx_all, zbx_psk_server_cb);
+#endif
 
 		SSL_CTX_set_mode(ctx_all, SSL_MODE_AUTO_RETRY);
 		SSL_CTX_set_options(ctx_all, SSL_OP_CIPHER_SERVER_PREFERENCE | SSL_OP_NO_TICKET);
@@ -4163,6 +4180,7 @@ int	zbx_tls_connect(zbx_socket_t *s, uns
 			goto out;
 		}
 
+#ifndef OPENSSL_NO_PSK
 		if (NULL == (s->tls_ctx->ctx = SSL_new(ctx_psk)))
 		{
 			zbx_snprintf_alloc(error, &error_alloc, &error_offset, "cannot create connection context:");
@@ -4185,6 +4203,7 @@ int	zbx_tls_connect(zbx_socket_t *s, uns
 			}
 		}
 		else
+#endif
 		{
 			/* PSK comes from a database (case for a server/proxy when it connects to an agent for */
 			/* passive checks, for a server when it connects to a passive proxy) */
@@ -5492,9 +5511,11 @@ int	zbx_tls_get_attr_psk(const zbx_socke
 	else
 		return FAIL;
 #elif defined(HAVE_OPENSSL)
+#ifndef OPENSSL_NO_PSK
 	if (NULL != (attr->psk_identity = SSL_get_psk_identity(s->tls_ctx->ctx)))
 		attr->psk_identity_len = strlen(attr->psk_identity);
 	else
+#endif
 		return FAIL;
 #endif
 
