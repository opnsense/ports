--- src/Mod/Part/App/BSplineCurvePyImp.cpp.orig	2026-07-02 09:44:54 UTC
+++ src/Mod/Part/App/BSplineCurvePyImp.cpp
@@ -313,7 +313,7 @@ PyObject* BSplineCurvePy::segment(PyObject* args)
         tempCurve->Segment(u1, u2);
         if (std::abs(tempCurve->FirstParameter() - u1) > Precision::Approximation()
             || std::abs(tempCurve->LastParameter() - u2) > Precision::Approximation()) {
-            Standard_Failure::Raise("Failed to segment BSpline curve");
+            throw Standard_Failure("Failed to segment BSpline curve");
             return nullptr;
         }
         else {
@@ -938,7 +938,7 @@ PyObject* BSplineCurvePy::approximate(PyObject* args, 
         }
 
         if (degMin > degMax) {
-            Standard_Failure::Raise("DegMin must be lower or equal to DegMax");
+            throw Standard_Failure("DegMin must be lower or equal to DegMax");
         }
 
         GeomAbs_Shape c;
@@ -977,7 +977,7 @@ PyObject* BSplineCurvePy::approximate(PyObject* args, 
                 Py_Return;
             }
             else {
-                Standard_Failure::Raise("Smoothing approximation failed");
+                throw Standard_Failure("Smoothing approximation failed");
                 return nullptr;  // goes to the catch block
             }
         }
@@ -998,7 +998,7 @@ PyObject* BSplineCurvePy::approximate(PyObject* args, 
                 Py_Return;
             }
             else {
-                Standard_Failure::Raise("Approximation with parameters failed");
+                throw Standard_Failure("Approximation with parameters failed");
                 return nullptr;  // goes to the catch block
             }
         }
@@ -1022,7 +1022,7 @@ PyObject* BSplineCurvePy::approximate(PyObject* args, 
             Py_Return;
         }
         else {
-            Standard_Failure::Raise("failed to approximate points");
+            throw Standard_Failure("failed to approximate points");
             return nullptr;  // goes to the catch block
         }
     }
@@ -1152,7 +1152,7 @@ PyObject* BSplineCurvePy::interpolate(PyObject* args, 
         }
 
         if (interpolationPoints->Length() < 2) {
-            Standard_Failure::Raise("not enough points given");
+            throw Standard_Failure("not enough points given");
         }
 
         Handle(TColStd_HArray1OfReal) parameters;
@@ -1221,14 +1221,18 @@ PyObject* BSplineCurvePy::interpolate(PyObject* args, 
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
@@ -1285,7 +1289,7 @@ PyObject* BSplineCurvePy::buildFromPoles(PyObject* arg
                 Py_Return;
             }
             else {
-                Standard_Failure::Raise("failed to create spline");
+                throw Standard_Failure("failed to create spline");
                 return nullptr;  // goes to the catch block
             }
         }
@@ -1306,7 +1310,7 @@ PyObject* BSplineCurvePy::buildFromPoles(PyObject* arg
                 Py_Return;
             }
             else {
-                Standard_Failure::Raise("failed to create spline");
+                throw Standard_Failure("failed to create spline");
                 return nullptr;  // goes to the catch block
             }
         }
@@ -1354,7 +1358,7 @@ PyObject* BSplineCurvePy::buildFromPolesMultsKnots(PyO
 
         number_of_poles = list.size();
         if ((number_of_poles) < 2) {
-            Standard_Failure::Raise("need two or more poles");
+            throw Standard_Failure("need two or more poles");
             return nullptr;
         }
         TColgp_Array1OfPnt occpoles(1, number_of_poles);
@@ -1368,7 +1372,7 @@ PyObject* BSplineCurvePy::buildFromPolesMultsKnots(PyO
         if (mults != Py_None && knots != Py_None) {
             number_of_knots = PyObject_Length(mults);
             if (PyObject_Length(knots) != number_of_knots) {
-                Standard_Failure::Raise("number of knots and mults mismatch");
+                throw Standard_Failure("number of knots and mults mismatch");
                 return nullptr;
             }
         }
@@ -1429,7 +1433,7 @@ PyObject* BSplineCurvePy::buildFromPolesMultsKnots(PyO
         // check multiplicity of inner knots
         for (Standard_Integer i = 2; i < occmults.Length(); i++) {
             if (occmults(i) > degree) {
-                Standard_Failure::Raise("multiplicity of inner knot higher than degree");
+                throw Standard_Failure("multiplicity of inner knot higher than degree");
             }
         }
         if (knots != Py_None) {  // knots are given
@@ -1449,7 +1453,7 @@ PyObject* BSplineCurvePy::buildFromPolesMultsKnots(PyO
         }
         if (weights != Py_None) {  // weights are given
             if (PyObject_Length(weights) != number_of_poles) {
-                Standard_Failure::Raise("number of poles and weights mismatch");
+                throw Standard_Failure("number of poles and weights mismatch");
                 return nullptr;
             }  // complain about mismatch
             Py::Sequence weightssq(weights);
@@ -1467,7 +1471,7 @@ PyObject* BSplineCurvePy::buildFromPolesMultsKnots(PyO
         // check if the number of poles matches the sum of mults
         if ((Base::asBoolean(periodic) && sum_of_mults != number_of_poles)
             || (!Base::asBoolean(periodic) && sum_of_mults - degree - 1 != number_of_poles)) {
-            Standard_Failure::Raise("number of poles and sum of mults mismatch");
+            throw Standard_Failure("number of poles and sum of mults mismatch");
             return (nullptr);
         }
 
@@ -1485,7 +1489,7 @@ PyObject* BSplineCurvePy::buildFromPolesMultsKnots(PyO
             Py_Return;
         }
         else {
-            Standard_Failure::Raise("failed to create spline");
+            throw Standard_Failure("failed to create spline");
             return nullptr;  // goes to the catch block
         }
     }
@@ -1564,7 +1568,11 @@ PyObject* BSplineCurvePy::makeC1Continuous(PyObject* a
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
@@ -1580,7 +1588,7 @@ PyObject* BSplineCurvePy::scaleKnotsToBounds(PyObject*
     }
     try {
         if (u0 >= u1) {
-            Standard_Failure::Raise("Bad parameter range");
+            throw Standard_Failure("Bad parameter range");
             return nullptr;
         }
         GeomBSplineCurve* curve = getGeomBSplineCurvePtr();
@@ -1590,7 +1598,11 @@ PyObject* BSplineCurvePy::scaleKnotsToBounds(PyObject*
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
