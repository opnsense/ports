--- src/Mod/Part/App/FCBRepAlgoAPI_BooleanOperation.cpp.orig	2026-07-01 20:30:18 UTC
+++ src/Mod/Part/App/FCBRepAlgoAPI_BooleanOperation.cpp
@@ -104,7 +104,7 @@ void FCBRepAlgoAPI_BooleanOperation::Build(const Messa
 void FCBRepAlgoAPI_BooleanOperation::Build(const Message_ProgressRange& progressRange)
 {
     if (progressRange.UserBreak()) {
-        Standard_ConstructionError::Raise("User aborted");
+        throw Standard_ConstructionError("User aborted");
     }
     if (myOperation == BOPAlgo_CUT && myArguments.Size() == 1 && myTools.Size() == 1
         && myTools.First().ShapeType() == TopAbs_COMPOUND) {
@@ -130,7 +130,7 @@ void FCBRepAlgoAPI_BooleanOperation::Build(const Messa
 #endif
     }
     if (progressRange.UserBreak()) {
-        Standard_ConstructionError::Raise("User aborted");
+        throw Standard_ConstructionError("User aborted");
     }
 }
 
