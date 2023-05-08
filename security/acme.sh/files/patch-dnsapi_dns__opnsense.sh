--- dnsapi/dns_opnsense.sh.orig	2023-05-08 12:20:30 UTC
+++ dnsapi/dns_opnsense.sh
@@ -137,7 +137,7 @@ _get_root() {
   domain=$1
   i=2
   p=1
-  if _opns_rest "GET" "/domain/searchMasterDomain"; then
+  if _opns_rest "GET" "/domain/searchPrimaryDomain"; then
     _domain_response="$response"
   else
     return 1
@@ -150,7 +150,7 @@ _get_root() {
       return 1
     fi
     _debug h "$h"
-    id=$(echo "$_domain_response" | _egrep_o "\"uuid\":\"[a-z0-9\-]*\",\"enabled\":\"1\",\"type\":\"master\",\"domainname\":\"${h}\"" | cut -d ':' -f 2 | cut -d '"' -f 2)
+    id=$(echo "$_domain_response" | _egrep_o "\"uuid\":\"[a-z0-9\-]*\",\"enabled\":\"1\",\"type\":\"primary\",\"domainname\":\"${h}\"" | cut -d ':' -f 2 | cut -d '"' -f 2)
     if [ -n "$id" ]; then
       _debug id "$id"
       _host=$(printf "%s" "$domain" | cut -d . -f 1-$p)
