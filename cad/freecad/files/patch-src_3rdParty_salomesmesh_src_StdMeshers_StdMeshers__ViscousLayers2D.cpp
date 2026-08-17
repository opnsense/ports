--- src/3rdParty/salomesmesh/src/StdMeshers/StdMeshers_ViscousLayers2D.cpp.orig	2026-07-01 16:20:28 UTC
+++ src/3rdParty/salomesmesh/src/StdMeshers/StdMeshers_ViscousLayers2D.cpp
@@ -49,8 +49,14 @@
 #include <BRepAdaptor_Curve.hxx>
 #include <BRepAdaptor_Curve2d.hxx>
 #include <BRep_Tool.hxx>
+#include <Standard_Version.hxx>
+#if OCC_VERSION_HEX >= 0x080000
+#include <Bnd_B2.hxx>
+#include <Bnd_B3.hxx>
+#else
 #include <Bnd_B2d.hxx>
 #include <Bnd_B3d.hxx>
+#endif
 #include <ElCLib.hxx>
 #include <GCPnts_AbscissaPoint.hxx>
 #include <Geom2dAdaptor_Curve.hxx>
@@ -71,7 +77,6 @@
 #include <TopExp_Explorer.hxx>
 #include <TopTools_IndexedDataMapOfShapeListOfShape.hxx>
 #include <TopTools_IndexedMapOfShape.hxx>
-#include <TopTools_ListIteratorOfListOfShape.hxx>
 #include <TopTools_ListOfShape.hxx>
 #include <TopTools_MapOfShape.hxx>
 #include <TopoDS.hxx>
