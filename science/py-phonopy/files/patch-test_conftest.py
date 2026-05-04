-- Fix test crash by setting matplotlib to use non-interactive Agg backend.
-- This prevents segmentation faults when matplotlib tries to use GTK4 backend
-- in a headless FreeBSD environment during test execution.
-- See: https://github.com/phonopy/phonopy/issues/???

--- test/conftest.py.orig	2026-04-24 07:29:40 UTC
+++ test/conftest.py
@@ -5,12 +5,15 @@ from collections.abc import Callable
 import pathlib
 from collections.abc import Callable
 
+import matplotlib
 import numpy as np
 import pytest
 
 import phonopy
 from phonopy import Phonopy
 from phonopy.structure.atoms import PhonopyAtoms
+
+matplotlib.use("Agg")
 
 cwd = pathlib.Path(__file__).parent
 
