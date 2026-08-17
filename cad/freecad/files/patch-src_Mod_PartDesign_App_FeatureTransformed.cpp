--- src/Mod/PartDesign/App/FeatureTransformed.cpp.orig	2026-07-02 13:09:26 UTC
+++ src/Mod/PartDesign/App/FeatureTransformed.cpp
@@ -445,7 +445,7 @@ TopoDS_Shape Transformed::getRemainingSolids(const Top
     builder.MakeCompound(compShape);
 
     if (shape.IsNull()) {
-        Standard_Failure::Raise("Shape is null");
+        throw Standard_Failure("Shape is null");
     }
     TopExp_Explorer xp;
     xp.Init(shape, TopAbs_SOLID);
