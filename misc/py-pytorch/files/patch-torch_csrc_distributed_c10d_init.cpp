--- torch/csrc/distributed/c10d/init.cpp.orig	2026-04-17 22:57:32 UTC
+++ torch/csrc/distributed/c10d/init.cpp
@@ -887,7 +887,7 @@ This class does not support ``__members__`` property.)
             return ::c10d::ReduceOp(self);
           })
       .def(py::pickle(
-          [](const ::c10d::ReduceOp& r) {
+          [](const ::c10d::ReduceOp& r) -> py::tuple {
             // __getstate__
             if (r.op_ != ::c10d::ReduceOp::RedOpType::PREMUL_SUM) {
               return py::make_tuple(r.op_, py::none());
