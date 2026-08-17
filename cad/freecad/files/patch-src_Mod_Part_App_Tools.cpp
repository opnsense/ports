--- src/Mod/Part/App/Tools.cpp.orig	2026-07-01 20:30:18 UTC
+++ src/Mod/Part/App/Tools.cpp
@@ -56,10 +56,11 @@
 #include <Standard_Mutex.hxx>
 #include <Standard_TypeMismatch.hxx>
 #include <Standard_Version.hxx>
-#include <TColStd_ListIteratorOfListOfTransient.hxx>
 #include <TColStd_ListOfTransient.hxx>
 #include <TColgp_SequenceOfXY.hxx>
 #include <TColgp_SequenceOfXYZ.hxx>
+#include <TColStd_Array1OfInteger.hxx>
+#include <TColgp_Array1OfPnt.hxx>
 #include <TopoDS.hxx>
 #if OCC_VERSION_HEX < 0x070600
 # include <Adaptor3d_HCurveOnSurface.hxx>
@@ -164,7 +165,7 @@ Handle(Geom_Surface) Part::Tools::makeSurface(
             const Handle(Standard_Transient) & aCur = anIt.Value();
             if (aCur.IsNull()) {
                 assert(0);
-                Standard_ConstructionError::Raise("Tools::makeSurface()");
+                throw Standard_ConstructionError("Tools::makeSurface()");
             }
 #if OCC_VERSION_HEX >= 0x070600
             else if (aCur->IsKind(STANDARD_TYPE(Adaptor3d_CurveOnSurface))) {
@@ -218,12 +219,12 @@ Handle(Geom_Surface) Part::Tools::makeSurface(
                 aPlateBuilder.Add(aConst);
             }
             else {
-                Standard_TypeMismatch::Raise("Tools::makeSurface()");
+                throw Standard_TypeMismatch("Tools::makeSurface()");
             }
         }
     }
     else {
-        Standard_ConstructionError::Raise("Tools::makeSurface()");
+        throw Standard_ConstructionError("Tools::makeSurface()");
     }
 
     // construct
