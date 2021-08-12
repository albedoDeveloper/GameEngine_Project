#include "MultiTexture.h"


PFNGLMULTITEXCOORD2FARBPROC m_glMultiTexCoord2fARB = NULL;
PFNGLACTIVETEXTUREARBPROC m_glActiveTextureARB = NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC m_glClientActiveTextureARB = NULL;

bool initMultiTextures(void)
{
	// Initialize the multitexturing functions
	m_glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)
		wglGetProcAddress("glActiveTextureARB");
	m_glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)
		wglGetProcAddress("glMultiTexCoord2fARB");
	m_glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC)
		wglGetProcAddress("glClientActiveTextureARB");
	// Make sure that an appropriate version of OpenGL is installed.
	// If the extension functions could not be found then the function pointers will be NULL
	if (!m_glActiveTextureARB || !m_glMultiTexCoord2fARB)
		return false;
	else
		return true;
}
