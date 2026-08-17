--- src/Mod/Part/App/Geom2d/BSplineCurve2dPyImp.cpp.orig	2026-07-02 10:41:24 UTC
+++ src/Mod/Part/App/Geom2d/BSplineCurve2dPyImp.cpp
@@ -846,7 +846,7 @@ PyObject* BSplineCurve2dPy::approximate(PyObject* args
         }
 
         if (degMin > degMax) {
-            Standard_Failure::Raise("DegMin must be lower or equal to DegMax");
+            throw Standard_Failure("DegMin must be lower or equal to DegMax");
         }
 
         GeomAbs_Shape c;
@@ -889,7 +889,7 @@ PyObject* BSplineCurve2dPy::approximate(PyObject* args
                 Py_Return;
             }
             else {
-                Standard_Failure::Raise("Smoothing approximation failed");
+                throw Standard_Failure("Smoothing approximation failed");
                 return nullptr;  // goes to the catch block
             }
         }
@@ -910,7 +910,7 @@ PyObject* BSplineCurve2dPy::approximate(PyObject* args
                 Py_Return;
             }
             else {
-                Standard_Failure::Raise("Approximation with parameters failed");
+                throw Standard_Failure("Approximation with parameters failed");
                 return nullptr;  // goes to the catch block
             }
         }
@@ -934,7 +934,7 @@ PyObject* BSplineCurve2dPy::approximate(PyObject* args
             Py_Return;
         }
         else {
-            Standard_Failure::Raise("failed to approximate points");
+            throw Standard_Failure("failed to approximate points");
             return nullptr;  // goes to the catch block
         }
     }
@@ -1057,7 +1057,7 @@ PyObject* BSplineCurve2dPy::interpolate(PyObject* args
         }
 
         if (interpolationPoints->Length() < 2) {
-            Standard_Failure::Raise("not enough points given");
+            throw Standard_Failure("not enough points given");
         }
 
         Handle(TColStd_HArray1OfReal) parameters;
@@ -1125,14 +1125,18 @@ PyObject* BSplineCurve2dPy::interpolate(PyObject* args
             Py_Return;
         }
         else {
-            Standard_Failure::Raise("failed to interpolate points");
+            throw Standard_Failure("failed to interpolate points");
             return nullptr;  // goes to the catch block
         }
     }
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
@@ -1188,7 +1192,7 @@ PyObject* BSplineCurve2dPy::buildFromPoles(PyObject* a
                 Py_Return;
             }
             else {
-                Standard_Failure::Raise("failed to create spline");
+                throw Standard_Failure("failed to create spline");
                 return nullptr;  // goes to the catch block
             }
         }
@@ -1209,7 +1213,7 @@ PyObject* BSplineCurve2dPy::buildFromPoles(PyObject* a
                 Py_Return;
             }
             else {
-                Standard_Failure::Raise("failed to create spline");
+                throw Standard_Failure("failed to create spline");
                 return nullptr;  // goes to the catch block
             }
         }
@@ -1254,7 +1258,7 @@ PyObject* BSplineCurve2dPy::buildFromPolesMultsKnots(P
 
         number_of_poles = list.size();
         if ((number_of_poles) < 2) {
-            Standard_Failure::Raise("need two or more poles");
+            throw Standard_Failure("need two or more poles");
             return nullptr;
         }
         TColgp_Array1OfPnt2d occpoles(1, number_of_poles);
@@ -1267,7 +1271,7 @@ PyObject* BSplineCurve2dPy::buildFromPolesMultsKnots(P
         if (mults != Py_None && knots != Py_None) {
             number_of_knots = PyObject_Length(mults);
             if (PyObject_Length(knots) != number_of_knots) {
-                Standard_Failure::Raise("number of knots and mults mismatch");
+                throw Standard_Failure("number of knots and mults mismatch");
                 return nullptr;
             }
         }
@@ -1342,7 +1346,7 @@ PyObject* BSplineCurve2dPy::buildFromPolesMultsKnots(P
         }
         if (weights != Py_None) {  // weights are given
             if (PyObject_Length(weights) != number_of_poles) {
-                Standard_Failure::Raise("number of poles and weights mismatch");
+                throw Standard_Failure("number of poles and weights mismatch");
                 return nullptr;
             }  // complain about mismatch
             Py::Sequence weightssq(weights);
@@ -1360,7 +1364,7 @@ PyObject* BSplineCurve2dPy::buildFromPolesMultsKnots(P
         // check if the number of poles matches the sum of mults
         if (((Base::asBoolean(periodic)) && sum_of_mults != number_of_poles)
             || (!Base::asBoolean(periodic) && sum_of_mults - degree - 1 != number_of_poles)) {
-            Standard_Failure::Raise("number of poles and sum of mults mismatch");
+            throw Standard_Failure("number of poles and sum of mults mismatch");
             return (nullptr);
         }
 
@@ -1377,7 +1381,7 @@ PyObject* BSplineCurve2dPy::buildFromPolesMultsKnots(P
             Py_Return;
         }
         else {
-            Standard_Failure::Raise("failed to create spline");
+            throw Standard_Failure("failed to create spline");
             return nullptr;  // goes to the catch block
         }
     }
@@ -1442,7 +1446,11 @@ PyObject* BSplineCurve2dPy::makeC1Continuous(PyObject*
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
