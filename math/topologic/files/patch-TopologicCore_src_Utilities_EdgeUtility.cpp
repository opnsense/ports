--- TopologicCore/src/Utilities/EdgeUtility.cpp.orig	2024-05-05 07:38:08 UTC
+++ TopologicCore/src/Utilities/EdgeUtility.cpp
@@ -54,7 +54,7 @@ namespace TopologicUtilities
 		else
 		{
 			// else more than 2 vertices
-			Handle(TColgp_HArray1OfPnt) pOcctPoints = new TColgp_HArray1OfPnt(1, numberOfVertices);
+			Handle(NCollection_HArray1<gp_Pnt>) pOcctPoints = new NCollection_HArray1<gp_Pnt>(1, numberOfVertices);
 			int i = 1;
 			for (const TopologicCore::Vertex::Ptr& kpVertex : rkVertices)
 			{
