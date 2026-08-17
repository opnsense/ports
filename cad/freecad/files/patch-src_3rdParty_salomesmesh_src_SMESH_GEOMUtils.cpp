--- src/3rdParty/salomesmesh/src/SMESH/GEOMUtils.cpp.orig	2026-07-01 17:04:15 UTC
+++ src/3rdParty/salomesmesh/src/SMESH/GEOMUtils.cpp
@@ -26,8 +26,6 @@
 # pragma clang diagnostic ignored "-Wimport-preprocessor-directive-pedantic"
 #endif
 
-#include <Standard_Stream.hxx>
-
 #include <GEOMUtils.hxx>
 
 #include <Basics_OCCTVersion.hxx>
@@ -69,7 +67,6 @@
 #include <TopExp_Explorer.hxx>
 #include <TopTools_MapOfShape.hxx>
 #include <TopTools_ListOfShape.hxx>
-#include <TopTools_ListIteratorOfListOfShape.hxx>
 #include <TopTools_Array1OfShape.hxx>
 
 #include <Geom_Circle.hxx>
@@ -406,10 +403,10 @@ gp_Vec GEOMUtils::GetVector (const TopoDS_Shape& theSh
                              Standard_Boolean doConsiderOrientation)
 {
   if (theShape.IsNull())
-    Standard_NullObject::Raise("Null shape is given for a vector");
+    throw Standard_NullObject("Null shape is given for a vector");
 
   if (theShape.ShapeType() != TopAbs_EDGE)
-    Standard_TypeMismatch::Raise("Invalid shape is given, must be a vector or an edge");
+    throw Standard_TypeMismatch("Invalid shape is given, must be a vector or an edge");
 
   TopoDS_Edge anE = TopoDS::Edge(theShape);
 
@@ -417,11 +414,11 @@ gp_Vec GEOMUtils::GetVector (const TopoDS_Shape& theSh
   TopExp::Vertices(anE, V1, V2, doConsiderOrientation);
 
   if (V1.IsNull() || V2.IsNull())
-    Standard_NullObject::Raise("Invalid edge is given, it must have two points");
+    throw Standard_NullObject("Invalid edge is given, it must have two points");
 
   gp_Vec aV (BRep_Tool::Pnt(V1), BRep_Tool::Pnt(V2));
   if (aV.Magnitude() < gp::Resolution()) {
-    Standard_ConstructionError::Raise("Vector of zero length is given");
+    throw Standard_ConstructionError("Vector of zero length is given");
   }
 
   return aV;
@@ -771,7 +768,7 @@ TopoDS_Shape GEOMUtils::GetEdgeNearPoint (const TopoDS
   }
 
   if (nbEdges == 0)
-    Standard_NullObject::Raise("Given shape contains no edges");
+    throw Standard_NullObject("Given shape contains no edges");
 
   mapShape.Clear();
   Standard_Integer ind = 1;
@@ -785,7 +782,7 @@ TopoDS_Shape GEOMUtils::GetEdgeNearPoint (const TopoDS
       // 2. Classify the point relatively each edge
       BRepExtrema_DistShapeShape aDistTool (thePoint, anEdges(ind));
       if (!aDistTool.IsDone())
-        Standard_ConstructionError::Raise("Cannot find a distance from the given point to one of edges");
+        throw Standard_ConstructionError("Cannot find a distance from the given point to one of edges");
 
       aDistances(ind) = aDistTool.Value();
       ind++;
@@ -808,10 +805,10 @@ TopoDS_Shape GEOMUtils::GetEdgeNearPoint (const TopoDS
     }
   }
   if (nbFound > 1) {
-    Standard_ConstructionError::Raise("Multiple edges near the given point are found");
+    throw Standard_ConstructionError("Multiple edges near the given point are found");
   }
   else if (nbFound == 0) {
-    Standard_ConstructionError::Raise("There are no edges near the given point");
+    throw Standard_ConstructionError("There are no edges near the given point");
   }
   else {
   }
