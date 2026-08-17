-- Add FreeBSD to the list of supported platforms and fix the path to the
-- SWIG-generated nlopt.py file. CMake places it directly in
-- extern/nlopt/src/swig, not in a python/ subdirectory.
--- extensions.py.orig	2026-07-17 06:44:12 UTC
+++ extensions.py
@@ -26,7 +26,7 @@ class NLOptBuild(build_ext):
         except OSError:
             raise RuntimeError("CMake must be installed")
 
-        if platform.system() not in ("Windows", "Linux", "Darwin"):
+        if platform.system() not in ("Windows", "Linux", "Darwin", "FreeBSD"):
             raise RuntimeError(f"Unsupported os: {platform.system()}")
 
         for ext in self.extensions:
@@ -86,7 +86,7 @@ class NLOptBuild(build_ext):
         )
 
         # Copy over the important bits
-        nlopt_py = build_dir / "extern" / "nlopt" / "src" / "swig" / "python" / "nlopt.py"
+        nlopt_py = build_dir / "extern" / "nlopt" / "src" / "swig" / "nlopt.py"
 
         logging.info(
             f"Ext Dir - {ext_dir}\n"
