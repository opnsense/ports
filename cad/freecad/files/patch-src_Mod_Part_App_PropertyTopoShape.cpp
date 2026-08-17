--- src/Mod/Part/App/PropertyTopoShape.cpp.orig	2026-07-01 20:50:53 UTC
+++ src/Mod/Part/App/PropertyTopoShape.cpp
@@ -33,6 +33,7 @@
 #include <Standard_Failure.hxx>
 #include <Standard_Version.hxx>
 #include <TopoDS.hxx>
+#include <TopTools_IndexedMapOfShape.hxx>
 
 #include <App/Application.h>
 #include <App/Document.h>
