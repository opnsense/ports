--- src/Mod/Part/App/PartFeatures.cpp.orig	2026-07-01 20:50:53 UTC
+++ src/Mod/Part/App/PartFeatures.cpp
@@ -39,8 +39,7 @@
 #include <TopoDS_Face.hxx>
 #include <TopoDS_Iterator.hxx>
 #include <TopoDS_Shell.hxx>
-#include <TopTools_HSequenceOfShape.hxx>
-#include <TopTools_ListIteratorOfListOfShape.hxx>
+#include <TopTools_ListOfShape.hxx>
 
 
 #include <App/Link.h>
