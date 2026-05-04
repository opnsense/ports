--- test/dynamo/test_aot_autograd.py.orig	2026-04-19 12:47:58 UTC
+++ test/dynamo/test_aot_autograd.py
@@ -1,6 +1,7 @@ import re
 # Owner(s): ["module: dynamo"]
 import copy
 import re
+import sys
 import unittest
 from textwrap import dedent
 from unittest.mock import patch
@@ -1009,6 +1010,7 @@ SeqNr|OrigAten|SrcFn|FwdSrcFn
 
     # set donated_buffer=False due to create_graph=True
     @torch._functorch.config.patch("donated_buffer", False)
+    @unittest.skipIf(sys.platform.startswith("freebsd"), "Kineto causes SIGABRT on FreeBSD")
     def test_eager_sequence_nr(self):
         class Model(torch.nn.Module):
             def __init__(self) -> None:
