--- src/Mod/Part/App/PartFeature.cpp.orig	2026-07-02 12:13:06 UTC
+++ src/Mod/Part/App/PartFeature.cpp
@@ -25,7 +25,9 @@
 
 #include <sstream>
 #include <Bnd_Box.hxx>
+#include <BRep_Builder.hxx>
 #include <BRepAdaptor_Curve.hxx>
+#include <TopoDS_Compound.hxx>
 #include <Mod/Part/App/FCBRepAlgoAPI_Fuse.h>
 #include <Mod/Part/App/FCBRepAlgoAPI_Common.h>
 #include <BRepBndLib.hxx>
@@ -38,9 +40,12 @@
 #include <BRepGProp.hxx>
 #include <BRepGProp_Face.hxx>
 #include <BRepIntCurveSurface_Inter.hxx>
+#include <gce_MakeCirc.hxx>
 #include <gce_MakeDir.hxx>
 #include <gce_MakeLin.hxx>
 #include <gp_Ax1.hxx>
+#include <gp_Ax2.hxx>
+#include <gp_Ax3.hxx>
 #include <gp_Dir.hxx>
 #include <gp_Pln.hxx>
 #include <gp_Trsf.hxx>
@@ -53,7 +58,7 @@
 #include <TopExp_Explorer.hxx>
 #include <TopoDS.hxx>
 #include <TopTools_IndexedMapOfShape.hxx>
-#include <TopTools_ListIteratorOfListOfShape.hxx>
+#include <TopTools_ListOfShape.hxx>
 
 
 #include <App/Application.h>
@@ -479,7 +484,11 @@ App::DocumentObject* Feature::getSubObject(
         Standard_CString msg = e.GetMessageString();
 
         // Avoid name mangling
+#if OCC_VERSION_HEX >= 0x080000
+        str << e.ExceptionType() << " ";
+#else
         str << e.DynamicType()->get_type_name() << " ";
+#endif
 
         if (msg) {
             str << msg;
