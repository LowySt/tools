#ifndef LS_UI_H
#define LS_UI_H

/*TODOs
-@Alpha-Un-Multiply
-Fix pre-multiplied alpha for LightenRGB and DarkenRGB

-When not finding a glyph in Release, we should return an empty/error glyph.
*/

#include "lsWindows.h"
#include "lsGraphics.h"
#include "lsCRT.h"
#include "lsMath.h"
#include "lsStack.h"
#include "lsString.h"

#include "lsArena.h"
#include "lsArray.h"

#include "lsInput.h"

#ifndef LS_FILEWATCH_IMPLEMENTATION
#define LS_FILEWATCH_IMPLEMENTATION
#include "lsFileWatch.h"
#endif

#include <typeinfo>

#define KeySet(k)       (UserInput->Keyboard.currentState.k = 1)
#define KeyUnset(k)     (UserInput->Keyboard.currentState.k = 0)
#define KeyPress(k)     (UserInput->Keyboard.currentState.k == 1 && UserInput->Keyboard.prevState.k == 0)
#define KeyHeld(k)      (UserInput->Keyboard.currentState.k == 1 && UserInput->Keyboard.prevState.k == 1)

#define KeySetAndRepeat(k, rp) (UserInput->Keyboard.currentState.k = 1); \
if(rp) { (UserInput->Keyboard.repeatState.k = 1); }

#define KeyRepeat(k)    (UserInput->Keyboard.currentState.k == 1 && UserInput->Keyboard.repeatState.k == 1)

#define KeyPressOrRepeat(k) (KeyPress(k) || KeyRepeat(k))


#define HasPrintableKey() (UserInput->Keyboard.hasPrintableKey == TRUE)
#define GetPrintableKey() (UserInput->Keyboard.keyCodepoint)
#define ClearPrintableKey() (UserInput->Keyboard.hasPrintableKey = FALSE)

#define GetClipboard(b,l) (UserInput->Keyboard.getClipboard(b,l))
#define SetClipboard(b,l) (UserInput->Keyboard.setClipboard(b,l))

#define MouseInRect(xP,yP,w,h) (((UserInput->Mouse.currPosX >= xP) && (UserInput->Mouse.currPosX <= xP+w)) && \
((UserInput->Mouse.currPosY >= yP) && (UserInput->Mouse.currPosY <= yP+h)))

#define LeftClick    ((UserInput->Mouse.isLeftPressed && !UserInput->Mouse.wasLeftPressed))
#define MiddleClick  ((UserInput->Mouse.isMiddlePressed && !UserInput->Mouse.wasMiddlePressed))
#define RightClick   ((UserInput->Mouse.isRightPressed && !UserInput->Mouse.wasRightPressed))

#define LeftHold     ((UserInput->Mouse.isLeftPressed && UserInput->Mouse.wasLeftPressed))
#define MiddleHold   ((UserInput->Mouse.isMiddlePressed && UserInput->Mouse.wasMiddlePressed))
#define RightHold    ((UserInput->Mouse.isRightPressed && UserInput->Mouse.wasRightPressed))

#define LeftUp       ((!UserInput->Mouse.isLeftPressed && UserInput->Mouse.wasLeftPressed))
#define MiddleUp     ((!UserInput->Mouse.isMiddlePressed && UserInput->Mouse.wasMiddlePressed))
#define RightUp      ((!UserInput->Mouse.isRightPressed && UserInput->Mouse.wasRightPressed))

#define LeftClear    ((!UserInput->Mouse.isLeftPressed && !UserInput->Mouse.wasLeftPressed))
#define MiddleClear  ((!UserInput->Mouse.isMiddlePressed && !UserInput->Mouse.wasMiddlePressed))
#define RightClear   ((!UserInput->Mouse.isRightPressed && !UserInput->Mouse.wasRightPressed))

#define WheelRotated (UserInput->Mouse.isWheelRotated)
#define WheelDeltaInPixels (UserInput->Mouse.wheelDelta)

#define LeftClickIn(x,y,w,h)       (LeftClick   && MouseInRect(x, y, w, h))
#define MiddleClickIn(x,y,w,h)     (MiddleClick && MouseInRect(x, y, w, h))
#define RightClickIn(x,y,w,h)      (RightClick  && MouseInRect(x, y, w, h))

#define LeftHoldIn(x,y,w,h)        (LeftHold   && MouseInRect(x, y, w, h))
#define MiddleHoldIn(x,y,w,h)      (MiddleHold && MouseInRect(x, y, w, h))
#define RightHoldIn(x,y,w,h)       (RightHold  && MouseInRect(x, y, w, h))

#define LeftUpIn(x,y,w,h)          (LeftUp   && MouseInRect(x, y, w, h))
#define MiddleUpIn(x,y,w,h)        (MiddleUp && MouseInRect(x, y, w, h))
#define RightUpIn(x,y,w,h)         (RightUp  && MouseInRect(x, y, w, h))

#define WheelRotatedIn(x, y, w, h) (WheelRotated && MouseInRect(x, y, w, h))

#if defined(LS_UI_OPENGL_BACKEND)
const     u32 __LS_UI_THREAD_COUNT     = 0;
#elif defined(LS_UI_SOFTWARE_BACKEND)
const     u32 __LS_UI_THREAD_COUNT     = 8;
#endif
constexpr u32 LS_UI_RENDER_GROUP_COUNT = __LS_UI_THREAD_COUNT == 0 ? 1 : __LS_UI_THREAD_COUNT;


struct UIContext;
struct RenderCommand;
struct UIWindow;
//NOTE: Base Struct for all UI elements
//      The reason it's made as a define is so that the entire anonymous struct definition 
//      Will be copy-pasted inside each Widget's body. This way each widget can access all element of the
//      Base struct without having to refer to it by name (like if it was a substruct).
//
//      C-style inheritance without access_control, constructors, dynamic_dispatch etc...

typedef b32(*UICallback)(UIContext *c, void *userData);
struct DummyUIWidgetBase { 
    /*NOTE: Generic Callbacks. All UIElements will use one or both of these.*/                    
    /*      Technically there's some wasted space here, but it shouldn't be a problem for now.*/  
    UICallback callback1;                                                                         
    void *callback1Data;                                                                          
    UICallback callback2;                                                                         
    void *callback2Data;                                                                          
    /*NOTE: This will be called whenever the element looses focus*/                               
    UICallback OnFocusLost;                                                                       
    void *onFocusLostData;                                                                        
};

#define UIWidget_Base struct { \
/*NOTE: Generic Callbacks. All UIElements will use one or both of these.*/                    \
/*      Technically there's some wasted space here, but it shouldn't be a problem for now.*/  \
UICallback callback1;                                                                         \
void *callback1Data;                                                                          \
UICallback callback2;                                                                         \
void *callback2Data;                                                                          \
/*NOTE: This will be called whenever the element looses focus*/                               \
UICallback OnFocusLost;                                                                       \
void *onFocusLostData;                                                                        \
}                                                                                             \



//Internal Includes?
#include "lsUI.primitives.h"
#include "lsUI.utils.h"

#ifdef LS_UI_OPENGL_BACKEND
#include "lsUI.opengl.h"
#endif

#include "lsUI.bitmaps.h"
#include "lsUI.rects.h"
#include "lsUI.circles.h"
#include "lsUI.fonts.h"
#include "lsUI.textboxes.h"
#include "lsUI.labels.h"
#include "lsUI.listboxes.h"
#include "lsUI.buttons.h"
#include "lsUI.checks.h"
#include "lsUI.sliders.h"
#include "lsUI.menus.h"
#include "lsUI.colorpickers.h"

#if 0
struct UILPane
{
    u32 dtOpen;
    b32 isOpening;
    b32 isOpen;
};
#endif

struct UIScrollableRegion
{
    s32 x, y, w, h; 
    s32 deltaX, deltaY;
    
    s32 maxX, minY;
    
    b32 isHeld;
};

const char* RenderCommandTypeAsString[] = {
    "UI_RC_INVALID",
    "UI_RC_TEXTBOX",
    "UI_RC_LABEL8",
    "UI_RC_LABEL32",
    "UI_RC_LABEL_LAYOUT",
    "UI_RC_BUTTON",
    "UI_RC_CHECK",
    "UI_RC_LISTBOX",
    "UI_RC_LISTBOX_ARR",
    "UI_RC_SLIDER",
    "UI_RC_RECT",
    "UI_RC_SEPARATOR",
    "UI_RC_MENU",
    "UI_RC_BACKGROUND",
    "UI_RC_SCROLLBAR",
    "UI_RC_TEXTURED_RECT",
    "UI_RC_COLOR_PICKER",
    "UI_RC_BITMAP",
    "UI_RC_CIRCLE",
};

enum RenderCommandType
{
    UI_RC_TESTBOX = 990,
    
    UI_RC_INVALID = 0,
    
    UI_RC_TEXTBOX = 1,
    UI_RC_LABEL8,
    UI_RC_LABEL32,
    UI_RC_LABEL_LAYOUT,
    UI_RC_BUTTON,
    UI_RC_CHECK,
    UI_RC_LISTBOX,
    UI_RC_LISTBOX_ARR,
    UI_RC_SLIDER,
    UI_RC_RECT,
    UI_RC_SEPARATOR,
    UI_RC_MENU,
    UI_RC_BACKGROUND,
    UI_RC_SCROLLBAR,
    UI_RC_TEXTURED_RECT,
    UI_RC_COLOR_PICKER,
    UI_RC_BITMAP,
    UI_RC_CIRCLE,
};

static s32 RenderCommandUID = 0;
//TODO: RenderCommand is getting big.
struct RenderCommand
{
    RenderCommandType  type;
    
    //NOTE: The render coord. after threaded dispatch
    //      Most widgets only use the rect. The layout contains 2 extra members: startX & startY
    //      other than the bounding rect, which are necessary when, for example, layouting text.
    UIRect rect;
    UILayoutRect layout;
    
    //TODO: Can we make this happen at compile time and just globally assign it to each
    //      Render Thread by ThreadID?
    //      Maybe just match the ThreadID to the threadRect index in an array?
    UIRect threadRect;
    
    //TODO: Should I pass the strings as pointers as well?
    union
    {
        UITextBox     *textBox;
        utf32          label32;
        utf8           label8;
        UIButton      *button;
        UICheck       *check;
        UIListBox     *listBox;
        UISlider      *slider;
        UIMenu        *menu;
        UIColorPicker *colorPicker;
        
        //TODO: I hate that I have to copy it.
        UIBitmap  bitmap;
    };
    
    Color bkgColor;
    Color textColor;
    Color borderColor;
    
    UIFont *selectedFont;
    s32     pixelHeight;
    
    //NOTE: If the command renders inside a scrollable region
    //      This are set to the rect of that region.
    //      (Which might be larger/smaller than the actual BackBuffer/Window)
    //
    //      Width/Height default to -1, when there is NO scrollable region.
    UIScrollableRegion scroll;
    
    //NOTETODO: Scissor for the current command.
    UIRect scissor;

    UIPos pos;
    
#if _DEBUG
    b32 isTagged;
    s32 UID;
#endif
};

const u32 UI_Z_LAYERS = 4;
struct RenderGroup
{
    stack RenderCommands[UI_Z_LAYERS];
    volatile b32 isDone;
};

struct UIWindow
{
    //NOTE: This is the actual allocated memory
    //      It is slightly larger than the drawn window because it contains a border
    //      Used for resizing
    u8 *drawBuffer;
    s32 backbufferW;
    s32 backbufferH;

    //NOTE: This is the area that all systems reference to draw. It's the area you should draw into
    s32 width; 
    s32 height;

    UIRect renderUIRects[LS_UI_RENDER_GROUP_COUNT];

    //NOTE: Windows specific Handles to a window-related object...
    HDC  WindowDC;
    HDC  BackBufferDC;
    HBITMAP DibSection;
    HWND Window;
    
    s32 windowPosX, windowPosY;
    b32 isDragging;
    s32 prevMousePosX, prevMousePosY;
    
    //IMPORTANT NOTE:
    // As of right now lsUI DEPENDS on Input.
    // I don't know if this is the right choice. I guess I'll discover it.
    Input UserInput;
    b32 hasReceivedInput;
    
    //Why did I even make this change? I just moved all the shit form UIContext to UIWindow
    u64 *currentFocus;
    u64 *lastFocus;
    b32 focusWasSetThisFrame;
    
    b32 nextFrameFocusChange;
    u64 *nextFrameFocus;
    
    u64 *mouseCapture;
};

typedef void (*RenderCallback)(UIContext *);
typedef void (*onDestroyFunc)(UIContext *);
struct UIContext
{
    //TODO: Do I actually need to store *ALL* the window information? Can't the user keep track of it?
    //UIWindow *win;
    UIWindow *currWindow;
    bool mustRender;
    

    UIFontGroup fontGroup;
    UIFont *currFont;
    u32 currPixelHeight; //TODO: This does not seem necessary
    
    //TODO: By putting the style in the context, each widget does NOT have to
    //      have it, thus making each widget's struct smaller. But it's also a pain for the user
    //      to program and less easily customizable by widget (where you may want specific parts of
    //      the widget to be styled different!)
    Color backgroundColor;
    Color borderColor;
    Color menuBarColor;
    
    Color highliteColor;
    Color pressedColor;
    
    Color widgetColor;
    Color textColor;
    Color invWidgetColor;
    Color invTextColor;
    
    UIRect scissor;
    
    UIScrollableRegion *scroll;
    
    RenderGroup renderGroups[LS_UI_RENDER_GROUP_COUNT];
#ifndef LS_UI_OPENGL_BACKEND
    CONDITION_VARIABLE startRender;
    CRITICAL_SECTION crit;
#endif
    
#ifdef LS_UI_OPENGL_BACKEND
    HGLRC    OGLContext;
    UIShader sdfTextProgram;
    UIShader textProgram;
    UIShader rectProgram;
    UIShader gradientRectProgram;
    UIShader texturedRectProgram;
    UIShader circleProgram;
    UIShader colorWheelProgram;
    s32      circleVertCount;
#endif
    
    
#if _DEBUG //NOTE: Tag to debug specific render commands
    b32 isTagged;
    FW_FileWatcher fileWatcher;
#endif
    
    RenderCallback renderFunc;
    u32 dt;
    RegionTimer frameTime;
    
    Arena frameArena;
    Arena contextArena;
    Arena widgetArena;
    
    //TODO: This means scratches could interfere with each other
    // Would be solved by making a ScratchArena type, which deals with this stuff.
    // So right now, the rule is *you have to allocate and de-allocate within the same function!*
    // This way, functions can't stomp over each other's data.
    // If it becomes a real problem in the future, I'll just fix it then.
    Arena scratchArena;
    
    onDestroyFunc onDestroy;
};

struct ___threadCtx
{
    UIContext *c;
    u64 ThreadID;
};


//NOTE: Functions

UIWindow     ls_uiCreateWindow(HINSTANCE MainInstance, UIContext *c, u8 *backBuffer, s32 w, s32 h, const char *name, bool shouldShow);
UIWindow     ls_uiCreateWindow(UIContext *c, u8 *backBuffer, s32 w, s32 h, const char *name, bool shouldShow);
UIContext *  ls_uiInitDefaultContext(s32 contextArenaSize, s32 frameArenaSize, s32 widgetArenaSize, RenderCallback cb);
UIContext *  ls_uiInitDefaultContext(Arena contextArena, Arena frameArena, Arena widgetArena, RenderCallback cb);

void         ls_uiStartFrameTimer(UIContext *c);
void         ls_uiEndFrameTimer(UIContext *c, u64 frameTimeTargetMs);

void         ls_uiFrameBegin(UIContext *c, UIWindow *win);
void         ls_uiFrameEnd(UIContext *c, u64 frameTimeTargetMs);

void         ls_uiAddOnDestroyCallback(UIContext *c, onDestroyFunc f);

void         ls_uiPushRenderCommand(UIContext *c, RenderCommand command, s32 zLayer);
void         ls_uiStartScrollableRegion(UIContext *c, UIScrollableRegion *scroll);
void         ls_uiEndScrollableRegion(UIContext *c);
void         ls_uiResetScrollableRegion(UIContext *c);

void         ls_uiFocusChangeSameFrame(UIContext *c, u64 *focus);
void         ls_uiFocusChange(UIContext *c, u64 *focus);
b32          ls_uiInFocus(UIContext *c, void *p);
b32          ls_uiHasCapture(UIContext *c, void *p);

void         ls_uiRender(UIContext *c);

#if _DEBUG
void         ls_uiDebugLog(UIContext *c, s32 x, s32 y, const char *fmt, ...);
#endif

#endif


#ifdef LS_UI_IMPLEMENTATION

//Internal Includes?
#include "lsUI.utils.cpp"
#include "lsUI.primitives.cpp"

#ifdef LS_UI_OPENGL_BACKEND
#include "lsUI.opengl.cpp"
#endif

#include "lsUI.bitmaps.cpp"
#include "lsUI.rects.cpp"
#include "lsUI.fonts.cpp"
#include "lsUI.textboxes.cpp"
#include "lsUI.labels.cpp"
#include "lsUI.listboxes.cpp"
#include "lsUI.buttons.cpp"
#include "lsUI.checks.cpp"
#include "lsUI.sliders.cpp"
#include "lsUI.menus.cpp"
#include "lsUI.colorpickers.cpp"


#if _DEBUG
static u64 __debug_frameNumber = 0;

void ls_uiDebugLog(UIContext *c, s32 x, s32 y, const char *fmt, ...)
{
    Arena prev = ls_arenaUse(c->frameArena);
    
    va_list argList;
    va_start(argList, fmt);
    
    const s32 buffSize = 512;
    char *buff = (char *)ls_alloc(buffSize);
    
    s32 len = ls_vlog(fmt, buff, buffSize, &argList);
    
    va_end(argList);
    
    utf8 label = ls_utf8Constant((u8 *)buff, len);
    
    ls_uiLabel(c, label, x, y, RGBg(255), 2);
    ls_uiLabel(c, label, x-1, y, RGBg(0), 2);
    
    ls_arenaUse(prev);
}

void ls_uiDebugDrawInfo(UIContext *c)
{
    Arena prev = ls_arenaUse(c->frameArena);
    s32 prevPx = ls_uiSelectFontByPixelHeight(c, 18);

#ifndef LS_UI_OPENGL_BACKEND
    for(s32 i = 0; i < __LS_UI_THREAD_COUNT; i++)
    {
        UIRect r = c->currWindow->renderUIRects[i];
        ls_uiRect(c, r.minX, r.minY, r.maxX - r.minX, r.maxY - r.minY, RGBA(0,0,0,0), RGB(253, 0, 255), 3);
    }
    ls_uiLabel(c, U"Backend: SOFTWARE"_W, 0.02f, 0.95f, c->textColor, 3);
#else
    ls_uiLabel(c, U"Backend: OPENGL"_W, 0.02f, 0.95f, c->textColor, 3);
#endif
    
    utf32 frameTime = ls_utf32FromInt(c->dt);
    ls_uiLabel(c, frameTime, 0.95f, 0.95f, c->textColor, 3);

    ls_uiSelectFontByPixelHeight(c, prevPx);
    ls_arenaUse(prev);
}

#else //_DEBUG

#define ls_uiDebugLog(...)
#define ls_uiDebugDrawInfo(...)

#endif //_DEBUG

#ifndef LS_UI_OPENGL_BACKEND
void __ls_ui_fillRenderThreadUIRects(UIContext *c, UIWindow *win)
{
    UIRect *renderUIRects = win->renderUIRects;

    //NOTE: All Thread Rects are inclusive on the left/bot, exclusive on the right/top
    switch(__LS_UI_THREAD_COUNT)
    {
        case 0:
        case 1: { renderUIRects[0] = {0, 0, win->width, win->height }; } break;
        
        case 2:
        {
            renderUIRects[0] = {            0, 0, win->width/2, win->height };
            renderUIRects[1] = { win->width/2, 0, win->width,   win->height };
        } break;
        
        case 4:
        {
            renderUIRects[0] = {            0,             0, win->width/2, win->height/2 };
            renderUIRects[1] = { win->width/2,             0, win->width,   win->height/2 };
            renderUIRects[2] = {            0, win->height/2, win->width/2, win->height   };
            renderUIRects[3] = { win->width/2, win->height/2, win->width,   win->height   };
        } break;
        
        case 8:
        {
            renderUIRects[0] = {              0,             0,   win->width/4, win->height/2 };
            renderUIRects[1] = {   win->width/4,             0,   win->width/2, win->height/2 };
            renderUIRects[2] = {   win->width/2,             0, 3*win->width/4, win->height/2 };
            renderUIRects[3] = { 3*win->width/4,             0,   win->width,   win->height/2 };
            renderUIRects[4] = {              0, win->height/2,   win->width/4, win->height   };
            renderUIRects[5] = {   win->width/4, win->height/2,   win->width/2, win->height   };
            renderUIRects[6] = {   win->width/2, win->height/2, 3*win->width/4, win->height   };
            renderUIRects[7] = { 3*win->width/4, win->height/2,   win->width,   win->height   };
        } break;
        
        default: { AssertMsg(FALSE, "Unhandled Thread Count"); } break;
    }
    
    return;
}
#else
#define __ls_ui_fillRenderThreadUIRects(...)
#endif

LRESULT ls_uiWindowProc(HWND h, UINT msg, WPARAM w, LPARAM l)
{
    LRESULT Result = 0;
    
    UIContext *c      = (UIContext *)GetWindowLongPtrA(h, GWLP_USERDATA);
    if (!c || !c->currWindow) {
        if (msg == WM_CREATE) {
            CREATESTRUCTA *CreateStruct = (CREATESTRUCTA *)l;
            c = (UIContext *)CreateStruct->lpCreateParams;
            SetWindowLongPtrA(h, GWLP_USERDATA, (LONG_PTR)c);
            //TODO: See If I need to access the UIWIndow (which has already been created) and assign this there
            // Otherwise, this can never be called
            //if (win) { win->hasReceivedInput = TRUE; }
            return 0;
        }
        else {
            return DefWindowProcA(h, msg, w, l);
        }
    }
    UIWindow *win     = c->currWindow;
    MouseInput *Mouse = &win->UserInput.Mouse;
    Input *UserInput  = &win->UserInput;

    //static b32 mouseTracking = FALSE;
    
    switch (msg)
    {
        case WM_ERASEBKGND: return TRUE; break;
        
        //NOTETODO:
        // This is used to handle the size of the non client area.
        // By handling it ourselves windows will not keep track of it, supposedly?
        case WM_NCCALCSIZE:
        {
            if(w == TRUE) {
                //NCCALCSIZE_PARAMS* pncsp = (NCCALCSIZE_PARAMS*)lParam;
                return 0;
            }
        } break;
        
        //NOTETODO:
        // Since we won't let windows keep track of the non client area, we need to hit test
        // ourselves for re-sizing the window
        case WM_NCHITTEST:
        {
            // Handle resizing
            // Allow resizing from the borders
            POINTS pts = MAKEPOINTS(l);
            RECT rcWindow;
            if(GetWindowRect(h, &rcWindow) == 0)
            { LogMsg(FALSE, "GetWindowRect failed during WM_NCHITTEST."); }
            
            const s32 BORDER_WIDTH = 4;
            if (pts.y >= rcWindow.top && pts.y <= rcWindow.top+BORDER_WIDTH) {
                if (pts.x >= rcWindow.left && pts.x <= rcWindow.left + BORDER_WIDTH) return HTTOPLEFT;
                if (pts.x >= rcWindow.right - BORDER_WIDTH && pts.x <= rcWindow.right) return HTTOPRIGHT;
                return HTTOP;
            }
            if (pts.y >= rcWindow.bottom - BORDER_WIDTH && pts.y <= rcWindow.bottom) {
                if (pts.x >= rcWindow.left && pts.x <= rcWindow.left + BORDER_WIDTH) return HTBOTTOMLEFT;
                if (pts.x >= rcWindow.right - BORDER_WIDTH && pts.x <= rcWindow.right) return HTBOTTOMRIGHT;
                return HTBOTTOM;
            }
            if (pts.x >= rcWindow.left && pts.x <= rcWindow.left + BORDER_WIDTH) return HTLEFT;
            if (pts.x >= rcWindow.right - BORDER_WIDTH && pts.x <= rcWindow.right) return HTRIGHT;
            
            return HTCLIENT;
        } break;
        
        //NOTE
        //A few messages are sent BEFORE WM_CREATE
        //   WM_GETMINMAXINFO WM_NCCREATE and WM_NCCALCSIZE.
        //   So GWL_USERDATA will be not yet set and "This" will be NULL for these messages. 
        //   Be careful if you are interested in processing these messages.
        case WM_CREATE:
        {
            CREATESTRUCTA *CreateStruct = (CREATESTRUCTA *)l;
            c = (UIContext *)CreateStruct->lpCreateParams;
            SetWindowLongPtrA(h, GWLP_USERDATA, (LONG_PTR)c);
            if (win) { win->hasReceivedInput = TRUE; } //I Think this can never be true?
            
        } break;
        
        case WM_ACTIVATE:
        {
            if(w == WA_INACTIVE) { 
                //SendMessageA(c->MainWindow, WM_LBUTTONUP, 0, 0);
                //TODO: Maybe NULL everything in the deactivated window? Input should not matter there anymore
                UserInput->Keyboard.currentState    = {};
                UserInput->Keyboard.prevState       = {};
                UserInput->Keyboard.repeatState     = {};
                UserInput->Keyboard.hasPrintableKey = FALSE;
                
                UserInput->Mouse.isLeftPressed    = FALSE;
                UserInput->Mouse.wasLeftPressed   = FALSE;
                UserInput->Mouse.isMiddlePressed  = FALSE;
                UserInput->Mouse.wasMiddlePressed = FALSE;
                UserInput->Mouse.isRightPressed   = FALSE;
                UserInput->Mouse.wasRightPressed  = FALSE;
            }
        } break;
        
        //TODO: Handling WM_SIZING would probably produce better results.
        //TODO: This will only be used for fixed size steps
        //TODO BUG!!! In Software Render, for specific resize dimensions, it seems like one of the render threads is getting
        //  stuck and not reporting the "isDone" condition variable. (maybe because of bad render rects?)
        case WM_SIZE:
        {
#ifndef LS_UI_OPENGL_BACKEND
            //if(!c || !c->currWindow) { return DefWindowProcA(h, msg, w, l); }
            UIWindow *win = c->currWindow;
            
            u32 width       = LOWORD(l);
            u32 height      = HIWORD(l);
            
            //NOTE: Need to resize the backbuffer if the window grows.
            if(width*height > win->backbufferW * win->backbufferH)
            {
                //NOTE: Delete the old DibSection AND the old BackBufferDC
                //      Otherwise it would VERY quickly leak GBs of memory
                DeleteObject(win->DibSection);
                DeleteDC(win->BackBufferDC);
                
                //NOTE: Create a new DC
                BITMAPINFO BackBufferInfo              = {};
                BackBufferInfo.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
                BackBufferInfo.bmiHeader.biWidth       = width;
                BackBufferInfo.bmiHeader.biHeight      = height;
                BackBufferInfo.bmiHeader.biPlanes      = 1;
                BackBufferInfo.bmiHeader.biBitCount    = 32;
                BackBufferInfo.bmiHeader.biCompression = BI_RGB;
                
                win->BackBufferDC       = CreateCompatibleDC(win->WindowDC);
                win->DibSection         = CreateDIBSection(win->BackBufferDC, &BackBufferInfo,
                                                         DIB_RGB_COLORS, (void **)&(win->drawBuffer), NULL, 0);
                SelectObject(win->BackBufferDC, win->DibSection);
                
                win->backbufferW = width;
                win->backbufferH = height;
            }
            
            //NOTE: Draw Buffer Dimensions
            //if(win)
            {
                win->width        = width;
                win->height       = height;
            }
            
            //NOTE: Client window position.
            RECT windowRect = {};
            if(GetWindowRect(h, &windowRect) != 0)
            {
                win->windowPosX = windowRect.left;
                win->windowPosY = windowRect.top;
            }
            else { LogMsg(FALSE, "GetWindowRect failed after resize."); }
            
            //NOTE: Mouse position
            POINT currMouse = {};
            if(GetCursorPos(&currMouse) != 0)
            {
                win->prevMousePosX = currMouse.x;
                win->prevMousePosY = currMouse.y;
            }
            else { LogMsg(FALSE, "GetCursorPos failed after resize."); }
            
            //NOTE: Reset the Render UIRect for every Thread.
            __ls_ui_fillRenderThreadUIRects(c, win);
#else
            if(!c || !glViewport) { return DefWindowProcA(h, msg, w, l); }
            
            u32 width       = LOWORD(l);
            u32 height      = HIWORD(l);
            
            //if(win)
            {
                //NOTE: Draw Buffer Dimensions
                //
                win->width        = width;
                win->height       = height;
                
                //NOTE: Client window position.
                RECT windowRect = {};
                if(GetWindowRect(h, &windowRect) != 0)
                {
                    win->windowPosX = windowRect.left;
                    win->windowPosY = windowRect.top;
                }
                else { LogMsg(FALSE, "GetWindowRect failed after resize."); }
                
                //NOTE: Mouse position
                POINT currMouse = {};
                if(GetCursorPos(&currMouse) != 0)
                {
                    win->prevMousePosX = currMouse.x;
                    win->prevMousePosY = currMouse.y;
                }
                else { LogMsg(FALSE, "GetCursorPos failed after resize."); }
                
                const f64 aspectRatio = (f64)width / (f64)height;
                f64 xSpan = 1.0;
                f64 ySpan = 1.0;
                
                //NOTE: Width > Height, so scale xSpan accordingly
                if(aspectRatio > 1.0) { xSpan *= aspectRatio; }
                //NOTE: Width < Height, so scale ySpan accordingly
                else                  { ySpan *= aspectRatio; }

                wglMakeCurrent(win->WindowDC, c->OGLContext);
            }
            
            glViewport(0, 0, width, height);
#endif
            return 0;
        } break;
        
        case WM_PAINT:
        {
            PAINTSTRUCT ps = {};
            RECT r;
            UIWindow *win = c->currWindow;
            
            //NOTE: I have to call BeginPaint() - EndPaint() Anyway.
            //If I don't, the message loop is gonna get stuck in PAINT calls.
            BeginPaint(h, &ps);
            
            //NOTE: Draw Background
            GetClientRect(h, &r);
            
            BITMAPINFO BitmapInfo = {};
            BitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            BitmapInfo.bmiHeader.biWidth = win->width;
            BitmapInfo.bmiHeader.biHeight = win->height;
            BitmapInfo.bmiHeader.biPlanes = 1;
            BitmapInfo.bmiHeader.biBitCount = 32;
            BitmapInfo.bmiHeader.biCompression = BI_RGB;
            
            StretchDIBits(win->BackBufferDC, 0, 0, win->width, win->height,
                          0, 0, win->width, win->height,
                          win->drawBuffer, &BitmapInfo, DIB_RGB_COLORS, SRCCOPY);
            
            Result = BitBlt(win->WindowDC, 0, 0, win->width, win->height, win->BackBufferDC, 0, 0, SRCCOPY);
            
            if(Result == 0) {
                DWORD Err = GetLastError();
                int breakHere = 0;
            }
            
            EndPaint(h, &ps);
        } break;
        
        case WM_CHAR:
        {
            win->hasReceivedInput = TRUE;
            
            b32 wasPressed = (l >> 30) & 0x1;
            u16 repeat     = (u16)l;
            
            b32 asciiRange  = ((w >= 32) && (w <= 126));
            b32 plane0Latin = ((w >= 0x00A1) && (w <= 0x024F));
            
            if(asciiRange || plane0Latin)
            {
                if(!wasPressed || repeat > 0)
                {
                    UserInput->Keyboard.hasPrintableKey = TRUE;
                    UserInput->Keyboard.keyCodepoint    = w;
                }
            }
            else if(w == 13) //NOTETODO: Hack to input a '\n' when Enter ('\r') is pressed.
            {
                if(!wasPressed || repeat > 0)
                {
                    UserInput->Keyboard.hasPrintableKey = TRUE;
                    UserInput->Keyboard.keyCodepoint    = 10;
                }
            }
            
        } break;
        
        case WM_KEYDOWN:
        {
            win->hasReceivedInput = TRUE;
            
            //Repeat is the first 16 bits of the LPARAM. Bits [0-15];
            u16 rep = (u16)l;
            
            switch(w)
            { 
                //NOTETODO: F9 and F10 (Maybe F11) seem to not send WM_KEYDOWN and WM_KEYUP messages)
                case VK_F1:      KeySetAndRepeat(keyMap::F1, rep);        break;
                case VK_F2:      KeySetAndRepeat(keyMap::F2, rep);        break;
                case VK_F3:      KeySetAndRepeat(keyMap::F3, rep);        break;
                case VK_F4:      KeySetAndRepeat(keyMap::F4, rep);        break;
                case VK_F5:      KeySetAndRepeat(keyMap::F5, rep);        break;
                case VK_F6:      KeySetAndRepeat(keyMap::F6, rep);        break;
                case VK_F7:      KeySetAndRepeat(keyMap::F7, rep);        break;
                case VK_F8:      KeySetAndRepeat(keyMap::F8, rep);        break;
                case VK_F12:     KeySetAndRepeat(keyMap::F12, rep);       break;
                
                case VK_DOWN:    KeySetAndRepeat(keyMap::DArrow, rep);    break;
                case VK_UP:      KeySetAndRepeat(keyMap::UArrow, rep);    break;
                case VK_LEFT:    KeySetAndRepeat(keyMap::LArrow, rep);    break;
                case VK_RIGHT:   KeySetAndRepeat(keyMap::RArrow, rep);    break;
                
                case VK_ESCAPE:  KeySetAndRepeat(keyMap::Escape, rep);    break;
                case VK_RETURN:  KeySetAndRepeat(keyMap::Enter, rep);     break;
                case VK_BACK:    KeySetAndRepeat(keyMap::Backspace, rep); break;
                case VK_DELETE:  KeySetAndRepeat(keyMap::Delete, rep);    break;
                case VK_HOME:    KeySetAndRepeat(keyMap::Home, rep);      break;
                case VK_END:     KeySetAndRepeat(keyMap::End, rep);       break;
                case VK_CONTROL: KeySetAndRepeat(keyMap::Control, rep);   break;
                case VK_MENU:    KeySetAndRepeat(keyMap::RAlt, rep);      break;
                case VK_SHIFT:   KeySetAndRepeat(keyMap::Shift, rep);     break; //TODO: Differentiate L/R Shift
                
                case 'A':        KeySetAndRepeat(keyMap::A, rep);         break;
                case 'B':        KeySetAndRepeat(keyMap::B, rep);         break;
                case 'C':        KeySetAndRepeat(keyMap::C, rep);         break;
                case 'D':        KeySetAndRepeat(keyMap::D, rep);         break;
                case 'E':        KeySetAndRepeat(keyMap::E, rep);         break;
                case 'F':        KeySetAndRepeat(keyMap::F, rep);         break;
                case 'G':        KeySetAndRepeat(keyMap::G, rep);         break;
                case 'H':        KeySetAndRepeat(keyMap::H, rep);         break;
                case 'I':        KeySetAndRepeat(keyMap::I, rep);         break;
                case 'J':        KeySetAndRepeat(keyMap::J, rep);         break;
                case 'K':        KeySetAndRepeat(keyMap::K, rep);         break;
                case 'L':        KeySetAndRepeat(keyMap::L, rep);         break;
                case 'M':        KeySetAndRepeat(keyMap::M, rep);         break;
                case 'N':        KeySetAndRepeat(keyMap::N, rep);         break;
                case 'O':        KeySetAndRepeat(keyMap::O, rep);         break;
                case 'P':        KeySetAndRepeat(keyMap::P, rep);         break;
                case 'Q':        KeySetAndRepeat(keyMap::Q, rep);         break;
                case 'R':        KeySetAndRepeat(keyMap::R, rep);         break;
                case 'S':        KeySetAndRepeat(keyMap::S, rep);         break;
                case 'T':        KeySetAndRepeat(keyMap::T, rep);         break;
                case 'U':        KeySetAndRepeat(keyMap::U, rep);         break;
                case 'V':        KeySetAndRepeat(keyMap::V, rep);         break;
                case 'W':        KeySetAndRepeat(keyMap::W, rep);         break;
                case 'X':        KeySetAndRepeat(keyMap::X, rep);         break;
                case 'Y':        KeySetAndRepeat(keyMap::Y, rep);         break;
                case 'Z':        KeySetAndRepeat(keyMap::Z, rep);         break;
            }
            
        } break;
        
        case WM_KEYUP:
        {
            win->hasReceivedInput = TRUE;
            
            switch(w)
            { 
                //NOTETODO: F9 and F10 (Maybe F11) seem to not send WM_KEYDOWN and WM_KEYUP messages)
                case VK_F1:      KeyUnset(keyMap::F1);        break;
                case VK_F2:      KeyUnset(keyMap::F2);        break;
                case VK_F3:      KeyUnset(keyMap::F3);        break;
                case VK_F4:      KeyUnset(keyMap::F4);        break;
                case VK_F5:      KeyUnset(keyMap::F5);        break;
                case VK_F6:      KeyUnset(keyMap::F6);        break;
                case VK_F7:      KeyUnset(keyMap::F7);        break;
                case VK_F8:      KeyUnset(keyMap::F8);        break;
                case VK_F12:     KeyUnset(keyMap::F12);       break;
                
                case VK_DOWN:    KeyUnset(keyMap::DArrow);    break;
                case VK_UP:      KeyUnset(keyMap::UArrow);    break;
                case VK_LEFT:    KeyUnset(keyMap::LArrow);    break;
                case VK_RIGHT:   KeyUnset(keyMap::RArrow);    break;
                
                case VK_ESCAPE:  KeyUnset(keyMap::Escape);    break;
                case VK_RETURN:  KeyUnset(keyMap::Enter);     break;
                case VK_BACK:    KeyUnset(keyMap::Backspace); break;
                case VK_DELETE:  KeyUnset(keyMap::Delete);    break;
                case VK_HOME:    KeyUnset(keyMap::Home);      break;
                case VK_END:     KeyUnset(keyMap::End);       break;
                case VK_CONTROL: KeyUnset(keyMap::Control);   break;
                case VK_MENU:    KeyUnset(keyMap::RAlt);      break;
                case VK_SHIFT:   KeyUnset(keyMap::Shift);     break; //TODO: Differentiate L/R Shift
                
                case 'A':        KeyUnset(keyMap::A);         break;
                case 'B':        KeyUnset(keyMap::B);         break;
                case 'C':        KeyUnset(keyMap::C);         break;
                case 'D':        KeyUnset(keyMap::D);         break;
                case 'E':        KeyUnset(keyMap::E);         break;
                case 'F':        KeyUnset(keyMap::F);         break;
                case 'G':        KeyUnset(keyMap::G);         break;
                case 'H':        KeyUnset(keyMap::H);         break;
                case 'I':        KeyUnset(keyMap::I);         break;
                case 'J':        KeyUnset(keyMap::J);         break;
                case 'K':        KeyUnset(keyMap::K);         break;
                case 'L':        KeyUnset(keyMap::L);         break;
                case 'M':        KeyUnset(keyMap::M);         break;
                case 'N':        KeyUnset(keyMap::N);         break;
                case 'O':        KeyUnset(keyMap::O);         break;
                case 'P':        KeyUnset(keyMap::P);         break;
                case 'Q':        KeyUnset(keyMap::Q);         break;
                case 'R':        KeyUnset(keyMap::R);         break;
                case 'S':        KeyUnset(keyMap::S);         break;
                case 'T':        KeyUnset(keyMap::T);         break;
                case 'U':        KeyUnset(keyMap::U);         break;
                case 'V':        KeyUnset(keyMap::V);         break;
                case 'W':        KeyUnset(keyMap::W);         break;
                case 'X':        KeyUnset(keyMap::X);         break;
                case 'Y':        KeyUnset(keyMap::Y);         break;
                case 'Z':        KeyUnset(keyMap::Z);         break;
            }
        } break;
        
        case WM_LBUTTONDOWN:
        {
            win->hasReceivedInput  = TRUE;
            Mouse->isLeftPressed = TRUE;
            return 0;
        } break;
        
        case WM_LBUTTONUP:
        {
            win->hasReceivedInput  = TRUE;
            Mouse->isLeftPressed = FALSE;
            return 0;
        } break;
        
        case WM_RBUTTONDOWN:
        { 
            win->hasReceivedInput   = TRUE;
            Mouse->isRightPressed = TRUE;
            return 0;
        } break;
        
        case WM_RBUTTONUP:
        { 
            win->hasReceivedInput   = TRUE; 
            Mouse->isRightPressed = FALSE;
            return 0;
        } break;
        
        /*
        case WM_MOUSELEAVE:
        {
            mouseTracking = FALSE;
            
            Mouse->isLeftPressed    = FALSE;
            Mouse->isMiddlePressed  = FALSE;
            Mouse->isRightPressed   = FALSE;
        } break;
        */
        case WM_MOUSEMOVE:
        {
            /*
            if(!mouseTracking) 
            {
                TRACKMOUSEEVENT tme;
                tme.cbSize = sizeof(tme);
                tme.hwndTrack = h;
                tme.dwFlags = TME_LEAVE;
                //tme.dwHoverTime = HOVER_DEFAULT;
                TrackMouseEvent(&tme);
                mouseTracking = TRUE;
            }
            */
            
            POINTS currMouseClient = *((POINTS *)&l);
            Mouse->currPosX = currMouseClient.x;
            Mouse->currPosY = win->height - currMouseClient.y;
            
            win->hasReceivedInput = TRUE;
            
            
            //NOTETODO: Is setting the cursor every single MOUSEMOVE bad?
            //      The spec says:
            //          The cursor is set only if the new cursor is different from 
            //          the previous cursor; otherwise, the function returns immediately.
            //
            //      So I believe this is fine.
            
            //NOTE: MSDN says to return 0
            return 0;
        } break;
        
        case WM_MOUSEWHEEL:
        {
            win->hasReceivedInput = TRUE;
            Mouse->wheelDelta     = GET_WHEEL_DELTA_WPARAM(w); //((s16)(w >> 16))*WHEEL_DELTA;
            Mouse->isWheelRotated = TRUE;
        } break;
        
        case WM_DESTROY:
        {
            if(c->onDestroy) { c->onDestroy(c); }
            ExitProcess(0);
        } break;
        
        default: { return DefWindowProcA(h, msg, w, l); }
    }
    
    return Result;
}

void __ui_RegisterWindow(HINSTANCE MainInstance, const char *name)
{
    
    u32 prop = CS_VREDRAW | CS_HREDRAW; //CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
    
    WNDCLASSA WindowClass = { 0 };
    WindowClass.style = prop;
    WindowClass.lpfnWndProc = ls_uiWindowProc;
    WindowClass.hInstance = MainInstance;
    WindowClass.lpszClassName = name;
    
    //NOTE: If we don't load the cursor here, windows wouldn't reset it to the correct bitmap
    //      after it changes (for example during resizing)
    WindowClass.hCursor = LoadCursorA(NULL, IDC_ARROW);
    
    if (!RegisterClassA(&WindowClass))
    {
        DWORD Error = GetLastError();
        ls_printf("When Registering WindowClass in Win32_SetupScreen got error: %d", Error);
    }
}

UIWindow __ui_CreateWindow(HINSTANCE MainInstance, UIContext *c, u8 *backBuffer, s32 width, s32 height, const char *windowName, const char* wndclass)
{
    UIWindow win        = {};
    win.drawBuffer      = backBuffer;
    win.backbufferW     = width;
    win.backbufferH     = height;
    win.width           = width;
    win.height          = height;

    u32 style = LS_THICK_BORDER | LS_POPUP;// | LS_RESIZE;// | LS_VISIBLE; //| LS_OVERLAPPEDWINDOW;
    BOOL Result;
    
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int screenWidth  = GetSystemMetrics(SM_CXSCREEN);
    
    int spaceX = (screenWidth - win.backbufferW) / 2;
    int spaceY = ((screenHeight - win.backbufferH) / 2);
    if(spaceX < 0) { spaceX = 0; }
    if(spaceY < 0) { spaceY = 0; }
    
    HWND WindowHandle;
    if ((WindowHandle = CreateWindowExA(0 /*WS_EX_LAYERED*/, wndclass, windowName, style,
                                        spaceX, spaceY, win.backbufferW, win.backbufferH,
                                        0, 0, MainInstance, c)) == nullptr)
    {
        DWORD Error = GetLastError();
        ls_printf("When Retrieving a WindowHandle in Win32_SetupScreen got error: %d", Error);
    }
    win.Window = WindowHandle;
    
    HCURSOR DefaultArrow = LoadCursorA(NULL, IDC_ARROW);
    SetCursor(DefaultArrow);
    
#ifdef LS_UI_OPENGL_BACKEND
    __ui_CreateOpenGLWindow(c, &win, WindowHandle);
#else
    
    BITMAPINFO BackBufferInfo = {};
    BackBufferInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    BackBufferInfo.bmiHeader.biWidth = win.backbufferW;
    BackBufferInfo.bmiHeader.biHeight = win.backbufferH;
    BackBufferInfo.bmiHeader.biPlanes = 1;
    BackBufferInfo.bmiHeader.biBitCount = 32;
    BackBufferInfo.bmiHeader.biCompression = BI_RGB;
    
    win.WindowDC           = GetDC(WindowHandle);
    win.BackBufferDC       = CreateCompatibleDC(win.WindowDC);
    win.DibSection         = CreateDIBSection(win.BackBufferDC, &BackBufferInfo,
                                             DIB_RGB_COLORS, (void **)&(win.drawBuffer), NULL, 0);
    SelectObject(win.BackBufferDC, win.DibSection);

#endif
    
    win.windowPosX = (s16)spaceX;
    win.windowPosY = (s16)spaceY;
    
    return win;
}

UIWindow ls_uiCreateWindow(HINSTANCE MainInstance, UIContext *c, u8 *backBuffer, s32 w, s32 h, const char *name, bool shouldShow = true)
{
    __ui_RegisterWindow(MainInstance, name);
    
    UIWindow win = __ui_CreateWindow(MainInstance, c, backBuffer, w, h, name, name);
    win.UserInput.Keyboard.getClipboard = windows_GetClipboard;
    win.UserInput.Keyboard.setClipboard = windows_SetClipboard;
    
    __ls_ui_fillRenderThreadUIRects(c, &win);

    if(shouldShow) { ShowWindow(win.Window, SW_SHOW); win.hasReceivedInput = TRUE; }
    
    return win;
}

UIWindow ls_uiCreateWindow(UIContext *c, u8 *backBuffer, s32 w, s32 h, const char *name, bool shouldShow = true)
{
    HINSTANCE MainInstance = NULL;
    __ui_RegisterWindow(MainInstance, name);
    
    UIWindow win = __ui_CreateWindow(MainInstance, c, backBuffer, w, h, name, name);
    win.UserInput.Keyboard.getClipboard = windows_GetClipboard;
    win.UserInput.Keyboard.setClipboard = windows_SetClipboard;
    
    __ls_ui_fillRenderThreadUIRects(c, &win);

    if(shouldShow) { ShowWindow(win.Window, SW_SHOW); win.hasReceivedInput = TRUE; }
    
    return win;
}

void ls_uiRender__(UIContext *c, u32 threadID);
#ifndef LS_UI_OPENGL_BACKEND
DWORD ls_uiRenderThreadProc(void *param)
{
    ___threadCtx *t = (___threadCtx *)param;
    
    UIContext *c = t->c;
    u64 threadID = t->ThreadID;
    
    while(TRUE)
    {
        EnterCriticalSection(&c->crit);
        SleepConditionVariableCS(&c->startRender, &c->crit, INFINITE);
        LeaveCriticalSection(&c->crit);
        
        ls_uiRender__(c, threadID);
    }
    
    AssertMsg(FALSE, "Render Thread should never exit\n");
    
    return 0;
}
#endif

void __ui_default_windows_render_callback(UIContext *c)
{
#ifdef LS_UI_OPENGL_BACKEND
    SwapBuffers(c->currWindow->WindowDC);
#else
    InvalidateRect(c->currWindow->Window, NULL, TRUE);
#endif //LS_UI_OPENGL_BACKEND
}

UIContext *ls_uiInitDefaultContext(Arena contextArena, Arena frameArena, Arena widgetArena,
                                   RenderCallback cb = __ui_default_windows_render_callback)
{
    ls_arenaUse(contextArena);
    
    UIContext *uiContext       = (UIContext *)ls_alloc(sizeof(UIContext));
    uiContext->currWindow      = NULL;
    uiContext->contextArena    = contextArena;
    uiContext->frameArena      = frameArena;
    uiContext->widgetArena     = widgetArena;
    uiContext->scratchArena    = ls_arenaCreate(MBytes(4), (char*)"scratchArena"); //TODO: Not a superfan of 4MB

    uiContext->renderFunc      = cb;
    uiContext->backgroundColor = RGB(34, 40, 49);
    uiContext->borderColor     = RGBg(0x22);
    uiContext->menuBarColor    = RGBg(0x20);
    uiContext->highliteColor   = RGBg(0x65);
    uiContext->pressedColor    = RGBg(0x75);
    uiContext->widgetColor     = RGBg(0x45);
    uiContext->textColor       = RGBg(0xCC);
    uiContext->invWidgetColor  = RGBg(0xBA);
    uiContext->invTextColor    = RGBg(0x33);
    uiContext->scroll          = {};
    
    //NOTETODO: The scissor is currently not used or relevant. The code remains around because fuck it.
    uiContext->scissor         = UIRect { 0, 0, 999999, 999999 };
    uiContext->frameTime       = {};
    
    //TODO: Make number of zLayers and zLayer Storage more customizable!
#ifdef LS_UI_SOFTWARE_BACKEND
    if(__LS_UI_THREAD_COUNT != 0)
    {
        for(u32 i = 0; i < __LS_UI_THREAD_COUNT; i++)
        {
            uiContext->renderGroups[i].RenderCommands[0] = ls_stackInit(sizeof(RenderCommand), 512);
            
            for(s32 zLayer = 1; zLayer < UI_Z_LAYERS; zLayer++)
            {
                uiContext->renderGroups[i].RenderCommands[zLayer] = ls_stackInit(sizeof(RenderCommand), 256);
            }
        }
        
        InitializeConditionVariable(&uiContext->startRender);
        InitializeCriticalSection(&uiContext->crit);
        
        for(u32 i = 0; i < __LS_UI_THREAD_COUNT; i++)
        {
            ___threadCtx *t = (___threadCtx *)ls_alloc(sizeof(___threadCtx));
            t->c            = uiContext;
            t->ThreadID     = i;
            
            CreateThread(NULL, KBytes(512), ls_uiRenderThreadProc, t, 0, NULL);
        }
    }
    else
    {
        uiContext->renderGroups[0].RenderCommands[0] = ls_stackInit(sizeof(RenderCommand), 512);
        
        for(s32 zLayer = 1; zLayer < UI_Z_LAYERS; zLayer++)
        {
            uiContext->renderGroups[0].RenderCommands[zLayer] = ls_stackInit(sizeof(RenderCommand), 256);
        }
    }
#elif defined(LS_UI_OPENGL_BACKEND)
    uiContext->renderGroups[0].RenderCommands[0] = ls_stackInit(sizeof(RenderCommand), 512);
    
    for(s32 zLayer = 1; zLayer < UI_Z_LAYERS; zLayer++)
    {
        uiContext->renderGroups[0].RenderCommands[zLayer] = ls_stackInit(sizeof(RenderCommand), 256);
    }
#else
    AssertMsg(FALSE, "Missing backend...");
#endif

#if _DEBUG
    const u32 fwMemSize    = sizeof(char)*4096;
    char *fwBackingMemory  = (char*)ls_alloc(fwMemSize);
    uiContext->fileWatcher = ls_fwCreateFileWatcher(fwBackingMemory, fwMemSize);
#endif
    
    //------------------------------------------------------
    //NOTE: This shit is necessary to request millisecond-precision sleeps.
    //      An equivalent call to timeEndPeriod should happen at the end. It technically
    //      Doesn't in this program, because we use it every frame, so we don't re-call it.
    //      But I'm pointing it out for possible microsoft weirdness...
    TIMECAPS tc = {};
    MMRESULT res = timeGetDevCaps(&tc, sizeof(TIMECAPS));
    res = timeBeginPeriod(tc.wPeriodMin);
    
    AssertMsg(res == TIMERR_NOERROR, "High Resolution Timer Init Failed");
    //------------------------------------------------------
    
    //NOTETODO: Should this be here? Should we have another function 
    //          that specifically takes care of initialization of these global things??
    windows_initRegionTimer();
    
    //NOTE: Just reminding myself of this function's existance
    //      It should be called at the end of the usage. but we use it always.
    //res = timeEndPeriod(tc.wPeriodMin);
    return uiContext;
}

UIContext *ls_uiInitDefaultContext(s32 contextArenaSize, s32 frameArenaSize, s32 widgetArenaSize,
                                   RenderCallback cb = __ui_default_windows_render_callback)
{
    Arena contextArena = ls_arenaCreate(contextArenaSize, (char*)"contextArena");
    Arena frameArena   = ls_arenaCreate(frameArenaSize, (char*)"frameArena");
    Arena widgetArena  = ls_arenaCreate(widgetArenaSize, (char*)"widgetArena");
    return ls_uiInitDefaultContext(contextArena, frameArena, widgetArena, cb);
}

void ls_uiStartFrameTimer(UIContext *c)
{
    RegionTimerBegin(c->frameTime);
}

void ls_uiEndFrameTimer(UIContext *c, u64 frameTimeTargetMs)
{
    static u32 lastFrameTime = 0;
    
#ifdef _DEBUG
    __debug_frameNumber += 1;
#endif
    
    RegionTimerEnd(c->frameTime);
    u32 frameTimeMs = RegionTimerGet(c->frameTime);
    if(frameTimeMs < frameTimeTargetMs)
    {
        u32 deltaTimeInMs = frameTimeTargetMs - frameTimeMs;
        Sleep(deltaTimeInMs);
    }
    
    RegionTimerEnd(c->frameTime);
    c->dt = RegionTimerGet(c->frameTime);
    lastFrameTime = c->dt;
}

void ls_uiFrameBegin(UIContext *c, UIWindow *win)
{
    ls_arenaUse(c->frameArena);
    
    // Set current window on the UIContext
    c->currWindow = win;
    c->mustRender = false;

#ifdef LS_UI_OPENGL_BACKEND
    wglMakeCurrent(win->WindowDC, c->OGLContext);
    RECT r1;
    GetClientRect(win->Window, &r1);
    glViewport(0, 0, r1.right-r1.left, r1.bottom - r1.top);
#endif

    win->UserInput.Keyboard.prevState       = win->UserInput.Keyboard.currentState;
    win->UserInput.Keyboard.repeatState     = {};
    win->UserInput.Keyboard.hasPrintableKey = FALSE;
    win->UserInput.Keyboard.keyCodepoint    = 0;
    
    win->UserInput.Mouse.prevPosX           = win->UserInput.Mouse.currPosX;
    win->UserInput.Mouse.prevPosY           = win->UserInput.Mouse.currPosY;
    win->UserInput.Mouse.wasLeftPressed     = win->UserInput.Mouse.isLeftPressed;
    win->UserInput.Mouse.wasRightPressed    = win->UserInput.Mouse.isRightPressed;
    win->UserInput.Mouse.wasMiddlePressed   = win->UserInput.Mouse.isMiddlePressed;
    win->UserInput.Mouse.isWheelRotated     = FALSE;
    
    //NOTETODO: Is it possible to at the same time setting the focus this frame, and 
    //          Having a pending request for a focus change, thus executing both this and the 
    //          next if block?
    //
    //TODO: Will this create problems in multi-window applications??
    if(!win->focusWasSetThisFrame) { win->lastFocus = win->currentFocus; }
    
    win->focusWasSetThisFrame = FALSE;
    if(win->nextFrameFocusChange == TRUE)
    {
        win->lastFocus            = win->currentFocus;
        win->currentFocus         = win->nextFrameFocus;
        win->nextFrameFocusChange = FALSE;
    }
    
    if(win->lastFocus && win->currentFocus != win->lastFocus)
    {
        DummyUIWidgetBase *base = (DummyUIWidgetBase *)win->lastFocus;
        if(base->OnFocusLost) {
            base->OnFocusLost(c, base->onFocusLostData);
        }
    }
    
    win->hasReceivedInput = FALSE;
    
    // Process Input
    MSG Msg;
    while (PeekMessageA(&Msg, win->Window, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&Msg);
        DispatchMessageA(&Msg);
    }

    // Reset the scissor at the beginning of every frame
    // This is placed after the MessageLoop, to ensure we are not a frame late with resizing
    // TODO: Make scissor a stack where you can push stuff onto and pop them
    // to make it easier, and stop passing the scissor around since it's part of the context?
    c->scissor = {0, 0, win->width, win->height};
    
    //NOTE: Make sure previous frame click is not put on hold this frame.
    if(win->UserInput.Mouse.wasLeftPressed  ||
       win->UserInput.Mouse.wasRightPressed || 
       win->UserInput.Mouse.wasMiddlePressed)
    { win->hasReceivedInput = TRUE; }
    
    Input *UserInput = &win->UserInput;
    //NOTE: Right-Alt Drag, only when nothing is in focus
    if(KeyHeld(keyMap::RAlt) && LeftClick && win->currentFocus == 0)
    { 
        win->isDragging = TRUE;
        POINT currMouse = {};
        GetCursorPos(&currMouse);
        win->prevMousePosX = currMouse.x;
        win->prevMousePosY = currMouse.y;
    }
    
    //NOTE: Handle Dragging
    if(win->isDragging && LeftHold)
    { 
        MouseInput *Mouse = &win->UserInput.Mouse;
        
        POINT currMouse = {};
        GetCursorPos(&currMouse);
        
        POINT prevMouse = { win->prevMousePosX, win->prevMousePosY };
        
        SHORT newX = prevMouse.x - currMouse.x;
        SHORT newY = prevMouse.y - currMouse.y;
        
        SHORT newWinX = win->windowPosX - newX;
        SHORT newWinY = win->windowPosY - newY;
        
        win->windowPosX = newWinX;
        win->windowPosY = newWinY;
        
        win->prevMousePosX  = currMouse.x;
        win->prevMousePosY  = currMouse.y;
        
        SetWindowPos(win->Window, 0, newWinX, newWinY, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
    }
    
    if(win->isDragging && LeftUp) { win->isDragging = FALSE; }
    
    if(LeftUp || RightUp || MiddleUp) { win->mouseCapture = 0; }
    
#ifdef LS_UI_OPENGL_BACKEND
    f64 rLinear = ((f64)c->backgroundColor.r / 255.0);
    f64 gLinear = ((f64)c->backgroundColor.g / 255.0);
    f64 bLinear = ((f64)c->backgroundColor.b / 255.0);
    f64 aLinear = ((f64)c->backgroundColor.a / 255.0);
    
    glClearColor(rLinear, gLinear, bLinear, aLinear);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#ifdef _DEBUG
    FW_WatchedFile *changedFile = 0;
    while(changedFile = ls_fwIterNext(&c->fileWatcher)) {
        if (changedFile->onCallResult) {
            ls_log("Reloaded Shader: {char*}", changedFile->fileName);
            c->mustRender = true;
        }
    }
#endif //_DEBUG

#endif //LS_UI_OPENGL_BACKEND
}

void ls_uiFrameEnd(UIContext *c)
{
    ls_arenaClear(c->frameArena);
    
    UIWindow *win = c->currWindow;
    Input *UserInput = &win->UserInput;
    //NOTE: If user clicked somewhere, but nothing set the focus, then we should reset the focus
    if(LeftClick && !win->focusWasSetThisFrame)
    { ls_uiFocusChange(c, 0); }
}


inline void ls_uiAddOnDestroyCallback(UIContext *c, onDestroyFunc f)
{ c->onDestroy = f; }

void ls_uiFocusChangeSameFrame(UIContext *c, u64 *focus)
{
    UIWindow *win             = c->currWindow;
    win->lastFocus            = win->currentFocus;
    win->currentFocus         = focus;
    win->focusWasSetThisFrame = TRUE;
}

void ls_uiFocusChange(UIContext *c, u64 *focus)
{
    UIWindow *win             = c->currWindow;
    win->nextFrameFocusChange = TRUE;
    win->nextFrameFocus       = focus;
}

b32 ls_uiInFocus(UIContext *c, void *p)
{
    if(c->currWindow->currentFocus == (u64 *)p) { return TRUE; }
    return FALSE;
}

b32 ls_uiHasCapture(UIContext *c, void *p)
{
    if(c->currWindow->mouseCapture == (u64 *)p) { return TRUE; }
    return FALSE;
}

//TODO @UIPos
void ls_uiStartScrollableRegion(UIContext *c, UIScrollableRegion *scroll)
{ 
    AssertMsg(c->scroll == NULL, "Starting a scrollable region inside a scrollable region is invalid\n");
    AssertMsg(scroll, "Invalid Scrollable Region\n");
    
    Input *UserInput = &c->currWindow->UserInput;
    
    if(LeftUp) { scroll->isHeld = FALSE; }
    
    //NOTE: Calculate current scrollbar position
    s32 scrollBarH    = 30;
    s32 usableHeight  = scroll->h - 4 - scrollBarH;
    s32 totalHeight   = scroll->y - scroll->minY;
    
    s32 scrollBarYOff = ((f32)-scroll->deltaY / (f32)totalHeight) * usableHeight;
    s32 scrollBarY    = (scroll->y + scroll->h - 4) - scrollBarYOff - scrollBarH;
    s32 scrollBarX    = scroll->x + scroll->w - 14;
    
    //TODO: Do mouse capture like in the slider??
    if(MouseInRect(scrollBarX, scrollBarY, 12, scrollBarH))
    {
        if(LeftHold) { scroll->isHeld = TRUE; }
    }
    
    s32 deltaY = 0;
    if(!scroll->isHeld && WheelRotatedIn(scroll->x, scroll->y, scroll->w, scroll->h))
    { 
        deltaY += WheelDeltaInPixels;
    }
    else if(scroll->isHeld)
    {
        s32 mouseDeltaY = (UserInput->Mouse.prevPosY - UserInput->Mouse.currPosY);
        s32 scaledDeltaY = (s32)(((f64)mouseDeltaY / (f64)scroll->h)*(f64)totalHeight);
        
        deltaY = -scaledDeltaY;
    }
    
    scroll->deltaY += deltaY;
    if(scroll->deltaY < -totalHeight) { scroll->deltaY = -totalHeight; }
    else if(scroll->deltaY > 0)       { scroll->deltaY = 0; }
    
    c->scroll    = scroll;
    c->scissor   = UIRect { scroll->x, scroll->y, scroll->w, scroll->h-2 };
    
    RenderCommand command = { UI_RC_SCROLLBAR, scroll->x, scroll->y, scroll->w, scroll->h };
    command.scroll        = *scroll;
    ls_uiPushRenderCommand(c, command, 0);
}

void ls_uiEndScrollableRegion(UIContext *c)
{ 
    c->scroll  = NULL;
    c->scissor = UIRect { 0, 0, s32(c->currWindow->width), s32(c->currWindow->height) };
}

void ls_uiResetScrollableRegion(UIContext *c)
{
    AssertMsg(c->scroll, "Null scroll pointer in UIContext\n");
    AssertMsg(c, "Null context pointer\n");
    
    c->scroll->deltaX = 0;
    c->scroll->deltaY = 0;
    c->scroll->minY   = 0;
    //TODO: scroll->maxX?
}

#if 0

//NOTETODO: Not using the command system. Basically broken.
void _ls_uiLPane(UIContext *c, UILPane *pane, s32 xPos, s32 yPos, s32 w, s32 h)
{
    if(pane->isOpen)
    {
        s32 xArrowPos  = xPos + w - 1;
        s32 arrowWidth = 16;
        
        s32 arrowHeight = 14;
        s32 yArrowPos   = yPos + h - arrowHeight;
        
        //TODO: Fix Left Pane Arrow Color
        ls_uiDrawArrow(c, xArrowPos, yArrowPos, arrowWidth, arrowHeight, c->widgetColor, UIA_LEFT);
        
        if(LeftClickIn(xArrowPos, yArrowPos, arrowWidth, arrowHeight))
        { pane->isOpen = FALSE; }
        
        ls_uiBorderedRect(c, xPos-1, yPos, w, h, c->widgetColor);
    }
    else
    {
        s32 width = 0;
        if(pane->isOpening)
        {
            pane->dtOpen += c->dt;
            
            s32 maxDT = 120;
            f64 dtFract = (f64)pane->dtOpen / maxDT;
            width = w*dtFract;
            
            if(pane->dtOpen >= maxDT) { 
                pane->isOpen = TRUE; pane->isOpening = FALSE; pane->dtOpen = 0;
                ls_uiBorderedRect(c, xPos-1, yPos, w, h, c->widgetColor);
            }
            
            if(!pane->isOpen) { ls_uiBorderedRect(c, xPos-1, yPos, width, h, c->widgetColor); }
        }
        
        s32 xArrowPos  = xPos + width;
        s32 arrowWidth = 16;
        
        s32 arrowHeight = 14;
        s32 yArrowPos   = yPos + h - arrowHeight;
        
        ls_uiDrawArrow(c, xArrowPos, yArrowPos, arrowWidth, arrowHeight, c->widgetColor, UIA_RIGHT);
        
        if(LeftClickIn(xArrowPos, yArrowPos, arrowWidth, arrowHeight))
        { pane->isOpening = TRUE; }
    }
}
#endif


#if _DEBUG
static b32 __ui_shouldTag = FALSE;
#endif

#ifndef LS_UI_OPENGL_BACKEND

void ls_uiPushRenderCommand(UIContext *c, RenderCommand command, s32 zLayer)
{
    AssertMsg(command.type != UI_RC_INVALID,  "Uninitialized Render Command?\n");
    AssertMsg(zLayer < UI_Z_LAYERS, "zLayer is invalid. A function call did an oopsie\n");
    
#if _DEBUG
    command.UID = RenderCommandUID++;
#endif
    
    command.selectedFont = c->currFont;
    command.pixelHeight  = c->currPixelHeight;
    command.scissor      = c->scissor;

    //TODO @UIPos
    if ((command.pos.iw != 0) && (command.pos.ih != 0)) {
        UIPos p = TEMPORARY_REMOVE_TO_ABS(c->currWindow->width, c->currWindow->height, command.pos);
        command.rect = {p.ix, p.iy, p.iw, p.ih};
    }
    
    //NOTE: Normalize the scrolled coordinates, and replace them in the render command.
    if(c->scroll && command.type != UI_RC_SCROLLBAR)
    {
        command.rect.x -= c->scroll->deltaX;
        command.rect.y -= c->scroll->deltaY;
        
        command.layout.startY -= c->scroll->deltaY;
        command.layout.startX -= c->scroll->deltaX;
    }
    
    UIRect commandRect = command.rect;
    
    //NOTETODO: Stupid hack correction.
    //          Because strings grow downward when creating a layout, and render commands expect objects
    //          to grow upward, the base Y and height are basically flipped.
    //          BUT ONLY FOR CHECKS AGAINST THREAD RECTS!
    if(command.type == UI_RC_LABEL_LAYOUT)
    {
        s32 fontHeight = command.selectedFont->pixelHeight;
        command.rect.y = command.rect.y + fontHeight;
    }
    
    //TODO: The difference between how the command rect and the thread rect's members are used is confusing
    //      and error prone. One uses x,y,w,h. The other uses minX,minY,maxX,maxY. @ConfusingUnion
    //      Should probably have 2 different types:
    //      UIRect       should use (x,y,w,h)
    //      UIRectRange? should use (minX,minY,maxX,maxY)
    auto ls_uiRectIsInside = [](UIRect r1, UIRect check) -> b32 {
        if((r1.x >= check.minX) && ((r1.x + r1.w) <= (check.maxX)))
        {
            if((r1.y >= check.minY) && ((r1.y + r1.h) <= (check.maxY)))
            {
                return TRUE;
            }
        }
        
        return FALSE;
    };
    
    auto ls_uiRectIntersects = [](UIRect r1, UIRect check) -> b32 {
        s32 x0 = r1.x;
        s32 x1 = r1.x + r1.w;
        s32 y0 = r1.y;
        s32 y1 = r1.y + r1.h;
        
        b32 cond = (x1 < check.minX || y1 < check.minY || x0 > (check.maxX) || y0 > (check.maxY));
        return !cond;
    };
    
    //NOTE: All Thread Rects are inclusive on the left/bot, exclusive on the right/top
    UIRect *renderUIRects = c->currWindow->renderUIRects;
    switch(__LS_UI_THREAD_COUNT)
    {
        case 0:
        case 1:
        {
            command.threadRect = renderUIRects[0];
            
            stack *renderStack = &c->renderGroups[0].RenderCommands[zLayer];
            AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 0\n");
            
            ls_stackPush(renderStack, (void *)&command);
            return;
        } break;
        
        case 2:
        case 4:
        case 8:
        {
            for(s32 i = 0; i < __LS_UI_THREAD_COUNT; i++)
            {
                if(ls_uiRectIntersects(commandRect, renderUIRects[i]))
                {
                    command.threadRect = renderUIRects[i];
                    stack *renderStack = &c->renderGroups[i].RenderCommands[zLayer];
                    AssertMsgF(renderStack->used < renderStack->capacity, "Out of space in RenderGroup %d\n", i);
                    ls_stackPush(renderStack, (void *)&command);
                }
            }
            
            return;
            
        } break;
        
        default: { AssertMsg(FALSE, "Thread count not supported\n"); } return;
    }
    
    AssertMsg(FALSE, "Should never reach this case!\n");
}
#else
void ls_uiPushRenderCommand(UIContext *c, RenderCommand command, s32 zLayer)
{
    AssertMsg(command.type != UI_RC_INVALID,  "Uninitialized Render Command?\n");
    
    //UIRect threadRect       = command.threadRect;
    //UIRect scissor          = command.scissor;
    Color bkgColor          = command.bkgColor;
    Color borderColor       = command.borderColor;
    Color textColor         = command.textColor;
    
    command.selectedFont    = c->currFont;
    command.pixelHeight     = c->currPixelHeight;

    //TODO @UIPos
    if ((command.pos.iw != 0) && (command.pos.ih != 0)) {
        UIPos p = TEMPORARY_REMOVE_TO_ABS(c->currWindow->width, c->currWindow->height, command.pos);
        command.rect = {p.ix, p.iy, p.iw, p.ih};
    }
    
    //NOTE: Normalize the scrolled coordinates, and replace them in the render command.
    if(c->scroll && command.type != UI_RC_SCROLLBAR)
    {
        command.rect.x -= c->scroll->deltaX;
        command.rect.y -= c->scroll->deltaY;
        
        command.layout.startY -= c->scroll->deltaY;
        command.layout.startX -= c->scroll->deltaX;
    }

    stack *renderStack = &c->renderGroups[0].RenderCommands[zLayer];
    AssertMsgF(renderStack->used < renderStack->capacity, "Out of space in RenderGroup %d\n", 0);
    ls_stackPush(renderStack, (void *)&command);
    
    return;
}
#endif

void ls_uiRender(UIContext *c)
{
#ifndef LS_UI_OPENGL_BACKEND
    AssertMsg(c->currWindow != NULL, "Cannot call render when no window is selected!");
    AssertMsg(c->currWindow->drawBuffer != NULL, "Trying to Call ls_uiRender on a Fake UIContext "
              "which doesn't have a draw buffer allocated!\n");
#endif

    if(__LS_UI_THREAD_COUNT < 2)
    {
        ls_uiRender__(c, 0);
        c->renderFunc(c);
        return;
    }
    
#ifndef LS_UI_OPENGL_BACKEND
    WakeAllConditionVariable(&c->startRender);
    
    volatile b32 areAllDone = FALSE;
    while(areAllDone == FALSE)
    {
        volatile b32 allDone = TRUE;
        for(u32 i = 0; i < __LS_UI_THREAD_COUNT; i++)
        {
            allDone = allDone && c->renderGroups[i].isDone;
        }
        
        areAllDone = allDone;
    }
    
    for(u32 i = 0; i < __LS_UI_THREAD_COUNT; i++)
    {
        c->renderGroups[i].isDone = FALSE;
    }
#endif
    
    c->renderFunc(c);
}

void ls_uiRenderSingleCommand(UIContext *c, RenderCommand *curr)
{
    s32 xPos                = curr->rect.x;
    s32 yPos                = curr->rect.y;
    s32 w                   = curr->rect.w;
    s32 h                   = curr->rect.h;
    
    UIRect threadRect       = curr->threadRect;
    UIRect scissor          = curr->scissor;
    Color bkgColor          = curr->bkgColor;
    Color borderColor       = curr->borderColor;
    Color textColor         = curr->textColor;
    
    UIFont *font            = curr->selectedFont;
    
    s32 pixelHeight         = curr->pixelHeight;
    
#if _DEBUG
    c->isTagged = curr->isTagged;
#endif
    
    switch(curr->type)
    {
        case UI_RC_LABEL8:
        {
            s32 yBaseOff = h - pixelHeight;
            ls_uiGlyphString(c, font, pixelHeight, xPos, yPos + yBaseOff, threadRect, scissor, curr->label8, textColor);
        } break;
        
        case UI_RC_LABEL32:
        {
            s32 yBaseOff = h - pixelHeight;
            ls_uiGlyphString(c, font, pixelHeight, xPos, yPos + yBaseOff, threadRect, scissor, curr->label32, textColor);
        } break;
        
        case UI_RC_LABEL_LAYOUT:
        {
            ls_uiGlyphStringInLayout(c, font, curr->layout, threadRect, scissor, curr->label32, textColor);
        } break;
        
        case UI_RC_TEXTBOX:
        {
            ls_uiBorderedRect(c, xPos, yPos, w, h, threadRect, scissor, bkgColor);
            
            UITextBox *box = curr->textBox;
            
            Color caretColor = textColor;
            const s32 horzOff = 4;
            
            s32 strX = xPos + horzOff;
            s32 strY = yPos + h - pixelHeight;
            
            
            ls_uiRenderStringOnRect(c, font, box, pixelHeight, strX, strY, w, h, threadRect, scissor, textColor, c->invTextColor);
        } break;
        
        case UI_RC_LISTBOX:
        {
            UIListBox *list = curr->listBox;
            
            s32 h = curr->layout.minY;
            s32 maxHeight = curr->rect.h;
            s32 origY     = yPos+maxHeight-h;
            
            ls_uiBorderedRect(c, xPos, origY, w, h, threadRect, scissor);
            
            s32 strHeight = pixelHeight; 
            s32 vertOff = ((h - strHeight) / 2) + 4; //TODO: @FontDescent
            
            if(list->list.count)
            {
                utf32 selected = list->list[list->selectedIndex].name;
                ls_uiGlyphString(c, font, pixelHeight, xPos+10, origY + vertOff, threadRect, scissor, selected, c->textColor);
            }
            
            if(list->isOpening)
            {
                s32 height = 0;
                if(list->dtOpen > 17)  { height = maxHeight*0.10f; }
                if(list->dtOpen > 34)  { height = maxHeight*0.35f; }
                if(list->dtOpen > 52)  { height = maxHeight*0.70f; }
                
                if(!list->isOpen)
                { ls_uiFillRect(c, xPos+1, origY - height, w-2, height,
                                threadRect, scissor, c->widgetColor); }
            }
            
            if(list->isOpen)
            {
                for(u32 i = 0; i < list->list.count; i++)
                {
                    s32 currY = origY - (h*(i+1));
                    UIListBoxItem *currItem = list->list + i;
                    
                    ls_uiRect(c, xPos+1, currY, w-2, h, threadRect, scissor, currItem->bkgColor);
                    ls_uiGlyphString(c, font, pixelHeight, xPos+10, origY + vertOff - (h*(i+1)),
                                     threadRect, scissor, currItem->name, currItem->textColor);
                }
                
                ls_uiBorder(c, xPos, yPos, w, maxHeight, threadRect, scissor);
            }
            
        } break;
        
        //TODO: Why is this a separate command?
        case UI_RC_LISTBOX_ARR:
        {
            ls_uiDrawArrow(c, xPos, yPos, w, h,
                           threadRect, scissor, curr->listBox->arrowBkg, UIA_DOWN);
        } break;
        
        case UI_RC_BUTTON:
        {
            UIButton *button = curr->button;
            
            if(button->style == UIBUTTON_CLASSIC)
            {
                ls_uiBorderedRect(c, xPos, yPos, w, h, threadRect, scissor, bkgColor, borderColor);
                
                if(button->name.data)
                {
                    s32 strHeight = pixelHeight;
                    s32 strWidth  = ls_uiGlyphStringRect(c, font, button->name, pixelHeight).w;
                    s32 xOff      = (w - strWidth) / 2; //TODO: What happens when the string is too long?
                    s32 yOff      = strHeight*0.25; //TODO: @FontDescent
                    
                    ls_uiGlyphString(c, font, pixelHeight, xPos+xOff, yPos+yOff, threadRect, scissor, 
                                     button->name, textColor);
                }
            }
            else if(button->style == UIBUTTON_LINK)
            {
                if(button->name.data)
                {
                    s32 strHeight = pixelHeight;
                    s32 strWidth  = ls_uiGlyphStringRect(c, font, button->name, pixelHeight).w;
                    s32 xOff      = (w - strWidth) / 2; //TODO: What happens when the string is too long?
                    s32 yOff      = strHeight*0.25; //TODO: @FontDescent
                    
                    ls_uiGlyphString(c, font, pixelHeight, xPos+xOff, yPos+yOff, threadRect, scissor,
                                     button->name, textColor);
                }
            }
            else if(button->style == UIBUTTON_TEXT_NOBORDER)
            {
                ls_uiRect(c, xPos, yPos, w, h, threadRect, scissor, bkgColor);
                
                if(button->name.data)
                {
                    s32 strHeight = pixelHeight;
                    s32 strWidth  = ls_uiGlyphStringRect(c, font, button->name, pixelHeight).w;
                    s32 xOff      = (w - strWidth) / 2; //TODO: What happens when the string is too long?
                    s32 yOff      = strHeight*0.25; //TODO: @FontDescent
                    
                    ls_uiGlyphString(c, font, pixelHeight, xPos+xOff, yPos+yOff, threadRect, scissor, 
                                     button->name, textColor);
                }
            }
            else if(button->style == UIBUTTON_NO_TEXT)
            {
                ls_uiRect(c, xPos, yPos, w, h, threadRect, scissor, bkgColor);
            }
            else if(button->style == UIBUTTON_BMP)
            {
                UIBitmap bmp = button->bmp;
                ls_uiStretchBitmap(c, &bmp, {xPos, yPos, bmp.w, bmp.h}, threadRect, scissor);
            }
            else { AssertMsg(FALSE, "Unhandled button style\n"); }
            
        } break;
        
        case UI_RC_CHECK:
        {
            UICheck *check = curr->check;
            
            if(check->style == UICHECK_BMP)
            {
                if(check->bmpActive.data && check->bmpInactive.data)
                {
                    UIBitmap chosen = check->isActive ? check->bmpActive : check->bmpInactive;
                    ls_uiStretchBitmap(c, &chosen, {xPos, yPos, chosen.w, chosen.h}, threadRect, scissor);
                }
                else if(check->bmpInactive.data && check->bmpAdditive.data)
                {
                    s32 addX = xPos;
                    s32 addY = yPos;
                    s32 addW = check->bmpAdditive.w;
                    s32 addH = check->bmpAdditive.h;
                    s32 inW  = check->bmpInactive.w;
                    s32 inH  = check->bmpInactive.h;

                    ls_uiStretchBitmap(c, &check->bmpInactive, {xPos, yPos, inW, inH}, threadRect, scissor);
                    if(check->isActive)
                    {
                        
                        if(addW > inW) { addX -= (addW - inW) / 2; }
                        if(addH > inH) { addY -= (addH - inH) / 2; }
                        
                        ls_uiStretchBitmap(c, &check->bmpAdditive, {addX, addY, addW, addH}, threadRect, scissor);
                    }
                }
                else { AssertMsg(FALSE, "Unhandled check bmp collection\n"); }
            }
            else { AssertMsg(FALSE, "Unhandled check style\n"); }
            
        } break;
        
        case UI_RC_SLIDER:
        {
            //TODO: There seems to be a rendering bug in here. the top right square of pixels
            //      in the colored slider area seem to not be properly colored.
            
            UISlider *slider = curr->slider;
            
            //NOTE: Box Slider Branchless Opacity Check
            //u8 opacity = 0xEE - (0xB0*slider->isHeld);
            u8 opacity = 0xC0 - (0xB0*slider->isHeld);
            
            if(slider->style == SL_BOX)
            {
                s32 slideWidth = 3;
                
                //NOTE: Not necessary. The border is drawn anyway later to display text. 
                //ls_uiBorder(c, xPos, yPos, w, h, threadRect,);
                
                s32 slidePos = w*slider->currPos;
                s32 lColorW = slidePos == w ? slidePos-2 : slidePos;
                s32 rColorW = w-slidePos-2;
                
                ls_uiFillRect(c, xPos+1, yPos+1, lColorW, h-2, threadRect, scissor, slider->lColor);
                ls_uiFillRect(c, xPos+slidePos+1, yPos+1, rColorW, h-2, threadRect, scissor, slider->rColor);
                
                u32 valBuf[32] = {};
                utf32 val = { valBuf, 0, 32};
                ls_utf32FromInt_t(&val, slider->currValue);
                
                s32 strHeight = pixelHeight;
                
                u32 textLen = ls_uiGlyphStringRect(c, font, val, pixelHeight).w;
                s32 strXPos = xPos + slidePos - textLen - 2;
                Color textBkgC = slider->lColor;
                
                if(strXPos < xPos+1) { strXPos = xPos + slidePos + slideWidth + 2; textBkgC = slider->rColor; }
                
                Color valueColor = c->borderColor;
                u8 alpha = 0x00 + (slider->isHeld*0xFF);
                valueColor = SetAlpha(valueColor, alpha);
                ls_uiGlyphString(c, font, pixelHeight, strXPos, yPos + h - strHeight, threadRect, scissor, val, valueColor);
                
                if(slider->isHot)
                {
                    s32 actualX = (xPos + slidePos) - 1;
                    s32 actualY = yPos - 2;
                    
                    s32 actualW = slideWidth+2;
                    s32 actualH = 4 + h;
                    
                    ls_uiFillRect(c, actualX, actualY, actualW, actualH, threadRect, scissor, c->borderColor);
                }
                else
                { ls_uiFillRect(c, xPos+slidePos, yPos, slideWidth, h, threadRect, scissor, c->borderColor); }
                
                //NOTE: Draw the displayed text, and hide through Alpha the slider info.
                Color rectColor = c->widgetColor;
                rectColor = SetAlpha(rectColor, opacity);
                
                ls_uiBorderedRect(c, xPos, yPos, w, h, threadRect, scissor, rectColor, borderColor);
                
                s32 strWidth  = ls_uiGlyphStringRect(c, font, slider->text, pixelHeight).w;
                s32 xOff      = (w - strWidth) / 2;
                s32 yOff      = (h - strHeight) + 3; //TODO: @FontDescent
                
                Color textColor = c->textColor;
                textColor = SetAlpha(textColor, opacity);
                
                ls_uiGlyphString(c, font, pixelHeight, xPos+xOff, yPos + yOff, threadRect, scissor,
                                 slider->text, textColor);
            }
            else if(slider->style == SL_LINE)
            { AssertMsg(FALSE, "Slider style line is not implemented\n"); }
            
        } break;
        
        case UI_RC_MENU:
        {
            UIMenu *menu = curr->menu;
            ls_uiBorderedRect(c, xPos, yPos, w+1, h, threadRect, scissor, bkgColor, c->widgetColor);
            
            s32 subY = yPos;
            s32 subW = menu->itemWidth;
            s32 subH = h;
            
            for(u32 subIdx = 0; subIdx < menu->subMenus.count; subIdx++)
            {
                UISubMenu *sub = menu->subMenus + subIdx;
                
                s32 subX = xPos + (subIdx*menu->itemWidth);
                
                s32 strWidth = ls_uiGlyphStringRect(c, font, sub->name, pixelHeight).w;
                s32 xOff = (subW - strWidth) / 2;
                s32 yOff = 5;
                
                Color subColor = sub->isHot ? c->highliteColor : bkgColor;
                ls_uiBorderedRect(c, subX, subY, subW, subH, threadRect, scissor, subColor, c->widgetColor);
                ls_uiGlyphString(c, font, pixelHeight, subX+xOff, subY+yOff, threadRect, scissor, sub->name, textColor);
                
                if(menu->isOpen && (menu->openIdx == subIdx))
                {
                    u32 openSubHeight = subH*sub->items.count;
                    ls_uiBorderedRect(c, subX, subY-openSubHeight, subW, openSubHeight+1,
                                      threadRect, scissor, bkgColor, c->widgetColor);
                    
                    u32 currY = subY-subH;
                    for(u32 itemIdx = 0; itemIdx < sub->items.count; itemIdx++)
                    {
                        UIMenuItem *item = sub->items + itemIdx;
                        
                        strWidth = ls_uiGlyphStringRect(c, font, item->name, pixelHeight).w;
                        xOff = (subW - strWidth) / 2;
                        
                        if(item->isVisible) {
                            if(item->isHot) {
                                ls_uiRect(c, subX, currY, subW, subH, threadRect, scissor, c->highliteColor);
                            }
                        }
                        else
                        {
                            Color bkgColor = ls_uiAlphaBlend(c->widgetColor, RGBg(0xAA));
                            ls_uiRect(c, subX, currY, subW, subH, threadRect, scissor, bkgColor);
                        }
                        
                        ls_uiGlyphString(c, font, pixelHeight, subX+xOff, currY+yOff, threadRect, scissor,
                                         item->name, c->textColor);
                        
                        currY -= subH;
                    }
                }
            }
            
            
            for(u32 itemIdx = 0; itemIdx < menu->items.count; itemIdx++)
            {
                UIMenuItem *item = menu->items + itemIdx;
                
                s32 realIndex = itemIdx + menu->subMenus.count;
                s32 itemX = xPos + (realIndex*menu->itemWidth);
                
                s32 strWidth = ls_uiGlyphStringRect(c, font, item->name, pixelHeight).w;
                s32 xOff = (subW - strWidth) / 2;
                s32 yOff = 5;
                
                Color itemColor = item->isHot ? c->highliteColor : bkgColor;
                ls_uiBorderedRect(c, itemX, subY, subW, subH,
                                  threadRect, scissor, itemColor, c->widgetColor);
                
                ls_uiGlyphString(c, font, pixelHeight, itemX+xOff, subY+yOff, threadRect, scissor,
                                 item->name, c->textColor);
            }
            
        } break;
        
        case UI_RC_RECT:
        {
            ls_uiBorderedRect(c, xPos, yPos, w, h, threadRect, scissor, bkgColor, borderColor);
        } break;
        
        case UI_RC_SEPARATOR:
        {
            ls_uiFillRect(c, xPos, yPos, w, h, threadRect, scissor, borderColor);
        } break;
        
        case UI_RC_SCROLLBAR:
        {
            //TODO: Differentiate between horizontal and vertical scrollbars
            s32 scrollRectX = xPos + w - 16;
            ls_uiBorderedRect(c, scrollRectX, yPos, 16, h-1, threadRect, scissor);
            
            //NOTE: Calculate current scrollbar position
            s32 scrollBarH   = 30;
            s32 usableHeight = h - 4 - scrollBarH;
            s32 totalHeight  = curr->scroll.y - curr->scroll.minY;
            
            s32 scrollBarYOff = ((f32)-curr->scroll.deltaY / (f32)totalHeight) * usableHeight;
            s32 scrollBarY    = (yPos + h - 4) - scrollBarYOff - scrollBarH;
            
            if(scrollBarY < yPos+2)                  { scrollBarY = yPos+2; }
            if(scrollBarY > yPos+h-2-scrollBarH)     { scrollBarY = yPos+h-2-scrollBarH; }
            
            ls_uiFillRect(c, scrollRectX+2, scrollBarY, 12, scrollBarH,
                          threadRect, scissor, c->borderColor);
        } break;
        
        case UI_RC_TEXTURED_RECT:
        {
            ls_uiStretchBitmap(c, &curr->bitmap, curr->rect, threadRect, scissor);
        } break;
        
        case UI_RC_COLOR_PICKER:
        {
            UIColorPicker *picker = curr->colorPicker;
            
            ls_uiBorderedRect(c, xPos, yPos, w, h, threadRect, scissor);
            
            ls_uiFillColorWheel(c, picker->centerX, picker->centerY, 
                                picker->radius, picker->value, threadRect, scissor);
            
            ls_uiColorValueRect(c, picker->valueRectX, picker->valueRectY, 
                                picker->valueRectW, picker->valueRectH, threadRect, scissor);
            
            //NOTE: Create a visible white rectangle around the selected value
            ls_uiBorder(c, picker->valueRectX, picker->valueRectY + (picker->valueRectH*picker->value) - 4, picker->valueRectW, 8, threadRect, scissor, RGBg(0xFF));
            
            if(picker->hasPicked == TRUE)
            {
                s32 cX = picker->pickedX - picker->centerX;
                s32 cY = picker->pickedY - picker->centerY;
                
                f32 saturation = ls_sqrt(cX*cX + cY*cY) / (f32)picker->radius;
                saturation     = ls_clamp(saturation*1.00f, 1.0f, 0.0f);
                
                f32 angle = ls_atan2((f32)cY, (f32)cX) / PI;
                s32 hue   = (angle*180) + 179;
                
                picker->pickedColor = ls_uiHSVtoRGB(hue, saturation, picker->value);
                
                //NOTE: Draw a small circle around the selected color
                ls_uiDrawCircle(c, picker->pickedX, picker->pickedY, 
                            picker->radius*0.1f+2, 2, threadRect, scissor, RGBg(0x0));
                ls_uiDrawCircle(c, picker->pickedX, picker->pickedY, 
                            picker->radius*0.1f, 2, threadRect, scissor, RGBg(0xFF));
                
                
                //NOTE: Add RGB Label
                s32 xMargin = w*0.15f;
                s32 yMargin = h*0.07f;
                s32 rgbX    = picker->centerX - picker->radius;
                s32 rgbY    = picker->centerY - picker->radius - yMargin;
                
                ls_uiGlyphString(c, font, pixelHeight, rgbX, rgbY, threadRect, scissor,
                                 ls_utf32Constant(U"RGB"), textColor);
                
                
                u32 numberBuff[32] = {};
                utf32 tmp = { numberBuff, 0, 32 };
                
                rgbX += xMargin;// + ls_uiGlyphStringLen(c, font, ls_utf32Constant(U"RGB"));
                ls_utf32FromInt_t(&tmp, picker->pickedColor.r);
                ls_uiGlyphString(c, font, pixelHeight, rgbX, rgbY, threadRect, scissor, tmp, textColor);
                
                rgbX += xMargin;// + ls_uiGlyphStringLen(c, font, tmp);
                ls_utf32FromInt_t(&tmp, picker->pickedColor.g);
                ls_uiGlyphString(c, font, pixelHeight, rgbX, rgbY, threadRect, scissor, tmp, textColor);
                
                rgbX += xMargin;// + ls_uiGlyphStringLen(c, font, tmp);
                ls_utf32FromInt_t(&tmp, picker->pickedColor.b);
                ls_uiGlyphString(c, font, pixelHeight, rgbX, rgbY, threadRect, scissor, tmp, textColor);
                
                //NOTE: Add HSV Label
                s32 hsvX = picker->centerX - picker->radius;
                s32 hsvY = picker->centerY - picker->radius - 2*yMargin;
                ls_uiGlyphString(c, font, pixelHeight, hsvX, hsvY, threadRect, scissor,
                                 ls_utf32Constant(U"HSV"), textColor);
                
                hsvX += xMargin;// + ls_uiGlyphStringLen(c, font, ls_utf32Constant(U"HSV"));
                ls_utf32FromInt_t(&tmp, hue);
                ls_uiGlyphString(c, font, pixelHeight, hsvX, hsvY, threadRect, scissor, tmp, textColor);
                
                hsvX += xMargin;// + ls_uiGlyphStringLen(c, font, tmp);
                ls_utf32FromInt_t(&tmp, saturation*100);
                ls_uiGlyphString(c, font, pixelHeight, hsvX, hsvY, threadRect, scissor, tmp, textColor);
                
                hsvX += xMargin;// + ls_uiGlyphStringLen(c, font, tmp);
                ls_utf32FromInt_t(&tmp, picker->value*100);
                ls_uiGlyphString(c, font, pixelHeight, hsvX, hsvY, threadRect, scissor, tmp, textColor);
                
            }
        } break;
        
        case UI_RC_BITMAP:
        {
            UIBitmap bmp = curr->bitmap;
            ls_uiStretchBitmap(c, &bmp, {xPos, yPos, w, h}, threadRect, scissor);
        } break;

        case UI_RC_CIRCLE:
        {
            ls_uiDrawCircle(c, xPos, yPos, w, h, threadRect, scissor, bkgColor);
        } break;
        
        default: { 
            char error[128]   = "Unhandled Render Command Type ";
            u32 cmdTypeStrLen = ls_len((char*)RenderCommandTypeAsString[curr->type]);
            ls_memcpy((void *)RenderCommandTypeAsString[curr->type], (void *)(error + 30), cmdTypeStrLen);
            error[30+cmdTypeStrLen] = '\n';
            
            AssertMsg(FALSE, (char *)error);
        } break;
    }
}

void ls_uiRender__(UIContext *c, u32 threadID)
{
    UIWindow *win = c->currWindow;

    //NOTE: First clear the background
    switch(__LS_UI_THREAD_COUNT)
    {
        case 0:
        case 1:
        { ls_uiClearRect(c, 0, 0, win->width, win->height, c->backgroundColor); } break;
        
        case 2:
        {
            s32 halfWidth = win->width/2;
            
            s32 tY = 0;
            s32 tX = halfWidth*threadID;
            s32 tH = win->height;
            s32 tW = halfWidth;
            
            ls_uiClearRect(c, tX, tY, tW, tH, c->backgroundColor);
        } break;
        
        case 4:
        {
            s32 halfWidth  = win->width/2;
            s32 halfHeight = win->height/2;
            
            s32 tY = halfHeight*(threadID/2);
            s32 tX = halfWidth*(threadID%2);
            s32 tH = halfHeight;
            s32 tW = halfWidth;
            
            ls_uiClearRect(c, tX, tY, tW, tH, c->backgroundColor);
        } break;
        
        case 8:
        {
            s32 qrtWidth   = win->width/4;
            s32 halfHeight = win->height/2;
            
            s32 tY = halfHeight*(threadID/4);
            s32 tX = qrtWidth*(threadID%4);
            s32 tH = halfHeight;
            s32 tW = qrtWidth;
            
            ls_uiClearRect(c, tX, tY, tW, tH, c->backgroundColor);
        } break;
        
        default: { AssertMsg(FALSE, "Unhandled thread count when clearing window\n"); } break;
    }
    
    //NOTE: Render Layers in Z-order. Layer Zero is the first to be rendered, 
    //      so it's the one farther away from the screen
    for(u32 zLayer = 0; zLayer < UI_Z_LAYERS; zLayer++)
    {
        stack *currLayer = c->renderGroups[threadID].RenderCommands + zLayer;
        
        s32 count = currLayer->count;
        for(u32 commandIdx = 0; commandIdx < count; commandIdx++)
        {
            RenderCommand *curr = (RenderCommand *)ls_stackPop(currLayer);
            ls_uiRenderSingleCommand(c, curr);
        }
    }
    
    c->renderGroups[threadID].isDone = TRUE;
    
#if _DEBUG
    RenderCommandUID = 0;
#endif
    
    return;
}

#endif //LS_UI_IMPLEMENTATION
