--- src/selection_classic.c.orig	2021-02-05 01:42:43 UTC
+++ src/selection_classic.c
@@ -86,7 +86,7 @@ void selection_classic_create(void)
 }
 
 
-void selection_classic_destroy()
+void selection_classic_destroy(void)
 {
     struct selection_t const *const sel = *selection_get();
     struct selection_classic_t* pc = sel->classic;
