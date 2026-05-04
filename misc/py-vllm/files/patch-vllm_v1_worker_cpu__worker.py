--- vllm/v1/worker/cpu_worker.py.orig	2026-04-07 17:26:12 UTC
+++ vllm/v1/worker/cpu_worker.py
@@ -91,6 +91,9 @@ class CPUWorker(Worker):
                 self.local_omp_cpuid = self._get_autobind_cpu_ids(lambda cpus: cpus)
             else:
                 self.local_omp_cpuid = "nobind"
+        elif omp_cpuids == "auto":
+            # Non-Linux OS: NUMA-based auto-binding not supported, fall back to nobind
+            self.local_omp_cpuid = "nobind"
         elif omp_cpuids == "nobind":
             self.local_omp_cpuid = "nobind"
         else:
