--- src/Mod/Part/App/modelRefine.cpp.orig	2026-07-01 20:30:18 UTC
+++ src/Mod/Part/App/modelRefine.cpp
@@ -62,10 +62,11 @@
 #include <TopoDS_Shape.hxx>
 #include <TopExp.hxx>
 #include <TopExp_Explorer.hxx>
-#include <TopTools_DataMapIteratorOfDataMapOfIntegerListOfShape.hxx>
-#include <TopTools_DataMapIteratorOfDataMapOfShapeShape.hxx>
-#include <TopTools_ListIteratorOfListOfShape.hxx>
 #include <TopTools_ListOfShape.hxx>
+#include <TopTools_IndexedMapOfShape.hxx>
+#include <TopTools_DataMapOfShapeShape.hxx>
+#include <TopTools_DataMapOfIntegerListOfShape.hxx>
+#include <TopTools_DataMapOfIntegerShape.hxx>
 
 #include <Base/Console.h>
 
@@ -1316,7 +1317,7 @@ void Part::BRepBuilderAPI_RefineModel::Build()
 #endif
 {
     if (myShape.IsNull()) {
-        Standard_Failure::Raise("Cannot remove splitter from empty shape");
+        throw Standard_Failure("Cannot remove splitter from empty shape");
     }
 
     if (myShape.ShapeType() == TopAbs_SOLID) {
@@ -1337,7 +1338,7 @@ void Part::BRepBuilderAPI_RefineModel::Build()
                 }
             }
             else {
-                Standard_Failure::Raise("Removing splitter failed");
+                throw Standard_Failure("Removing splitter failed");
             }
         }
         myShape = mkSolid.Solid();
@@ -1351,7 +1352,7 @@ void Part::BRepBuilderAPI_RefineModel::Build()
             LogModifications(uniter);
         }
         else {
-            Standard_Failure::Raise("Removing splitter failed");
+            throw Standard_Failure("Removing splitter failed");
         }
     }
     else if (myShape.ShapeType() == TopAbs_COMPOUND) {
