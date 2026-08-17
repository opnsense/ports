--- src/Mod/Part/App/GeomPlate/BuildPlateSurfacePyImp.cpp.orig	2026-07-01 20:50:53 UTC
+++ src/Mod/Part/App/GeomPlate/BuildPlateSurfacePyImp.cpp
@@ -26,6 +26,10 @@
 
 #include <Standard_Failure.hxx>
 
+#include <TColGeom2d_HArray1OfCurve.hxx>
+#include <TColStd_HArray1OfInteger.hxx>
+#include <TColgp_SequenceOfXY.hxx>
+#include <TColgp_SequenceOfXYZ.hxx>
 
 #include "GeomPlate/BuildPlateSurfacePy.h"
 #include "GeomPlate/BuildPlateSurfacePy.cpp"
