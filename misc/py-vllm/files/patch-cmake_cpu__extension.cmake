--- cmake/cpu_extension.cmake.orig	2026-04-03 01:57:10 UTC
+++ cmake/cpu_extension.cmake
@@ -20,6 +20,11 @@ set (ENABLE_NUMA TRUE)
 
 set (ENABLE_NUMA TRUE)
 
+# FreeBSD does not have libnuma
+if (CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
+    set(ENABLE_NUMA OFF)
+endif()
+
 #
 # Check the compile flags
 #
@@ -33,12 +38,25 @@ if (NOT MACOSX_FOUND)
 endif()
 
 if (NOT MACOSX_FOUND)
-    execute_process(COMMAND cat /proc/cpuinfo
-                    RESULT_VARIABLE CPUINFO_RET
-                    OUTPUT_VARIABLE CPUINFO)
-    if (NOT CPUINFO_RET EQUAL 0)
-        message(FATAL_ERROR "Failed to check CPU features via /proc/cpuinfo")
+    # Try Linux /proc/cpuinfo first, then the FreeBSD linuxulator path
+    if (EXISTS "/proc/cpuinfo")
+        set(_cpuinfo_path "/proc/cpuinfo")
+    elseif (EXISTS "/compat/linux/proc/cpuinfo")
+        set(_cpuinfo_path "/compat/linux/proc/cpuinfo")
+    else()
+        set(_cpuinfo_path "")
     endif()
+    if (_cpuinfo_path)
+        execute_process(COMMAND cat ${_cpuinfo_path}
+                        RESULT_VARIABLE CPUINFO_RET
+                        OUTPUT_VARIABLE CPUINFO)
+        if (NOT CPUINFO_RET EQUAL 0)
+            message(FATAL_ERROR "Failed to check CPU features via ${_cpuinfo_path}")
+        endif()
+    else()
+        message(STATUS "No cpuinfo available; relying on CMAKE_SYSTEM_PROCESSOR for ISA detection")
+        set(CPUINFO "")
+    endif()
 endif()
 
 
@@ -91,9 +109,10 @@ if (CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|amd64" OR E
 
 if (CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|amd64" OR ENABLE_X86_ISA)
     set(ENABLE_X86_ISA ON)
-    if (NOT (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND
-            CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 12.3))
-        message(FATAL_ERROR "X86 backend requires gcc/g++ >= 12.3")
+    if (NOT (
+            (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 12.3) OR
+            (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 15.0)))
+        message(FATAL_ERROR "X86 backend requires gcc/g++ >= 12.3 or clang >= 15.0")
     endif()
     list(APPEND CXX_COMPILE_FLAGS "-mf16c")
     list(APPEND CXX_COMPILE_FLAGS_AVX512 ${CXX_COMPILE_FLAGS})
@@ -407,9 +426,15 @@ if (ENABLE_X86_ISA)
     message(STATUS "CPU extension (AVX512F) source files: ${VLLM_EXT_SRC_AVX512}")
     message(STATUS "CPU extension (AVX2) source files: ${VLLM_EXT_SRC_AVX2}")
 
-    set(_C_LIBS numa dnnl_ext)
-    set(_C_AVX512_LIBS numa dnnl_ext)
-    set(_C_AVX2_LIBS numa)
+    if(ENABLE_NUMA)
+        set(_C_LIBS numa dnnl_ext)
+        set(_C_AVX512_LIBS numa dnnl_ext)
+        set(_C_AVX2_LIBS numa)
+    else()
+        set(_C_LIBS dnnl_ext)
+        set(_C_AVX512_LIBS dnnl_ext)
+        set(_C_AVX2_LIBS "")
+    endif()
 
     # AMX + AVX512F + AVX512BF16 + AVX512VNNI
     define_extension_target(
