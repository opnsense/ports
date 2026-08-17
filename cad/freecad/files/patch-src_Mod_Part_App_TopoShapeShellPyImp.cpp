--- src/Mod/Part/App/TopoShapeShellPyImp.cpp.orig	2026-07-01 20:50:53 UTC
+++ src/Mod/Part/App/TopoShapeShellPyImp.cpp
@@ -120,7 +120,7 @@ PyObject* TopoShapeShellPy::add(PyObject* args)
             }
         }
         else {
-            Standard_Failure::Raise("cannot add empty shape");
+            throw Standard_Failure("cannot add empty shape");
         }
     }
     catch (Standard_Failure& e) {
