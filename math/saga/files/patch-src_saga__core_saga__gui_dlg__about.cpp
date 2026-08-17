--- src/saga_core/saga_gui/dlg_about.cpp.orig	2026-07-17 09:03:12 UTC
+++ src/saga_core/saga_gui/dlg_about.cpp
@@ -183,12 +183,7 @@ wxString CDLG_About::_Get_Version(void)
 	#else
 		s	+= " (32 bit)</b><br>";
 	#endif
-	#ifdef GIT_HASH
-		if( *GIT_HASH )
-		{
-			s	+= "<br><i>Git commit hash</i><br>[ <a href=\"" LINK_GIT "ci/" GIT_HASH "\">#" GIT_HASH "</a> ]<br>";
-		}
-	#endif
+	s	+= "<br><i>Git commit hash</i><br>[ <a href=\"https://sourceforge.net/p/saga-gis/code/ci/GIT_TAGNAME \">#" + wxString("GIT_TAGNAME") + "</a> ]<br>";
 	s	+= "<br>";
 	s	+= "<a href=\"" LINK_SAGA "\">saga-gis.org</a>";
 
