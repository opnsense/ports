--- adm/cmake/occt_macros.cmake.orig	2026-05-06 22:31:54 UTC
+++ adm/cmake/occt_macros.cmake
@@ -63,7 +63,7 @@ macro (OCCT_MAKE_OS_WITH_BITNESS)
   elseif(APPLE)
     set (OS_WITH_BIT "mac${COMPILER_BITNESS}")
   else()
-    set (OS_WITH_BIT "lin${COMPILER_BITNESS}")
+    set (OS_WITH_BIT "bsd${COMPILER_BITNESS}")
   endif()
 endmacro()
 
@@ -409,7 +409,7 @@ function (COLLECT_AND_INSTALL_OCCT_HEADER_FILES THE_RO
 
   set (OCCT_HEADER_FILES_INSTALLATION ${OCCT_HEADER_FILES_COMPLETE})
   list (FILTER OCCT_HEADER_FILES_INSTALLATION INCLUDE REGEX ".*[.](h|hxx|lxx)$")
-  install (FILES ${OCCT_HEADER_FILES_INSTALLATION} DESTINATION "${INSTALL_DIR}/${THE_OCCT_INSTALL_DIR_PREFIX}")
+  install (FILES ${OCCT_HEADER_FILES_INSTALLATION} DESTINATION "${THE_OCCT_INSTALL_DIR_PREFIX}")
 endfunction()
 
 # Macro to configure and install Standard_Version.hxx file
@@ -420,7 +420,7 @@ macro (CONFIGURE_AND_INSTALL_VERSION_HEADER)
     set(BUILD_OCCT_VERSION_EXT "${OCC_VERSION_STRING_EXT}" CACHE STRING "OCCT Version string. Used only for caching, can't impact on build. For modification of version, please check adm/cmake/version.cmake" FORCE)
     mark_as_advanced(BUILD_OCCT_VERSION_EXT)
     string(TIMESTAMP OCCT_VERSION_DATE "%Y-%m-%d" UTC)
-    OCCT_CONFIGURE_AND_INSTALL ("adm/templates/Standard_Version.hxx.in" "${INSTALL_DIR_INCLUDE}/Standard_Version.hxx" "Standard_Version.hxx" "${INSTALL_DIR}/${INSTALL_DIR_INCLUDE}")
+    OCCT_CONFIGURE_AND_INSTALL ("adm/templates/Standard_Version.hxx.in" "${OCCT_BINARY_DIR}/${INSTALL_DIR_INCLUDE}/Standard_Version.hxx" "Standard_Version.hxx" "${INSTALL_DIR_INCLUDE}")
   endif()
 endmacro()
 
