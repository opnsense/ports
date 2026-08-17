--- src/3rdParty/salomesmesh/inc/StdMeshers_Distribution.hxx.orig	2026-04-14 22:09:59 UTC
+++ src/3rdParty/salomesmesh/inc/StdMeshers_Distribution.hxx
@@ -34,7 +34,12 @@
 #include <vector>
 #include <math_Function.hxx>
 #include <ExprIntrp_GenExp.hxx>
+#include <Standard_Version.hxx>
+#if OCC_VERSION_HEX >= 0x080000
+#include <Expr_NamedUnknown.hxx>
+#else
 #include <Expr_Array1OfNamedUnknown.hxx>
+#endif
 #include <TColStd_Array1OfReal.hxx>
 
 namespace StdMeshers
@@ -86,6 +91,10 @@ class STDMESHERS_EXPORT FunctionTable : public Functio
 private:
   std::vector<double>  myData;
 };
+
+#if OCC_VERSION_HEX >= 0x080000
+using Expr_Array1OfNamedUnknown = NCollection_Array1<occ::handle<Expr_NamedUnknown>>;
+#endif
 
 class STDMESHERS_EXPORT FunctionExpr : public Function, public math_Function
 {
