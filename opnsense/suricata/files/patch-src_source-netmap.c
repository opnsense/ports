--- src/source-netmap.c.orig	2023-04-14 06:47:16 UTC
+++ src/source-netmap.c
@@ -615,6 +615,7 @@ static TmEcode NetmapWritePacket(NetmapThreadVars *ntv
 
     /* attempt to write the packet into the netmap ring buffer(s) */
     if (nmport_inject(ntv->ifdst->nmd, GET_PKT_DATA(p), GET_PKT_LEN(p)) == 0) {
+        ioctl(ntv->ifdst->nmd->fd, NIOCTXSYNC, 0);
         if (ntv->flags & NETMAP_FLAG_EXCL_RING_ACCESS) {
             SCMutexUnlock(&ntv->ifdst->netmap_dev_lock);
         }
