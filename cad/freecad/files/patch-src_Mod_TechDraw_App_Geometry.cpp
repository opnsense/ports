--- src/Mod/TechDraw/App/Geometry.cpp.orig	2026-07-02 14:27:52 UTC
+++ src/Mod/TechDraw/App/Geometry.cpp
@@ -34,7 +34,6 @@
 # include <BRepLib.hxx>
 # include <BRepLProp_CLProps.hxx>
 # include <BRepTools.hxx>
-# include <BRepLProp_CurveTool.hxx>
 # include <GC_MakeArcOfCircle.hxx>
 # include <GC_MakeEllipse.hxx>
 # include <GC_MakeCircle.hxx>
@@ -1712,8 +1711,8 @@ double GeometryUtils::edgeLength(TopoDS_Edge occEdge)
 {
     BRepAdaptor_Curve adapt(occEdge);
     const Handle(Geom_Curve) curve = adapt.Curve().Curve();
-    double first = BRepLProp_CurveTool::FirstParameter(adapt);
-    double last = BRepLProp_CurveTool::LastParameter(adapt);
+    double first = adapt.FirstParameter();
+    double last = adapt.LastParameter();
     try {
         GeomAdaptor_Curve adaptor(curve);
         return GCPnts_AbscissaPoint::Length(adaptor,first,last,Precision::Confusion());
