--- src/source-ipfw.c.orig	2025-12-22 19:23:25 UTC
+++ src/source-ipfw.c
@@ -359,6 +359,15 @@ TmEcode ReceiveIPFWThreadInit(ThreadVars *tv, const vo
         SCLogError("Can't set IPFW divert socket timeout: %s", strerror(errno));
         SCReturnInt(TM_ECODE_FAILED);
     }
+    
+#ifdef PF_DIVERT
+    int one = 1;
+    if (setsockopt(nq->fd, SOL_SOCKET, SO_REUSEPORT_LB, &one, sizeof(one)) == -1) {
+        SCLogError("Can't set IPFW divert socket SO_REUSEPORT_LB: %s", strerror(errno));
+        SCReturnInt(TM_ECODE_FAILED);
+    }
+#endif
+    
 
     nq->ipfw_sinlen=sizeof(nq->ipfw_sin);
     memset(&nq->ipfw_sin, 0, nq->ipfw_sinlen);
