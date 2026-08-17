commit 9e5555fe3fd762474a531da72a3aa1a3cdb1b6c4
Author: Chris <chris.r.jones.1983@gmail.com>
Date:   Mon Apr 13 22:18:38 2026 -0500

    TechDraw: Remove explicit template use of std::abs (#28985)
    
    Unnecessary, and fails to build on macOS 26.

--- src/Mod/TechDraw/Gui/CommandCreateDims.cpp.orig	2026-07-01 13:44:38 UTC
+++ src/Mod/TechDraw/Gui/CommandCreateDims.cpp
@@ -1103,7 +1103,7 @@ class TDHandlerDimension : public TechDrawHandler, (pr
             TechDraw::pointPair pp = dim->getLinearPoints();
             float dx = pp.first().x - pp.second().x;
             float dy = pp.first().y - pp.second().y;
-            int alpha = std::round(Base::toDegrees(std::abs<float>(std::atan(type == "DistanceY" ? (dx / dy) : (dy / dx)))));
+            int alpha = std::round(Base::toDegrees(std::abs(std::atan(type == "DistanceY" ? (dx / dy) : (dy / dx)))));
             std::string sAlpha = std::to_string(alpha);
             std::string formatSpec = dim->FormatSpec.getStrValue();
             formatSpec = formatSpec + " x" + sAlpha + "°";
--- src/Mod/TechDraw/Gui/CommandExtensionDims.cpp.orig	2026-07-01 13:44:38 UTC
+++ src/Mod/TechDraw/Gui/CommandExtensionDims.cpp
@@ -1984,7 +1984,7 @@ void execCreateHorizChamferDimension(Gui::Command* cmd
         dim->Y.setValue(-yMax);
         float dx = allVertexes[0].point.x - allVertexes[1].point.x;
         float dy = allVertexes[0].point.y - allVertexes[1].point.y;
-        float alpha = std::round(Base::toDegrees(std::abs<float>(std::atan(dy / dx))));
+        float alpha = std::round(Base::toDegrees(std::abs(std::atan(dy / dx))));
         std::string sAlpha = std::to_string((int)alpha);
         std::string formatSpec = dim->FormatSpec.getStrValue();
         formatSpec = formatSpec + " x" + sAlpha + "°";
@@ -2050,7 +2050,7 @@ void execCreateVertChamferDimension(Gui::Command* cmd)
         dim->Y.setValue(-mid.y);
         float dx = allVertexes[0].point.x - allVertexes[1].point.x;
         float dy = allVertexes[0].point.y - allVertexes[1].point.y;
-        float alpha = std::round(Base::toDegrees(std::abs<float>(std::atan(dx / dy))));
+        float alpha = std::round(Base::toDegrees(std::abs(std::atan(dx / dy))));
         std::string sAlpha = std::to_string((int)alpha);
         std::string formatSpec = dim->FormatSpec.getStrValue();
         formatSpec = formatSpec + " x" + sAlpha + "°";
