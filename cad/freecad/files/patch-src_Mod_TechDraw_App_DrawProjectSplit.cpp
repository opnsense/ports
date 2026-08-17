--- src/Mod/TechDraw/App/DrawProjectSplit.cpp.orig	2026-07-02 14:27:52 UTC
+++ src/Mod/TechDraw/App/DrawProjectSplit.cpp
@@ -32,7 +32,6 @@
 #include <BRepBndLib.hxx>
 #include <BRepBuilderAPI_Copy.hxx>
 #include <BRepBuilderAPI_MakeEdge.hxx>
-#include <BRepLProp_CurveTool.hxx>
 #include <Geom_Curve.hxx>
 #include <GeomLib_Tool.hxx>
 #include <gp_Ax2.hxx>
@@ -216,8 +215,8 @@ std::vector<TopoDS_Edge> DrawProjectSplit::split1Edge(
 
     BRepAdaptor_Curve adapt(e);
     Handle(Geom_Curve) c = adapt.Curve().Curve();
-    double first = BRepLProp_CurveTool::FirstParameter(adapt);
-    double last = BRepLProp_CurveTool::LastParameter(adapt);
+    double first = adapt.FirstParameter();
+    double last = adapt.LastParameter();
     if (first > last) {
         //TODO parms.reverse();
         Base::Console().message("DPS::split1Edge - edge is backwards!\n");
