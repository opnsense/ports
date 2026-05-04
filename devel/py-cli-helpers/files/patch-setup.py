--- setup.py.orig	2026-04-13 15:13:15 UTC
+++ setup.py
@@ -37,7 +37,7 @@ setup(
     long_description_content_type="text/x-rst",
     install_requires=[
         "configobj >= 5.0.5",
-        "tabulate[widechars] ~= 0.10.0",
+        "tabulate[widechars] >= 0.9.0",
     ],
     extras_require={
         "styles": ["Pygments >= 1.6"],
