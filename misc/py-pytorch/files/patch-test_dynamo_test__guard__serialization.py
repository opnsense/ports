--- test/dynamo/test_guard_serialization.py.orig	2026-04-19 12:47:58 UTC
+++ test/dynamo/test_guard_serialization.py
@@ -1506,6 +1506,7 @@ class TestGuardSerialization(TestGuardSerializationBas
             True,
         )
 
+    @unittest.skipIf(sys.platform.startswith("freebsd"), "Gloo does not support FreeBSD")
     def test_ddp_module(self):
         import torch.distributed as dist
 
@@ -1558,6 +1559,7 @@ class TestGuardSerialization(TestGuardSerializationBas
             True,
         )
 
+    @unittest.skipIf(sys.platform.startswith("freebsd"), "Gloo does not support FreeBSD")
     def test_unserializable_sharded_tensor(self):
         import torch.distributed as dist
 
@@ -1675,6 +1677,7 @@ class TestGuardSerialization(TestGuardSerializationBas
             ref, loaded, {"inputs": Inputs(x, torch.cuda.Stream())}, True
         )
 
+    @unittest.skipIf(sys.platform.startswith("freebsd"), "Gloo does not support FreeBSD")
     def test_unused_process_group(self):
         import torch.distributed as dist
 
