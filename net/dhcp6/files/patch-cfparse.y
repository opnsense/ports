--- cfparse.y.orig	2017-02-28 19:06:15 UTC
+++ cfparse.y
@@ -41,6 +41,11 @@
 #include <stdlib.h>
 #include <string.h>
 
+/* XXX */
+
+#include <stdio.h>
+#include <ctype.h>
+
 #include "dhcp6.h"
 #include "config.h"
 #include "common.h"
@@ -145,6 +150,9 @@ static void cleanup_cflist __P((struct c
 %type <range> rangeparam
 %type <pool> poolparam
 
+/* XXX */
+%token RAW
+
 %%
 statements:
 		/* empty */
@@ -664,6 +672,63 @@ dhcpoption:
 			/* currently no value */
 			$$ = l;
 		}
+	/* XXX */
+	|	RAW NUMBER STRING
+		{		
+			struct cf_list *l;
+			struct rawoption *rawop;
+			char *tmp, *opstr = $2, *datastr = $3;
+
+			yywarn("Got raw option: %s %s", opstr, datastr);			
+			
+			if ((rawop = malloc(sizeof(*rawop))) == NULL) {
+				yywarn("can't allocate memory");
+				free(datastr);
+				free(opstr);
+				return (-1);
+			}
+			
+			/* convert op num */
+			rawop->opnum = (int)strtol(opstr, NULL, 10);
+						
+			/* convert string to lowercase */
+			tmp = datastr;
+			for ( ; *tmp; ++tmp) *tmp = tolower(*tmp);
+			
+			/* allocate buffer */
+			int len = strlen(datastr);
+			len -= len / 3; /* remove ':' from length */						
+			len = len / 2; /* byte length */			
+			rawop->datalen = len;
+			
+			if ((rawop->data = malloc(len)) == NULL) {
+				yywarn("can't allocate memory");
+				free(datastr);
+				free(opstr);
+				return (-1);
+			}
+			
+			/* convert hex string to byte array */					
+			char *h = datastr;
+			char *b = rawop->data;
+			char xlate[] = "0123456789abcdef";
+			int p1, p2, i = 0;
+
+			for ( ; *h; h += 3, ++b) { /* string is xx(:xx)\0 */
+				p1 = (int)(strchr(xlate, *h) - xlate);
+				p2 = (int)(strchr(xlate, *(h+1)) - xlate);
+				*b = (char)((p1 * 16) + p2);
+			}   
+			//free(datastr);
+			//free(opstr);
+
+			yywarn("Raw option %d length %d stored at %p with data at %p",
+				rawop->opnum, rawop->datalen, (void*)rawop, (void*)rawop->data);			
+			
+			MAKE_CFLIST(l, DHCPOPT_RAW, NULL, NULL);
+			l->ptr = rawop;
+			$$ = l;
+		}
 	|	DNS_SERVERS
 		{
 			struct cf_list *l;
