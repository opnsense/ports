--- test/dynamo/test_guard_serialization.py.orig	2026-09-02 17:43:46 UTC
+++ test/dynamo/test_guard_serialization.py
@@ -1582,6 +1582,7 @@ class TestGuardSerialization(TestGuardSerializationBas
             True,
         )
 
+    @unittest.skipIf(sys.platform.startswith("freebsd"), "Gloo does not support FreeBSD")
     def test_ddp_module(self):
         import torch.distributed as dist
 
@@ -1636,6 +1637,7 @@ class TestGuardSerialization(TestGuardSerializationBas
             True,
         )
 
+    @unittest.skipIf(sys.platform.startswith("freebsd"), "Gloo does not support FreeBSD")
     def test_unserializable_sharded_tensor(self):
         import torch.distributed as dist
 
@@ -1751,6 +1753,7 @@ class TestGuardSerialization(TestGuardSerializationBas
         )
         self._test_check_fn(ref, loaded, {"inputs": Inputs(x, torch.Stream())}, True)
 
+    @unittest.skipIf(sys.platform.startswith("freebsd"), "Gloo does not support FreeBSD")
     def test_unused_process_group(self):
         import torch.distributed as dist
 
