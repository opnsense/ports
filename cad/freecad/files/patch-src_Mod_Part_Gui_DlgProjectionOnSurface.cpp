--- src/Mod/Part/Gui/DlgProjectionOnSurface.cpp.orig	2026-07-01 20:50:53 UTC
+++ src/Mod/Part/Gui/DlgProjectionOnSurface.cpp
@@ -43,6 +43,8 @@
 #include <TopoDS_Builder.hxx>
 #include <TopoDS_Edge.hxx>
 #include <TopoDS_Face.hxx>
+#include <TopTools_HSequenceOfShape.hxx>
+#include <TopTools_IndexedMapOfShape.hxx>
 
 
 #include <App/Document.h>
