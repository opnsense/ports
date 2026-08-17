--- src/3rdParty/salomesmesh/src/StdMeshers/StdMeshers_ProjectionUtils.cpp.orig	2026-07-01 15:13:02 UTC
+++ src/3rdParty/salomesmesh/src/StdMeshers/StdMeshers_ProjectionUtils.cpp
@@ -57,12 +57,10 @@
 #include <TopExp.hxx>
 #include <TopExp_Explorer.hxx>
 #include <TopTools_Array1OfShape.hxx>
-#include <TopTools_DataMapIteratorOfDataMapOfShapeListOfShape.hxx>
-#include <TopTools_DataMapIteratorOfDataMapOfShapeShape.hxx>
 #include <TopTools_IndexedMapOfShape.hxx>
-#include <TopTools_ListIteratorOfListOfShape.hxx>
 #include <TopTools_ListOfShape.hxx>
 #include <TopTools_MapOfShape.hxx>
+#include <TopTools_DataMapOfShapeListOfShape.hxx>
 #include <TopoDS.hxx>
 #include <TopoDS_Compound.hxx>
 #include <TopoDS_Shape.hxx>
