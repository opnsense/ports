--- src/Mod/Part/App/Geom2d/Curve2dPyImp.cpp.orig	2026-07-02 12:13:06 UTC
+++ src/Mod/Part/App/Geom2d/Curve2dPyImp.cpp
@@ -24,6 +24,7 @@
 
 #include <sstream>
 
+#include <Standard_Version.hxx>
 #include <BRepAdaptor_Curve.hxx>
 #include <BRepAdaptor_Surface.hxx>
 #include <BRepBuilderAPI_MakeEdge.hxx>
@@ -44,7 +45,11 @@
 #include <Geom2dAPI_InterCurveCurve.hxx>
 #include <Geom2dAPI_ProjectPointOnCurve.hxx>
 #include <Geom2dConvert_ApproxCurve.hxx>
-#include <Geom2dLProp_CLProps2d.hxx>
+#if OCC_VERSION_HEX >= 0x080000
+# include <GeomLProp_CLProps.hxx>
+#else
+# include <Geom2dLProp_CLProps2d.hxx>
+#endif
 #include <gp_Dir2d.hxx>
 #include <Precision.hxx>
 #include <ShapeConstruct_Curve.hxx>
@@ -602,7 +607,11 @@ PyObject* Curve2dPy::tangent(PyObject* args)
                 return nullptr;
             }
             gp_Dir2d dir;
+#if OCC_VERSION_HEX >= 0x080000
+            GeomLProp_CLProps2d prop(c, u, 2, Precision::Confusion());
+#else
             Geom2dLProp_CLProps2d prop(c, u, 2, Precision::Confusion());
+#endif
             if (prop.IsTangentDefined()) {
                 prop.Tangent(dir);
             }
@@ -630,7 +639,11 @@ PyObject* Curve2dPy::normal(PyObject* args) const
                 return nullptr;
             }
             gp_Dir2d dir;
+#if OCC_VERSION_HEX >= 0x080000
+            GeomLProp_CLProps2d prop(c, u, 2, Precision::Confusion());
+#else
             Geom2dLProp_CLProps2d prop(c, u, 2, Precision::Confusion());
+#endif
             prop.Normal(dir);
 
             return Py::new_reference_to(Base::Vector2dPy::create(dir.X(), dir.Y()));
@@ -655,7 +668,11 @@ PyObject* Curve2dPy::curvature(PyObject* args) const
             if (!PyArg_ParseTuple(args, "d", &u)) {
                 return nullptr;
             }
+#if OCC_VERSION_HEX >= 0x080000
+            GeomLProp_CLProps2d prop(c, u, 2, Precision::Confusion());
+#else
             Geom2dLProp_CLProps2d prop(c, u, 2, Precision::Confusion());
+#endif
             double C = prop.Curvature();
             return Py::new_reference_to(Py::Float(C));
         }
@@ -679,7 +696,11 @@ PyObject* Curve2dPy::centerOfCurvature(PyObject* args)
             if (!PyArg_ParseTuple(args, "d", &u)) {
                 return nullptr;
             }
+#if OCC_VERSION_HEX >= 0x080000
+            GeomLProp_CLProps2d prop(c, u, 2, Precision::Confusion());
+#else
             Geom2dLProp_CLProps2d prop(c, u, 2, Precision::Confusion());
+#endif
             gp_Pnt2d pnt;
             prop.CentreOfCurvature(pnt);
 
@@ -737,7 +758,7 @@ PyObject* Curve2dPy::toBSpline(PyObject* args)
             ShapeConstruct_Curve scc;
             Handle(Geom2d_BSplineCurve) spline = scc.ConvertToBSpline(c, u, v, Precision::Confusion());
             if (spline.IsNull()) {
-                Standard_NullValue::Raise("Conversion to B-spline failed");
+                throw Standard_NullValue("Conversion to B-spline failed");
             }
             return new BSplineCurve2dPy(new Geom2dBSplineCurve(spline));
         }
