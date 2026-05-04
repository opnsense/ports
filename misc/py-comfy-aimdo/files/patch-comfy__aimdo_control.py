--- comfy_aimdo/control.py.orig	2026-03-19 07:04:32 UTC
+++ comfy_aimdo/control.py
@@ -19,6 +19,8 @@ def init():
             lib = ctypes.CDLL(str(base_path / "aimdo.dll"))
         elif system == "Linux":
             lib = ctypes.CDLL(str(base_path / "aimdo.so"), mode=258)
+        elif system == "FreeBSD":
+            lib = ctypes.CDLL(str(base_path / "aimdo.so"), mode=258)
         else:
             logging.info(f"comfy-aimdo os not supported {system}")
             logging.info(f"NOTE: comfy-aimdo is currently only support for Windows and Linux")
