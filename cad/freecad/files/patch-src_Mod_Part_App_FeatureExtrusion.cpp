--- src/Mod/Part/App/FeatureExtrusion.cpp.orig	2026-07-01 20:50:53 UTC
+++ src/Mod/Part/App/FeatureExtrusion.cpp
@@ -349,7 +349,7 @@ void Extrusion::extrudeShape(TopoShape& result, const 
         std::vector<TopoShape> drafts;
         ExtrusionHelper::makeElementDraft(params, myShape, drafts, result.Hasher);
         if (drafts.empty()) {
-            Standard_Failure::Raise("Drafting shape failed");
+            throw Standard_Failure("Drafting shape failed");
         }
         else {
             result.makeElementCompound(
@@ -362,7 +362,7 @@ void Extrusion::extrudeShape(TopoShape& result, const 
     else {
         // Regular (non-tapered) extrusion!
         if (source.isNull()) {
-            Standard_Failure::Raise("Cannot extrude empty shape");
+            throw Standard_Failure("Cannot extrude empty shape");
         }
 
         // apply reverse part of extrusion by shifting the source shape
