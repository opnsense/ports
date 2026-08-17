--- src/Mod/Sketcher/Gui/DrawSketchHandlerOffset.h.orig	2026-07-03 08:39:31 UTC
+++ src/Mod/Sketcher/Gui/DrawSketchHandlerOffset.h
@@ -42,6 +42,7 @@
 #include <BRepBuilderAPI.hxx>
 #include <BRepExtrema_DistShapeShape.hxx>
 #include <TopoDS.hxx>
+#include <TopExp_Explorer.hxx>
 #include <gp_Pln.hxx>
 
 #include <Base/Exception.h>
