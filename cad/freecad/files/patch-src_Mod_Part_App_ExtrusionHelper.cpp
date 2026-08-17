--- src/Mod/Part/App/ExtrusionHelper.cpp.orig	2026-07-01 20:50:53 UTC
+++ src/Mod/Part/App/ExtrusionHelper.cpp
@@ -92,13 +92,13 @@ void ExtrusionHelper::makeDraft(
     bool bMid = !bFwd || !bRev || -1.0 * AngleFwd != AngleRev;
 
     if (shape.IsNull()) {
-        Standard_Failure::Raise("Not a valid shape");
+        throw Standard_Failure("Not a valid shape");
     }
 
     // store all wires of the shape into an array
     size_t numWires = addWiresToWireSections(wiresections);
     if (numWires == 0) {
-        Standard_Failure::Raise("Extrusion: Input must not only consist if a vertex");
+        throw Standard_Failure("Extrusion: Input must not only consist if a vertex");
     }
 
     // to store the sections for the loft
@@ -128,7 +128,7 @@ void ExtrusionHelper::makeDraft(
             auto tempFace = mkFace.Shape();
             BRepPrimAPI_MakePrism mkPrism(tempFace, vecFwd);
             if (!mkPrism.IsDone()) {
-                Standard_Failure::Raise("Extrusion: Generating prism failed");
+                throw Standard_Failure("Extrusion: Generating prism failed");
             }
             singlePrism = mkPrism.Shape();
             resultPrisms.push_back(singlePrism);
@@ -287,7 +287,7 @@ void ExtrusionHelper::makeDraft(
             }
             mkTS.Build();
             if (!mkTS.IsDone()) {
-                Standard_Failure::Raise("Extrusion: Loft could not be built");
+                throw Standard_Failure("Extrusion: Loft could not be built");
             }
 
             shells.push_back(mkTS.Shape());
@@ -321,7 +321,7 @@ void ExtrusionHelper::makeDraft(
                         );
                         FCBRepAlgoAPI_Cut mkCut(*itOuter, *itInner);
                         if (!mkCut.IsDone()) {
-                            Standard_Failure::Raise("Extrusion: Final cut out failed");
+                            throw Standard_Failure("Extrusion: Final cut out failed");
                         }
                         BRepGProp::VolumeProperties(mkCut.Shape(), tempProperties);
                         momentOfInertiaFinal = tempProperties.MomentOfInertia(
@@ -415,7 +415,7 @@ void ExtrusionHelper::checkInnerWires(
             momentOfInertiaInitial = tempProperties.MomentOfInertia(gp_Ax1(gp_Pnt(), direction));
             FCBRepAlgoAPI_Cut mkCut(*itInner, *itOuter);
             if (!mkCut.IsDone()) {
-                Standard_Failure::Raise("Extrusion: Cut out failed");
+                throw Standard_Failure("Extrusion: Cut out failed");
             }
             BRepGProp::VolumeProperties(mkCut.Shape(), tempProperties);
             momentOfInertiaFinal = tempProperties.MomentOfInertia(gp_Ax1(gp_Pnt(), direction));
@@ -520,7 +520,7 @@ void ExtrusionHelper::createTaperedPrismOffset(
             throw Base::RuntimeError(e.what());
         }
         if (!mkOffset.IsDone()) {
-            Standard_Failure::Raise("Extrusion: Offset could not be created");
+            throw Standard_Failure("Extrusion: Offset could not be created");
         }
     }
     else {
@@ -539,7 +539,7 @@ void ExtrusionHelper::createTaperedPrismOffset(
                 "This means most probably that the along taper angle is too large or small.\n"
             );
         }
-        Standard_Failure::Raise("Extrusion: end face of tapered extrusion is empty");
+        throw Standard_Failure("Extrusion: end face of tapered extrusion is empty");
     }
     // assure we return a wire and no edge
     TopAbs_ShapeEnum type = offsetShape.ShapeType();
@@ -592,7 +592,7 @@ void ExtrusionHelper::makeElementDraft(
     TopoShape shape = _shape;
     TopoShape sourceWire;
     if (shape.isNull()) {
-        Standard_Failure::Raise("Not a valid shape");
+        throw Standard_Failure("Not a valid shape");
     }
 
     if (params.solid && !shape.hasSubShape(TopAbs_FACE)) {
@@ -603,7 +603,7 @@ void ExtrusionHelper::makeElementDraft(
         std::vector<TopoShape> wires;
         TopoShape outerWire = shape.splitWires(&wires, TopoShape::ReorientForward);
         if (outerWire.isNull()) {
-            Standard_Failure::Raise("Missing outer wire");
+            throw Standard_Failure("Missing outer wire");
         }
         if (wires.empty()) {
             shape = outerWire;
@@ -612,7 +612,7 @@ void ExtrusionHelper::makeElementDraft(
             unsigned pos = drafts.size();
             makeElementDraft(params, outerWire, drafts, hasher);
             if (drafts.size() != pos + 1) {
-                Standard_Failure::Raise("Failed to make drafted extrusion");
+                throw Standard_Failure("Failed to make drafted extrusion");
             }
             std::vector<TopoShape> inner;
             // Inner wires are lofted into separate solids and then cut from the
@@ -626,7 +626,7 @@ void ExtrusionHelper::makeElementDraft(
                 makeElementDraft(innerParams, innerWire, inner, hasher);
             }
             if (inner.empty()) {
-                Standard_Failure::Raise("Failed to make drafted extrusion with inner hole");
+                throw Standard_Failure("Failed to make drafted extrusion with inner hole");
             }
             inner.insert(inner.begin(), drafts.back());
             drafts.back().makeElementCut(inner);
@@ -650,7 +650,7 @@ void ExtrusionHelper::makeElementDraft(
         }
     }
     else {
-        Standard_Failure::Raise("Only a wire or a face is supported");
+        throw Standard_Failure("Only a wire or a face is supported");
     }
 
     if (!sourceWire.isNull()) {
