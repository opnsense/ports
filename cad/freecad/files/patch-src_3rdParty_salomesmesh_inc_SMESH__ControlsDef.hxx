--- src/3rdParty/salomesmesh/inc/SMESH_ControlsDef.hxx.orig	2026-04-14 22:09:59 UTC
+++ src/3rdParty/salomesmesh/inc/SMESH_ControlsDef.hxx
@@ -29,7 +29,12 @@
 #include "SMESH_TypeDefs.hxx"
 
 #include <BRepClass3d_SolidClassifier.hxx>
+#include <Standard_Version.hxx>
+#if OCC_VERSION_HEX >= 0x080000
+#include <Bnd_B3.hxx>
+#else
 #include <Bnd_B3d.hxx>
+#endif
 #include <GeomAPI_ProjectPointOnCurve.hxx>
 #include <GeomAPI_ProjectPointOnSurf.hxx>
 #include <Quantity_Color.hxx>
