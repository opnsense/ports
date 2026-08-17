--- src/import_step/step_importer.cpp.orig	2025-12-03 22:56:50 UTC
+++ src/import_step/step_importer.cpp
@@ -30,7 +30,7 @@
 
 #include <Poly_PolygonOnTriangulation.hxx>
 #include <Poly_Triangulation.hxx>
-#include <TShort_Array1OfShortReal.hxx>
+#include <NCollection_Array1.hxx>
 #include <Precision.hxx>
 #include <Quantity_Color.hxx>
 #include <BRepTools_WireExplorer.hxx>
@@ -38,7 +38,7 @@
 #include <BRepAdaptor_Curve.hxx>
 
 #include <TDF_ChildIterator.hxx>
-#include <TDF_LabelSequence.hxx>
+#include <NCollection_Sequence.hxx>
 #include <Poly.hxx>
 #include <gp_Circ.hxx>
 
@@ -143,7 +143,7 @@ bool STEPImporter::processFace(const TopoDS_Face &face
 
 bool STEPImporter::processFace(const TopoDS_Face &face, Quantity_Color *color, const glm::dmat4 &mat)
 {
-    if (Standard_True == face.IsNull())
+    if (face.IsNull())
         return false;
 
     {
@@ -163,18 +163,18 @@ bool STEPImporter::processFace(const TopoDS_Face &face
     //	bool useBothSides = false;
 
     TopLoc_Location loc;
-    Standard_Boolean isTessellate(Standard_False);
+    bool isTessellate = false;
     Handle(Poly_Triangulation) triangulation = BRep_Tool::Triangulation(face, loc);
 
     if (triangulation.IsNull() || triangulation->Deflection() > USER_PREC + Precision::Confusion())
-        isTessellate = Standard_True;
+        isTessellate = true;
 
     if (isTessellate) {
-        BRepMesh_IncrementalMesh IM(face, USER_PREC, Standard_False, USER_ANGLE);
+        BRepMesh_IncrementalMesh IM(face, USER_PREC, false, USER_ANGLE);
         triangulation = BRep_Tool::Triangulation(face, loc);
     }
 
-    if (triangulation.IsNull() == Standard_True)
+    if (triangulation.IsNull())
         return false;
 
     Quantity_Color lcolor;
@@ -192,13 +192,6 @@ bool STEPImporter::processFace(const TopoDS_Face &face
 
     Poly::ComputeNormals(triangulation);
 
-#ifndef HORIZON_NEW_OCC
-    const TColgp_Array1OfPnt &arrPolyNodes = triangulation->Nodes();
-    const Poly_Array1OfTriangle &arrTriangles = triangulation->Triangles();
-    const TShort_Array1OfShortReal &arrNormals = triangulation->Normals();
-#endif
-
-
     result->faces.emplace_back();
     auto &face_out = result->faces.back();
     if (color) {
@@ -213,11 +206,7 @@ bool STEPImporter::processFace(const TopoDS_Face &face
 
     std::map<Vertex, std::vector<size_t>> pts_map;
     for (int i = 1; i <= triangulation->NbNodes(); i++) {
-#ifdef HORIZON_NEW_OCC
         gp_XYZ v(triangulation->Node(i).Coord());
-#else
-        gp_XYZ v(arrPolyNodes(i).Coord());
-#endif
         const glm::vec4 vg(v.X(), v.Y(), v.Z(), 1);
         const auto vt = mat * vg;
         const Vertex vertex(vt.x, vt.y, vt.z);
@@ -227,16 +216,8 @@ bool STEPImporter::processFace(const TopoDS_Face &face
 
     face_out.normals.reserve(triangulation->NbNodes());
     for (int i = 1; i <= triangulation->NbNodes(); i++) {
-#ifdef HORIZON_NEW_OCC
         const auto n = triangulation->Normal(i);
         glm::vec4 vg(n.X(), n.Y(), n.Z(), 0);
-#else
-        auto offset = (i - 1) * 3 + 1;
-        auto x = arrNormals(offset + 0);
-        auto y = arrNormals(offset + 1);
-        auto z = arrNormals(offset + 2);
-        glm::vec4 vg(x, y, z, 0);
-#endif
         auto vt = mat * vg;
         vt /= vt.length();
         face_out.normals.emplace_back(vt.x, vt.y, vt.z);
@@ -259,11 +240,7 @@ bool STEPImporter::processFace(const TopoDS_Face &face
     face_out.triangle_indices.reserve(triangulation->NbTriangles());
     for (int i = 1; i <= triangulation->NbTriangles(); i++) {
         int a, b, c;
-#ifdef HORIZON_NEW_OCC
         triangulation->Triangle(i).Get(a, b, c);
-#else
-        arrTriangles(i).Get(a, b, c);
-#endif
         face_out.triangle_indices.emplace_back(a - 1, b - 1, c - 1);
     }
 
@@ -306,7 +283,7 @@ bool STEPImporter::processSolid(const TopoDS_Shape &sh
 
 bool STEPImporter::processSolid(const TopoDS_Shape &shape, const glm::dmat4 &mat_in)
 {
-    TDF_Label label = m_assy->FindShape(shape, Standard_False);
+    TDF_Label label = m_assy->FindShape(shape, false);
     bool ret = false;
 
     hasSolid = true;
@@ -328,7 +305,7 @@ bool STEPImporter::processSolid(const TopoDS_Shape &sh
     auto mat = mat_in * glm::translate(glm::dvec3(coord.X(), coord.Y(), coord.Z()));
 
     gp_XYZ axis;
-    Standard_Real angle;
+    double angle;
 
     if (T.GetRotation(axis, angle)) {
         glm::dvec3 gaxis(axis.X(), axis.Y(), axis.Z());
@@ -358,7 +335,7 @@ bool STEPImporter::processComp(const TopoDS_Shape &sha
     auto mat = mat_in * glm::translate(glm::dvec3(coord.X(), coord.Y(), coord.Z()));
 
     gp_XYZ axis;
-    Standard_Real angle;
+    double angle;
 
     if (T.GetRotation(axis, angle)) {
         glm::dvec3 gaxis(axis.X(), axis.Y(), axis.Z());
@@ -442,7 +419,7 @@ Result STEPImporter::get_faces_and_points()
     Result res;
     result = &res;
 
-    TDF_LabelSequence frshapes;
+    NCollection_Sequence<TDF_Label> frshapes;
     m_assy->GetFreeShapes(frshapes);
 
     int nshapes = frshapes.Length();
@@ -461,7 +438,7 @@ std::vector<TopoDS_Shape> STEPImporter::get_shapes()
 std::vector<TopoDS_Shape> STEPImporter::get_shapes()
 {
     std::vector<TopoDS_Shape> r;
-    TDF_LabelSequence frshapes;
+    NCollection_Sequence<TDF_Label> frshapes;
     m_assy->GetFreeShapes(frshapes);
 
     int nshapes = frshapes.Length();
