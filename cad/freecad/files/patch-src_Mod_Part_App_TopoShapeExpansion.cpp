--- src/Mod/Part/App/TopoShapeExpansion.cpp.orig	2026-07-01 20:30:18 UTC
+++ src/Mod/Part/App/TopoShapeExpansion.cpp
@@ -4982,9 +4982,17 @@ TopoShape& TopoShape::makeElementBSplineFace(
         auto e4 = mk4.Edge();
 
         ShapeMapper mapper;
-        mapper.populate(MappingStatus::Modified, e, {e1, e2, e3, e4});
-        mapper.populate(MappingStatus::Generated, v, {TopExp::FirstVertex(e1)});
-        mapper.populate(MappingStatus::Generated, v, {TopExp::LastVertex(e4)});
+        mapper.populate(MappingStatus::Modified, e, std::vector<Part::TopoShape> {e1, e2, e3, e4});
+        mapper.populate(
+            MappingStatus::Generated,
+            v,
+            std::vector<Part::TopoShape> {TopExp::FirstVertex(e1)}
+        );
+        mapper.populate(
+            MappingStatus::Generated,
+            v,
+            std::vector<Part::TopoShape> {TopExp::LastVertex(e4)}
+        );
 
         BRep_Builder builder;
         TopoDS_Compound comp;
@@ -5089,7 +5097,7 @@ TopoShape& TopoShape::makeElementBSplineFace(
                     Handle(Geom_BSplineCurve) spline
                         = scc.ConvertToBSpline(c_geom, u1, u2, Precision::Confusion());
                     if (spline.IsNull()) {
-                        Standard_Failure::Raise(
+                        throw Standard_Failure(
                             "A curve was not a B-spline and could not be converted into one."
                         );
                     }
