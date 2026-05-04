--- setup.py.orig	2026-04-06 20:05:23 UTC
+++ setup.py
@@ -77,7 +77,7 @@ def _setup_install_requires() -> List:
     )
 
 def _setup_install_requires() -> List:
-    return ["torch>=1.7.0", "transformers<5.0.0", "pydantic>=2.0", "loguru"]
+    return ["torch>=1.7.0", "transformers>=4.0.0", "pydantic>=2.0", "loguru"]
 
 def _setup_extras() -> Dict:
     return {
