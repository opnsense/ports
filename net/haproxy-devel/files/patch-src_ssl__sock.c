--- src/ssl_sock.c.orig	2019-01-16 17:18:07 UTC
+++ src/ssl_sock.c
@@ -57,7 +57,7 @@
 #include <openssl/engine.h>
 #endif
 
-#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC)
+#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC) && !defined(LIBRESSL_VERSION_NUMBER)
 #include <openssl/async.h>
 #endif
 
@@ -151,6 +151,11 @@
 #define MC_SSL_O_NO_TLSV12      0x0008	/* disable TLSv12 */
 #define MC_SSL_O_NO_TLSV13      0x0010	/* disable TLSv13 */
 
+#ifdef LIBRESSL_VERSION_NUMBER
+#define OSSL_HANDSHAKE_STATE int
+#define TLS_ST_BEFORE 0
+#endif
+
 /* ssl_methods versions */
 enum {
 	CONF_TLSV_NONE = 0,
@@ -459,7 +464,7 @@ fail_get:
 }
 #endif
 
-#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC)
+#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC) && !defined(LIBRESSL_VERSION_NUMBER)
 /*
  * openssl async fd handler
  */
@@ -1199,8 +1204,11 @@ static int ssl_sock_load_ocsp(SSL_CTX *ctx, const char
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
 
@@ -1228,7 +1236,10 @@ static int ssl_sock_load_ocsp(SSL_CTX *ctx, const char
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
@@ -2063,7 +2074,7 @@ ssl_sock_generate_certificate_from_conn(struct bind_co
 #define SSL_OP_PRIORITIZE_CHACHA 0
 #endif
 
-#if (OPENSSL_VERSION_NUMBER < 0x1010000fL)
+#if (OPENSSL_VERSION_NUMBER < 0x1010000fL) || defined(LIBRESSL_VERSION_NUMBER)
 typedef enum { SET_CLIENT, SET_SERVER } set_context_func;
 
 static void ctx_set_SSLv3_func(SSL_CTX *ctx, set_context_func c)
@@ -2170,7 +2181,7 @@ static void ssl_sock_switchctx_set(SSL *ssl, SSL_CTX *
 	SSL_set_SSL_CTX(ssl, ctx);
 }
 
-#if (OPENSSL_VERSION_NUMBER >= 0x10101000L) || defined(OPENSSL_IS_BORINGSSL)
+#if ((OPENSSL_VERSION_NUMBER >= 0x10101000L) || defined(OPENSSL_IS_BORINGSSL)) && !defined(LIBRESSL_VERSION_NUMBER)
 
 static int ssl_sock_switchctx_err_cbk(SSL *ssl, int *al, void *priv)
 {
@@ -3876,7 +3887,7 @@ ssl_sock_initial_ctx(struct bind_conf *bind_conf)
 	conf_ssl_methods->min = min;
 	conf_ssl_methods->max = max;
 
-#if (OPENSSL_VERSION_NUMBER < 0x1010000fL)
+#if (OPENSSL_VERSION_NUMBER < 0x1010000fL) || defined(LIBRESSL_VERSION_NUMBER)
 	/* Keep force-xxx implementation as it is in older haproxy. It's a
 	   precautionary measure to avoid any surprise with older openssl version. */
 	if (min == max)
@@ -3897,7 +3908,7 @@ ssl_sock_initial_ctx(struct bind_conf *bind_conf)
 		options &= ~SSL_OP_CIPHER_SERVER_PREFERENCE;
 	SSL_CTX_set_options(ctx, options);
 
-#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC)
+#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC) && !defined(LIBRESSL_VERSION_NUMBER)
 	if (global_ssl.async)
 		mode |= SSL_MODE_ASYNC;
 #endif
@@ -3909,7 +3920,7 @@ ssl_sock_initial_ctx(struct bind_conf *bind_conf)
 #ifdef OPENSSL_IS_BORINGSSL
 	SSL_CTX_set_select_certificate_cb(ctx, ssl_sock_switchctx_cbk);
 	SSL_CTX_set_tlsext_servername_callback(ctx, ssl_sock_switchctx_err_cbk);
-#elif (OPENSSL_VERSION_NUMBER >= 0x10101000L)
+#elif (OPENSSL_VERSION_NUMBER >= 0x10101000L) && !defined(LIBRESSL_VERSION_NUMBER)
 	if (bind_conf->ssl_conf.early_data) {
 		SSL_CTX_set_options(ctx, SSL_OP_NO_ANTI_REPLAY);
 		SSL_CTX_set_max_early_data(ctx, global.tune.bufsize - global.tune.maxrewrite);
@@ -4664,7 +4675,7 @@ int ssl_sock_prepare_srv_ctx(struct server *srv)
 		cfgerr += 1;
 	}
 
-#if (OPENSSL_VERSION_NUMBER < 0x1010000fL)
+#if (OPENSSL_VERSION_NUMBER < 0x1010000fL) || defined(LIBRESSL_VERSION_NUMBER)
 	/* Keep force-xxx implementation as it is in older haproxy. It's a
 	   precautionary measure to avoid any surprise with older openssl version. */
 	if (min == max)
@@ -4683,7 +4694,7 @@ int ssl_sock_prepare_srv_ctx(struct server *srv)
 		options |= SSL_OP_NO_TICKET;
 	SSL_CTX_set_options(ctx, options);
 
-#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC)
+#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC) && !defined(LIBRESSL_VERSION_NUMBER)
 	if (global_ssl.async)
 		mode |= SSL_MODE_ASYNC;
 #endif
@@ -5206,7 +5217,7 @@ int ssl_sock_handshake(struct connection *conn, unsign
 	if (!conn->xprt_ctx)
 		goto out_error;
 
-#if OPENSSL_VERSION_NUMBER >= 0x10101000L
+#if (OPENSSL_VERSION_NUMBER >= 0x10101000L) && !defined(LIBRESSL_VERSION_NUMBER)
 	/*
 	 * Check if we have early data. If we do, we have to read them
 	 * before SSL_do_handshake() is called, And there's no way to
@@ -5263,7 +5274,7 @@ int ssl_sock_handshake(struct connection *conn, unsign
 				fd_cant_recv(conn->handle.fd);
 				return 0;
 			}
-#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC)
+#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC) && !defined(LIBRESSL_VERSION_NUMBER)
 			else if (ret == SSL_ERROR_WANT_ASYNC) {
 				ssl_async_process_fds(conn, conn->xprt_ctx);
 				return 0;
@@ -5278,7 +5289,7 @@ int ssl_sock_handshake(struct connection *conn, unsign
 					conn->err_code = CO_ER_SSL_HANDSHAKE;
 #else
 					int empty_handshake;
-#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(LIBRESSL_VERSION_NUMBER)
+#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL)
 					OSSL_HANDSHAKE_STATE state = SSL_get_state((SSL *)conn->xprt_ctx);
 					empty_handshake = state == TLS_ST_BEFORE;
 #else
@@ -5347,7 +5358,7 @@ check_error:
 			fd_cant_recv(conn->handle.fd);
 			return 0;
 		}
-#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC)
+#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC) && !defined(LIBRESSL_VERSION_NUMBER)
 		else if (ret == SSL_ERROR_WANT_ASYNC) {
 			ssl_async_process_fds(conn, conn->xprt_ctx);
 			return 0;
@@ -5362,7 +5373,7 @@ check_error:
 				conn->err_code = CO_ER_SSL_HANDSHAKE;
 #else
 				int empty_handshake;
-#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(LIBRESSL_VERSION_NUMBER)
+#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL)
 				OSSL_HANDSHAKE_STATE state = SSL_get_state((SSL *)conn->xprt_ctx);
 				empty_handshake = state == TLS_ST_BEFORE;
 #else
@@ -5406,7 +5417,7 @@ check_error:
 			goto out_error;
 		}
 	}
-#if (OPENSSL_VERSION_NUMBER >= 0x10101000L)
+#if (OPENSSL_VERSION_NUMBER >= 0x10101000L) && !defined(LIBRESSL_VERSION_NUMBER)
 	else {
 		/*
 		 * If the server refused the early data, we have to send a
@@ -5425,7 +5436,7 @@ check_error:
 
 reneg_ok:
 
-#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC)
+#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC) && !defined(LIBRESSL_VERSION_NUMBER)
 	/* ASYNC engine API doesn't support moving read/write
 	 * buffers. So we disable ASYNC mode right after
 	 * the handshake to avoid buffer oveflows.
@@ -5521,7 +5532,7 @@ static size_t ssl_sock_to_buf(struct connection *conn,
 			continue;
 		}
 
-#if (OPENSSL_VERSION_NUMBER >= 0x10101000L)
+#if (OPENSSL_VERSION_NUMBER >= 0x10101000L) && !defined(LIBRESSL_VERSION_NUMBER)
 		if (conn->flags & CO_FL_EARLY_SSL_HS) {
 			size_t read_length;
 
@@ -5573,7 +5584,7 @@ static size_t ssl_sock_to_buf(struct connection *conn,
 				/* handshake is running, and it needs to enable write */
 				conn->flags |= CO_FL_SSL_WAIT_HS;
 				__conn_sock_want_send(conn);
-#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC)
+#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC) && !defined(LIBRESSL_VERSION_NUMBER)
 				/* Async mode can be re-enabled, because we're leaving data state.*/
 				if (global_ssl.async)
 					SSL_set_mode(conn->xprt_ctx, SSL_MODE_ASYNC);
@@ -5585,7 +5596,7 @@ static size_t ssl_sock_to_buf(struct connection *conn,
 					/* handshake is running, and it may need to re-enable read */
 					conn->flags |= CO_FL_SSL_WAIT_HS;
 					__conn_sock_want_recv(conn);
-#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC)
+#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC) && !defined(LIBRESSL_VERSION_NUMBER)
 					/* Async mode can be re-enabled, because we're leaving data state.*/
 					if (global_ssl.async)
 						SSL_set_mode(conn->xprt_ctx, SSL_MODE_ASYNC);
@@ -5682,7 +5693,7 @@ static size_t ssl_sock_from_buf(struct connection *con
 			conn->xprt_st |= SSL_SOCK_SEND_UNLIMITED;
 		}
 
-#if (OPENSSL_VERSION_NUMBER >= 0x10101000L)
+#if (OPENSSL_VERSION_NUMBER >= 0x10101000L) && !defined(LIBRESSL_VERSION_NUMBER)
 		if (!SSL_is_init_finished(conn->xprt_ctx)) {
 			unsigned int max_early;
 
@@ -5735,7 +5746,7 @@ static size_t ssl_sock_from_buf(struct connection *con
 					/* handshake is running, and it may need to re-enable write */
 					conn->flags |= CO_FL_SSL_WAIT_HS;
 					__conn_sock_want_send(conn);
-#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC)
+#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC) && !defined(LIBRESSL_VERSION_NUMBER)
 					/* Async mode can be re-enabled, because we're leaving data state.*/
 					if (global_ssl.async)
 						SSL_set_mode(conn->xprt_ctx, SSL_MODE_ASYNC);
@@ -5750,7 +5761,7 @@ static size_t ssl_sock_from_buf(struct connection *con
 				/* handshake is running, and it needs to enable read */
 				conn->flags |= CO_FL_SSL_WAIT_HS;
 				__conn_sock_want_recv(conn);
-#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC)
+#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC) && !defined(LIBRESSL_VERSION_NUMBER)
 				/* Async mode can be re-enabled, because we're leaving data state.*/
 				if (global_ssl.async)
 					SSL_set_mode(conn->xprt_ctx, SSL_MODE_ASYNC);
@@ -5776,7 +5787,7 @@ static size_t ssl_sock_from_buf(struct connection *con
 static void ssl_sock_close(struct connection *conn) {
 
 	if (conn->xprt_ctx) {
-#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC)
+#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC) && !defined(LIBRESSL_VERSION_NUMBER)
 		if (global_ssl.async) {
 			OSSL_ASYNC_FD all_fd[32], afd;
 			size_t num_all_fds = 0;
