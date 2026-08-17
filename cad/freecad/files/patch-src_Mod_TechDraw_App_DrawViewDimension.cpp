--- src/Mod/TechDraw/App/DrawViewDimension.cpp.orig	2026-07-02 14:27:52 UTC
+++ src/Mod/TechDraw/App/DrawViewDimension.cpp
@@ -52,6 +52,7 @@
 #include <TopExp_Explorer.hxx>
 #include <TopoDS_Edge.hxx>
 #include <TopoDS_Shape.hxx>
+#include <TopTools_IndexedMapOfShape.hxx>
 
 #include <App/Application.h>
 #include <App/Document.h>
