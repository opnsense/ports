--- src/source-netmap.c.orig	2018-12-21 14:43:34 UTC
+++ src/source-netmap.c
@@ -268,6 +268,7 @@ static int NetmapOpen(char *ifname, int 
 {
     NetmapDevice *pdev = NULL;
     struct nmreq nm_req;
+    struct netmap_if *nifp = NULL;
 
     *pdevice = NULL;
 
@@ -367,7 +368,7 @@ static int NetmapOpen(char *ifname, int 
             nm_req.nr_ringid = i | NETMAP_NO_TX_POLL;
         } else {
             nm_req.nr_flags = NR_REG_SW;
-            nm_req.nr_ringid = NETMAP_NO_TX_POLL;
+            nm_req.nr_ringid = i | NETMAP_NO_TX_POLL;
         }
         if (ioctl(pring->fd, NIOCREGIF, &nm_req) != 0) {
             SCLogError(SC_ERR_NETMAP_CREATE,
@@ -385,14 +386,15 @@ static int NetmapOpen(char *ifname, int 
                            strerror(errno));
                 break;
             }
-            pdev->nif = NETMAP_IF(pdev->mem, nm_req.nr_offset);
-        }
+            pdev->nif = nifp = NETMAP_IF(pdev->mem, nm_req.nr_offset);
+        } else
+		nifp = NETMAP_IF(pdev->mem, nm_req.nr_offset);
 
         if ((i < pdev->rx_rings_cnt) || (i == pdev->rings_cnt)) {
-            pring->rx = NETMAP_RXRING(pdev->nif, i);
+            pring->rx = NETMAP_RXRING(nifp, i);
         }
         if ((i < pdev->tx_rings_cnt) || (i == pdev->rings_cnt)) {
-            pring->tx = NETMAP_TXRING(pdev->nif, i);
+            pring->tx = NETMAP_TXRING(nifp, i);
         }
         SCSpinInit(&pring->tx_lock, 0);
         success_cnt++;
