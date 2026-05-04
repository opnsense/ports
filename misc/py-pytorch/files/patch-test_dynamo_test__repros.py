--- test/dynamo/test_repros.py.orig	2026-04-19 12:47:58 UTC
+++ test/dynamo/test_repros.py
@@ -6105,6 +6105,7 @@ def forward(self, s77 : torch.SymInt, s27 : torch.SymI
         self.assertEqual(result, result_test)
         self.assertEqual(x, x_test)
 
+    @unittest.skipIf(sys.platform.startswith("freebsd"), "Kineto causes SIGABRT on FreeBSD")
     def test_aot_autograd_runtime_wrapper_prologue_profiled(self):
         # Names for prologue profiling event
         prologue_name = "AOTDispatcher Runtime Wrapper Prologue"
