--- src/3rdParty/salomesmesh/src/StdMeshers/StdMeshers_NumberOfSegments.cpp.orig	2026-07-01 16:20:28 UTC
+++ src/3rdParty/salomesmesh/src/StdMeshers/StdMeshers_NumberOfSegments.cpp
@@ -34,12 +34,20 @@
 #include "SMESH_Comment.hxx"
 
 #include <ExprIntrp_GenExp.hxx>
+#include <Standard_Version.hxx>
+#if OCC_VERSION_HEX < 0x080000
 #include <Expr_Array1OfNamedUnknown.hxx>
+#endif
 #include <Expr_NamedUnknown.hxx>
 #include <TColStd_Array1OfReal.hxx>
 #include <TCollection_AsciiString.hxx>
 #include <TopExp.hxx>
 #include <TopTools_IndexedMapOfShape.hxx>
+
+
+#if OCC_VERSION_HEX >= 0x080000
+using Expr_Array1OfNamedUnknown = NCollection_Array1<occ::handle<Expr_NamedUnknown>>;
+#endif
 
 #if (OCC_VERSION_MAJOR << 16 | OCC_VERSION_MINOR << 8 | OCC_VERSION_MAINTENANCE) > 0x060100
 #define NO_CAS_CATCH
