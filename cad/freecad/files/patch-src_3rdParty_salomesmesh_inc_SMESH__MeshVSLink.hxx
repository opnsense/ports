--- src/3rdParty/salomesmesh/inc/SMESH_MeshVSLink.hxx.orig	2026-04-14 22:09:59 UTC
+++ src/3rdParty/salomesmesh/inc/SMESH_MeshVSLink.hxx
@@ -27,6 +27,8 @@
 #ifndef _SMESH_MeshVSLink_HeaderFile
 #define _SMESH_MeshVSLink_HeaderFile
 
+#include <MeshVS_HArray1OfSequenceOfInteger.hxx>
+#include <TColStd_Array1OfReal.hxx>
 #if OCC_VERSION_HEX < 0x070000
 #ifndef _Handle_SMESH_MeshVSLink_HeaderFile
 #include <Handle_SMESH_MeshVSLink.hxx>
