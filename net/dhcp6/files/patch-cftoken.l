--- cftoken.l.orig	2017-02-28 19:06:15 UTC
+++ cftoken.l
@@ -1,5 +1,7 @@
 /*	$KAME: cftoken.l,v 1.35 2005/01/12 06:06:11 suz Exp $	*/
 
+%option noyywrap
+
 %{
 /*
  * Copyright (C) 2002 WIDE Project.
@@ -109,6 +111,9 @@ slash		\/
 bcl		\{
 ecl		\}
 
+/* XXX */
+hexdata 	{hexpair}(:{hexpair})*
+
 %s S_CNF
 %s S_IFACE
 %s S_PREF
@@ -120,6 +125,8 @@ ecl		\}
 %s S_SECRET
 %s S_ADDRPOOL
 %s S_INCL
+/* XXX */
+%s S_RAW
 
 %%
 %{
@@ -205,6 +212,15 @@ ecl		\}
 <S_CNF>bcmcs-server-address { DECHO; return (BCMCS_SERVERS); }
 <S_CNF>bcmcs-server-domain-name { DECHO; return (BCMCS_NAME); }
 <S_CNF>refreshtime { DECHO; return (REFRESHTIME); }
+	/* XXX */
+<S_CNF>raw-option { DECHO; BEGIN S_RAW; return (RAW); }
+<S_RAW>{integer} { DECHO; yylval.str = strdup(yytext); return(NUMBER); }
+<S_RAW>{hexdata} {
+	DECHO;
+	yylval.str = strdup(yytext);
+	BEGIN S_CNF;
+	return (STRING);
+}
 
 	/* provided for a backward compatibility to WIDE-DHCPv6 before Oct 1 2006 */
 <S_CNF>nis-server-domain-name { DECHO; return (NIS_NAME); }
