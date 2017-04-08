--- phalcon.zep.c.orig	2017-04-05 21:26:32 UTC
+++ phalcon.zep.c
@@ -2117,8 +2117,8 @@ static int ZEPHIR_FASTCALL zephir_memory
 #define ZEPHIR_MM_RESTORE() zephir_memory_restore_stack(NULL)
 
 #else
-static void ZEPHIR_FASTCALL zephir_memory_grow_stack();
-static int ZEPHIR_FASTCALL zephir_memory_restore_stack();
+static void zephir_memory_grow_stack();
+static int zephir_memory_restore_stack();
 
 #define ZEPHIR_MM_GROW() zephir_memory_grow_stack()
 #define ZEPHIR_MM_RESTORE() zephir_memory_restore_stack()
@@ -2131,7 +2131,7 @@ static int ZEPHIR_FASTCALL zephir_memory
 static void ZEPHIR_FASTCALL zephir_memory_observe(zval *var);
 static void ZEPHIR_FASTCALL zephir_memory_alloc(zval *var);
 
-static int ZEPHIR_FASTCALL zephir_clean_restore_stack();
+static int zephir_clean_restore_stack();
 
 #define zephir_safe_zval_ptr_dtor(pzval)
 
@@ -4240,7 +4240,7 @@ static void ZEPHIR_FASTCALL zephir_memor
 
 #else
 
-static void ZEPHIR_FASTCALL zephir_memory_grow_stack()
+static void zephir_memory_grow_stack()
 {
 	zend_zephir_globals_def *g = ZEPHIR_VGLOBAL;
 	if (g->start_memory == NULL) {
@@ -4249,7 +4249,7 @@ static void ZEPHIR_FASTCALL zephir_memor
 	zephir_memory_grow_stack_common(g);
 }
 
-static int ZEPHIR_FASTCALL zephir_memory_restore_stack()
+static int zephir_memory_restore_stack()
 {
 	zephir_memory_restore_stack_common(ZEPHIR_VGLOBAL);
 	return SUCCESS;
@@ -4496,8 +4496,8 @@ static void ZEPHIR_FASTCALL zephir_memor
 	ZVAL_NULL(var);
 }
 
-static int ZEPHIR_FASTCALL zephir_clean_restore_stack() {
-
+static int zephir_clean_restore_stack()
+{
 	zend_zephir_globals_def *zephir_globals_ptr = ZEPHIR_VGLOBAL;
 
 	while (zephir_globals_ptr->active_memory != NULL) {
