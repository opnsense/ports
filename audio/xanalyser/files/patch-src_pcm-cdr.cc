--- src/pcm-cdr.cc.orig	Mon Apr 16 17:23:03 2007
+++ src/pcm-cdr.cc	Mon Apr 16 17:25:16 2007
@@ -14,6 +14,16 @@
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <iostream>
+#ifdef __NetBSD__
+#  include <machine/byte_swap.h>
+#elif __FreeBSD__
+#  include <sys/endian.h>
+#  define	__BYTE_ORDER	_BYTE_ORDER
+#  define	__LITTLE_ENDIAN	_LITTLE_ENDIAN
+#  define	__BIG_ENDIAN	_BIG_ENDIAN
+#else
+#  include <byteswap.h>
+#endif
 
 using std::cerr;
 
