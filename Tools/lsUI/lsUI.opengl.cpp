#include "lsUI.opengl.h"

void __ui_InitOpenGLExtensions()
{
    static s32 ___stupid_fucking_counter = 0;
    char dummyName[64] = {};
    ls_sprintf(dummyName, 64, "Dummy_WGL___%d", ___stupid_fucking_counter);
    ___stupid_fucking_counter += 1;

    WNDCLASSA DummyClass = {
        .style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
        .lpfnWndProc = DefWindowProcA,
        .hInstance = GetModuleHandleA(0),
        .lpszClassName = dummyName,
    };
    
    if(!RegisterClassA(&DummyClass))
    {
        DWORD Error = GetLastError();
        AssertMsgF(FALSE, "When Registering Dummy OpenGL"
                   "WindowClass got error: %d", Error);
    }
    
    HWND DummyWindow;
    if ((DummyWindow = CreateWindowExA(0, DummyClass.lpszClassName, "Dummy OpenGL Window", 0,
                                       CW_USEDEFAULT, CW_USEDEFAULT,
                                       CW_USEDEFAULT, CW_USEDEFAULT,
                                       0, 0, DummyClass.hInstance, 0)) == nullptr)
    {
        DWORD Error = GetLastError();
        AssertMsgF(FALSE, "When Creating Dummy OpenGL Window"
                   "got error: %d", Error);
    }
    
    HDC DummyDC = GetDC(DummyWindow);
    
    PIXELFORMATDESCRIPTOR pfd = {
        .nSize = sizeof(pfd),
        .nVersion = 1,
        .dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        .iPixelType = PFD_TYPE_RGBA,
        .cColorBits = 32,
        .cAlphaBits = 8,
        .cDepthBits = 24,
        .cStencilBits = 8,
        .iLayerType = PFD_MAIN_PLANE,
    };
    
    s32 pixelFormat = ChoosePixelFormat(DummyDC, &pfd);
    if(!pixelFormat) {
        AssertMsg(FALSE, "Failed to find Pixel Format");
    }
    
    if(!SetPixelFormat(DummyDC, pixelFormat, &pfd)) {
        AssertMsg(FALSE, "Failed to set Pixel Format");
    }
    
    HGLRC DummyContext = wglCreateContext(DummyDC);
    if(!DummyContext) {
        AssertMsg(FALSE, "Failed to create Dummy OpenGL context");
    }
    
    if(!wglMakeCurrent(DummyDC, DummyContext)) {
        AssertMsg(FALSE, "Failed to activate Dummy OpenGL context");
    }
    
    wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
    wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
    
    wglMakeCurrent(DummyDC, 0);
    wglDeleteContext(DummyContext);
    ReleaseDC(DummyWindow, DummyDC);
    DestroyWindow(DummyWindow);
    
}

void __ui_CreateDefaultShaders(UIContext *c)
{
    c->rectShader = ls_glCreateShader(__ls_ui_default_vert_shader_src, __ls_ui_default_rect_frag_shader_src);
    
    f32 rectVertices[18][4] =
    {
        {-1.0, -1.0, 0.0, 0.0},  // Bot-left
        {-1.0,  1.0, 0.0, 1.0},  // Top-left
        { 1.0, -1.0, 1.0, 0.0},  // Bot-right
        
        { 1.0, -1.0, 1.0, 0.0},  // Bot-right
        {-1.0,  1.0, 0.0, 1.0},  // Top-left
        { 1.0,  1.0, 1.0, 1.0},  // Top-right
        
        //NOTE: This is just for arrows in ls_uiDrawArrows
        // TOP
        {-1.0, -1.0, 0.0, 0.0},  // Bot-left
        { 1.0, -1.0, 1.0, 0.0},  // Bot-right
        { 0.0,  1.0, 0.5, 1.0},  // Top-center
        
        // RIGHT
        {-1.0, -1.0, 0.0, 0.0},  // Bot-left
        {-1.0,  1.0, 0.0, 1.0},  // Top-left
        { 1.0,  0.0, 1.0, 0.5},  // Center-right
        
        // DOWN
        {-1.0,  1.0, 0.0, 1.0},  // Top-left
        { 1.0,  1.0, 1.0, 1.0},  // Top-right
        { 0.0, -1.0, 0.5, 0.0},  // Bot-center
        
        // LEFT
        { 1.0,  1.0, 1.0, 1.0},  // Top-right
        { 1.0, -1.0, 1.0, 0.0},  // Bot-right
        {-1.0,  0.0, 0.0, 0.5},  // Center-left
    };
    
    GLuint VBO;
    glGenVertexArrays(1, &c->rectVAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(c->rectVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    //NOTE: Since you can free the underling buffer after the call to glBufferData, this means
    // that glBufferData will copy over the data right here. I'm not sure if it uploads it to the gpu
    // or create a temporary copy in RAM (which would be undesirable)
    // TODO: Look into glMapBufferRange() which apparently does things a little different
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertices), rectVertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    //
    // --------------------------------

    // --------------------------------
    //NOTE: Gradient Rect VAO
    //

    c->gradientRectShader = ls_glCreateShader(__ls_ui_DefGradientRectVertSrc, __ls_ui_DefGradientRectFragSrc);
    
    // NOTE: The extra float is either 0.0 or 1.0 and indicates if the vertex should be
    // black of white in color.
    f32 rectGradientVertices[6][5] =
    {
        {-1.0, -1.0, 0.0, 0.0, 0.0},  // Bot-left
        {-1.0,  1.0, 0.0, 1.0, 1.0},  // Top-left
        { 1.0, -1.0, 1.0, 0.0, 0.0},  // Bot-right
        
        { 1.0, -1.0, 1.0, 0.0, 0.0},  // Bot-right
        {-1.0,  1.0, 0.0, 1.0, 1.0},  // Top-left
        { 1.0,  1.0, 1.0, 1.0, 1.0},  // Top-right
    };
    
    GLuint rectGradientVBO;
    glGenVertexArrays(1, &c->rectGradientVAO);
    glGenBuffers(1, &rectGradientVBO);
    glBindVertexArray(c->rectGradientVAO);
    glBindBuffer(GL_ARRAY_BUFFER, rectGradientVBO);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectGradientVertices), rectGradientVertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(4 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //
    // --------------------------------
    
    // --------------------------------
    //NOTE: Textured Rect Shader Compilation
    //
    
    c->texturedRectShader = ls_glCreateShader(__ls_ui_default_vert_shader_src, __ls_ui_DefTexturedRectFragSrc);
    
    //TODO: Pass center and radius to specialized vertex shader for
    // circles and do the position calcs there!
    
    // --------------------------------
    //NOTE: Circle Shader Compilation
    //
    
    c->circleShader = ls_glCreateShader(__ls_ui_default_vert_shader_src, __ls_ui_DefCircleFragSrc);

    // --------------------------------
    //NOTE: Circle Color Wheel Shader Compilation
    //

    c->colorWheelShader = ls_glCreateShader(__ls_ui_default_vert_shader_src, __ls_uiDefCircleColorWheelFragSrc);
    
    constexpr s32 circleVertCount = 80;
    f32 circleVertices[circleVertCount][4] = {};
    c->circleVertCount = circleVertCount;
    
    //NOTE: Radius is 1.0f, so it's implicit in the calculations.
    f32 angleStep = TAU / circleVertCount;
    f32 pX = 1.0f;
    f32 pY = 0.0f;
    f32 u  = 1.0f;
    f32 v  = 0.5f;
    for (s32 cvIdx = 0; cvIdx < circleVertCount; cvIdx++)
    {
        circleVertices[cvIdx][0] = pX;
        circleVertices[cvIdx][1] = pY;
        circleVertices[cvIdx][2] = u;
        circleVertices[cvIdx][3] = v;
        pX = cos(cvIdx*angleStep);
        pY = sin(cvIdx*angleStep);
        u  = (cos(cvIdx*angleStep) + 1.0f) * 0.5f;
        v  = (sin(cvIdx*angleStep) + 1.0f) * 0.5f;
    }
    
    GLuint circleVBO;
    glGenVertexArrays(1, &c->circleVAO);
    glGenBuffers(1, &circleVBO);
    glBindVertexArray(c->circleVAO);
    glBindBuffer(GL_ARRAY_BUFFER, circleVBO);
    
    //NOTE: Since you can free the underling buffer after the call to glBufferData, this means
    // that glBufferData will copy over the data right here. I'm not sure if it uploads it to the gpu
    // or create a temporary copy in RAM (which would be undesirable)
    // TODO: Look into glMapBufferRange() which apparently does things a little different
    glBufferData(GL_ARRAY_BUFFER, sizeof(circleVertices), circleVertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    // --------------------------------
    //NOTE: SDF Shader Compilation
    //

    c->sdfTextShader = ls_glCreateShader(__ls_ui_DefTextVertSrc, __ls_ui_DefSDFTextFragSrc);

    // --------------------------------
    //NOTE: Text Shader Compilation
    //
    
    
    c->textShader = ls_glCreateShader(__ls_ui_DefTextVertSrc, __ls_ui_DefTextFragSrc);
    
    //
    // --------------------------------
}

void __ui_CreateOpenGLWindow(UIContext *c, UIWindow *win, HWND WindowHandle)
{
    if(c->OGLContext == NULL)
    {
        __ui_InitOpenGLExtensions();
    }
    
    s32 pixelFormatAttribs[] = {
        WGL_DRAW_TO_WINDOW_ARB,     GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB,     GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB,      GL_TRUE,
        WGL_ACCELERATION_ARB,       WGL_FULL_ACCELERATION_ARB,
        WGL_PIXEL_TYPE_ARB,         WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB,         32,
        WGL_DEPTH_BITS_ARB,         24,
        WGL_STENCIL_BITS_ARB,       8,
        0
    };
    
    s32 pixelFormat;
    u32 numFormats;
    win->WindowDC = GetDC(WindowHandle);
    wglChoosePixelFormatARB(win->WindowDC, pixelFormatAttribs, 0, 1, &pixelFormat, &numFormats);
    if(!numFormats) {
        AssertMsg(FALSE, "Failed to set OpenGL Pixel Format");
    }
    
    PIXELFORMATDESCRIPTOR pfd;
    DescribePixelFormat(win->WindowDC, pixelFormat, sizeof(pfd), &pfd);
    if(!SetPixelFormat(win->WindowDC, pixelFormat, &pfd)) {
        AssertMsg(FALSE, "Failed to set OpenGL Pixel Format");
    }

    if(c->OGLContext == NULL)
    {
        s32 gl33Attribs[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
            WGL_CONTEXT_MINOR_VERSION_ARB, 3,
            WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0,
        };
        
        HGLRC gl33Context = wglCreateContextAttribsARB(win->WindowDC, 0, gl33Attribs);
        if(!gl33Context) {
            AssertMsg(FALSE, "Failed to create OpenGL 3.3 context");
        }
        
        if(!wglMakeCurrent(win->WindowDC, gl33Context)) {
            AssertMsg(FALSE, "Failed to Activate OpenGL 3.3 context");
        }
        c->OGLContext = gl33Context;
        
        ls_glLoadFunc(win->WindowDC);
     
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        __ui_CreateDefaultShaders(c);
    }
}
