--- test/dynamo/test_repros.py.orig	2026-09-02 17:43:46 UTC
+++ test/dynamo/test_repros.py
@@ -6457,6 +6457,7 @@ def forward(self, L_x_ : torch.Tensor, s77 : torch.Sym
         graph_code = backend.graphs[0].print_readable(print_output=False)
         self.assertIn("torch._C._nn.linear", graph_code)
 
+    @unittest.skipIf(sys.platform.startswith("freebsd"), "Kineto causes SIGABRT on FreeBSD")
     def test_aot_autograd_runtime_wrapper_prologue_profiled(self):
         # Names for prologue profiling event
         prologue_name = "AOTDispatcher Runtime Wrapper Prologue"
