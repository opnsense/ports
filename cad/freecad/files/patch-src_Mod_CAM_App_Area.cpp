--- src/Mod/CAM/App/Area.cpp.orig	2026-07-02 14:27:52 UTC
+++ src/Mod/CAM/App/Area.cpp
@@ -381,7 +381,7 @@ static std::vector<gp_Pnt> discretize(const TopoDS_Edg
     //
     GCPnts_UniformDeflection discretizer(curve, deflection, efirst, elast);
     if (!discretizer.IsDone()) {
-        Standard_Failure::Raise("Curve discretization failed");
+        throw Standard_Failure("Curve discretization failed");
     }
     if (discretizer.NbPoints() > 1) {
         int nbPoints = discretizer.NbPoints();
