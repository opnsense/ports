--- src/3rdParty/salomesmesh/src/StdMeshers/StdMeshers_Regular_1D.cpp.orig	2026-07-01 15:13:02 UTC
+++ src/3rdParty/salomesmesh/src/StdMeshers/StdMeshers_Regular_1D.cpp
@@ -63,6 +63,7 @@
 #include <TopoDS.hxx>
 #include <TopoDS_Edge.hxx>
 #include <TopoDS_Vertex.hxx>
+#include <TColStd_SequenceOfReal.hxx>
 
 #include <string>
 #include <limits>
