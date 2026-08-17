--- src/Mod/Part/App/Geom2d/Line2dPyImp.cpp.orig	2026-07-01 20:30:18 UTC
+++ src/Mod/Part/App/Geom2d/Line2dPyImp.cpp
@@ -93,7 +93,7 @@ int Line2dPy::PyInit(PyObject* args, PyObject* /*kwd*/
             // Create line out of two points
             double distance = (v1 - v2).Length();
             if (distance < gp::Resolution()) {
-                Standard_Failure::Raise("Both points are equal");
+                throw Standard_Failure("Both points are equal");
             }
             GCE2d_MakeLine ms(gp_Pnt2d(v1.x, v1.y), gp_Pnt2d(v2.x, v2.y));
             if (!ms.IsDone()) {
