--- src/source-ipfw.c.orig	2026-01-09 15:27:36 UTC
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
@@ -570,6 +578,10 @@ TmEcode IPFWSetVerdict(ThreadVars *tv, IPFWThreadVars 
                     SCReturnInt(TM_ECODE_FAILED);
                 case EHOSTDOWN:
                 case ENETDOWN:
+#ifdef PF_DIVERT
+                case EHOSTUNREACH:
+                case ENETUNREACH:
+#endif
                     break;
             }
         }
