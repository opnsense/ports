--- src/Mod/ReverseEngineering/App/AppReverseEngineering.cpp.orig	2026-07-02 13:42:31 UTC
+++ src/Mod/ReverseEngineering/App/AppReverseEngineering.cpp
@@ -23,6 +23,7 @@
  ***************************************************************************/
 
 #include <Geom_BSplineSurface.hxx>
+#include <Standard_Version.hxx>
 #include <TColgp_Array1OfPnt.hxx>
 
 
@@ -403,7 +404,11 @@ class Module : public Py::ExtensionModule<Module> (pri
                 }
             }
 
+#if OCC_VERSION_HEX >= 0x080000
+            TColgp_Array1OfPnt clPoints(pts.size()-1);
+#else
             TColgp_Array1OfPnt clPoints(0, pts.size()-1);
+#endif
             if (clPoints.Length() < uPoles * vPoles) {
                 throw Py::ValueError("Too less data points for the specified number of poles");
             }
