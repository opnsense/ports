--- src/3rdParty/salomesmesh/src/NETGENPlugin/NETGENPlugin_Mesher.cpp.orig	2026-07-01 16:20:28 UTC
+++ src/3rdParty/salomesmesh/src/NETGENPlugin/NETGENPlugin_Mesher.cpp
@@ -62,7 +62,12 @@
 #include <BRepBuilderAPI_Copy.hxx>
 #include <BRepMesh_IncrementalMesh.hxx>
 #include <BRep_Tool.hxx>
+#include <Standard_Version.hxx>
+#if OCC_VERSION_HEX >= 0x080000
+#include <Bnd_B3.hxx>
+#else
 #include <Bnd_B3d.hxx>
+#endif
 #include <NCollection_Map.hxx>
 #include <Standard_ErrorHandler.hxx>
 #include <Standard_ProgramError.hxx>
