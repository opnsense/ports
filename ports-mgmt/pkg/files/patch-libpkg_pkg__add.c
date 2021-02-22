--- libpkg/pkg_add.c.orig	2020-10-11 12:57:45 UTC
+++ libpkg/pkg_add.c
@@ -823,7 +823,7 @@ pkg_globmatch(char *pattern, const char *name)
 		buf = strrchr(g.gl_pathv[i], '-');
 		if (buf == NULL)
 			continue;
-		buf2 = strchr(g.gl_pathv[i], '/');
+		buf2 = strrchr(g.gl_pathv[i], '/');
 		if (buf2 == NULL)
 			buf2 = g.gl_pathv[i];
 		else
@@ -838,7 +838,11 @@ pkg_globmatch(char *pattern, const char *name)
 		if (pkg_version_cmp(path, g.gl_pathv[i]) == 1)
 			path = g.gl_pathv[i];
 	}
-	path = xstrdup(path);
+
+	if (path != NULL) {
+		path = xstrdup(path);
+	}
+
 	globfree(&g);
 
 	return (path);
@@ -853,7 +857,7 @@ pkg_add_check_pkg_archive(struct pkgdb *db, struct pkg
 	int	ret, retcode;
 	struct pkg_dep	*dep = NULL;
 	char	bd[MAXPATHLEN], *basedir = NULL;
-	char	dpath[MAXPATHLEN], *ppath;
+	char	dpath[MAXPATHLEN] = "", *ppath;
 	const char	*ext = NULL;
 	struct pkg	*pkg_inst = NULL;
 	bool	fromstdin;
@@ -925,7 +929,9 @@ pkg_add_check_pkg_archive(struct pkgdb *db, struct pkg
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
@@ -1159,6 +1165,7 @@ pkg_add_common(struct pkgdb *db, const char *path, uns
 	}
 
 	if (local != NULL) {
+		pkg_open_root_fd(local);
 		pkg_debug(1, "Cleaning up old version");
 		if (pkg_add_cleanup_old(db, local, pkg, flags) != EPKG_OK) {
 			retcode = EPKG_FATAL;
