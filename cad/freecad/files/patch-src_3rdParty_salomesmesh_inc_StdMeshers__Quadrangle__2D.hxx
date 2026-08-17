--- src/3rdParty/salomesmesh/inc/StdMeshers_Quadrangle_2D.hxx.orig	2026-04-14 22:09:59 UTC
+++ src/3rdParty/salomesmesh/inc/StdMeshers_Quadrangle_2D.hxx
@@ -34,7 +34,12 @@
 #include "StdMeshers_QuadrangleParams.hxx"
 
 #include <TopoDS_Face.hxx>
+#include <Standard_Version.hxx>
+#if OCC_VERSION_HEX >= 0x080000
+#include <Bnd_B2.hxx>
+#else
 #include <Bnd_B2d.hxx>
+#endif
 
 class SMDS_MeshNode;
 class SMESH_Mesh;
