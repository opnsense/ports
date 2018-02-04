--- include/common/hathreads.h.orig	2018-02-04 16:36:55 UTC
+++ include/common/hathreads.h
@@ -99,6 +99,55 @@ extern THREAD_LOCAL unsigned long tid_bi
 
 /* TODO: thread: For now, we rely on GCC builtins but it could be a good idea to
  * have a header file regrouping all functions dealing with threads. */
+
+#ifdef __clang__
+#define HA_ATOMIC_ADD(val, i)        __sync_add_and_fetch(val, i)
+#define HA_ATOMIC_SUB(val, i)        __sync_sub_and_fetch(val, i)
+#define HA_ATOMIC_AND(val, flags)    __sync_and_and_fetch(val, flags)
+#define HA_ATOMIC_OR(val, flags)     __sync_or_and_fetch(val,  flags)
+
+/* the CAS is a bit complicated. The older API doesn't support returning the
+ * value and the swap's result at the same time. So here we take what looks
+ * like the safest route, consisting in using the boolean version guaranteeing
+ * that the operation was performed or not, and we snoop a previous value. If
+ * the compare succeeds, we return. If it fails, we return the previous value,
+ * but only if it differs from the expected one. If it's the same it's a race
+ * thus we try again to avoid confusing a possibly sensitive caller.
+ */
+#define HA_ATOMIC_CAS(val, old, new)					       \
+	({								       \
+		typeof((val)) __val = (val);				       \
+		typeof((old)) __oldp = (old);				       \
+		typeof(*(old)) __oldv;					       \
+		typeof((new)) __new = (new);				       \
+		int __ret;						       \
+		do {							       \
+			__oldv = *__val;				       \
+			__ret = __sync_bool_compare_and_swap(__val, *__oldp, __new); \
+		} while (!__ret && *__oldp == __oldv);			       \
+		if (!__ret)						       \
+			*__oldp = __oldv;				       \
+		__ret;							       \
+	})
+
+#define HA_ATOMIC_XCHG(val, new)					       \
+	({								       \
+		typeof((val)) __val = (val);				       \
+		typeof(*(val)) __old;					       \
+		typeof((new)) __new = (new);				       \
+		do { __old = *__val;					       \
+		} while (!__sync_bool_compare_and_swap(__val, __old, __new));  \
+		__old;							       \
+	})
+#define HA_ATOMIC_STORE(val, new)					     \
+	({								       \
+		typeof((val)) __val = (val);				       \
+		typeof(*(val)) __old;					       \
+		typeof((new)) __new = (new);				       \
+		do { __old = *__val;					       \
+		} while (!__sync_bool_compare_and_swap(__val, __old, __new));  \
+	})
+#else
 #define HA_ATOMIC_CAS(val, old, new) __atomic_compare_exchange_n(val, old, new, 0, 0, 0)
 #define HA_ATOMIC_ADD(val, i)        __atomic_add_fetch(val, i, 0)
 #define HA_ATOMIC_SUB(val, i)        __atomic_sub_fetch(val, i, 0)
@@ -106,6 +155,8 @@ extern THREAD_LOCAL unsigned long tid_bi
 #define HA_ATOMIC_OR(val, flags)     __atomic_or_fetch(val,  flags, 0)
 #define HA_ATOMIC_XCHG(val, new)     __atomic_exchange_n(val, new, 0)
 #define HA_ATOMIC_STORE(val, new)    __atomic_store_n(val, new, 0)
+#endif
+
 #define HA_ATOMIC_UPDATE_MAX(val, new)					\
 	({								\
 		typeof(*(val)) __old = *(val);				\
