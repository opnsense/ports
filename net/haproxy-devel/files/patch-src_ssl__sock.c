--- src/ssl_sock.c.orig	2018-08-02 16:12:50 UTC
+++ src/ssl_sock.c
@@ -56,7 +56,7 @@
 #include <openssl/engine.h>
 #endif
 
-#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC)
+#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC) && !defined(LIBRESSL_VERSION_NUMBER)
 #include <openssl/async.h>
 #endif
 
@@ -433,7 +433,7 @@ fail_get:
 }
 #endif
 
-#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC)
+#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC) && !defined(LIBRESSL_VERSION_NUMBER)
 /*
  * openssl async fd handler
  */
@@ -1132,8 +1132,11 @@ static int ssl_sock_load_ocsp(SSL_CTX *c
 		ocsp = NULL;
 
 #ifndef SSL_CTX_get_tlsext_status_cb
+#ifndef SSL_CTRL_GET_TLSEXT_STATUS_REQ_CB
+#define SSL_CTRL_GET_TLSEXT_STATUS_REQ_CB 128
+#endif
 # define SSL_CTX_get_tlsext_status_cb(ctx, cb) \
-	*cb = (void (*) (void))ctx->tlsext_status_cb;
+	*cb = SSL_CTX_ctrl(ctx,SSL_CTRL_GET_TLSEXT_STATUS_REQ_CB,0, (void (**)(void))cb)
 #endif
 	SSL_CTX_get_tlsext_status_cb(ctx, &callback);
 
@@ -1161,7 +1164,10 @@ static int ssl_sock_load_ocsp(SSL_CTX *c
 		int key_type;
 		EVP_PKEY *pkey;
 
-#ifdef SSL_CTX_get_tlsext_status_arg
+#if defined(SSL_CTX_get_tlsext_status_arg) || defined(LIBRESSL_VERSION_NUMBER)
+#ifndef SSL_CTRL_GET_TLSEXT_STATUS_REQ_CB_ARG
+#define SSL_CTRL_GET_TLSEXT_STATUS_REQ_CB_ARG 129
+#endif
 		SSL_CTX_ctrl(ctx, SSL_CTRL_GET_TLSEXT_STATUS_REQ_CB_ARG, 0, &cb_arg);
 #else
 		cb_arg = ctx->tlsext_status_arg;
@@ -1970,7 +1976,7 @@ ssl_sock_generate_certificate_from_conn(
 #define SSL_OP_PRIORITIZE_CHACHA 0
 #endif
 
-#if (OPENSSL_VERSION_NUMBER < 0x1010000fL)
+#if (OPENSSL_VERSION_NUMBER < 0x1010000fL) || defined(LIBRESSL_VERSION_NUMBER)
 typedef enum { SET_CLIENT, SET_SERVER } set_context_func;
 
 static void ctx_set_SSLv3_func(SSL_CTX *ctx, set_context_func c)
@@ -2077,7 +2083,7 @@ static void ssl_sock_switchctx_set(SSL *
 	SSL_set_SSL_CTX(ssl, ctx);
 }
 
-#if (OPENSSL_VERSION_NUMBER >= 0x10101000L) || defined(OPENSSL_IS_BORINGSSL)
+#if ((OPENSSL_VERSION_NUMBER >= 0x10101000L) || defined(OPENSSL_IS_BORINGSSL)) && !defined(LIBRESSL_VERSION_NUMBER)
 
 static int ssl_sock_switchctx_err_cbk(SSL *ssl, int *al, void *priv)
 {
@@ -3783,7 +3789,7 @@ ssl_sock_initial_ctx(struct bind_conf *b
 	conf_ssl_methods->min = min;
 	conf_ssl_methods->max = max;
 
-#if (OPENSSL_VERSION_NUMBER < 0x1010000fL)
+#if (OPENSSL_VERSION_NUMBER < 0x1010000fL) || defined(LIBRESSL_VERSION_NUMBER)
 	/* Keep force-xxx implementation as it is in older haproxy. It's a
 	   precautionary measure to avoid any suprise with older openssl version. */
 	if (min == max)
@@ -3804,7 +3810,7 @@ ssl_sock_initial_ctx(struct bind_conf *b
 		options &= ~SSL_OP_CIPHER_SERVER_PREFERENCE;
 	SSL_CTX_set_options(ctx, options);
 
-#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC)
+#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC) && !defined(LIBRESSL_VERSION_NUMBER)
 	if (global_ssl.async)
 		mode |= SSL_MODE_ASYNC;
 #endif
@@ -3816,7 +3822,7 @@ ssl_sock_initial_ctx(struct bind_conf *b
 #ifdef OPENSSL_IS_BORINGSSL
 	SSL_CTX_set_select_certificate_cb(ctx, ssl_sock_switchctx_cbk);
 	SSL_CTX_set_tlsext_servername_callback(ctx, ssl_sock_switchctx_err_cbk);
-#elif (OPENSSL_VERSION_NUMBER >= 0x10101000L)
+#elif (OPENSSL_VERSION_NUMBER >= 0x10101000L) && !defined(LIBRESSL_VERSION_NUMBER)
 	SSL_CTX_set_client_hello_cb(ctx, ssl_sock_switchctx_cbk, NULL);
 	SSL_CTX_set_tlsext_servername_callback(ctx, ssl_sock_switchctx_err_cbk);
 #else
@@ -4554,7 +4560,7 @@ int ssl_sock_prepare_srv_ctx(struct serv
 		cfgerr += 1;
 	}
 
-#if (OPENSSL_VERSION_NUMBER < 0x1010000fL)
+#if (OPENSSL_VERSION_NUMBER < 0x1010000fL) || defined(LIBRESSL_VERSION_NUMBER)
 	/* Keep force-xxx implementation as it is in older haproxy. It's a
 	   precautionary measure to avoid any suprise with older openssl version. */
 	if (min == max)
@@ -4573,7 +4579,7 @@ int ssl_sock_prepare_srv_ctx(struct serv
 		options |= SSL_OP_NO_TICKET;
 	SSL_CTX_set_options(ctx, options);
 
-#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC)
+#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC) && !defined(LIBRESSL_VERSION_NUMBER)
 	if (global_ssl.async)
 		mode |= SSL_MODE_ASYNC;
 #endif
@@ -5070,7 +5076,7 @@ int ssl_sock_handshake(struct connection
 	if (!conn->xprt_ctx)
 		goto out_error;
 
-#if OPENSSL_VERSION_NUMBER >= 0x10101000L
+#if (OPENSSL_VERSION_NUMBER >= 0x10101000L) && !defined(LIBRESSL_VERSION_NUMBER)
 	/*
 	 * Check if we have early data. If we do, we have to read them
 	 * before SSL_do_handshake() is called, And there's no way to
@@ -5127,7 +5133,7 @@ int ssl_sock_handshake(struct connection
 				fd_cant_recv(conn->handle.fd);
 				return 0;
 			}
-#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC)
+#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC) && !defined(LIBRESSL_VERSION_NUMBER)
 			else if (ret == SSL_ERROR_WANT_ASYNC) {
 				ssl_async_process_fds(conn, conn->xprt_ctx);
 				return 0;
@@ -5211,7 +5217,7 @@ check_error:
 			fd_cant_recv(conn->handle.fd);
 			return 0;
 		}
-#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC)
+#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC) && !defined(LIBRESSL_VERSION_NUMBER)
 		else if (ret == SSL_ERROR_WANT_ASYNC) {
 			ssl_async_process_fds(conn, conn->xprt_ctx);
 			return 0;
@@ -5270,7 +5276,7 @@ check_error:
 			goto out_error;
 		}
 	}
-#if (OPENSSL_VERSION_NUMBER >= 0x10101000L)
+#if (OPENSSL_VERSION_NUMBER >= 0x10101000L) && !defined(LIBRESSL_VERSION_NUMBER)
 	else {
 		/*
 		 * If the server refused the early data, we have to send a
@@ -5289,7 +5295,7 @@ check_error:
 
 reneg_ok:
 
-#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC)
+#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC) && !defined(LIBRESSL_VERSION_NUMBER)
 	/* ASYNC engine API doesn't support moving read/write
 	 * buffers. So we disable ASYNC mode right after
 	 * the handshake to avoid buffer oveflows.
@@ -5387,7 +5393,7 @@ static size_t ssl_sock_to_buf(struct con
 			continue;
 		}
 
-#if (OPENSSL_VERSION_NUMBER >= 0x10101000L)
+#if (OPENSSL_VERSION_NUMBER >= 0x10101000L) && !defined(LIBRESSL_VERSION_NUMBER)
 		if (conn->flags & CO_FL_EARLY_SSL_HS) {
 			size_t read_length;
 
@@ -5439,7 +5445,7 @@ static size_t ssl_sock_to_buf(struct con
 				/* handshake is running, and it needs to enable write */
 				conn->flags |= CO_FL_SSL_WAIT_HS;
 				__conn_sock_want_send(conn);
-#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC)
+#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC) && !defined(LIBRESSL_VERSION_NUMBER)
 				/* Async mode can be re-enabled, because we're leaving data state.*/
 				if (global_ssl.async)
 					SSL_set_mode(conn->xprt_ctx, SSL_MODE_ASYNC);
@@ -5451,7 +5457,7 @@ static size_t ssl_sock_to_buf(struct con
 					/* handshake is running, and it may need to re-enable read */
 					conn->flags |= CO_FL_SSL_WAIT_HS;
 					__conn_sock_want_recv(conn);
-#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC)
+#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC) && !defined(LIBRESSL_VERSION_NUMBER)
 					/* Async mode can be re-enabled, because we're leaving data state.*/
 					if (global_ssl.async)
 						SSL_set_mode(conn->xprt_ctx, SSL_MODE_ASYNC);
@@ -5548,7 +5554,7 @@ static size_t ssl_sock_from_buf(struct c
 			conn->xprt_st |= SSL_SOCK_SEND_UNLIMITED;
 		}
 
-#if (OPENSSL_VERSION_NUMBER >= 0x10101000L)
+#if (OPENSSL_VERSION_NUMBER >= 0x10101000L) && !defined(LIBRESSL_VERSION_NUMBER)
 		if (!SSL_is_init_finished(conn->xprt_ctx)) {
 			unsigned int max_early;
 
@@ -5601,7 +5607,7 @@ static size_t ssl_sock_from_buf(struct c
 					/* handshake is running, and it may need to re-enable write */
 					conn->flags |= CO_FL_SSL_WAIT_HS;
 					__conn_sock_want_send(conn);
-#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC)
+#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC) && !defined(LIBRESSL_VERSION_NUMBER)
 					/* Async mode can be re-enabled, because we're leaving data state.*/
 					if (global_ssl.async)
 						SSL_set_mode(conn->xprt_ctx, SSL_MODE_ASYNC);
@@ -5616,7 +5622,7 @@ static size_t ssl_sock_from_buf(struct c
 				/* handshake is running, and it needs to enable read */
 				conn->flags |= CO_FL_SSL_WAIT_HS;
 				__conn_sock_want_recv(conn);
-#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC)
+#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC) && !defined(LIBRESSL_VERSION_NUMBER)
 				/* Async mode can be re-enabled, because we're leaving data state.*/
 				if (global_ssl.async)
 					SSL_set_mode(conn->xprt_ctx, SSL_MODE_ASYNC);
@@ -5642,7 +5648,7 @@ static size_t ssl_sock_from_buf(struct c
 static void ssl_sock_close(struct connection *conn) {
 
 	if (conn->xprt_ctx) {
-#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC)
+#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC) && !defined(LIBRESSL_VERSION_NUMBER)
 		if (global_ssl.async) {
 			OSSL_ASYNC_FD all_fd[32], afd;
 			size_t num_all_fds = 0;
