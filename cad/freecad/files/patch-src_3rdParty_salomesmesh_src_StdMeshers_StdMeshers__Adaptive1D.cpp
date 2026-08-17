--- src/3rdParty/salomesmesh/src/StdMeshers/StdMeshers_Adaptive1D.cpp.orig	2026-07-01 16:20:28 UTC
+++ src/3rdParty/salomesmesh/src/StdMeshers/StdMeshers_Adaptive1D.cpp
@@ -38,7 +38,10 @@
 #include <BRepBndLib.hxx>
 #include <BRepMesh_IncrementalMesh.hxx>
 #include <BRep_Tool.hxx>
+#include <Standard_Version.hxx>
+#if OCC_VERSION_HEX < 0x080000
 #include <Bnd_B3d.hxx>
+#endif
 #include <Bnd_Box.hxx>
 #include <GCPnts_AbscissaPoint.hxx>
 #include <GeomAdaptor_Curve.hxx>
@@ -48,6 +51,7 @@
 #include <Poly_Triangulation.hxx>
 #include <Standard_Version.hxx>
 #include <TColgp_Array1OfPnt.hxx>
+#include <TColStd_Array1OfInteger.hxx>
 #include <TopExp.hxx>
 #include <TopExp_Explorer.hxx>
 #include <TopLoc_Location.hxx>
@@ -73,9 +77,27 @@ namespace // internal utils
    */
   struct BBox : public Bnd_B3d
   {
+#if OCC_VERSION_HEX >= 0x080000
+      gp_XYZ Center() const
+      {
+          const auto& myCenter = Bnd_B3d::Center();
+          return gp_XYZ(myCenter[0], myCenter[1], myCenter[2]);
+      }
+      gp_XYZ HSize() const
+      {
+          const auto& myHSize = Bnd_B3d::HSize();
+          return gp_XYZ(myHSize[0], myHSize[1], myHSize[2]);
+      }
+      double Size() const
+      {
+          const auto& myHSize = Bnd_B3d::HSize();
+          return 2 * myHSize[0];
+      }
+#else
     gp_XYZ Center() const { return gp_XYZ( myCenter[0], myCenter[1], myCenter[2] ); }
     gp_XYZ HSize()  const { return gp_XYZ( myHSize[0],  myHSize[1],  myHSize[2]  ); }
     double Size()   const { return 2 * myHSize[0]; }
+#endif
   };
   //================================================================================
   /*!
