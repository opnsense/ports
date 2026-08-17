--- src/Mod/Import/App/dxf/ImpExpDxf.cpp.orig	2026-07-02 13:42:30 UTC
+++ src/Mod/Import/App/dxf/ImpExpDxf.cpp
@@ -45,6 +45,9 @@
 #include <Geom_Line.hxx>
 #include <Geom_BSplineCurve.hxx>
 #include <TColgp_Array1OfPnt.hxx>
+#include <TColStd_Array1OfInteger.hxx>
+#include <TColStd_Array1OfReal.hxx>
+#include <TColgp_HArray1OfPnt.hxx>
 #include <TopExp.hxx>
 #include <TopExp_Explorer.hxx>
 #include <TopoDS.hxx>
