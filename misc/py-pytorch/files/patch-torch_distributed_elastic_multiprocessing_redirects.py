--- torch/distributed/elastic/multiprocessing/redirects.py.orig	2026-04-19 02:32:30 UTC
+++ torch/distributed/elastic/multiprocessing/redirects.py
@@ -31,7 +31,9 @@ def get_libc():
         )
         return None
     else:
-        return ctypes.CDLL("libc.so.6")
+        import ctypes.util
+        libc_name = ctypes.util.find_library("c") or "libc.so.6"
+        return ctypes.CDLL(libc_name)
 
 
 libc = get_libc()
