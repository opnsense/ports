--- src/Mod/TechDraw/App/DrawUtil.cpp.orig	2026-07-02 14:27:52 UTC
+++ src/Mod/TechDraw/App/DrawUtil.cpp
@@ -38,7 +38,6 @@
 #include <BRepBuilderAPI_MakeEdge.hxx>
 #include <BRepExtrema_DistShapeShape.hxx>
 #include <BRepLProp_CLProps.hxx>
-#include <BRepLProp_CurveTool.hxx>
 #include <BRepLProp_SLProps.hxx>
 #include <BRepTools.hxx>
 #include <BRep_Builder.hxx>
@@ -1172,8 +1171,8 @@ bool DrawUtil::isCrazy(TopoDS_Edge e)
         return true;
     }
 
-    double start = BRepLProp_CurveTool::FirstParameter(adapt);
-    double end = BRepLProp_CurveTool::LastParameter(adapt);
+    double start = adapt.FirstParameter();
+    double end = adapt.LastParameter();
     BRepLProp_CLProps propStart(adapt, start, 0, Precision::Confusion());
     const gp_Pnt& vStart = propStart.Value();
     BRepLProp_CLProps propEnd(adapt, end, 0, Precision::Confusion());
@@ -1934,8 +1933,8 @@ void DrawUtil::dumpEdge(const char* label, int i, Topo
 void DrawUtil::dumpEdge(const char* label, int i, TopoDS_Edge e)
 {
     BRepAdaptor_Curve adapt(e);
-    double start = BRepLProp_CurveTool::FirstParameter(adapt);
-    double end = BRepLProp_CurveTool::LastParameter(adapt);
+    double start = adapt.FirstParameter();
+    double end = adapt.LastParameter();
     BRepLProp_CLProps propStart(adapt, start, 0, Precision::Confusion());
     const gp_Pnt& vStart = propStart.Value();
     BRepLProp_CLProps propEnd(adapt, end, 0, Precision::Confusion());
