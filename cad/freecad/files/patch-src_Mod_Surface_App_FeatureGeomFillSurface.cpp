--- src/Mod/Surface/App/FeatureGeomFillSurface.cpp.orig	2026-07-02 13:42:30 UTC
+++ src/Mod/Surface/App/FeatureGeomFillSurface.cpp
@@ -69,7 +69,7 @@ void ShapeValidator::checkEdge(const TopoDS_Shape& sha
 void ShapeValidator::checkEdge(const TopoDS_Shape& shape)
 {
     if (shape.IsNull() || shape.ShapeType() != TopAbs_EDGE) {
-        Standard_Failure::Raise("Shape is not an edge.\n");
+        throw Standard_Failure("Shape is not an edge.\n");
     }
 
     TopoDS_Edge etmp = TopoDS::Edge(shape);                             // Curve TopoDS_Edge
@@ -120,7 +120,7 @@ void ShapeValidator::checkAndAdd(
         }
     }
     catch (Standard_Failure&) {  // any OCC exception means an inappropriate shape in the selection
-        Standard_Failure::Raise("Wrong shape type.\n");
+        throw Standard_Failure("Wrong shape type.\n");
     }
 }
 
@@ -200,7 +200,7 @@ GeomFill_FillingStyle GeomFillSurface::getFillingStyle
         case GeomFill_CurvedStyle:
             return static_cast<GeomFill_FillingStyle>(FillType.getValue());
         default:
-            Standard_Failure::Raise("Filling style must be 0 (Stretch), 1 (Coons), or 2 (Curved).\n");
+            throw Standard_Failure("Filling style must be 0 (Stretch), 1 (Coons), or 2 (Curved).\n");
             return GeomFill_StretchStyle;  // this is to shut up the compiler
     }
 }
@@ -212,7 +212,7 @@ bool GeomFillSurface::getWire(TopoDS_Wire& aWire)
 
     std::vector<App::PropertyLinkSubList::SubSet> boundary = BoundaryList.getSubListValues();
     if (boundary.size() > 4) {  // if too many not even try
-        Standard_Failure::Raise("Only 2-4 curves are allowed\n");
+        throw Standard_Failure("Only 2-4 curves are allowed\n");
     }
 
     ShapeValidator validator;
@@ -224,12 +224,12 @@ bool GeomFillSurface::getWire(TopoDS_Wire& aWire)
             }
         }
         else {
-            Standard_Failure::Raise("Curve not from Part::Feature\n");
+            throw Standard_Failure("Curve not from Part::Feature\n");
         }
     }
 
     if (validator.numEdges() < 2 || validator.numEdges() > 4) {
-        Standard_Failure::Raise("Only 2-4 curves are allowed\n");
+        throw Standard_Failure("Only 2-4 curves are allowed\n");
     }
 
     // Reorder the curves and fix the wire if required
@@ -244,7 +244,7 @@ bool GeomFillSurface::getWire(TopoDS_Wire& aWire)
     aWire = aShFW->Wire();  // Healed Wire
 
     if (aWire.IsNull()) {
-        Standard_Failure::Raise("Wire unable to be constructed\n");
+        throw Standard_Failure("Wire unable to be constructed\n");
     }
 
     return validator.isBezier();
@@ -261,10 +261,10 @@ void GeomFillSurface::createFace(const Handle(Geom_Bou
     TopoDS_Face aFace = aFaceBuilder.Face();
 
     if (!aFaceBuilder.IsDone()) {
-        Standard_Failure::Raise("Face unable to be constructed\n");
+        throw Standard_Failure("Face unable to be constructed\n");
     }
     if (aFace.IsNull()) {
-        Standard_Failure::Raise("Resulting Face is null\n");
+        throw Standard_Failure("Resulting Face is null\n");
     }
     this->Shape.setValue(aFace);
 }
@@ -291,7 +291,7 @@ void GeomFillSurface::createBezierSurface(TopoDS_Wire&
             curves.push_back(bezier);
         }
         else {
-            Standard_Failure::Raise("Curve not a Bezier Curve");
+            throw Standard_Failure("Curve not a Bezier Curve");
         }
     }
 
@@ -360,7 +360,7 @@ void GeomFillSurface::createBSplineSurface(TopoDS_Wire
                 Handle(Geom_BSplineCurve) spline
                     = scc.ConvertToBSpline(c_geom, u1, u2, Precision::Confusion());
                 if (spline.IsNull()) {
-                    Standard_Failure::Raise(
+                    throw Standard_Failure(
                         "A curve was not a B-spline and could not be converted into one."
                     );
                 }
