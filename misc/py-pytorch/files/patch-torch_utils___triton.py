--- torch/utils/_triton.py.orig	2026-04-19 02:46:16 UTC
+++ torch/utils/_triton.py
@@ -7,9 +7,10 @@ def has_triton_package() -> bool:
 def has_triton_package() -> bool:
     try:
         import triton  # noqa: F401
+        import triton.language  # noqa: F401  # Verify it's a real install, not a namespace pkg
 
         return True
-    except ImportError:
+    except (ImportError, AttributeError):
         return False
 
 
