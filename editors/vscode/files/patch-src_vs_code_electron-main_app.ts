--- src/vs/code/electron-main/app.ts.orig	2026-04-21 23:12:14 UTC
+++ src/vs/code/electron-main/app.ts
@@ -1062,6 +1062,7 @@ export class CodeApplication extends Disposable {
 				break;
 
 			case 'linux':
+			case 'freebsd':
 				if (isLinuxSnap) {
 					services.set(IUpdateService, new SyncDescriptor(SnapUpdateService, [process.env['SNAP'], process.env['SNAP_REVISION']]));
 				} else {
