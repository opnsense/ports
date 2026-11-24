--- cmake/cflags-generic.cmake.orig	2026-11-09 09:25:32 UTC
+++ cmake/cflags-generic.cmake
@@ -1,6 +1,6 @@
 # set compiler flags - more are tested and added later
-set(EXTRA_C_FLAGS "${OPT_C_FLAG} -std=c17 -Wall -Wextra ")
-set(EXTRA_CXX_FLAGS "${OPT_CXX_FLAG} -std=c++17 -Wall -Wextra ")
+set(EXTRA_C_FLAGS "-std=c17 -Wall -Wextra ")
+set(EXTRA_CXX_FLAGS "-std=c++17 -Wall -Wextra ")
 if (NOT CMAKE_COMPILER_IS_CLANG)
     set(EXTRA_CXX_FLAGS "${EXTRA_CXX_FLAGS} -fno-new-ttp-matching")
 endif()
--- cmake/cflags-x86.cmake.orig	2026-11-09 09:25:32 UTC
+++ cmake/cflags-x86.cmake
@@ -124,6 +124,10 @@ if (FAT_RUNTIME)
     if (BUILD_AVX512VBMI AND NOT HAVE_AVX512VBMI)
         message(FATAL_ERROR "AVX512VBMI support requested but not supported")
     endif ()
+    if (ARCH_X86_64)
+        set(ARCH_C_FLAGS "-march=x86-64")
+        set(ARCH_CXX_FLAGS "-march=x86-64")
+    endif ()
 else (NOT FAT_RUNTIME)
     if (NOT BUILD_AVX2)
         message(STATUS "Building without AVX2 support")
