--- TopologicCore/src/Graph.cpp.orig	2024-05-05 07:38:08 UTC
+++ TopologicCore/src/Graph.cpp
@@ -999,7 +999,7 @@ namespace TopologicCore
 		}
 
         std::queue<TopoDS_Vertex> occtVertexQueue;
-        TopTools_DataMapOfShapeInteger occtVertexDistanceMap; // also to check if the vertex is processed
+        NCollection_DataMap<TopoDS_Shape, Standard_Integer, TopTools_ShapeMapHasher> occtVertexDistanceMap; // also to check if the vertex is processed
         
         occtVertexQueue.push(occtCoincidentStartVertex);
         
@@ -1021,7 +1021,7 @@ namespace TopologicCore
             {
                 const TopoDS_Vertex& rkOcctAdjacentVertex = TopoDS::Vertex(occtVertexAdjacency.Value());
                 try {
-                    const int& rDistance = occtVertexDistanceMap.Find(rkOcctAdjacentVertex);
+                    const Standard_Integer& rDistance = occtVertexDistanceMap.Find(rkOcctAdjacentVertex);
 
                     // vertex is already processed, so continue.
                     continue; 
