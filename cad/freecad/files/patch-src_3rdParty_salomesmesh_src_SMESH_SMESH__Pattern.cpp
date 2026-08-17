--- src/3rdParty/salomesmesh/src/SMESH/SMESH_Pattern.cpp.orig	2026-07-01 15:13:02 UTC
+++ src/3rdParty/salomesmesh/src/SMESH/SMESH_Pattern.cpp
@@ -60,7 +60,8 @@
 #include <TopExp.hxx>
 #include <TopExp_Explorer.hxx>
 #include <TopLoc_Location.hxx>
-#include <TopTools_ListIteratorOfListOfShape.hxx>
+#include <TopTools_ListOfShape.hxx>
+#include <TopTools_MapOfShape.hxx>
 #include <TopoDS.hxx>
 #include <TopoDS_Edge.hxx>
 #include <TopoDS_Face.hxx>
