--- src/Mod/Part/App/GeometrySurfacePyImp.cpp.orig	2026-07-01 20:30:18 UTC
+++ src/Mod/Part/App/GeometrySurfacePyImp.cpp
@@ -835,7 +835,7 @@ PyObject* GeometrySurfacePy::toBSpline(PyObject* args,
             return new BSplineSurfacePy(new GeomBSplineSurface(cvt.Surface()));
         }
         else {
-            Standard_Failure::Raise("Cannot convert to B-spline surface");
+            throw Standard_Failure("Cannot convert to B-spline surface");
         }
     }
     catch (Standard_Failure& e) {
