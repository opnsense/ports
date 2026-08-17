--- src/Mod/Part/App/FaceMakerCheese.cpp.orig	2026-07-01 20:50:53 UTC
+++ src/Mod/Part/App/FaceMakerCheese.cpp
@@ -88,7 +88,7 @@ TopoDS_Face FaceMakerCheese::validateFace(const TopoDS
             TopoDS_Face fixedFace = TopoDS::Face(fix.Shape());
             aChecker.Init(fixedFace);
             if (!aChecker.IsValid()) {
-                Standard_Failure::Raise("Failed to validate broken face");
+                throw Standard_Failure("Failed to validate broken face");
             }
             return fixedFace;
         }
@@ -132,7 +132,7 @@ bool FaceMakerCheese::isInside(const TopoDS_Wire& wire
 
     BRepBuilderAPI_MakeFace mkFace(wire1);
     if (!mkFace.IsDone()) {
-        Standard_Failure::Raise("Failed to create a face from wire in sketch");
+        throw Standard_Failure("Failed to create a face from wire in sketch");
     }
     TopoDS_Face face = validateFace(mkFace.Face());
     BRepAdaptor_Surface adapt(face);
