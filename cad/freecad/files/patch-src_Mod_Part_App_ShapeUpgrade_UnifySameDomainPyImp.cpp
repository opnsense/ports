--- src/Mod/Part/App/ShapeUpgrade/UnifySameDomainPyImp.cpp.orig	2026-07-01 20:50:53 UTC
+++ src/Mod/Part/App/ShapeUpgrade/UnifySameDomainPyImp.cpp
@@ -29,6 +29,7 @@
 
 // Needed for OCCT 7.5.2
 #include <TopoDS_Edge.hxx>
+#include <TopTools_MapOfShape.hxx>
 
 #include <Base/PyWrapParseTupleAndKeywords.h>
 
