--- src/Mod/Surface/App/FeatureSewing.cpp.orig	2026-07-02 13:42:30 UTC
+++ src/Mod/Surface/App/FeatureSewing.cpp
@@ -84,7 +84,7 @@ App::DocumentObjectExecReturn* Sewing::execute()
                 }
             }
             else {
-                Standard_Failure::Raise("Shape item not from Part::Feature");
+                throw Standard_Failure("Shape item not from Part::Feature");
             }
         }
 
