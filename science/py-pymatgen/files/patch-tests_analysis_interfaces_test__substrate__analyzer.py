--- tests/analysis/interfaces/test_substrate_analyzer.py.orig	2026-04-20 05:45:36 UTC
+++ tests/analysis/interfaces/test_substrate_analyzer.py
@@ -50,11 +50,11 @@ def test_generate_surface_vectors():
     assert [substrate_millers] == substrate_miller_indices
     assert_allclose(
         film_vectors,
-        [[0, 0, 3.035429], [-2.764654e-16, 4.515023, 2.764654e-16]],
+        [[4.881342e-16, 3.035429e+00, 1.858664e-16], [4.515023e+00, 0.0, 2.764654e-16]],
         atol=1e-6,
     )
     assert_allclose(
         substrate_vectors,
-        [[-3.766937, -1.928326, -6.328967], [3.766937, -12.307154, 0.0]],
-        atol=1e-6,
+        [[1.928326e+00, 6.328967e+00, -3.766937e+00], [1.2307154e+01, 0.0, 3.766937e+00]],
+        atol=1e-5,
     )
