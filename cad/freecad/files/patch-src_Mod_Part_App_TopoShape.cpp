--- src/Mod/Part/App/TopoShape.cpp.orig	2026-07-01 20:30:18 UTC
+++ src/Mod/Part/App/TopoShape.cpp
@@ -56,8 +56,8 @@
 #include <BRepBuilderAPI_Sewing.hxx>
 #include <BRepBuilderAPI_Transform.hxx>
 #include <BRepCheck_Analyzer.hxx>
+#include <BRepCheck_ListOfStatus.hxx>
 #include <BRepClass_FaceClassifier.hxx>
-#include <BRepCheck_ListIteratorOfListOfStatus.hxx>
 #include <BRepCheck_Result.hxx>
 #include <BRepFill_CompatibleWires.hxx>
 #include <BRepGProp.hxx>
@@ -139,10 +139,10 @@
 #include <TopoDS_Vertex.hxx>
 #include <TopExp.hxx>
 #include <TopExp_Explorer.hxx>
-#include <TopTools_ListIteratorOfListOfShape.hxx>
 #include <TopTools_HSequenceOfShape.hxx>
 #include <Transfer_FinderProcess.hxx>
 #include <Transfer_TransientProcess.hxx>
+#include <TColgp_Array1OfPnt.hxx>
 #include <XSControl_TransferWriter.hxx>
 #include <XSControl_WorkSession.hxx>
 
@@ -1855,7 +1855,7 @@ TopoDS_Shape TopoShape::fuse(const std::vector<TopoDS_
 TopoDS_Shape TopoShape::fuse(const std::vector<TopoDS_Shape>& shapes, Standard_Real tolerance) const
 {
     if (this->_Shape.IsNull()) {
-        Standard_Failure::Raise("Base shape is null");
+        throw Standard_Failure("Base shape is null");
     }
 
     FCBRepAlgoAPI_Fuse mkFuse;
@@ -1893,10 +1893,10 @@ TopoDS_Shape TopoShape::section(TopoDS_Shape shape, St
 TopoDS_Shape TopoShape::section(TopoDS_Shape shape, Standard_Boolean approximate) const
 {
     if (this->_Shape.IsNull()) {
-        Standard_Failure::Raise("Base shape is null");
+        throw Standard_Failure("Base shape is null");
     }
     if (shape.IsNull()) {
-        Standard_Failure::Raise("Tool shape is null");
+        throw Standard_Failure("Tool shape is null");
     }
     FCBRepAlgoAPI_Section mkSection;
     mkSection.Init1(this->_Shape);
@@ -1920,7 +1920,7 @@ TopoDS_Shape TopoShape::section(
 ) const
 {
     if (this->_Shape.IsNull()) {
-        Standard_Failure::Raise("Base shape is null");
+        throw Standard_Failure("Base shape is null");
     }
 
     FCBRepAlgoAPI_Section mkSection;
@@ -1994,7 +1994,7 @@ TopoDS_Shape TopoShape::generalFuse(
 ) const
 {
     if (this->_Shape.IsNull()) {
-        Standard_Failure::Raise("Base shape is null");
+        throw Standard_Failure("Base shape is null");
     }
 
     BRepAlgoAPI_BuilderAlgo mkGFA;
@@ -2036,13 +2036,13 @@ TopoDS_Shape TopoShape::makePipe(const TopoDS_Shape& p
 TopoDS_Shape TopoShape::makePipe(const TopoDS_Shape& profile) const
 {
     if (this->_Shape.IsNull()) {
-        Standard_Failure::Raise("Cannot sweep along empty spine");
+        throw Standard_Failure("Cannot sweep along empty spine");
     }
     if (this->_Shape.ShapeType() != TopAbs_WIRE) {
-        Standard_Failure::Raise("Spine shape is not a wire");
+        throw Standard_Failure("Spine shape is not a wire");
     }
     if (profile.IsNull()) {
-        Standard_Failure::Raise("Cannot sweep empty profile");
+        throw Standard_Failure("Cannot sweep empty profile");
     }
     BRepOffsetAPI_MakePipe mkPipe(TopoDS::Wire(this->_Shape), profile);
     return mkPipe.Shape();
@@ -2056,10 +2056,10 @@ TopoDS_Shape TopoShape::makePipeShell(
 ) const
 {
     if (this->_Shape.IsNull()) {
-        Standard_Failure::Raise("Cannot sweep along empty spine");
+        throw Standard_Failure("Cannot sweep along empty spine");
     }
     if (this->_Shape.ShapeType() != TopAbs_WIRE) {
-        Standard_Failure::Raise("Spine shape is not a wire");
+        throw Standard_Failure("Spine shape is not a wire");
     }
 
     BRepOffsetAPI_MakePipeShell mkPipeShell(TopoDS::Wire(this->_Shape));
@@ -2124,7 +2124,7 @@ TopoDS_Shape TopoShape::makeTube(double radius, double
     Standard_Integer theMaxSegment = maxsegm;
 
     if (this->_Shape.IsNull()) {
-        Standard_Failure::Raise("Cannot sweep along empty spine");
+        throw Standard_Failure("Cannot sweep along empty spine");
     }
 
 #if OCC_VERSION_HEX >= 0x070600
@@ -2145,7 +2145,7 @@ TopoDS_Shape TopoShape::makeTube(double radius, double
 #endif
 
     else {
-        Standard_Failure::Raise("Spine shape is not an edge");
+        throw Standard_Failure("Spine shape is not an edge");
     }
 
     // circular profile
@@ -2180,17 +2180,17 @@ TopoDS_Shape TopoShape::makeSweep(const TopoDS_Shape& 
 {
     // http://opencascade.blogspot.com/2009/10/surface-modeling-part2.html
     if (this->_Shape.IsNull()) {
-        Standard_Failure::Raise("Cannot sweep along empty spine");
+        throw Standard_Failure("Cannot sweep along empty spine");
     }
     if (this->_Shape.ShapeType() != TopAbs_EDGE) {
-        Standard_Failure::Raise("Spine shape is not an edge");
+        throw Standard_Failure("Spine shape is not an edge");
     }
 
     if (profile.IsNull()) {
-        Standard_Failure::Raise("Cannot sweep with empty profile");
+        throw Standard_Failure("Cannot sweep with empty profile");
     }
     if (profile.ShapeType() != TopAbs_EDGE) {
-        Standard_Failure::Raise("Profile shape is not an edge");
+        throw Standard_Failure("Profile shape is not an edge");
     }
 
     const TopoDS_Edge& path_edge = TopoDS::Edge(this->_Shape);
@@ -2206,7 +2206,7 @@ TopoDS_Shape TopoShape::makeSweep(const TopoDS_Shape& 
     hPath = Handle(Geom_Curve)::DownCast(hPath->Transformed(loc1.Transformation()));
 
     if (hPath.IsNull()) {
-        Standard_Failure::Raise("invalid curve in path edge");
+        throw Standard_Failure("invalid curve in path edge");
     }
 
     BRepAdaptor_Curve prof_adapt(prof_edge);
@@ -2219,7 +2219,7 @@ TopoDS_Shape TopoShape::makeSweep(const TopoDS_Shape& 
     hProfile = Handle(Geom_Curve)::DownCast(hProfile->Transformed(loc2.Transformation()));
 
     if (hProfile.IsNull()) {
-        Standard_Failure::Raise("invalid curve in profile edge");
+        throw Standard_Failure("invalid curve in profile edge");
     }
 
     GeomFill_Pipe mkSweep(hPath, hProfile, static_cast<GeomFill_Trihedron>(fillMode));
@@ -2287,29 +2287,29 @@ TopoDS_Shape TopoShape::makeHelix(
     using std::numbers::pi;
 
     if (fabs(pitch) < Precision::Confusion()) {
-        Standard_Failure::Raise("Pitch of helix too small");
+        throw Standard_Failure("Pitch of helix too small");
     }
 
     if (fabs(height) < Precision::Confusion()) {
-        Standard_Failure::Raise("Height of helix too small");
+        throw Standard_Failure("Height of helix too small");
     }
 
     if ((height > 0 && pitch < 0) || (height < 0 && pitch > 0)) {
-        Standard_Failure::Raise("Pitch and height of helix not compatible");
+        throw Standard_Failure("Pitch and height of helix not compatible");
     }
 
     gp_Ax2 cylAx2(gp_Pnt(0.0, 0.0, 0.0), gp::DZ());
     Handle(Geom_Surface) surf;
     if (angle < Precision::Confusion()) {
         if (radius < Precision::Confusion()) {
-            Standard_Failure::Raise("Radius of helix too small");
+            throw Standard_Failure("Radius of helix too small");
         }
         surf = new Geom_CylindricalSurface(cylAx2, radius);
     }
     else {
         angle = Base::toRadians(angle);
         if (angle < Precision::Confusion()) {
-            Standard_Failure::Raise("Angle of helix too small");
+            throw Standard_Failure("Angle of helix too small");
         }
         surf = new Geom_ConicalSurface(gp_Ax3(cylAx2), angle, radius);
     }
@@ -2361,11 +2361,11 @@ TopoDS_Shape TopoShape::makeLongHelix(
     using std::numbers::pi;
 
     if (pitch < Precision::Confusion()) {
-        Standard_Failure::Raise("Pitch of helix too small");
+        throw Standard_Failure("Pitch of helix too small");
     }
 
     if (height < Precision::Confusion()) {
-        Standard_Failure::Raise("Height of helix too small");
+        throw Standard_Failure("Height of helix too small");
     }
 
     gp_Ax2 cylAx2(gp_Pnt(0.0, 0.0, 0.0), gp::DZ());
@@ -2374,7 +2374,7 @@ TopoDS_Shape TopoShape::makeLongHelix(
 
     if (std::fabs(angle) < Precision::Confusion()) {  // Cylindrical helix
         if (radius < Precision::Confusion()) {
-            Standard_Failure::Raise("Radius of helix too small");
+            throw Standard_Failure("Radius of helix too small");
         }
         surf = new Geom_CylindricalSurface(cylAx2, radius);
         isCylinder = true;
@@ -2451,13 +2451,13 @@ TopoDS_Shape TopoShape::makeSpiralHelix(
     // 1000 periods is an OCCT limit. The 3D curve gets truncated
     // if the 2D curve spans beyond this limit.
     if ((breakperiod < 0) || (breakperiod > 1000)) {
-        Standard_Failure::Raise("Break period must be in [0, 1000]");
+        throw Standard_Failure("Break period must be in [0, 1000]");
     }
     if (breakperiod == 0) {
         breakperiod = 1000;
     }
     if (nbturns <= 0) {
-        Standard_Failure::Raise("Number of turns must be greater than 0");
+        throw Standard_Failure("Number of turns must be greater than 0");
     }
 
     Standard_Real nbPeriods = nbturns / breakperiod;
@@ -2517,19 +2517,19 @@ TopoDS_Shape TopoShape::makeThread(
 {
     using std::numbers::pi;
     if (pitch < Precision::Confusion()) {
-        Standard_Failure::Raise("Pitch of thread too small");
+        throw Standard_Failure("Pitch of thread too small");
     }
 
     if (depth < Precision::Confusion()) {
-        Standard_Failure::Raise("Depth of thread too small");
+        throw Standard_Failure("Depth of thread too small");
     }
 
     if (height < Precision::Confusion()) {
-        Standard_Failure::Raise("Height of thread too small");
+        throw Standard_Failure("Height of thread too small");
     }
 
     if (radius < Precision::Confusion()) {
-        Standard_Failure::Raise("Radius of thread too small");
+        throw Standard_Failure("Radius of thread too small");
     }
 
     // Threading : Create Surfaces
@@ -2609,7 +2609,7 @@ TopoDS_Shape TopoShape::makeLoft(
     }
 
     if (countShapes < 2) {
-        Standard_Failure::Raise("Need at least two vertices, edges or wires to create loft face");
+        throw Standard_Failure("Need at least two vertices, edges or wires to create loft face");
     }
     else {
         // close loft by duplicating initial profile as last profile.  not perfect.
@@ -2651,7 +2651,7 @@ TopoDS_Shape TopoShape::makeLoft(
     aGenerator.Build();
 #endif
     if (!aGenerator.IsDone()) {
-        Standard_Failure::Raise("Failed to create loft face");
+        throw Standard_Failure("Failed to create loft face");
     }
 
     // Base::Console().message("DEBUG: TopoShape::makeLoft returns.\n");
@@ -2661,7 +2661,7 @@ TopoDS_Shape TopoShape::makePrism(const gp_Vec& vec) c
 TopoDS_Shape TopoShape::makePrism(const gp_Vec& vec) const
 {
     if (this->_Shape.IsNull()) {
-        Standard_Failure::Raise("cannot sweep empty shape");
+        throw Standard_Failure("cannot sweep empty shape");
     }
     BRepPrimAPI_MakePrism mkPrism(this->_Shape, vec);
     return mkPrism.Shape();
@@ -2670,7 +2670,7 @@ TopoDS_Shape TopoShape::revolve(const gp_Ax1& axis, do
 TopoDS_Shape TopoShape::revolve(const gp_Ax1& axis, double d, Standard_Boolean isSolid) const
 {
     if (this->_Shape.IsNull()) {
-        Standard_Failure::Raise("cannot revolve empty shape");
+        throw Standard_Failure("cannot revolve empty shape");
     }
 
     TopoDS_Face f;
@@ -2755,7 +2755,7 @@ TopoDS_Shape TopoShape::makeOffsetShape(
     );
 
     if (!mkOffset.IsDone()) {
-        Standard_Failure::Raise("BRepOffsetAPI_MakeOffsetShape not done");
+        throw Standard_Failure("BRepOffsetAPI_MakeOffsetShape not done");
     }
     const TopoDS_Shape& res = mkOffset.Shape();
     if (!fill) {
@@ -2767,7 +2767,7 @@ TopoDS_Shape TopoShape::makeOffsetShape(
     ShapeAnalysis_FreeBoundsProperties freeCheck(this->_Shape);
     freeCheck.Perform();
     if (freeCheck.NbClosedFreeBounds() < 1) {
-        Standard_Failure::Raise("no closed bounds");
+        throw Standard_Failure("no closed bounds");
     }
 
     BRep_Builder builder;
@@ -2783,7 +2783,7 @@ TopoDS_Shape TopoShape::makeOffsetShape(
         TopExp_Explorer xp;
         for (xp.Init(originalWire, TopAbs_EDGE); xp.More(); xp.Next()) {
             if (!img.HasImage(xp.Current())) {
-                Standard_Failure::Raise("no image for shape");
+                throw Standard_Failure("no image for shape");
             }
             const TopTools_ListOfShape& currentImage = img.Image(xp.Current());
             TopTools_ListIteratorOfListOfShape listIt;
@@ -2800,7 +2800,7 @@ TopoDS_Shape TopoShape::makeOffsetShape(
             if (edgeCount != 1) {
                 std::ostringstream stream;
                 stream << "wrong edge count: " << edgeCount << std::endl;
-                Standard_Failure::Raise(stream.str().c_str());
+                throw Standard_Failure(stream.str().c_str());
             }
             builder.Add(offsetWire, mappedEdge);
         }
@@ -2817,7 +2817,7 @@ TopoDS_Shape TopoShape::makeOffsetShape(
         aGenerator.Build();
 #endif
         if (!aGenerator.IsDone()) {
-            Standard_Failure::Raise("ThruSections failed");
+            throw Standard_Failure("ThruSections failed");
         }
 
         builder.Add(perimeterCompound, aGenerator.Shape());
@@ -3259,7 +3259,7 @@ void TopoShape::transformGeometry(const Base::Matrix4D
 {
     try {
         if (this->_Shape.IsNull()) {
-            Standard_Failure::Raise("Cannot transform null shape");
+            throw Standard_Failure("Cannot transform null shape");
         }
 
         *this = makeGTransform(rclMat);
@@ -3296,7 +3296,7 @@ TopoDS_Shape TopoShape::transformGShape(const Base::Ma
 TopoDS_Shape TopoShape::transformGShape(const Base::Matrix4D& rclTrf, bool copy) const
 {
     if (this->_Shape.IsNull()) {
-        Standard_Failure::Raise("Cannot transform null shape");
+        throw Standard_Failure("Cannot transform null shape");
     }
 
     gp_GTrsf mat;
@@ -3322,7 +3322,7 @@ bool TopoShape::transformShape(const Base::Matrix4D& r
 bool TopoShape::transformShape(const Base::Matrix4D& rclTrf, bool copy, bool checkScale)
 {
     if (this->_Shape.IsNull()) {
-        Standard_Failure::Raise("Cannot transform null shape");
+        throw Standard_Failure("Cannot transform null shape");
     }
 
     return _makeTransform(TopoShape(*this), rclTrf, nullptr, checkScale, copy);
@@ -3339,7 +3339,7 @@ TopoDS_Shape TopoShape::toNurbs() const
 TopoDS_Shape TopoShape::toNurbs() const
 {
     if (this->_Shape.IsNull()) {
-        Standard_Failure::Raise("Cannot convert null shape to NURBS");
+        throw Standard_Failure("Cannot convert null shape to NURBS");
     }
 
     BRepBuilderAPI_NurbsConvert mkNurbs(this->_Shape);
@@ -3484,7 +3484,7 @@ TopoDS_Shape TopoShape::removeSplitter() const
 TopoDS_Shape TopoShape::removeSplitter() const
 {
     if (_Shape.IsNull()) {
-        Standard_Failure::Raise("Cannot remove splitter from empty shape");
+        throw Standard_Failure("Cannot remove splitter from empty shape");
     }
 
     if (_Shape.ShapeType() == TopAbs_SOLID) {
@@ -3504,7 +3504,7 @@ TopoDS_Shape TopoShape::removeSplitter() const
                 }
             }
             else {
-                Standard_Failure::Raise("Removing splitter failed");
+                throw Standard_Failure("Removing splitter failed");
                 return _Shape;
             }
         }
@@ -3517,7 +3517,7 @@ TopoDS_Shape TopoShape::removeSplitter() const
             return uniter.getShell();
         }
         else {
-            Standard_Failure::Raise("Removing splitter failed");
+            throw Standard_Failure("Removing splitter failed");
         }
     }
     else if (_Shape.ShapeType() == TopAbs_COMPOUND) {
@@ -4026,7 +4026,7 @@ TopoDS_Shape TopoShape::defeaturing(const std::vector<
 TopoDS_Shape TopoShape::defeaturing(const std::vector<TopoDS_Shape>& s) const
 {
     if (this->_Shape.IsNull()) {
-        Standard_Failure::Raise("Base shape is null");
+        throw Standard_Failure("Base shape is null");
     }
     BRepAlgoAPI_Defeaturing defeat;
     defeat.SetRunParallel(true);
