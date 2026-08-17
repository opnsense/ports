--- src/3rdParty/salomesmesh/src/StdMeshers/SMESH_MAT2d.cpp.orig	2026-07-01 16:20:28 UTC
+++ src/3rdParty/salomesmesh/src/StdMeshers/SMESH_MAT2d.cpp
@@ -32,7 +32,12 @@
 #include <BRepBuilderAPI_MakeVertex.hxx>
 #include <BRep_Builder.hxx>
 #include <BRep_Tool.hxx>
+#include <Standard_Version.hxx>
+#if OCC_VERSION_HEX >= 0x080000
+#include <Bnd_B2.hxx>
+#else
 #include <Bnd_B2d.hxx>
+#endif
 //#include <GCPnts_AbscissaPoint.hxx>
 #include <GCPnts_TangentialDeflection.hxx>
 // #include <GCPnts_UniformAbscissa.hxx>
