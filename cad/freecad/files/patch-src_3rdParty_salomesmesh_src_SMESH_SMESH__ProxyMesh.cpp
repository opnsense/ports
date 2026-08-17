--- src/3rdParty/salomesmesh/src/SMESH/SMESH_ProxyMesh.cpp.orig	2026-07-01 15:13:02 UTC
+++ src/3rdParty/salomesmesh/src/SMESH/SMESH_ProxyMesh.cpp
@@ -26,7 +26,7 @@
 #include "SMDS_SetIterator.hxx"
 #include "SMESH_MesherHelper.hxx"
 
-#include <TopTools_ListIteratorOfListOfShape.hxx>
+#include <TopTools_ListOfShape.hxx>
 #include <TopExp.hxx>
 #include <TopTools_IndexedMapOfShape.hxx>
 
