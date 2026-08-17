--- src/Mod/Part/App/PrimitiveFeature.cpp.orig	2026-07-02 08:28:36 UTC
+++ src/Mod/Part/App/PrimitiveFeature.cpp
@@ -914,11 +914,11 @@ App::DocumentObjectExecReturn* Helix::execute()
         Standard_Boolean myLocalCS = LocalCoord.getValue() ? Standard_True : Standard_False;
         Standard_Real mySegLen = SegmentLength.getValue();
         if (myPitch < Precision::Confusion()) {
-            Standard_Failure::Raise("Pitch too small");
+            throw Standard_Failure("Pitch too small");
         }
         Standard_Real nbTurns = myHeight / myPitch;
         if (nbTurns > 1e4) {
-            Standard_Failure::Raise("Number of turns too high (> 1e4)");
+            throw Standard_Failure("Number of turns too high (> 1e4)");
         }
         Standard_Real myRadiusTop = myRadius + myHeight * tan(Base::toRadians<double>(myAngle));
 
@@ -1001,7 +1001,7 @@ App::DocumentObjectExecReturn* Spiral::execute()
         Standard_Real mySegLen = SegmentLength.getValue();
 
         if (myNumRot < Precision::Confusion()) {
-            Standard_Failure::Raise("Number of rotations too small");
+            throw Standard_Failure("Number of rotations too small");
         }
 
         this->Shape.setValue(
