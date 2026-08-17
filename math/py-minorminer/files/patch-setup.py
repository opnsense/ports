-- Add missing commas between include_dirs entries for the subgraph extension.
-- Without the commas Python concatenates the strings into a single invalid
-- path, so the glasgow-subgraph-solver headers cannot be found.

--- setup.py.orig	2026-07-20 00:04:15 UTC
+++ setup.py
@@ -122,8 +122,8 @@ extensions = [
         name="minorminer.subgraph",
         sources=["./minorminer/subgraph.pyx"] + glasgow_cc,
         include_dirs=['', './include', './external',
-                      './external/glasgow-subgraph-solver'
-                      './external/glasgow-subgraph-solver/src'
+                      './external/glasgow-subgraph-solver',
+                      './external/glasgow-subgraph-solver/src',
                       './external/glasgow-subgraph-solver/gss'],
         library_dirs=['./include', './external', './external/glasgow-subgraph-solver/gss/formats'],
         language='c++',
