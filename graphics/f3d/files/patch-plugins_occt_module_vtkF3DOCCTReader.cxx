--- plugins/occt/module/vtkF3DOCCTReader.cxx.orig	2026-04-05 11:41:50 UTC
+++ plugins/occt/module/vtkF3DOCCTReader.cxx
@@ -20,9 +20,7 @@
 #include <Quantity_Color.hxx>
 #include <STEPControl_Reader.hxx>
 #include <Standard_Handle.hxx>
-#include <Standard_PrimitiveTypes.hxx>
 #include <Storage_StreamTypeMismatchError.hxx>
-#include <TColgp_Array1OfVec.hxx>
 #include <TopExp_Explorer.hxx>
 #include <TopoDS.hxx>
 #include <TopoDS_Edge.hxx>
@@ -81,7 +79,7 @@ class vtkF3DOCCTReader::vtkInternals
 class vtkF3DOCCTReader::vtkInternals
 {
 #if F3D_PLUGIN_OCCT_XCAF
-  using StyleMap = XCAFPrs_IndexedDataMapOfShapeStyle;
+  using StyleMap = NCollection_IndexedDataMap<TopoDS_Shape, XCAFPrs_Style, TopTools_ShapeMapHasher>;
 #endif
 
 public:
@@ -113,7 +111,7 @@ class vtkF3DOCCTReader::vtkInternals
     vtkNew<vtkCellArray> trianglesCells;
     vtkNew<vtkCellArray> linesCells;
 
-    Standard_Integer shift = 0;
+    int shift = 0;
 
 #if F3D_PLUGIN_OCCT_XCAF
     const StyleMap inheritedStyles = this->CollectInheritedStyles(label, shape);
@@ -121,7 +119,7 @@ class vtkF3DOCCTReader::vtkInternals
 
     /* Mesh the whole shape. This only affect faces, edges have to be handled separately. */
     BRepMesh_IncrementalMesh(shape, this->Parent->GetLinearDeflection(),
-      this->Parent->GetRelativeDeflection(), this->Parent->GetAngularDeflection(), Standard_True);
+      this->Parent->GetRelativeDeflection(), this->Parent->GetAngularDeflection(), true);
 
     if (this->Parent->GetReadWire())
     {
@@ -138,8 +136,7 @@ class vtkF3DOCCTReader::vtkInternals
           edges.push_back(edge);
         }
         BRepMesh_IncrementalMesh(compound, this->Parent->GetLinearDeflection(),
-          this->Parent->GetRelativeDeflection(), this->Parent->GetAngularDeflection(),
-          Standard_True);
+          this->Parent->GetRelativeDeflection(), this->Parent->GetAngularDeflection(), true);
       }
 
       // Add all edges to polydata
@@ -153,11 +150,11 @@ class vtkF3DOCCTReader::vtkInternals
           continue;
         }
 
-        Standard_Integer nbV = poly->NbNodes();
+        int nbV = poly->NbNodes();
 
         // Points
-        const TColgp_Array1OfPnt& aNodes = poly->Nodes();
-        for (Standard_Integer i = 1; i <= nbV; i++)
+        const NCollection_Array1<gp_Pnt>& aNodes = poly->Nodes();
+        for (int i = 1; i <= nbV; i++)
         {
           gp_Pnt pt = aNodes(i).Transformed(location);
           points->InsertNextPoint(pt.X(), pt.Y(), pt.Z());
@@ -213,11 +210,11 @@ class vtkF3DOCCTReader::vtkInternals
       Poly::ComputeNormals(poly);
       TopAbs_Orientation faceOrientation = face.Orientation();
 
-      Standard_Integer nbT = poly->NbTriangles();
-      Standard_Integer nbV = poly->NbNodes();
+      int nbT = poly->NbTriangles();
+      int nbV = poly->NbNodes();
 
       // Points
-      for (Standard_Integer i = 1; i <= nbV; i++)
+      for (int i = 1; i <= nbV; i++)
       {
         gp_Pnt pt = poly->Node(i).Transformed(location);
         points->InsertNextPoint(pt.X(), pt.Y(), pt.Z());
@@ -226,7 +223,7 @@ class vtkF3DOCCTReader::vtkInternals
       // Normals
       if (poly->HasNormals())
       {
-        for (Standard_Integer i = 1; i <= nbV; i++)
+        for (int i = 1; i <= nbV; i++)
         {
           gp_Dir n = poly->Normal(i);
           float fn[3] = { static_cast<float>(n.X()), static_cast<float>(n.Y()),
@@ -242,7 +239,7 @@ class vtkF3DOCCTReader::vtkInternals
       {
         // just in case a face does not have normals, add a dummy normal
         float fn[3] = { 0.0, 0.0, 1.0 };
-        for (Standard_Integer i = 1; i <= nbV; i++)
+        for (int i = 1; i <= nbV; i++)
         {
           normals->InsertNextTypedTuple(fn);
         }
@@ -251,7 +248,7 @@ class vtkF3DOCCTReader::vtkInternals
       // UVs
       if (poly->HasUVNodes())
       {
-        for (Standard_Integer i = 1; i <= nbV; i++)
+        for (int i = 1; i <= nbV; i++)
         {
           gp_Pnt2d uv = poly->UVNode(i);
           float fn[2] = { static_cast<float>(uv.X()), static_cast<float>(uv.Y()) };
@@ -572,7 +569,7 @@ class ProgressIndicator : public Message_ProgressIndic
   }
 
 protected:
-  void Show(const Message_ProgressScope&, const Standard_Boolean) override
+  void Show(const Message_ProgressScope&, bool) override
   {
     double currentPosition = this->GetPosition();
     if (currentPosition - this->LastPosition > 0.01)
@@ -763,12 +760,12 @@ int vtkF3DOCCTReader::RequestData(
 
   this->Internals->ShapeTool = XCAFDoc_DocumentTool::ShapeTool(doc->Main());
 
-  TDF_LabelSequence topLevelShapes;
+  NCollection_Sequence<TDF_Label> topLevelShapes;
 
   // create polydata leaves
   this->Internals->ShapeTool->GetShapes(topLevelShapes);
 
-  for (Standard_Integer iLabel = 1; iLabel <= topLevelShapes.Length(); ++iLabel)
+  for (int iLabel = 1; iLabel <= topLevelShapes.Length(); ++iLabel)
   {
     TDF_Label label = topLevelShapes.Value(iLabel);
 
@@ -787,7 +784,7 @@ int vtkF3DOCCTReader::RequestData(
 
   vtkNew<vtkMatrix4x4> mat;
   mat->Identity();
-  for (Standard_Integer iLabel = 1; iLabel <= topLevelShapes.Length(); ++iLabel)
+  for (int iLabel = 1; iLabel <= topLevelShapes.Length(); ++iLabel)
   {
     this->Internals->AddLabel(topLevelShapes.Value(iLabel), mat, output);
   }
@@ -828,7 +825,7 @@ int vtkF3DOCCTReader::RequestData(
     ProgressIndicator pi(this);
     reader->TransferRoots(pi.Start());
 
-    Standard_Integer nbShapes = reader->NbShapes();
+    int nbShapes = reader->NbShapes();
 
     output->SetNumberOfBlocks(nbShapes);
 
