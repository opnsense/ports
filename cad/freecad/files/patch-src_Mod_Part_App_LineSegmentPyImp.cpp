--- src/Mod/Part/App/LineSegmentPyImp.cpp.orig	2026-07-01 20:30:18 UTC
+++ src/Mod/Part/App/LineSegmentPyImp.cpp
@@ -136,7 +136,7 @@ int LineSegmentPy::PyInit(PyObject* args, PyObject* /*
             // Create line out of two points
             double distance = Base::Distance(v1, v2);
             if (distance < gp::Resolution()) {
-                Standard_Failure::Raise("Both points are equal");
+                throw Standard_Failure("Both points are equal");
             }
             GC_MakeSegment ms(gp_Pnt(v1.x, v1.y, v1.z), gp_Pnt(v2.x, v2.y, v2.z));
             if (!ms.IsDone()) {
@@ -239,7 +239,7 @@ void LineSegmentPy::setStartPoint(Py::Object arg)
     try {
         // Create line out of two points
         if (p1.Distance(p2) < gp::Resolution()) {
-            Standard_Failure::Raise("Both points are equal");
+            throw Standard_Failure("Both points are equal");
         }
         GC_MakeSegment ms(p1, p2);
         if (!ms.IsDone()) {
@@ -297,7 +297,7 @@ void LineSegmentPy::setEndPoint(Py::Object arg)
     try {
         // Create line out of two points
         if (p1.Distance(p2) < gp::Resolution()) {
-            Standard_Failure::Raise("Both points are equal");
+            throw Standard_Failure("Both points are equal");
         }
         GC_MakeSegment ms(p1, p2);
         if (!ms.IsDone()) {
