--- doc/gen.sh.orig	2026-04-25 17:08:32 UTC
+++ doc/gen.sh
@@ -18,7 +18,7 @@ for FILE in "$DIR"/*scd; do
 fi
 
 for FILE in "$DIR"/*scd; do
-	GEN="$GEN_DIR"/"$(basename -s .scd "$FILE")"
+	GEN="$GEN_DIR"/"$(basename "$FILE" .scd)"
 	printf "generating %s..." "$GEN"
 	scdoc < "$FILE" > "$GEN"
 	printf " ...done!\n"
