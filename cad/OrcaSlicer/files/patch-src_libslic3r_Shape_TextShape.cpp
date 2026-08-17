--- src/libslic3r/Shape/TextShape.cpp.orig	2026-03-22 17:56:38 UTC
+++ src/libslic3r/Shape/TextShape.cpp
@@ -6,6 +6,7 @@
 
 #include <string>
 #include <vector>
+#include <cstring>
 
 #include "Standard_TypeDef.hxx"
 #include "STEPCAFControl_Reader.hxx"
@@ -50,8 +51,7 @@ std::vector<std::string> init_occt_fonts()
     Handle(Font_FontMgr) aFontMgr = Font_FontMgr::GetInstance();
     aFontMgr->InitFontDataBase();
 
-    TColStd_SequenceOfHAsciiString availFontNames;
-    aFontMgr->GetAvailableFontsNames(availFontNames);
+    const NCollection_List<Handle(Font_SystemFont)>& availFontNames = aFontMgr->GetAvailableFonts();
     stdFontNames.reserve(availFontNames.Size());
 
     g_occt_fonts_maps.clear();
@@ -62,16 +62,17 @@ std::vector<std::string> init_occt_fonts()
     stdFontNames.push_back("HarmonyOS Sans SC");
     g_occt_fonts_maps.insert(std::make_pair("HarmoneyOS Sans SC", Slic3r::resources_dir() + "/fonts/" + "HarmonyOS_Sans_SC_Regular.ttf"));
 #endif
-    for (auto afn : availFontNames) {
+    for (auto sys_font : availFontNames) {
+        TCollection_AsciiString font_name = sys_font->FontName();
 #ifdef __APPLE__
-        if(afn->String().StartsWith("."))
+        if(font_name.StartsWith("."))
             continue;
 #endif
-        if(afn->Search("Emoji") != -1 || afn->Search("emoji") != -1)
+        if(font_name.Search("Emoji") != -1 || font_name.Search("emoji") != -1)
             continue;
         bool repeat = false;
         for (size_t i = 0; i < fonts_suffix.size(); i++) {
-            if (afn->SearchFromEnd(fonts_suffix[i]) != -1) {
+            if (font_name.SearchFromEnd(fonts_suffix[i]) != -1) {
                 repeat = true;
                 break;
             }
@@ -79,13 +80,12 @@ std::vector<std::string> init_occt_fonts()
         if (repeat)
             continue;
 
-        Handle(Font_SystemFont) sys_font = aFontMgr->GetFont(afn->ToCString());
         TCollection_AsciiString font_path = sys_font->FontPath(Font_FontAspect::Font_FontAspect_Regular);
         if (!font_path.IsEmpty() && font_path.SearchFromEnd(".") != -1) {
             auto  file_type = font_path.SubString(font_path.SearchFromEnd(".") + 1, font_path.Length());
             file_type.LowerCase();
             if (file_type == "ttf" || file_type == "otf" || file_type == "ttc") {
-                g_occt_fonts_maps.insert(std::make_pair(afn->ToCString(), decode_path(font_path.ToCString())));
+                g_occt_fonts_maps.insert(std::make_pair(font_name.ToCString(), decode_path(font_path.ToCString())));
             }
         }
     }
@@ -131,12 +131,12 @@ static bool TextToBRep(const char* text, const char* f
     aFormatter->Format();
 
     // get the text width
-    text_width                  = 0;
-    NCollection_String coll_str = aText;
-    for (NCollection_Utf8Iter anIter = coll_str.Iterator(); *anIter != 0;) {
-        const Standard_Utf32Char aCharThis = *anIter;
-        const Standard_Utf32Char aCharNext = *++anIter;
-        double                   width     = aFont.AdvanceX(aCharThis, aCharNext);
+    text_width = 0;
+    int str_len = strlen(aText);
+    for (int i = 0; i < str_len; ++i) {
+        Standard_Utf32Char aCharThis = (unsigned char)aText[i];
+        Standard_Utf32Char aCharNext = (i + 1 < str_len) ? (unsigned char)aText[i + 1] : 0;
+        double width = aFont.AdvanceX(aCharThis, aCharNext);
         text_width += width;
     }
 
@@ -199,7 +199,7 @@ static void MakeMesh(TopoDS_Shape& theSolid, TriangleM
         for (Standard_Integer aNodeIter = 1; aNodeIter <= aTriangulation->NbNodes(); ++aNodeIter) {
             gp_Pnt aPnt = aTriangulation->Node(aNodeIter);
             aPnt.Transform(aTrsf);
-            points.emplace_back(std::move(Vec3f(aPnt.X(), aPnt.Y(), aPnt.Z())));
+            points.emplace_back(Vec3f(aPnt.X(), aPnt.Y(), aPnt.Z()));
         }
         //BBS: copy triangles
         const TopAbs_Orientation anOrientation = anExpSF.Current().Orientation();
@@ -269,4 +269,4 @@ void load_text_shape(const char*text, const char* font
     MakeMesh(aTextShape, text_result.text_mesh);
 }
 
-}; // namespace Slic3r
+}; // namespace Slic3r
\ No newline at end of file
