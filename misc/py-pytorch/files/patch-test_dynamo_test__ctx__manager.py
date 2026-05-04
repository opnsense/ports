--- test/dynamo/test_ctx_manager.py.orig	2026-04-19 12:47:58 UTC
+++ test/dynamo/test_ctx_manager.py
@@ -167,6 +167,7 @@ class CtxManagerTests(torch._dynamo.test_case.TestCase
             opt_fn(a)
         self.assertEqual(cnts.frame_count, 2)
 
+    @unittest.skipIf(sys.platform.startswith("freebsd"), "Kineto causes SIGABRT on FreeBSD")
     def test_torch_profiler(self):
         # wrap torch.profiler.* as NullContextVariable and do nothing
         def fn(x):
@@ -187,6 +188,7 @@ class CtxManagerTests(torch._dynamo.test_case.TestCase
         self.assertTrue(same(ref, res))
         self.assertEqual(cnts.frame_count, 2)
 
+    @unittest.skipIf(sys.platform.startswith("freebsd"), "Kineto causes SIGABRT on FreeBSD")
     def test_autograd_profiler(self):
         # wrap torch.autograd.profiler.* as NullContextVariable and do nothing
         def fn(x):
@@ -583,6 +585,7 @@ class CtxManagerTests(torch._dynamo.test_case.TestCase
         res = opt_fn(x)
         self.assertEqual(ref, res)
 
+    @unittest.skipIf(sys.platform.startswith("freebsd"), "Kineto causes SIGABRT on FreeBSD")
     def test_autograd_profiler_enabled(self):
         def fn(x):
             if torch.autograd._profiler_enabled():
@@ -1830,6 +1833,7 @@ class GraphModule(torch.nn.Module):
         opt_f = torch.compile(f, backend="eager")
         opt_f(torch.randn(2, 2))
 
+    @unittest.skipIf(sys.platform.startswith("freebsd"), "Kineto causes SIGABRT on FreeBSD")
     def test_torch_profiler_use_after_with_block(self):
         counters.clear()
 
