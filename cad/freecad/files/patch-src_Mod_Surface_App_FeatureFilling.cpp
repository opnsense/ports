--- src/Mod/Surface/App/FeatureFilling.cpp.orig	2026-07-02 13:42:30 UTC
+++ src/Mod/Surface/App/FeatureFilling.cpp
@@ -165,7 +165,7 @@ void Filling::addConstraints(
                                 builder.Add(TopoDS::Edge(edge), cont, bnd);
                             }
                             else {
-                                Standard_Failure::Raise(
+                                throw Standard_Failure(
                                     "Boundary edges must be added in a consecutive order"
                                 );
                             }
@@ -185,25 +185,25 @@ void Filling::addConstraints(
                                     builder.Add(TopoDS::Edge(edge), TopoDS::Face(face), cont, bnd);
                                 }
                                 else {
-                                    Standard_Failure::Raise(
+                                    throw Standard_Failure(
                                         "Boundary edges must be added in a consecutive order"
                                     );
                                 }
                             }
                         }
                         else {
-                            Standard_Failure::Raise("Sub-shape is not a face");
+                            throw Standard_Failure("Sub-shape is not a face");
                         }
                     }
                 }
                 else {
-                    Standard_Failure::Raise("Sub-shape is not an edge");
+                    throw Standard_Failure("Sub-shape is not an edge");
                 }
             }
         }
     }
     else {
-        Standard_Failure::Raise("Number of links does not match with the number of orders");
+        throw Standard_Failure("Number of links does not match with the number of orders");
     }
 }
 
@@ -230,13 +230,13 @@ void Filling::addConstraints(
                     builder.Add(TopoDS::Face(face), cont);
                 }
                 else {
-                    Standard_Failure::Raise("Sub-shape is not a face");
+                    throw Standard_Failure("Sub-shape is not a face");
                 }
             }
         }
     }
     else {
-        Standard_Failure::Raise("Number of links does not match with the number of orders");
+        throw Standard_Failure("Number of links does not match with the number of orders");
     }
 }
 
@@ -319,7 +319,7 @@ App::DocumentObjectExecReturn* Filling::execute()
             builder.Build();
         }
         if (!builder.IsDone()) {
-            Standard_Failure::Raise("Failed to create a face from constraints");
+            throw Standard_Failure("Failed to create a face from constraints");
         }
 
         // Return the face
