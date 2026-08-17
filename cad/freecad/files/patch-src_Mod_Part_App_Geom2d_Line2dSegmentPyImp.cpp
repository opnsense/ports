--- src/Mod/Part/App/Geom2d/Line2dSegmentPyImp.cpp.orig	2026-07-01 20:30:18 UTC
+++ src/Mod/Part/App/Geom2d/Line2dSegmentPyImp.cpp
@@ -140,7 +140,7 @@ int Line2dSegmentPy::PyInit(PyObject* args, PyObject* 
             // Create line out of two points
             double distance = (v1 - v2).Length();
             if (distance < gp::Resolution()) {
-                Standard_Failure::Raise("Both points are equal");
+                throw Standard_Failure("Both points are equal");
             }
             GCE2d_MakeSegment ms(gp_Pnt2d(v1.x, v1.y), gp_Pnt2d(v2.x, v2.y));
             if (!ms.IsDone()) {
@@ -241,7 +241,7 @@ void Line2dSegmentPy::setStartPoint(Py::Object arg)
     try {
         // Create line out of two points
         if (p1.Distance(p2) < gp::Resolution()) {
-            Standard_Failure::Raise("Both points are equal");
+            throw Standard_Failure("Both points are equal");
         }
         GCE2d_MakeSegment ms(p1, p2);
         if (!ms.IsDone()) {
@@ -297,7 +297,7 @@ void Line2dSegmentPy::setEndPoint(Py::Object arg)
     try {
         // Create line out of two points
         if (p1.Distance(p2) < gp::Resolution()) {
-            Standard_Failure::Raise("Both points are equal");
+            throw Standard_Failure("Both points are equal");
         }
         GCE2d_MakeSegment ms(p1, p2);
         if (!ms.IsDone()) {
