--- vendor/github.com/sgtdi/fswatcher/watcher_kqueue.go.orig	2026-07-17 12:13:51 UTC
+++ vendor/github.com/sgtdi/fswatcher/watcher_kqueue.go
@@ -256,7 +256,7 @@ func (k *kqueue) batchAddWatchesLocked(entries []struc
 		}
 
 		changes = append(changes, unix.Kevent_t{
-			Ident:  uint64(fd),
+			Ident:  uint32(fd),
 			Filter: unix.EVFILT_VNODE,
 			Flags:  unix.EV_ADD | unix.EV_CLEAR,
 			Fflags: unix.NOTE_WRITE | unix.NOTE_DELETE | unix.NOTE_RENAME | unix.NOTE_ATTRIB | unix.NOTE_EXTEND,
@@ -332,7 +332,7 @@ func (k *kqueue) addSingleWatchLocked(path string) err
 	}
 	events := []unix.Kevent_t{
 		{
-			Ident:  uint64(fd),
+			Ident:  uint32(fd),
 			Filter: unix.EVFILT_VNODE,
 			Flags:  unix.EV_ADD | unix.EV_CLEAR,
 			Fflags: unix.NOTE_WRITE | unix.NOTE_DELETE | unix.NOTE_RENAME | unix.NOTE_ATTRIB | unix.NOTE_EXTEND,
