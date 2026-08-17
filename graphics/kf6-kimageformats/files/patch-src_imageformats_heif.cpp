From ac374da215eb30d67355be00c89a73c06fea8ae8 Mon Sep 17 00:00:00 2001
From: Kyle Alexander Buan <me@kylxbn.com>
Date: Thu, 16 Jul 2026 15:33:49 +0800
Subject: [PATCH] HEIF: keep reader callback table alive

libheif retains the heif_reader pointer after
heif_context_read_from_reader returns. The callback table was scoped
to the non-sequential branch and could be destroyed before
tiled image decoding used it from worker threads.

Give the callback table static storage duration.

BUG: 523105

--- src/imageformats/heif.cpp.orig	2026-07-03 10:55:53 UTC
+++ src/imageformats/heif.cpp
@@ -711,7 +711,8 @@ bool HEIFHandler::ensureDecoder()
         buffer = deviceRead(dev, kMaxQVectorSize);
         err = heif_context_read_from_memory(ctx, static_cast<const void *>(buffer.constData()), buffer.size(), nullptr);
     } else {
-        heif_reader reader = create_heif_reader_for_qiodevice();
+        // Must not be destroyed until decoding ends
+        static const heif_reader reader = create_heif_reader_for_qiodevice();
         err = heif_context_read_from_reader(ctx, &reader, dev, nullptr);
     }
     if (err.code) {
