--- vllm/platforms/cpu.py.orig	2026-04-03 01:57:10 UTC
+++ vllm/platforms/cpu.py
@@ -74,7 +74,8 @@ class CpuPlatform(Platform):
     device_name: str = "cpu"
     device_type: str = "cpu"
     dispatch_key: str = "CPU"
-    dist_backend: str = "gloo"
+    # FreeBSD lacks gloo TCP transport (epoll-based); use fake backend.
+    dist_backend: str = "fake" if sys.platform.startswith("freebsd") else "gloo"
     device_control_env_var = "CPU_VISIBLE_MEMORY_NODES"
 
     @property
@@ -378,7 +379,28 @@ class CpuPlatform(Platform):
 
     @classmethod
     def get_allowed_cpu_core_node_list(cls) -> tuple[list[int], list[LogicalCPUInfo]]:
-        assert platform.system() == "Linux"
+        assert platform.system() in ("Linux", "FreeBSD")
+
+        if platform.system() == "FreeBSD":
+            # FreeBSD lacks lscpu -J; treat all CPUs as a single NUMA node.
+            allowed_cpu_id_set = (
+                os.sched_getaffinity(0)
+                if hasattr(os, "sched_getaffinity")
+                else set(range(os.cpu_count() or 1))
+            )
+            logical_cpu_list = [
+                LogicalCPUInfo(id=cpu_id, physical_core=cpu_id, numa_node=0)
+                for cpu_id in sorted(allowed_cpu_id_set)
+            ]
+            allowed_numa_nodes_list = [0]
+            env_key = CpuPlatform.device_control_env_var
+            if env_key in os.environ and os.environ[env_key] != "":
+                visible_nodes = [int(s) for s in os.environ[env_key].split(",")]
+                allowed_numa_nodes_list = [
+                    x for x in sorted(list(set(visible_nodes)))
+                    if x in allowed_numa_nodes_list
+                ]
+            return allowed_numa_nodes_list, logical_cpu_list
 
         # Init LogicalCPUInfo from lscpu
         lscpu_output = subprocess.check_output(
