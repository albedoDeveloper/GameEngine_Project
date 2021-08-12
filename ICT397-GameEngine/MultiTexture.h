#ifndef __MULTITEXTURE_H
#define __MULTITEXTURE_H

#ifdef __cplusplus
extern "C" {
#endif
#if _MCS_VER >= 1020
#pragma once
#endif
#if defined(_WIN32) && !defined(APIENTRY) && !defined(__CYGWIN__)
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#endif
#ifndef APIENTRY
#define APIENTRY
#endif
#include <GL/gl.h> // Header File For The OpenGL32 Library
#include <GL/glu.h> // Header File For The GLu32 Library
#define GL_TEXTURE0_ARB 0x84C0
#define GL_TEXTURE1_ARB 0x84C1
#define GL_COMBINE_ARB 0x8570
#define GL_RGB_SCALE_ARB 0x8573
	typedef void (APIENTRY* PFNGLMULTITEXCOORD2FARBPROC) (GLenum target, GLfloat s, GLfloat t);
	typedef void (APIENTRY* PFNGLACTIVETEXTUREARBPROC) (GLenum target);
	typedef void (APIENTRY* PFNGLCLIENTACTIVETEXTUREARBPROC) (GLenum target);
	bool initMultiTextures(void);
	extern PFNGLMULTITEXCOORD2FARBPROC m_glMultiTexCoord2fARB;
	extern PFNGLACTIVETEXTUREARBPROC m_glActiveTextureARB;
	extern PFNGLCLIENTACTIVETEXTUREARBPROC m_glClientActiveTextureARB;
#ifdef __cplusplus
}
#endif
#endif