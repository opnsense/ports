--- src/Mod/Part/App/FCBRepAlgoAPI_Section.cpp.orig	2026-07-01 20:50:53 UTC
+++ src/Mod/Part/App/FCBRepAlgoAPI_Section.cpp
@@ -48,10 +48,10 @@ FCBRepAlgoAPI_Section::FCBRepAlgoAPI_Section(
     : BRepAlgoAPI_Section(S1, S2, false)
 {
     if (!BRepCheck_Analyzer(S1).IsValid()) {
-        Standard_ConstructionError::Raise("Base shape is not valid for boolean operation");
+        throw Standard_ConstructionError("Base shape is not valid for boolean operation");
     }
     if (!BRepCheck_Analyzer(S2).IsValid()) {
-        Standard_ConstructionError::Raise("Tool shape is not valid for boolean operation");
+        throw Standard_ConstructionError("Tool shape is not valid for boolean operation");
     }
     setAutoFuzzy();
     SetRunParallel(Standard_True);
@@ -69,7 +69,7 @@ FCBRepAlgoAPI_Section::FCBRepAlgoAPI_Section(
     : BRepAlgoAPI_Section(Sh, Pl, false)
 {
     if (!BRepCheck_Analyzer(Sh).IsValid()) {
-        Standard_ConstructionError::Raise("Base shape is not valid for boolean operation");
+        throw Standard_ConstructionError("Base shape is not valid for boolean operation");
     }
     setAutoFuzzy();
     SetRunParallel(Standard_True);
