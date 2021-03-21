--- compat.h.orig	2021-03-21 14:54:54 UTC
+++ compat.h
@@ -85,4 +85,6 @@ static inline uint32_t arc4random_uniform(uint32_t bou
 
 	return ret % bound;
 }
+
+typedef void callout_func_t(void *);
 #endif
