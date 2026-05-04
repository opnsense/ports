--- tests/analysis/interfaces/test_coherent_interface.py.orig	2026-04-20 05:45:36 UTC
+++ tests/analysis/interfaces/test_coherent_interface.py
@@ -46,7 +46,9 @@ class TestInterfaceBuilder(MatSciTest):
         assert len(builder.terminations) == 2
         # SP: this test is super fragile and the result fluctuates between 6, 30 and 42 for
         # no apparent reason. The author should fix this.
-        assert len(list(builder.get_interfaces(termination=("O2_Pmmm_1", "Si_R-3m_1")))) >= 6
+        # Use the O2 termination dynamically since spglib versions can yield different suffix numbers
+        o2_termination = next(t for t in builder.terminations if t[0].startswith("O2_"))
+        assert len(list(builder.get_interfaces(termination=o2_termination))) >= 6
 
 
 class TestCoherentInterfaceBuilder:
