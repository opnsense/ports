--- torch/csrc/jit/python/init.cpp.orig	2026-04-17 22:48:51 UTC
+++ torch/csrc/jit/python/init.cpp
@@ -1796,7 +1796,7 @@ void initJITBindings(PyObject* module) {
 
   m.def(
       "_jit_get_operation",
-      [](const std::string& op_name) {
+      [](const std::string& op_name) -> py::tuple {
         try {
           auto symbol = Symbol::fromQualString(op_name);
           const auto sortedOps = getAllSortedOperatorsFor(symbol);
@@ -1843,7 +1843,7 @@ void initJITBindings(PyObject* module) {
       "_maybe_call_torch_function_for_op_packet",
       [](py::handle op_overload_packet,
          const py::args& args,
-         const py::kwargs& kwargs) {
+         const py::kwargs& kwargs) -> py::tuple {
         py::list ns_method =
             op_overload_packet.attr("_qualified_op_name").attr("split")("::");
         auto res = _maybe_handle_torch_function(
