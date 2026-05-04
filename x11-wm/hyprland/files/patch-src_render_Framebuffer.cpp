--- src/render/Framebuffer.cpp.orig	2026-04-10 13:44:26 UTC
+++ src/render/Framebuffer.cpp
@@ -136,5 +136,11 @@ void CFramebuffer::invalidate(const std::vector<GLenum
     if (!isAllocated())
         return;
 
+    GLint restoreFB = 0;
+    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &restoreFB);
+
+    glBindFramebuffer(GL_FRAMEBUFFER, m_fb);
     glInvalidateFramebuffer(GL_FRAMEBUFFER, attachments.size(), attachments.data());
+
+    glBindFramebuffer(GL_FRAMEBUFFER, restoreFB);
 }
