#pragma once

void __ui_InitOpenGLExtensions();
void __ui_CreateDefaultShaders(UIContext *c);
void __ui_CreateOpenGLWindow(UIContext *c, UIWindow *win, HWND WindowHandle);

#include "OpenGLShaders/lsUI.SimpleRect.h"
#include "OpenGLShaders/lsUI.GradientRect.h"
#include "OpenGLShaders/lsUI.TexturedRect.h"
#include "OpenGLShaders/lsUI.Circle.h"
#include "OpenGLShaders/lsUI.Text.h"
