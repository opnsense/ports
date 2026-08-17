--- src/Mod/Part/App/Geometry.cpp.orig	2026-07-01 20:30:18 UTC
+++ src/Mod/Part/App/Geometry.cpp
@@ -38,6 +38,9 @@
 #include <GC_MakeHyperbola.hxx>
 #include <GC_MakeSegment.hxx>
 #include <GCPnts_AbscissaPoint.hxx>
+#include <TColStd_Array1OfInteger.hxx>
+#include <TColgp_Array1OfPnt2d.hxx>
+#include <TColgp_Array1OfVec.hxx>
 #include <gce_ErrorType.hxx>
 #include <gce_MakeParab.hxx>
 #include <Geom_BezierCurve.hxx>
@@ -1684,7 +1687,7 @@ void GeomBSplineCurve::interpolate(const std::vector<g
 void GeomBSplineCurve::interpolate(const std::vector<gp_Pnt>& p, Standard_Boolean periodic)
 {
     if (p.size() < 2) {
-        Standard_ConstructionError::Raise();
+        throw Standard_ConstructionError();
     }
 
     double tol3d = Precision::Approximation();
@@ -1701,10 +1704,10 @@ void GeomBSplineCurve::interpolate(const std::vector<g
 void GeomBSplineCurve::interpolate(const std::vector<gp_Pnt>& p, const std::vector<gp_Vec>& t)
 {
     if (p.size() < 2) {
-        Standard_ConstructionError::Raise();
+        throw Standard_ConstructionError();
     }
     if (p.size() != t.size()) {
-        Standard_ConstructionError::Raise();
+        throw Standard_ConstructionError();
     }
 
     double tol3d = Precision::Approximation();
@@ -1734,10 +1737,10 @@ void GeomBSplineCurve::getCardinalSplineTangents(
 {
     // https://de.wikipedia.org/wiki/Kubisch_Hermitescher_Spline#Cardinal_Spline
     if (p.size() < 2) {
-        Standard_ConstructionError::Raise();
+        throw Standard_ConstructionError();
     }
     if (p.size() != c.size()) {
-        Standard_ConstructionError::Raise();
+        throw Standard_ConstructionError();
     }
 
     t.resize(p.size());
@@ -1768,7 +1771,7 @@ void GeomBSplineCurve::getCardinalSplineTangents(
 {
     // https://de.wikipedia.org/wiki/Kubisch_Hermitescher_Spline#Cardinal_Spline
     if (p.size() < 2) {
-        Standard_ConstructionError::Raise();
+        throw Standard_ConstructionError();
     }
 
     t.resize(p.size());
@@ -2931,7 +2934,7 @@ void GeomArcOfCircle::setHandle(const Handle(Geom_Trim
 {
     Handle(Geom_Circle) basis = Handle(Geom_Circle)::DownCast(c->BasisCurve());
     if (basis.IsNull()) {
-        Standard_Failure::Raise("Basis curve is not a circle");
+        throw Standard_Failure("Basis curve is not a circle");
     }
     this->myCurve = Handle(Geom_TrimmedCurve)::DownCast(c->Copy());
 }
@@ -3463,7 +3466,7 @@ void GeomArcOfEllipse::setHandle(const Handle(Geom_Tri
 {
     Handle(Geom_Ellipse) basis = Handle(Geom_Ellipse)::DownCast(c->BasisCurve());
     if (basis.IsNull()) {
-        Standard_Failure::Raise("Basis curve is not an ellipse");
+        throw Standard_Failure("Basis curve is not an ellipse");
     }
     this->myCurve = Handle(Geom_TrimmedCurve)::DownCast(c->Copy());
 }
@@ -3936,7 +3939,7 @@ void GeomArcOfHyperbola::setHandle(const Handle(Geom_T
 {
     Handle(Geom_Hyperbola) basis = Handle(Geom_Hyperbola)::DownCast(c->BasisCurve());
     if (basis.IsNull()) {
-        Standard_Failure::Raise("Basis curve is not an hyperbola");
+        throw Standard_Failure("Basis curve is not an hyperbola");
     }
     this->myCurve = Handle(Geom_TrimmedCurve)::DownCast(c->Copy());
 }
@@ -4374,7 +4377,7 @@ void GeomArcOfParabola::setHandle(const Handle(Geom_Tr
 {
     Handle(Geom_Parabola) basis = Handle(Geom_Parabola)::DownCast(c->BasisCurve());
     if (basis.IsNull()) {
-        Standard_Failure::Raise("Basis curve is not a parabola");
+        throw Standard_Failure("Basis curve is not a parabola");
     }
     this->myCurve = Handle(Geom_TrimmedCurve)::DownCast(c->Copy());
 }
@@ -4708,7 +4711,7 @@ void GeomLineSegment::setHandle(const Handle(Geom_Trim
 {
     Handle(Geom_Line) basis = Handle(Geom_Line)::DownCast(c->BasisCurve());
     if (basis.IsNull()) {
-        Standard_Failure::Raise("Basis curve is not a line");
+        throw Standard_Failure("Basis curve is not a line");
     }
     this->myCurve = Handle(Geom_TrimmedCurve)::DownCast(c->Copy());
 }
