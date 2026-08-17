--- ElmerGUI/Application/cad/cadview.cpp.orig	2026-04-29 13:04:57 UTC
+++ ElmerGUI/Application/cad/cadview.cpp
@@ -687,7 +687,9 @@ TopoDS_Shape CadView::readStep(QString fileName) {
 
 TopoDS_Shape CadView::readStep(QString fileName) {
   TopoDS_Shape shape;
-  Handle_TopTools_HSequenceOfShape shapes;
+  /* Patch from upstream 827b6124abc626c85daec970ca3920868709a230 */
+  /* Handle_TopTools_HSequenceOfShape shapes; */
+  Handle(TopTools_HSequenceOfShape) shapes;
   STEPControl_Reader stepReader;
   IFSelect_ReturnStatus status;
 
