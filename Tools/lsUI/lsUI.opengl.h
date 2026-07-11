#pragma once

//NOTE TODO: This is full of assumptions.
// We are assuming there is a vertex/fragment shader in each program
// And that shader data (in array buffers, etc...) does not 
// need to be reloaded (and so it isn't tracked)
struct UIShader
{
    const char *vertSrc;
    const char *fragSrc;
    u32 idx;
    u32 VAO;

#if _DEBUG
    const char *vertFilePath;
    const char *fragFilePath;
#endif
};

void     __ui_InitOpenGLExtensions();
UIShader __ui_CreateGLShader(const char *vertSrcOrFile, const char *fragSrcOrFile, bool isSource);
void     __ui_CreateDefaultShaders(UIContext *c);
u32      __ui_ReloadShader(UIContext *c, UIShader *s);
void     __ui_CreateOpenGLWindow(UIContext *c, UIWindow *win, HWND WindowHandle);

LS_COMPILE_TIME_FILE_REL_PATH(__ui_DebugShadersParentDir, __FILE__, "OpenGLShaders\\Debug");

//TODO: Until major compilers decide to support the essential and simple feature of '#embed'
// Either I have to preprocess the following files and ensure the Debug versions and the source string
// versions remain aligned, or I have to modify 2 places at the same time.
// Annoying but I believe better than always loading at startup anyway...
// (We also get hot-reloading this way, so it's an *extremely* useful thing to have during development)
#include "OpenGLShaders/lsUI.SimpleRect.h"
#include "OpenGLShaders/lsUI.GradientRect.h"
#include "OpenGLShaders/lsUI.TexturedRect.h"
#include "OpenGLShaders/lsUI.Circle.h"
#include "OpenGLShaders/lsUI.Text.h"
