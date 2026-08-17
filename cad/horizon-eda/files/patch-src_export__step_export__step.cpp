--- src/export_step/export_step.cpp.orig	2025-12-03 22:56:50 UTC
+++ src/export_step/export_step.cpp
@@ -27,7 +27,7 @@
 #include <APIHeaderSection_MakeHeader.hxx>
 #include <TCollection_ExtendedString.hxx>
 #include <TDataStd_Name.hxx>
-#include <TDF_LabelSequence.hxx>
+#include <NCollection_Sequence.hxx>
 #include <TDF_ChildIterator.hxx>
 #include <TopExp_Explorer.hxx>
 #include <XCAFDoc_DocumentTool.hxx>
@@ -97,13 +97,13 @@ class CanvasHole : public Canvas { (public)
 
 class CanvasHole : public Canvas {
 public:
-    CanvasHole(TopTools_ListOfShape &cs, uint64_t mdia = 0) : cutouts(cs), min_diameter(mdia)
+    CanvasHole(NCollection_List<TopoDS_Shape> &cs, uint64_t mdia = 0) : cutouts(cs), min_diameter(mdia)
     {
         img_mode = true;
     }
 
 private:
-    TopTools_ListOfShape &cutouts;
+    NCollection_List<TopoDS_Shape> &cutouts;
     uint64_t min_diameter;
 
     void img_hole(const class Hole &hole) override
@@ -302,7 +302,7 @@ static TDF_Label transferModel(Handle(TDocStd_Document
     Handle(XCAFDoc_ShapeTool) s_assy = XCAFDoc_DocumentTool::ShapeTool(source->Main());
 
     // retrieve all free shapes within the assembly
-    TDF_LabelSequence frshapes;
+    NCollection_Sequence<TDF_Label> frshapes;
     s_assy->GetFreeShapes(frshapes);
 
     // d_assy = shape tool for the destination
@@ -431,7 +431,7 @@ void export_step(const std::string &filename, const Bo
         auto outline = brd.get_outline();
         if (outline.outline.vertices.size()) { // board has valid outline
             progress_cb("Board cutouts…");
-            TopTools_ListOfShape cutouts;
+            NCollection_List<TopoDS_Shape> cutouts;
 
             progress_cb("Holes…");
             {
@@ -451,12 +451,12 @@ void export_step(const std::string &filename, const Bo
                 if (!cutouts.IsEmpty()) {
                     BRepAlgoAPI_Cut builder;
 
-                    TopTools_ListOfShape board_shapes;
+                    NCollection_List<TopoDS_Shape> board_shapes;
                     board_shapes.Append(board_face);
 
                     builder.SetArguments(board_shapes);
                     builder.SetTools(cutouts);
-                    builder.SetRunParallel(Standard_True);
+                    builder.SetRunParallel(true);
                     builder.Build();
 
                     board = BRepPrimAPI_MakePrism(builder.Shape(), v);
@@ -546,9 +546,9 @@ void export_step(const std::string &filename, const Bo
         assy->UpdateAssemblies();
 #endif
         STEPCAFControl_Writer writer;
-        writer.SetColorMode(Standard_True);
-        writer.SetNameMode(Standard_True);
-        if (Standard_False == writer.Transfer(doc, STEPControl_AsIs)) {
+        writer.SetColorMode(true);
+        writer.SetNameMode(true);
+        if (false == writer.Transfer(doc, STEPControl_AsIs)) {
             throw std::runtime_error("transfer error");
         }
 
@@ -559,7 +559,7 @@ void export_step(const std::string &filename, const Bo
         hdr.SetOriginatingSystem(new TCollection_HAsciiString("horizon EDA"));
         hdr.SetDescriptionValue(1, new TCollection_HAsciiString("Electronic assembly"));
 
-        if (Standard_False == writer.Write(filename.c_str()))
+        if (false == writer.Write(filename.c_str()))
             throw std::runtime_error("write error");
 
         progress_cb("Done");
