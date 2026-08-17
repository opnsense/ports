--- src/3rdParty/salomesmesh/src/StdMeshers/StdMeshers_ViscousLayers.cpp.orig	2026-07-01 16:20:28 UTC
+++ src/3rdParty/salomesmesh/src/StdMeshers/StdMeshers_ViscousLayers.cpp
@@ -52,8 +52,13 @@
 #include <BRepAdaptor_Surface.hxx>
 #include <BRepLProp_SLProps.hxx>
 #include <BRep_Tool.hxx>
+#if OCC_VERSION_HEX >= 0x080000
+#include <Bnd_B2.hxx>
+#include <Bnd_B3.hxx>
+#else
 #include <Bnd_B2d.hxx>
 #include <Bnd_B3d.hxx>
+#endif
 #include <ElCLib.hxx>
 #include <GCPnts_AbscissaPoint.hxx>
 #include <Geom2d_Circle.hxx>
