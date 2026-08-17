--- hazkey-server/build_swift.cmake.orig	2026-02-08 10:07:38 UTC
+++ hazkey-server/build_swift.cmake
@@ -25,6 +25,14 @@ endif()
     list(APPEND SWIFT_COMMAND "-Xlinker" "-L${SWIFT_LINK_PATH}")
 endif()
 
+if(CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
+    list(APPEND SWIFT_COMMAND "--skip-update")
+    list(APPEND SWIFT_COMMAND "-Xlinker" "-lexecinfo")
+    if(FREEBSD_CLANG_21_OR_GREATER)
+        list(APPEND SWIFT_COMMAND "-Xcc" "-D_WCHAR_H_CPLUSPLUS_98_CONFORMANCE_")
+    endif()
+endif()
+
 execute_process(
     COMMAND ${SWIFT_COMMAND}
     WORKING_DIRECTORY "${SWIFT_WORK_DIR}"
