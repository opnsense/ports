--- src/go/sp/sp/sp.go.orig	2026-06-03 15:31:18 UTC
+++ src/go/sp/sp/sp.go
@@ -512,32 +512,27 @@ func prependXML(arg string) {
 }
 
 // Return the full path to the TeX executable. It is called sdluatex(.exe) and
-// can be overridden by the 'luatex' option. It panics if the TeX binary cannot
-// be found.
+// can be overridden by the 'luatex' option. As a fallback, luahbtex(.exe) is
+// also accepted. It panics if no TeX binary can be found.
 func getExecutablePath() string {
-	// 1 check the installdir/bin for sdluatex(.exe)
-	// 2 panic!
 	if luatex := getOption("luatex"); luatex != "" {
 		return luatex
 	}
-	executableName := "sdluatex" + exeSuffix
-	var p string
 
-	// 1 check the installdir/bin for sdluatex(.exe)
-	p = filepath.Join(installdir, "bin", executableName)
-	fi, _ := os.Stat(p)
-	if fi != nil {
-		return p
-	}
+	for _, name := range []string{"sdluatex", "luahbtex"} {
+		executableName := name + exeSuffix
 
-	// 2 look in the PATH
-	executableName, err := exec.LookPath("sdluatex" + exeSuffix)
-	if err == nil {
-		return executableName
+		p := filepath.Join(installdir, "bin", executableName)
+		if fi, _ := os.Stat(p); fi != nil {
+			return p
+		}
+
+		if p, err := exec.LookPath(executableName); err == nil {
+			return p
+		}
 	}
 
-	// 3 panic!
-	log.Fatal("Can't find sdluatex binary")
+	log.Fatal("Can't find sdluatex or luahbtex binary")
 	return ""
 }
 
