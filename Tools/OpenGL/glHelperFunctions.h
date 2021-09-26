#pragma once

#include "glCoreARB.h"
#include "wglExt.h"

#define internal static

#define GL_FN(a, b) __declspec(selectany) a b;
#define GET_FN(a, b) a = (b)GetAnyGLFuncAddress("a");

extern "C"
{
    
	///////////////////////////////////////////////////////////////////////////////////////////
	//					FUNCTION POINTERS
	///////////////////////////////////////////////////////////////////////////////////////////
    
	//
	//	Extensions
	//
    
    //WGL_ARB_extensions_string
	GL_FN(PFNWGLGETEXTENSIONSSTRINGARBPROC, wglGetExtensionsStringARB);
    
	//WGL_ARB_pixel_format
	GL_FN(PFNWGLGETPIXELFORMATATTRIBIVARBPROC, wglGetPixelFormatAttribivARB);	;
	GL_FN(PFNWGLGETPIXELFORMATATTRIBFVARBPROC, wglGetPixelFormatAttribfvARB);	;
	GL_FN(PFNWGLCHOOSEPIXELFORMATARBPROC, wglChoosePixelFormatARB);
    
	//WGL_EXT_swap_control
	GL_FN(PFNWGLSWAPINTERVALEXTPROC, wglSwapIntervalEXT);
	GL_FN(PFNWGLGETSWAPINTERVALEXTPROC, wglGetSwapIntervalEXT);
    
	//WGL_ARB_pbuffer
	GL_FN(PFNWGLCREATEPBUFFERARBPROC, wglCreatePbufferARB);
	GL_FN(PFNWGLGETPBUFFERDCARBPROC, wglGetPbufferDCARB);
	GL_FN(PFNWGLRELEASEPBUFFERDCARBPROC, wglReleasePbufferDCARB);	;
	GL_FN(PFNWGLDESTROYPBUFFERARBPROC, wglDestroyPbufferARB);
	GL_FN(PFNWGLQUERYPBUFFERARBPROC, wglQueryPbufferARB);
    
	//WGL_ARB_render_texture
	GL_FN(PFNWGLBINDTEXIMAGEARBPROC, wglBindTexImageARB);
	GL_FN(PFNWGLRELEASETEXIMAGEARBPROC, wglReleaseTexImageARB);
	GL_FN(PFNWGLSETPBUFFERATTRIBARBPROC, wglSetPbufferAttribARB);	;
    
	//WGL_ARB_make_current_read
	GL_FN(PFNWGLMAKECONTEXTCURRENTARBPROC, wglMakeContextCurrentARB);	;
	GL_FN(PFNWGLGETCURRENTREADDCARBPROC, wglGetCurrentReadDCARB);	;
    
	//WGL_EXT_extensions_string
	GL_FN(PFNWGLGETEXTENSIONSSTRINGEXTPROC, wglGetExtensionsStringEXT);	;
    
	//WGL_ARB_buffer_region
	GL_FN(PFNWGLCREATEBUFFERREGIONARBPROC, wglCreateBufferRegionARB);	;
	GL_FN(PFNWGLDELETEBUFFERREGIONARBPROC, wglDeleteBufferRegionARB);	;
	GL_FN(PFNWGLSAVEBUFFERREGIONARBPROC, wglSaveBufferRegionARB);	;
	GL_FN(PFNWGLRESTOREBUFFERREGIONARBPROC, wglRestoreBufferRegionARB);	;
    
	//WGL_ATI_render_texture_rectangle NOTE: NOT FOUND IN MY wglExt.h FILE DOWNLOADED FROM OPENGL REFERENCE SITE!!!
    
	//WGL_I3D_genlock
	GL_FN(PFNWGLENABLEGENLOCKI3DPROC, wglEnableGenlockI3D);
	GL_FN(PFNWGLDISABLEGENLOCKI3DPROC, wglDisableGenlockI3D);
	GL_FN(PFNWGLISENABLEDGENLOCKI3DPROC, wglIsEnabledGenlockI3D);	;
	GL_FN(PFNWGLGENLOCKSOURCEI3DPROC, wglGenlockSourceI3D);
	GL_FN(PFNWGLGETGENLOCKSOURCEI3DPROC, wglGetGenlockSourceI3D);	;
	GL_FN(PFNWGLGENLOCKSOURCEEDGEI3DPROC, wglGenlockSourceEdgeI3D);
	GL_FN(PFNWGLGETGENLOCKSOURCEEDGEI3DPROC, wglGetGenlockSourceEdgeI3D);	;
	GL_FN(PFNWGLGENLOCKSAMPLERATEI3DPROC, wglGenlockSampleRateI3D);
	GL_FN(PFNWGLGETGENLOCKSAMPLERATEI3DPROC, wglGetGenlockSampleRateI3D);	;
	GL_FN(PFNWGLGENLOCKSOURCEDELAYI3DPROC, wglGenlockSourceDelayI3D);	;
	GL_FN(PFNWGLGETGENLOCKSOURCEDELAYI3DPROC, wglGetGenlockSourceDelayI3D);	;
	GL_FN(PFNWGLQUERYGENLOCKMAXSOURCEDELAYI3DPROC, wglQueryGenlockMaxSourceDelayI3D);	;
    
	//WGL_NV_swap_group
	GL_FN(PFNWGLJOINSWAPGROUPNVPROC, wglJoinSwapGroupNV);
	GL_FN(PFNWGLBINDSWAPBARRIERNVPROC, wglBindSwapBarrierNV);
	GL_FN(PFNWGLQUERYSWAPGROUPNVPROC, wglQuerySwapGroupNV);
	GL_FN(PFNWGLQUERYMAXSWAPGROUPSNVPROC, wglQueryMaxSwapGroupsNV);
	GL_FN(PFNWGLQUERYFRAMECOUNTNVPROC, wglQueryFrameCountNV);
	GL_FN(PFNWGLRESETFRAMECOUNTNVPROC, wglResetFrameCountNV);
    
	//WGL_ARB_create_context
	GL_FN(PFNWGLCREATECONTEXTATTRIBSARBPROC, wglCreateContextAttribsARB);	;
    
	//WGL_AMD_gpu_association
	GL_FN(PFNWGLGETGPUIDSAMDPROC, wglGetGPUIDsAMD);
	GL_FN(PFNWGLGETGPUINFOAMDPROC, wglGetGPUInfoAMD);
	GL_FN(PFNWGLGETCONTEXTGPUIDAMDPROC, wglGetContextGPUIDAMD);
	GL_FN(PFNWGLCREATEASSOCIATEDCONTEXTAMDPROC, wglCreateAssociatedContextAMD);	;
	GL_FN(PFNWGLCREATEASSOCIATEDCONTEXTATTRIBSAMDPROC, wglCreateAssociatedContextAttribsAMD);
	GL_FN(PFNWGLDELETEASSOCIATEDCONTEXTAMDPROC, wglDeleteAssociatedContextAMD);	;
	GL_FN(PFNWGLMAKEASSOCIATEDCONTEXTCURRENTAMDPROC, wglMakeAssociatedContextCurrentAMD);
	GL_FN(PFNWGLGETCURRENTASSOCIATEDCONTEXTAMDPROC, wglGetCurrentAssociatedContextAMD);
	GL_FN(PFNWGLBLITCONTEXTFRAMEBUFFERAMDPROC, wglBlitContextFramebufferAMD);	;
    
	//WGL_AMDX_gpu_association NOTE: ANOTHER ONE WITH NOTHING IN wglExt.h FILE!
    
	//WGL_NV_DX_interop
	GL_FN(PFNWGLDXSETRESOURCESHAREHANDLENVPROC, wglDXSetResourceShareHandleNV);	;
	GL_FN(PFNWGLDXOPENDEVICENVPROC, wglDXOpenDeviceNV);
	GL_FN(PFNWGLDXCLOSEDEVICENVPROC, wglDXCloseDeviceNV);
	GL_FN(PFNWGLDXREGISTEROBJECTNVPROC, wglDXRegisterObjectNV);
	GL_FN(PFNWGLDXUNREGISTEROBJECTNVPROC, wglDXUnregisterObjectNV);
	GL_FN(PFNWGLDXOBJECTACCESSNVPROC, wglDXObjectAccessNV);
	GL_FN(PFNWGLDXLOCKOBJECTSNVPROC, wglDXLockObjectsNV);
	GL_FN(PFNWGLDXUNLOCKOBJECTSNVPROC, wglDXUnlockObjectsNV);
    
    
    
	//
	//	GL Functions
	//
    
	// Debug/Init Functions
	GL_FN(PFNGLGETERRORPROC, glGetError);
	GL_FN(PFNGLGETINTEGERVPROC, glGetIntegerv);
	GL_FN(PFNGLGETSTRINGIPROC, glGetStringi);
	GL_FN(PFNGLGETSTRINGPROC, glGetString);
    
	GL_FN(PFNGLGETSHADERIVPROC, glGetShaderiv);
	GL_FN(PFNGLGETSHADERINFOLOGPROC, glGetShaderInfoLog);
	GL_FN(PFNGLGETPROGRAMIVPROC, glGetProgramiv);
	GL_FN(PFNGLGETPROGRAMINFOLOGPROC, glGetProgramInfoLog);
    
	GL_FN(PFNGLENABLEPROC, glEnable);
	GL_FN(PFNGLFINISHPROC, glFinish);
    
	// Blitting Functions
	GL_FN(PFNGLVIEWPORTPROC, glViewport);
	GL_FN(PFNGLCLEARCOLORPROC, glClearColor);
	GL_FN(PFNGLCLEARPROC, glClear);
    GL_FN(PFNGLCLEARDEPTHPROC, glClearDepth);
    GL_FN(PFNGLDEPTHFUNCPROC, glDepthFunc);
	GL_FN(PFNGLDRAWARRAYSPROC, glDrawArrays);
	GL_FN(PFNGLDRAWELEMENTSPROC, glDrawElements);
    
	// GPU Memory Managment
	GL_FN(PFNGLGENBUFFERSPROC, glGenBuffers);
    GL_FN(PFNGLDELETEBUFFERSPROC, glDeleteBuffers);
	GL_FN(PFNGLGENVERTEXARRAYSPROC, glGenVertexArrays);
    GL_FN(PFNGLDELETEVERTEXARRAYSPROC, glDeleteVertexArrays);
	GL_FN(PFNGLBINDBUFFERPROC, glBindBuffer);
	GL_FN(PFNGLBINDVERTEXARRAYPROC, glBindVertexArray);
	GL_FN(PFNGLBUFFERDATAPROC, glBufferData);
    GL_FN(PFNGLPIXELSTOREIPROC, glPixelStorei);
    
	// Shader Functions
	GL_FN(PFNGLCREATESHADERPROC, glCreateShader);
	GL_FN(PFNGLCREATEPROGRAMPROC, glCreateProgram);
	GL_FN(PFNGLDELETESHADERPROC, glDeleteShader);
    
	GL_FN(PFNGLSHADERSOURCEPROC, glShaderSource);
	GL_FN(PFNGLCOMPILESHADERPROC, glCompileShader);
	GL_FN(PFNGLATTACHSHADERPROC, glAttachShader);
    GL_FN(PFNGLBINDFRAGDATALOCATIONPROC, glBindFragDataLocation);
	GL_FN(PFNGLLINKPROGRAMPROC, glLinkProgram);
	GL_FN(PFNGLUSEPROGRAMPROC, glUseProgram);
    
	GL_FN(PFNGLGETUNIFORMFVPROC, glGetUniformfv);
	GL_FN(PFNGLGETUNIFORMIVPROC, glGetUniformiv);
	GL_FN(PFNGLGETUNIFORMUIVPROC, glGetUniformuiv);
	GL_FN(PFNGLGETUNIFORMLOCATIONPROC, glGetUniformLocation);
	GL_FN(PFNGLUNIFORM4FPROC, glUniform4f);
	GL_FN(PFNGLUNIFORM3FPROC, glUniform3f);
	GL_FN(PFNGLUNIFORM2FPROC, glUniform2f);
	GL_FN(PFNGLUNIFORM1FPROC, glUniform1f);
    
	GL_FN(PFNGLUNIFORM4FVPROC, glUniform4fv);
	GL_FN(PFNGLUNIFORM3FVPROC, glUniform3fv);
	GL_FN(PFNGLUNIFORM2FVPROC, glUniform2fv);
	GL_FN(PFNGLUNIFORM1FVPROC, glUniform1fv);
    
	GL_FN(PFNGLUNIFORMMATRIX4FVPROC, glUniformMatrix4fv);
	GL_FN(PFNGLUNIFORMMATRIX3FVPROC, glUniformMatrix3fv);
	GL_FN(PFNGLUNIFORMMATRIX2FVPROC, glUniformMatrix2fv);
    
	GL_FN(PFNGLUNIFORM4DPROC, glUniform4d);
	GL_FN(PFNGLUNIFORM3DPROC, glUniform3d);
	GL_FN(PFNGLUNIFORM2DPROC, glUniform2d);
	GL_FN(PFNGLUNIFORM1DPROC, glUniform1d);
    
	GL_FN(PFNGLUNIFORM4IPROC, glUniform4i);
	GL_FN(PFNGLUNIFORM3IPROC, glUniform3i);
	GL_FN(PFNGLUNIFORM2IPROC, glUniform2i);
	GL_FN(PFNGLUNIFORM1IPROC, glUniform1i);
    
	GL_FN(PFNGLTEXPARAMETERIPROC, glTexParameteri);
	GL_FN(PFNGLTEXPARAMETERFVPROC, glTexParameterfv);
    
	GL_FN(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer);
	GL_FN(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray);
    GL_FN(PFNGLGETVERTEXATTRIBIUIVPROC, glGetVertexAttribIuiv);
    
	// Texture Functions
    
	GL_FN(PFNGLGENTEXTURESPROC, glGenTextures);
	GL_FN(PFNGLBINDTEXTUREPROC, glBindTexture);
    GL_FN(PFNGLOBJECTLABELPROC, glObjectLabel);
	GL_FN(PFNGLTEXIMAGE2DPROC, glTexImage2D);
	GL_FN(PFNGLACTIVETEXTUREPROC, glActiveTexture);
    GL_FN(PFNGLGETATTRIBLOCATIONPROC, glGetAttribLocation);
    
	GL_FN(PFNGLGENERATEMIPMAPPROC, glGenerateMipmap);
    
    
    extern const GLubyte* APIENTRY gluErrorString( GLenum errorCode );
    
	///////////////////////////////////////////////////////////////////////////////////////////
	//					LOADING FUNCTIONS
	///////////////////////////////////////////////////////////////////////////////////////////
    
	void *GetAnyGLFuncAddress(const char *name)
	{
		void *p = (void *)wglGetProcAddress(name);
		if ((p == 0) || (p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) || (p == (void*)-1))
		{
			HMODULE module = LoadLibraryA("opengl32.dll");
			p = (void *)GetProcAddress(module, name);
		}
        
		return p;
	}
    
	GLint getGLVersion()
	{
		GLint Result = 0;
		GLint Major = 0;
		GLint Minor = 0;
        
		glGetIntegerv(GL_MAJOR_VERSION, &Major);
		if (Major == 0)
		{
			GLenum Error = glGetError();
			ls_printf("In getGLVersion error: %d", Error);
		}
        
		glGetIntegerv(GL_MINOR_VERSION, &Minor);
		if (Minor == 0)
		{
			GLenum Error = glGetError();
			ls_printf("In getGLVersion error: %d", Error);
		}
        
		Result = (Major * 10) + Minor;
		return Result;
	}
    
	void LoadGLFunc(HDC DeviceContext)
	{
		glGetIntegerv  = (PFNGLGETINTEGERVPROC)GetAnyGLFuncAddress("glGetIntegerv");
		glGetStringi   = (PFNGLGETSTRINGIPROC)GetAnyGLFuncAddress("glGetStringi");
		glGetString	= (PFNGLGETSTRINGPROC)GetAnyGLFuncAddress("glGetString");
		glGetError	 = (PFNGLGETERRORPROC)GetAnyGLFuncAddress("glGetError");
        
		GLint Version = getGLVersion();
		wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)GetAnyGLFuncAddress("wglGetExtensionsStringARB");
		const char *extensions = wglGetExtensionsStringARB(DeviceContext);
        
		//@TODO: This is actually not enough to check if we have these extensions, gonna have to implement more extensive checks later.
        
#ifdef WGL_ARB_pixel_format
        GET_FN(wglGetPixelFormatAttribivARB, PFNWGLGETPIXELFORMATATTRIBIVARBPROC);
		GET_FN(wglGetPixelFormatAttribfvARB, PFNWGLGETPIXELFORMATATTRIBFVARBPROC);
		GET_FN(wglChoosePixelFormatARB, PFNWGLCHOOSEPIXELFORMATARBPROC);
#endif
        
        
#ifdef WGL_EXT_swap_control
		GET_FN(wglSwapIntervalEXT, PFNWGLSWAPINTERVALEXTPROC);
		GET_FN(wglGetSwapIntervalEXT, PFNWGLGETSWAPINTERVALEXTPROC);
#endif
        
        
#ifdef WGL_ARB_pbuffer
		GET_FN(wglCreatePbufferARB, PFNWGLCREATEPBUFFERARBPROC);
		GET_FN(wglGetPbufferDCARB, PFNWGLGETPBUFFERDCARBPROC);
		GET_FN(wglReleasePbufferDCARB, PFNWGLRELEASEPBUFFERDCARBPROC);
		GET_FN(wglDestroyPbufferARB, PFNWGLDESTROYPBUFFERARBPROC);
		GET_FN(wglQueryPbufferARB, PFNWGLQUERYPBUFFERARBPROC);
#endif
        
        
#ifdef WGL_ARB_render_texture
		GET_FN(wglBindTexImageARB, PFNWGLBINDTEXIMAGEARBPROC);
		GET_FN(wglReleaseTexImageARB, PFNWGLRELEASETEXIMAGEARBPROC);
		GET_FN(wglSetPbufferAttribARB, PFNWGLSETPBUFFERATTRIBARBPROC);
#endif
        
        
#ifdef WGL_ARB_make_current_read
		GET_FN(wglMakeContextCurrentARB, PFNWGLMAKECONTEXTCURRENTARBPROC);
		GET_FN(wglGetCurrentReadDCARB, PFNWGLGETCURRENTREADDCARBPROC);
#endif
        
        
#ifdef WGL_EXT_extensions_string
		GET_FN(wglGetExtensionsStringEXT, PFNWGLGETEXTENSIONSSTRINGEXTPROC);
#endif
        
        
#ifdef WGL_ARB_buffer_region
		GET_FN(wglCreateBufferRegionARB, PFNWGLCREATEBUFFERREGIONARBPROC);
		GET_FN(wglDeleteBufferRegionARB, PFNWGLDELETEBUFFERREGIONARBPROC);
		GET_FN(wglSaveBufferRegionARB, PFNWGLSAVEBUFFERREGIONARBPROC);
		GET_FN(wglRestoreBufferRegionARB, PFNWGLRESTOREBUFFERREGIONARBPROC);
#endif
        
        
#ifdef WGL_I3D_genlock
		GET_FN(wglEnableGenlockI3D, PFNWGLENABLEGENLOCKI3DPROC);
		GET_FN(wglDisableGenlockI3D, PFNWGLDISABLEGENLOCKI3DPROC);
		GET_FN(wglIsEnabledGenlockI3D, PFNWGLISENABLEDGENLOCKI3DPROC);
		GET_FN(wglGenlockSourceI3D, PFNWGLGENLOCKSOURCEI3DPROC);
		GET_FN(wglGetGenlockSourceI3D, PFNWGLGETGENLOCKSOURCEI3DPROC);
		GET_FN(wglGenlockSourceEdgeI3D, PFNWGLGENLOCKSOURCEEDGEI3DPROC);
		GET_FN(wglGetGenlockSourceEdgeI3D, PFNWGLGETGENLOCKSOURCEEDGEI3DPROC);
		GET_FN(wglGenlockSampleRateI3D, PFNWGLGENLOCKSAMPLERATEI3DPROC);
		GET_FN(wglGetGenlockSampleRateI3D, PFNWGLGETGENLOCKSAMPLERATEI3DPROC);
		GET_FN(wglGenlockSourceDelayI3D, PFNWGLGENLOCKSOURCEDELAYI3DPROC);
		GET_FN(wglGetGenlockSourceDelayI3D, PFNWGLGETGENLOCKSOURCEDELAYI3DPROC);
		GET_FN(wglQueryGenlockMaxSourceDelayI3D, PFNWGLQUERYGENLOCKMAXSOURCEDELAYI3DPROC);
#endif
        
        
#ifdef WGL_NV_swap_group
		GET_FN(wglJoinSwapGroupNV, PFNWGLJOINSWAPGROUPNVPROC);
		GET_FN(wglBindSwapBarrierNV, PFNWGLBINDSWAPBARRIERNVPROC);
		GET_FN(wglQuerySwapGroupNV, PFNWGLQUERYSWAPGROUPNVPROC);
		GET_FN(wglQueryMaxSwapGroupsNV, PFNWGLQUERYMAXSWAPGROUPSNVPROC);
		GET_FN(wglQueryFrameCountNV, PFNWGLQUERYFRAMECOUNTNVPROC);
		GET_FN(wglResetFrameCountNV, PFNWGLRESETFRAMECOUNTNVPROC);
#endif
        
        
#ifdef WGL_ARB_create_context
		GET_FN(wglCreateContextAttribsARB, PFNWGLCREATECONTEXTATTRIBSARBPROC);
#endif
        
        
#ifdef WGL_AMD_gpu_association
		GET_FN(wglGetGPUIDsAMD, PFNWGLGETGPUIDSAMDPROC);
		GET_FN(wglGetGPUInfoAMD, PFNWGLGETGPUINFOAMDPROC);
		GET_FN(wglGetContextGPUIDAMD, PFNWGLGETCONTEXTGPUIDAMDPROC);
		GET_FN(wglCreateAssociatedContextAMD, PFNWGLCREATEASSOCIATEDCONTEXTAMDPROC);
		GET_FN(wglCreateAssociatedContextAttribsAMD, PFNWGLCREATEASSOCIATEDCONTEXTATTRIBSAMDPROC);
		GET_FN(wglDeleteAssociatedContextAMD, PFNWGLDELETEASSOCIATEDCONTEXTAMDPROC);
		GET_FN(wglMakeAssociatedContextCurrentAMD, PFNWGLMAKEASSOCIATEDCONTEXTCURRENTAMDPROC);
		GET_FN(wglGetCurrentAssociatedContextAMD, PFNWGLGETCURRENTASSOCIATEDCONTEXTAMDPROC);
		GET_FN(wglBlitContextFramebufferAMD, PFNWGLBLITCONTEXTFRAMEBUFFERAMDPROC);
#endif
        
#ifdef WGL_NV_DX_interop
		GET_FN(wglDXSetResourceShareHandleNV, PFNWGLDXSETRESOURCESHAREHANDLENVPROC);
		GET_FN(wglDXOpenDeviceNV, PFNWGLDXOPENDEVICENVPROC);
		GET_FN(wglDXCloseDeviceNV, PFNWGLDXCLOSEDEVICENVPROC);
		GET_FN(wglDXRegisterObjectNV, PFNWGLDXREGISTEROBJECTNVPROC);
		GET_FN(wglDXUnregisterObjectNV, PFNWGLDXUNREGISTEROBJECTNVPROC);
		GET_FN(wglDXObjectAccessNV, PFNWGLDXOBJECTACCESSNVPROC);
		GET_FN(wglDXLockObjectsNV, PFNWGLDXLOCKOBJECTSNVPROC);
		GET_FN(wglDXUnlockObjectsNV, PFNWGLDXUNLOCKOBJECTSNVPROC);
#endif
        
        
		if (Version >= 33)
		{
			GET_FN(glGetShaderiv, PFNGLGETSHADERIVPROC);
			GET_FN(glGetShaderInfoLog, PFNGLGETSHADERINFOLOGPROC);
			GET_FN(glGetProgramiv, PFNGLGETPROGRAMIVPROC);
			GET_FN(glGetProgramInfoLog, PFNGLGETPROGRAMINFOLOGPROC);
            
			GET_FN(glEnable, PFNGLENABLEPROC);
			GET_FN(glFinish, PFNGLFINISHPROC);
            
			GET_FN(glViewport, PFNGLVIEWPORTPROC);
			GET_FN(glClearColor, PFNGLCLEARCOLORPROC);
			GET_FN(glClear, PFNGLCLEARPROC);
            GET_FN(glClearDepth, PFNGLCLEARDEPTHPROC);
            GET_FN(glDepthFunc, PFNGLDEPTHFUNCPROC);
			GET_FN(glDrawArrays, PFNGLDRAWARRAYSPROC);
			GET_FN(glDrawElements, PFNGLDRAWELEMENTSPROC);
            
			GET_FN(glGenBuffers, PFNGLGENBUFFERSPROC);
            GET_FN(glDeleteBuffers, PFNGLDELETEBUFFERSPROC);
			GET_FN(glGenVertexArrays,PFNGLGENVERTEXARRAYSPROC);
            GET_FN(glDeleteVertexArrays, PFNGLDELETEVERTEXARRAYSPROC);
			GET_FN(glBindBuffer, PFNGLBINDBUFFERPROC);
			GET_FN(glBindVertexArray,PFNGLBINDVERTEXARRAYPROC);
			GET_FN(glBufferData, PFNGLBUFFERDATAPROC);
            GET_FN(glPixelStorei, PFNGLPIXELSTOREIPROC);
            
			GET_FN(glCreateShader, PFNGLCREATESHADERPROC);
			GET_FN(glCreateProgram, PFNGLCREATEPROGRAMPROC);
			GET_FN(glDeleteShader, PFNGLDELETESHADERPROC);
            
			GET_FN(glShaderSource, PFNGLSHADERSOURCEPROC);
			GET_FN(glCompileShader, PFNGLCOMPILESHADERPROC);
			GET_FN(glAttachShader, PFNGLATTACHSHADERPROC);
            GET_FN(glBindFragDataLocation, PFNGLBINDFRAGDATALOCATIONPROC);
			GET_FN(glLinkProgram, PFNGLLINKPROGRAMPROC);
			GET_FN(glUseProgram, PFNGLUSEPROGRAMPROC);
            
			GET_FN(glGetUniformfv, PFNGLGETUNIFORMFVPROC);
			GET_FN(glGetUniformiv, PFNGLGETUNIFORMIVPROC);
			GET_FN(glGetUniformuiv, PFNGLGETUNIFORMUIVPROC);
			GET_FN(glGetUniformLocation, PFNGLGETUNIFORMLOCATIONPROC);
			GET_FN(glUniform4f, PFNGLUNIFORM4FPROC);
			GET_FN(glUniform3f, PFNGLUNIFORM3FPROC);
			GET_FN(glUniform2f, PFNGLUNIFORM2FPROC);
			GET_FN(glUniform1f, PFNGLUNIFORM1FPROC);
            
			GET_FN(glUniform4fv, PFNGLUNIFORM4FVPROC);
			GET_FN(glUniform3fv, PFNGLUNIFORM3FVPROC);
			GET_FN(glUniform2fv, PFNGLUNIFORM2FVPROC);
			GET_FN(glUniform1fv, PFNGLUNIFORM1FVPROC);
            
			GET_FN(glUniformMatrix4fv, PFNGLUNIFORMMATRIX4FVPROC);
			GET_FN(glUniformMatrix3fv, PFNGLUNIFORMMATRIX3FVPROC);
			GET_FN(glUniformMatrix2fv, PFNGLUNIFORMMATRIX2FVPROC);
            
			GET_FN(glUniform4d, PFNGLUNIFORM4DPROC);
			GET_FN(glUniform3d, PFNGLUNIFORM3DPROC);
			GET_FN(glUniform2d, PFNGLUNIFORM2DPROC);
			GET_FN(glUniform1d, PFNGLUNIFORM1DPROC);
            
			GET_FN(glUniform4i, PFNGLUNIFORM4IPROC);
			GET_FN(glUniform3i, PFNGLUNIFORM3IPROC);
			GET_FN(glUniform2i, PFNGLUNIFORM2IPROC);
			GET_FN(glUniform1i, PFNGLUNIFORM1IPROC);
            
			GET_FN(glTexParameteri, PFNGLTEXPARAMETERIPROC);
			GET_FN(glTexParameterfv, PFNGLTEXPARAMETERFVPROC);
            
			GET_FN(glVertexAttribPointer, PFNGLVERTEXATTRIBPOINTERPROC);
			GET_FN(glEnableVertexAttribArray, PFNGLENABLEVERTEXATTRIBARRAYPROC);
            GET_FN(glGetVertexAttribIuiv, PFNGLGETVERTEXATTRIBIUIVPROC);
            
			GET_FN(glGenTextures, PFNGLGENTEXTURESPROC);
			GET_FN(glBindTexture, PFNGLBINDTEXTUREPROC);
            GET_FN(glObjectLabel, PFNGLOBJECTLABELPROC);
			GET_FN(glTexImage2D, PFNGLTEXIMAGE2DPROC);
			GET_FN(glActiveTexture, PFNGLACTIVETEXTUREPROC);
            
            GET_FN(glGetAttribLocation, PFNGLGETATTRIBLOCATIONPROC);
            
			GET_FN(glGenerateMipmap, PFNGLGENERATEMIPMAPPROC);
		}
	}
}

#undef GL_FN(a, b)
#undef GET_FN(a, b)
