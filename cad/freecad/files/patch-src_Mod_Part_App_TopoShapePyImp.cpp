--- src/Mod/Part/App/TopoShapePyImp.cpp.orig	2026-07-01 20:30:18 UTC
+++ src/Mod/Part/App/TopoShapePyImp.cpp
@@ -63,8 +63,10 @@
 #include <TopoDS.hxx>
 #include <TopoDS_Iterator.hxx>
 #include <TopTools_IndexedMapOfShape.hxx>
-#include <TopTools_ListIteratorOfListOfShape.hxx>
 #include <TopTools_ListOfShape.hxx>
+#include <TopTools_IndexedDataMapOfShapeListOfShape.hxx>
+#include <TopTools_HSequenceOfShape.hxx>
+#include <BRepExtrema_MapOfIntegerPackedMapOfInteger.hxx>
 
 #include <App/PropertyStandard.h>
 #include <App/StringHasherPy.h>
@@ -1539,7 +1541,7 @@ PyObject* TopoShapePy::isClosed(PyObject* args) const
 
     try {
         if (getTopoShapePtr()->getShape().IsNull()) {
-            Standard_Failure::Raise("Cannot determine the 'Closed'' flag of an empty shape");
+            throw Standard_Failure("Cannot determine the 'Closed'' flag of an empty shape");
         }
         return Py_BuildValue("O", (getTopoShapePtr()->isClosed() ? Py_True : Py_False));
     }
