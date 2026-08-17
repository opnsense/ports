--- src/3rdParty/salomesmesh/src/StdMeshers/StdMeshers_Prism_3D.cpp.orig	2026-07-01 16:20:28 UTC
+++ src/3rdParty/salomesmesh/src/StdMeshers/StdMeshers_Prism_3D.cpp
@@ -46,14 +46,18 @@
 
 #include <BRepAdaptor_CompCurve.hxx>
 #include <BRep_Tool.hxx>
+#include <Standard_Version.hxx>
+#if OCC_VERSION_HEX >= 0x080000
+#include <Bnd_B3.hxx>
+#else
 #include <Bnd_B3d.hxx>
+#endif
 #include <Geom2dAdaptor_Curve.hxx>
 #include <Geom2d_Line.hxx>
 #include <GeomLib_IsPlanarSurface.hxx>
 #include <Geom_Curve.hxx>
 #include <TopExp.hxx>
 #include <TopExp_Explorer.hxx>
-#include <TopTools_ListIteratorOfListOfShape.hxx>
 #include <TopTools_ListOfShape.hxx>
 #include <TopTools_MapOfShape.hxx>
 #include <TopTools_SequenceOfShape.hxx>
