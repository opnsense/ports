--- src/3rdParty/salomesmesh/src/SMESH/SMESH_Mesh.cpp.orig	2026-07-01 17:17:39 UTC
+++ src/3rdParty/salomesmesh/src/SMESH/SMESH_Mesh.cpp
@@ -71,7 +71,6 @@
 #include <TColStd_MapOfInteger.hxx>
 #include <TopExp.hxx>
 #include <TopExp_Explorer.hxx>
-#include <TopTools_ListIteratorOfListOfShape.hxx>
 #include <TopTools_ListOfShape.hxx>
 #include <TopTools_MapOfShape.hxx>
 #include <TopoDS_Iterator.hxx>
@@ -83,7 +82,7 @@
 #ifndef WIN32
 #include <boost/thread/thread.hpp>
 #include <boost/bind/bind.hpp>
-#else 
+#else
 #include <boost/thread/thread.hpp>
 #include <boost/bind/bind.hpp>
 //#include <pthread.h>
