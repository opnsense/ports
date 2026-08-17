--- src/Mod/Part/App/Geometry2d.cpp.orig	2026-07-02 12:43:46 UTC
+++ src/Mod/Part/App/Geometry2d.cpp
@@ -28,7 +28,12 @@
 #include <Geom2dAPI_ProjectPointOnCurve.hxx>
 #include <Geom2dConvert.hxx>
 #include <Geom2dConvert_CompCurveToBSplineCurve.hxx>
-#include <Geom2dLProp_CLProps2d.hxx>
+#include <Standard_Version.hxx>
+#if OCC_VERSION_HEX >= 0x080000
+# include <GeomLProp_CLProps.hxx>
+#else
+# include <Geom2dLProp_CLProps2d.hxx>
+#endif
 #include <gce_ErrorType.hxx>
 #include <gp_Ax22d.hxx>
 #include <gp_Circ2d.hxx>
@@ -221,7 +226,11 @@ bool Geom2dCurve::tangent(double u, gp_Dir2d& dir) con
 bool Geom2dCurve::tangent(double u, gp_Dir2d& dir) const
 {
     Handle(Geom2d_Curve) c = Handle(Geom2d_Curve)::DownCast(handle());
+#if OCC_VERSION_HEX >= 0x080000
+    GeomLProp_CLProps2d prop(c, u, 2, Precision::Confusion());
+#else
     Geom2dLProp_CLProps2d prop(c, u, 2, Precision::Confusion());
+#endif
     if (prop.IsTangentDefined()) {
         prop.Tangent(dir);
         return true;
@@ -233,7 +242,11 @@ Base::Vector2d Geom2dCurve::pointAtParameter(double u)
 Base::Vector2d Geom2dCurve::pointAtParameter(double u) const
 {
     Handle(Geom2d_Curve) c = Handle(Geom2d_Curve)::DownCast(handle());
+#if OCC_VERSION_HEX >= 0x080000
+    GeomLProp_CLProps2d prop(c, u, 0, Precision::Confusion());
+#else
     Geom2dLProp_CLProps2d prop(c, u, 0, Precision::Confusion());
+#endif
 
     const gp_Pnt2d& point = prop.Value();
     return {point.X(), point.Y()};
@@ -242,7 +255,11 @@ Base::Vector2d Geom2dCurve::firstDerivativeAtParameter
 Base::Vector2d Geom2dCurve::firstDerivativeAtParameter(double u) const
 {
     Handle(Geom2d_Curve) c = Handle(Geom2d_Curve)::DownCast(handle());
+#if OCC_VERSION_HEX >= 0x080000
+    GeomLProp_CLProps2d prop(c, u, 1, Precision::Confusion());
+#else
     Geom2dLProp_CLProps2d prop(c, u, 1, Precision::Confusion());
+#endif
 
     const gp_Vec2d& vec = prop.D1();
     return {vec.X(), vec.Y()};
@@ -251,7 +268,11 @@ Base::Vector2d Geom2dCurve::secondDerivativeAtParamete
 Base::Vector2d Geom2dCurve::secondDerivativeAtParameter(double u) const
 {
     Handle(Geom2d_Curve) c = Handle(Geom2d_Curve)::DownCast(handle());
+#if OCC_VERSION_HEX >= 0x080000
+    GeomLProp_CLProps2d prop(c, u, 2, Precision::Confusion());
+#else
     Geom2dLProp_CLProps2d prop(c, u, 2, Precision::Confusion());
+#endif
 
     const gp_Vec2d& vec = prop.D2();
     return {vec.X(), vec.Y()};
@@ -260,7 +281,11 @@ bool Geom2dCurve::normal(double u, gp_Dir2d& dir) cons
 bool Geom2dCurve::normal(double u, gp_Dir2d& dir) const
 {
     Handle(Geom2d_Curve) c = Handle(Geom2d_Curve)::DownCast(handle());
+#if OCC_VERSION_HEX >= 0x080000
+    GeomLProp_CLProps2d prop(c, u, 2, Precision::Confusion());
+#else
     Geom2dLProp_CLProps2d prop(c, u, 2, Precision::Confusion());
+#endif
     if (prop.IsTangentDefined()) {
         prop.Normal(dir);
         return true;
@@ -466,10 +491,10 @@ void Geom2dBSplineCurve::interpolate(const std::vector
 void Geom2dBSplineCurve::interpolate(const std::vector<gp_Pnt2d>& p, const std::vector<gp_Vec2d>& t)
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
@@ -499,10 +524,10 @@ void Geom2dBSplineCurve::getCardinalSplineTangents(
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
@@ -533,7 +558,7 @@ void Geom2dBSplineCurve::getCardinalSplineTangents(
 {
     // https://de.wikipedia.org/wiki/Kubisch_Hermitescher_Spline#Cardinal_Spline
     if (p.size() < 2) {
-        Standard_ConstructionError::Raise();
+        throw Standard_ConstructionError();
     }
 
     t.resize(p.size());
@@ -563,7 +588,7 @@ std::list<Geometry2d*> Geom2dBSplineCurve::toBiArcs(do
 
 std::list<Geometry2d*> Geom2dBSplineCurve::toBiArcs(double /*tolerance*/) const
 {
-    Standard_Failure::Raise("Not yet implemented");
+    throw Standard_Failure("Not yet implemented");
     return {};
 }
 
@@ -960,7 +985,7 @@ void Geom2dArcOfCircle::setHandle(const Handle(Geom2d_
 {
     Handle(Geom2d_Circle) basis = Handle(Geom2d_Circle)::DownCast(c->BasisCurve());
     if (basis.IsNull()) {
-        Standard_Failure::Raise("Basis curve is not a circle");
+        throw Standard_Failure("Basis curve is not a circle");
     }
     this->myCurve = Handle(Geom2d_TrimmedCurve)::DownCast(c->Copy());
 }
@@ -1238,7 +1263,7 @@ void Geom2dArcOfEllipse::setHandle(const Handle(Geom2d
 {
     Handle(Geom2d_Ellipse) basis = Handle(Geom2d_Ellipse)::DownCast(c->BasisCurve());
     if (basis.IsNull()) {
-        Standard_Failure::Raise("Basis curve is not an ellipse");
+        throw Standard_Failure("Basis curve is not an ellipse");
     }
     this->myCurve = Handle(Geom2d_TrimmedCurve)::DownCast(c->Copy());
 }
@@ -1534,7 +1559,7 @@ void Geom2dArcOfHyperbola::setHandle(const Handle(Geom
 {
     Handle(Geom2d_Hyperbola) basis = Handle(Geom2d_Hyperbola)::DownCast(c->BasisCurve());
     if (basis.IsNull()) {
-        Standard_Failure::Raise("Basis curve is not an hyperbola");
+        throw Standard_Failure("Basis curve is not an hyperbola");
     }
     this->myCurve = Handle(Geom2d_TrimmedCurve)::DownCast(c->Copy());
 }
@@ -1775,7 +1800,7 @@ void Geom2dArcOfParabola::setHandle(const Handle(Geom2
 {
     Handle(Geom2d_Parabola) basis = Handle(Geom2d_Parabola)::DownCast(c->BasisCurve());
     if (basis.IsNull()) {
-        Standard_Failure::Raise("Basis curve is not a parabola");
+        throw Standard_Failure("Basis curve is not a parabola");
     }
     this->myCurve = Handle(Geom2d_TrimmedCurve)::DownCast(c->Copy());
 }
@@ -2001,7 +2026,7 @@ void Geom2dLineSegment::setHandle(const Handle(Geom2d_
 {
     Handle(Geom2d_Line) basis = Handle(Geom2d_Line)::DownCast(c->BasisCurve());
     if (basis.IsNull()) {
-        Standard_Failure::Raise("Basis curve is not a line");
+        throw Standard_Failure("Basis curve is not a line");
     }
     this->myCurve = Handle(Geom2d_TrimmedCurve)::DownCast(c->Copy());
 }
@@ -2040,7 +2065,7 @@ void Geom2dLineSegment::setPoints(const Base::Vector2d
     try {
         // Create line out of two points
         if (p1.Distance(p2) < gp::Resolution()) {
-            Standard_Failure::Raise("Both points are equal");
+            throw Standard_Failure("Both points are equal");
         }
         GCE2d_MakeSegment ms(p1, p2);
         if (!ms.IsDone()) {
