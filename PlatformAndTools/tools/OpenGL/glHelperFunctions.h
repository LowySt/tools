#pragma once

#include "glCoreARB.h"
#include "wglExt.h"
#include "tools\lsCRT.h"

#define internal static

extern "C"
{

	///////////////////////////////////////////////////////////////////////////////////////////
	//					FUNCTION POINTERS
	///////////////////////////////////////////////////////////////////////////////////////////

	//
	//	Extensions
	//

#pragma region Extension Fn Pointers

//WGL_ARB_extensions_string
	__declspec(selectany) PFNWGLGETEXTENSIONSSTRINGARBPROC				wglGetExtensionsStringARB;

	//WGL_ARB_pixel_format
	__declspec(selectany) PFNWGLGETPIXELFORMATATTRIBIVARBPROC			wglGetPixelFormatAttribivARB;
	__declspec(selectany) PFNWGLGETPIXELFORMATATTRIBFVARBPROC			wglGetPixelFormatAttribfvARB;
	__declspec(selectany) PFNWGLCHOOSEPIXELFORMATARBPROC				wglChoosePixelFormatARB;

	//WGL_EXT_swap_control
	__declspec(selectany) PFNWGLSWAPINTERVALEXTPROC						wglSwapIntervalEXT;
	__declspec(selectany) PFNWGLGETSWAPINTERVALEXTPROC					wglGetSwapIntervalEXT;

	//WGL_ARB_pbuffer
	__declspec(selectany) PFNWGLCREATEPBUFFERARBPROC					wglCreatePbufferARB;
	__declspec(selectany) PFNWGLGETPBUFFERDCARBPROC						wglGetPbufferDCARB;
	__declspec(selectany) PFNWGLRELEASEPBUFFERDCARBPROC					wglReleasePbufferDCARB;
	__declspec(selectany) PFNWGLDESTROYPBUFFERARBPROC					wglDestroyPbufferARB;
	__declspec(selectany) PFNWGLQUERYPBUFFERARBPROC						wglQueryPbufferARB;

	//WGL_ARB_render_texture
	__declspec(selectany) PFNWGLBINDTEXIMAGEARBPROC						wglBindTexImageARB;
	__declspec(selectany) PFNWGLRELEASETEXIMAGEARBPROC					wglReleaseTexImageARB;
	__declspec(selectany) PFNWGLSETPBUFFERATTRIBARBPROC					wglSetPbufferAttribARB;

	//WGL_ARB_make_current_read
	__declspec(selectany) PFNWGLMAKECONTEXTCURRENTARBPROC				wglMakeContextCurrentARB;
	__declspec(selectany) PFNWGLGETCURRENTREADDCARBPROC					wglGetCurrentReadDCARB;

	//WGL_EXT_extensions_string
	__declspec(selectany) PFNWGLGETEXTENSIONSSTRINGEXTPROC				wglGetExtensionsStringEXT;

	//WGL_ARB_buffer_region
	__declspec(selectany) PFNWGLCREATEBUFFERREGIONARBPROC				wglCreateBufferRegionARB;
	__declspec(selectany) PFNWGLDELETEBUFFERREGIONARBPROC				wglDeleteBufferRegionARB;
	__declspec(selectany) PFNWGLSAVEBUFFERREGIONARBPROC					wglSaveBufferRegionARB;
	__declspec(selectany) PFNWGLRESTOREBUFFERREGIONARBPROC				wglRestoreBufferRegionARB;

	//WGL_ATI_render_texture_rectangle NOTE: NOT FOUND IN MY wglExt.h FILE DOWNLOADED FROM OPENGL REFERENCE SITE!!!

	//WGL_I3D_genlock
	__declspec(selectany) PFNWGLENABLEGENLOCKI3DPROC					wglEnableGenlockI3D;
	__declspec(selectany) PFNWGLDISABLEGENLOCKI3DPROC					wglDisableGenlockI3D;
	__declspec(selectany) PFNWGLISENABLEDGENLOCKI3DPROC					wglIsEnabledGenlockI3D;
	__declspec(selectany) PFNWGLGENLOCKSOURCEI3DPROC					wglGenlockSourceI3D;
	__declspec(selectany) PFNWGLGETGENLOCKSOURCEI3DPROC					wglGetGenlockSourceI3D;
	__declspec(selectany) PFNWGLGENLOCKSOURCEEDGEI3DPROC				wglGenlockSourceEdgeI3D;
	__declspec(selectany) PFNWGLGETGENLOCKSOURCEEDGEI3DPROC				wglGetGenlockSourceEdgeI3D;
	__declspec(selectany) PFNWGLGENLOCKSAMPLERATEI3DPROC				wglGenlockSampleRateI3D;
	__declspec(selectany) PFNWGLGETGENLOCKSAMPLERATEI3DPROC				wglGetGenlockSampleRateI3D;
	__declspec(selectany) PFNWGLGENLOCKSOURCEDELAYI3DPROC				wglGenlockSourceDelayI3D;
	__declspec(selectany) PFNWGLGETGENLOCKSOURCEDELAYI3DPROC			wglGetGenlockSourceDelayI3D;
	__declspec(selectany) PFNWGLQUERYGENLOCKMAXSOURCEDELAYI3DPROC		wglQueryGenlockMaxSourceDelayI3D;

	//WGL_NV_swap_group
	__declspec(selectany) PFNWGLJOINSWAPGROUPNVPROC						wglJoinSwapGroupNV;
	__declspec(selectany) PFNWGLBINDSWAPBARRIERNVPROC					wglBindSwapBarrierNV;
	__declspec(selectany) PFNWGLQUERYSWAPGROUPNVPROC					wglQuerySwapGroupNV;
	__declspec(selectany) PFNWGLQUERYMAXSWAPGROUPSNVPROC				wglQueryMaxSwapGroupsNV;
	__declspec(selectany) PFNWGLQUERYFRAMECOUNTNVPROC					wglQueryFrameCountNV;
	__declspec(selectany) PFNWGLRESETFRAMECOUNTNVPROC					wglResetFrameCountNV;

	//WGL_ARB_create_context
	__declspec(selectany) PFNWGLCREATECONTEXTATTRIBSARBPROC				wglCreateContextAttribsARB;

	//WGL_AMD_gpu_association
	__declspec(selectany) PFNWGLGETGPUIDSAMDPROC						wglGetGPUIDsAMD;
	__declspec(selectany) PFNWGLGETGPUINFOAMDPROC						wglGetGPUInfoAMD;
	__declspec(selectany) PFNWGLGETCONTEXTGPUIDAMDPROC					wglGetContextGPUIDAMD;
	__declspec(selectany) PFNWGLCREATEASSOCIATEDCONTEXTAMDPROC			wglCreateAssociatedContextAMD;
	__declspec(selectany) PFNWGLCREATEASSOCIATEDCONTEXTATTRIBSAMDPROC	wglCreateAssociatedContextAttribsAMD;
	__declspec(selectany) PFNWGLDELETEASSOCIATEDCONTEXTAMDPROC			wglDeleteAssociatedContextAMD;
	__declspec(selectany) PFNWGLMAKEASSOCIATEDCONTEXTCURRENTAMDPROC		wglMakeAssociatedContextCurrentAMD;
	__declspec(selectany) PFNWGLGETCURRENTASSOCIATEDCONTEXTAMDPROC		wglGetCurrentAssociatedContextAMD;
	__declspec(selectany) PFNWGLBLITCONTEXTFRAMEBUFFERAMDPROC			wglBlitContextFramebufferAMD;

	//WGL_AMDX_gpu_association NOTE: ANOTHER ONE WITH NOTHING IN wglExt.h FILE!

	//WGL_NV_DX_interop
	__declspec(selectany) PFNWGLDXSETRESOURCESHAREHANDLENVPROC			wglDXSetResourceShareHandleNV;
	__declspec(selectany) PFNWGLDXOPENDEVICENVPROC						wglDXOpenDeviceNV;
	__declspec(selectany) PFNWGLDXCLOSEDEVICENVPROC						wglDXCloseDeviceNV;
	__declspec(selectany) PFNWGLDXREGISTEROBJECTNVPROC					wglDXRegisterObjectNV;
	__declspec(selectany) PFNWGLDXUNREGISTEROBJECTNVPROC				wglDXUnregisterObjectNV;
	__declspec(selectany) PFNWGLDXOBJECTACCESSNVPROC					wglDXObjectAccessNV;
	__declspec(selectany) PFNWGLDXLOCKOBJECTSNVPROC						wglDXLockObjectsNV;
	__declspec(selectany) PFNWGLDXUNLOCKOBJECTSNVPROC					wglDXUnlockObjectsNV;

#pragma endregion

	//
	//	GL Functions
	//

	// Debug/Init Functions
	__declspec(selectany) PFNGLGETERRORPROC							glGetError;
	__declspec(selectany) PFNGLGETINTEGERVPROC						glGetIntegerv;
	__declspec(selectany) PFNGLGETSTRINGIPROC						glGetStringi;
	__declspec(selectany) PFNGLGETSTRINGPROC						glGetString;

	__declspec(selectany) PFNGLGETSHADERIVPROC						glGetShaderiv;
	__declspec(selectany) PFNGLGETSHADERINFOLOGPROC					glGetShaderInfoLog;
	__declspec(selectany) PFNGLGETPROGRAMIVPROC						glGetProgramiv;
	__declspec(selectany) PFNGLGETPROGRAMINFOLOGPROC				glGetProgramInfoLog;

	__declspec(selectany) PFNGLENABLEPROC							glEnable;
	__declspec(selectany) PFNGLFINISHPROC							glFinish;

	// Blitting Functions
	__declspec(selectany) PFNGLVIEWPORTPROC							glViewport;
	__declspec(selectany) PFNGLCLEARCOLORPROC						glClearColor;
	__declspec(selectany) PFNGLCLEARPROC							glClear;
	__declspec(selectany) PFNGLDRAWARRAYSPROC						glDrawArrays;
	__declspec(selectany) PFNGLDRAWELEMENTSPROC						glDrawElements;

	// GPU Memory Managment
	__declspec(selectany) PFNGLGENBUFFERSPROC						glGenBuffers;
	__declspec(selectany) PFNGLGENVERTEXARRAYSPROC					glGenVertexArrays;
	__declspec(selectany) PFNGLBINDBUFFERPROC						glBindBuffer;
	__declspec(selectany) PFNGLBINDVERTEXARRAYPROC					glBindVertexArray;
	__declspec(selectany) PFNGLBUFFERDATAPROC						glBufferData;

	// Shader Functions
	__declspec(selectany) PFNGLCREATESHADERPROC						glCreateShader;
	__declspec(selectany) PFNGLCREATEPROGRAMPROC					glCreateProgram;
	__declspec(selectany) PFNGLDELETESHADERPROC						glDeleteShader;

	__declspec(selectany) PFNGLSHADERSOURCEPROC						glShaderSource;
	__declspec(selectany) PFNGLCOMPILESHADERPROC					glCompileShader;
	__declspec(selectany) PFNGLATTACHSHADERPROC						glAttachShader;
	__declspec(selectany) PFNGLLINKPROGRAMPROC						glLinkProgram;
	__declspec(selectany) PFNGLUSEPROGRAMPROC						glUseProgram;

	__declspec(selectany) PFNGLGETUNIFORMLOCATIONPROC				glGetUniformLocation;
	__declspec(selectany) PFNGLUNIFORM4FPROC						glUniform4f;
	__declspec(selectany) PFNGLUNIFORM3FPROC						glUniform3f;
	__declspec(selectany) PFNGLUNIFORM2FPROC						glUniform2f;
	__declspec(selectany) PFNGLUNIFORM1FPROC						glUniform1f;

	__declspec(selectany) PFNGLUNIFORM4FVPROC						glUniform4fv;
	__declspec(selectany) PFNGLUNIFORM3FVPROC						glUniform3fv;
	__declspec(selectany) PFNGLUNIFORM2FVPROC						glUniform2fv;
	__declspec(selectany) PFNGLUNIFORM1FVPROC						glUniform1fv;

	__declspec(selectany) PFNGLUNIFORMMATRIX4FVPROC					glUniformMatrix4fv;
	__declspec(selectany) PFNGLUNIFORMMATRIX3FVPROC					glUniformMatrix3fv;
	__declspec(selectany) PFNGLUNIFORMMATRIX2FVPROC					glUniformMatrix2fv;

	__declspec(selectany) PFNGLUNIFORM4DPROC						glUniform4d;
	__declspec(selectany) PFNGLUNIFORM3DPROC						glUniform3d;
	__declspec(selectany) PFNGLUNIFORM2DPROC						glUniform2d;
	__declspec(selectany) PFNGLUNIFORM1DPROC						glUniform1d;

	__declspec(selectany) PFNGLUNIFORM4IPROC						glUniform4i;
	__declspec(selectany) PFNGLUNIFORM3IPROC						glUniform3i;
	__declspec(selectany) PFNGLUNIFORM2IPROC						glUniform2i;
	__declspec(selectany) PFNGLUNIFORM1IPROC						glUniform1i;

	__declspec(selectany) PFNGLTEXPARAMETERIPROC					glTexParameteri;
	__declspec(selectany) PFNGLTEXPARAMETERFVPROC					glTexParameterfv;

	__declspec(selectany) PFNGLVERTEXATTRIBPOINTERPROC				glVertexAttribPointer;
	__declspec(selectany) PFNGLENABLEVERTEXATTRIBARRAYPROC			glEnableVertexAttribArray;

	// Texture Functions

	__declspec(selectany) PFNGLGENTEXTURESPROC						glGenTextures;
	__declspec(selectany) PFNGLBINDTEXTUREPROC						glBindTexture;
	__declspec(selectany) PFNGLTEXIMAGE2DPROC						glTexImage2D;
	__declspec(selectany) PFNGLACTIVETEXTUREPROC					glActiveTexture;

	__declspec(selectany) PFNGLGENERATEMIPMAPPROC					glGenerateMipmap;


	///////////////////////////////////////////////////////////////////////////////////////////
	//					LOADING FUNCTIONS
	///////////////////////////////////////////////////////////////////////////////////////////

	internal void *GetAnyGLFuncAddress(const char *name)
	{
		void *p = (void *)wglGetProcAddress(name);
		if ((p == 0) || (p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) || (p == (void*)-1))
		{
			HMODULE module = LoadLibraryA("opengl32.dll");
			p = (void *)GetProcAddress(module, name);
		}

		return p;
	}

	internal GLint getGLVersion()
	{
		GLint Result = 0;
		GLint Major = 0;
		GLint Minor = 0;

		glGetIntegerv(GL_MAJOR_VERSION, &Major);
		if (Major == 0)
		{
			GLenum Error = glGetError();
			LogErrori("In getGLVersion error: ", Error);
		}

		glGetIntegerv(GL_MINOR_VERSION, &Minor);
		if (Minor == 0)
		{
			GLenum Error = glGetError();
			LogErrori("In getGLVersion error: ", Error);
		}

		Result = (Major * 10) + Minor;
		return Result;
	}

	internal void LoadGLFunc(HDC DeviceContext)
	{
		glGetIntegerv	= (PFNGLGETINTEGERVPROC)GetAnyGLFuncAddress("glGetIntegerv");
		glGetStringi	= (PFNGLGETSTRINGIPROC)GetAnyGLFuncAddress("glGetStringi");
		glGetString		= (PFNGLGETSTRINGPROC)GetAnyGLFuncAddress("glGetString");
		glGetError		= (PFNGLGETERRORPROC)GetAnyGLFuncAddress("glGetError");

		GLint Version = getGLVersion();
		wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)GetAnyGLFuncAddress("wglGetExtensionsStringARB");
		const char *extensions = wglGetExtensionsStringARB(DeviceContext);

		//@TODO: This is actually not enough to check if we have these extensions, gonna have to implement more extensive checks later.
#pragma region Load Extension Fn Pointers
#ifdef WGL_ARB_pixel_format
		wglGetPixelFormatAttribivARB			= (PFNWGLGETPIXELFORMATATTRIBIVARBPROC)GetAnyGLFuncAddress("wglGetPixelFormatAttribivARB");
		wglGetPixelFormatAttribfvARB			= (PFNWGLGETPIXELFORMATATTRIBFVARBPROC)GetAnyGLFuncAddress("wglGetPixelFormatAttribfvARB");
		wglChoosePixelFormatARB					= (PFNWGLCHOOSEPIXELFORMATARBPROC)GetAnyGLFuncAddress("wglChoosePixelFormatARB");
#endif
#ifdef WGL_EXT_swap_control
		wglSwapIntervalEXT						= (PFNWGLSWAPINTERVALEXTPROC)GetAnyGLFuncAddress("wglSwapIntervalEXT");
		wglGetSwapIntervalEXT					= (PFNWGLGETSWAPINTERVALEXTPROC)GetAnyGLFuncAddress("wglGetSwapIntervalEXT");
#endif
#ifdef WGL_ARB_pbuffer
		wglCreatePbufferARB						= (PFNWGLCREATEPBUFFERARBPROC)GetAnyGLFuncAddress("wglCreatePbufferARB");
		wglGetPbufferDCARB						= (PFNWGLGETPBUFFERDCARBPROC)GetAnyGLFuncAddress("wglGetPbufferDCARB");
		wglReleasePbufferDCARB					= (PFNWGLRELEASEPBUFFERDCARBPROC)GetAnyGLFuncAddress("wglReleasePbufferDCARB");
		wglDestroyPbufferARB					= (PFNWGLDESTROYPBUFFERARBPROC)GetAnyGLFuncAddress("wglDestroyPbufferARB");
		wglQueryPbufferARB						= (PFNWGLQUERYPBUFFERARBPROC)GetAnyGLFuncAddress("wglQueryPbufferARB");
#endif
#ifdef WGL_ARB_render_texture
		wglBindTexImageARB						= (PFNWGLBINDTEXIMAGEARBPROC)GetAnyGLFuncAddress("wglBindTexImageARB");
		wglReleaseTexImageARB					= (PFNWGLRELEASETEXIMAGEARBPROC)GetAnyGLFuncAddress("wglReleaseTexImageARB");
		wglSetPbufferAttribARB					= (PFNWGLSETPBUFFERATTRIBARBPROC)GetAnyGLFuncAddress("wglSetPbufferAttribARB");
#endif
#ifdef WGL_ARB_make_current_read
		wglMakeContextCurrentARB				= (PFNWGLMAKECONTEXTCURRENTARBPROC)GetAnyGLFuncAddress("wglMakeContextCurrentARB");
		wglGetCurrentReadDCARB					= (PFNWGLGETCURRENTREADDCARBPROC)GetAnyGLFuncAddress("wglGetCurrentReadDCARB");
#endif
#ifdef WGL_EXT_extensions_string
		wglGetExtensionsStringEXT				= (PFNWGLGETEXTENSIONSSTRINGEXTPROC)GetAnyGLFuncAddress("wglGetExtensionsStringEXT");
#endif
#ifdef WGL_ARB_buffer_region
		wglCreateBufferRegionARB				= (PFNWGLCREATEBUFFERREGIONARBPROC)GetAnyGLFuncAddress("wglCreateBufferRegionARB");
		wglDeleteBufferRegionARB				= (PFNWGLDELETEBUFFERREGIONARBPROC)GetAnyGLFuncAddress("wglDeleteBufferRegionARB");
		wglSaveBufferRegionARB					= (PFNWGLSAVEBUFFERREGIONARBPROC)GetAnyGLFuncAddress("wglSaveBufferRegionARB");
		wglRestoreBufferRegionARB				= (PFNWGLRESTOREBUFFERREGIONARBPROC)GetAnyGLFuncAddress("wglRestoreBufferRegionARB");
#endif
#ifdef WGL_I3D_genlock
		wglEnableGenlockI3D						= (PFNWGLENABLEGENLOCKI3DPROC)GetAnyGLFuncAddress("wglEnableGenlockI3D");
		wglDisableGenlockI3D					= (PFNWGLDISABLEGENLOCKI3DPROC)GetAnyGLFuncAddress("wglDisableGenlockI3D");
		wglIsEnabledGenlockI3D					= (PFNWGLISENABLEDGENLOCKI3DPROC)GetAnyGLFuncAddress("wglIsEnabledGenlockI3D");
		wglGenlockSourceI3D						= (PFNWGLGENLOCKSOURCEI3DPROC)GetAnyGLFuncAddress("wglGenlockSourceI3D");
		wglGetGenlockSourceI3D					= (PFNWGLGETGENLOCKSOURCEI3DPROC)GetAnyGLFuncAddress("wglGetGenlockSourceI3D");
		wglGenlockSourceEdgeI3D					= (PFNWGLGENLOCKSOURCEEDGEI3DPROC)GetAnyGLFuncAddress("wglGenlockSourceEdgeI3D");
		wglGetGenlockSourceEdgeI3D				= (PFNWGLGETGENLOCKSOURCEEDGEI3DPROC)GetAnyGLFuncAddress("wglGetGenlockSourceEdgeI3D");
		wglGenlockSampleRateI3D					= (PFNWGLGENLOCKSAMPLERATEI3DPROC)GetAnyGLFuncAddress("wglGenlockSampleRateI3D");
		wglGetGenlockSampleRateI3D				= (PFNWGLGETGENLOCKSAMPLERATEI3DPROC)GetAnyGLFuncAddress("wglGetGenlockSampleRateI3D");
		wglGenlockSourceDelayI3D				= (PFNWGLGENLOCKSOURCEDELAYI3DPROC)GetAnyGLFuncAddress("wglGenlockSourceDelayI3D");
		wglGetGenlockSourceDelayI3D				= (PFNWGLGETGENLOCKSOURCEDELAYI3DPROC)GetAnyGLFuncAddress("wglGetGenlockSourceDelayI3D");
		wglQueryGenlockMaxSourceDelayI3D		= (PFNWGLQUERYGENLOCKMAXSOURCEDELAYI3DPROC)GetAnyGLFuncAddress("wglQueryGenlockMaxSourceDelayI3D");
#endif
#ifdef WGL_NV_swap_group
		wglJoinSwapGroupNV						= (PFNWGLJOINSWAPGROUPNVPROC)GetAnyGLFuncAddress("wglJoinSwapGroupNV");
		wglBindSwapBarrierNV					= (PFNWGLBINDSWAPBARRIERNVPROC)GetAnyGLFuncAddress("wglBindSwapBarrierNV");
		wglQuerySwapGroupNV						= (PFNWGLQUERYSWAPGROUPNVPROC)GetAnyGLFuncAddress("wglQuerySwapGroupNV");
		wglQueryMaxSwapGroupsNV					= (PFNWGLQUERYMAXSWAPGROUPSNVPROC)GetAnyGLFuncAddress("wglQueryMaxSwapGroupsNV");
		wglQueryFrameCountNV					= (PFNWGLQUERYFRAMECOUNTNVPROC)GetAnyGLFuncAddress("wglQueryFrameCountNV");
		wglResetFrameCountNV					= (PFNWGLRESETFRAMECOUNTNVPROC)GetAnyGLFuncAddress("wglResetFrameCountNV");
#endif
#ifdef WGL_ARB_create_context
		wglCreateContextAttribsARB				= (PFNWGLCREATECONTEXTATTRIBSARBPROC)GetAnyGLFuncAddress("wglCreateContextAttribsARB");
#endif
#ifdef WGL_AMD_gpu_association
		wglGetGPUIDsAMD							= (PFNWGLGETGPUIDSAMDPROC)GetAnyGLFuncAddress("wglGetGPUIDsAMD");
		wglGetGPUInfoAMD						= (PFNWGLGETGPUINFOAMDPROC)GetAnyGLFuncAddress("wglGetGPUInfoAMD");
		wglGetContextGPUIDAMD					= (PFNWGLGETCONTEXTGPUIDAMDPROC)GetAnyGLFuncAddress("wglGetContextGPUIDAMD");
		wglCreateAssociatedContextAMD			= (PFNWGLCREATEASSOCIATEDCONTEXTAMDPROC)GetAnyGLFuncAddress("wglCreateAssociatedContextAMD");
		wglCreateAssociatedContextAttribsAMD	= (PFNWGLCREATEASSOCIATEDCONTEXTATTRIBSAMDPROC)GetAnyGLFuncAddress("wglCreateAssociatedContextAttribsAMD");
		wglDeleteAssociatedContextAMD			= (PFNWGLDELETEASSOCIATEDCONTEXTAMDPROC)GetAnyGLFuncAddress("wglDeleteAssociatedContextAMD");
		wglMakeAssociatedContextCurrentAMD		= (PFNWGLMAKEASSOCIATEDCONTEXTCURRENTAMDPROC)GetAnyGLFuncAddress("wglMakeAssociatedContextCurrentAMD");
		wglGetCurrentAssociatedContextAMD		= (PFNWGLGETCURRENTASSOCIATEDCONTEXTAMDPROC)GetAnyGLFuncAddress("wglGetCurrentAssociatedContextAMD");
		wglBlitContextFramebufferAMD			= (PFNWGLBLITCONTEXTFRAMEBUFFERAMDPROC)GetAnyGLFuncAddress("wglBlitContextFramebufferAMD");
#endif
#ifdef WGL_NV_DX_interop
		wglDXSetResourceShareHandleNV			= (PFNWGLDXSETRESOURCESHAREHANDLENVPROC)GetAnyGLFuncAddress("wglDXSetResourceShareHandleNV");
		wglDXOpenDeviceNV						= (PFNWGLDXOPENDEVICENVPROC)GetAnyGLFuncAddress("wglDXOpenDeviceNV");
		wglDXCloseDeviceNV						= (PFNWGLDXCLOSEDEVICENVPROC)GetAnyGLFuncAddress("wglDXCloseDeviceNV");
		wglDXRegisterObjectNV					= (PFNWGLDXREGISTEROBJECTNVPROC)GetAnyGLFuncAddress("wglDXRegisterObjectNV");
		wglDXUnregisterObjectNV					= (PFNWGLDXUNREGISTEROBJECTNVPROC)GetAnyGLFuncAddress("wglDXUnregisterObjectNV");
		wglDXObjectAccessNV						= (PFNWGLDXOBJECTACCESSNVPROC)GetAnyGLFuncAddress("wglDXObjectAccessNV");
		wglDXLockObjectsNV						= (PFNWGLDXLOCKOBJECTSNVPROC)GetAnyGLFuncAddress("wglDXLockObjectsNV");
		wglDXUnlockObjectsNV					= (PFNWGLDXUNLOCKOBJECTSNVPROC)GetAnyGLFuncAddress("wglDXUnlockObjectsNV");
#endif
#pragma endregion

		if (Version >= 33)
		{
			glGetShaderiv						= (PFNGLGETSHADERIVPROC)GetAnyGLFuncAddress("glGetShaderiv");
			glGetShaderInfoLog					= (PFNGLGETSHADERINFOLOGPROC)GetAnyGLFuncAddress("glGetShaderInfoLog");
			glGetProgramiv						= (PFNGLGETPROGRAMIVPROC)GetAnyGLFuncAddress("glGetProgramiv");
			glGetProgramInfoLog					= (PFNGLGETPROGRAMINFOLOGPROC)GetAnyGLFuncAddress("glGetProgramInfoLog");

			glEnable							= (PFNGLENABLEPROC)GetAnyGLFuncAddress("glEnable");
			glFinish							= (PFNGLFINISHPROC)GetAnyGLFuncAddress("glFinish");

			glViewport							= (PFNGLVIEWPORTPROC)GetAnyGLFuncAddress("glViewport");
			glClearColor						= (PFNGLCLEARCOLORPROC)GetAnyGLFuncAddress("glClearColor");
			glClear								= (PFNGLCLEARPROC)GetAnyGLFuncAddress("glClear");
			glDrawArrays						= (PFNGLDRAWARRAYSPROC)GetAnyGLFuncAddress("glDrawArrays");
			glDrawElements						= (PFNGLDRAWELEMENTSPROC)GetAnyGLFuncAddress("glDrawElements");

			glGenBuffers						= (PFNGLGENBUFFERSPROC)GetAnyGLFuncAddress("glGenBuffers");
			glGenVertexArrays					= (PFNGLGENVERTEXARRAYSPROC)GetAnyGLFuncAddress("glGenVertexArrays");
			glBindBuffer						= (PFNGLBINDBUFFERPROC)GetAnyGLFuncAddress("glBindBuffer");
			glBindVertexArray					= (PFNGLBINDVERTEXARRAYPROC)GetAnyGLFuncAddress("glBindVertexArray");
			glBufferData						= (PFNGLBUFFERDATAPROC)GetAnyGLFuncAddress("glBufferData");

			glCreateShader						= (PFNGLCREATESHADERPROC)GetAnyGLFuncAddress("glCreateShader");
			glCreateProgram						= (PFNGLCREATEPROGRAMPROC)GetAnyGLFuncAddress("glCreateProgram");
			glDeleteShader						= (PFNGLDELETESHADERPROC)GetAnyGLFuncAddress("glDeleteShader");

			glShaderSource						= (PFNGLSHADERSOURCEPROC)GetAnyGLFuncAddress("glShaderSource");
			glCompileShader						= (PFNGLCOMPILESHADERPROC)GetAnyGLFuncAddress("glCompileShader");
			glAttachShader						= (PFNGLATTACHSHADERPROC)GetAnyGLFuncAddress("glAttachShader");
			glLinkProgram						= (PFNGLLINKPROGRAMPROC)GetAnyGLFuncAddress("glLinkProgram");
			glUseProgram						= (PFNGLUSEPROGRAMPROC)GetAnyGLFuncAddress("glUseProgram");

			glGetUniformLocation				= (PFNGLGETUNIFORMLOCATIONPROC)GetAnyGLFuncAddress("glGetUniformLocation");
			glUniform4f							= (PFNGLUNIFORM4FPROC)GetAnyGLFuncAddress("glUniform4f");
			glUniform3f							= (PFNGLUNIFORM3FPROC)GetAnyGLFuncAddress("glUniform3f");
			glUniform2f							= (PFNGLUNIFORM2FPROC)GetAnyGLFuncAddress("glUniform2f");
			glUniform1f							= (PFNGLUNIFORM1FPROC)GetAnyGLFuncAddress("glUniform1f");

			glUniform4fv						= (PFNGLUNIFORM4FVPROC)GetAnyGLFuncAddress("glUniform4fv");
			glUniform3fv						= (PFNGLUNIFORM3FVPROC)GetAnyGLFuncAddress("glUniform3fv");
			glUniform2fv						= (PFNGLUNIFORM2FVPROC)GetAnyGLFuncAddress("glUniform2fv");
			glUniform1fv						= (PFNGLUNIFORM1FVPROC)GetAnyGLFuncAddress("glUniform1fv");

			glUniformMatrix4fv					= (PFNGLUNIFORMMATRIX4FVPROC)GetAnyGLFuncAddress("glUniformMatrix4fv");
			glUniformMatrix3fv					= (PFNGLUNIFORMMATRIX3FVPROC)GetAnyGLFuncAddress("glUniformMatrix3fv");
			glUniformMatrix2fv					= (PFNGLUNIFORMMATRIX2FVPROC)GetAnyGLFuncAddress("glUniformMatrix2fv");

			glUniform4d							= (PFNGLUNIFORM4DPROC)GetAnyGLFuncAddress("glUniform4d");
			glUniform3d							= (PFNGLUNIFORM3DPROC)GetAnyGLFuncAddress("glUniform3d");
			glUniform2d							= (PFNGLUNIFORM2DPROC)GetAnyGLFuncAddress("glUniform2d");
			glUniform1d							= (PFNGLUNIFORM1DPROC)GetAnyGLFuncAddress("glUniform1d");

			glUniform4i							= (PFNGLUNIFORM4IPROC)GetAnyGLFuncAddress("glUniform4i");
			glUniform3i							= (PFNGLUNIFORM3IPROC)GetAnyGLFuncAddress("glUniform3i");
			glUniform2i							= (PFNGLUNIFORM2IPROC)GetAnyGLFuncAddress("glUniform2i");
			glUniform1i							= (PFNGLUNIFORM1IPROC)GetAnyGLFuncAddress("glUniform1i");

			glTexParameteri						= (PFNGLTEXPARAMETERIPROC)GetAnyGLFuncAddress("glTexParameteri");
			glTexParameterfv					= (PFNGLTEXPARAMETERFVPROC)GetAnyGLFuncAddress("glTexParameterfv");

			glVertexAttribPointer				= (PFNGLVERTEXATTRIBPOINTERPROC)GetAnyGLFuncAddress("glVertexAttribPointer");
			glEnableVertexAttribArray			= (PFNGLENABLEVERTEXATTRIBARRAYPROC)GetAnyGLFuncAddress("glEnableVertexAttribArray");

			glGenTextures						= (PFNGLGENTEXTURESPROC)GetAnyGLFuncAddress("glGenTextures");
			glBindTexture						= (PFNGLBINDTEXTUREPROC)GetAnyGLFuncAddress("glBindTexture");
			glTexImage2D						= (PFNGLTEXIMAGE2DPROC)GetAnyGLFuncAddress("glTexImage2D");
			glActiveTexture						= (PFNGLACTIVETEXTUREPROC)GetAnyGLFuncAddress("glActiveTexture");

			glGenerateMipmap					= (PFNGLGENERATEMIPMAPPROC)GetAnyGLFuncAddress("glGenerateMipmap");
		}
	}
}