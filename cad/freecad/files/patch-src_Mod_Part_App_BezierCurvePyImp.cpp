--- src/Mod/Part/App/BezierCurvePyImp.cpp.orig	2026-07-01 20:30:18 UTC
+++ src/Mod/Part/App/BezierCurvePyImp.cpp
@@ -388,7 +388,7 @@ PyObject* BezierCurvePy::interpolate(PyObject* args)
         Py::Sequence constraints(obj);
         int nb_pts = constraints.size();
         if (nb_pts < 2) {
-            Standard_Failure::Raise("not enough points given");
+            throw Standard_Failure("not enough points given");
         }
 
         TColStd_Array1OfReal params(1, nb_pts);
@@ -396,7 +396,7 @@ PyObject* BezierCurvePy::interpolate(PyObject* args)
             Py::Sequence plist(par);
             int param_size = plist.size();
             if (param_size != nb_pts) {
-                Standard_Failure::Raise("number of points and parameters don't match");
+                throw Standard_Failure("number of points and parameters don't match");
             }
             int idx = 1;
             for (Py::Sequence::iterator pit = plist.begin(); pit != plist.end(); ++pit) {
@@ -416,7 +416,7 @@ PyObject* BezierCurvePy::interpolate(PyObject* args)
             num_poles += (int)row.size();
         }
         if (num_poles > curve->MaxDegree()) {
-            Standard_Failure::Raise("number of constraints exceeds bezier curve capacity");
+            throw Standard_Failure("number of constraints exceeds bezier curve capacity");
         }
         // create a bezier-type knot sequence
         TColStd_Array1OfReal knots(1, 2 * num_poles);
@@ -459,15 +459,15 @@ PyObject* BezierCurvePy::interpolate(PyObject* args)
         math_Gauss gauss(OCCmatrix);
         gauss.Solve(res_x);
         if (!gauss.IsDone()) {
-            Standard_Failure::Raise("Failed to solve equations");
+            throw Standard_Failure("Failed to solve equations");
         }
         gauss.Solve(res_y);
         if (!gauss.IsDone()) {
-            Standard_Failure::Raise("Failed to solve equations");
+            throw Standard_Failure("Failed to solve equations");
         }
         gauss.Solve(res_z);
         if (!gauss.IsDone()) {
-            Standard_Failure::Raise("Failed to solve equations");
+            throw Standard_Failure("Failed to solve equations");
         }
 
         TColgp_Array1OfPnt poles(1, num_poles);
