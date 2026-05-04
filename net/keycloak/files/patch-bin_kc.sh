--- bin/kc.sh.orig	2026-04-07 11:28:05 UTC
+++ bin/kc.sh
@@ -113,7 +113,7 @@ if [ -z "$JAVA_ADD_OPENS" ]; then
 
 # See also https://github.com/wildfly/wildfly-core/blob/7e5624cf92ebe4b64a4793a8c0b2a340c0d6d363/core-feature-pack/common/src/main/resources/content/bin/common.sh#L57-L60
 if [ -z "$JAVA_ADD_OPENS" ]; then
-   JAVA_ADD_OPENS="--add-opens=java.base/java.util=ALL-UNNAMED --add-opens=java.base/java.util.concurrent=ALL-UNNAMED --add-opens=java.base/java.security=ALL-UNNAMED"
+   JAVA_ADD_OPENS="--add-opens=java.base/java.util=ALL-UNNAMED --add-opens=java.base/java.util.concurrent=ALL-UNNAMED --add-opens=java.base/java.security=ALL-UNNAMED --add-opens=java.base/java.lang=ALL-UNNAMED --enable-native-access=ALL-UNNAMED"
 else
    echo "JAVA_ADD_OPENS already set in environment; overriding default settings"
 fi
