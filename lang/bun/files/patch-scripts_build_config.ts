-- Add BUN_HOST_OS environment variable support to override host OS detection.
-- When building with a Linux bootstrap bun binary on FreeBSD, bun reports
-- host.os = "linux" which triggers cross-compilation mode (dep_cargo_cross,
-- rustup target add, cross-compile clang flags). Setting BUN_HOST_OS=freebsd
-- makes the build treat FreeBSD as native, using dep_cargo (no rustup needed)
-- and native LLVM/clang without cross-compile sysroot flags.
--
-- Also inline WEBKIT_VERSION to break a circular ES module dependency:
-- deps/index.ts → deps/webkit.ts → source.ts → config.ts → deps/webkit.ts
-- Bun 1.3.14 enforces strict TDZ for circular ES modules; inlining breaks cycle.

--- scripts/build/config.ts.orig	2026-04-27 07:22:36 UTC
+++ scripts/build/config.ts
@@ -11,7 +11,9 @@
 import { homedir, arch as hostArch, platform as hostPlatform } from "node:os";
 import { isAbsolute, join, relative, resolve, sep } from "node:path";
 import { NODEJS_ABI_VERSION, NODEJS_VERSION } from "./deps/nodejs-headers.ts";
-import { WEBKIT_VERSION } from "./deps/webkit.ts";
+// WEBKIT_VERSION inlined here (was imported from deps/webkit.ts) to break circular module dep:
+// deps/index.ts → deps/webkit.ts → source.ts → config.ts → deps/webkit.ts
+const WEBKIT_VERSION = "bdf6aab38a9c6f99df3fd1486406ab6b74180fbb";
 import { assert, BuildError } from "./error.ts";
 import { clangTargetArch } from "./tools.ts";
 import { cyan, dim, green } from "./tty.ts";
@@ -341,9 +343,12 @@
 
 /**
  * Host platform detection. Only used for picking defaults.
+ * The BUN_HOST_OS environment variable can override the detected OS.
+ * This is needed when using a Linux bun bootstrap binary on FreeBSD.
  */
 export function detectHost(): Host {
-  const plat = hostPlatform();
+  const envOs = process.env.BUN_HOST_OS;
+  const plat = envOs !== undefined ? envOs : hostPlatform();
   const os: OS =
     plat === "linux"
       ? "linux"
