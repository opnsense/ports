--- src/Mod/Part/App/LinePyImp.cpp.orig	2026-07-01 20:50:53 UTC
+++ src/Mod/Part/App/LinePyImp.cpp
@@ -83,7 +83,7 @@ int LinePy::PyInit(PyObject* args, PyObject* /*kwd*/)
             // Create line out of two points
             double distance = Base::Distance(v1, v2);
             if (distance < gp::Resolution()) {
-                Standard_Failure::Raise("Both points are equal");
+                throw Standard_Failure("Both points are equal");
             }
             GC_MakeLine ms(gp_Pnt(v1.x, v1.y, v1.z), gp_Pnt(v2.x, v2.y, v2.z));
             if (!ms.IsDone()) {
