--- src/Mod/Part/App/AppPartPy.cpp.orig	2026-07-01 20:30:18 UTC
+++ src/Mod/Part/App/AppPartPy.cpp
@@ -67,7 +67,7 @@
 #include <TopoDS_Face.hxx>
 #include <TopoDS_Shell.hxx>
 #include <TopoDS_Solid.hxx>
-#include <TopTools_ListIteratorOfListOfShape.hxx>
+#include <TopTools_ListOfShape.hxx>
 
 #include <BRepFill_Generator.hxx>
 
@@ -1633,7 +1633,7 @@ class Module: public Py::ExtensionModule<Module> (priv
             }
 
             if (!mkPoly.IsDone()) {
-                Standard_Failure::Raise(
+                throw Standard_Failure(
                     "Cannot create polygon because less than two vertices are given"
                 );
             }
