--- src/Mod/Part/App/BRepFeat/MakePrismPyImp.cpp.orig	2026-07-01 20:50:53 UTC
+++ src/Mod/Part/App/BRepFeat/MakePrismPyImp.cpp
@@ -27,6 +27,7 @@
 #include <TopoDS.hxx>
 #include <TopoDS_Edge.hxx>
 #include <TopoDS_Face.hxx>
+#include <TColGeom_SequenceOfCurve.hxx>
 
 
 #include <Base/PyWrapParseTupleAndKeywords.h>
