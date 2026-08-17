--- src/3rdParty/salomesmesh/src/StdMeshers/StdMeshers_Cartesian_3D.cpp.orig	2026-07-01 16:20:28 UTC
+++ src/3rdParty/salomesmesh/src/StdMeshers/StdMeshers_Cartesian_3D.cpp
@@ -55,7 +55,12 @@
 #include <BRepTopAdaptor_FClass2d.hxx>
 #include <BRep_Builder.hxx>
 #include <BRep_Tool.hxx>
+#include <Standard_Version.hxx>
+#if OCC_VERSION_HEX >= 0x080000
+#include <Bnd_B3.hxx>
+#else
 #include <Bnd_B3d.hxx>
+#endif
 #include <Bnd_Box.hxx>
 #include <ElSLib.hxx>
 #include <GCPnts_UniformDeflection.hxx>
@@ -3462,7 +3467,11 @@ namespace
         double dist = GEOMUtils::GetMinDistance( plane, allFacesComp, pPlane, pFaces );
         if ( dist < 0 )
         {
+#if OCC_VERSION_HEX >= 0x080000
+          Bnd_B3<double> bb;
+#else
           Bnd_B3d bb;
+#endif
           gp_XYZ corner;
           for ( int i = 0; i < 2; ++i ) {
             corner.SetCoord( 1, sP[ i*3 ]);
