--- src/Mod/Surface/App/Blending/BlendCurve.cpp.orig	2026-07-02 13:42:30 UTC
+++ src/Mod/Surface/App/Blending/BlendCurve.cpp
@@ -72,7 +72,7 @@ Handle(Geom_BezierCurve) BlendCurve::compute()
 
         Handle(Geom_BezierCurve) curve;
         if (num_poles > (curve->MaxDegree() + 1)) {  // use Geom_BezierCurve max degree
-            Standard_Failure::Raise("number of constraints exceeds bezier curve capacity");
+            throw Standard_Failure("number of constraints exceeds bezier curve capacity");
         }
 
         TColStd_Array1OfReal knots(1, 2 * num_poles);
@@ -114,15 +114,15 @@ Handle(Geom_BezierCurve) BlendCurve::compute()
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
