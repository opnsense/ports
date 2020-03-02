--- src/nvidia/nvidia_os.c	2020-03-02 12:37:50.624383000 -0500
+++ src/nvidia/nvidia_os.c	2020-03-02 12:39:24.911021000 -0500
@@ -630,6 +630,8 @@
 
 NV_STATUS NV_API_CALL os_alloc_mutex(void **mutex)
 {
+    static size_t nmtx = 0;
+    char smtx[21];
     NV_STATUS status;
     struct sx *sx;
 
@@ -637,7 +639,9 @@
     if (status != NV_OK)
         return status;
 
-    sx_init(sx, "os.lock_sx");
+    memset(smtx, 0, sizeof(smtx));
+    snprintf(smtx, sizeof(smtx)-1, "os.lock_sx%zu", nmtx++);
+    sx_init(sx, smtx);
     *mutex = (void *)sx;
 
     return NV_OK;
