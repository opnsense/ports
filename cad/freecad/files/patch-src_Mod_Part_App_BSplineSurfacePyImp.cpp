--- src/Mod/Part/App/BSplineSurfacePyImp.cpp.orig	2026-07-02 10:00:05 UTC
+++ src/Mod/Part/App/BSplineSurfacePyImp.cpp
@@ -31,6 +31,7 @@
 #include <TColStd_Array1OfReal.hxx>
 #include <TColStd_Array2OfReal.hxx>
 #include <TColStd_Array1OfInteger.hxx>
+#include <TColGeom_SequenceOfCurve.hxx>
 
 #include <GeomFill_NSections.hxx>
 
@@ -1360,11 +1361,11 @@ PyObject* BSplineSurfacePy::approximate(PyObject* args
         }
 
         if (continuity < 0 || continuity > 2) {
-            Standard_Failure::Raise("continuity must be between 0 and 2");
+            throw Standard_Failure("continuity must be between 0 and 2");
         }
 
         if (interpolationPoints.RowLength() < 2 || interpolationPoints.ColLength() < 2) {
-            Standard_Failure::Raise("not enough points given");
+            throw Standard_Failure("not enough points given");
         }
 
         GeomAbs_Shape c = GeomAbs_C2;
@@ -1420,7 +1421,11 @@ PyObject* BSplineSurfacePy::approximate(PyObject* args
     catch (Standard_Failure& e) {
         std::string err = e.GetMessageString();
         if (err.empty()) {
+#if OCC_VERSION_HEX >= 0x080000
+            err = e.ExceptionType();
+#else
             err = e.DynamicType()->Name();
+#endif
         }
         PyErr_SetString(PartExceptionOCCError, err.c_str());
         return nullptr;
@@ -1470,7 +1475,7 @@ PyObject* BSplineSurfacePy::interpolate(PyObject* args
         }
 
         if (interpolationPoints.RowLength() < 2 || interpolationPoints.ColLength() < 2) {
-            Standard_Failure::Raise("not enough points given");
+            throw Standard_Failure("not enough points given");
         }
 
         GeomAPI_PointsToBSplineSurface surInterpolation;
@@ -1487,7 +1492,11 @@ PyObject* BSplineSurfacePy::interpolate(PyObject* args
     catch (Standard_Failure& e) {
         std::string err = e.GetMessageString();
         if (err.empty()) {
+#if OCC_VERSION_HEX >= 0x080000
+            err = e.ExceptionType();
+#else
             err = e.DynamicType()->Name();
+#endif
         }
         PyErr_SetString(PartExceptionOCCError, err.c_str());
         return nullptr;
@@ -1570,7 +1579,7 @@ PyObject* BSplineSurfacePy::buildFromPolesMultsKnots(P
             }
         }
         if (occpoles.RowLength() < 2 || occpoles.ColLength() < 2) {
-            Standard_Failure::Raise("not enough points given");
+            throw Standard_Failure("not enough points given");
         }
         if (!genweights) {  // copy the weights
             Py::Sequence list(weights);
@@ -1578,7 +1587,7 @@ PyObject* BSplineSurfacePy::buildFromPolesMultsKnots(P
             Py::Sequence col(list.getItem(0));
             Standard_Integer lwv = col.size();
             if (lwu != lu || lwv != lv) {
-                Standard_Failure::Raise("weights and poles mismatch");
+                throw Standard_Failure("weights and poles mismatch");
             }
             Standard_Integer index1 = 0;
             Standard_Integer index2 = 0;
@@ -1597,7 +1606,7 @@ PyObject* BSplineSurfacePy::buildFromPolesMultsKnots(P
         number_of_vknots = PyObject_Length(vmults);
         if (((uknots != Py_None) && PyObject_Length(uknots) != number_of_uknots)
             || ((vknots != Py_None) && PyObject_Length(vknots) != number_of_vknots)) {
-            Standard_Failure::Raise("number of knots and mults mismatch");
+            throw Standard_Failure("number of knots and mults mismatch");
             return nullptr;
         }
         // copy mults
@@ -1664,17 +1673,17 @@ PyObject* BSplineSurfacePy::buildFromPolesMultsKnots(P
             || (!Base::asBoolean(uperiodic) && sum_of_umults - udegree - 1 != lu)
             || (Base::asBoolean(vperiodic) && sum_of_vmults != lv)
             || (!Base::asBoolean(vperiodic) && sum_of_vmults - vdegree - 1 != lv)) {
-            Standard_Failure::Raise("number of poles and sum of mults mismatch");
+            throw Standard_Failure("number of poles and sum of mults mismatch");
         }
         // check multiplicity of inner knots
         for (Standard_Integer i = 2; i < occumults.Length(); i++) {
             if (occumults(i) > udegree) {
-                Standard_Failure::Raise("multiplicity of inner knot higher than degree");
+                throw Standard_Failure("multiplicity of inner knot higher than degree");
             }
         }
         for (Standard_Integer i = 2; i < occvmults.Length(); i++) {
             if (occvmults(i) > vdegree) {
-                Standard_Failure::Raise("multiplicity of inner knot higher than degree");
+                throw Standard_Failure("multiplicity of inner knot higher than degree");
             }
         }
 
@@ -1695,7 +1704,7 @@ PyObject* BSplineSurfacePy::buildFromPolesMultsKnots(P
             Py_Return;
         }
         else {
-            Standard_Failure::Raise("failed to create spline");
+            throw Standard_Failure("failed to create spline");
             return nullptr;  // goes to the catch block
         }
     }
@@ -1923,7 +1932,7 @@ PyObject* BSplineSurfacePy::scaleKnotsToBounds(PyObjec
     }
     try {
         if (u0 >= u1 || v0 >= v1) {
-            Standard_Failure::Raise("Bad parameter range");
+            throw Standard_Failure("Bad parameter range");
             return nullptr;
             ;
         }
@@ -1934,7 +1943,11 @@ PyObject* BSplineSurfacePy::scaleKnotsToBounds(PyObjec
     catch (Standard_Failure& e) {
         std::string err = e.GetMessageString();
         if (err.empty()) {
+#if OCC_VERSION_HEX >= 0x080000
+            err = e.ExceptionType();
+#else
             err = e.DynamicType()->Name();
+#endif
         }
         PyErr_SetString(PartExceptionOCCError, err.c_str());
         return nullptr;
