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
#include "lsUI.fonts.h"
#include "lsUI.bitmaps.h"
#include "lsUI.rects.h"
#include "lsUI.textboxes.h"
#include "lsUI.labels.h"
#include "lsUI.listboxes.h"
#include "lsUI.buttons.h"
#include "lsUI.checks.h"
#include "lsUI.sliders.h"
#include "lsUI.menus.h"
#include "lsUI.colorpickers.h"


struct UILPane
{
    u32 dtOpen;
    b32 isOpening;
    b32 isOpen;
};

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
    HGLRC OGLContext;
    u32 sdfTextShader;
    u32 textShader;
    u32 rectShader;
    u32 rectVAO;
    u32 gradientRectShader;
    u32 rectGradientVAO;
    u32 texturedRectShader;
    u32 circleShader;
    u32 colorWheelShader;
    u32 circleVAO;
    s32 circleVertCount;
#endif
    
    
#if _DEBUG //NOTE: Tag to debug specific render commands
    b32 isTagged;
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


template<typename T> UIRect ls_uiGlyphStringRect(UIContext *c, UIFont *font, T text, s32 pixelHeight);

void         ls_uiCircle(UIContext *c, s32 centerX, s32 centerY, s32 radius, s32 thickness, Color col, s32 zLayer);

void         ls_uiRender(UIContext *c);

#if _DEBUG
void         ls_uiDebugLog(UIContext *c, s32 x, s32 y, const char *fmt, ...);
#endif

#endif


#ifdef LS_UI_IMPLEMENTATION

//Internal Includes?
#include "lsUI.utils.cpp"
#include "lsUI.primitives.cpp"
#include "lsUI.fonts.cpp"
#include "lsUI.bitmaps.cpp"
#include "lsUI.rects.cpp"
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

template<typename T>
void ls_uiGlyphString(UIContext *c, UIFont *font, s32 pixelHeight, s32 xPos, s32 yPos,
                      UIRect threadRect, UIRect scissor, T text, Color textColor);
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
            win->hasReceivedInput   = TRUE;
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

#ifdef LS_UI_OPENGL_BACKEND
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
    // --------------------------------
    //NOTE: SHARED Vertex Shader
    //
    const char *vertShader = R"LONGLONG(
    #version 330 core

    layout(location = 0) in vec2 inPosition;      // Vertex position
    layout(location = 1) in vec2 inTexCoord;      // Texture coordinates

    out vec2 TexCoord;

    uniform mat4 transform;

    void main() {
        gl_Position = transform * vec4(inPosition, 0.0, 1.0);  // Transform into clip space
        TexCoord = inTexCoord;  // Pass texture coordinates to fragment shader
    }
    )LONGLONG";
    
    
    // --------------------------------
    //NOTE: Rect Shader Compilation
    //
    
    const char *rectFragShader = R"LONGLONG(
    #version 330 core

    in vec2 TexCoord;
    out vec4 FragColor;

    uniform uvec4 color;        // Premultiplied RGBA color
    uniform float zLayer;       // zLayer used to determine frag depth

    vec4 convertIntColToFloat(uvec4 inC) {
        vec4 result = vec4(float(inC.r), float(inC.g), float(inC.b), float(inC.a));
        result.rgba /= 255.0;
        return result;
    }

    void main() {
        vec4 converted = convertIntColToFloat(color);
        if(converted.a < 0.01) { discard; }

        gl_FragDepth = zLayer;
        FragColor = converted;
    }
    )LONGLONG";
    
    c->rectShader = ls_glCreateShader(vertShader, rectFragShader);
    
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
    const char *gradientRectVertShader = R"LONGLONG(
    #version 330 core

    layout(location = 0) in vec2 inPosition;      // Vertex position
    layout(location = 1) in vec2 inTexCoord;      // Texture coordinates
    layout(location = 2) in float gradientFactor; // 0.0 is Black, 1.0 is White

    out vec2 TexCoord;
    out vec4 VertColor;
    uniform mat4 transform;
    uniform uvec4 color;        // Premultiplied RGBA color

    vec4 convertIntColToFloat(uvec4 inC) {
        vec4 result = vec4(float(inC.r), float(inC.g), float(inC.b), float(inC.a));
        result.rgba /= 255.0;
        return result;
    }

    void main() {
        gl_Position = transform * vec4(inPosition, 0.0, 1.0);  // Transform into clip space
        TexCoord = inTexCoord;  // Pass texture coordinates to fragment shader

        vec4 gradientColor = vec4(gradientFactor, gradientFactor, gradientFactor, 1.0);
        vec4 convertedColor = convertIntColToFloat(color);
        if (convertedColor.a > 0.0) {
            gradientColor *= convertedColor;
        }
        VertColor = gradientColor;
    }
    )LONGLONG";
    
    const char *gradientRectFragShader = R"LONGLONG(
    #version 330 core

    in  vec2 TexCoord;
    in  vec4 VertColor;
    out vec4 FragColor;

    uniform float zLayer;       // zLayer used to determine frag depth
    void main() {
        gl_FragDepth = zLayer;
        FragColor    = VertColor;
    }
    )LONGLONG";
    
    c->gradientRectShader = ls_glCreateShader(gradientRectVertShader, gradientRectFragShader);
    
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
    
    const char *texRectFragShader = R"LONGLONG(
    #version 330 core

    in vec2 TexCoord;
    out vec4 FragColor;

    uniform sampler2D tex;
    uniform uvec4 color;        // Premultiplied RGBA color
    uniform float zLayer;       // zLayer used to determine frag depth

    vec4 convertIntColToFloat(uvec4 inC) {
        vec4 result = vec4(float(inC.r), float(inC.g), float(inC.b), float(inC.a));
        result.rgba /= 255.0;
        return result;
    }

    void main() {
        vec4 texColor = texture(tex, TexCoord);
        vec4 converted = convertIntColToFloat(color);

        vec4 finalColor = texColor * converted;
        if(finalColor.a < 0.01) { discard; }

        gl_FragDepth = zLayer;
        FragColor = finalColor;
    }
    )LONGLONG";
    
    c->texturedRectShader = ls_glCreateShader(vertShader, texRectFragShader);
    
    //TODO: Pass center and radius to specialized vertex shader for
    // circles and do the position calcs there!
    
    // --------------------------------
    //NOTE: Circle Shader Compilation
    //
    
    const char *circleFragShader = R"LONGLONG(
    #version 330 core

    in vec2 TexCoord;
    out vec4 FragColor;

    uniform uvec4 color;        // Premultiplied RGBA color
    uniform float thickness;    // Thickness of the outline
    uniform float zLayer;       // zLayer used to determine frag depth

    vec4 convertIntColToFloat(uvec4 inC) {
        vec4 result = vec4(float(inC.r), float(inC.g), float(inC.b), float(inC.a));
        result.rgba /= 255.0;
        return result;
    }

    void main() {
        vec2 center = vec2(0.5, 0.5);
        float dist = distance(TexCoord, center);
        float innerRadius = 0.5 - thickness;

        if (dist > 0.5 || dist < innerRadius) {
            discard;
        }

        vec4 converted = convertIntColToFloat(color);
        if(converted.a < 0.01) { discard; }

        gl_FragDepth = zLayer;
        FragColor = converted;
    }
    )LONGLONG";
    
    c->circleShader = ls_glCreateShader(vertShader, circleFragShader);

    // --------------------------------
    //NOTE: Circle Color Wheel Shader Compilation
    //

    const char *colorWheelFragShader = R"LONGLONG(
        #version 330 core

        in vec2 TexCoord;
        out vec4 FragColor;

        uniform vec2 centerInScreenSpace;
        uniform float radiusInScreenSpace;

        uniform float brightness;
        uniform float zLayer;       // zLayer used to determine frag depth

        void main() {
            float dist_from_center = distance(gl_FragCoord.xy, centerInScreenSpace);
            if (dist_from_center > radiusInScreenSpace) {
                discard;
            }

            vec2 delta = gl_FragCoord.xy - centerInScreenSpace;
            float angle = atan(delta.y, delta.x); // Angle in Radians
            float hue = (angle + 3.14159265) / (2.0 * 3.14159265); // Normalize to [0, 1]
            float saturation = dist_from_center / radiusInScreenSpace;

            //Convert HSV to RGB
            float c = brightness * saturation;
            float x = c * (1.0 - abs(mod(hue * 6.0, 2.0) - 1.0));
            float m = brightness - c;
            
            vec3 color;
            if (hue < 1.0 / 6.0)      { color = vec3(c, x, 0.0); }
            else if (hue < 2.0 / 6.0) { color = vec3(x, c, 0.0); }
            else if (hue < 3.0 / 6.0) { color = vec3(0.0, c, x); }
            else if (hue < 4.0 / 6.0) { color = vec3(0.0, x, c); }
            else if (hue < 5.0 / 6.0) { color = vec3(x, 0.0, c); }
            else                      { color = vec3(c, 0.0, x); }
            color += vec3(m);

            gl_FragDepth = zLayer;
            FragColor = vec4(clamp(color, 0.0, 1.0), 1.0);
        }
    )LONGLONG";
    
    c->colorWheelShader = ls_glCreateShader(vertShader, colorWheelFragShader);
    
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
    
    const char *textVertShader = R"LONGLONG(
    #version 330 core

    layout(location = 0) in vec2 localPositions;   // Vertex position (0 to glyph pixel's Width/Height)
    layout(location = 1) in vec2 inTexCoord;       // Texture coordinates
    layout(location = 2) in vec2 yOffset;          // y0,y1 font pixel offsets

    uniform vec2 viewportSize; // Screen pixel dimensions
    uniform mat4 transform;

    out vec2 TexCoord;

    void main() {
        float scaledY1 = yOffset.y / viewportSize.y;

        vec2 realPos = localPositions / viewportSize;
        realPos.y   -= scaledY1;

        gl_Position = transform * vec4(realPos, 0.0, 1.0);  // Transform into clip space
        TexCoord    = inTexCoord;                           // Pass texture coordinates to fragment shader
    }
    )LONGLONG";
    
    const char *sdfFragShader = R"LONGLONG(
    #version 330 core

    //#define SUPERSAMPLED_SUBPIXEL_AA
    //#define SUBPIXELAA
    //#define SUPERSAMPLING

    in vec2 TexCoord;
    out vec4 FragColor;

    uniform sampler2D tex;  // SDF font texture
    uniform uvec4 textColor;       // Premultiplied RGBA color
    uniform float smoothing;       // Smoothing factor for the SDF edge
    uniform float zLayer;          // zLayer used to determine frag depth

    const float gamma = 2.2;

    vec4 convertIntColToFloat(uvec4 inC) {

    vec4 result = vec4(float(inC.r), float(inC.g), float(inC.b), float(inC.a));
    result.rgba /= 255.0;
    return result;
    }

    void main() {

    // Convert color from integer to float and apply alpha
    vec4 fColor = convertIntColToFloat(textColor);

    #ifdef SUPERSAMPLING

    //2X Supersampling
    vec2 offset = vec2(0.5) / textureSize(tex, 0);

    float sdfValues[4];
    sdfValues[0] = texture(tex, TexCoord + vec2(-offset.x, -offset.y)).r;
    sdfValues[1] = texture(tex, TexCoord + vec2( offset.x, -offset.y)).r;
    sdfValues[2] = texture(tex, TexCoord + vec2(-offset.x,  offset.y)).r;
    sdfValues[3] = texture(tex, TexCoord + vec2( offset.x,  offset.y)).r;

    // Compute the alpha value using a threshold (0.5 is the middle distance)
    float base  = 0.65;
    float alpha = 0.0;
    for (int i = 0; i < 4; ++i) {
    alpha += smoothstep(base - smoothing, base + smoothing, sdfValues[i]);
    }

    alpha /= 4.0; // Average the alphas

    // Output color with pre-multiplied alpha
    vec4 result = vec4(fColor.rgb * alpha, fColor.a * alpha);

    #elif defined(SUBPIXELAA)

    vec2 redOff = vec2(-0.33, 0.0) / textureSize(tex, 0); // Left of Pixel
    vec2 greOff = vec2(  0.0, 0.0) / textureSize(tex, 0); // Center
    vec2 bluOff = vec2( 0.33, 0.0) / textureSize(tex, 0); // Right of Pixel

    // Sample the Texture at each subpixel offset and calc alpha
    float base = 0.65;
    float alphaRed = smoothstep(base - smoothing, base + smoothing, texture(tex, TexCoord + redOff).r);
    float alphaGre = smoothstep(base - smoothing, base + smoothing, texture(tex, TexCoord + greOff).r);
    float alphaBlu = smoothstep(base - smoothing, base + smoothing, texture(tex, TexCoord + bluOff).r);

    // Gamma-correct
    alphaRed = pow(alphaRed, 1.0 / gamma);
    alphaGre = pow(alphaGre, 1.0 / gamma);
     alphaBlu = pow(alphaBlu, 1.0 / gamma);

    // Blend to reduce noticeable fringing
    alphaRed = mix(alphaRed, alphaGre, 0.3);
    alphaBlu = mix(alphaBlu, alphaGre, 0.3);

    // Set each channel to its corresponding subpixel alpha intensity
    vec3 subpixelColor = vec3(fColor.r * alphaRed, fColor.g * alphaGre, fColor.b * alphaBlu);

    // Average alpha value for visibility control (not premultiplied alpha)
    float finalAlpha = (alphaRed + alphaGre + alphaBlu) / 3.0;

    vec4 result = vec4(subpixelColor, finalAlpha);

    #elif defined(SUPERSAMPLED_SUBPIXEL_AA)

    //2X Supersampling
     vec2 offset = vec2(0.5) / textureSize(tex, 0);

     vec2 redOff = vec2(-0.33, 0.0) / textureSize(tex, 0); // Left of Pixel
     vec2 greOff = vec2(  0.0, 0.0) / textureSize(tex, 0); // Center
     vec2 bluOff = vec2( 0.33, 0.0) / textureSize(tex, 0); // Right of Pixel

     vec2 offsetFrags[4];
    offsetFrags[0] = TexCoord + vec2(-offset.x, -offset.y);
    offsetFrags[1] = TexCoord + vec2( offset.x, -offset.y);
    offsetFrags[2] = TexCoord + vec2(-offset.x,  offset.y);
    offsetFrags[3] = TexCoord + vec2( offset.x,  offset.y);

    float base = 0.65;
    float red;
    float green;
    float blue;
    vec3 subpix;
    float finalAlpha;
    for (int i = 0; i < 4; ++i) {
      red   = smoothstep(base - smoothing, base + smoothing, texture(tex, offsetFrags[i] + redOff).r);
     green = smoothstep(base - smoothing, base + smoothing, texture(tex, offsetFrags[i] + greOff).r);
     blue  = smoothstep(base - smoothing, base + smoothing, texture(tex, offsetFrags[i] + bluOff).r);

    red = pow(red, 1.0 / gamma);
    green = pow(green, 1.0 / gamma);
     blue = pow(blue, 1.0 / gamma);

    red = mix(red, green, 0.3);
    blue = mix(blue, green, 0.3);

      subpix += vec3(fColor.r * red, fColor.g * green, fColor.b * blue);

    // Average alpha value for visibility control (not premultiplied alpha)
     finalAlpha += (red + green + blue) / 3.0;
    }

    finalAlpha /= 4.0;
    subpix /= 4.0;

    vec4 result = vec4(subpix * finalAlpha, finalAlpha);

    #else //NO FILTERS

    // Sample the SDF texture, values range from 0 to 1
        float sdfValue = texture(tex, TexCoord).r;
    float base  = 0.58;
    float alpha = smoothstep(base - smoothing, base + smoothing, sdfValue);

        // Output color with pre-multiplied alpha
    vec4 result = vec4(fColor.rgb * alpha, fColor.a * alpha);

    #endif

    if(result.a < 0.01) { discard; }
    gl_FragDepth = zLayer;
    FragColor = result;
    }
    )LONGLONG";
    
    c->sdfTextShader = ls_glCreateShader(textVertShader, sdfFragShader);
    
    
    // --------------------------------
    //NOTE: Text Shader Compilation
    //
    
    const char *textFragShader = R"LONGLONG(
    #version 330 core

    in vec2 TexCoord;
    out vec4 FragColor;

    uniform sampler2D tex;   // Atlas font texture
    uniform uvec4 textColor; // Premultiplied RGBA color
    uniform float zLayer;    // zLayer used to determine frag depth

    vec4 convertIntColToFloat(uvec4 inC) {
        vec4 result = vec4(float(inC.r), float(inC.g), float(inC.b), float(inC.a));
        result.rgba /= 255.0;
        return result;
    }

    void main() {
        vec4 texColor = texture(tex, TexCoord);
        vec4 converted = convertIntColToFloat(textColor);

        vec4 finalColor = texColor * converted;
        if(finalColor.a < 0.01) { discard; }

        gl_FragDepth = zLayer;
        FragColor = finalColor;
    }
    )LONGLONG";
    
    c->textShader = ls_glCreateShader(textVertShader, textFragShader);
    
    //
    // --------------------------------
}
#endif

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
    win.WindowDC = GetDC(WindowHandle);
    wglChoosePixelFormatARB(win.WindowDC, pixelFormatAttribs, 0, 1, &pixelFormat, &numFormats);
    if(!numFormats) {
        AssertMsg(FALSE, "Failed to set OpenGL Pixel Format");
    }
    
    PIXELFORMATDESCRIPTOR pfd;
    DescribePixelFormat(win.WindowDC, pixelFormat, sizeof(pfd), &pfd);
    if(!SetPixelFormat(win.WindowDC, pixelFormat, &pfd)) {
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
        
        HGLRC gl33Context = wglCreateContextAttribsARB(win.WindowDC, 0, gl33Attribs);
        if(!gl33Context) {
            AssertMsg(FALSE, "Failed to create OpenGL 3.3 context");
        }
        
        if(!wglMakeCurrent(win.WindowDC, gl33Context)) {
            AssertMsg(FALSE, "Failed to Activate OpenGL 3.3 context");
        }
        c->OGLContext = gl33Context;
        
        ls_glLoadFunc(win.WindowDC);
     
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        __ui_CreateDefaultShaders(c);
    }
    
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
#endif
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


void ls_uiClearRect(UIContext *c, s32 startX, s32 startY, s32 w, s32 h, Color col)
{
    UIWindow *win = c->currWindow;
#ifdef LS_UI_OPENGL_BACKEND
    
    glUseProgram(c->rectShader);
    glUniform4ui(glGetUniformLocation(c->rectShader, "color"), col.r, col.g, col.b, col.a);
    
    f32 normZ = 1.0f; //1.0f - ((f32)c->zLayer / (f32)(UI_Z_LAYERS-1));
    glUniform1f(glGetUniformLocation(c->rectShader, "zLayer"), normZ);
    
    f64 xf = (f64)startY;
    f64 yf = (f64)startY;
    f64 wf = (f64)win->width;
    f64 hf = (f64)win->height;
    
    // Positions need to be adjusted by the width and height... for some reason?
    f64 xp = ((xf + (f64)w / 2.0) / (wf / 2.0)) - 1.0;
    f64 yp = ((yf + (f64)h / 2.0) / (hf / 2.0)) - 1.0;
    Mat4 translate = Translate(vec4(xp, yp, 0.0, 1.0));
    Mat4 scale     = Scale4(vec4((f64)w / wf, (f64)h / hf, 0.0, 1.0));
    Mat4 transform = ls_mat4x4Mul(scale, translate);
    
    glUniformMatrix4fv(glGetUniformLocation(c->rectShader, "transform"), 1, GL_TRUE, (GLfloat *)transform.values);
    
    glBindVertexArray(c->rectVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glBindVertexArray(0);
    glUseProgram(0);
    
#else
    s32 diffWidth = (w % 4);
    s32 simdWidth = w - diffWidth;
    
    s32 diffHeight = (h % 4);
    s32 simdHeight = h - diffHeight;
    
    //NOTE: Do the first Sub-Rectangle divisible by 4.
    __m128i color = _mm_set1_epi32((int)col.value);
    
    for(s32 y = startY; y < startY+simdHeight; y++)
    {
        for(s32 x = startX; x < startX+simdWidth; x += 4)
        {
            u32 idx = ((y*win->width) + x)*sizeof(s32);
            __m128i *At = (__m128i *)(win->drawBuffer + idx);
            
            _mm_storeu_si128(At, color);
        }
    }
    
    //NOTE: Complete the 2 remaining Sub-Rectangles at the right and top. (if there are).
    //      We decide to have the right rectangle be full height
    //      And the top one be less-than-full width, to avoid over-drawing the small subrect
    //        in the top right corner.
    u32 *At = (u32 *)win->drawBuffer;
    
    if(diffWidth) 
    {
        for(s32 y = startY; y < startY+h; y++)
        {
            for(s32 x = startX+simdWidth; x < startX+w; x++)
            {
                At[y*win->width + x] = col.value;
            }
        }
    }
    
    if(diffHeight)
    {
        for(s32 y = startY+simdHeight; y < startY+h; y++)
        {
            for(s32 x = startX; x < startX+simdWidth; x++)
            {
                At[y*win->width + x] = col.value;
            }
        }
    }
#endif
}

//TODO @UIPos
void ls_uiCircle(UIContext *c, s32 centerX, s32 centerY, s32 radius, s32 thickness, Color col, s32 zLayer = 0)
{
    RenderCommand command = { UI_RC_CIRCLE, centerX, centerY, radius, thickness };
    command.bkgColor = col;
    ls_uiPushRenderCommand(c, command, zLayer);
}

//TODO @UIPos
void ls_uiCircle(UIContext *c, UIPos pos, Color col, s32 zLayer = 0)
{
    RenderCommand command = { UI_RC_CIRCLE };
    command.bkgColor = col;
    command.pos      = pos;
    ls_uiPushRenderCommand(c, command, zLayer);
}

void ls_uiRenderStringOnRect(UIContext *c, UIFont *f, UITextBox *box, s32 pixelHeight, s32 x, s32 y, s32 w, s32 h, UIRect threadRect, UIRect scissor, Color textColor, Color invTextColor)
{
    AssertMsg(c, "Context is null\n");
    AssertMsg(box, "TextBox is null\n");
    AssertMsg(f, "Passed Font is null\n");
    
    UIWindow *win = c->currWindow;
    s32 cIdx = box->caretIndex - box->currLineBeginIdx;
    
    const f64 scaling    = (f64)pixelHeight / (f64)f->pixelHeight;
    const s32 lineHeight = f->ascent*scaling -  f->descent*scaling +  f->lineGap*scaling;
    const u32 horzOff    = (u32)(win->width*0.01f);
    const u32 strMaxX    = x + (w - 2*horzOff);
    
    //TODO: do I even need padding?
    const s32 maxLines   = h / lineHeight;
    
    s32 xOffset = box->viewBeginIdx;
    s32 yOffset = 0;
    
    //TODO: SIMD this?
    //TODO: If we stored the text differently (maybe store an index array of the start of every line...)
    //      this entire thing does not need to loop. (and the memory cost would not be too large)
    //NOTE: If the caret line index is currently larger than the maximum renderable lines
    // we need to skip the first N lines.
    s32 viewStartIdx = 0;
    if(box->caretLineIdx > maxLines) { 
        yOffset = box->caretLineIdx - maxLines + 1;
        s32 tmpYOff = yOffset;
        
        //NOTE: Advance the string vertically to the nth line
        while(tmpYOff)
        {
            u32 code = box->text.data[viewStartIdx];
            AssertMsgF(code <= c->fontGroup.maxCodepoint, "GlyphIndex %d OutOfBounds\n", code);
            
            if(code == (char32_t)'\n') { tmpYOff -= 1; }
            viewStartIdx += 1;
        }
    }
    
    s32 currX = x;
    s32 currY = y;
    s32 relativeCaretLineIdx = box->caretLineIdx - yOffset;
    u32 code     = 0;
    u32 codeNext = 0xFFFFFFFF;
    
    utf32 realString = { box->text.data + viewStartIdx, box->text.len - viewStartIdx, box->text.size - viewStartIdx };
    uview lineView = ls_uviewCreate(realString);
    utf32 firstLine = ls_uviewNextLine(lineView).s;
    
    s32 initialXPos = x;
    switch(box->align)
    {
        case UI_TB_ALIGN_LEFT: {
            initialXPos = x;
        } break;
        
        case UI_TB_ALIGN_RIGHT: {
            initialXPos = x+w-horzOff - ls_uiGlyphStringRect(c, f, firstLine, pixelHeight).w;
        } break;
        
        case UI_TB_ALIGN_CENTER: {
            initialXPos = x+w-horzOff - (ls_uiGlyphStringRect(c, f, firstLine, pixelHeight).w / 2);
        } break;
        
        default: { AssertMsg(FALSE, "Unhandled TextBox Alignement\n"); } break;
    }
    
    currX = initialXPos;
    
    //NOTE: This is the index into the entire original string data for the textbox.
    //      This is necessary because some textbox metadata (like selection begin/end indices) are absolute
    //      (so relative to the beginning of the entire textbox string, rather than its line). And if we need to
    //      compare against them, we need an absolute index into the string, rather then an index relative to the
    //      currently rendered line.
    s32 absoluteTextIdx = viewStartIdx;
    for(u32 lineIdx = 0; lineIdx < maxLines; lineIdx++)
    {
        s32 relativeLineIdx = lineIdx + yOffset;
        
        lineView = ls_uviewNextLine(lineView);
        utf32 line = lineView.s;
        
        //NOTE: xOffset will only be > 0 when scrolled right.
        // We must not advance more than a given line's length, otherwise the successive lines
        // will have their absoluteTextIdx wrongly offsetted.
        if(line.len < xOffset) { absoluteTextIdx += line.len; }
        else                   { absoluteTextIdx += xOffset; }
        
        s32 caretX = currX - 3; //TODO: hardcoded pixel diff...
        for(u32 lIdx = xOffset; lIdx < line.len; lIdx++, absoluteTextIdx++)
        {
            if((lineIdx == relativeCaretLineIdx) && (cIdx == lIdx)) { caretX = currX-3; }
            
            //NOTE: If we're trying to render data past the current view (scrolled away to the right)
            //      We just stop. We re-adjust the caret position if necessary, and advance the
            //      absoluteTextIdx to take into consideration the missed iterations.
            if(currX > strMaxX)
            {
                if((lineIdx == relativeCaretLineIdx) && (cIdx == lIdx+1)) { caretX = currX-3; }
                absoluteTextIdx += (line.len - lIdx); break;
            }
            
            code = line.data[lIdx];
            if(lIdx < line.len-1) { codeNext = line.data[lIdx+1]; }
            AssertMsgF(code <= c->fontGroup.maxCodepoint, "GlyphIndex %d OutOfBounds\n", code);
            
            Color actualColor = textColor;
            
            //TODO: Pretty inefficient to keep redrawing the background all the time.
            if(box->isSelecting && (box->selectBeginLine <= relativeLineIdx) && (box->selectEndLine >= relativeLineIdx)
               && (box->selectBeginIdx <= absoluteTextIdx) && (box->selectEndIdx > absoluteTextIdx))
            {
                actualColor = invTextColor;
                s32 xAdv    = ls_uiGlyphAdv(c, f, code, codeNext, scaling);
                ls_uiFillRect(c, currX, currY, xAdv, lineHeight, threadRect, scissor, c->invWidgetColor);
            }
            
            s32 xAdvance = ls_uiGlyph(c, f, code, codeNext, currX, currY, scaling, threadRect, scissor, actualColor);
            currX += xAdvance;
        }
        
        if((lineIdx == relativeCaretLineIdx) && (cIdx == line.len)) { caretX = currX-3; }
        
        if(box->isCaretOn && (win->currentFocus == (u64 *)box) && (lineIdx == relativeCaretLineIdx))
        {
            ls_uiGlyph(c, f, (u32)'|', 0xFFFFFFFF, caretX, currY, scaling, threadRect, scissor, textColor);
        }
        
        currY -= lineHeight;
        currX  = initialXPos;
    }
}


template<typename T>
void ls_uiGlyphString(UIContext *c, UIFont *font, s32 pixelHeight, s32 xPos, s32 yPos,
                      UIRect threadRect, UIRect scissor, T text, Color textColor)
{
    AssertMsg(c, "Context is null\n");
    LogMsg(font, "Passed font is null\n");
    if(!font) { return; }
    
    //TODO: Does it ever make sense to use LeftSideBearing on the left edge of the viewport?
    // Seems easier to just keep an healthy pad. It's not `font-indipendent` but who cares?
    s32 currXPos  = xPos;
    s32 currYPos  = yPos;
    f64 scaling   = (f64)pixelHeight / (f64)font->pixelHeight;
    s32 lineSpace = font->ascent*scaling - font->descent*scaling + font->lineGap*scaling;
    
    for(u32 i = 0; i < text.len; i++)
    {
        u32 cp = 0xFFFFFFFF;
        u32 cpNext = 0xFFFFFFFF;
        if constexpr(typeid(T) == typeid(utf32))
        { cp = text.data[i]; cpNext = i < text.len-1 ? text.data[i+1] : 0xFFFFFFFF; }
        else if constexpr(typeid(T) == typeid(utf8))
        { cp = ls_utf32CharFromUtf8(text, i); cpNext = i < text.len-1 ? ls_utf32CharFromUtf8(text, i+1) : 0xFFFFFFFF; }
        else
        { AssertMsg(FALSE, "Invalid use of string type. Only utf32 and utf8 are supported"); }
        AssertMsgF(cp <= c->fontGroup.maxCodepoint, "GlyphIndex %d OutOfBounds\n", cp);
        AssertMsgF(cpNext == 0xFFFFFFFF || cpNext <= c->fontGroup.maxCodepoint, "CPN GlyphIndex %d OutOfBounds\n", cpNext);
        
        s32 xAdvance = ls_uiGlyph(c, font, cp, cpNext, currXPos, currYPos, scaling, threadRect, scissor, textColor);
        currXPos += xAdvance;
        if(cp == (u32)'\n') { currXPos = xPos; currYPos -= lineSpace; }
    }
}


//TODO: Should I always pass a layout, and maybe only keep an helper when I want no layout, so the layout region
//      would just be the entire window???
void ls_uiGlyphStringInLayout(UIContext *c, UIFont *font, UILayoutRect layout,
                              UIRect threadRect, UIRect scissor, utf32 text, Color textColor)
{
    AssertMsg(c, "Context is null\n");
    LogMsg(font, "Passed font is null\n");
    if(!font) { return; }
    
    s32 currXPos = layout.startX;
    s32 currYPos = layout.startY + layout.maxY;
    for(u32 i = 0; i < text.len; i++)
    {
        u32 cp = text.data[i];
        u32 cpNext = i < text.len - 1 ? text.data[i+1] : 0xFFFFFFFF;
        AssertMsgF(cp <= c->fontGroup.maxCodepoint, "GlyphIndex %d OutOfBounds\n", cp);
        AssertMsgF(cpNext == 0xFFFFFFFF || cpNext <= c->fontGroup.maxCodepoint, "CPN GlyphIndex %d OutOfBounds\n", cpNext);
        
        if(cp == (u32)'\n') {
            currYPos -= font->pixelHeight;
            currXPos = layout.minX;
            continue;
        }
        
        s32 newAdvance = ls_uiGlyph(c, font, cp, cpNext, currXPos, currYPos, 1.0, threadRect, scissor, textColor);
        if((currXPos + newAdvance) > (layout.maxX))
        { 
            currYPos -= font->pixelHeight; 
            currXPos = layout.minX;
            continue;
        }
        
        currXPos += newAdvance;
    }
}

//TODO: Should actually have totalWidth and totalHeight be floating point instead of ints
//      Because of scaling, the intermediate values will probably be fractional, and flooring
//        at the end should yield more accurate results, especially in long strings!
template<typename T>
UIRect ls_uiGlyphStringRect(UIContext *c, UIFont *font, T text, s32 pixelHeight)
{
    AssertMsg(c, "Context is null\n");
    LogMsg(font, "Passed font is null\n");
    if(!font) { return {}; }
    
    s32 maxWidth = 0;
    s32 totalWidth  = 0;
    s32 totalHeight = pixelHeight;
    
    f64 scaling = (f64)pixelHeight / (f64)font->pixelHeight;
    s32 lineSpace = font->ascent*scaling - font->descent*scaling + font->lineGap*scaling;
    
    for(u32 i = 0; i < text.len; i++)
    {
        u32 cp = 0xFFFFFFFF, cpNext = 0xFFFFFFFF;
        if constexpr(typeid(T) == typeid(utf32))
        { cp = text.data[i]; cpNext = i < text.len-1 ? text.data[i+1] : 0xFFFFFFFF; }
        else if constexpr(typeid(T) == typeid(utf8))
        { cp = ls_utf32CharFromUtf8(text, i); cpNext = i < text.len-1 ? ls_utf32CharFromUtf8(text, i+1) : 0xFFFFFFFF; }
        else
        { AssertMsg(FALSE, "Invalid use of string type. Only utf32 and utf8 are supported"); }
        
        AssertMsgF(cp <= c->fontGroup.maxCodepoint, "CP GlyphIndex %d OutOfBounds\n", cp);
        AssertMsgF(cpNext == 0xFFFFFFFF || cpNext <= c->fontGroup.maxCodepoint, "CPN GlyphIndex %d OutOfBounds\n", cpNext);
        
        totalWidth += ls_uiGlyphAdv(c, font, cp, cpNext, scaling);
        if(cp == (u32)'\n')       { totalWidth = 0; totalHeight += lineSpace; }
        if(totalWidth > maxWidth) { maxWidth = totalWidth; }
    }
    
    UIRect result = {0, 0, maxWidth, totalHeight};
    return result;
}


void ls_uiDrawArrow(UIContext *c, s32 x, s32 yPos, s32 w, s32 h,
                    UIRect threadRect, UIRect scissor, Color bkgColor, UIArrowSide s)
{
    UIWindow *win = c->currWindow;

#ifdef LS_UI_OPENGL_BACKEND
    
    ls_uiBorderedRect(c, x-1, yPos, w, h, threadRect, scissor, bkgColor);
    
    //TODO: Customize color?
    Color col = c->borderColor;
    
    f64 arrowWidth  = 0.0;
    f64 arrowHeight = 0.0;
    s32 vaoOffset   = 0;
    
    switch(s)
    {
        case UIA_DOWN:
        {
            arrowWidth  = 0.58f*(f64)w;
            arrowHeight = 0.52f*(f64)h;
            vaoOffset   = 12;
        } break;
        
        case UIA_RIGHT:
        {
            arrowWidth  = 0.52f*w;
            arrowHeight = 0.58f*h;
            vaoOffset   = 9;
        } break;
        
        case UIA_LEFT:
        {
            arrowWidth  = 0.52f*w;
            arrowHeight = 0.58f*h;
            vaoOffset   = 15;
        } break;
    }
    
    s32 startX = x + (w - (s32)arrowWidth)/2 - 1;
    s32 startY = (yPos + (h-(s32)arrowHeight)/2) - 1;
    
    glUseProgram(c->rectShader);
    glUniform4ui(glGetUniformLocation(c->rectShader, "color"), col.r, col.g, col.b, col.a);
    
    f32 normZ = 1.0f ;//- ((f32)c->zLayer / (f32)(UI_Z_LAYERS-1));
    glUniform1f(glGetUniformLocation(c->rectShader, "zLayer"), normZ);
    
    f64 xf = (f64)startX;
    f64 yf = (f64)startY;
    f64 wf = (f64)win->width;
    f64 hf = (f64)win->height;
    
    // Positions need to be adjusted by the width and height... for some reason?
    f64 xp = ((xf + (f64)arrowWidth / 2.0) / (wf / 2.0)) - 1.0;
    f64 yp = ((yf + (f64)arrowHeight / 2.0) / (hf / 2.0)) - 1.0;
    
    Mat4 translate = Translate(vec4(xp, yp, 0.0, 1.0));
    Mat4 scale = Scale4(vec4((f64)arrowWidth / wf, (f64)arrowHeight / hf, 0.0, 1.0));
    Mat4 transform = ls_mat4x4Mul(scale, translate);
    
    glUniformMatrix4fv(glGetUniformLocation(c->rectShader, "transform"), 1, GL_TRUE, (GLfloat *)transform.values);
    
    glBindVertexArray(c->rectVAO);
    glDrawArrays(GL_TRIANGLES, vaoOffset, 3);
    
    glBindVertexArray(0);
    glUseProgram(0);
    
#else
    
    //TODO: Scissor???
    s32 minX = threadRect.minX;
    s32 minY = threadRect.minY;
    s32 maxX = threadRect.maxX;
    s32 maxY = threadRect.maxY;
    
    u32 *At = (u32 *)win->drawBuffer;
    
    s32 xPos = x-1;
    
    ls_uiBorderedRect(c, xPos, yPos, w, h, threadRect, scissor, bkgColor);
    
    //TODO: Fix threadRect pre-calculated bounds checks on every arrow direction!
    if(s == UIA_DOWN)
    {
        Color arrowColor = c->borderColor;
        
        s32 arrowWidth = 0.50f*w;
        s32 arrowHeight = 0.40f*h;
        
        f32 scaling = (f32)arrowHeight / (f32)arrowWidth;
        f32 progressiveX = 0.0f;
        
        s32 xBase = xPos  + (w - arrowWidth)/2;
        s32 xEnd  = xBase + arrowWidth;
        s32 xMid  = xBase + arrowWidth/2;
        
        s32 yStart = (yPos + h - (h - arrowHeight)/2) - 1;
        s32 yEnd = yStart - arrowHeight;
        
        //TODO: This is still wrong with multithreaded
        //TODO: Could this every invert base and end?
        if(xBase < minX)   { xBase  = minX; }
        if(xEnd >= maxX)   { xEnd   = maxX-1; }
        if(yStart >= maxY) {
            s32 yAdv = (yStart - maxY + 1);
            f32 fractAdv = yAdv*scaling;
            xBase += (s32)fractAdv; xEnd -= (s32)fractAdv;
            progressiveX = fractAdv - (s32)fractAdv;
            yStart = maxY-1;
        }
        if(yEnd < minY) { yEnd = minY; }
        
        for(s32 y = yStart; y >= yEnd; y--)
        {
            for(s32 x = xBase; x < xEnd; x++)
            {
                AssertMsg(x >= 0 && x < win->width,  "X out of range. Should have been guarded by thread UI Rects?\n");
                AssertMsg(y >= 0 && y < win->height, "Y out of range. Should have been guarded by thread UI Rects?\n");
                
                //TODO: Setting fractional alpha on the rows where progressiveX advances a fractional amount
                //      would allow better `sub-pixel like` blending. Just a tiny thing to make it look better
                //      at small resolutions.
                At[y*win->width + x] = c->borderColor.value;
            }
            
            progressiveX += scaling;
            s32 intProgress = (s32)progressiveX;
            xBase += intProgress;
            xEnd  -= intProgress;
            progressiveX -= intProgress;
        }
        
    }
    else if(s == UIA_RIGHT)
    {
        s32 arrowWidth  = 0.40f*w;
        s32 hBearing    = (w - arrowWidth)/2;
        s32 xBase       = xPos + hBearing;
        s32 xEnd        = xBase+1;
        
        s32 arrowHeight = 0.50f*h;
        s32 vBearing    = (h - arrowHeight)/2;
        s32 yStart1     = (yPos + h - vBearing) - 1;
        s32 yEnd1       = yStart1 - (arrowHeight/2);
        s32 yStart2     = yEnd1;
        s32 yEnd2       = yStart2 - arrowHeight;
        
        if(yStart1 >= maxY) { yStart1 = maxY; }
        if(yStart2 >= maxY) { yStart2 = maxY; }
        if(xBase  < minX)   { xEnd -= (minX - xBase); xBase = minX; }
        
        for(s32 y = yStart1; y >= yEnd1; y--)
        {
            if(y < minY) { break; }
            
            for(s32 x = xBase; x < xEnd; x++)
            {
                if(x >= maxX) { break; }
                
                if(x < 0 || x >= win->width)  continue;
                if(y < 0 || y >= win->height) continue;
                
                At[y*win->width + x] = RGBg(0x00).value;
            }
            
            xEnd  += 1;
        }
        
        xEnd -= 1;
        for(s32 y = yStart2; y >= yEnd2; y--)
        {
            if(y < minY) { break; }
            
            for(s32 x = xBase; x < xEnd; x++)
            {
                if(x >= maxX) { break; }
                
                if(x < 0 || x >= win->width)  continue;
                if(y < 0 || y >= win->height) continue;
                
                At[y*win->width + x] = RGBg(0x00).value;
            }
            
            xEnd  -= 1;
        }
    }
    else if(s == UIA_LEFT)
    {
        s32 arrowWidth  = 0.40f*w;
        s32 hBearing    = (w - arrowWidth)/2;
        s32 xBase       = xPos + w - hBearing - 1;
        s32 xEnd        = xBase+1;
        
        s32 arrowHeight = 0.50f*h;
        s32 vBearing    = (h - arrowHeight)/2;
        s32 yStart1     = (yPos + h - vBearing) - 1;
        s32 yEnd1       = yStart1 - (arrowHeight/2);
        s32 yStart2     = yEnd1;
        s32 yEnd2       = yStart2 - arrowHeight;
        
        if(yStart1 >= maxY) { yStart1 = maxY; }
        if(yStart2 >= maxY) { yStart2 = maxY; }
        if(xBase  < minX)   { xEnd -= (minX - xBase); xBase = minX; }
        
        for(s32 y = yStart1; y >= yEnd1; y--)
        {
            if(y < minY) { break; }
            
            for(s32 x = xBase; x < xEnd; x++)
            {
                if(x >= maxX) { break; }
                
                if(x < 0 || x >= win->width)  continue;
                if(y < 0 || y >= win->height) continue;
                
                At[y*win->width + x] = RGBg(0x00).value;
            }
            
            xBase -= 1;
        }
        
        xBase += 1;
        for(s32 y = yStart2; y >= yEnd2; y--)
        {
            if(y < minY) { break; }
            
            for(s32 x = xBase; x < xEnd; x++)
            {
                if(x >= maxX) { break; }
                
                if(x < 0 || x >= win->width)  continue;
                if(y < 0 || y >= win->height) continue;
                
                At[y*win->width + x] = RGBg(0x00).value;
            }
            
            xBase += 1;
        }
    }
    
#endif
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



void ls_uiColorValueRect(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h, UIRect threadRect, UIRect scissor)
{
    UIWindow *win = c->currWindow;

#ifdef LS_UI_OPENGL_BACKEND
    
    glUseProgram(c->gradientRectShader);
    glUniform4ui(glGetUniformLocation(c->gradientRectShader, "color"), 0, 0, 0, 0);
    
    f32 normZ = 1.0f ;//- ((f32)c->zLayer / (f32)(UI_Z_LAYERS-1));
    glUniform1f(glGetUniformLocation(c->gradientRectShader, "zLayer"), normZ);
    
    f64 xf = (f64)xPos;
    f64 yf = (f64)yPos;
    f64 wf = (f64)win->width;
    f64 hf = (f64)win->height;
    
    // Positions need to be adjusted by the width and height... for some reason?
    f64 xp = ((xf + (f64)w / 2.0) / (wf / 2.0)) - 1.0;
    f64 yp = ((yf + (f64)h / 2.0) / (hf / 2.0)) - 1.0;
    Mat4 translate = Translate(vec4(xp, yp, 0.0, 1.0));
    Mat4 scale = Scale4(vec4((f64)w / wf, (f64)h / hf, 0.0, 1.0));
    Mat4 transform = ls_mat4x4Mul(scale, translate);
    
    glUniformMatrix4fv(glGetUniformLocation(c->gradientRectShader, "transform"), 1, GL_TRUE, (GLfloat *)transform.values);
    
    glBindVertexArray(c->rectGradientVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glBindVertexArray(0);
    glUseProgram(0);

#else
    
    s32 minX = threadRect.minX > scissor.x ? threadRect.minX : scissor.x;
    s32 minY = threadRect.minY > scissor.y ? threadRect.minY : scissor.y;
    s32 maxX = threadRect.maxX < scissor.x+scissor.w ? threadRect.maxX : scissor.x+scissor.w;
    s32 maxY = threadRect.maxY < scissor.y+scissor.h ? threadRect.maxY : scissor.y+scissor.h;
    
    f32 currGray = 0.0f;
    f32 step     = (f32)h / 255.0f;
    if(yPos < minY) { currGray = ((f32)(minY - yPos) / (f32)h)*255.0f; }
    f32 startGray = currGray;
    
    s32 startY = yPos;
    if(startY < minY) { h -= (minY-startY); startY = minY; }
    
    s32 startX = xPos;
    if(startX < minX) { w -= (minX-startX); startX = minX; }
    
    if(startX+w > maxX) { w = maxX-startX+1; }
    if(startY+h > maxY) { h = maxY-startY+1; }
    
    s32 diffWidth = (w % 4);
    s32 simdWidth = w - diffWidth;
    
    s32 diffHeight = (h % 4);
    s32 simdHeight = h - diffHeight;
    
    //TODO: Make AlphaBlending happen with SSE!!!
    
    //NOTE: Do the first Sub-Rectangle divisible by 4.
    //__m128i color = _mm_set1_epi32((int)c);
    
    for(s32 y = startY; y < startY+simdHeight; y++)
    {
        AssertMsg(y <= maxY, "Should never happen. Height was precomputed\n");
        //if(y > maxY) { break; }
        
        Color col = RGBg((u32)currGray);
        
        for(s32 x = startX; x < startX+simdWidth; x+=4)
        {
            AssertMsg(x <= maxX, "Should never happen. Width was precomputed\n");
            
            if(x < 0 || x >= win->width)  continue;
            if(y < 0 || y >= win->height) continue;
            
            u32 idx = ((y*win->width) + x)*sizeof(s32);
            __m128i *At = (__m128i *)(win->drawBuffer + idx);
            
            __m128i val = _mm_loadu_si128(At);
            
            u32 a1 = _mm_cvtsi128_si32(_mm_shuffle_epi32(val, 0b00000000));
            u32 a2 = _mm_cvtsi128_si32(_mm_shuffle_epi32(val, 0b01010101));
            u32 a3 = _mm_cvtsi128_si32(_mm_shuffle_epi32(val, 0b10101010));
            u32 a4 = _mm_cvtsi128_si32(_mm_shuffle_epi32(val, 0b11111111));
            
            Color c1 = ls_uiAlphaBlend(col, {.value = a1});
            Color c2 = ls_uiAlphaBlend(col, {.value = a2});
            Color c3 = ls_uiAlphaBlend(col, {.value = a3});
            Color c4 = ls_uiAlphaBlend(col, {.value = a4});
            
            __m128i color = _mm_setr_epi32(c1.value, c2.value, c3.value, c4.value);
            
            _mm_storeu_si128(At, color);
        }
        
        currGray += step;
    }
    
    //NOTE: Complete the 2 remaining Sub-Rectangles at the right and top. (if there are).
    //      We decide to have the right rectangle be full height
    //      And the top one be less-than-full width, to avoid over-drawing the small subrect
    //        in the top right corner.
    u32 *At = (u32 *)win->drawBuffer;
    
    if(diffWidth)
    {
        f32 diffGray = startGray;
        
        for(s32 y = startY; y < startY+h; y++)
        {
            if(y > maxY) { break; }
            
            Color col = RGBg((u32)diffGray);
            
            for(s32 x = startX+simdWidth; x < startX+w; x++)
            {
                if(x > maxX) { 
                    ls_printf("diffSIMDWidth: %d, diffWidth: %d\n", x-maxX, diffWidth);
                    break; 
                }
                
                if(x < 0 || x >= win->width)  continue;
                if(y < 0 || y >= win->height) continue;
                
                Color base = {.value = At[y*win->width + x] };
                Color blendedColor = ls_uiAlphaBlend(col, base);
                At[y*win->width + x] = blendedColor.value;
            }
            
            diffGray += step;
        }
    }
    
    if(diffHeight)
    {
        for(s32 y = startY+simdHeight; y < startY+h; y++)
        {
            if(y > maxY) { break; }
            
            Color col = RGBg((u32)currGray);
            
            for(s32 x = startX; x < startX+simdWidth; x++)
            {
                if(x > maxX) { break; }
                
                if(x < 0 || x >= win->width)  continue;
                if(y < 0 || y >= win->height) continue;
                
                Color base = { .value = At[y*win->width + x] };
                Color blendedColor = ls_uiAlphaBlend(col, base);
                At[y*win->width + x] = blendedColor.value;
            }
            
            currGray += step;
        }
    }
    
#endif
}

void ls_uiFillColorWheel(UIContext *c, s32 centerX, s32 centerY, s32 radius, f32 value,
                         UIRect threadRect, UIRect scissor)
{
    UIWindow *win = c->currWindow;

#ifdef LS_UI_OPENGL_BACKEND
    
    glUseProgram(c->colorWheelShader);
    
    s32 leftCornerX = centerX - radius;
    s32 leftCornerY = centerY - radius;
    
    f64 xf = (f64)leftCornerX;
    f64 yf = (f64)leftCornerY;
    f64 wf = (f64)win->width;
    f64 hf = (f64)win->height;
    
    s32 w = radius*2;
    s32 h = radius*2;
    
    f64 xp = ((xf + (f64)w / 2.0) / (wf / 2.0)) - 1.0;
    f64 yp = ((yf + (f64)h / 2.0) / (hf / 2.0)) - 1.0;
    
    f64 aspectRatio = wf/hf;
    Mat4 translate = Translate(vec4(xp, yp, 0.0, 1.0));
    Mat4 scale = Scale4(vec4((f64)w / wf, (f64)h / hf, 0.0, 1.0));
    Mat4 transform = ls_mat4x4Mul(scale, translate);

    glUniformMatrix4fv(glGetUniformLocation(c->colorWheelShader, "transform"), 1, GL_TRUE, (GLfloat *)transform.values);
    glUniform2f(glGetUniformLocation(c->colorWheelShader, "centerInScreenSpace"), (f64)centerX, (f64)centerY);
    glUniform1f(glGetUniformLocation(c->colorWheelShader, "radiusInScreenSpace"), (f64)radius);
    glUniform1f(glGetUniformLocation(c->colorWheelShader, "brightness"), value);

    f32 normZ = 1.0f ;//- ((f32)c->zLayer / (f32)(UI_Z_LAYERS-1));
    glUniform1f(glGetUniformLocation(c->colorWheelShader, "zLayer"), normZ);
    
    glBindVertexArray(c->rectVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glBindVertexArray(0);
    glUseProgram(0);
    
#else
    
    s32 minX = threadRect.minX > scissor.x ? threadRect.minX : scissor.x;
    s32 minY = threadRect.minY > scissor.y ? threadRect.minY : scissor.y;
    s32 maxX = threadRect.maxX < scissor.x+scissor.w ? threadRect.maxX : scissor.x+scissor.w;
    s32 maxY = threadRect.maxY < scissor.y+scissor.h ? threadRect.maxY : scissor.y+scissor.h;
    
    s32 startX = centerX - radius;
    s32 startY = centerY - radius;
    
    if(startX < minX) { startX = minX; }
    if(startY < minY) { startY = minY; }
    
    s32 endX   = centerX + radius;
    s32 endY   = centerY + radius;
    
    if(endX > maxX) { endX = maxX+1; }
    if(endY > maxY) { endY = maxY+1; }
    
    u32 *At = (u32 *)win->drawBuffer;
    for(s32 y = startY; y < endY; y++)
    {
        for(s32 x = startX; x < endX; x++)
        {
            s32 cX = x - centerX;
            s32 cY = y - centerY;
            
            b32 cond = (cY*cY + cX*cX) <= (radius*radius);
            
            if(cond)
            {
                f32 saturation = ls_sqrt(cX*cX + cY*cY) / (f32)radius;
                saturation     = ls_clamp(saturation*1.00f, 1.0f, 0.0f);
                
                f32 angle = ls_atan2((f32)cY, (f32)cX) / PI;
                s32 hue   = (angle*180) + 179;
                
                Color converted = ls_uiHSVtoRGB(hue, saturation, value);
                
                Color base         = { .value = At[y*win->width + x] };
                Color blendedColor = ls_uiAlphaBlend(converted, base);
                At[y*win->width + x] = blendedColor.value;
            }
        }
    }
    
#endif
}


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
