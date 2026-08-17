--- TopologicCore/src/CellComplex.cpp.orig	2024-05-05 07:38:08 UTC
+++ TopologicCore/src/CellComplex.cpp
@@ -113,7 +113,7 @@ namespace TopologicCore
 
 		occtBuilder.MakeCompSolid(occtCompSolid);
 
-		TopTools_ListOfShape::iterator occtSolidIterator = rkOcctSolids.begin();
+		TopTools_ListOfShape::const_iterator occtSolidIterator = rkOcctSolids.begin();
 		CellComplex::Ptr pCellComplex = nullptr;
 
 		// If there is only one solid, create a CellComplex with only that cells
@@ -264,7 +264,7 @@ namespace TopologicCore
 
 		TopTools_ListOfShape occtListToTake;
 		TopTools_ListOfShape occtListToAvoid;
-		for (TopTools_ListIteratorOfListOfShape occtShapeIterator(occtCellsBuildersArguments);
+		for (TopTools_ListOfShape::Iterator occtShapeIterator(occtCellsBuildersArguments);
 			occtShapeIterator.More();
 			occtShapeIterator.Next())
 		{
