--- upnphttp.c.orig
+++ upnphttp.c
@@ -262,9 +262,10 @@
 					p++;
 				while(p[n]>=' ')
 					n++;
-				if((p[0] == '"' && p[n-1] == '"')
-				  || (p[0] == '\'' && p[n-1] == '\''))
+				if((n >= 2) && ((p[0] == '"' && p[n-1] == '"')
+				             || (p[0] == '\'' && p[n-1] == '\'')))
 				{
+					/* remove the quotes */
 					p++; n -= 2;
 				}
 				h->req_soapActionOff = p - h->req_buf;
