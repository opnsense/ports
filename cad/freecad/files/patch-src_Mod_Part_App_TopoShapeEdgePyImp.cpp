--- src/Mod/Part/App/TopoShapeEdgePyImp.cpp.orig	2026-07-02 12:13:06 UTC
+++ src/Mod/Part/App/TopoShapeEdgePyImp.cpp
@@ -29,7 +29,6 @@
 #include <BRepBuilderAPI_MakeWire.hxx>
 #include <BRepGProp.hxx>
 #include <BRepLProp_CLProps.hxx>
-#include <BRepLProp_CurveTool.hxx>
 #include <GProp_GProps.hxx>
 #include <GProp_PrincipalProps.hxx>
 #include <Geom_Circle.hxx>
@@ -62,6 +61,7 @@
 #include <GCPnts_TangentialDeflection.hxx>
 #include <GCPnts_UniformAbscissa.hxx>
 #include <GCPnts_UniformDeflection.hxx>
+#include <TColStd_HArray1OfReal.hxx>
 
 #include <Base/GeometryPyCXX.h>
 #include <Base/PyWrapParseTupleAndKeywords.h>
@@ -214,8 +214,8 @@ PyObject* TopoShapeEdgePy::getParameterByLength(PyObje
     BRepAdaptor_Curve adapt(e);
 
     // transform value of [0,Length] to [First,Last]
-    double first = BRepLProp_CurveTool::FirstParameter(adapt);
-    double last = BRepLProp_CurveTool::LastParameter(adapt);
+    double first = adapt.FirstParameter();
+    double last = adapt.LastParameter();
     if (!Precision::IsInfinite(first) && !Precision::IsInfinite(last)) {
         double length = GCPnts_AbscissaPoint::Length(adapt, t);
 
