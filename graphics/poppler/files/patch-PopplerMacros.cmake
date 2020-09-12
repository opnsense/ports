--- cmake/modules/PopplerMacros.cmake.orig	2020-09-14 17:49:21.913826000 +0000
+++ cmake/modules/PopplerMacros.cmake	2020-09-14 17:50:02.896226000 +0000
@@ -167,7 +167,7 @@
   set(DEFAULT_COMPILE_WARNINGS_EXTRA "${_warn} ${_warnx}")
 
   set(_save_cxxflags "${CMAKE_CXX_FLAGS}")
-  set(CMAKE_CXX_FLAGS                "-fno-exceptions -fno-check-new -fno-common -D_DEFAULT_SOURCE")
+  set(CMAKE_CXX_FLAGS                "-fno-exceptions -fno-check-new -fno-common -D_DEFAULT_SOURCE -fPIC -fPIE")
   set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g ${_save_cxxflags}")
   set(CMAKE_CXX_FLAGS_RELEASE        "-O2 -DNDEBUG ${_save_cxxflags}")
   # clang does not support -fno-reorder-blocks -fno-schedule-insns, so do not use -O2
@@ -175,7 +175,7 @@
   set(CMAKE_CXX_FLAGS_DEBUGFULL      "-g3 -fno-inline ${_save_cxxflags}")
   set(CMAKE_CXX_FLAGS_PROFILE        "-g3 -fno-inline -ftest-coverage -fprofile-arcs ${_save_cxxflags}")
   set(_save_cflags "${CMAKE_C_FLAGS}")
-  set(CMAKE_C_FLAGS                  "-std=c99 -D_DEFAULT_SOURCE")
+  set(CMAKE_C_FLAGS                  "-std=c99 -D_DEFAULT_SOURCE -fPIC -fPIE")
   set(CMAKE_C_FLAGS_RELWITHDEBINFO   "-O2 -g ${_save_cflags}")
   set(CMAKE_C_FLAGS_RELEASE          "-O2 -DNDEBUG ${_save_cflags}")
   # clang does not support -fno-reorder-blocks -fno-schedule-insns, so do not use -O2
@@ -197,4 +197,3 @@
   set(CMAKE_C_FLAGS_DEBUG            "-O2 -g -Ob0 -noalign ${_save_cflags}")
   set(CMAKE_C_FLAGS_DEBUGFULL        "-g -Ob0 -noalign ${_save_cflags}")
 endif(CMAKE_C_COMPILER MATCHES "icc")
-
