--- src/3rdParty/salomesmesh/src/SMESH/SMESH_subMesh.cpp.orig	2026-07-01 16:20:28 UTC
+++ src/3rdParty/salomesmesh/src/SMESH/SMESH_subMesh.cpp
@@ -48,9 +48,9 @@
 #include <BRep_Builder.hxx>
 #include <BRep_Tool.hxx>
 #include <TopExp.hxx>
+#include <Standard_Version.hxx>
 #include <TopExp_Explorer.hxx>
 #include <TopTools_IndexedMapOfShape.hxx>
-#include <TopTools_ListIteratorOfListOfShape.hxx>
 #include <TopTools_ListOfShape.hxx>
 #include <TopoDS.hxx>
 #include <TopoDS_Compound.hxx>
@@ -1548,7 +1548,11 @@ bool SMESH_subMesh::ComputeStateEngine(int event)
         catch (Standard_Failure& ex) {
           if ( !_computeError ) _computeError = SMESH_ComputeError::New();
           _computeError->myName    = COMPERR_OCC_EXCEPTION;
+#if OCC_VERSION_HEX >= 0x080000
+          _computeError->myComment += ex.ExceptionType();
+#else
           _computeError->myComment += ex.DynamicType()->Name();
+#endif
           if ( ex.GetMessageString() && strlen( ex.GetMessageString() )) {
             _computeError->myComment += ": ";
             _computeError->myComment += ex.GetMessageString();
