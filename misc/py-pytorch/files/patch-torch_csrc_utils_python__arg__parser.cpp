--- torch/csrc/utils/python_arg_parser.cpp.orig	2026-04-17 22:45:38 UTC
+++ torch/csrc/utils/python_arg_parser.cpp
@@ -755,9 +755,11 @@ auto handle_torch_function_indexing(
   }
   py::object func =
       PyObject_FastGetAttrString(THPVariableClass, (char*)func_name);
-  py::object args = (val == nullptr)
-      ? py::make_tuple(py::handle(self), py::handle(index))
-      : py::make_tuple(py::handle(self), py::handle(index), py::handle(val));
+  py::tuple args;
+  if (val == nullptr)
+    args = py::make_tuple(py::handle(self), py::handle(index));
+  else
+    args = py::make_tuple(py::handle(self), py::handle(index), py::handle(val));
   return handle_torch_function_no_python_arg_parser(
       overridable_args,
       args.ptr(),
