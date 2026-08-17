--- src/occt_wrapper/OCCTWrapper.cpp.orig	2026-05-19 09:09:17 UTC
+++ src/occt_wrapper/OCCTWrapper.cpp
@@ -15,6 +15,7 @@
 #include "XCAFDoc_DocumentTool.hxx"
 #include "XCAFDoc_ShapeTool.hxx"
 #include "XCAFApp_Application.hxx"
+#include "TDF_LabelSequence.hxx"
 #include "TopoDS_Builder.hxx"
 #include "TopoDS.hxx"
 #include "TDataStd_Name.hxx"
@@ -149,13 +150,13 @@ try {
             for (Standard_Integer aNodeIter = 1; aNodeIter <= aTriangulation->NbNodes(); ++aNodeIter) {
                 gp_Pnt aPnt = aTriangulation->Node(aNodeIter);
                 aPnt.Transform(aTrsf);
-                vertices.emplace_back(std::move(Vec3f(float(aPnt.X()), float(aPnt.Y()), float(aPnt.Z()))));
+                vertices.emplace_back(Vec3f(float(aPnt.X()), float(aPnt.Y()), float(aPnt.Z())));
             }
 
             // Now copy the facets.
             const TopAbs_Orientation anOrientation = anExpSF.Current().Orientation();
             for (Standard_Integer aTriIter = 1; aTriIter <= aTriangulation->NbTriangles(); ++aTriIter) {
-                const int aTriangleOffet = int(facets.size());
+                // const int aTriangleOffet = int(facets.size());	// Unused variable
                 Poly_Triangle aTri = aTriangulation->Triangle(aTriIter);
 
                 Standard_Integer anId[3];
