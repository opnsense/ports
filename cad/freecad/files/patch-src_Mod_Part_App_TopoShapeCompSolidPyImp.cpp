--- src/Mod/Part/App/TopoShapeCompSolidPyImp.cpp.orig	2026-07-01 20:50:53 UTC
+++ src/Mod/Part/App/TopoShapeCompSolidPyImp.cpp
@@ -95,7 +95,7 @@ PyObject* TopoShapeCompSolidPy::add(PyObject* args)
                 builder.Add(comp, ts.getShape());
             }
             else {
-                Standard_Failure::Raise("Cannot empty shape to compound solid");
+                throw Standard_Failure("Cannot empty shape to compound solid");
             }
         }
         auto& self = *getTopoShapePtr();
