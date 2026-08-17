--- setup.py.orig	2026-07-11 02:11:30 UTC
+++ setup.py
@@ -0,0 +1,11 @@
+from setuptools import Extension, find_packages, setup
+
+setup(
+    name="crosshair-tool",
+    ext_modules=[
+        Extension(
+            "_crosshair_tracers",
+            sources=["crosshair/_tracers.c"],
+        ),
+    ],
+)
