--- src/vendor/libgit2-sys/libgit2/src/openssl_stream.h.orig	2018-03-25 15:53:19 UTC
+++ src/vendor/libgit2-sys/libgit2/src/openssl_stream.h
@@ -27,7 +27,8 @@ extern int git_openssl_stream_new(git_stream **out, co
 
 
 
-# if OPENSSL_VERSION_NUMBER < 0x10100000L || defined(LIBRESSL_VERSION_NUMBER)
+# if OPENSSL_VERSION_NUMBER < 0x10100000L || \
+     (defined(LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER < 0x20700000L)
 
 GIT_INLINE(BIO_METHOD*) BIO_meth_new(int type, const char *name)
 {
