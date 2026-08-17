--- src/3rdParty/salomesmesh/src/SMESH/SMESH_Block.cpp.orig	2026-07-01 16:20:28 UTC
+++ src/3rdParty/salomesmesh/src/SMESH/SMESH_Block.cpp
@@ -38,7 +38,12 @@
 #include <BRepTools_WireExplorer.hxx>
 #include <BRep_Builder.hxx>
 #include <BRep_Tool.hxx>
+#include <Standard_Version.hxx>
+#if OCC_VERSION_HEX >= 0x080000
+#include <Bnd_B2.hxx>
+#else
 #include <Bnd_B2d.hxx>
+#endif
 #include <Bnd_Box.hxx>
 #include <Extrema_ExtPC.hxx>
 #include <Extrema_ExtPS.hxx>
@@ -48,7 +53,6 @@
 #include <ShapeAnalysis.hxx>
 #include <TopExp_Explorer.hxx>
 #include <TopTools_IndexedDataMapOfShapeListOfShape.hxx>
-#include <TopTools_ListIteratorOfListOfShape.hxx>
 #include <TopTools_ListOfShape.hxx>
 #include <TopoDS.hxx>
 #include <TopoDS_Compound.hxx>
