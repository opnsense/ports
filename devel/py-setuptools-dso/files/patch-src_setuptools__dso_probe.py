-- Add FreeBSD support to target OS detection.
-- FreeBSD uses the __FreeBSD__ macro which is not recognized by the 
-- original probe, causing target_os to be None. This patch adds FreeBSD
-- to the list of recognized operating systems.

--- src/setuptools_dso/probe.py.orig	2026-02-11 01:15:48 UTC
+++ src/setuptools_dso/probe.py
@@ -403,6 +403,7 @@ class ToolchainInfo(object):
         'target_os':[
             ('__APPLE__', 'osx'),
             ('__CYGWIN__', 'cygwin'),
+            ('__FreeBSD__', 'freebsd'),
             ('__linux__', 'linux'),
             ('_WIN32', 'windows'),
         ],
