--- torch/_inductor/ir.py.orig	2026-04-19 02:49:11 UTC
+++ torch/_inductor/ir.py
@@ -133,7 +133,7 @@ try:
 
     triton_version = triton.__version__
     has_triton = True
-except ImportError:
+except (ImportError, AttributeError):
     triton_version = None
     has_triton = False
 
