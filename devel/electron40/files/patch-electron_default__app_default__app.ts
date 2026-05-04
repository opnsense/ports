--- electron/default_app/default_app.ts.orig	2026-04-15 14:05:49 UTC
+++ electron/default_app/default_app.ts
@@ -101,7 +101,7 @@ async function createWindow (backgroundColor?: string)
     show: false
   };
 
-  if (process.platform === 'linux') {
+  if (process.platform === 'linux' || process.platform === 'freebsd') {
     options.icon = url.fileURLToPath(new URL('icon.png', import.meta.url));
   }
 
