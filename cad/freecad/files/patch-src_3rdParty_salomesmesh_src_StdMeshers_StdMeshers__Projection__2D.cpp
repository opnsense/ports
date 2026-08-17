--- src/3rdParty/salomesmesh/src/StdMeshers/StdMeshers_Projection_2D.cpp.orig	2026-07-01 16:20:28 UTC
+++ src/3rdParty/salomesmesh/src/StdMeshers/StdMeshers_Projection_2D.cpp
@@ -49,13 +49,16 @@
 
 #include <BRepAdaptor_Surface.hxx>
 #include <BRep_Tool.hxx>
+#include <Standard_Version.hxx>
+#if OCC_VERSION_HEX >= 0x080000
+#include <Bnd_B2.hxx>
+#else
 #include <Bnd_B2d.hxx>
+#endif
 #include <GeomAPI_ProjectPointOnSurf.hxx>
 #include <GeomLib_IsPlanarSurface.hxx>
 #include <TopExp.hxx>
 #include <TopExp_Explorer.hxx>
-#include <TopTools_DataMapIteratorOfDataMapOfShapeShape.hxx>
-#include <TopTools_ListIteratorOfListOfShape.hxx>
 #include <TopTools_MapOfShape.hxx>
 #include <TopoDS.hxx>
 #include <TopoDS_Solid.hxx>
