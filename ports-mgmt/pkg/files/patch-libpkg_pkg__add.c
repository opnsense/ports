--- libpkg/pkg_add.c.orig	2021-02-18 18:07:35 UTC
+++ libpkg/pkg_add.c
@@ -867,7 +867,7 @@ pkg_add_check_pkg_archive(struct pkgdb *db, struct pkg
 	int	ret, retcode;
 	struct pkg_dep	*dep = NULL;
 	char	bd[MAXPATHLEN], *basedir = NULL;
-	char	dpath[MAXPATHLEN], *ppath;
+	char	dpath[MAXPATHLEN] = "", *ppath;
 	const char	*ext = NULL;
 	struct pkg	*pkg_inst = NULL;
 	bool	fromstdin;
@@ -939,7 +939,9 @@ pkg_add_check_pkg_archive(struct pkgdb *db, struct pkg
 		if (dep->version != NULL && dep->version[0] != '\0') {
 			snprintf(dpath, sizeof(dpath), "%s/%s-%s%s", bd,
 				dep->name, dep->version, ext);
-		} else {
+		}
+
+		if (strlen(dpath) > 0 && access(dpath, F_OK) != 0) {
 			snprintf(dpath, sizeof(dpath), "%s/%s-*%s", bd,
 			    dep->name, ext);
 			ppath = pkg_globmatch(dpath, dep->name);
