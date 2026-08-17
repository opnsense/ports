--- src/Mod/Inspection/App/InspectionFeature.cpp.orig	2026-07-02 13:09:26 UTC
+++ src/Mod/Inspection/App/InspectionFeature.cpp
@@ -32,6 +32,7 @@
 #include <BRepGProp_Face.hxx>
 #include <TopExp.hxx>
 #include <TopoDS.hxx>
+#include <TopTools_IndexedMapOfShape.hxx>
 #include <gp_Pnt.hxx>
 
 #include <QEventLoop>
