-- Fix build on FreeBSD 16 where xdrproc_t changed from a variadic to a
-- two-argument function pointer type, so calling it with three arguments fails.

--- src/utils/xdr_cxx.C.orig	2026-07-19 04:45:48 UTC
+++ src/utils/xdr_cxx.C
@@ -28,6 +28,9 @@
 #include "libmesh/xdr_cxx.h"
 #include "libmesh/libmesh_logging.h"
 #ifdef LIBMESH_HAVE_GZSTREAM
+#ifdef __FreeBSD__
+# include <sys/param.h>
+#endif
 # include "libmesh/ignore_warnings.h" // shadowing in gzstream.h
 # include "gzstream.h" // For reading/writing compressed streams
 # include "libmesh/restore_warnings.h"
@@ -484,7 +487,12 @@ bool xdr_translate(XDR * x, T & a)
 template <typename T>
 bool xdr_translate(XDR * x, T & a)
 {
+#if defined(__FreeBSD__) && __FreeBSD_version >= 1600000
+  // FreeBSD 16 changed xdrproc_t to a two-argument function pointer.
+  return (xdr_translator<T>())(x, &a);
+#else
   return (xdr_translator<T>())(x, &a, 0);
+#endif
 }

 template <>
