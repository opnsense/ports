--- src/cli.c.orig	2019-05-11 03:44:42 UTC
+++ src/cli.c
@@ -939,7 +939,7 @@ static int cli_io_handler_show_fd(struct
 			     (fdt.iocb == poller_pipe_io_handler) ? "poller_pipe_io_handler" :
 			     (fdt.iocb == mworker_accept_wrapper) ? "mworker_accept_wrapper" :
 #ifdef USE_OPENSSL
-#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC)
+#if (OPENSSL_VERSION_NUMBER >= 0x1010000fL) && !defined(OPENSSL_NO_ASYNC) && !defined(LIBRESSL_VERSION_NUMBER)
 			     (fdt.iocb == ssl_async_fd_free) ? "ssl_async_fd_free" :
 			     (fdt.iocb == ssl_async_fd_handler) ? "ssl_async_fd_handler" :
 #endif
