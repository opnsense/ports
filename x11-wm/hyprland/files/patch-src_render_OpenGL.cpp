--- src/render/OpenGL.cpp.orig	2026-03-27 18:19:38 UTC
+++ src/render/OpenGL.cpp
@@ -813,13 +813,9 @@ void CHyprOpenGLImpl::end() {
     }
 
     // invalidate our render FBs to signal to the driver we don't need them anymore
-    m_renderData.pCurrentMonData->mirrorFB.bind();
     m_renderData.pCurrentMonData->mirrorFB.invalidate({GL_STENCIL_ATTACHMENT, GL_COLOR_ATTACHMENT0});
-    m_renderData.pCurrentMonData->mirrorSwapFB.bind();
     m_renderData.pCurrentMonData->mirrorSwapFB.invalidate({GL_STENCIL_ATTACHMENT, GL_COLOR_ATTACHMENT0});
-    m_renderData.pCurrentMonData->offloadFB.bind();
     m_renderData.pCurrentMonData->offloadFB.invalidate({GL_STENCIL_ATTACHMENT, GL_COLOR_ATTACHMENT0});
-    m_renderData.pCurrentMonData->offMainFB.bind();
     m_renderData.pCurrentMonData->offMainFB.invalidate({GL_STENCIL_ATTACHMENT, GL_COLOR_ATTACHMENT0});
 
     // reset our data
