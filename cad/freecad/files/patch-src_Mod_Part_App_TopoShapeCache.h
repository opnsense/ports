--- src/Mod/Part/App/TopoShapeCache.h.orig	2026-07-01 20:30:17 UTC
+++ src/Mod/Part/App/TopoShapeCache.h
@@ -32,7 +32,8 @@
 #include <TopoDS_Vertex.hxx>
 #include <TopExp.hxx>
 #include <TopExp_Explorer.hxx>
-#include <TopTools_ListIteratorOfListOfShape.hxx>
+#include <TopTools_IndexedDataMapOfShapeListOfShape.hxx>
+#include <TopTools_IndexedMapOfShape.hxx>
 #include <utility>
 
 #include <App/ElementMap.h>
