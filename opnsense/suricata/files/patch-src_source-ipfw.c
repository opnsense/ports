--- src/source-ipfw.c.orig	2025-11-05 14:48:20 UTC
+++ src/source-ipfw.c
@@ -360,6 +360,14 @@ TmEcode ReceiveIPFWThreadInit(ThreadVars *tv, const vo
         SCReturnInt(TM_ECODE_FAILED);
     }
 
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
     nq->ipfw_sin.sin_family = PF_INET;
