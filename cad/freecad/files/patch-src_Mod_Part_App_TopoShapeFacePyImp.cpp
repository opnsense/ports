--- src/Mod/Part/App/TopoShapeFacePyImp.cpp.orig	2026-07-01 20:50:53 UTC
+++ src/Mod/Part/App/TopoShapeFacePyImp.cpp
@@ -303,11 +303,11 @@ int TopoShapeFacePy::PyInit(PyObject* args, PyObject* 
                         wires.push_back(TopoDS::Wire(sh));
                     }
                     else {
-                        Standard_Failure::Raise("shape is not a wire");
+                        throw Standard_Failure("shape is not a wire");
                     }
                 }
                 else {
-                    Standard_Failure::Raise("shape is not a wire");
+                    throw Standard_Failure("shape is not a wire");
                 }
             }
 
@@ -316,19 +316,19 @@ int TopoShapeFacePy::PyInit(PyObject* args, PyObject* 
                 if (!mkFace.IsDone()) {
                     switch (mkFace.Error()) {
                         case BRepBuilderAPI_NoFace:
-                            Standard_Failure::Raise("No face");
+                            throw Standard_Failure("No face");
                             break;
                         case BRepBuilderAPI_NotPlanar:
-                            Standard_Failure::Raise("Not planar");
+                            throw Standard_Failure("Not planar");
                             break;
                         case BRepBuilderAPI_CurveProjectionFailed:
-                            Standard_Failure::Raise("Curve projection failed");
+                            throw Standard_Failure("Curve projection failed");
                             break;
                         case BRepBuilderAPI_ParametersOutOfRange:
-                            Standard_Failure::Raise("Parameters out of range");
+                            throw Standard_Failure("Parameters out of range");
                             break;
                         default:
-                            Standard_Failure::Raise("Unknown failure");
+                            throw Standard_Failure("Unknown failure");
                             break;
                     }
                 }
@@ -340,7 +340,7 @@ int TopoShapeFacePy::PyInit(PyObject* args, PyObject* 
                 return 0;
             }
             else {
-                Standard_Failure::Raise("no wires in list");
+                throw Standard_Failure("no wires in list");
             }
         }
         catch (Standard_Failure& e) {
@@ -812,11 +812,11 @@ PyObject* TopoShapeFacePy::cutHoles(PyObject* args)
                         wires.push_back(TopoDS::Wire(sh));
                     }
                     else {
-                        Standard_Failure::Raise("shape is not a wire");
+                        throw Standard_Failure("shape is not a wire");
                     }
                 }
                 else {
-                    Standard_Failure::Raise("argument is not a shape");
+                    throw Standard_Failure("argument is not a shape");
                 }
             }
 
@@ -829,19 +829,19 @@ PyObject* TopoShapeFacePy::cutHoles(PyObject* args)
                 if (!mkFace.IsDone()) {
                     switch (mkFace.Error()) {
                         case BRepBuilderAPI_NoFace:
-                            Standard_Failure::Raise("No face");
+                            throw Standard_Failure("No face");
                             break;
                         case BRepBuilderAPI_NotPlanar:
-                            Standard_Failure::Raise("Not planar");
+                            throw Standard_Failure("Not planar");
                             break;
                         case BRepBuilderAPI_CurveProjectionFailed:
-                            Standard_Failure::Raise("Curve projection failed");
+                            throw Standard_Failure("Curve projection failed");
                             break;
                         case BRepBuilderAPI_ParametersOutOfRange:
-                            Standard_Failure::Raise("Parameters out of range");
+                            throw Standard_Failure("Parameters out of range");
                             break;
                         default:
-                            Standard_Failure::Raise("Unknown failure");
+                            throw Standard_Failure("Unknown failure");
                             break;
                     }
                 }
@@ -850,7 +850,7 @@ PyObject* TopoShapeFacePy::cutHoles(PyObject* args)
                 Py_Return;
             }
             else {
-                Standard_Failure::Raise("empty wire list");
+                throw Standard_Failure("empty wire list");
             }
         }
         catch (Standard_Failure& e) {
