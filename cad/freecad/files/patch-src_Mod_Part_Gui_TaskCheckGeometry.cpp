--- src/Mod/Part/Gui/TaskCheckGeometry.cpp.orig	2026-07-01 20:50:53 UTC
+++ src/Mod/Part/Gui/TaskCheckGeometry.cpp
@@ -38,7 +38,7 @@
 #include <BRepBndLib.hxx>
 #include <BRepBuilderAPI_Copy.hxx>
 #include <BRepCheck_Analyzer.hxx>
-#include <BRepCheck_ListIteratorOfListOfStatus.hxx>
+#include <BRepCheck_ListOfStatus.hxx>
 #include <BRepCheck_Result.hxx>
 #include <BRepTools_ShapeSet.hxx>
 #include <ShapeAnalysis_FreeBounds.hxx>
