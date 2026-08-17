--- src/Mod/Part/App/FeatureMirroring.cpp.orig	2026-07-01 20:30:18 UTC
+++ src/Mod/Part/App/FeatureMirroring.cpp
@@ -345,7 +345,7 @@ App::DocumentObjectExecReturn* Mirroring::execute()
         gp_Ax2 ax2(gp_Pnt(base.x, base.y, base.z), gp_Dir(norm.x, norm.y, norm.z));
 
         if (shape.isNull()) {
-            Standard_Failure::Raise("Cannot mirror empty shape");
+            throw Standard_Failure("Cannot mirror empty shape");
         }
 
         auto mirrored = TopoShape(0).makeElementMirror(shape, ax2);
