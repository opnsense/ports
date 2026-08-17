--- src/3rdParty/salomesmesh/inc/SMESH_Octree.hxx.orig	2026-04-14 22:09:59 UTC
+++ src/3rdParty/salomesmesh/inc/SMESH_Octree.hxx
@@ -31,7 +31,12 @@
 
 #include "SMESH_Utils.hxx"
 #include "SMESH_tree.hxx"
+#include <Standard_Version.hxx>
+#if OCC_VERSION_HEX >= 0x080000
+#include <Bnd_B3.hxx>
+#else
 #include <Bnd_B3d.hxx>
+#endif
 
 //================================================================================
 /*!
