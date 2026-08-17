--- src/3rdParty/salomesmesh/src/SMESH/SMESH_MesherHelper.cpp.orig	2026-07-01 15:13:02 UTC
+++ src/3rdParty/salomesmesh/src/SMESH/SMESH_MesherHelper.cpp
@@ -50,8 +50,7 @@
 #include <ShapeAnalysis.hxx>
 #include <TopExp.hxx>
 #include <TopExp_Explorer.hxx>
-#include <TopTools_ListIteratorOfListOfShape.hxx>
-#include <TopTools_MapIteratorOfMapOfShape.hxx>
+#include <TopTools_ListOfShape.hxx>
 #include <TopTools_MapOfShape.hxx>
 #include <TopoDS.hxx>
 #include <gp_Ax3.hxx>
