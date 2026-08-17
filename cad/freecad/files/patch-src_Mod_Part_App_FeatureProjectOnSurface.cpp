--- src/Mod/Part/App/FeatureProjectOnSurface.cpp.orig	2026-07-01 20:50:53 UTC
+++ src/Mod/Part/App/FeatureProjectOnSurface.cpp
@@ -38,6 +38,7 @@
 #include <ShapeFix_Wireframe.hxx>
 #include <Standard_Failure.hxx>
 #include <TopExp_Explorer.hxx>
+#include <TopTools_HSequenceOfShape.hxx>
 #include <TopoDS.hxx>
 #include <TopoDS_Builder.hxx>
 #include <sstream>
