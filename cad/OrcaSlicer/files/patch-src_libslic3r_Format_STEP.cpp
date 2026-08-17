--- src/libslic3r/Format/STEP.cpp.orig	2026-03-22 17:56:38 UTC
+++ src/libslic3r/Format/STEP.cpp
@@ -25,6 +25,7 @@
 #include "XCAFDoc_DocumentTool.hxx"
 #include "XCAFDoc_ShapeTool.hxx"
 #include "XCAFApp_Application.hxx"
+#include "TDF_LabelSequence.hxx"
 #include "TopoDS_Solid.hxx"
 #include "TopoDS_Compound.hxx"
 #include "TopoDS_Builder.hxx"
