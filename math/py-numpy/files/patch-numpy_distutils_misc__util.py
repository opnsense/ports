--- numpy/distutils/misc_util.py.orig	2022-12-26 03:52:53 UTC
+++ numpy/distutils/misc_util.py
@@ -91,7 +91,7 @@ def get_num_build_jobs():
     from numpy.distutils.core import get_distribution
     try:
         cpu_count = len(os.sched_getaffinity(0))
-    except AttributeError:
+    except Exception:
         cpu_count = multiprocessing.cpu_count()
     cpu_count = min(cpu_count, 8)
     envjobs = int(os.environ.get("NPY_NUM_BUILD_JOBS", cpu_count))
