--- tests/src/Mod/Part/App/TopoShapeExpansion.cpp.orig	2026-07-01 20:50:53 UTC
+++ tests/src/Mod/Part/App/TopoShapeExpansion.cpp
@@ -1,5 +1,6 @@
 // SPDX-License-Identifier: LGPL-2.1-or-later
 
+#include <TColgp_Array2OfPnt.hxx>
 #include <gtest/gtest.h>
 #include "src/App/InitApplication.h"
 #include <Mod/Part/App/TopoShape.h>
@@ -29,6 +30,7 @@
 #include <ShapeBuild_ReShape.hxx>
 #include <TopExp_Explorer.hxx>
 #include <TopoDS_Edge.hxx>
+#include <TColgp_Array1OfPnt.hxx>
 
 // NOLINTBEGIN(readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)
 
