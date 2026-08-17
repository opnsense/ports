--- src/Mod/Part/App/WireJoiner.cpp.orig	2026-07-01 20:50:53 UTC
+++ src/Mod/Part/App/WireJoiner.cpp
@@ -53,6 +53,9 @@
 #include <TopExp.hxx>
 #include <TopExp_Explorer.hxx>
 #include <TopTools_HSequenceOfShape.hxx>
+#include <IntRes2d_SequenceOfIntersectionPoint.hxx>
+#include <TColStd_SequenceOfReal.hxx>
+#include <TColgp_SequenceOfPnt.hxx>
 
 #include <BRepTools_History.hxx>
 #include <ShapeBuild_ReShape.hxx>
