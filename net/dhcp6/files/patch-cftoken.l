--- cftoken.l.orig	2016-12-19 08:16:42 UTC
+++ cftoken.l
@@ -1,5 +1,7 @@
 /*	$KAME: cftoken.l,v 1.35 2005/01/12 06:06:11 suz Exp $	*/
 
+%option noyywrap
+
 %{
 /*
  * Copyright (C) 2002 WIDE Project.
