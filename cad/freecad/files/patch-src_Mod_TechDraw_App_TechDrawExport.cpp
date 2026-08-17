--- src/Mod/TechDraw/App/TechDrawExport.cpp.orig	2026-07-02 14:27:52 UTC
+++ src/Mod/TechDraw/App/TechDrawExport.cpp
@@ -45,6 +45,7 @@
 # include <Standard_Version.hxx>
 # include <TColStd_Array1OfReal.hxx>
 # include <TopExp_Explorer.hxx>
+# include <TColgp_Array1OfPnt.hxx>
 # include <TopoDS.hxx>
 # include <TopoDS_Edge.hxx>
 # include <TopoDS_Shape.hxx>
@@ -290,7 +291,7 @@ void SVGOutput::printBezier(const BRepAdaptor_Curve& c
                 printBSpline(spline, id, out);
             }
             else {
-                Standard_Failure::Raise("do it the generic way");
+                throw Standard_Failure("do it the generic way");
             }
 
             return;
@@ -301,7 +302,7 @@ void SVGOutput::printBezier(const BRepAdaptor_Curve& c
         str << p1.X() << ", " << p1.Y();
         if (bezier->Degree() == 3) {
             if (poles != 4)
-                Standard_Failure::Raise("do it the generic way");
+                throw Standard_Failure("do it the generic way");
             gp_Pnt p2 = bezier->Pole(2);
             gp_Pnt p3 = bezier->Pole(3);
             gp_Pnt p4 = bezier->Pole(4);
@@ -312,7 +313,7 @@ void SVGOutput::printBezier(const BRepAdaptor_Curve& c
         }
         else if (bezier->Degree() == 2) {
             if (poles != 3)
-                Standard_Failure::Raise("do it the generic way");
+                throw Standard_Failure("do it the generic way");
             gp_Pnt p2 = bezier->Pole(2);
             gp_Pnt p3 = bezier->Pole(3);
             str << " Q"
@@ -321,12 +322,12 @@ void SVGOutput::printBezier(const BRepAdaptor_Curve& c
         }
         else if (bezier->Degree() == 1) {
             if (poles != 2)
-                Standard_Failure::Raise("do it the generic way");
+                throw Standard_Failure("do it the generic way");
             gp_Pnt p2 = bezier->Pole(2);
             str << " L" << p2.X() << ", " << p2.Y() << " ";
         }
         else {
-            Standard_Failure::Raise("do it the generic way");
+            throw Standard_Failure("do it the generic way");
         }
 
         str << "\" />";
@@ -367,7 +368,7 @@ void SVGOutput::printBSpline(const BRepAdaptor_Curve& 
             }
             if (bezier->Degree() == 3) {
                 if (poles != 4)
-                    Standard_Failure::Raise("do it the generic way");
+                    throw Standard_Failure("do it the generic way");
                 gp_Pnt p2 = bezier->Pole(2);
                 gp_Pnt p3 = bezier->Pole(3);
                 gp_Pnt p4 = bezier->Pole(4);
@@ -378,7 +379,7 @@ void SVGOutput::printBSpline(const BRepAdaptor_Curve& 
             }
             else if (bezier->Degree() == 2) {
                 if (poles != 3)
-                    Standard_Failure::Raise("do it the generic way");
+                    throw Standard_Failure("do it the generic way");
                 gp_Pnt p2 = bezier->Pole(2);
                 gp_Pnt p3 = bezier->Pole(3);
                 str << " Q"
@@ -387,12 +388,12 @@ void SVGOutput::printBSpline(const BRepAdaptor_Curve& 
             }
             else if (bezier->Degree() == 1) {
                 if (poles != 2)
-                    Standard_Failure::Raise("do it the generic way");
+                    throw Standard_Failure("do it the generic way");
                 gp_Pnt p2 = bezier->Pole(2);
                 str << " L" << p2.X() << ", " << p2.Y() << " ";
             }
             else {
-                Standard_Failure::Raise("do it the generic way");
+                throw Standard_Failure("do it the generic way");
             }
         }
 
