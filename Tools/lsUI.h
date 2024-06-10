#ifndef LS_UI_H
#define LS_UI_H

/*TODOs
-Implement the OpenGL backend

-Premultiplied Alpha

-8 Render Threads
-Maybe pre-compute thread rects and collapse even further the pushRenderCommand function sub-switch cases.

-@Alpha-Un-Multiply
-Fix pre-multiplied alpha for LightenRGB and DarkenRGB
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


const     u32 THREAD_COUNT       = 8;
constexpr u32 RENDER_GROUP_COUNT = THREAD_COUNT == 0 ? 1 : THREAD_COUNT;

//-------------------------
//NOTE: Color RGBA stuff

union Color
{
    struct { u32 value; };
    struct { u8 b, g, r, a; };
};

Color RGBA(u8 r, u8 g, u8 b, u8 a)
{ 
    f32 floatAlpha = (f32)a / 255.0f;
    Color res      = { .b = (u8)(b*floatAlpha), .g = (u8)(g*floatAlpha), .r = (u8)(r*floatAlpha), .a = a };
    return res;
}

Color RGB(u8 r, u8 g, u8 b)
{ 
    Color res = { .b = b, .g = g, .r = r, .a = 0xFF };
    return res;
}

Color RGBg(u8 v)
{ 
    Color res = { .b = v, .g = v, .r = v, .a = 0xFF };
    return res;
}

Color ls_uiAlphaPremultiply(Color source)
{
    f32 fAlpha = (f32)source.a / 255.0f;
    Color Result = {
        .b = (u8)(source.b*fAlpha),
        .g = (u8)(source.g*fAlpha),
        .r = (u8)(source.r*fAlpha),
        .a = source.a
    };
    return Result;
}

Color SetAlpha(Color v, u8 a)
{ 
    f32 alphaConv = ((f32)a / (f32)v.a);
    Color res     = { .b = (u8)(v.b*alphaConv), .g = (u8)(v.g*alphaConv), .r = (u8)(v.r*alphaConv), .a = a };
    return res;
}

u8 GetAlpha(Color v)
{ return v.a; }

//NOTE: Color RGBA stuff
//-------------------------

//TODO: The difference between how the command rect and the thread rect's members are used is confusing
//      and error prone. One uses x,y,w,h. The other uses minX,minY,maxX,maxY. @ConfusingUnion
//      Should probably have 2 different types:
//      UIRect       should use (x,y,w,h)
//      UIRectRange? should use (minX,minY,maxX,maxY) 
union UIRect
{
    struct { s32 minX, minY, maxX, maxY; };
    struct { s32 x,    y,    w,    h; };
    struct { f32 leftX, botY, rightX, topY; };
};

struct UILayoutRect
{
    s32 minX, minY, maxX, maxY;
    s32 startX, startY;
};

struct UIGlyph
{
    u8 *data;
    //u32 size;
    
    u32 width;
    u32 height;
    
    s32 x0, x1;
    s32 y0, y1;
    
    s32 xAdv;
    s32 yAdv;
};

enum UIFontSize
{
    FS_SMALL = 0,
    FS_MEDIUM = 1,
    FS_LARGE = 2,
    FS_EXTRALARGE = 3
};

//TODO: Add max descent of font to adjust text vertical position in text boxes.
struct UIFont
{
    //NOTE: Either the font is loaded as a collection of glyph bitmaps at a specific size
    //      Or it's loaded as a single large bitmap, the font atlas, which right now can only be in SDF format
    union {
        UIGlyph *glyph;
        u8 *fontAtlasSDF;
    };
    
    u32 pixelHeight;
    u32 maxCodepoint;
    s32 ascent;
    s32 descent;
    s32 lineGap;
    s32 cpCount;
    
    //NOTE: The kernAdvanceTable may be null!
    s32 **kernAdvanceTable;
    
    //NOTETODO: Currently we determine if we're working with an atlas or a glyph array through this boolean
    //          Tagged unions would be cool.
    b32 isAtlas;
    s32 atlasWidth;
    s32 atlasHeight;
    
#ifdef LS_UI_OPENGL_BACKEND
    //NOTE: As of right now OpenGL expects the font to be loaded as an SDFAtlas, uploaded to the gpu as a single
    //      large bitmap, represented by this texture ID.
    GLuint texID;
#endif
};

struct UILPane
{
    u32 dtOpen;
    b32 isOpening;
    b32 isOpen;
};

struct UIBitmap
{
    void *data;
    s32   w;
    s32   h;
    
#ifdef LS_UI_OPENGL_BACKEND
    GLuint texID;
#endif
};

struct UIContext;

//NOTE: Base Struct for all UI elements
//      The reason it's made as a define is so that the entire anonymous struct definition 
//      Will be copy-pasted inside each Widget's body. This way each widget can access all element of the
//      Base struct without having to refer to it by name (like if it was a substruct).
//
//      C-style inheritance without access_control, constructors, dynamic_dispatch etc. Just PODs.

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
}                                                                                                 \


enum UIButtonStyle { UIBUTTON_CLASSIC, UIBUTTON_LINK, UIBUTTON_TEXT_NOBORDER, UIBUTTON_NO_TEXT, UIBUTTON_BMP };
struct UIButton
{
    //NOTE: callback1 -> onClick; callback2 -> onHold
    UIWidget_Base;
    
    //TODO: With the current design I have to select the font in 2 different places.
    //      The best solution is probably to just hold a pointer to the font to be used in the 
    //      Button itself (And all other text widgets as well...)
    UIButtonStyle style;
    
    utf32 name;
    u8 *bmpData;
    s32 w, h;
    
    b32 isHot;
    b32 isHeld;
    
    //NOTE: When this is set, the button is drawn greyed out, and
    //      the user can't interact with it.
    b32 isInactive;
};

enum UICheckStyle { UICHECK_BMP };
struct UICheck
{
    //NOTE: callback1 -> onClick; callback2 -> UNUSED
    UIWidget_Base;
    
    UICheckStyle style;
    
    b32 isActive;
    
    //TODO: UIBitmap
    u8 *bmpActive;
    u8 *bmpInactive;
    s32 w, h;
    
    u8 *bmpAdditive;
    s32 addW, addH;
};

enum UITextBoxAlignment : u8
{
    UI_TB_ALIGN_LEFT = 0,
    UI_TB_ALIGN_RIGHT,
    UI_TB_ALIGN_CENTER
};

struct UITextBox
{
    //NOTE: callback1 -> preInput; callback2 -> postInput
    UIWidget_Base;
    
    UITextBoxAlignment align;
    
    utf32 text;
    u32 maxLen; // maxLen == 0 means it is ignored. No max Len.
    
    b32 isSingleLine;
    b32 isReadonly;
    
    s32 lineCount;
    s32 currLineBeginIdx;
    
    u32 dtCaret;
    b32 isCaretOn;
    s32 caretIndex;
    s32 caretLineIdx;
    
    //NOTE:TODO: Call this viewMinIdx;
    s32 viewBeginIdx;
    
    s32 selectBeginLine;
    s32 selectEndLine;
    s32 selectBeginIdx;
    s32 selectEndIdx;
    b32 isSelecting;
};

enum UIArrowSide { UIA_LEFT, UIA_RIGHT, UIA_UP, UIA_DOWN };

struct UIListBoxItem
{
    utf32 name;
    Color bkgColor;
    Color textColor;
};

struct UIListBox
{
    //NOTE: callback1 -> onSelect; callback2 -> UNUSED
    UIWidget_Base;
    
    FixedArray<UIListBoxItem> list;
    s32 selectedIndex;
    
    u32 dtOpen;
    b32 isOpening;
    b32 isOpen;
    
    Color arrowBkg;
};


enum SliderStyle { SL_LINE, SL_BOX };

struct UISlider
{
    //NOTE: callback1 -> UNUSED; callback2 -> UNUSED
    UIWidget_Base;
    
    b32 isHot;
    b32 isHeld;
    
    utf32 text;
    
    s32 currValue;
    s32 maxValue;
    s32 minValue;
    
    f64 currPos;
    
    SliderStyle style;
    Color lColor;
    Color rColor;
};

struct UIColorPicker
{
    //NOTE: callback1 -> onClick; callback2 -> UNUSED
    UIWidget_Base;
    
    s32 valueRectX;
    s32 valueRectY;
    s32 valueRectW;
    s32 valueRectH;
    f32 value;
    
    s32 centerX;
    s32 centerY;
    s32 radius;
    
    b32   hasPicked;
    s32   pickedX;
    s32   pickedY;
    Color pickedColor;
    
    UIButton apply;
};

struct UIMenuItem
{
    //NOTE: callback1 -> onClick; callback2 -> UNUSED
    UIWidget_Base;
    
    utf32 name;
    
    b32 isVisible;
    b32 isHot;
};

struct UISubMenu
{
    utf32 name;
    Array<UIMenuItem> items;
    
    b32 isHot;
};

//TODO: Very Shitty implementation of Menus
struct UIMenu
{
    UIButton          closeWindow;
    UIButton          minimize;
    
    Array<UISubMenu>  subMenus;
    b32               isOpen;
    s32               openIdx;
    
    Array<UIMenuItem> items;
    
    s32               itemWidth;
    
    //TODO: Add bkgColor and textColor
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
    
#if _DEBUG
    b32 isTagged;
    s32 UID;
#endif
};

#ifndef LS_UI_OPENGL_BACKEND
const u32 UI_Z_LAYERS = 4;

struct RenderGroup
{
    stack RenderCommands[UI_Z_LAYERS];
    volatile b32 isDone;
};
#endif

struct UIContext;
typedef void (*RenderCallback)(UIContext *);
typedef void (*onDestroyFunc)(UIContext *);
struct UIContext
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
    
#if 0
    //NOTE: This is sligtly smaller than the draw area, because it doesn't include the menu bar
    s32 clientWidth;
    s32 clientHeight;
#endif
    
    UIFont *fonts;
    u32 numFonts;
    
    UIFont *currFont;
    u32 currPixelHeight;
    
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
    
    u64 *currentFocus;
    u64 *lastFocus;
    b32 focusWasSetThisFrame;
    
    b32 nextFrameFocusChange;
    u64 *nextFrameFocus;
    
    u64 *mouseCapture;
    
#ifndef LS_UI_OPENGL_BACKEND
    RenderGroup renderGroups[RENDER_GROUP_COUNT];
    UIRect      renderUIRects[THREAD_COUNT];
    
    CONDITION_VARIABLE startRender;
    CRITICAL_SECTION crit;
#endif
    
    HDC  WindowDC;
    HDC  BackBufferDC;
    HBITMAP DibSection;
    
#if _DEBUG //NOTE: Tag to debug specific render commands
    b32 isTagged;
#endif
    
    //IMPORTANT NOTE:
    // As of right now lsUI DEPENDS on Input.
    // I don't know if this is the right choice. I guess I'll discover it.
    Input UserInput;
    
    RenderCallback renderFunc;
    u32 dt;
    RegionTimer frameTime;
    
    HWND Window;
    
    s32 windowPosX, windowPosY;
    b32 isDragging;
    s32 prevMousePosX, prevMousePosY;
    
    b32 hasReceivedInput;
    
    Arena frameArena;
    Arena contextArena;
    Arena widgetArena;
    
    onDestroyFunc onDestroy;
};

struct ___threadCtx
{
    UIContext *c;
    u64 ThreadID;
};


//NOTE: Functions

HWND         ls_uiCreateWindow(HINSTANCE MainInstance, UIContext *c, const char *name);
HWND         ls_uiCreateWindow(UIContext *c, const char *name);
UIContext *  ls_uiInitDefaultContext(u8 *drawBuffer, u32 width, u32 height,
                                     s32 contextArenaSize, s32 frameArenaSize, s32 widgetArenaSize, RenderCallback cb);
UIContext *  ls_uiInitDefaultContext(u8 *backBuffer, u32 width, u32 height,
                                     Arena contextArena, Arena frameArena, Arena widgetArena, RenderCallback cb);

void         ls_uiFrameBegin(UIContext *c);
void         ls_uiFrameBeginChild(UIContext *c);
void         ls_uiFrameEnd(UIContext *c, u64 frameTimeTargetMs);
void         ls_uiFrameEndChild(UIContext *c, u64 frameTimeTargetMs);

void         ls_uiLoadPackedFontAtlas(UIContext *c, char *path);
UIBitmap     ls_uiBitmapFromRGBAPixelData(UIContext *c, s32 w, s32 h, void *data);

void         ls_uiAddOnDestroyCallback(UIContext *c, onDestroyFunc f);

void         ls_uiPushRenderCommand(UIContext *c, RenderCommand command, s32 zLayer);
void         ls_uiStartScrollableRegion(UIContext *c, UIScrollableRegion *scroll);
void         ls_uiEndScrollableRegion(UIContext *c);
void         ls_uiResetScrollableRegion(UIContext *c);

void         ls_uiFocusChangeSameFrame(UIContext *c, u64 *focus);
void         ls_uiFocusChange(UIContext *c, u64 *focus);
b32          ls_uiInFocus(UIContext *c, void *p);
b32          ls_uiHasCapture(UIContext *c, void *p);
void         ls_uiSelectFontByPixelHeight(UIContext *c, u32 pixelHeight);
s32          ls_uiSelectFontByFontSize(UIContext *c, UIFontSize fontSize);

UIRect       ls_uiScreenCoordsToUnitSquare(UIContext *c, s32 x, s32 y, s32 w, s32 h);

Color        ls_uiDarkenRGB(Color c, f32 percentage);
Color        ls_uiLightenRGB(Color c, f32 percentage);
Color        ls_uiAlphaBlend(Color source, Color dest, u8 alpha);
Color        ls_uiAlphaBlend(Color source, Color dest);
Color        ls_uiRGBAtoARGB(Color c);
Color        ls_uiARGBtoRGBA(Color c);

template<typename T> UIRect ls_uiGlyphStringRect(UIContext *c, UIFont *font, T text, s32 pixelHeight);

void         ls_uiRect(UIContext *c, s32 x, s32 y, s32 w, s32 h, Color bkgColor, Color borderColor, s32 zLayer);

void         ls_uiHSeparator(UIContext *c, s32 x, s32 y, s32 width, s32 lineWidth, Color lineColor, s32 zLayer);
void         ls_uiVSeparator(UIContext *c, s32 x, s32 y, s32 height, s32 lineWidth, Color lineColor, s32 zLayer);

UIButton     ls_uiButtonInit(UIContext *c, UIButtonStyle s, UICallback onClick, UICallback onHold, void *data);
UIButton     ls_uiButtonInit(UIContext *c, UIButtonStyle s, const char32_t *text, UICallback onClick,
                             UICallback onHold, void *userData);
UIButton     ls_uiButtonInit(UIContext *c, UIButtonStyle s, utf32 text, 
                             UICallback onClick, UICallback onHold, void *data);
UIButton     ls_uiButtonInit(UIContext *c, UIButtonStyle s, const char32_t *text,
                             UICallback onClick, UICallback onHold, void *data);
void         ls_uiButtonInit(UIContext *c, UIButton *b, UIButtonStyle s, utf32 t,
                             UICallback onClick, UICallback onHold, void *data);
void         ls_uiButtonInit(UIContext *c, UIButton *, UIButtonStyle, const char32_t *t,
                             UICallback onClick, UICallback onHold, void *data);

b32          ls_uiButton(UIContext *c, UIButton *button, s32 xPos, s32 yPos, Color bkgColor, s32 zLayer);
b32          ls_uiButton(UIContext *c, UIButton *button, s32 xPos, s32 yPos, s32 zLayer);


UICheck      ls_uiCheckInit(UIContext *c, UICheckStyle s,
                            u8 *bmpActive, u8 *bmpInactive, s32 w, s32 h, UICallback onChange, void *data);
UICheck      ls_uiCheckInit(UIContext *c, UICheckStyle s, u8 *bmpInactive, s32 w, s32 h,
                            u8 *bmpAdditive, s32 addW, s32 addH, UICallback onChange, void *data);

void         ls_uiLabelInRect(UIContext *c, utf8 label, s32 xPos, s32 yPos,
                              Color bkgColor, Color borderColor, Color textColor, s32 zLayer);
void         ls_uiLabelInRect(UIContext *c, utf8 label, s32 xPos, s32 yPos, s32 minWidth, s32 minHeight,
                              Color bkgColor, Color borderColor, Color textColor, s32 zLayer);

UILayoutRect ls_uiLabelLayout(UIContext *c, utf32 label, UILayoutRect layout, UIRect deltaPos, Color textColor, s32 zLayer);
UILayoutRect ls_uiLabelLayout(UIContext *c, utf32 label, UILayoutRect layout, Color textColor, s32 zLayer);
UILayoutRect ls_uiLabelLayout(UIContext *c, const char32_t *label, UILayoutRect layout, Color textColor, s32 zLayer);
UILayoutRect ls_uiLabelLayout(UIContext *c, utf32 label, UILayoutRect layout, s32 zLayer);
UILayoutRect ls_uiLabelLayout(UIContext *c, const char32_t *label, UILayoutRect layout, s32 zLayer);

void         ls_uiLabel(UIContext *c, utf32 label, f32 relX, f32 relY, Color textColor, s32 zLayer);
void         ls_uiLabel(UIContext *c, utf32 label, s32 xPos, s32 yPos, Color textColor, s32 zLayer);
void         ls_uiLabel(UIContext *c, const char32_t *label, s32 xPos, s32 yPos, Color textColor, s32 zLayer);
void         ls_uiLabel(UIContext *c, utf8 label, s32 xPos, s32 yPos, Color textColor, s32 zLayer);
void         ls_uiLabel(UIContext *c, const u8 *label, s32 xPos, s32 yPos, Color textColor, s32 zLayer);

void         ls_uiLabel(UIContext *c, utf32 label, s32 xPos, s32 yPos, s32 zLayer);
void         ls_uiLabel(UIContext *c, const char32_t *label, s32 xPos, s32 yPos, s32 zLayer);
void         ls_uiLabel(UIContext *c, utf8 label, s32 xPos, s32 yPos, s32 zLayer);
void         ls_uiLabel(UIContext *c, const u8 *label, s32 xPos, s32 yPos, s32 zLayer);

void         ls_uiTextBoxClear(UIContext *c, UITextBox *box);
void         ls_uiTextBoxSet(UIContext *c, UITextBox *box, const char32_t *s);
void         ls_uiTextBoxSet(UIContext *c, UITextBox *box, utf32 s);
void         ls_uiTextBoxInit(UIContext *c, UITextBox *box, s32 initialCap, s32 maxLen, b32 singleLine, 
                              b32 readOnly, UICallback preInput, UICallback postInput);
b32          ls_uiTextBox(UIContext *c, UITextBox *box, s32 xPos, s32 yPos, s32 w, s32 h, s32 zLayer);

UIListBox    ls_uiListBoxInit(UIContext *c, s32 maxItemCount);
//NOTE: This does NOT allocate memory for the string
u32          ls_uiListBoxAddEntry(UIContext *c, UIListBox *list, utf32 s);
//NOTE: This does NOT free the memory of the string
void         ls_uiListBoxRemoveEntry(UIContext *c, UIListBox *list, u32 index);
b32          ls_uiListBox(UIContext *c, UIListBox *list, s32 xPos, s32 yPos, s32 w, s32 h, u32 zLayer);

UISlider     ls_uiSliderInit(UIContext *c, char32_t *name, s32 maxVal, s32 minVal, 
                             f64 currPos, SliderStyle s, Color l, Color r);
void         ls_uiSliderChangeValueBy(UIContext *c, UISlider *f, s32 valueDiff);
s32          ls_uiSliderCalculateValueFromPosition(UIContext *c, UISlider *f);
b32          ls_uiSlider(UIContext *c, UISlider *slider, s32 xPos, s32 yPos, s32 w, s32 h);

UIButton     ls_uiMenuButton(UICallback onClick, u8 *bitmapData, s32 width, s32 height);
UISubMenu  * ls_uiMenuAddSub(UIContext *c, UIMenu *menu, UISubMenu sub);
UISubMenu  * ls_uiMenuAddSub(UIContext *c, UIMenu *menu, const char32_t *name);
UIMenuItem * ls_uiMenuAddItem(UIContext *c, UIMenu *menu, const char32_t *name, UICallback onClick, void *userData);
UIMenuItem * ls_uiSubMenuAddItem(UIContext *c, UISubMenu *sub, const char32_t *name, UICallback onClick, void *userData);
UIMenuItem * ls_uiSubMenuAddItem(UIContext *c, UIMenu *menu, u32 subIdx, const char32_t *name, UICallback onClick, void *data);
b32          ls_uiMenu(UIContext *c, UIMenu *menu, s32 x, s32 y, s32 w, s32 h, s32 zLayer);

void         ls_uiTexturedRect(UIContext *c, s32 x, s32 y, s32 w, s32 h, void *data, s32 dataW, s32 dataH, s32 zLayer);

UIColorPicker ls_uiColorPickerInit(UIContext *c, void *userData);

void         ls_uiRender(UIContext *c);

#if _DEBUG
void         ls_uiDebugLog(UIContext *c, s32 x, s32 y, const char *fmt, ...);
#endif

#endif


#ifdef LS_UI_IMPLEMENTATION


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

void ls_uiBorder(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h, UIRect threadRect, UIRect scissor, Color col);
template<typename T>
void ls_uiGlyphString(UIContext *c, UIFont *font, s32 pixelHeight, s32 xPos, s32 yPos,
                      UIRect threadRect, UIRect scissor, T text, Color textColor);
void ls_uiDebugDrawInfo(UIContext *c)
{
#ifndef LS_UI_OPENGL_BACKEND
    for(s32 i = 0; i < THREAD_COUNT; i++)
    {
        UIRect r = c->renderUIRects[i];
        ls_uiBorder(c, r.minX, r.minY, r.maxX - r.minX, r.maxY - r.minY, 
                    {0, 0, c->width, c->height}, {0,0,c->width,c->height}, 
                    RGB(253, 0, 255));
    }
#endif
    
    u32 buff[64]    = {};
    utf32 frameTime = { buff, 0, 64 };
    ls_utf32FromInt_t(&frameTime, c->dt);
    
    ls_uiGlyphString(c, c->currFont, 16, (s32)(0.95f*c->width), (s32)(0.95f*c->height),
                     {0, 0, c->width, c->height}, {0,0,c->width,c->height}, frameTime, c->textColor);
}

#endif //_DEBUG

#ifndef LS_UI_OPENGL_BACKEND
void __ls_ui_fillRenderThreadUIRects(UIContext *c)
{
    //NOTE: All Thread Rects are inclusive on the left/bot, exclusive on the right/top
    switch(THREAD_COUNT)
    {
        case 0:
        case 1: { c->renderUIRects[0] = {0, 0, c->width, c->height }; } break;
        
        case 2:
        {
            c->renderUIRects[0] = {          0, 0, c->width/2, c->height };
            c->renderUIRects[1] = { c->width/2, 0, c->width,   c->height };
        } break;
        
        case 4:
        {
            c->renderUIRects[0] = {          0,           0, c->width/2, c->height/2 };
            c->renderUIRects[1] = { c->width/2,           0, c->width,   c->height/2 };
            c->renderUIRects[2] = {          0, c->height/2, c->width/2, c->height   };
            c->renderUIRects[3] = { c->width/2, c->height/2, c->width,   c->height   };
        } break;
        
        case 8:
        {
            c->renderUIRects[0] = {            0,           0,   c->width/4, c->height/2 };
            c->renderUIRects[1] = {   c->width/4,           0,   c->width/2, c->height/2 };
            c->renderUIRects[2] = {   c->width/2,           0, 3*c->width/4, c->height/2 };
            c->renderUIRects[3] = { 3*c->width/4,           0,   c->width,   c->height/2 };
            c->renderUIRects[4] = {            0, c->height/2,   c->width/4, c->height   };
            c->renderUIRects[5] = {   c->width/4, c->height/2,   c->width/2, c->height   };
            c->renderUIRects[6] = {   c->width/2, c->height/2, 3*c->width/4, c->height   };
            c->renderUIRects[7] = { 3*c->width/4, c->height/2,   c->width,   c->height   };
        } break;
        
        default: { AssertMsg(FALSE, "Unhandled Thread Count"); } break;
    }
    
    return;
}
#endif

LRESULT ls_uiWindowProc(HWND h, UINT msg, WPARAM w, LPARAM l)
{
    LRESULT Result = 0;
    
    UIContext *c      = (UIContext *)GetWindowLongPtrA(h, GWLP_USERDATA);;
    MouseInput *Mouse = &c->UserInput.Mouse;
    Input *UserInput  = &c->UserInput;
    
    //static b32 mouseTracking = FALSE;
    
    switch (msg)
    {
        case WM_ERASEBKGND: return TRUE; break;
        
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
            c->hasReceivedInput = TRUE;
            
        } break;
        
        case WM_ACTIVATE:
        {
            if(w == WA_INACTIVE) { 
                //SendMessageA(c->MainWindow, WM_LBUTTONUP, 0, 0);
                //TODO: Maybe NULL everything in the deactivated window? Input should not matter there anymore
                c->UserInput.Keyboard.currentState    = {};
                c->UserInput.Keyboard.prevState       = {};
                c->UserInput.Keyboard.repeatState     = {};
                c->UserInput.Keyboard.hasPrintableKey = FALSE;
                
                c->UserInput.Mouse.isLeftPressed    = FALSE;
                c->UserInput.Mouse.wasLeftPressed   = FALSE;
                c->UserInput.Mouse.isMiddlePressed  = FALSE;
                c->UserInput.Mouse.wasMiddlePressed = FALSE;
                c->UserInput.Mouse.isRightPressed   = FALSE;
                c->UserInput.Mouse.wasRightPressed  = FALSE;
            }
        } break;
        
        //TODO: Handling WM_SIZING would probably produce better results.
        //TODO: This will only be used for fixed size steps
        case WM_SIZE:
        {
            if(!c || !c->drawBuffer) { return DefWindowProcA(h, msg, w, l); }
            
            u32 width       = LOWORD(l);
            u32 height      = HIWORD(l);
            
            //NOTE: Need to resize the backbuffer if the window grows.
            if(width*height > c->backbufferW*c->backbufferH)
            {
                //NOTE: Delete the old DibSection AND the old BackBufferDC
                //      Otherwise it would VERY quickly leak GBs of memory
                DeleteObject(c->DibSection);
                DeleteDC(c->BackBufferDC);
                
                //NOTE: Create a new DC
                BITMAPINFO BackBufferInfo              = {};
                BackBufferInfo.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
                BackBufferInfo.bmiHeader.biWidth       = width;
                BackBufferInfo.bmiHeader.biHeight      = height;
                BackBufferInfo.bmiHeader.biPlanes      = 1;
                BackBufferInfo.bmiHeader.biBitCount    = 32;
                BackBufferInfo.bmiHeader.biCompression = BI_RGB;
                
                c->BackBufferDC       = CreateCompatibleDC(c->WindowDC);
                c->DibSection         = CreateDIBSection(c->BackBufferDC, &BackBufferInfo,
                                                         DIB_RGB_COLORS, (void **)&(c->drawBuffer), NULL, 0);
                SelectObject(c->BackBufferDC, c->DibSection);
                
                c->backbufferW = width;
                c->backbufferH = height;
            }
            
            //NOTE: Draw Buffer Dimensions
            c->width        = width;
            c->height       = height;
#if 0
            //NOTE: Client window dimensions
            c->windowWidth  = (s32)width;
            c->windowHeight = (s32)height;
#endif
            
            //NOTE: Client window position.
            RECT windowRect = {};
            if(GetWindowRect(h, &windowRect) != 0)
            {
                c->windowPosX = windowRect.left;
                c->windowPosY = windowRect.top;
            }
            else { LogMsg(FALSE, "GetWindowRect failed after resize."); }
            
            //NOTE: Mouse position
            POINT currMouse = {};
            if(GetCursorPos(&currMouse) != 0)
            {
                c->prevMousePosX = currMouse.x;
                c->prevMousePosY = currMouse.y;
            }
            else { LogMsg(FALSE, "GetCursorPos failed after resize."); }
            
#ifndef LS_UI_OPENGL_BACKEND
            //NOTE: Reset the Render UIRect for every Thread.
            __ls_ui_fillRenderThreadUIRects(c);
#endif
        } break;
        
        case WM_PAINT:
        {
            PAINTSTRUCT ps = {};
            RECT r;
            
            //NOTE: I have to call BeginPaint() - EndPaint() Anyway.
            //If I don't, the message loop is gonna get stuck in PAINT calls.
            BeginPaint(h, &ps);
            
            //NOTE: Draw Background
            GetClientRect(h, &r);
            
            BITMAPINFO BitmapInfo = {};
            BitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            BitmapInfo.bmiHeader.biWidth = c->width;
            BitmapInfo.bmiHeader.biHeight = c->height;
            BitmapInfo.bmiHeader.biPlanes = 1;
            BitmapInfo.bmiHeader.biBitCount = 32;
            BitmapInfo.bmiHeader.biCompression = BI_RGB;
            
            StretchDIBits(c->BackBufferDC, 0, 0, c->width, c->height,
                          0, 0, c->width, c->height,
                          c->drawBuffer, &BitmapInfo, DIB_RGB_COLORS, SRCCOPY);
            
            Result = BitBlt(c->WindowDC, 0, 0, c->width, c->height, c->BackBufferDC, 0, 0, SRCCOPY);
            
            if(Result == 0) {
                DWORD Err = GetLastError();
                int breakHere = 0;
            }
            
            EndPaint(h, &ps);
        } break;
        
        case WM_CHAR:
        {
            c->hasReceivedInput = TRUE;
            
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
            c->hasReceivedInput = TRUE;
            
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
                case 'C':        KeySetAndRepeat(keyMap::C, rep);         break;
                case 'D':        KeySetAndRepeat(keyMap::D, rep);         break;
                case 'G':        KeySetAndRepeat(keyMap::G, rep);         break;
                case 'S':        KeySetAndRepeat(keyMap::S, rep);         break;
                case 'V':        KeySetAndRepeat(keyMap::V, rep);         break;
                case 'W':        KeySetAndRepeat(keyMap::W, rep);         break;
                case 'Y':        KeySetAndRepeat(keyMap::Y, rep);         break;
                case 'Z':        KeySetAndRepeat(keyMap::Z, rep);         break;
            }
            
        } break;
        
        case WM_KEYUP:
        {
            c->hasReceivedInput = TRUE;
            
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
                case 'C':        KeyUnset(keyMap::C);         break;
                case 'D':        KeyUnset(keyMap::D);         break;
                case 'G':        KeyUnset(keyMap::G);         break;
                case 'S':        KeyUnset(keyMap::S);         break;
                case 'V':        KeyUnset(keyMap::V);         break;
                case 'W':        KeyUnset(keyMap::W);         break;
                case 'Y':        KeyUnset(keyMap::Y);         break;
                case 'Z':        KeyUnset(keyMap::Z);         break;
            }
        } break;
        
        case WM_LBUTTONDOWN:
        {
            c->hasReceivedInput  = TRUE;
            Mouse->isLeftPressed = TRUE;
            return 0;
        } break;
        
        case WM_LBUTTONUP:
        {
            c->hasReceivedInput  = TRUE;
            Mouse->isLeftPressed = FALSE;
            return 0;
        } break;
        
        case WM_RBUTTONDOWN:
        { 
            c->hasReceivedInput   = TRUE;
            Mouse->isRightPressed = TRUE;
            return 0;
        } break;
        
        case WM_RBUTTONUP:
        { 
            c->hasReceivedInput   = TRUE; 
            Mouse->isRightPressed = FALSE;
            return 0;
        } break;
        
        /*
        case WM_MOUSELEAVE:
        {
            mouseTracking = FALSE;
            
            c->UserInput.Mouse.isLeftPressed    = FALSE;
            c->UserInput.Mouse.isMiddlePressed  = FALSE;
            c->UserInput.Mouse.isRightPressed   = FALSE;
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
            Mouse->currPosY = c->height - currMouseClient.y;
            
            c->hasReceivedInput = TRUE;
            
            
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
            c->hasReceivedInput   = TRUE;
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
    
    //NOTE: We load the cursor after creating the window, 
    //      otherwise windows will reset it to this default after every MOUSEMOVE event if we ever change it.
    WindowClass.hCursor = NULL;
    
    if (!RegisterClassA(&WindowClass))
    {
        DWORD Error = GetLastError();
        ls_printf("When Registering WindowClass in Win32_SetupScreen got error: %d", Error);
    }
}

HWND __ui_CreateWindow(HINSTANCE MainInstance, UIContext *c, const char *windowName)
{
    u32 style = LS_THIN_BORDER | LS_POPUP;// | LS_VISIBLE; //| LS_OVERLAPPEDWINDOW;
    BOOL Result;
    
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int screenWidth  = GetSystemMetrics(SM_CXSCREEN);
    
    const int taskbarHeight = 20;
    
    int spaceX = (screenWidth - c->backbufferW) / 2;
    int spaceY = ((screenHeight - c->backbufferH) / 2);// - taskbarHeight;
    if(spaceX < 0) { spaceX = 0; }
    if(spaceY < 0) { spaceY = 0; }
    
    //NOTE: We repliacate windowName in both the windowClass name and the actual window name, to avoid conflict
    //      when creating multiple windows under the same process.
    HWND WindowHandle;
    if ((WindowHandle = CreateWindowExA(0 /*WS_EX_LAYERED*/, windowName, windowName, style,
                                        spaceX, spaceY, c->backbufferW, c->backbufferH,
                                        0, 0, MainInstance, c)) == nullptr)
    {
        DWORD Error = GetLastError();
        ls_printf("When Retrieving a WindowHandle in Win32_SetupScreen got error: %d", Error);
    }
    
    HCURSOR DefaultArrow = LoadCursorA(NULL, IDC_ARROW);
    SetCursor(DefaultArrow);
    
#ifdef LS_UI_OPENGL_BACKEND
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
        PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
        32,                   // Colordepth of the framebuffer.
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        24,                   // Number of bits for the depthbuffer
        8,                    // Number of bits for the stencilbuffer
        0,                    // Number of Aux buffers in the framebuffer.
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };
    
    c->WindowDC = GetDC(WindowHandle);
    s32 windowsChosenFormat = ChoosePixelFormat(c->WindowDC, &pfd);
    SetPixelFormat(c->WindowDC, windowsChosenFormat, &pfd);
    
    HGLRC wglRenderingContext = wglCreateContext(c->WindowDC);
    if(wglRenderingContext == NULL)
    {
        ls_log("Error Code: {s32}", GetLastError());
    }
    AssertNonNull(wglRenderingContext);
    wglMakeCurrent(c->WindowDC, wglRenderingContext);
    //ls_glLoadFunc(c->WindowDC);
    ls_log("OpenGL Version: {char*}", (char *)glGetString(GL_VERSION));
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
#else
    
    BITMAPINFO BackBufferInfo = {};
    BackBufferInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    BackBufferInfo.bmiHeader.biWidth = c->backbufferW;
    BackBufferInfo.bmiHeader.biHeight = c->backbufferH;
    BackBufferInfo.bmiHeader.biPlanes = 1;
    BackBufferInfo.bmiHeader.biBitCount = 32;
    BackBufferInfo.bmiHeader.biCompression = BI_RGB;
    
    c->WindowDC           = GetDC(WindowHandle);
    c->BackBufferDC       = CreateCompatibleDC(c->WindowDC);
    c->DibSection         = CreateDIBSection(c->BackBufferDC, &BackBufferInfo,
                                             DIB_RGB_COLORS, (void **)&(c->drawBuffer), NULL, 0);
    SelectObject(c->BackBufferDC, c->DibSection);
#endif
    
    c->windowPosX = (s16)spaceX;
    c->windowPosY = (s16)spaceY;
    
    return WindowHandle;
}

HWND ls_uiCreateWindow(HINSTANCE MainInstance, UIContext *c, const char *name)
{
    __ui_RegisterWindow(MainInstance, name);
    
    c->UserInput.Keyboard.getClipboard = windows_GetClipboard;
    c->UserInput.Keyboard.setClipboard = windows_SetClipboard;
    
    c->Window = __ui_CreateWindow(MainInstance, c, name);
    
    return c->Window;
}

HWND ls_uiCreateWindow(UIContext *c, const char *name)
{
    HINSTANCE MainInstance = NULL;
    __ui_RegisterWindow(MainInstance, name);
    
    c->UserInput.Keyboard.getClipboard = windows_GetClipboard;
    c->UserInput.Keyboard.setClipboard = windows_SetClipboard;
    
    c->Window = __ui_CreateWindow(MainInstance, c, name);
    
    return c->Window;
}

#ifndef LS_UI_OPENGL_BACKEND
void ls_uiRender__(UIContext *c, u32 threadID);
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
    SwapBuffers(c->WindowDC);
#else
#if 1
    InvalidateRect(c->Window, NULL, TRUE);
#else
    //TODO: Works but appears transparent? My alpha is not being used?
    BLENDFUNCTION BlendFunc = { 
        .BlendOp = AC_SRC_OVER, 
        .BlendFlags = 0, 
        .SourceConstantAlpha = 0xFF, 
        .AlphaFormat = AC_SRC_ALPHA
    };
    
    if(UpdateLayeredWindow(c->Window, NULL, NULL, NULL, c->BackBufferDC, NULL, NULL, &BlendFunc, ULW_ALPHA) == 0)
    {
        DWORD Error = GetLastError();
        AssertMsgF(FALSE, "When Updating a Layered Window got error: %d", Error);
    }
#endif
    
#endif //LS_UI_OPENGL_BACKEND
}

UIContext *ls_uiInitDefaultContext(u8 *backBuffer, u32 width, u32 height,
                                   Arena contextArena, Arena frameArena, Arena widgetArena,
                                   RenderCallback cb = __ui_default_windows_render_callback)
{
    ls_arenaUse(contextArena);
    
    UIContext *uiContext       = (UIContext *)ls_alloc(sizeof(UIContext));
    uiContext->contextArena    = contextArena;
    uiContext->frameArena      = frameArena;
    uiContext->widgetArena     = widgetArena;
    uiContext->drawBuffer      = backBuffer;
    
    uiContext->backbufferW     = width;
    uiContext->backbufferH     = height;
    
    uiContext->width           = width;
    uiContext->height          = height;
    
#if 0
    //TODO: These are initially set to 0, but are set when a ls_uiMenu call is given
    uiContext->clientWidth     = 0;
    uiContext->clientHeight    = 0;
#endif
    
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
    
#ifndef LS_UI_OPENGL_BACKEND
    //TODO: Make number of zLayers and zLayer Storage more customizable!
    if(THREAD_COUNT != 0)
    {
        for(u32 i = 0; i < THREAD_COUNT; i++)
        {
            uiContext->renderGroups[i].RenderCommands[0] = ls_stackInit(sizeof(RenderCommand), 512);
            
            for(s32 zLayer = 1; zLayer < UI_Z_LAYERS; zLayer++)
            {
                uiContext->renderGroups[i].RenderCommands[zLayer] = ls_stackInit(sizeof(RenderCommand), 256);
            }
        }
        
        InitializeConditionVariable(&uiContext->startRender);
        InitializeCriticalSection(&uiContext->crit);
        
        for(u32 i = 0; i < THREAD_COUNT; i++)
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
    
    //NOTE: Set the Render UIRect for every Thread.
    __ls_ui_fillRenderThreadUIRects(uiContext);
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

UIContext *ls_uiInitDefaultContext(u8 *backBuffer, u32 width, u32 height,
                                   s32 contextArenaSize, s32 frameArenaSize, s32 widgetArenaSize,
                                   RenderCallback cb = __ui_default_windows_render_callback)
{
    Arena contextArena = ls_arenaCreate(contextArenaSize);
    Arena frameArena = ls_arenaCreate(frameArenaSize);
    Arena widgetArena = ls_arenaCreate(widgetArenaSize);
    return ls_uiInitDefaultContext(backBuffer, width, height, contextArena, frameArena, widgetArena, cb);
}

void ls_uiFrameBegin(UIContext *c)
{
    static b32 isStartup = TRUE;
    
    ls_arenaUse(c->frameArena);
    
    RegionTimerBegin(c->frameTime);
    
    c->UserInput.Keyboard.prevState = c->UserInput.Keyboard.currentState;
    c->UserInput.Keyboard.repeatState = {};
    
    c->UserInput.Keyboard.hasPrintableKey = FALSE;
    c->UserInput.Keyboard.keyCodepoint    = 0;
    
    c->UserInput.Mouse.prevPosX         = c->UserInput.Mouse.currPosX;
    c->UserInput.Mouse.prevPosY         = c->UserInput.Mouse.currPosY;
    c->UserInput.Mouse.wasLeftPressed   = c->UserInput.Mouse.isLeftPressed;
    c->UserInput.Mouse.wasRightPressed  = c->UserInput.Mouse.isRightPressed;
    c->UserInput.Mouse.wasMiddlePressed = c->UserInput.Mouse.isMiddlePressed;
    c->UserInput.Mouse.isWheelRotated   = FALSE;
    
    //NOTETODO: Is it possible to at the same time setting the focus this frame, and 
    //          Having a pending request for a focus change, thus executing both this and the 
    //          next if block?
    if(!c->focusWasSetThisFrame) { c->lastFocus = c->currentFocus; }
    
    c->focusWasSetThisFrame = FALSE;
    if(c->nextFrameFocusChange == TRUE)
    {
        c->lastFocus            = c->currentFocus;
        c->currentFocus         = c->nextFrameFocus;
        c->nextFrameFocusChange = FALSE;
    }
    
    if(c->lastFocus && c->currentFocus != c->lastFocus)
    {
        DummyUIWidgetBase *base = (DummyUIWidgetBase *)c->lastFocus;
        if(base->OnFocusLost) {
            base->OnFocusLost(c, base->onFocusLostData);
        }
    }
    
    c->hasReceivedInput = FALSE;
    
    // Process Input
    MSG Msg;
    while (PeekMessageA(&Msg, NULL, 0, 0, PM_REMOVE))
        //while (PeekMessageA(&Msg, c->Window, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&Msg);
        DispatchMessageA(&Msg);
    }
    
    //NOTE: Make sure previous frame click is not put on hold this frame.
    if(c->UserInput.Mouse.wasLeftPressed  ||
       c->UserInput.Mouse.wasRightPressed || 
       c->UserInput.Mouse.wasMiddlePressed)
    { c->hasReceivedInput = TRUE; }
    
    //NOTE: Window starts hidden, and then is shown after the first frame, 
    //      to avoid flashing because initially the frame buffer is all white.
    if(isStartup) { ShowWindow(c->Window, SW_SHOW); isStartup = FALSE; c->hasReceivedInput = TRUE; }
    
    Input *UserInput = &c->UserInput;
    //NOTE: Right-Alt Drag, only when nothing is in focus
    if(KeyHeld(keyMap::RAlt) && LeftClick && c->currentFocus == 0)
    { 
        c->isDragging = TRUE;
        POINT currMouse = {};
        GetCursorPos(&currMouse);
        c->prevMousePosX = currMouse.x;
        c->prevMousePosY = currMouse.y;
    }
    
    //NOTE: Handle Dragging
    if(c->isDragging && LeftHold)
    { 
        MouseInput *Mouse = &c->UserInput.Mouse;
        
        POINT currMouse = {};
        GetCursorPos(&currMouse);
        
        POINT prevMouse = { c->prevMousePosX, c->prevMousePosY };
        
        SHORT newX = prevMouse.x - currMouse.x;
        SHORT newY = prevMouse.y - currMouse.y;
        
        SHORT newWinX = c->windowPosX - newX;
        SHORT newWinY = c->windowPosY - newY;
        
        c->windowPosX = newWinX;
        c->windowPosY = newWinY;
        
        c->prevMousePosX  = currMouse.x;
        c->prevMousePosY  = currMouse.y;
        
        SetWindowPos(c->Window, 0, newWinX, newWinY, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
    }
    
    if(c->isDragging && LeftUp) { c->isDragging = FALSE; }
    
    if(LeftUp || RightUp || MiddleUp) { c->mouseCapture = 0; }
    
#ifdef LS_UI_OPENGL_BACKEND
    f64 rLinear  = ((f64)c->backgroundColor.r / 255.0);
    f64 gLinear  = ((f64)c->backgroundColor.g / 255.0);
    f64 bLinear  = ((f64)c->backgroundColor.b / 255.0);
    
    glClearColor(rLinear, gLinear, bLinear, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#endif
}

void ls_uiFrameBeginChild(UIContext *c)
{
    static b32 isStartup = TRUE;
    
    ls_arenaUse(c->frameArena);
    
    RegionTimerBegin(c->frameTime);
    
    c->UserInput.Keyboard.prevState = c->UserInput.Keyboard.currentState;
    c->UserInput.Keyboard.repeatState = {};
    
    c->UserInput.Keyboard.hasPrintableKey = FALSE;
    c->UserInput.Keyboard.keyCodepoint    = 0;
    
    c->UserInput.Mouse.prevPosX         = c->UserInput.Mouse.currPosX;
    c->UserInput.Mouse.prevPosY         = c->UserInput.Mouse.currPosY;
    c->UserInput.Mouse.wasLeftPressed   = c->UserInput.Mouse.isLeftPressed;
    c->UserInput.Mouse.wasRightPressed  = c->UserInput.Mouse.isRightPressed;
    c->UserInput.Mouse.wasMiddlePressed = c->UserInput.Mouse.isMiddlePressed;
    c->UserInput.Mouse.isWheelRotated   = FALSE;
    
    //NOTETODO: Is it possible to at the same time setting the focus this frame, and 
    //          Having a pending request for a focus change, thus executing both this and the 
    //          next if block?
    if(!c->focusWasSetThisFrame) { c->lastFocus = c->currentFocus; }
    
    c->focusWasSetThisFrame = FALSE;
    if(c->nextFrameFocusChange == TRUE)
    {
        c->lastFocus            = c->currentFocus;
        c->currentFocus         = c->nextFrameFocus;
        c->nextFrameFocusChange = FALSE;
    }
    
    if(c->lastFocus && c->currentFocus != c->lastFocus)
    {
        DummyUIWidgetBase *base = (DummyUIWidgetBase *)c->lastFocus;
        if(base->OnFocusLost) {
            base->OnFocusLost(c, base->onFocusLostData);
        }
    }
    
    c->hasReceivedInput = FALSE;
    
    //NOTE: The child frame doesn't need a message pump, because windows
    //      Pumps messages to all windows that were created by this thread.
    //      BUT This means that we must begin the child frame before the main frame
    //      to properly clear input.
    //      TODO: Maybe we want to move the message pump to a separate function
    //      to make the order of function calls more obvious and less error prone!
    
    if(isStartup) { isStartup = FALSE; c->hasReceivedInput = TRUE; }
    
    Input *UserInput = &c->UserInput;
    //NOTE: Right-Alt Drag, only when nothing is in focus
    if(KeyHeld(keyMap::RAlt) && LeftClick && c->currentFocus == 0)
    { 
        c->isDragging = TRUE;
        POINT currMouse = {};
        GetCursorPos(&currMouse);
        c->prevMousePosX = currMouse.x;
        c->prevMousePosY = currMouse.y;
    }
    
    //NOTE: Handle Dragging
    if(c->isDragging && LeftHold)
    { 
        MouseInput *Mouse = &c->UserInput.Mouse;
        
        POINT currMouse = {};
        GetCursorPos(&currMouse);
        
        POINT prevMouse = { c->prevMousePosX, c->prevMousePosY };
        
        SHORT newX = prevMouse.x - currMouse.x;
        SHORT newY = prevMouse.y - currMouse.y;
        
        SHORT newWinX = c->windowPosX - newX;
        SHORT newWinY = c->windowPosY - newY;
        
        c->windowPosX = newWinX;
        c->windowPosY = newWinY;
        
        c->prevMousePosX  = currMouse.x;
        c->prevMousePosY  = currMouse.y;
        
        SetWindowPos(c->Window, 0, newWinX, newWinY, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
    }
    
    if(c->isDragging && LeftUp) { c->isDragging = FALSE; }
    
    if(LeftUp || RightUp || MiddleUp) { c->mouseCapture = 0; }
}

void ls_uiFrameEnd(UIContext *c, u64 frameTimeTargetMs)
{
    ls_arenaClear(c->frameArena);
    
    static u32 lastFrameTime = 0;
    
#ifdef _DEBUG
    __debug_frameNumber += 1;
#endif
    
    Input *UserInput = &c->UserInput;
    //NOTE: If user clicked somewhere, but nothing set the focus, then we should reset the focus
    if(LeftClick && !c->focusWasSetThisFrame)
    { 
        ls_uiFocusChange(c, 0);
    }
    
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

void ls_uiFrameEndChild(UIContext *c, u64 frameTimeTargetMs)
{
    ls_arenaClear(c->frameArena);
    
    static u32 lastFrameTime = 0;
    
    Input *UserInput = &c->UserInput;
    //NOTE: If user clicked somewhere, but nothing set the focus, then we should reset the focus
    if(LeftClick && !c->focusWasSetThisFrame)
    { ls_uiFocusChange(c, 0); }
    
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

void ls_uiLoadPackedFontAtlas(UIContext *c, char *path)
{
    Arena prev = ls_arenaUse(c->contextArena);
    
    u8 *bitmapFile = NULL;
    u64 bytesRead = ls_readFile(path, (char **)&bitmapFile, 0);
    
    b32 isWindowyfied = FALSE;
    u32 PixelOffset = *((u32 *)((char *)bitmapFile + 10));
    u32 HeaderSize = *((u32 *)((char *)bitmapFile + 14));
    
    s32 Width = *((s32 *)((char *)bitmapFile + 18));
    s32 Height = *((s32 *)((char *)bitmapFile + 22));
    if(Height < 0) { isWindowyfied = TRUE; Height = -Height; }
    
    u32 Compression = *((u32 *)((char *)bitmapFile + 30));
    
    u32 PixelBufferSize = *((u32 *)((char *)bitmapFile + 34));
    
    c->fonts = (UIFont *)ls_alloc(sizeof(UIFont)*1);
    c->fonts[0].fontAtlasSDF = (u8 *)((char *)bitmapFile + PixelOffset);
    c->fonts[0].atlasWidth  = Width;
    c->fonts[0].atlasHeight = Height;
    
    s32 *metaInfo = ((s32*)(c->fonts->fontAtlasSDF + ((c->fonts->atlasWidth*c->fonts->atlasHeight) - sizeof(s32))));
    c->fonts[0].ascent      = metaInfo[-5];
    c->fonts[0].descent     = metaInfo[-4];
    c->fonts[0].lineGap     = metaInfo[-3];
    c->fonts[0].pixelHeight = metaInfo[-2];
    c->fonts[0].cpCount     = metaInfo[-1];
    
    c->currFont                   = c->fonts;
    c->currPixelHeight            = c->fonts[0].pixelHeight;
    c->currFont->isAtlas          = TRUE;
    c->currFont->kernAdvanceTable = NULL;
    
    //TODO: Actually make it proper!
    c->currFont->maxCodepoint     = c->fonts[0].cpCount;
    
#ifdef LS_UI_OPENGL_BACKEND
    glGenTextures(1, &c->fonts[0].texID);
    glBindTexture(GL_TEXTURE_2D, c->fonts[0].texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_INTENSITY, Width, Height, 0, GL_RED, GL_UNSIGNED_BYTE, c->fonts[0].fontAtlasSDF);
    
    GLenum err = glGetError();
    if(err != GL_NO_ERROR)
    {
        ls_log("OpenGL Error: {s32}", err);
    }
#endif
    
    ls_arenaUse(prev);
    return;
}

UIBitmap ls_uiBitmapFromRGBAPixelData(UIContext *c, s32 w, s32 h, void *data)
{
    UIBitmap result = { data, w, h };
    
#ifdef LS_UI_OPENGL_BACKEND
    glGenTextures(1, &result.texID);
    glBindTexture(GL_TEXTURE_2D, result.texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    
    GLenum err = glGetError();
    if(err != GL_NO_ERROR)
    {
        ls_log("OpenGL Error When Loading Bitmap from RGBA Pixel Data: {s32}", err);
    }
#endif
    
    return result;
}

inline void ls_uiAddOnDestroyCallback(UIContext *c, onDestroyFunc f)
{ c->onDestroy = f; }

void ls_uiFocusChangeSameFrame(UIContext *c, u64 *focus)
{
    c->lastFocus            = c->currentFocus;
    c->currentFocus         = focus;
    c->focusWasSetThisFrame = TRUE;
}

void ls_uiFocusChange(UIContext *c, u64 *focus)
{
    c->nextFrameFocusChange = TRUE;
    c->nextFrameFocus = focus;
}

b32 ls_uiInFocus(UIContext *c, void *p)
{
    if(c->currentFocus == (u64 *)p) { return TRUE; }
    return FALSE;
}

b32 ls_uiHasCapture(UIContext *c, void *p)
{
    if(c->mouseCapture == (u64 *)p) { return TRUE; }
    return FALSE;
}

void ls_uiStartScrollableRegion(UIContext *c, UIScrollableRegion *scroll)
{ 
    AssertMsg(c->scroll == NULL, "Starting a scrollable region inside a scrollable region is invalid\n");
    AssertMsg(scroll, "Invalid Scrollable Region\n");
    
    Input *UserInput = &c->UserInput;
    
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
        s32 mouseDeltaY = (c->UserInput.Mouse.prevPosY - c->UserInput.Mouse.currPosY);
        s32 scaledDeltaY = (s32)(((f64)mouseDeltaY / (f64)scroll->h)*(f64)totalHeight);
        
        deltaY = -scaledDeltaY;
    }
    
    scroll->deltaY += deltaY;
    
    //TODO: What the fuck is this???? What was supposed to be here!?
    //scroll->maxX    = scroll->maxX;
    //scroll->minY    = scroll->minY;
    
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
    c->scissor = UIRect { 0, 0, s32(c->width), s32(c->height) };
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

UIRect ls_uiScreenCoordsToUnitSquare(UIContext *c, s32 x, s32 y, s32 w, s32 h)
{
    UIRect result = {};
    result.leftX  = (2.0f*(f32)x / (f32)c->width)-1.0f;
    result.botY   = (2.0f*(f32)y / (f32)c->height)-1.0f;
    result.rightX = (2.0f*(f32)(x+w) / (f32)c->width)-1.0f;
    result.topY   = (2.0f*(f32)(y+h) / (f32)c->height)-1.0f;
    return result;
}

Color ls_uiDarkenRGB(Color c, f32 percentage)
{
    //NOTE: Ensure the percentage is within valid bounds
    if (percentage < 0.0)
    { percentage = 0.0; }
    else if (percentage > 1.0)
    { percentage = 1.0; }
    
    /*TODO: I can't currently apply gamma correction, since I don't have a good log(a) and pow(f32, f32)
 *       implementation, which are required to properly handle the inv gamma
    //NOTE: Apply Gamma Correction (perceptual weighting)
    f32 gamma    = 2.2; //NOTE: Typical gamma value for Display Devices
    f32 invGamma = 1.0 / gamma;
    */
    
    //NOTE Convert Premultiplied Color to Linear Color
    f64 invAlpha = (f64)c.a / 255.0;
    f64 rLinear  = ((f64)c.r / invAlpha);
    f64 gLinear  = ((f64)c.g / invAlpha);
    f64 bLinear  = ((f64)c.b / invAlpha);
    
    //NOTE: Darken the Linear Color
    rLinear *= (1.0 - percentage);
    gLinear *= (1.0 - percentage);
    bLinear *= (1.0 - percentage);
    
    c.r = (u8)(rLinear * invAlpha);
    c.g = (u8)(gLinear * invAlpha);
    c.b = (u8)(bLinear * invAlpha);
    
    /*TODO: Gamma Correction when log(a) and pow(f32, f32) are implemented and good.
    //NOTE: Convert back to premultiplied RGBA, and apply inverse gamma.
    *r = (int)(pow(rLinear, invGamma) * alpha);
    *g = (int)(pow(gLinear, invGamma) * alpha);
    *b = (int)(pow(bLinear, invGamma) * alpha);
*/
    
    return c;
}


//TODO: Fix for premultiplied alpha?
Color ls_uiLightenRGB(Color c, f32 percentage)
{
    u8 *c8 = (u8 *)&c;
    
    u8 lowest = 255;
    if(c8[0] < lowest) { lowest = c8[0]; }
    if(c8[1] < lowest) { lowest = c8[1]; }
    if(c8[2] < lowest) { lowest = c8[2]; }
    
    if(lowest == 255)  { return c; }
    
    u8 diffFactor  = 255 - lowest;
    u8  sum        = diffFactor * percentage;
    f32 realFactor = (f32)sum / (f32)diffFactor;
    
    c8[0] += (255 - c8[0]) * realFactor;
    c8[1] += (255 - c8[1]) * realFactor;
    c8[2] += (255 - c8[2]) * realFactor;
    
    return c;
}

//TODO: This feels wrong. In the backbuffer I'm storing the pixels *emissions* rather then the color.
//      Why am I not un-multiplying the alpha before writing into the backbuffer, and why does it look
//      correct?? @Alpha-Un-Multiply
Color ls_uiAlphaBlend(Color source, Color dest, u8 alpha)
{
    //NOTE: If the alpha was premultiplied
    //f32 factor = (f32)(255 - source.a) / 255.0f;
    f32 factor = (f32)(255 - alpha) / 255.0f;
    
    Color Result = {};
    Result.b = source.b + dest.b*factor;
    Result.g = source.g + dest.g*factor;
    Result.r = source.r + dest.r*factor;
    Result.a = alpha + dest.a*factor;
    
    return Result;
}

Color ls_uiAlphaBlend(Color source, Color dest)
{
    return ls_uiAlphaBlend(source, dest, source.a);
}

Color ls_uiRGBAtoARGB(Color c)
{
    u8 *c8 = (u8 *)&c;
    u8 A   = c8[0];
    
    c8[0]  = c8[1];
    c8[1]  = c8[2];
    c8[2]  = c8[3];
    c8[3]  = A;
    
    return c;
}

Color ls_uiARGBtoRGBA(Color c)
{
    u8 *c8 = (u8 *)&c;
    u8 A   = c8[3];
    
    c8[3]  = c8[2];
    c8[2]  = c8[1];
    c8[1]  = c8[0];
    c8[0]  = A;
    
    return c;
}

//TODO: Should *MAYBE* convert to floating point colors, rather than u8 colors.
//      Better for converting into different color spaces.
Color ls_uiHSVtoRGB(u32 h, f32 s, f32 v)
{
    f32 cFactor = s * v;
    
    f32 fmodded = ls_fmod(((f32)h / 60.0f), 2.0f);
    
    f32 xFactor = cFactor * (1.0f - ls_fabs(fmodded - 1.0f));
    f32 mFactor = v - cFactor;
    
    f32 rPrime = 0.0f;
    f32 gPrime = 0.0f;
    f32 bPrime = 0.0f;
    
    //NOTE: Answer changes depending on which Hectant we are in
    if(h < 60)
    {
        rPrime = cFactor;
        gPrime = xFactor;
    }
    else if(h < 120)
    {
        rPrime = xFactor;
        gPrime = cFactor;
    }
    else if(h < 180)
    {
        gPrime = cFactor;
        bPrime = xFactor;
    }
    else if(h < 240)
    {
        gPrime = xFactor;
        bPrime = cFactor;
    }
    else if(h < 300)
    {
        rPrime = xFactor;
        bPrime = cFactor;
    }
    else if(h < 360)
    {
        rPrime = cFactor;
        bPrime = xFactor;
    }
    
    u8 finalR = (rPrime+mFactor)*255;
    u8 finalG = (gPrime+mFactor)*255;
    u8 finalB = (bPrime+mFactor)*255;
    
    Color final = RGB(finalR, finalG, finalB);
    return final;
}

void ls_uiClearRect(UIContext *c, s32 startX, s32 startY, s32 w, s32 h, Color col)
{
#ifdef LS_UI_OPENGL_BACKEND
    
    UIRect normRect = ls_uiScreenCoordsToUnitSquare(c, startX, startY, w, h);
    
    glColor3ub(col.r, col.g, col.b);
    glBegin(GL_TRIANGLES);
    glVertex2f(normRect.leftX,  normRect.topY);
    glVertex2f(normRect.leftX,  normRect.botY);
    glVertex2f(normRect.rightX, normRect.topY);
    glVertex2f(normRect.rightX, normRect.topY);
    glVertex2f(normRect.leftX,  normRect.botY);
    glVertex2f(normRect.rightX, normRect.botY);
    glEnd();
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
            u32 idx = ((y*c->width) + x)*sizeof(s32);
            __m128i *At = (__m128i *)(c->drawBuffer + idx);
            
            _mm_storeu_si128(At, color);
        }
    }
    
    //NOTE: Complete the 2 remaining Sub-Rectangles at the right and top. (if there are).
    //      We decide to have the right rectangle be full height
    //      And the top one be less-than-full width, to avoid over-drawing the small subrect
    //        in the top right corner.
    u32 *At = (u32 *)c->drawBuffer;
    
    if(diffWidth) 
    {
        for(s32 y = startY; y < startY+h; y++)
        {
            for(s32 x = startX+simdWidth; x < startX+w; x++)
            {
                At[y*c->width + x] = col.value;
            }
        }
    }
    
    if(diffHeight)
    {
        for(s32 y = startY+simdHeight; y < startY+h; y++)
        {
            for(s32 x = startX; x < startX+simdWidth; x++)
            {
                At[y*c->width + x] = col.value;
            }
        }
    }
#endif
}

void ls_uiFillRect(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h, 
                   UIRect threadRect, UIRect scissor, Color col)
{
#ifdef LS_UI_OPENGL_BACKEND
    
    UIRect normRect = ls_uiScreenCoordsToUnitSquare(c, xPos, yPos, w, h);
    
    glColor4ub(col.r, col.g, col.b, col.a);
    glBegin(GL_TRIANGLES);
    glVertex2f(normRect.leftX,  normRect.topY);
    glVertex2f(normRect.leftX,  normRect.botY);
    glVertex2f(normRect.rightX, normRect.topY);
    glVertex2f(normRect.rightX, normRect.topY);
    glVertex2f(normRect.leftX,  normRect.botY);
    glVertex2f(normRect.rightX, normRect.botY);
    glEnd();
    
#else
    s32 minX = threadRect.minX > scissor.x ? threadRect.minX : scissor.x;
    s32 minY = threadRect.minY > scissor.y ? threadRect.minY : scissor.y;
    s32 maxX = threadRect.maxX < scissor.x+scissor.w ? threadRect.maxX : scissor.x+scissor.w;
    s32 maxY = threadRect.maxY < scissor.y+scissor.h ? threadRect.maxY : scissor.y+scissor.h;
    
    s32 startY = yPos;
    if(startY < minY) { h -= (minY-startY); startY = minY; }
    
    s32 startX = xPos;
    if(startX < minX) { w -= (minX-startX); startX = minX; }
    
    /*Old Thread Rect being confused about inclusive and exclusive regions stuff
    if(startX+w > maxX) { w = maxX-startX+1; }
    if(startY+h > maxY) { h = maxY-startY+1; }
    */
    
    if(startX+w > maxX) { w = maxX-startX; }
    if(startY+h > maxY) { h = maxY-startY; }
    
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
        
        for(s32 x = startX; x < startX+simdWidth; x+=4)
        {
            AssertMsg(x <= maxX, "Should never happen. Width was precomputed\n");
            
            if(x < 0 || x >= c->width)  continue;
            if(y < 0 || y >= c->height) continue;
            
            u32 idx = ((y*c->width) + x)*sizeof(s32);
            __m128i *At = (__m128i *)(c->drawBuffer + idx);
            
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
    }
    
    //NOTE: Complete the 2 remaining Sub-Rectangles at the right and top. (if there are).
    //      We decide to have the right rectangle be full height
    //      And the top one be less-than-full width, to avoid over-drawing the small subrect
    //        in the top right corner.
    u32 *At = (u32 *)c->drawBuffer;
    
    if(diffWidth) 
    {
        for(s32 y = startY; y < startY+h; y++)
        {
            if(y > maxY) { break; }
            
            for(s32 x = startX+simdWidth; x < startX+w; x++)
            {
                if(x > maxX) { 
                    ls_printf("diffSIMDWidth: %d, diffWidth: %d\n", x-maxX, diffWidth);
                    break; 
                }
                
                if(x < 0 || x >= c->width)  continue;
                if(y < 0 || y >= c->height) continue;
                
                Color base = {.value = At[y*c->width + x] };
                Color blendedColor = ls_uiAlphaBlend(col, base);
                At[y*c->width + x] = blendedColor.value;
            }
        }
    }
    
    if(diffHeight)
    {
        for(s32 y = startY+simdHeight; y < startY+h; y++)
        {
            AssertMsg(y <= maxY, "Should never happen. Height was precomputed\n");
            if(y > maxY) { break; }
            
            for(s32 x = startX; x < startX+simdWidth; x++)
            {
                if(x > maxX) { break; }
                
                if(x < 0 || x >= c->width)  continue;
                if(y < 0 || y >= c->height) continue;
                
                Color base = { .value = At[y*c->width + x] };
                Color blendedColor = ls_uiAlphaBlend(col, base);
                At[y*c->width + x] = blendedColor.value;
            }
        }
    }
#endif //LS_UI_OPENGL_BACKEND
}

void ls_uiFillCircle(UIContext *c, s32 centerX, s32 centerY, s32 radius,
                     UIRect threadRect, UIRect scissor, Color col)
{
#ifdef LS_UI_OPENGL_BACKEND
    
    const s32 triangleCount = 30;
    
    f32 normCx   = (2.0f*(f32)centerX / (f32)c->width)-1.0f;
    f32 normCy   = (2.0f*(f32)centerY / (f32)c->height)-1.0f;
    f32 normRadX = ((f32)radius / (f32)c->width);
    f32 normRadY = ((f32)radius / (f32)c->height);
    
    //NOTE: We start at angle 0, and create triangles by moving one angle step at a time
    f32 angleStep = TAU / triangleCount;
    f32 p1X = normCx+normRadX;
    f32 p1Y = normCy;
    f32 p2X = normCx+normRadX * cos(angleStep);
    f32 p2Y = normCy+normRadY * sin(angleStep);
    
    glColor4ub(col.r, col.g, col.b, col.a);
    glBegin(GL_TRIANGLE_FAN);
    
    glVertex2f(normCx, normCy);
    for(s32 i = 0; i < triangleCount+1; i++)
    {
        glVertex2f(p1X, p1Y);
        p1X = normCx+normRadX * cos(i*angleStep);
        p1Y = normCy+normRadY * sin(i*angleStep);
    }
    glVertex2f(normCx+normRadX, normCy);
    
    glEnd();
    
#else
    
    s32 minX = threadRect.minX > scissor.x ? threadRect.minX : scissor.x;
    s32 minY = threadRect.minY > scissor.y ? threadRect.minY : scissor.y;
    s32 maxX = threadRect.maxX < scissor.x+scissor.w ? threadRect.maxX : scissor.x+scissor.w;
    s32 maxY = threadRect.maxY < scissor.y+scissor.h ? threadRect.maxY : scissor.y+scissor.h;
    
    s32 startX = centerX - radius;
    s32 startY = centerY - radius;
    
    if(startX < minX) { startX = minX; }
    if(startY < minY) { startY = minY; }
    
    s32 endX   = centerX + radius + 1;
    s32 endY   = centerY + radius + 1;
    
    if(endX > maxX) { endX = maxX+1; }
    if(endY > maxY) { endY = maxY+1; }
    
    u32 *At = (u32 *)c->drawBuffer;
    for(s32 y = startY; y < endY; y++)
    {
        for(s32 x = startX; x < endX; x++)
        {
            s32 cX = x - centerX;
            s32 cY = y - centerY;
            
            b32 cond = (cY*cY + cX*cX) <= (radius*radius);
            
            if(cond)
            {
                Color base         = { .value = At[y*c->width + x] };
                Color blendedColor = ls_uiAlphaBlend(col, base);
                At[y*c->width + x] = blendedColor.value;
            }
        }
    }
    
#endif
}

//TODO: Change with better rasterizer
void ls_uiCircle(UIContext *c, s32 centerX, s32 centerY, s32 radius, s32 thickness,
                 UIRect threadRect, UIRect scissor, Color col)
{
#ifdef LS_UI_OPENGL_BACKEND
    const s32 linesCount = 30;
    
    //NOTE: Make sure we don't overflow the drawing stupidly
    AssertMsg(thickness <= radius, "Thickness overflows the radius\n");
    if(thickness > radius) { thickness = radius; }
    
    f32 normCx   = (2.0f*(f32)centerX / (f32)c->width)-1.0f;
    f32 normCy   = (2.0f*(f32)centerY / (f32)c->height)-1.0f;
    f32 normRadX = ((f32)radius / (f32)c->width);
    f32 normRadY = ((f32)radius / (f32)c->height);
    
    //NOTE: We start at angle 0, and create triangles by moving one angle step at a time
    f32 angleStep = TAU / linesCount;
    f32 p1X = normCx+normRadX;
    f32 p1Y = normCy;
    f32 p2X = normCx+normRadX * cos(angleStep);
    f32 p2Y = normCy+normRadY * sin(angleStep);
    
    glColor4ub(col.r, col.g, col.b, col.a);
    glBegin(GL_LINE_STRIP);
    
    for(s32 th = 0; th < thickness; th++)
    {
        glVertex2f(p1X, p1Y);
        for(s32 i = 0; i < linesCount+1; i++)
        {
            glVertex2f(p2X, p2Y);
            p2X = normCx+normRadX * cos((i+1)*angleStep);
            p2Y = normCy+normRadY * sin((i+1)*angleStep);
        }
        glVertex2f(p1X, p1Y);
        
        radius -= 1;
        normRadX = ((f32)radius / (f32)c->width);
        normRadY = ((f32)radius / (f32)c->height);
        p1X = normCx+normRadX;
        p1Y = normCy;
        p2X = normCx+normRadX * cos(angleStep);
        p2Y = normCy+normRadY * sin(angleStep);
    }
    glEnd();
    
#else
    s32 minX = threadRect.minX > scissor.x ? threadRect.minX : scissor.x;
    s32 minY = threadRect.minY > scissor.y ? threadRect.minY : scissor.y;
    s32 maxX = threadRect.maxX < scissor.x+scissor.w ? threadRect.maxX : scissor.x+scissor.w;
    s32 maxY = threadRect.maxY < scissor.y+scissor.h ? threadRect.maxY : scissor.y+scissor.h;
    
    s32 startX = centerX - radius;
    s32 startY = centerY - radius;
    
    if(startX < minX) { startX = minX; }
    if(startY < minY) { startY = minY; }
    
    s32 endX   = centerX + radius + 1;
    s32 endY   = centerY + radius + 1;
    
    if(endX > maxX) { endX = maxX+1; }
    if(endY > maxY) { endY = maxY+1; }
    
    u32 *At = (u32 *)c->drawBuffer;
    for(s32 y = startY; y < endY; y++)
    {
        for(s32 x = startX; x < endX; x++)
        {
            s32 cX = x - centerX;
            s32 cY = y - centerY;
            
            b32 cond1 = (cY*cY + cX*cX) <= (radius*radius);
            b32 cond2 = (cY*cY + cX*cX) >= ((radius-thickness)*(radius-thickness));
            
            if(cond1 && cond2)
            {
                Color base         = { .value = At[y*c->width + x] };
                Color blendedColor = ls_uiAlphaBlend(col, base);
                At[y*c->width + x] = blendedColor.value;
            }
        }
    }
#endif
}

inline
void ls_uiBorder(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h,
                 UIRect threadRect, UIRect scissor)
{
    Color C = c->borderColor;
    
    ls_uiFillRect(c, xPos,     yPos,     w, 1, threadRect, scissor, C);
    ls_uiFillRect(c, xPos,     yPos+h-1, w, 1, threadRect, scissor, C);
    ls_uiFillRect(c, xPos,     yPos,     1, h, threadRect, scissor, C);
    ls_uiFillRect(c, xPos+w-1, yPos,     1, h, threadRect, scissor, C);
}

inline
void ls_uiBorder(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h,
                 UIRect threadRect, UIRect scissor, Color borderColor)
{
    Color C = borderColor;
    
    ls_uiFillRect(c, xPos,     yPos,     w, 1, threadRect, scissor, C);
    ls_uiFillRect(c, xPos,     yPos+h-1, w, 1, threadRect, scissor, C);
    ls_uiFillRect(c, xPos,     yPos,     1, h, threadRect, scissor, C);
    ls_uiFillRect(c, xPos+w-1, yPos,     1, h, threadRect, scissor, C);
}

inline
void ls_uiBorderedRect(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h,
                       UIRect threadRect, UIRect scissor)
{
    ls_uiBorder(c, xPos, yPos, w, h, threadRect, scissor);
    ls_uiFillRect(c, xPos+1, yPos+1, w-2, h-2, threadRect, scissor, c->widgetColor);
}

inline
void ls_uiBorderedRect(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h,
                       UIRect threadRect, UIRect scissor, Color widgetColor)
{
    ls_uiBorder(c, xPos, yPos, w, h, threadRect, scissor);
    ls_uiFillRect(c, xPos+1, yPos+1, w-2, h-2, threadRect, scissor, widgetColor);
}

inline
void ls_uiBorderedRect(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h, 
                       UIRect threadRect, UIRect scissor, Color widgetColor, Color borderColor)
{
    ls_uiBorder(c, xPos, yPos, w, h, threadRect, scissor, borderColor);
    ls_uiFillRect(c, xPos+1, yPos+1, w-2, h-2, threadRect, scissor, widgetColor);
}

inline
void ls_uiRect(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h,
               UIRect threadRect, UIRect scissor)
{
    ls_uiFillRect(c, xPos, yPos, w, h, threadRect, scissor, c->widgetColor);
}

inline
void ls_uiRect(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h, 
               UIRect threadRect, UIRect scissor, Color widgetColor)
{
    ls_uiFillRect(c, xPos, yPos, w, h, threadRect, scissor, widgetColor);
}

void ls_uiRect(UIContext *c, s32 x, s32 y, s32 w, s32 h, Color bkgColor, Color borderColor, s32 zLayer = 0)
{
    RenderCommand command = { UI_RC_RECT, x, y, w, h };
    command.bkgColor      = bkgColor;
    command.borderColor   = borderColor;
    
    ls_uiPushRenderCommand(c, command, zLayer);
}

void ls_uiRect(UIContext *c, s32 x, s32 y, s32 w, s32 h, s32 zLayer = 0)
{
    RenderCommand command = { UI_RC_RECT, x, y, w, h };
    command.bkgColor    = c->widgetColor;
    command.borderColor = c->borderColor;
    
    ls_uiPushRenderCommand(c, command, zLayer);
}

void ls_uiHSeparator(UIContext *c, s32 x, s32 y, s32 width, s32 lineWidth, Color lineColor, s32 zLayer = 0)
{
    RenderCommand command = { UI_RC_SEPARATOR, x, y, width, lineWidth };
    command.borderColor   = lineColor;
    ls_uiPushRenderCommand(c, command, zLayer);
    
    //TODO: Do I like this???
    command.rect.y       += 1;
    command.borderColor   = ls_uiDarkenRGB(command.borderColor, 0.10f);
    ls_uiPushRenderCommand(c, command, zLayer);
}

void ls_uiVSeparator(UIContext *c, s32 x, s32 y, s32 height, s32 lineWidth, Color lineColor, s32 zLayer = 0)
{
    RenderCommand command = { UI_RC_SEPARATOR, x, y, lineWidth, height };
    command.borderColor = lineColor;
    ls_uiPushRenderCommand(c, command, zLayer);
    
    //TODO: Do I like this???
    command.rect.x += 1;
    command.borderColor = ls_uiDarkenRGB(command.borderColor, 0.10f);
    ls_uiPushRenderCommand(c, command, zLayer);
}

void ls_uiStretchBitmap(UIContext *c, UIRect threadRect, UIRect dst, UIBitmap *bmp)
{
#ifdef LS_UI_OPENGL_BACKEND
    
    UIRect norm = ls_uiScreenCoordsToUnitSquare(c, dst.x, dst.y, dst.w, dst.h);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, bmp->texID);
    //TODO: We will care about these kinda stuff in the near future
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    
    glTexCoord2f(0.0, 1.0); glVertex2f(norm.leftX,  norm.topY);
    glTexCoord2f(0.0, 0.0); glVertex2f(norm.leftX,  norm.botY);
    glTexCoord2f(1.0, 1.0); glVertex2f(norm.rightX, norm.topY);
    glTexCoord2f(1.0, 1.0); glVertex2f(norm.rightX, norm.topY);
    glTexCoord2f(0.0, 0.0); glVertex2f(norm.leftX,  norm.botY);
    glTexCoord2f(1.0, 0.0); glVertex2f(norm.rightX, norm.botY);
    
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
#else
    
    s32 minX = threadRect.minX;
    s32 minY = threadRect.minY;
    s32 maxX = threadRect.maxX;
    s32 maxY = threadRect.maxY;
    
    //NOTE: We multiply the scale factors by 0.99.. to avoid sampling a pixel from 1 off outside
    //      the source bitmap because of rounding inaccuracies with floating point values.
    //TODO: We could probably keep the original scale factors, and correctly round up/down when necessary
    //      to avoid this accuracy problem.
    f32 scaleW   = ((f32)dst.w / (f32)bmp->w) * 0.999999f;
    f32 scaleH   = ((f32)dst.h / (f32)bmp->h) * 0.999999f;
    f32 factorW  = 1.0f / scaleW;
    f32 factorH  = 1.0f / scaleH;
    
    s32 startY = dst.y;
    if(startY < minY) { dst.h -= (minY-startY); startY = minY; }
    
    s32 startX = dst.x;
    if(startX < minX) { dst.w -= (minX-startX); startX = minX; }
    
    if(startX+dst.w > maxX) { dst.w = maxX-startX+1; }
    if(startY+dst.h > maxY) { dst.h = maxY-startY+1; }
    
    u32 *At = (u32 *)c->drawBuffer;
    Color *SrcBmp = (Color *)bmp->data;
    
    if(scaleW > 1.0f && scaleH > 1.0f)
    {
        //NOTE: Enlarging the bitmap (Scaling up)
        TODO;
    }
    else if(scaleW < 1.0f && scaleH < 1.0f)
    {
        //NOTE: Shrinking the bitmap (Scaling down)
        //      factorW tells me how many pixels horiz. of the bmp I need to blend
        //      to obtain a single pixel of the destination
        f32 eY = 0.0f;
        for(s32 y = startY; y < dst.y+dst.h; y++)
        {
            AssertMsg(y <= maxY, "Should never happen. Height was precomputed\n");
            
            f32 eX = 0.0f;
            for(s32 x = startX; x < dst.x+dst.w; x++)
            {
                AssertMsg(x <= maxX, "Should never happen. Width was precomputed\n");
                
                if(x < 0 || x >= c->width)  continue;
                if(y < 0 || y >= c->height) continue;
                
                u32 *DstPixel    = &At[(y * c->width) + x];
                Color finalColor = {.value = *DstPixel};
                
                for(u32 heightIdx = 0; heightIdx < factorH; heightIdx++)
                {
                    for(u32 widthIdx = 0; widthIdx < factorW; widthIdx++)
                    {
                        s32 bmpY = eY + heightIdx;
                        s32 bmpX = eX + widthIdx;
                        
                        if(bmpY >= bmp->h) break;
                        if(bmpX >= bmp->w) break;
                        
                        Color SrcPixel = SrcBmp[bmpY*bmp->w + bmpX];
                        finalColor = ls_uiAlphaBlend(SrcPixel, finalColor);
                    }
                }
                
                *DstPixel = finalColor.value;
                
                eX += factorW;
            }
            
            eY += factorH;
        }
    }
    else
    {
        TODO;
    }
    
#endif
}

void ls_uiBitmap(UIContext *c, UIBitmap bmp, s32 xPos, s32 yPos, UIRect threadRect)
{
#ifdef LS_UI_OPENGL_BACKEND
    ls_uiStretchBitmap(c, threadRect, {xPos, yPos, bmp.w, bmp.h}, &bmp);
#else
    
    s32 minX = threadRect.minX;
    s32 minY = threadRect.minY;
    s32 maxX = threadRect.maxX;
    s32 maxY = threadRect.maxY;
    
    u32 *data = (u32 *)bmp.data;
    s32 w = bmp.w;
    s32 h = bmp.h;
    
    s32 startY = yPos;
    s32 startEY = 0;
    s32 rH = h;
    if(startY < minY) { rH -= (minY-startY); startEY += (minY-startY); startY = minY;  }
    
    s32 startX = xPos;
    s32 startEX = 0;
    s32 rW = w;
    if(startX < minX) { rW -= (minX-startX); startEX += (minX-startX); startX = minX; }
    
    if(startX+rW > maxX) { rW = maxX-startX+1; }
    if(startY+rH > maxY) { rH = maxY-startY+1; }
    
    u32 *At = (u32 *)c->drawBuffer;
    
    for(s32 y = startY, eY = startEY; y < startY+rH; y++, eY++)
    {
        AssertMsg(y <= maxY, "Should never happen. Height was precomputed\n");
        
        for(s32 x = startX, eX = startEX; x < startX+rW; x++, eX++)
        {
            AssertMsg(x <= maxX, "Should never happen. Width was precomputed\n");
            
            if(x < 0 || x >= c->width)  continue;
            if(y < 0 || y >= c->height) continue;
            
            Color src  = { .value = data[eY*w + eX] };
            Color base = { .value = At[y*c->width + x] };
            
            Color blendedColor = ls_uiAlphaBlend(src, base);
            At[y*c->width + x] = blendedColor.value;
        }
    }
    
#endif
}

//TODO: I don't like that uiGlyph and SDFGlyph are separate functions...
void ls_uiGlyph(UIContext *c, s32 xPos, s32 yPos, UIRect threadRect, UIRect scissor, UIGlyph *glyph, Color textColor)
{
    s32 minX = threadRect.minX;
    s32 minY = threadRect.minY;
    s32 maxX = threadRect.maxX;
    s32 maxY = threadRect.maxY;
    
    u32 *At = (u32 *)c->drawBuffer;
    
    s32 startY = yPos-glyph->y1;
    s32 eY = glyph->height-1;
    if(startY < minY) { eY -= (minY - startY); startY = minY; }
    
    //TODO: Remove bound checking against the threadRect by pre-computing proper boundaries
    //      And also with the scissor. *Basically compute the smalles rectangle that is valid*
    for(s32 y = startY; eY >= 0; y++, eY--)
    {
        if(y > maxY) break;
        if(y < scissor.y || y > scissor.y + scissor.h) break;
        
        s32 startX = xPos+glyph->x0;
        s32 eX = 0;
        if(startX < minX) { eX += (minX - startX); startX = minX; }
        
        for(s32 x = startX; eX < glyph->width; x++, eX++)
        {
            if(x > maxX) break;
            if(x < scissor.x || x >= scissor.x + scissor.w) break;
            
            Color base = { .value = At[y*c->width + x] };
            u8 dstA    = glyph->data[eY*glyph->width + eX];
            
            f64 dA = (f64)dstA / 255.0;
            
            Color actual = {
                .b = (u8)(textColor.b*dA),
                .g = (u8)(textColor.g*dA),
                .r = (u8)(textColor.r*dA),
                .a = (u8)(textColor.a*dA)
            };
            
            Color blendedColor = ls_uiAlphaBlend(actual, base);
            At[y*c->width + x] = blendedColor.value;
        }
    }
}

void ls_uiSDFGlyph(UIContext *c, UIGlyph *glyph, s32 xPos, s32 yPos, s32 stride, f64 scaling, 
                   UIRect threadRect, UIRect scissor, Color textColor)
{
    auto bl_interp = [stride](UIGlyph *glyph, f64 x, f64 y) -> f64 {
        //NOTE: Calculate the Integer and Fractional parts of the coordinates
        s32 x0 = (s32)x;
        s32 x1 = (x0 + 1 < glyph->width) ? x0 + 1 : x0;
        s32 y0 = (s32)y;
        s32 y1 = (y0 + 1 < glyph->height) ? y0 + 1 : y0;
        
        f64 dx = x - x0;
        f64 dy = y - y0;
        
        //NOTE: Get a 4x4 pixel square
        f64 v00 = (f64)glyph->data[y0 * stride + x0] / 255.0;
        f64 v01 = (f64)glyph->data[y1 * stride + x0] / 255.0;
        f64 v10 = (f64)glyph->data[y0 * stride + x1] / 255.0;
        f64 v11 = (f64)glyph->data[y1 * stride + x1] / 255.0;
        
        //NOTE: Bilinear Interpolation (It's just a lerp between two lerps. Hence Bi- Linear!)
        f64 v0 = v00 * (1.0 - dy) + v01 * dy;
        f64 v1 = v10 * (1.0 - dy) + v11 * dy;
        f64 final = v0 * (1.0 - dx) + v1 * dx;
        
        return final;
    };
    
    u32 *At = (u32 *)c->drawBuffer;
    s32 startY = yPos-glyph->y1*scaling;
    s32 startX = xPos+glyph->x0*scaling;
    
    const s32 todoOnEdgeValue = 160;
    const f64 todoFractOnEdge = (f64)todoOnEdgeValue/255.0;
    
    //NOTE: Scaled dimensions for the glyph
    s32 scaledHeight = glyph->height*scaling;
    s32 scaledWidth  = glyph->width*scaling;
    
    s32 yOff = 0;
    s32 xOff = 0;
    
    //NOTE: Output bounding box in the backbuffer based on the scaled dimensions
    s32 maxY = scaledHeight;
    if(startY + maxY > threadRect.maxY) { maxY -= (startY+maxY) - threadRect.maxY; }
    s32 maxX = scaledWidth;
    if(startX + maxX > threadRect.maxX) { maxX -= (startX+maxX) - threadRect.maxX; }
    
    s32 minY = threadRect.minY;
    if(startY < minY) { yOff = minY - startY; maxY -= yOff; startY = minY; }
    s32 minX = threadRect.minX;
    if(startX < minX) { xOff = minX - startX; maxX -= xOff; startX = minX; }
    
    /*NOTE: This is not required, since the threadRects already clamp to the client area
    if(startY + maxY > c->height) { maxY -= ((startY + maxY) - c->height); }
    if(startX + maxX > c->width)  { maxX -= ((startX + maxX) - c->width); }
    */
    
    for(s32 y = 0; y < maxY; ++y)
    {
        s32 backbufferY = startY + y;
        
        for(s32 x = 0; x < maxX; ++x)
        {
            s32 backbufferX = startX + x;
            
            //NOTE: map the output pixel position to the sdf glyph position
            f64 sdfX = (x+xOff) / scaling;
            f64 sdfY = ((scaledHeight - 1) - (y+yOff)) / scaling;
            
            //NOTE: Fetch the sdf value by doing bilinear interpolation on the sdf bitmap
            f64 sdf_value = bl_interp(glyph, sdfX, sdfY);
            
            //NOTETODO: Shitty sdf filtering.
            //f64 realAlpha = sdf_value < todoFractOnEdge ? 0.0 : 1.0;
            f64 realAlpha = sdf_value < todoFractOnEdge ? sdf_value : 1.0;
            Color actual = {
                .b = (u8)(textColor.b*realAlpha),
                .g = (u8)(textColor.g*realAlpha),
                .r = (u8)(textColor.r*realAlpha),
                .a = (u8)(textColor.a*realAlpha)
            };
            
            Color base  = { .value = At[backbufferY*c->width + backbufferX] };
            Color final = ls_uiAlphaBlend(actual, base);
            At[backbufferY * c->width + backbufferX] = final.value;
        }
    }
}


s32 ls_uiGetKernAdvance(UIContext *c, s32 codepoint1, s32 codepoint2)
{
    AssertNonNull(c);
    AssertNonNull(c->currFont);
    AssertNonNull(c->currFont->kernAdvanceTable);
    
    UIFont *font = c->currFont;
    s32 kernAdvance = font->kernAdvanceTable[codepoint1][codepoint2];
    
    return kernAdvance;
}

s32 ls_uiGetKernAdvance(UIFont *font, s32 codepoint1, s32 codepoint2)
{
    AssertNonNull(font);
    AssertNonNull(font->kernAdvanceTable);
    
    s32 kernAdvance = font->kernAdvanceTable[codepoint1][codepoint2];
    
    return kernAdvance;
}

void ls_uiRenderAlignedStringOnRect(UIContext *c, UIFont *font, UITextBox *box, s32 xPos, s32 yPos, s32 w, s32 h, 
                                    UIRect threadRect, UIRect scissor, Color textColor, Color invTextColor)
{
    AssertMsg(c, "Context is null\n");
    AssertMsg(box, "TextBox is null\n");
    AssertMsg(c->currFont, "Current Font is null\n");
    
    s32 cIdx = box->caretIndex-box->currLineBeginIdx;
    
    //NOTETODO Hacky shit.
    const s32 lineHeight = font->pixelHeight*1.1f;
    
    //NOTETODO: Hacky shit.
    const u32 horzOff = font->pixelHeight*0.40f;
    const u32 strMaxX = xPos + (w - 2*horzOff);
    
    //NOTETODO: Hacky shit.
    const u32 vertOff = 8;
    const u32 strMaxH = (h-(vertOff*2));
    const u32 vertGlyphOff = 3;
    
    s32 xOffset = box->viewBeginIdx;
    s32 yOffset = 0;
    
    s32 maxLines = strMaxH / lineHeight;
    
    //TODO: SIMD this?
    s32 i = 0;
    if(box->caretLineIdx > maxLines) { 
        yOffset = box->caretLineIdx - maxLines;
        
        //NOTE: Advance the string vertically to the nth line
        while(yOffset)
        {
            u32 code = box->text.data[i];
            AssertMsgF(code <= font->maxCodepoint, "GlyphIndex %d OutOfBounds\n", code);
            
            if(code == (char32_t)'\n') { yOffset -= 1; }
            i += 1;
        }
    }
    
    s32 adjustedCaretLine = box->caretLineIdx - yOffset;
    
    s32 currXPos = xPos;
    s32 currYPos = yPos;
    u32 code    = 0;
    
    utf32 realString = { box->text.data + i, box->text.len - i, box->text.size - i };
    uview lineView = ls_uviewCreate(realString);
    utf32 firstLine = ls_uviewNextLine(lineView).s;
    
    switch(box->align)
    {
        case UI_TB_ALIGN_LEFT: {
            currXPos = xPos;
        } break;
        
        case UI_TB_ALIGN_RIGHT: {
            currXPos = xPos+w-horzOff - ls_uiGlyphStringRect(c, font, firstLine, font->pixelHeight).w;
        } break;
        
        case UI_TB_ALIGN_CENTER: {
            currXPos = xPos+w-horzOff - (ls_uiGlyphStringRect(c, font, firstLine, font->pixelHeight).w / 2);
        } break;
        
        default: { AssertMsg(FALSE, "Unhandled TextBox Alignement\n"); } break;
    }
    
    for(u32 lineIdx = 0; lineIdx < (box->lineCount+1-yOffset); lineIdx++)
    {
        lineView = ls_uviewNextLine(lineView);
        utf32 line = lineView.s;
        
        i += xOffset;
        u32 lIdx = xOffset;
        s32 caretX = currXPos-3;
        for(; lIdx < line.len; lIdx++, i++)
        {
            if((lineIdx == box->caretLineIdx) && (cIdx == lIdx)) { caretX = currXPos-3; }
            if(currXPos > strMaxX)
            {
                if((lineIdx == box->caretLineIdx) && (cIdx == lIdx+1)) { caretX = currXPos-3; }
                i += line.len - lIdx; break;
            }
            
            code = line.data[lIdx];
            AssertMsgF(code <= font->maxCodepoint, "GlyphIndex %d OutOfBounds\n", code);
            
            Color actualColor = textColor;
            UIGlyph *currGlyph = &font->glyph[code];
            
            //TODO: Pretty inefficient to keep redrawing the background all the time.
            if(box->isSelecting && (box->selectBeginLine <= lineIdx) && (box->selectEndLine >= lineIdx)
               && (box->selectBeginIdx <= i) && (box->selectEndIdx > i))
            { 
                actualColor = invTextColor;
                ls_uiFillRect(c, currXPos, currYPos, currGlyph->xAdv, lineHeight-vertGlyphOff, 
                              threadRect, scissor, c->invWidgetColor);
            }
            
            ls_uiGlyph(c, currXPos, currYPos+vertGlyphOff, threadRect, scissor, currGlyph, actualColor);
            
            s32 kernAdvance = 0;
            if(lIdx < line.len-1) { kernAdvance = ls_uiGetKernAdvance(c, line.data[lIdx], line.data[lIdx+1]); }
            currXPos += (currGlyph->xAdv + kernAdvance);
            
        }
        
        if(((lineIdx == box->caretLineIdx) && cIdx == line.len)) { caretX = currXPos-3; }
        
        if(box->isCaretOn && (c->currentFocus == (u64 *)box) && (lineIdx == box->caretLineIdx))
        {
            UIGlyph *currGlyph = &font->glyph[(char32_t)'|'];
            ls_uiGlyph(c, caretX, currYPos+vertGlyphOff, threadRect, scissor, currGlyph, textColor);
        }
        
        currYPos -= lineHeight;
        switch(box->align)
        {
            case UI_TB_ALIGN_LEFT: {
                currXPos = xPos;
            } break;
            
            case UI_TB_ALIGN_RIGHT: {
                currXPos = xPos+w-horzOff - ls_uiGlyphStringRect(c, font, firstLine, font->pixelHeight).w;
            } break;
            
            case UI_TB_ALIGN_CENTER: {
                currXPos = xPos+w-horzOff - (ls_uiGlyphStringRect(c, font, firstLine, font->pixelHeight).w / 2);
            } break;
            
            default: { AssertMsg(FALSE, "Unhandled TextBox Alignement\n"); } break;
        }
    }
}

void ls_uiRenderStringOnRect(UIContext *c, UITextBox *box, s32 xPos, s32 yPos, s32 w, s32 h, 
                             UIRect threadRect, UIRect scissor, Color textColor, Color invTextColor)
{
    AssertMsg(c, "Context is null\n");
    AssertMsg(box, "TextBox is null\n");
    AssertMsg(c->currFont, "Current Font is null\n");
    
    s32 cIdx = box->caretIndex-box->currLineBeginIdx;
    
    //NOTETODO Hacky shit.
    const s32 lineHeight = 18;
    
    //NOTETODO: Hacky shit.
    const u32 horzOff = 8;
    const u32 strMaxX = xPos + (w - 2*horzOff);
    
    //NOTETODO: Hacky shit.
    const u32 vertOff = 8;
    const u32 strMaxH = (h-(vertOff*2));
    const u32 vertGlyphOff = 3;
    
    s32 xOffset = box->viewBeginIdx;
    s32 yOffset = 0;
    
    s32 maxLines = strMaxH / lineHeight;
    
    //TODO: SIMD this?
    s32 i = 0;
    if(box->caretLineIdx > maxLines) { 
        yOffset = box->caretLineIdx - maxLines;
        
        //NOTE: Advance the string vertically to the nth line
        while(yOffset)
        {
            u32 code = box->text.data[i];
            AssertMsgF(code <= c->currFont->maxCodepoint, "GlyphIndex %d OutOfBounds\n", code);
            
            if(code == (char32_t)'\n') { yOffset -= 1; }
            i += 1;
        }
    }
    
    s32 adjustedCaretLine = box->caretLineIdx - yOffset;
    
    s32 currXPos = xPos;
    s32 currYPos = yPos;
    u32 code    = 0;
    
    utf32 realString = { box->text.data + i, box->text.len - i, box->text.size - i };
    uview lineView = ls_uviewCreate(realString);
    
    for(u32 lineIdx = 0; lineIdx < (box->lineCount+1-yOffset); lineIdx++)
    {
        lineView = ls_uviewNextLine(lineView);
        utf32 line = lineView.s;
        
        i += xOffset;
        u32 lIdx = xOffset;
        s32 caretX = currXPos-3;
        for(; lIdx < line.len; lIdx++, i++)
        {
            if((lineIdx == box->caretLineIdx) && (cIdx == lIdx)) { caretX = currXPos-3; }
            if(currXPos > strMaxX)
            {
                if((lineIdx == box->caretLineIdx) && (cIdx == lIdx+1)) { caretX = currXPos-3; }
                i += line.len - lIdx; break;
            }
            
            code = line.data[lIdx];
            AssertMsgF(code <= c->currFont->maxCodepoint, "GlyphIndex %d OutOfBounds\n", code);
            
            Color actualColor = textColor;
            UIGlyph *currGlyph = &c->currFont->glyph[code];
            
            //TODO: Pretty inefficient to keep redrawing the background all the time.
            if(box->isSelecting && (box->selectBeginLine <= lineIdx) && (box->selectEndLine >= lineIdx)
               && (box->selectBeginIdx <= i) && (box->selectEndIdx > i))
            { 
                actualColor = invTextColor;
                ls_uiFillRect(c, currXPos, currYPos, currGlyph->xAdv, lineHeight-vertGlyphOff, 
                              threadRect, scissor, c->invWidgetColor);
            }
            
            ls_uiGlyph(c, currXPos, currYPos+vertGlyphOff, threadRect, scissor, currGlyph, actualColor);
            
            s32 kernAdvance = 0;
            if(lIdx < line.len-1) { kernAdvance = ls_uiGetKernAdvance(c, line.data[lIdx], line.data[lIdx+1]); }
            currXPos += (currGlyph->xAdv + kernAdvance);
            
        }
        
        if(((lineIdx == box->caretLineIdx) && cIdx == line.len)) { caretX = currXPos-3; }
        
        if(box->isCaretOn && (c->currentFocus == (u64 *)box) && (lineIdx == box->caretLineIdx))
        {
            UIGlyph *currGlyph = &c->currFont->glyph[(char32_t)'|'];
            ls_uiGlyph(c, caretX, currYPos+vertGlyphOff, threadRect, scissor, currGlyph, textColor);
        }
        
        
        currYPos -= lineHeight;
        currXPos  = xPos;
    }
    
}

template<typename T>
void ls_uiGlyphString(UIContext *c, UIFont *font, s32 pixelHeight, s32 xPos, s32 yPos,
                      UIRect threadRect, UIRect scissor, T text, Color textColor)
{
    struct MapEntry
    { //NOTE: I'm gonna assume this will be packed, being a multiple of 32 bits in size...
        u32 codepoint;
        s32 pixelX;
        s32 pixelY;
        s32 width;
        s32 height;
        s32 xOff;
        s32 yOff;
        s32 xAdv;
        s32 leftSB;
    };
    
    //NOTE: Look for the glyph pixel data in the map
    auto getMapEntryFromAtlas = [](UIFont *font, u32 codepoint) -> MapEntry *{
        s32 mapSize    = *((s32*)(font->fontAtlasSDF + ((font->atlasWidth*font->atlasHeight) - sizeof(s32))));
        s32 glyphCount = font->cpCount;
        MapEntry *map  = (MapEntry *)(font->fontAtlasSDF + ((font->atlasWidth*font->atlasHeight) - mapSize));
        while(glyphCount-- && map->codepoint != codepoint) { map += 1; }
        AssertMsg(map->codepoint == codepoint, "Glyph Codepoint is not present in Atlas");
        return map;
    };
    
    AssertMsg(c, "Context is null\n");
    LogMsg(font, "Passed font is null\n");
    if(!font) { return; }
    
    s32 currXPos = xPos;
    s32 currYPos = yPos;
    f64 scaling = (f64)pixelHeight / (f64)font->pixelHeight;
    s32 lineSpace = font->ascent*scaling - font->descent*scaling + font->lineGap*scaling;
    
#ifdef LS_UI_OPENGL_BACKEND
    
    AssertMsg(font->isAtlas == TRUE, "Using a glyph array with the OpenGL Backend is currently not supported\n");
    
    f32 colorRed   = (f32)textColor.r / 255.0f;
    f32 colorGreen = (f32)textColor.g / 255.0f;
    f32 colorBlue  = (f32)textColor.b / 255.0f;
    
    for(u32 i = 0; i < text.len; i++)
    {
        u32 codepoint = 0xFFFFFFFF;
        if constexpr(typeid(T) == typeid(utf32))
        { codepoint = text.data[i]; }
        else if constexpr(typeid(T) == typeid(utf8))
        { codepoint = ls_utf32CharFromUtf8(text, i); }
        else
        { AssertMsg(FALSE, "Invalid use of string type. Only utf32 and utf8 are supported"); }
        AssertMsgF(codepoint <= font->maxCodepoint, "GlyphIndex %d OutOfBounds\n", codepoint);
        
        MapEntry *map = getMapEntryFromAtlas(font, codepoint);
        
        f64 texelLeft  = (f64)map->pixelX / (f64)font->atlasWidth;
        f64 texelRight = (f64)(map->pixelX+map->width) / (f64)font->atlasWidth;
        f64 texelBot   = (f64)map->pixelY / (f64)font->atlasHeight;
        f64 texelTop   = (f64)(map->pixelY+map->height) / (f64)font->atlasHeight;
        
        //TODOf32 limitAlpha = (f32)map->onEdgeValue / 255.0f;
        f32 limitAlpha = 160.0f / 255.0f;
        
        //NOTE: HOW THE FUCK TO POSITION GLYPHS!!!
        //NOTE: HOW THE FUCK TO POSITION GLYPHS!!!
        //NOTE: HOW THE FUCK TO POSITION GLYPHS!!!
        //   ----> https://github.com/nothings/stb/issues/450
        // Proper vertical positioning of a glyph requires this y1 computation.
        // Basically, (y1 - y0) == Height of the bounding box
        // y1 represents the portion of the glyph below the baseline (usually positive)
        // y0 represents the portion of the glyph above the baseline (usually negative)
        // The font ascent represents the highest point from the baseline a glyph will draw (usually positive)
        // The descent represent the lowest point from the baseline a glyph will draw (usually negative)
        // The line gap is simply the distance between two separate lines (usually positive)
        // Thus to compute the distance between 2 consecutive lines baselines you do:
        //  linespace = ascent - descent + linegap
        //NOTE: HOW THE FUCK TO POSITION GLYPHS!!!
        //NOTE: HOW THE FUCK TO POSITION GLYPHS!!!
        //NOTE: HOW THE FUCK TO POSITION GLYPHS!!!
        s32 y1 = map->height*scaling + map->yOff*scaling;
        s32 realY = currYPos - y1;
        
        UIRect norm = ls_uiScreenCoordsToUnitSquare(c, currXPos, realY, 
                                                    map->width*scaling, map->height*scaling);
        
        //NOTE: Escape the whitespace drawing because for some reason the fonts render it as the null glyph?
        if(ls_UTF32IsWhitespace(codepoint)) {
            currXPos += map->xAdv*scaling;
            if(codepoint == (u32)'\n') { currXPos = xPos; currYPos -= lineSpace; }
            continue;
        }
        
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, limitAlpha);
        
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, font->texID);
        //TODO: We will care about these kinda stuff in the near future
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        glColor4f(colorRed, colorGreen, colorBlue, 1.0f);
        glBegin(GL_TRIANGLES);
        
        glTexCoord2f(texelLeft,  texelBot); glVertex2f(norm.leftX,  norm.topY);
        glTexCoord2f(texelLeft,  texelTop); glVertex2f(norm.leftX,  norm.botY);
        glTexCoord2f(texelRight, texelBot); glVertex2f(norm.rightX, norm.topY);
        glTexCoord2f(texelRight, texelBot); glVertex2f(norm.rightX, norm.topY);
        glTexCoord2f(texelLeft,  texelTop); glVertex2f(norm.leftX,  norm.botY);
        glTexCoord2f(texelRight, texelTop); glVertex2f(norm.rightX, norm.botY);
        
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_ALPHA_TEST);
        
        currXPos += map->xAdv*scaling;
        if(codepoint == (u32)'\n') { currXPos = xPos; currYPos -= lineSpace; }
    }
#else
    
    for(u32 i = 0; i < text.len; i++)
    {
        u32 codepoint = 0xFFFFFFFF;
        if constexpr(typeid(T) == typeid(utf32))
        { codepoint = text.data[i]; }
        else if constexpr(typeid(T) == typeid(utf8))
        { codepoint = ls_utf32CharFromUtf8(text, i); }
        else
        { AssertMsg(FALSE, "Invalid use of string type. Only utf32 and utf8 are supported"); }
        
        AssertMsgF(codepoint <= font->maxCodepoint, "GlyphIndex %d OutOfBounds\n", codepoint);
        
        //TODO: I don't like branching inside the loop for a constant result, 
        //      the branch predictor should get it though...
        if(font->isAtlas)
        {
            MapEntry *map = getMapEntryFromAtlas(font, codepoint);
            UIGlyph currGlyph = { 
                .data = &font->fontAtlasSDF[map->pixelY*font->atlasWidth + map->pixelX],
                .width = (u32)map->width,
                .height = (u32)map->height,
                .x0 = map->xOff,
                .y0 = map->yOff,
                .y1 = map->height + map->yOff,
                .xAdv = map->xAdv,
                .yAdv = 0
            };
            
            ls_uiSDFGlyph(c, &currGlyph, currXPos, currYPos, font->atlasWidth, scaling, 
                          threadRect, scissor, textColor);
            
            currXPos += map->xAdv*scaling;
            if(codepoint == (u32)'\n') { currXPos = xPos; currYPos -= lineSpace; }
        }
        else
        {
            UIGlyph *currGlyph = &font->glyph[codepoint];
            ls_uiGlyph(c, currXPos, currYPos, threadRect, scissor, currGlyph, textColor);
            
            s32 kernAdvance = 0;
            if(i < text.len-1) { kernAdvance = ls_uiGetKernAdvance(font, text.data[i], text.data[i+1]); }
            
            currXPos += (currGlyph->xAdv + kernAdvance);
            //NOTETODO VERY BAD!! need to determine
            if(codepoint == (u32)'\n') { currYPos -= font->pixelHeight; currXPos = xPos; }
        }
    }
#endif
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
        u32 indexInGlyphArray = text.data[i];
        AssertMsgF(indexInGlyphArray <= font->maxCodepoint, "GlyphIndex %d OutOfBounds\n", indexInGlyphArray);
        
        if(indexInGlyphArray == (u32)'\n') {
            currYPos -= font->pixelHeight;
            currXPos = layout.minX;
            continue;
        }
        
        UIGlyph *currGlyph = &font->glyph[indexInGlyphArray];
        ls_uiGlyph(c, currXPos, currYPos, threadRect, scissor, currGlyph, textColor);
        
        s32 kernAdvance = 0;
        if(i < text.len-1) { kernAdvance = ls_uiGetKernAdvance(font, text.data[i], text.data[i+1]); }
        
        s32 newAdvance = currGlyph->xAdv + kernAdvance;
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
    struct MapEntry
    { //NOTE: I'm gonna assume this will be packed, being a multiple of 32 bits in size...
        u32 codepoint;
        s32 pixelX;
        s32 pixelY;
        s32 width;
        s32 height;
        s32 xOff;
        s32 yOff;
        s32 xAdv;
        s32 leftSB;
    };
    
    //NOTE: Look for the glyph pixel data in the map
    auto getMapEntryFromAtlas = [](UIFont *font, u32 codepoint) -> MapEntry *{
        s32 mapSize    = *((s32*)(font->fontAtlasSDF + ((font->atlasWidth*font->atlasHeight) - sizeof(s32))));
        s32 glyphCount = font->cpCount;
        MapEntry *map  = (MapEntry *)(font->fontAtlasSDF + ((font->atlasWidth*font->atlasHeight) - mapSize));
        while(glyphCount-- && map->codepoint != codepoint) { map += 1; }
        AssertMsg(map->codepoint == codepoint, "Glyph Codepoint is not present in Atlas");
        return map;
    };
    
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
        u32 codepoint = 0xFFFFFFFF;
        if constexpr(typeid(T) == typeid(utf32))
        { codepoint = text.data[i]; }
        else if constexpr(typeid(T) == typeid(utf8))
        { codepoint = ls_utf32CharFromUtf8(text, i); }
        else
        { AssertMsg(FALSE, "Invalid use of string type. Only utf32 and utf8 are supported"); }
        
        AssertMsgF(codepoint <= font->maxCodepoint, "GlyphIndex %d OutOfBounds\n", codepoint);
        
        //TODO: I don't like branching inside the loop for a constant result, 
        //      the branch predictor should get it though...
        if(font->isAtlas)
        {
            MapEntry *map = getMapEntryFromAtlas(font, codepoint);
            totalWidth += map->xAdv*scaling;
            if(codepoint == (u32)'\n') { totalWidth = 0; totalHeight += lineSpace; }
            if(totalWidth > maxWidth) { maxWidth = totalWidth; }
        }
        else
        {
            UIGlyph *currGlyph = &font->glyph[codepoint];
            
            s32 kernAdvance = 0;
            if(i < text.len-1) { kernAdvance = ls_uiGetKernAdvance(font, text.data[i], text.data[i+1]); }
            
            if(codepoint == (u32)'\n')
            {
                totalHeight += font->pixelHeight;
                totalWidth   = 0;
                continue;
            }
            
            totalWidth += (currGlyph->xAdv + kernAdvance);
            if(totalWidth > maxWidth) { maxWidth = totalWidth; }
        }
    }
    
    UIRect result = {0, 0, maxWidth, totalHeight};
    return result;
}

//TODO: This is only used in a lambda inside ls_uiTextBox()
//      So, maybe either find a way to remove this, or just fit it inside ls_uiTextBox() instead!
s32 ls_uiGlyphStringFit(UIContext *c, UIFont *font, utf32 text, s32 maxLen)
{
    AssertMsg(c, "Context is null\n");
    LogMsg(font, "Passed font is null\n");
    if(!font) { return 0; }
    
    s32 totalLen = 0;
    for(s32 i = text.len-1; i > 0; i--)
    {
        u32 indexInGlyphArray = text.data[i];
        AssertMsgF(indexInGlyphArray <= font->maxCodepoint, "GlyphIndex %d OutOfBounds\n", indexInGlyphArray);
        
        UIGlyph *currGlyph = &font->glyph[indexInGlyphArray];
        
        s32 kernAdvance = 0;
        if(i > 0) { kernAdvance = ls_uiGetKernAdvance(font, text.data[i-1], text.data[i]); }
        
        totalLen += (currGlyph->xAdv + kernAdvance);
        if(totalLen >= maxLen) { return i; }
    }
    
    return 0;
}

//TODO: This is only used in a lambda inside ls_uiTextBox()
//      So, maybe either find a way to remove this, or just fit it inside ls_uiTextBox() instead!
s32 ls_uiMonoGlyphMaxIndexDiff(UIContext *c, UIFont *font, s32 width)
{
    AssertMsg(c, "Context is null\n");
    LogMsg(font, "Passed font is null\n");
    if(!font) { return 0; }
    
    s32 kernAdvance = ls_uiGetKernAdvance(font, 'a', 'w');
    UIGlyph *aGlyph = &font->glyph['a'];
    
    s32 maxGlyphs = width / (aGlyph->xAdv + kernAdvance);
    return maxGlyphs;
}

//NOTE: ls_uiGlyphStringLayout calculates the height of the rectangle of the layout text 
//      (finalLayout.y, finalLayout.h in the return value).
//      It also returns the coordinates of where the next character would go, if you were to keep writing.
//      (finalLayout.x, finalLayout.y in the return value).
//
//      This is done to allow automatic layout of multiple strings inside a given rect (UILayoutRect).
UIRect ls_uiGlyphStringLayout(UIContext *c, UIFont *font, UILayoutRect layout, utf32 text)
{
    //TODO: Only one quirk remains, the y offset is determined based on the font height of the current element, 
    //      which obviously generates too large gaps when the font becomes smaller from one call to the 
    //      other and too small gaps when the font becomes bigger. The solution to this is to consider 
    //      the y Position when rendering a glyph the top left of the glyph (rather than the bottom left), 
    //      and subtract the font height to obtain the baseline. This way the y offset in layouting will 
    //      correctly move the y coordinate of the next line below the current line, regardless of font size.
    //      P.S.
    //      The baseline should already be present in the font, so why should I compute it?
    AssertMsg(c, "Context is null\n");
    LogMsg(font, "Passed font is null\n");
    if(!font) { return {}; }
    
    s32 currX          = layout.startX;
    s32 currY          = layout.startY;
    s32 currLineHeight = font->pixelHeight;
    for(u32 i = 0; i < text.len; i++)
    {
        u32 indexInGlyphArray = text.data[i];
        AssertMsgF(indexInGlyphArray <= font->maxCodepoint, "GlyphIndex %d OutOfBounds\n", indexInGlyphArray);
        
        if(indexInGlyphArray == (u32)'\n')
        { currX = layout.minX; currY -= font->pixelHeight; currLineHeight += font->pixelHeight; continue; }
        
        UIGlyph *currGlyph = &font->glyph[indexInGlyphArray];
        
        s32 kernAdvance = 0;
        if(i < text.len-1) { kernAdvance = ls_uiGetKernAdvance(font, text.data[i], text.data[i+1]); }
        
        s32 newAdvance = currGlyph->xAdv + kernAdvance;
        if(currX + newAdvance > layout.maxX)
        { currX = layout.minX; currY -= font->pixelHeight; currLineHeight += font->pixelHeight; continue; }
        
        currX += newAdvance;
    }
    
    //UIRect finalLayout = { currX, currY, layout.maxX, currLineHeight };
    UIRect finalLayout = { currX, currY, layout.maxX, layout.startY - currY + (s32)font->pixelHeight };
    
    return finalLayout;
}

void ls_uiSelectFontByPixelHeight(UIContext *c, u32 pixelHeight)
{
    LogMsg(c->fonts, "No fonts were loaded\n");
    AssertMsg(c->currFont, "The currFont was not selected!\n");
    if(!c->fonts) { return; }
    
#ifdef LS_UI_OPENGL_BACKEND
    c->currPixelHeight = pixelHeight;
#else
    if(c->currFont->isAtlas)
    {
        c->currPixelHeight = pixelHeight;
        return;
    }
    else
    {
        //TODO: Hardcoded
        for(u32 i = 0; i < 4; i++)
        { if(c->fonts[i].pixelHeight == pixelHeight) { c->currFont = &c->fonts[i]; return; } }
    }
    
    AssertMsg(FALSE, "Asked pixelHeight not available\n");
#endif
}

inline
s32 ls_uiSelectFontByFontSize(UIContext *c, UIFontSize fontSize)
{ 
    LogMsg(c->fonts, "No fonts were loaded\n");
    if(!c->fonts) { return 0; }
#ifdef LS_UI_OPENGL_BACKEND
    TODO;
#else
    c->currFont = &c->fonts[fontSize]; return c->currFont->pixelHeight;
#endif
}

UIButton ls_uiButtonInit(UIContext *c, UIButtonStyle s, UICallback onClick, UICallback onHold = NULL, void *userData = NULL)
{
    AssertMsg(c, "UI Context is null\n");
    
    UIButton Result = {
        {onClick, userData, onHold, userData, NULL, NULL}, 
        s, {}, 0, 0, 0, FALSE, FALSE 
    };
    
    return Result;
}

UIButton ls_uiButtonInit(UIContext *c, UIButtonStyle s, const char32_t *text, UICallback onClick,
                         UICallback onHold = NULL, void *userData = NULL)
{
    Arena prev = ls_arenaUse(c->widgetArena);
    
    AssertMsg(c, "UI Context is null\n");
    AssertMsg(c->currFont, "Font is not selected\n");
    
    //TODO: Super mega shit for pixelHeight
    utf32 name = ls_utf32FromUTF32(text);
    s32 pixelHeight = c->currFont->pixelHeight;
    if(c->currFont->isAtlas) { pixelHeight = c->currPixelHeight; }
    
#ifndef LS_UI_OPENGL_BACKEND
    s32 height = pixelHeight + 2; //Add Margin above and below text
    //Add margin on each side
    s32 width = ls_uiGlyphStringRect(c, c->currFont, name, pixelHeight).w + 16;
#else
    s32 height = pixelHeight + 2; //Add Margin above and below text
    //Add margin on each side
    s32 width = ls_uiGlyphStringRect(c, c->currFont, name, pixelHeight).w + 16;
#endif
    
    UIButton Result = {
        {onClick, userData, onHold, userData, NULL, NULL}, 
        s, name, 0, width, height, FALSE, FALSE
    };
    
    ls_arenaUse(prev);
    return Result;
}

UIButton ls_uiButtonInit(UIContext *c, UIButtonStyle s, utf32 text, UICallback onClick,
                         UICallback onHold = NULL, void *userData = NULL)
{
    AssertMsg(c, "UI Context is null\n");
    AssertMsg(c->currFont, "Font is not selected\n");
    
    //TODO: Super mega shit for pixelHeight
    s32 pixelHeight = c->currFont->pixelHeight;
    if(c->currFont->isAtlas) { pixelHeight = c->currPixelHeight; }
    
#ifndef LS_UI_OPENGL_BACKEND
    s32 height = pixelHeight + 2; //Add Margin above and below text
    //Add margin on each side
    s32 width = ls_uiGlyphStringRect(c, c->currFont, text, pixelHeight).w + 16;
#else
    s32 height = c->currPixelHeight + 2; //Add Margin above and below text
    //Add margin on each side
    s32 width = ls_uiGlyphStringRect(c, c->currFont, text, pixelHeight).w + 16;
#endif
    
    UIButton Result = {
        {onClick, userData, onHold, userData, NULL, NULL}, 
        s, text, 0, width, height, FALSE, FALSE
    };
    
    return Result;
}

void ls_uiButtonInit(UIContext *c, UIButton *b, UIButtonStyle s, utf32 text, UICallback onClick,
                     UICallback onHold = NULL, void *userData = NULL)
{
    AssertMsg(c, "UI Context is null\n");
    AssertMsg(c->currFont, "Font is not selected\n");
    
    b->style         = s;
    b->name          = text;
    b->callback1     = onClick;
    b->callback2     = onHold;
    b->callback1Data = userData;
    b->callback2Data = userData;
    
    //TODO: Super mega shit for pixelHeight
    s32 pixelHeight = c->currFont->pixelHeight;
    if(c->currFont->isAtlas) { pixelHeight = c->currPixelHeight; }
    
#ifndef LS_UI_OPENGL_BACKEND
    s32 height = pixelHeight + 2; //Add Margin above and below text
    //Add margin on each side
    s32 width = ls_uiGlyphStringRect(c, c->currFont, text, pixelHeight).w + 16;
#else
    s32 height = c->currPixelHeight + 2; //Add Margin above and below text
    //Add margin on each side
    s32 width = ls_uiGlyphStringRect(c, c->currFont, text, pixelHeight).w + 16;
#endif
    
    b->w = width;
    b->h = height;
}

void ls_uiButtonInit(UIContext *c, UIButton *b, UIButtonStyle s, const char32_t *t, UICallback onClick,
                     UICallback onHold = NULL, void *data = NULL)
{
    Arena prev = ls_arenaUse(c->widgetArena);
    
    AssertMsg(c, "UI Context is null\n");
    AssertMsg(c->currFont, "Font is not selected\n");
    
    b->style   = s;
    
    //TODO: Should this be a ls_utf32Constant() ??? I've been passed a constant literal...
    b->name          = ls_utf32FromUTF32(t);
    b->callback1     = onClick;
    b->callback2     = onHold;
    b->callback1Data = data;
    b->callback2Data = data;
    
    //TODO: Super mega shit for pixelHeight
    s32 pixelHeight = c->currFont->pixelHeight;
    if(c->currFont->isAtlas) { pixelHeight = c->currPixelHeight; }
    
#ifndef LS_UI_OPENGL_BACKEND
    s32 height = pixelHeight + 2; //Add Margin above and below text
    //Add margin on each side
    s32 width = ls_uiGlyphStringRect(c, c->currFont, b->name, pixelHeight).w + 16;
#else
    s32 height = c->currPixelHeight + 2; //Add Margin above and below text
    //Add margin on each side
    s32 width = ls_uiGlyphStringRect(c, c->currFont, b->name, pixelHeight).w + 16;
#endif
    
    b->w = width;
    b->h = height;
    
    ls_arenaUse(prev);
}

//TODO:Menus use buttons, but also claim Focus, which means I can't use the global focus trick to avoid input
//     handling between overlapping elements.
//     I don't think the menu should deal with things like this [It shouldn't hold the close button first,
//     and it also shouldn't use 'normal' buttons for its drop down sub-menus, so... basically @MenuIsShit
//     and I wanna redo it completely.

b32 ls_uiButton(UIContext *c, UIButton *button, s32 xPos, s32 yPos, Color bkgColor, s32 zLayer = 0)
{
    Input *UserInput = &c->UserInput;
    
    b32 inputUse = FALSE;
    
    Color textColor   = c->textColor;
    Color borderColor = c->borderColor;
    
    if(button->style == UIBUTTON_TEXT_NOBORDER) { bkgColor = c->backgroundColor; }
    
    if(button->isInactive == TRUE)
    {
        textColor = ls_uiDarkenRGB(textColor, 0.50f);
        bkgColor  = ls_uiDarkenRGB(bkgColor, 0.50f);
        
        RenderCommand command = { UI_RC_BUTTON, xPos, yPos, button->w, button->h };
        command.button        = button;
        command.bkgColor      = bkgColor;
        command.borderColor   = borderColor;
        command.textColor     = textColor;
        ls_uiPushRenderCommand(c, command, zLayer);
        
        return FALSE;
    }
    
    if(MouseInRect(xPos, yPos, button->w, button->h-1))// && ls_uiInFocus(cxt, 0))
    { 
        button->isHot = TRUE;
        bkgColor = c->highliteColor;
        if(button->style == UIBUTTON_LINK) { textColor = c->highliteColor; }
        
        //b32 noCapture = ls_uiHasCapture(cxt, 0);
        
        if(LeftClick)// && noCapture)
        {
            //NOTE: button->onClick
            if(button->callback1) { inputUse |= button->callback1(c, button->callback1Data); }
        }
        
        if(LeftHold)//  && noCapture)
        {
            button->isHeld = TRUE;
            bkgColor       = c->pressedColor;
            
            //NOTE: button->onHold
            if(button->callback2) { inputUse |= button->callback2(c, button->callback2Data); }
        }
    }
    
    RenderCommand command = { UI_RC_BUTTON, xPos, yPos, button->w, button->h };
    command.button        = button;
    command.bkgColor      = bkgColor;
    command.borderColor   = borderColor;
    command.textColor     = textColor;
    ls_uiPushRenderCommand(c, command, zLayer);
    
    return inputUse;
}

//TODO: Why do I have an almost copy-paste of this function above? Compact them...
b32 ls_uiButton(UIContext *c, UIButton *button, s32 xPos, s32 yPos, s32 zLayer = 0)
{
    Input *UserInput = &c->UserInput;
    
    b32 inputUse = FALSE;
    
    Color bkgColor    = c->widgetColor;
    Color textColor   = c->textColor;
    Color borderColor = c->borderColor;
    
    if(button->style == UIBUTTON_TEXT_NOBORDER) { bkgColor = c->backgroundColor; }
    
    if(button->isInactive == TRUE)
    {
        textColor = ls_uiDarkenRGB(textColor, 0.50f);
        bkgColor  = ls_uiDarkenRGB(bkgColor, 0.50f);
        
        RenderCommand command = { UI_RC_BUTTON, xPos, yPos, button->w, button->h };
        command.button        = button;
        command.bkgColor      = bkgColor;
        command.borderColor   = borderColor;
        command.textColor     = textColor;
        ls_uiPushRenderCommand(c, command, zLayer);
        
        return FALSE;
    }
    
    if(MouseInRect(xPos, yPos, button->w, button->h-1))// && ls_uiInFocus(cxt, 0))
    { 
        button->isHot = TRUE;
        bkgColor = c->highliteColor;
        if(button->style == UIBUTTON_LINK) { textColor = c->highliteColor; }
        
        //b32 noCapture = ls_uiHasCapture(cxt, 0);
        
        if(LeftClick)// && noCapture)
        {
            //NOTE: button->onClick
            if(button->callback1) { inputUse |= button->callback1(c, button->callback1Data); }
        }
        
        if(LeftHold)//  && noCapture)
        {
            button->isHeld = TRUE;
            bkgColor       = c->pressedColor;
            
            //NOTE: button->onHold
            if(button->callback2) { inputUse |= button->callback2(c, button->callback2Data); }
        }
    }
    
    RenderCommand command = { UI_RC_BUTTON, xPos, yPos, button->w, button->h };
    command.button        = button;
    command.bkgColor      = bkgColor;
    command.borderColor   = borderColor;
    command.textColor     = textColor;
    ls_uiPushRenderCommand(c, command, zLayer);
    
    return inputUse;
}

UICheck ls_uiCheckInit(UIContext *c, UICheckStyle s,
                       u8 *bmpActive, u8 *bmpInactive, s32 w, s32 h, UICallback onChange, void *data)
{
    UICheck result = {};
    
    result.style       = s;
    result.isActive    = FALSE;
    result.bmpActive   = bmpActive;
    result.bmpInactive = bmpInactive;
    result.w           = w;
    result.h           = h;
    
    result.callback1     = onChange;
    result.callback1Data = data;
    
    return result;
}

UICheck ls_uiCheckInit(UIContext *c, UICheckStyle s, u8 *bmpInactive, s32 w, s32 h,
                       u8 *bmpAdditive, s32 addW, s32 addH, UICallback onChange, void *data)
{
    UICheck result = {};
    
    result.style       = s;
    result.isActive    = FALSE;
    result.bmpInactive = bmpInactive;
    result.w           = w;
    result.h           = h;
    result.bmpAdditive = bmpAdditive;
    result.addW        = addW;
    result.addH        = addH;
    
    result.callback1     = onChange;
    result.callback1Data = data;
    
    return result;
}

b32 ls_uiCheck(UIContext *c, UICheck *check, s32 x, s32 y, s32 zLayer = 0)
{
    Input *UserInput = &c->UserInput;
    b32 inputUse = FALSE;
    
    if(MouseInRect(x, y, check->w, check->h) && ls_uiHasCapture(c, 0))
    {
        if(LeftClick)
        {
            check->isActive = !check->isActive;
            
            //NOTE: check->onChange
            if(check->callback1) { inputUse |= check->callback1(c, check->callback1Data); }
        }
    }
    
    RenderCommand command = { UI_RC_CHECK, x, y, check->w, check->h };
    command.check         = check;
    ls_uiPushRenderCommand(c, command, zLayer);
    
    return inputUse;
}

UIRect ls_uiLabelRect(UIContext *c, utf32 label, s32 xPos, s32 yPos)
{
    s32 marginX    = 0.3f*c->currFont->pixelHeight;
    s32 marginY    = 0.3f*c->currFont->pixelHeight;
    
    UIRect rect = ls_uiGlyphStringRect(c, c->currFont, label, c->currFont->pixelHeight);
    s32 rectWidth  = rect.w + 2*marginX;
    s32 rectHeight = rect.h + 2*marginY; //TODO: Ascent/Descent, not this bullshit.
    
    return { xPos, yPos, rectWidth, rectHeight };
}

void ls_uiLabelInRect(UIContext *c, utf32 label, s32 xPos, s32 yPos,
                      Color bkgColor, Color borderColor, Color textColor, s32 zLayer = 0)
{
    s32 marginX    = 0.3f*c->currFont->pixelHeight;
    s32 marginY    = 0.25f*c->currFont->pixelHeight;
    
    UIRect rect = ls_uiGlyphStringRect(c, c->currFont, label, c->currFont->pixelHeight);
    s32 rectWidth  = rect.w + 2*marginX;
    s32 rectHeight = rect.h + 2*marginY; //TODO: Ascent/Descent, not this bullshit.
    
    s32 labelOffset = rect.h - c->currFont->pixelHeight;
    ls_uiLabel(c, label, xPos + marginX, yPos + 2*marginY + labelOffset, textColor, zLayer);
    ls_uiRect(c, xPos, yPos, rectWidth, rectHeight, bkgColor, borderColor, zLayer);
}

void ls_uiLabelInRect(UIContext *c, utf8 label, s32 xPos, s32 yPos,
                      Color bkgColor, Color borderColor, Color textColor, s32 zLayer = 0)
{
    s32 marginX    = 0.3f*c->currFont->pixelHeight;
    s32 marginY    = 0.25f*c->currFont->pixelHeight;
    
    UIRect rect = ls_uiGlyphStringRect(c, c->currFont, label, c->currFont->pixelHeight);
    s32 rectWidth  = rect.w + 2*marginX;
    s32 rectHeight = rect.h + 2*marginY; //TODO: Ascent/Descent, not this bullshit.
    
    s32 labelOffset = rect.h - c->currFont->pixelHeight;
    ls_uiLabel(c, label, xPos + marginX, yPos + 2*marginY + labelOffset, textColor, zLayer);
    ls_uiRect(c, xPos, yPos, rectWidth, rectHeight, bkgColor, borderColor, zLayer);
}

void ls_uiLabelInRect(UIContext *c, utf8 label, s32 xPos, s32 yPos, s32 minWidth, s32 minHeight,
                      Color bkgColor, Color borderColor, Color textColor, s32 zLayer = 0)
{
    s32 marginX    = 0.3f*c->currFont->pixelHeight;
    s32 marginY    = 0.25f*c->currFont->pixelHeight;
    
    UIRect rect = ls_uiGlyphStringRect(c, c->currFont, label, c->currFont->pixelHeight);
    s32 rectWidth  = rect.w + 2*marginX;
    s32 rectHeight = rect.h + 2*marginY; //TODO: Ascent/Descent, not this bullshit.
    
    if(rectWidth  < minWidth)  { marginX += (minWidth - rectWidth) / 2; rectWidth = minWidth; }
    if(rectHeight < minHeight) { marginY += (minHeight - rectHeight) / 2; rectHeight = minHeight; }
    
    s32 labelOffset = rect.h - c->currFont->pixelHeight;
    ls_uiLabel(c, label, xPos + marginX, yPos + 2*marginY + labelOffset, textColor, zLayer);
    ls_uiRect(c, xPos, yPos, rectWidth, rectHeight, bkgColor, borderColor, zLayer);
}

void ls_uiLabel(UIContext *c, utf32 label, f32 relX, f32 relY, Color textColor, s32 zLayer = 0)
{
    s32 xPos = c->width * relX;
    s32 yPos = c->height * relY;
    
    ls_uiLabel(c, label, xPos, yPos, textColor, zLayer);
}

void ls_uiLabel(UIContext *c, utf32 label, s32 xPos, s32 yPos, Color textColor, s32 zLayer = 0)
{
    AssertMsg(c, "Context pointer was null");
    AssertMsg(c->currFont, "No font was selected before sizing a label\n");
    
    if(label.len == 0) { return; }
    
    UIRect rect = ls_uiGlyphStringRect(c, c->currFont, label, c->currPixelHeight);
    s32 yBaseOff = rect.h - c->currPixelHeight;
    
    RenderCommand command = { UI_RC_LABEL32, xPos, yPos - yBaseOff, rect.w, rect.h };
    command.label32 = label;
    command.textColor = textColor;
    ls_uiPushRenderCommand(c, command, zLayer);
}

void ls_uiLabel(UIContext *c, const char32_t *label, s32 xPos, s32 yPos, Color textColor, s32 zLayer = 0)
{
    utf32 lab = ls_utf32Constant(label);
    ls_uiLabel(c, lab, xPos, yPos, textColor, zLayer);
}

void ls_uiLabel(UIContext *c, utf8 label, s32 xPos, s32 yPos, Color textColor, s32 zLayer = 0)
{
    AssertMsg(c, "Context pointer was null");
    AssertMsg(c->currFont, "No font was selected before sizing a label\n");
    
    if(label.len == 0) { return; }
    
    UIRect rect = ls_uiGlyphStringRect(c, c->currFont, label, c->currPixelHeight);
    s32 yBaseOff = rect.h - c->currPixelHeight;
    
    RenderCommand command = { UI_RC_LABEL8, xPos, yPos - yBaseOff, rect.w, rect.h };
    command.label8 = label;
    command.textColor = textColor;
    ls_uiPushRenderCommand(c, command, zLayer);
}

void ls_uiLabel(UIContext *c, const u8 *label, s32 xPos, s32 yPos, Color textColor, s32 zLayer = 0)
{
    utf8 lab = ls_utf8Constant(label);
    ls_uiLabel(c, lab, xPos, yPos, textColor, zLayer);
}

void ls_uiLabel(UIContext *c, utf32 label, s32 xPos, s32 yPos, s32 zLayer = 0)
{
    ls_uiLabel(c, label, xPos, yPos, c->textColor, zLayer);
}

void ls_uiLabel(UIContext *c, const char32_t *label, s32 xPos, s32 yPos, s32 zLayer = 0)
{
    utf32 lab = ls_utf32Constant(label);
    ls_uiLabel(c, lab, xPos, yPos, c->textColor, zLayer);
}

void ls_uiLabel(UIContext *c, utf8 label, s32 xPos, s32 yPos, s32 zLayer = 0)
{
    ls_uiLabel(c, label, xPos, yPos, c->textColor, zLayer);
}

void ls_uiLabel(UIContext *c, const u8 *label, s32 xPos, s32 yPos, s32 zLayer = 0)
{
    utf8 lab = ls_utf8Constant(label);
    ls_uiLabel(c, lab, xPos, yPos, c->textColor, zLayer);
}

UILayoutRect ls_uiLabelLayout(UIContext *c, utf32 label, UILayoutRect layout, UIRect deltaPos,
                              Color textColor, s32 zLayer = 0)
{
    AssertMsg(c, "Context pointer was null");
    AssertMsg(c->currFont, "No font was selected before sizing a label\n");
    
    if(label.len == 0) { return {}; }
    
    //NOTE: layoutRegion.y refers to the top of the string, which grows downward
    //      The rect containing it has the y growing up, thus we offset it by it's height, deltaPos.h
    RenderCommand command = { UI_RC_LABEL_LAYOUT, layout.minX, deltaPos.y, layout.maxX-layout.minX, deltaPos.h };
    command.layout = { layout.minX, layout.minY, layout.maxX, deltaPos.h, layout.startX, layout.startY-deltaPos.h };
    command.label32       = label;
    command.textColor     = textColor;
    ls_uiPushRenderCommand(c, command, zLayer);
    
    UILayoutRect newLayout = { layout.minX, layout.minY, layout.maxX, deltaPos.h, deltaPos.x, deltaPos.y };
    return newLayout;
}

UILayoutRect ls_uiLabelLayout(UIContext *c, utf32 label, UILayoutRect layout, Color textColor, s32 zLayer = 0)
{
    AssertMsg(c, "Context pointer was null");
    AssertMsg(c->currFont, "No font was selected before sizing a label\n");
    
    if(label.len == 0) { return {}; }
    
    UIRect deltaPos = ls_uiGlyphStringLayout(c, c->currFont, layout, label);
    
    //NOTE: layoutRegion.y refers to the top of the string, which grows downward
    //      The rect containing it has the y growing up, thus we offset it by it's height, deltaPos.h
    RenderCommand command = { UI_RC_LABEL_LAYOUT, layout.minX, deltaPos.y, layout.maxX-layout.minX, deltaPos.h };
    command.layout = { layout.minX, layout.minY, layout.maxX, deltaPos.h, layout.startX, layout.startY-deltaPos.h };
    command.label32       = label;
    command.textColor     = textColor;
    ls_uiPushRenderCommand(c, command, zLayer);
    
    UILayoutRect newLayout = { layout.minX, layout.minY, layout.maxX, deltaPos.h, deltaPos.x, deltaPos.y };
    return newLayout;
}

UILayoutRect ls_uiLabelLayout(UIContext *c, const char32_t *label, UILayoutRect layout, 
                              Color textColor, s32 zLayer = 0)
{
    utf32 lab = ls_utf32Constant(label);
    return ls_uiLabelLayout(c, lab, layout, textColor, zLayer);
}

UILayoutRect ls_uiLabelLayout(UIContext *c, utf32 label, UILayoutRect layout, s32 zLayer = 0)
{
    return ls_uiLabelLayout(c, label, layout, c->textColor, zLayer);
}

UILayoutRect ls_uiLabelLayout(UIContext *c, const char32_t *label, UILayoutRect layout, s32 zLayer = 0)
{
    utf32 lab = ls_utf32Constant(label);
    return ls_uiLabelLayout(c, lab, layout, c->textColor, zLayer);
}

void ls_uiTextBoxClear(UIContext *c, UITextBox *box)
{
    Arena prev = ls_arenaUse(c->widgetArena);
    
    AssertMsg(c, "Context pointer was null");
    
    ls_utf32Clear(&box->text);
    
    box->isReadonly       = FALSE;
    box->caretIndex       = 0;
    box->caretLineIdx     = 0;
    box->lineCount        = 1;
    box->currLineBeginIdx = 0;
    
    box->selectBeginLine  = 0;
    box->selectEndLine    = 0;
    box->selectBeginIdx   = 0;
    box->selectEndIdx     = 0;
    box->isSelecting      = FALSE;
    box->viewBeginIdx     = 0;
    
    ls_arenaUse(prev);
}

//TODO: Now that viewEndIdx is deprecated these functions are a lot less usefuk
void ls_uiTextBoxSet(UIContext *c, UITextBox *box, const char32_t *s)
{
    Arena prev = ls_arenaUse(c->widgetArena);
    ls_utf32FromUTF32_t(&box->text, s);
    ls_arenaUse(prev);
}

void ls_uiTextBoxSet(UIContext *c, UITextBox *box, utf32 s)
{
    Arena prev = ls_arenaUse(c->widgetArena);
    ls_utf32Set(&box->text, s);
    ls_arenaUse(prev);
}

void ls_uiTextBoxInit(UIContext *c, UITextBox *box, s32 initialCap, s32 maxLen = 0, b32 singleLine = TRUE,
                      b32 readOnly = FALSE, UICallback preInput = NULL, UICallback postInput = NULL)
{
    Arena prev = ls_arenaUse(c->widgetArena);
    box->text         = ls_utf32Alloc(initialCap);
    box->maxLen       = maxLen;
    box->isSingleLine = singleLine;
    box->isReadonly   = readOnly;
    box->align        = UI_TB_ALIGN_LEFT;
    
    box->callback1    = preInput;
    box->callback2    = postInput;
    ls_arenaUse(prev);
}

//TODO: Text Alignment
//TODO: NonLethal display (like all maxLen numerical displays) is asymmetrical in the value range
//      it can represent.
//
//      I.E.  A maxLen = 4 textBox can represent: [-999, 9999]
//            Instead of the more correct:        [-999, 999]
b32 ls_uiTextBox(UIContext *c, UITextBox *box, s32 xPos, s32 yPos, s32 w, s32 h, s32 zLayer = 0)
{
    Arena prev = ls_arenaUse(c->widgetArena);
    
    Input *UserInput = &c->UserInput;
    b32 inputUse = FALSE;
    
    if(LeftClickIn(xPos, yPos, w, h-1) && ls_uiHasCapture(c, 0)) {
        ls_uiFocusChangeSameFrame(c, (u64 *)box);
        box->isCaretOn = TRUE;
    }
    
    //TODOHACKHACK
    if(box->lineCount == 0) box->lineCount = 1;
    //TODOHACKHACK
    
    //TODO: Hardcoded values.
    const s32 horzOff      = 12;
    const s32 viewAddWidth = w - 2*horzOff;
    
    //TODO: This shit is kinda strange.
    //const s32 maxIndexDiff = ls_uiMonoGlyphMaxIndexDiff(c, c->currFont, viewAddWidth);
    const s32 maxIndexDiff = c->currPixelHeight;
    
    auto lineBeginIdx = [box](s32 index) -> u32 {
        if(index <= 0) { 
            box->viewBeginIdx = 0;
            
            //TODONOTE: Very wrong.
            //if(box->text.data[0] == (char32_t)'\n') { return 1; }
            return 0;
        }
        
        u32 beginOffset    = ls_utf32RightFind(box->text, index, (char32_t)'\n');
        
        s32 realOffset = beginOffset+1;
        if(beginOffset == -1) { realOffset = 0; }
        return realOffset;
    };
    
    auto setIndices = [c, box, viewAddWidth, lineBeginIdx](s32 index) -> u32 {
        
        u32 realOffset    = lineBeginIdx(index);
        s32 lineLength    = index-realOffset;
        utf32 currLine    = { box->text.data + realOffset, lineLength, lineLength };
        u32 maxBeginIndex = ls_uiGlyphStringFit(c, c->currFont, currLine, viewAddWidth);
        
        box->viewBeginIdx = maxBeginIndex;
        
        return realOffset;
    };
    
    auto handleSelection = [UserInput, box](s32 direction) {
        
        AssertMsg((direction == -1) || (direction == 1) || (direction == -2) || (direction == 2) ||
                  (direction == -3) || (direction == 3), "Invalid direction passed to handleSelection\n");
        
        if(KeyHeld(keyMap::Shift))
        {
            if(!box->isSelecting) 
            { 
                box->isSelecting = TRUE;
                
                switch(direction)
                {
                    case -1:
                    case  1: //NOTE: Left/Right Arrow
                    {
                        box->selectBeginLine = box->caretLineIdx;
                        box->selectEndLine   = box->caretLineIdx;
                        
                        if(direction == -1)
                        {
                            if(box->text.data[box->caretIndex] == (char32_t)'\n')
                            { box->selectBeginLine = box->caretLineIdx - 1; }
                            else if(box->text.data[box->caretIndex + direction] == (char32_t)'\n')
                            { box->selectBeginLine = box->caretLineIdx - 1; }
                            
                            box->selectBeginIdx  = box->caretIndex - 1;
                            box->selectEndIdx    = box->caretIndex;
                        }
                        else
                        {
                            if(box->text.data[box->caretIndex + direction] == (char32_t)'\n')
                            { box->selectEndLine   = box->caretLineIdx + 1; }
                            
                            box->selectBeginIdx  = box->caretIndex;
                            box->selectEndIdx    = box->caretIndex + 1;
                        }
                    } break;
                    
                    
                    case -2: //NOTE: Home
                    {
                        if(box->caretIndex == 0) { box->isSelecting = FALSE; break; }
                        
                        box->selectBeginLine = 0;
                        box->selectEndLine   = box->caretLineIdx;
                        box->selectBeginIdx  = 0;
                        box->selectEndIdx    = box->caretIndex;
                    } break;
                    
                    case  2: //NOTE: End
                    {
                        if(box->caretIndex >= box->text.len) { box->isSelecting = FALSE; break; }
                        
                        box->selectBeginLine = box->caretLineIdx;
                        box->selectEndLine   = box->lineCount;
                        box->selectBeginIdx  = box->caretIndex;
                        box->selectEndIdx    = box->text.len;
                    } break;
                    
                    case -3: //NOTE: Up Arrow
                    { 
                        
                    } break;
                    
                    case 3: //NOTE: Down Arrow
                    { 
                        
                    } break;
                }
            }
            else
            {
                switch(direction)
                {
                    case -1:
                    case  1:
                    {
                        if(box->caretIndex == box->selectBeginIdx)
                        { 
                            box->selectBeginIdx += direction;
                            if(box->text.data[box->caretIndex + direction] == (char32_t)'\n')
                            { box->selectBeginLine += direction;}
                        }
                        else if(box->caretIndex == box->selectEndIdx)
                        { 
                            box->selectEndIdx   += direction;
                            if(box->text.data[box->caretIndex] == (char32_t)'\n') { box->selectEndLine += direction; }
                        }
                        else
                        { AssertMsg(FALSE, "Arrow Left Or Right -> Caret is not aligned with select anymore\n"); }
                        
                    } break;
                    
                    case -2:
                    {
                        if(box->caretIndex == box->selectBeginIdx)
                        { box->selectBeginIdx = 0; box->selectBeginLine = 0; }
                        else if(box->caretIndex == box->selectEndIdx)
                        { 
                            box->selectEndIdx    = box->selectBeginIdx; box->selectBeginIdx = 0; 
                            box->selectBeginLine = 0; box->selectEndLine = box->caretLineIdx;
                        }
                        else
                        { AssertMsg(FALSE, "Home -> Caret is not aligned with select anymore\n"); }
                        
                    } break;
                    case  2:
                    {
                        if(box->caretIndex == box->selectBeginIdx)
                        { 
                            box->selectBeginIdx  = box->selectEndIdx; box->selectEndIdx  = box->text.len; 
                            box->selectBeginLine = box->caretLineIdx; box->selectEndLine = box->lineCount;
                        }
                        else if(box->caretIndex == box->selectEndIdx)
                        { box->selectEndIdx   = box->text.len; box->selectEndLine = box->lineCount; }
                        else
                        { AssertMsg(FALSE, "End -> Caret is not aligned with select anymore\n"); }
                        
                    } break;
                }
                
                if(box->selectBeginIdx == box->selectEndIdx) 
                { box->isSelecting = FALSE; }
            }
        }
        else 
        { 
            if(box->isSelecting)
            { 
                box->isSelecting     = FALSE;
                box->selectEndIdx    = 0; box->selectBeginIdx  = 0; 
                box->selectBeginLine = 0; box->selectEndLine   = 0;
            }
        }
        
    };
    
    auto removeSelection = [=]() {
        box->lineCount   -= (box->selectEndLine - box->selectBeginLine);
        box->caretIndex   = box->selectBeginIdx;
        box->caretLineIdx = box->selectBeginLine;
        box->isSelecting  = FALSE;
        
        ls_utf32RmSubstr(&box->text, box->selectBeginIdx, box->selectEndIdx-1);
        box->currLineBeginIdx = setIndices(box->caretIndex);
    };
    
    if(ls_uiInFocus(c, box))
    {
        //NOTE: box->preInput
        if(box->callback1)
        { inputUse |= box->callback1(c, box->callback1Data); }
        
        //NOTE: Unset Focus on "Enter" press when textBox is single line.
        if(HasPrintableKey() && (GetPrintableKey() == (char32_t)'\n') &&
           ((box->isSingleLine == TRUE) || box->isReadonly == TRUE))
        { ls_uiFocusChange(c, 0); }
        
        //NOTE: Draw characters. (box->maxLen == 0 means there's no max len)
        else if(HasPrintableKey() && (box->text.len < box->maxLen || box->maxLen == 0) && (box->isReadonly == FALSE))
        {
            if(box->isSelecting) { removeSelection(); }
            
            if(box->caretIndex == box->text.len) { ls_utf32AppendChar(&box->text, GetPrintableKey()); }
            else { ls_utf32InsertChar(&box->text, GetPrintableKey(), box->caretIndex); }
            
            //NOTE We changed line, so we reset the view (Which is always relative caret curret line)
            if(GetPrintableKey() == (char32_t)'\n') {
                box->lineCount        += 1;
                box->caretLineIdx     += 1;
                box->currLineBeginIdx  = box->caretIndex+1;
            }
            
            box->caretIndex += 1;
            box->isCaretOn = TRUE; box->dtCaret = 0;
            
            setIndices(box->caretIndex-1);
            
            inputUse = TRUE;
        }
        
        else if(KeyPressOrRepeat(keyMap::Backspace) && box->text.len > 0 && box->caretIndex >= 0
                && (box->isReadonly == FALSE) ) 
        {
            if(box->caretIndex == 0 && !box->isSelecting) { goto goto_skip_to_post_input; }
            
            if(box->isSelecting) 
            { 
                removeSelection();
            }
            else
            {
                if(box->text.data[box->caretIndex-1] == (char32_t)'\n')
                { 
                    u32 beginOffset = setIndices(box->caretIndex-2);
                    
                    box->lineCount        -= 1;
                    box->caretLineIdx     -= 1;
                    box->currLineBeginIdx  = beginOffset;
                    
                }
                else { setIndices(box->caretIndex-1); }
                
                if(box->caretIndex == box->text.len) { ls_utf32TrimRight(&box->text, 1); }
                else { ls_utf32RmIdx(&box->text, box->caretIndex-1); }
                box->caretIndex -= 1;
            }
            
            box->isCaretOn = TRUE; box->dtCaret = 0;
            inputUse = TRUE;
        }
        
        else if(KeyPressOrRepeat(keyMap::Delete) && (box->text.len > 0) && (box->caretIndex <= box->text.len)
                && (box->isReadonly == FALSE) )
        {
            if(box->caretIndex == box->text.len && !box->isSelecting) { goto goto_skip_to_post_input; }
            
            if(box->isSelecting) 
            { 
                removeSelection();
            }
            else
            {
                b32 isCR = (box->text.data[box->caretIndex] == (char32_t)'\n');
                
                if(box->caretIndex == box->text.len-1) { ls_utf32TrimRight(&box->text, 1); }
                else { ls_utf32RmIdx(&box->text, box->caretIndex); }
                
                if(isCR) { box->lineCount -= 1; }
            }
            
            box->isCaretOn = TRUE; box->dtCaret = 0;
            inputUse = TRUE;
        }
        
        else if(KeyPressOrRepeat(keyMap::LArrow) && box->caretIndex > 0)
        {
            handleSelection(-1);
            
            box->isCaretOn      = TRUE;
            box->dtCaret        = 0;
            box->caretIndex    -= 1;
            
            if(box->text.data[box->caretIndex] == (char32_t)'\n')
            {
                if(box->caretIndex == 0)
                {
                    box->caretLineIdx     = 0;
                    box->currLineBeginIdx = 0;
                    box->viewBeginIdx     = 0;
                }
                else
                {
                    s32 newLineBeginIdx = setIndices(box->caretIndex-1);
                    if(newLineBeginIdx < box->currLineBeginIdx)
                    {
                        box->caretLineIdx    -= 1;
                        box->currLineBeginIdx = newLineBeginIdx;
                    }
                }
            }
            else
            { 
                s32 lineIdx = box->caretIndex - box->currLineBeginIdx;
                if(lineIdx < box->viewBeginIdx) { box->viewBeginIdx -= 1; }
            }
        }
        
        else if(KeyPressOrRepeat(keyMap::RArrow) && box->caretIndex < box->text.len)
        { 
            handleSelection(1);
            
            if(box->text.data[box->caretIndex] == (char32_t)'\n')
            { 
                box->caretLineIdx    += 1;
                box->currLineBeginIdx = box->caretIndex+1;
                box->viewBeginIdx     = 0;
            }
            else
            { 
                s32 lineIdx = box->caretIndex+1 - box->currLineBeginIdx;
                if(lineIdx - box->viewBeginIdx > maxIndexDiff) { box->viewBeginIdx += 1; }
            }
            
            box->isCaretOn      = TRUE;
            box->dtCaret        = 0;
            box->caretIndex    += 1;
        }
        
        else if(KeyPressOrRepeat(keyMap::UArrow) && box->caretLineIdx > 0)
        {
            box->isCaretOn = TRUE; box->dtCaret = 0;
            
            s32 oldCaretIndex = box->caretIndex;
            s32 lineRelativeCaretIndex = box->caretIndex - box->currLineBeginIdx;
            s32 oldLineBeginIdx = box->currLineBeginIdx;
            
            box->caretLineIdx    -= 1;
            box->currLineBeginIdx = lineBeginIdx(oldLineBeginIdx - 2);
            
            s32 newLineLen = oldLineBeginIdx-1 - box->currLineBeginIdx;
            
            if(lineRelativeCaretIndex > newLineLen)
            { box->caretIndex = newLineLen + box->currLineBeginIdx; }
            else
            { box->caretIndex = lineRelativeCaretIndex + box->currLineBeginIdx; }
            
            s32 lineIdx = box->caretIndex - box->currLineBeginIdx;
            s32 diff = lineIdx - box->viewBeginIdx;
            if(diff > maxIndexDiff) { box->viewBeginIdx = diff; }
            else                    { box->viewBeginIdx = 0; }
            
            //TODO: Handle Selection is a mess.
            if(KeyHeld(keyMap::Shift))
            {
                if(!box->isSelecting)
                {
                    box->isSelecting     = TRUE;
                    box->selectBeginLine = box->caretLineIdx;
                    box->selectEndLine   = box->caretLineIdx+1;
                    box->selectBeginIdx  = box->caretIndex;
                    box->selectEndIdx    = oldCaretIndex;
                }
                else
                {
                    if(oldCaretIndex == box->selectBeginIdx)
                    {
                        box->selectBeginLine -= 1;
                        box->selectBeginIdx   = box->caretIndex;
                    }
                    else if(oldCaretIndex == box->selectEndIdx)
                    {
                        if(box->selectEndLine > box->selectBeginLine) { box->selectEndLine   -= 1; }
                        else                                          { box->selectBeginLine -= 1; }
                        
                        if(box->caretIndex > box->selectBeginIdx)
                        { box->selectEndIdx = box->caretIndex; }
                        else
                        {
                            box->selectEndIdx   = box->selectBeginIdx;
                            box->selectBeginIdx = box->caretIndex;
                        }
                    }
                    else { AssertMsg(FALSE, "Arrow Up -> Caret is not aligned with select anymore\n"); }
                }
            }
            else
            {
                if(box->isSelecting)
                { 
                    box->isSelecting     = FALSE;
                    box->selectEndIdx    = 0; box->selectBeginIdx  = 0; 
                    box->selectBeginLine = 0; box->selectEndLine   = 0;
                }
            }
        }
        
        else if(KeyPressOrRepeat(keyMap::DArrow) && box->caretLineIdx < box->lineCount-1)
        {
            //TODO: handleSelection()
            
            box->isCaretOn = TRUE; box->dtCaret = 0;
            
            s32 oldCaretIndex = box->caretIndex;
            s32 lineRelativeCaretIndex = box->caretIndex - box->currLineBeginIdx;
            
            box->caretLineIdx    += 1;
            box->currLineBeginIdx = ls_utf32LeftFind(box->text, box->caretIndex, (char32_t)'\n') + 1;
            
            AssertMsg(box->currLineBeginIdx != -1, "No \\n Found, but there HAVE to be more lines ??");
            
            s32 nextLineIdx = ls_utf32LeftFind(box->text, box->currLineBeginIdx, (char32_t)'\n');
            s32 nextLineLen = nextLineIdx - box->currLineBeginIdx;
            
            if(nextLineIdx != -1)
            {
                if(lineRelativeCaretIndex > nextLineLen)
                { box->caretIndex = box->currLineBeginIdx + nextLineLen; }
                else
                { box->caretIndex = lineRelativeCaretIndex + box->currLineBeginIdx; }
            }
            else
            {
                if(box->currLineBeginIdx + lineRelativeCaretIndex > box->text.len)
                { box->caretIndex = box->text.len; }
                else
                { box->caretIndex = lineRelativeCaretIndex + box->currLineBeginIdx; }
            }
            
            s32 lineIdx = box->caretIndex - box->currLineBeginIdx;
            s32 diff = lineIdx - box->viewBeginIdx;
            if(diff > maxIndexDiff) { box->viewBeginIdx = diff; }
            else                    { box->viewBeginIdx = 0; }
            
            //TODO: Handle Selection is a mess.
            if(KeyHeld(keyMap::Shift))
            {
                if(!box->isSelecting)
                {
                    box->isSelecting     = TRUE;
                    box->selectBeginLine = box->caretLineIdx-1;
                    box->selectEndLine   = box->caretLineIdx;
                    box->selectBeginIdx  = oldCaretIndex;
                    box->selectEndIdx    = box->caretIndex;
                }
                else
                {
                    if(oldCaretIndex == box->selectBeginIdx)
                    {
                        if(box->selectBeginLine < box->selectEndLine) { box->selectBeginLine += 1; }
                        else                                          { box->selectEndLine   += 1; }
                        
                        if(box->caretIndex <= box->selectEndIdx)
                        { box->selectBeginIdx = box->caretIndex; }
                        else
                        { 
                            box->selectBeginIdx = box->selectEndIdx;
                            box->selectEndIdx   = box->caretIndex;
                        }
                    }
                    else if(oldCaretIndex == box->selectEndIdx)
                    {
                        box->selectEndLine += 1;
                        box->selectEndIdx   = box->caretIndex;
                    }
                    else { AssertMsg(FALSE, "Arrow Down -> Caret is not aligned with select anymore\n"); }
                }
            }
            else
            {
                if(box->isSelecting)
                { 
                    box->isSelecting     = FALSE;
                    box->selectEndIdx    = 0; box->selectBeginIdx  = 0; 
                    box->selectBeginLine = 0; box->selectEndLine   = 0;
                }
            }
        }
        
        else if(KeyPress(keyMap::Home))
        { 
            handleSelection(-2);
            
            box->isCaretOn = TRUE; box->dtCaret = 0;
            box->caretIndex       = 0;
            box->currLineBeginIdx = 0;
            box->caretLineIdx     = 0;
            
            setIndices(0);
        }
        
        else if(KeyPress(keyMap::End))
        {
            handleSelection(2);
            
            box->isCaretOn    = TRUE; box->dtCaret = 0; 
            box->caretIndex   = box->text.len;
            box->caretLineIdx = box->lineCount-1;
            
            box->currLineBeginIdx = setIndices(box->caretIndex-1);
        }
        
        else if(KeyHeld(keyMap::Control) && KeyPress(keyMap::A))
        {
            box->isSelecting     = TRUE;
            box->selectBeginIdx  = 0;
            box->selectEndIdx    = box->text.len;
            box->selectBeginLine = 0;
            box->selectEndLine   = box->lineCount;
        }
        
        else if(KeyHeld(keyMap::Control) && KeyPress(keyMap::C) && box->isSelecting)
        { 
            u32 *data = box->text.data + box->selectBeginIdx;;
            u32 selectionLen = box->selectEndIdx - box->selectBeginIdx;
            
            SetClipboard(data, selectionLen);
        }
        
        else if(KeyHeld(keyMap::Control) && KeyPress(keyMap::V) && (box->isReadonly == FALSE))
        {
            if(box->isSelecting) { removeSelection(); }
            
            u32 buff[4096] = {};
            u32 copiedLen = GetClipboard(buff, 4096);
            
            s32 realCopyLen = copiedLen;
            
            //NOTE: maxLen == 0 means there's no max len.
            if(box->maxLen != 0) 
            {
                if(box->text.len + copiedLen > box->maxLen) {
                    if(box->text.len < box->maxLen) { realCopyLen = box->maxLen - box->text.len; }
                    else { realCopyLen = 0; }
                }
            }
            
            u32 addedLines = ls_utf32CountOccurrences({buff, realCopyLen, realCopyLen}, (u32)'\n');
            
            //NOTE: Skip if box is single line and you're trying to paste a multiline text.
            if(addedLines > 0 && box->isSingleLine) { goto goto_skip_to_post_input; }
            
            if(box->caretIndex == box->text.len) { ls_utf32AppendBuffer(&box->text, buff, realCopyLen); }
            else { ls_utf32InsertBuffer(&box->text, buff, realCopyLen, box->caretIndex); }
            
            box->caretIndex      += realCopyLen;
            box->lineCount       += addedLines;
            box->caretLineIdx    += addedLines;
            box->currLineBeginIdx = setIndices(box->caretIndex-1);
            
            inputUse = TRUE;
        }
        
        //NOTE: GOTO label to skip here.
        goto_skip_to_post_input:
        
        box->dtCaret += c->dt;
        if(box->dtCaret >= 400) { box->dtCaret = 0; box->isCaretOn = !box->isCaretOn; }
        
        //NOTE: box->postInput
        if(box->callback2 && inputUse)
        { box->callback2(c, box->callback2Data); }
    }
    
    RenderCommand command = {UI_RC_TEXTBOX, xPos, yPos, w, h };
    command.textBox       = box;
    command.bkgColor      = c->widgetColor;
    command.textColor     = c->textColor;
    ls_uiPushRenderCommand(c, command, zLayer);
    
    ls_arenaUse(prev);
    return inputUse;
}

void ls_uiDrawArrow(UIContext *c, s32 x, s32 yPos, s32 w, s32 h,
                    UIRect threadRect, UIRect scissor, Color bkgColor, UIArrowSide s)
{
#ifdef LS_UI_OPENGL_BACKEND
    
    s32 xPos = x-1;
    ls_uiBorderedRect(c, xPos, yPos, w, h, threadRect, scissor, bkgColor);
    
    //TODO: Customize color?
    Color col = c->borderColor;
    
    switch(s)
    {
        case UIA_DOWN:
        {
            s32 arrowWidth  = 0.50f*w;
            s32 arrowHeight = 0.40f*h;
            
            s32 startX = x + (w - arrowWidth)/2 - 1;
            s32 startY = (yPos + (h-arrowHeight)/2) - 1;
            s32 midX = (startX + arrowWidth/2);
            
            UIRect norm = ls_uiScreenCoordsToUnitSquare(c, startX, startY, arrowWidth, arrowHeight);
            f32 botX = (2.0f*(f32)midX / (f32)c->width)-1.0f;
            
            glColor4ub(col.r, col.g, col.b, col.a);
            glBegin(GL_TRIANGLES);
            glVertex2f(norm.leftX, norm.topY);
            glVertex2f(norm.rightX, norm.topY);
            glVertex2f(botX, norm.botY);
            glEnd();
            
        } break;
        
        case UIA_RIGHT:
        {
            s32 arrowWidth  = 0.40f*w;
            s32 arrowHeight = 0.50f*h;
            
            s32 startX = x + (w - arrowWidth)/2 + 1;
            s32 startY = (yPos + (h-arrowHeight)/2);
            s32 midY = (startY + arrowHeight/2);
            
            UIRect norm = ls_uiScreenCoordsToUnitSquare(c, startX, startY, arrowWidth, arrowHeight);
            f32 rightY = (2.0f*(f32)midY / (f32)c->height)-1.0f;
            
            glColor4ub(col.r, col.g, col.b, col.a);
            glBegin(GL_TRIANGLES);
            glVertex2f(norm.leftX, norm.botY);
            glVertex2f(norm.leftX, norm.topY);
            glVertex2f(norm.rightX, rightY);
            glEnd();
            
        } break;
        
        case UIA_LEFT:
        {
            s32 arrowWidth  = 0.40f*w;
            s32 arrowHeight = 0.50f*h;
            
            s32 startX = x + (w - arrowWidth)/2 - 1;
            s32 startY = (yPos + (h-arrowHeight)/2);
            s32 midY = (startY + arrowHeight/2);
            
            UIRect norm = ls_uiScreenCoordsToUnitSquare(c, startX, startY, arrowWidth, arrowHeight);
            f32 leftY = (2.0f*(f32)midY / (f32)c->height)-1.0f;
            
            glColor4ub(col.r, col.g, col.b, col.a);
            glBegin(GL_TRIANGLES);
            glVertex2f(norm.rightX, norm.botY);
            glVertex2f(norm.rightX, norm.topY);
            glVertex2f(norm.leftX, leftY);
            glEnd();
            
        } break;
    }
#else
    
    //TODO: Scissor???
    s32 minX = threadRect.minX;
    s32 minY = threadRect.minY;
    s32 maxX = threadRect.maxX;
    s32 maxY = threadRect.maxY;
    
    u32 *At = (u32 *)c->drawBuffer;
    
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
                AssertMsg(x >= 0 && x < c->width,  "X out of range. Should have been guarded by thread UI Rects?\n");
                AssertMsg(y >= 0 && y < c->height, "Y out of range. Should have been guarded by thread UI Rects?\n");
                
                //TODO: Setting fractional alpha on the rows where progressiveX advances a fractional amount
                //      would allow better `sub-pixel like` blending. Just a tiny thing to make it look better
                //      at small resolutions.
                At[y*c->width + x] = c->borderColor.value;
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
                
                if(x < 0 || x >= c->width)  continue;
                if(y < 0 || y >= c->height) continue;
                
                At[y*c->width + x] = RGBg(0x00).value;
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
                
                if(x < 0 || x >= c->width)  continue;
                if(y < 0 || y >= c->height) continue;
                
                At[y*c->width + x] = RGBg(0x00).value;
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
                
                if(x < 0 || x >= c->width)  continue;
                if(y < 0 || y >= c->height) continue;
                
                At[y*c->width + x] = RGBg(0x00).value;
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
                
                if(x < 0 || x >= c->width)  continue;
                if(y < 0 || y >= c->height) continue;
                
                At[y*c->width + x] = RGBg(0x00).value;
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

UIListBox ls_uiListBoxInit(UIContext *c, FixedArray<UIListBoxItem> container)
{
    UIListBox lb = {};
    lb.list = container;
    return lb;
}

inline u32 ls_uiListBoxAddEntry(UIContext *c, UIListBox *lb, utf32 s)
{
    AssertNonNull(c);
    AssertNonNull(lb);
    AssertNonNull(lb->list.data);
    
    UIListBoxItem item = { s, c->widgetColor, c->textColor };
    return ls_fixedArrayAppendIndex(&lb->list, item);
}

//NOTE: This does NOT free the memory of the string
inline void ls_uiListBoxRemoveEntry(UIContext *c, UIListBox *lb, u32 index)
{ 
    AssertNonNull(c);
    AssertNonNull(lb);
    AssertNonNull(lb->list.data);
    
    //NOTETODO: Is this good????
    if(lb->selectedIndex == index) { lb->selectedIndex = 0; }
    
    UIListBoxItem val = lb->list[index];
    ls_fixedArrayRemove(&lb->list, index);
}

//TODO: Currently the renderer doesn't care if the item's name is too long, and just renders it in full
b32 ls_uiListBox(UIContext *c, UIListBox *lb, s32 xPos, s32 yPos, s32 w, s32 h, u32 zLayer = 0)
{
    Input *UserInput = &c->UserInput;
    b32 inputUse = FALSE;
    
    //TODO: Why is this constant?
    const s32 arrowBoxWidth = 24;
    if(LeftClickIn(xPos+w, yPos, arrowBoxWidth, h) && ls_uiHasCapture(c, 0))
    {
        ls_uiFocusChangeSameFrame(c, (u64 *)lb);
        
        if(lb->isOpen) { lb->isOpen = FALSE; }
        //else { lb->isOpening = TRUE; } //NOTE:TODO: This is because Claudio wanted instant list open. 
        else { lb->isOpen = TRUE; }
    }
    
    Color bkgColor = c->widgetColor;
    s32 arrowX = xPos + w - 1;
    if(MouseInRect(arrowX, yPos, arrowBoxWidth, h)) { bkgColor = c->highliteColor; }
    lb->arrowBkg = bkgColor;
    
    if(lb->isOpening)
    {
        lb->dtOpen += c->dt;
        if(lb->dtOpen > 70) { lb->isOpen = TRUE; lb->isOpening = FALSE; lb->dtOpen = 0; }
    }
    
    if(ls_uiInFocus(c, lb))
    {
        if(lb->isOpen)
        {
            for(u32 i = 0; i < lb->list.count; i++)
            {
                s32 currY = yPos - (h*(i+1));
                UIListBoxItem *currItem = lb->list + i;
                
                //TODO: The constant resetting is kinda stupid. Makes me think I should just not
                //      have listbox items with their own colors. Never even used that feature.
                currItem->bkgColor  = c->widgetColor;
                currItem->textColor = c->textColor;
                if(MouseInRect(xPos+1, currY+1, w-2, h-1)) 
                { 
                    currItem->bkgColor = c->highliteColor;
                    if(LeftClick) { 
                        c->mouseCapture = (u64 *)lb;
                        
                        lb->selectedIndex = i; lb->isOpen = FALSE;
                        inputUse = TRUE;
                        
                        //NOTE: lb->onSelect
                        if(lb->callback1) { lb->callback1(c, lb->callback1Data); }
                    }
                    
                    //TODO: Lost the ability to hold because of mouse capture.
                    //      Should be able to regain it if capture is handled deferred?
                    //if(LeftHold) { currItem->bkgColor = cxt->pressedColor; }
                    //if(LeftUp) { ls_printf("here\n");  }
                }
            }
        }
    }
    else
    { lb->isOpen = FALSE; }
    
    //TODO: I think it *should* be fine if the count is 0, since the height of the box is set to maxHeight+h
    //      But i need to test it!
    s32 maxHeight = (lb->list.count)*(h);
    //NOTE: Here the maxHeight in the command rect is used to determine the maximum height when expanded
    //      the height passed in the layout rect in minY determines the minimum height when contracted.
    //      This also means that yPos is shifted by maxHeight
    RenderCommand list_command = { UI_RC_LISTBOX, xPos, yPos-maxHeight, w, maxHeight+h };
    list_command.layout.minY = h;
    list_command.listBox = lb;
    ls_uiPushRenderCommand(c, list_command, zLayer);
    
    RenderCommand arr_command = { UI_RC_LISTBOX_ARR, xPos+w, yPos, arrowBoxWidth, h };
    arr_command.listBox = lb;
    ls_uiPushRenderCommand(c, arr_command, zLayer);
    
    return inputUse;
}

UISlider ls_uiSliderInit(UIContext *c, char32_t *name, s32 maxVal, s32 minVal, f64 currPos, 
                         SliderStyle s, Color l, Color r)
{
    Arena prev = ls_arenaUse(c->widgetArena);
    
    UISlider Result = {};
    
    if(name) { Result.text = ls_utf32FromUTF32((const char32_t *)name); }
    else     { Result.text = ls_utf32Alloc(16); }
    
    Result.maxValue = maxVal;
    Result.minValue = minVal;
    Result.currPos  = currPos;
    Result.style    = s;
    Result.lColor   = l;
    Result.rColor   = r;
    
    ls_arenaUse(prev);
    return Result;
}

void ls_uiSliderChangeValueBy(UIContext *c, UISlider *f, s32 valueDiff)
{
    s32 newValue = f->currValue + valueDiff;
    
    if(newValue <= f->minValue) { newValue = f->minValue; }
    if(newValue >= f->maxValue) { newValue = f->maxValue; }
    
    s32 range = (f->maxValue - f->minValue);
    f->currValue = newValue;
    f->currPos = (f64)(newValue - f->minValue) / (f64)range;
    
    return;
}

s32 ls_uiSliderCalculateValueFromPosition(UIContext *c, UISlider *f)
{
    return ((f->maxValue - f->minValue) * f->currPos) + f->minValue;
}

//TODO: The things are rendered in a logical order, but that makes the function's flow very annoying
//      going in and out of if blocks to check hot/held and style.
b32 ls_uiSlider(UIContext *c, UISlider *slider, s32 xPos, s32 yPos, s32 w, s32 h)
{
    Input *UserInput = &c->UserInput;
    
    if(LeftUp) { slider->isHeld = FALSE; }
    
    if(slider->style == SL_BOX)
    {
        //NOTE: hotness needs to be logically re-checked every frame, else it always stays on.
        slider->isHot = FALSE;
        s32 slidePos = w*slider->currPos;
        
        if(MouseInRect(xPos + slidePos-5, yPos, 10, h) && !(c->mouseCapture != 0 && c->mouseCapture != (u64 *)slider))
        {
            slider->isHot = TRUE;
            if(LeftHold) { slider->isHeld = TRUE; c->mouseCapture = (u64 *)slider; }
        }
    }
    else if(slider->style == SL_LINE)
    { AssertMsg(FALSE, "Slider style line is not implemented\n"); }
    
    b32 hasAnsweredToInput = FALSE;
    
    if(slider->isHeld) { 
        s32 deltaX = (c->UserInput.Mouse.prevPosX - c->UserInput.Mouse.currPosX);//*c->dt;
        
        f64 fractionMove = (f64)deltaX / (f64)w;
        
        if(fractionMove != 0.0)
        {
            slider->currPos  -= fractionMove;
            slider->currPos   = ls_clamp(slider->currPos, 1.0, 0.0);
            slider->currValue = ((slider->maxValue - slider->minValue) * slider->currPos) + slider->minValue;
        }
        
        hasAnsweredToInput = TRUE;
    }
    
    RenderCommand command = { UI_RC_SLIDER, xPos, yPos, w, h };
    command.slider = slider;
    command.borderColor = c->borderColor;
    
    ls_uiPushRenderCommand(c, command, 0);
    
    return hasAnsweredToInput;
}

UIButton ls_uiMenuButton(UICallback onClick, u8 *bitmapData, s32 width, s32 height)
{
    UIButton result  = {};
    result.style     = UIBUTTON_BMP;
    result.bmpData   = bitmapData;
    result.w         = width;
    result.h         = height;
    result.callback1 = onClick;
    return result;
}

inline UISubMenu *ls_uiMenuAddSub(UIContext *c, UIMenu *menu, UISubMenu sub)
{
    Arena prev = ls_arenaUse(c->widgetArena);
    UISubMenu *result = ls_arrayAppend(&menu->subMenus, sub);
    ls_arenaUse(prev);
    return result;
}

UISubMenu *ls_uiMenuAddSub(UIContext *c, UIMenu *menu, const char32_t *name)
{ 
    Arena prev = ls_arenaUse(c->widgetArena);
    UISubMenu newSub = {};
    newSub.name = ls_utf32FromUTF32(name);
    UISubMenu *result = ls_arrayAppend(&menu->subMenus, newSub);
    ls_arenaUse(prev);
    return result;
}

UIMenuItem *ls_uiMenuAddItem(UIContext *c, UIMenu *menu, const char32_t *name, UICallback onClick, void *userData)
{
    Arena prev = ls_arenaUse(c->widgetArena);
    
    UIMenuItem newItem    = {};
    newItem.name          = ls_utf32FromUTF32(name);
    newItem.isVisible     = TRUE;
    newItem.callback1     = onClick;
    newItem.callback1Data = userData;
    UIMenuItem *result = ls_arrayAppend(&menu->items, newItem);
    
    ls_arenaUse(prev);
    return result;
}

UIMenuItem *ls_uiSubMenuAddItem(UIContext *c, UISubMenu *sub, const char32_t *name, 
                                UICallback onClick, void *userData)
{
    Arena prev = ls_arenaUse(c->widgetArena);
    
    UIMenuItem newItem    = {};
    newItem.name          = ls_utf32FromUTF32(name);
    newItem.isVisible     = TRUE;
    newItem.callback1     = onClick;
    newItem.callback1Data = userData;
    UIMenuItem *result = ls_arrayAppend(&sub->items, newItem);
    
    ls_arenaUse(prev);
    return result;
}

UIMenuItem *ls_uiSubMenuAddItem(UIContext *c, UIMenu *menu, u32 subIdx, 
                                const char32_t *name, UICallback onClick, void *userData)
{
    Arena prev = ls_arenaUse(c->widgetArena);
    
    UIMenuItem newItem    = {};
    newItem.name          = ls_utf32FromUTF32(name);
    newItem.isVisible     = TRUE;
    newItem.callback1     = onClick;
    newItem.callback1Data = userData;
    UIMenuItem *result = ls_arrayAppend(&menu->subMenus[subIdx].items, newItem);
    
    ls_arenaUse(prev);
    return result;
}

b32 ls_uiMenu(UIContext *c, UIMenu *menu, s32 x, s32 y, s32 w, s32 h, s32 zLayer = 2)
{
    Input *UserInput = &c->UserInput;
    b32 inputUse = FALSE;
    
    if(c->currentFocus != (u64 *)menu) { menu->isOpen = FALSE; }
    
    s32 subY = y;
    s32 subW = menu->itemWidth;
    s32 subH = h;
    
    s32 subCount  = menu->subMenus.count;
    s32 itemCount = menu->items.count;
    
    s32 closeX    = x + w - menu->closeWindow.w - 6;
    s32 minimizeX = closeX - menu->closeWindow.w - 6;
    
    s32 dragX = x + ((subCount+itemCount)*subW);
    
    if(LeftClickIn(dragX, y, minimizeX-dragX, h))
    {
        c->isDragging = TRUE;
        ls_uiFocusChange(c, 0);
        
        //NOTETODO: Maybe find a way to move platform specific code away?
        POINT currMouse = {};
        GetCursorPos(&currMouse);
        c->prevMousePosX = currMouse.x;
        c->prevMousePosY = currMouse.y;
        
        goto uiMenuRenderLabel;
    }
    
    for(u32 i = 0; i < subCount; i++)
    {
        UISubMenu *sub = menu->subMenus + i;
        sub->isHot = FALSE;
        
        s32 subX = x + (i*menu->itemWidth);
        
        if(menu->isOpen && menu->openIdx == i)
        {
            for(u32 j = 0; j < sub->items.count; j++)
            {
                UIMenuItem *currItem = sub->items + j;
                if(!currItem->isVisible) continue; 
                
                currItem->isHot = FALSE;
                
                s32 itemX = subX;
                s32 itemY = subY - (subH*(j+1));
                
                if(MouseInRect(itemX, itemY, menu->itemWidth, subH-1)) 
                { 
                    currItem->isHot = TRUE;
                    
                    if(LeftClick) {
                        //NOTETODO: mouseCapture vs focus????
                        c->mouseCapture = (u64 *)menu;
                        
                        //NOTE: currItem->onClick
                        if(currItem->callback1) { currItem->callback1(c, currItem->callback1Data); }
                        inputUse = TRUE;
                        
                        ls_uiFocusChange(c, 0);
                        menu->isOpen = FALSE;
                        
                    }
                }
            }
        }
        
        if(MouseInRect(subX, subY, subW, subH))
        {
            sub->isHot = TRUE;
            if(LeftClick) {
                ls_uiFocusChangeSameFrame(c, (u64 *)menu);
                
                menu->isOpen  = TRUE;
                menu->openIdx = i;
                break;
            }
        }
    }
    
    //NOTE: Items HAVE to come after submenus
    for(u32 i = 0; i < itemCount; i++)
    {
        UIMenuItem *item = menu->items + i;
        if(!item->isVisible) continue;
        
        item->isHot   = FALSE;
        s32 realIndex = i + subCount;
        s32 subX      = x + (realIndex*menu->itemWidth);
        
        if(MouseInRect(subX, subY, subW, subH)) {
            item->isHot = TRUE;
            
            if(LeftClick)
            {
                ls_uiFocusChange(c, 0);
                menu->isOpen = FALSE;
                
                //NOTE: item->onClick
                if(item->callback1) { inputUse |= item->callback1(c, item->callback1Data); }
            }
        }
    }
    
    //NOTE: goto label jump to avoid annoying mega-nesting ifs.
    uiMenuRenderLabel:
    
    
    //NOTE: Only render when the bitmap is set!
    if(menu->closeWindow.bmpData)
        inputUse |= ls_uiButton(c, &menu->closeWindow, closeX, y + 2, 2);
    
    if(menu->minimize.bmpData)
        inputUse |= ls_uiButton(c, &menu->minimize, minimizeX, y + 2, 2);
    
    
    RenderCommand command = { UI_RC_MENU, x, y, w, h };
    command.menu          = menu;
    command.bkgColor      = c->menuBarColor;
    command.textColor     = c->textColor;
    ls_uiPushRenderCommand(c, command, zLayer);
    
    return inputUse;
}

void ls_uiTexturedRect(UIContext *c, s32 x, s32 y, s32 w, s32 h, void *data, s32 dataW, s32 dataH, s32 zLayer = 0)
{
    RenderCommand command = { UI_RC_TEXTURED_RECT, x, y, w, h };
    command.bitmap = { data, dataW, dataH };
    ls_uiPushRenderCommand(c, command, zLayer);
}

UIColorPicker ls_uiColorPickerInit(UIContext *c, void *userData)
{
    UIColorPicker result = {};
    result.value = 1.0f;
    result.apply = ls_uiButtonInit(c, UIBUTTON_CLASSIC, U"Apply", NULL, NULL, userData);
    
    return result;
}

void ls_uiColorValueRect(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h, UIRect threadRect, UIRect scissor)
{
#ifdef LS_UI_OPENGL_BACKEND
    
    UIRect normRect = ls_uiScreenCoordsToUnitSquare(c, xPos, yPos, w, h);
    
    glBegin(GL_TRIANGLES);
    glColor4ub(0, 0, 0, 0xFF);
    glVertex2f(normRect.leftX,  normRect.botY);
    glVertex2f(normRect.rightX, normRect.botY);
    
    glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);
    glVertex2f(normRect.leftX,  normRect.topY);
    glVertex2f(normRect.leftX,  normRect.topY);
    glVertex2f(normRect.rightX, normRect.topY);
    
    glColor4ub(0, 0, 0, 0xFF);
    glVertex2f(normRect.rightX, normRect.botY);
    glEnd();
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
            
            if(x < 0 || x >= c->width)  continue;
            if(y < 0 || y >= c->height) continue;
            
            u32 idx = ((y*c->width) + x)*sizeof(s32);
            __m128i *At = (__m128i *)(c->drawBuffer + idx);
            
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
    u32 *At = (u32 *)c->drawBuffer;
    
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
                
                if(x < 0 || x >= c->width)  continue;
                if(y < 0 || y >= c->height) continue;
                
                Color base = {.value = At[y*c->width + x] };
                Color blendedColor = ls_uiAlphaBlend(col, base);
                At[y*c->width + x] = blendedColor.value;
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
                
                if(x < 0 || x >= c->width)  continue;
                if(y < 0 || y >= c->height) continue;
                
                Color base = { .value = At[y*c->width + x] };
                Color blendedColor = ls_uiAlphaBlend(col, base);
                At[y*c->width + x] = blendedColor.value;
            }
            
            currGray += step;
        }
    }
    
#endif
}

f32 ls_uiLerp(f32 base, f32 towards, f32 step)
{
    return base + step * (towards - base);
    //return (1.0f - step) * base + step * towards;
}

//TODO: On my laptop the color wheel appears with a fucked up single tone color. Why?
void ls_uiFillColorWheel(UIContext *c, s32 centerX, s32 centerY, s32 radius, f32 value,
                         UIRect threadRect, UIRect scissor)
{
#ifdef LS_UI_OPENGL_BACKEND
    //TODO: This is not actually equivalent to the software renderer version.
    //      It's kinda annoying to do in immediate mode.
    const s32 triangleCount = 100;
    
    f32 normCx   = (2.0f*(f32)centerX / (f32)c->width)-1.0f;
    f32 normCy   = (2.0f*(f32)centerY / (f32)c->height)-1.0f;
    f32 normRadX = ((f32)radius / (f32)c->width);
    f32 normRadY = ((f32)radius / (f32)c->height);
    
    //NOTE: We start at angle 0, and create triangles by moving one angle step at a time
    f32 angleStep = TAU / triangleCount;
    f32 p1X = normCx+normRadX;
    f32 p1Y = normCy;
    f32 p2X = normCx+normRadX * cos(angleStep);
    f32 p2Y = normCy+normRadY * sin(angleStep);
    
    f32 baseR = 1.0f;
    f32 baseG = 0.0f;
    f32 baseB = 0.0f;
    f32 step  = 1.0f / ((f32)(triangleCount+1) / 3.0f);
    
    glBegin(GL_TRIANGLE_FAN);
    
    glColor4ub(0xFF*value, 0xFF*value, 0xFF*value, 0xFF);
    glVertex2f(normCx, normCy);
    for(s32 i = 0; i < triangleCount+1; i++)
    {
        glColor4ub(baseR*0xFF, baseG*0xFF, baseB*0xFF, 0xFF);
        glVertex2f(p1X, p1Y);
        p1X = normCx+normRadX * cos(i*angleStep);
        p1Y = normCy+normRadY * sin(i*angleStep);
        
        if (i < (triangleCount+1)/3) {
            baseR -= step; if(baseR < 0.0005f) { baseR = 0.0f; }
            baseG += step; if(baseG > 1.0f)    { baseG = 1.0f; }
        }
        else if (i < 2*(triangleCount+1)/3) {
            baseG -= step; if(baseG < 0.0005f) { baseG = 0.0f; }
            baseB += step; if(baseB > 1.0f)    { baseB = 1.0f; }
        }
        else {
            baseR += step; if(baseR > 1.0f)    { baseR = 1.0f; }
            baseB -= step; if(baseB < 0.0005f) { baseB = 0.0f; }
        }
    }
    glVertex2f(normCx+normRadX, normCy);
    glEnd();
    
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
    
    static u32 stupidIdx = 0;
    
    u32 *At = (u32 *)c->drawBuffer;
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
                
                Color base         = { .value = At[y*c->width + x] };
                Color blendedColor = ls_uiAlphaBlend(converted, base);
                At[y*c->width + x] = blendedColor.value;
            }
        }
    }
    
#endif
}

b32 ls_uiColorPicker(UIContext *c, UIColorPicker *picker, s32 x, s32 y, s32 w, s32 h, s32 zLayer = 0)
{
    Input *UserInput = &c->UserInput;
    
    if(LeftClickIn(x, y, w, h) && ls_uiHasCapture(c, 0)) {
        ls_uiFocusChangeSameFrame(c, (u64 *)picker);
        c->mouseCapture = (u64 *)picker;
    }
    
    s32 xMargin = w*0.1f;
    s32 yMargin = h*0.1f;
    
    s32 valueRectX = x + xMargin;
    s32 valueRectY = y + yMargin;
    s32 valueRectW = w*0.1f;
    s32 valueRectH = h*0.8f;
    
    s32 buttonH = picker->apply.h;
    
    s32 radius  = w*0.30f;
    s32 centerX = x + 2*xMargin + valueRectW + radius;
    s32 centerY = y + 3*yMargin + buttonH + radius;
    
    s32 buttonX = centerX - picker->apply.w/2;
    s32 buttonY = y + yMargin;
    
    if(ls_uiHasCapture(c, picker) && LeftClickIn(centerX - radius, centerY - radius, radius*2, radius*2))
    {
        s32 cX         = UserInput->Mouse.currPosX - centerX;
        s32 cY         = UserInput->Mouse.currPosY - centerY;
        s32 pickRadius = radius + 0.05f*radius;
        b32 cond = (cY*cY + cX*cX) <= (pickRadius*pickRadius);
        
        if(cond)
        {
            picker->pickedX   = UserInput->Mouse.currPosX;
            picker->pickedY   = UserInput->Mouse.currPosY;
            picker->hasPicked = TRUE;
        }
    }
    
    picker->centerX = centerX;
    picker->centerY = centerY;
    picker->radius  = radius;
    
    picker->valueRectX = valueRectX;
    picker->valueRectY = valueRectY;
    picker->valueRectW = valueRectW;
    picker->valueRectH = valueRectH;
    
    if(ls_uiHasCapture(c, picker) &&
       LeftClickIn(picker->valueRectX, picker->valueRectY, picker->valueRectW, picker->valueRectH))
    {
        s32 clickedY  = UserInput->Mouse.currPosY;
        f32 value     = (f32)(clickedY - picker->valueRectY) / (f32)picker->valueRectH;
        picker->value = value;
    }
    
    b32 usedInput  = ls_uiButton(c, &picker->apply, buttonX, buttonY, picker->pickedColor, zLayer);
    
    RenderCommand command = { UI_RC_COLOR_PICKER, x, y, w, h };
    command.colorPicker   = picker;
    command.textColor     = c->textColor;
    ls_uiPushRenderCommand(c, command, zLayer);
    
    return usedInput;
}


#ifndef LS_UI_OPENGL_BACKEND

#if _DEBUG
static b32 __ui_shouldTag = FALSE;
#endif

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
    switch(THREAD_COUNT)
    {
        case 0:
        case 1:
        {
            command.threadRect = c->renderUIRects[0];
            
            stack *renderStack = &c->renderGroups[0].RenderCommands[zLayer];
            AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 0\n");
            
            ls_stackPush(renderStack, (void *)&command);
            return;
        } break;
        
        case 2:
        case 4:
        case 8:
        {
            for(s32 i = 0; i < THREAD_COUNT; i++)
            {
                if(ls_uiRectIntersects(commandRect, c->renderUIRects[i]))
                {
                    command.threadRect = c->renderUIRects[i];
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
//NOTE: With the OpenGL backend there's no point in deferring the command execution
void ls_uiPushRenderCommand(UIContext *c, RenderCommand command, s32 zLayer)
{
    AssertMsg(command.type != UI_RC_INVALID,  "Uninitialized Render Command?\n");
    
    s32 xPos                = command.rect.x;
    s32 yPos                = command.rect.y;
    s32 w                   = command.rect.w;
    s32 h                   = command.rect.h;
    
    //UIRect threadRect       = command.threadRect;
    //UIRect scissor          = command.scissor;
    Color bkgColor          = command.bkgColor;
    Color borderColor       = command.borderColor;
    Color textColor         = command.textColor;
    
    UIFont *font            = c->currFont;
    s32 pixelHeight         = c->currPixelHeight;
    
    switch(command.type)
    {
        case UI_RC_RECT:
        {
            ls_uiBorderedRect(c, xPos, yPos, w, h, {}, {}, bkgColor, borderColor);
        } break;
        
        case UI_RC_LABEL32:
        {
            s32 yBaseOff = h - pixelHeight;
            ls_uiGlyphString(c, font, pixelHeight, xPos, yPos + yBaseOff, 
                             {}, {}, command.label32, textColor);
        } break;
        
        case UI_RC_LABEL8:
        {
            s32 yBaseOff = h - pixelHeight;
            ls_uiGlyphString(c, font, pixelHeight, xPos, yPos + yBaseOff, 
                             {}, {}, command.label8, textColor);
        } break;
        
        case UI_RC_SEPARATOR:
        {
            ls_uiFillRect(c, xPos, yPos, w, h, {}, {}, borderColor);
        } break;
        
        case UI_RC_BUTTON:
        {
            UIButton *button = command.button;
            
            if(button->style == UIBUTTON_CLASSIC)
            {
                ls_uiBorderedRect(c, xPos, yPos, w, h, {}, {}, bkgColor, borderColor);
                
                if(button->name.data)
                {
                    s32 strHeight = pixelHeight;
                    s32 strWidth  = ls_uiGlyphStringRect(c, font, button->name, pixelHeight).w;
                    s32 xOff      = (w - strWidth) / 2; //TODO: What happens when the string is too long?
                    s32 yOff      = strHeight*0.25; //TODO: @FontDescent
                    
                    ls_uiGlyphString(c, font, pixelHeight, xPos+xOff, yPos+yOff, {}, {}, 
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
                    
                    ls_uiGlyphString(c, font, pixelHeight, xPos+xOff, yPos+yOff, {}, {},
                                     button->name, textColor);
                }
            }
            else if(button->style == UIBUTTON_TEXT_NOBORDER)
            {
                ls_uiRect(c, xPos, yPos, w, h, {}, {}, bkgColor);
                
                if(button->name.data)
                {
                    s32 strHeight = pixelHeight;
                    s32 strWidth  = ls_uiGlyphStringRect(c, font, button->name, pixelHeight).w;
                    s32 xOff      = (w - strWidth) / 2; //TODO: What happens when the string is too long?
                    s32 yOff      = strHeight*0.25; //TODO: @FontDescent
                    
                    ls_uiGlyphString(c, font, pixelHeight, xPos+xOff, yPos+yOff, {}, {}, 
                                     button->name, textColor);
                }
            }
            else if(button->style == UIBUTTON_NO_TEXT)
            {
                ls_uiRect(c, xPos, yPos, w, h, {}, {}, bkgColor);
            }
            else if(button->style == UIBUTTON_BMP)
            {
                UIBitmap bmp = { button->bmpData, button->w, button->h };
                ls_uiBitmap(c, bmp, xPos, yPos, {});
            }
            else { AssertMsg(FALSE, "Unhandled button style\n"); }
            
        } break;
        
        case UI_RC_LISTBOX:
        {
            UIListBox *lb = command.listBox;
            
            s32 h = command.layout.minY;
            s32 maxHeight = command.rect.h;
            s32 origY     = yPos+maxHeight-h;
            
            s32 strHeight = pixelHeight; 
            s32 vertOff = ((h - strHeight) / 2) + 4; //TODO: @FontDescent
            
            ls_uiBorderedRect(c, xPos, origY, w, h, {}, {});
            
            if(lb->list.count)
            {
                utf32 selected = lb->list[lb->selectedIndex].name;
                ls_uiGlyphString(c, font, pixelHeight, xPos+10, origY + vertOff, {}, {}, selected, c->textColor);
            }
            
            if(lb->isOpening)
            {
                s32 height = 0;
                if(lb->dtOpen > 17)  { height = maxHeight*0.10f; }
                if(lb->dtOpen > 34)  { height = maxHeight*0.35f; }
                if(lb->dtOpen > 52)  { height = maxHeight*0.70f; }
                
                if(!lb->isOpen)
                { ls_uiFillRect(c, xPos+1, origY - height, w-2, height, {}, {}, c->widgetColor); }
            }
            
            if(lb->isOpen)
            {
                for(u32 i = 0; i < lb->list.count; i++)
                {
                    s32 currY = origY - (h*(i+1));
                    UIListBoxItem *currItem = lb->list + i;
                    
                    ls_uiRect(c, xPos+1, currY, w-2, h, {}, {}, currItem->bkgColor);
                    ls_uiGlyphString(c, font, pixelHeight, xPos+10, origY + vertOff - (h*(i+1)),
                                     {}, {}, currItem->name, currItem->textColor);
                    
                }
                
                ls_uiBorder(c, xPos, yPos, w, maxHeight+1, {}, {});
            }
            
        } break;
        
        //TODO: Why is this a separate command?
        case UI_RC_LISTBOX_ARR:
        {
            ls_uiDrawArrow(c, xPos, yPos, w, h, {}, {}, command.listBox->arrowBkg, UIA_DOWN);
        } break;
        
        case UI_RC_TEXTBOX:
        {
            UITextBox *box = command.textBox;
            
            Color caretColor = textColor;
            const s32 horzOff = 4;
            
            ls_uiBorderedRect(c, xPos, yPos, w, h, {}, {}, bkgColor);
            
            s32 strX = xPos + horzOff;
            s32 strY = yPos + h - pixelHeight;
            
            if(box->align == UI_TB_ALIGN_RIGHT || box->align == UI_TB_ALIGN_CENTER)
            {
                ls_uiRenderAlignedStringOnRect(c, font, box, strX, strY, w, h, {}, {}, textColor, c->invTextColor);
            }
            else
            {
                //NOTETODO: For now we double draw for selected strings. We can improve with 3-segment drawing.
                ls_uiRenderStringOnRect(c, box, strX, strY, w, h, {}, {}, textColor, c->invTextColor);
            }
            
        } break;
        
        
        default: 
        { 
            AssertMsgF(FALSE, "Render Command Type %cs not implemented yet", 
                       RenderCommandTypeAsString[command.type]);
        } break;
    }
    
    return;
}
#endif

void ls_uiRender(UIContext *c)
{
#ifndef LS_UI_OPENGL_BACKEND
    AssertMsg(c->drawBuffer != NULL, "Trying to Call ls_uiRender on a Fake UIContext "
              "which doesn't have a draw buffer allocated!\n");
    if(THREAD_COUNT == 0)
    {
        ls_uiRender__(c, 0);
        c->renderFunc(c);
        return;
    }
    
    WakeAllConditionVariable(&c->startRender);
    
    volatile b32 areAllDone = FALSE;
    while(areAllDone == FALSE)
    {
        volatile b32 allDone = TRUE;
        for(u32 i = 0; i < THREAD_COUNT; i++)
        {
            allDone = allDone && c->renderGroups[i].isDone;
        }
        
        areAllDone = allDone;
    }
    
    for(u32 i = 0; i < THREAD_COUNT; i++)
    {
        c->renderGroups[i].isDone = FALSE;
    }
#endif
    
    c->renderFunc(c);
}

//TODO: Put the single command handling in a separate function, something like:
//      ls_uiRenderSingleCommand().
//      This would allow us to avoid repeating most of the code below in PushRenderCommand in other backends.
#ifndef LS_UI_OPENGL_BACKEND
void ls_uiRender__(UIContext *c, u32 threadID)
{
    //NOTE: First clear the background
    switch(THREAD_COUNT)
    {
        case 0:
        case 1:
        { ls_uiClearRect(c, 0, 0, c->width, c->height, c->backgroundColor); } break;
        
        case 2:
        {
            s32 halfWidth = c->width/2;
            
            s32 tY = 0;
            s32 tX = halfWidth*threadID;
            s32 tH = c->height;
            s32 tW = halfWidth;
            
            ls_uiClearRect(c, tX, tY, tW, tH, c->backgroundColor);
        } break;
        
        case 4:
        {
            s32 halfWidth  = c->width/2;
            s32 halfHeight = c->height/2;
            
            s32 tY = halfHeight*(threadID/2);
            s32 tX = halfWidth*(threadID%2);
            s32 tH = halfHeight;
            s32 tW = halfWidth;
            
            ls_uiClearRect(c, tX, tY, tW, tH, c->backgroundColor);
        } break;
        
        case 8:
        {
            s32 qrtWidth   = c->width/4;
            s32 halfHeight = c->height/2;
            
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
            RenderCommand *curr     = (RenderCommand *)ls_stackPop(currLayer);
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
            
            //TODO: I don't know if this is good
            s32 pixelHeight         = curr->pixelHeight;
#if _DEBUG
            c->isTagged = curr->isTagged;
#endif
            
            switch(curr->type)
            {
                case UI_RC_LABEL8:
                {
                    //TODO: I don't like this.
                    s32 yBaseOff = h - pixelHeight;
                    //ls_uiGlyphString_8(c, font, xPos, yPos + yBaseOff, threadRect, scissor, curr->label8, textColor);
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
                    UITextBox *box = curr->textBox;
                    
                    Color caretColor = textColor;
                    const s32 horzOff = 4;
                    
                    //TODO: Make the font selection more of a global thing??
                    s32 strPixelHeight = pixelHeight;
                    
                    ls_uiBorderedRect(c, xPos, yPos, w, h, threadRect, scissor, bkgColor);
                    
                    s32 strX = xPos + horzOff;
                    s32 strY = yPos + h - strPixelHeight;
                    
                    if(box->align == UI_TB_ALIGN_RIGHT || box->align == UI_TB_ALIGN_CENTER)
                    {
                        ls_uiRenderAlignedStringOnRect(c, font, box, strX, strY, w, h, threadRect, scissor, textColor, c->invTextColor);
                    }
                    else
                    {
                        //NOTETODO: For now we double draw for selected strings. We can improve with 3-segment drawing.
                        ls_uiRenderStringOnRect(c, box, strX, strY, w, h, threadRect, scissor, textColor, c->invTextColor);
                    }
                    
                } break;
                
                case UI_RC_LISTBOX:
                {
                    UIListBox *list = curr->listBox;
                    
                    s32 h = curr->layout.minY;
                    s32 maxHeight = curr->rect.h;
                    s32 origY     = yPos+maxHeight-h;
                    
                    s32 strHeight = pixelHeight; 
                    s32 vertOff = ((h - strHeight) / 2) + 4; //TODO: @FontDescent
                    
                    ls_uiBorderedRect(c, xPos, origY, w, h, threadRect, scissor);
                    
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
                        
                        ls_uiBorder(c, xPos, yPos, w, maxHeight+1, threadRect, scissor);
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
                        UIBitmap bmp = { button->bmpData, button->w, button->h };
                        ls_uiBitmap(c, bmp, xPos, yPos, threadRect);
                    }
                    else { AssertMsg(FALSE, "Unhandled button style\n"); }
                    
                } break;
                
                case UI_RC_CHECK:
                {
                    UICheck *check = curr->check;
                    
                    if(check->style == UICHECK_BMP)
                    {
                        if(check->bmpActive && check->bmpInactive)
                        {
                            UIBitmap inactive = { check->bmpInactive, check->w, check->h };
                            UIBitmap active   = { check->bmpActive, check->w, check->h };
                            
                            UIBitmap chosen = check->isActive ? active : inactive;
                            ls_uiBitmap(c, chosen, xPos, yPos, threadRect);
                        }
                        else if(check->bmpInactive && check->bmpAdditive)
                        {
                            UIBitmap inactive = { check->bmpInactive, check->w, check->h };
                            ls_uiBitmap(c, inactive, xPos, yPos, threadRect);
                            if(check->isActive)
                            {
                                s32 addX = xPos;
                                s32 addY = yPos;
                                
                                if(check->addW > check->w) { addX -= (check->addW - check->w) / 2; }
                                if(check->addH > check->h) { addY -= (check->addH - check->h) / 2; }
                                
                                UIBitmap additive = { check->bmpAdditive, check->w, check->h };
                                ls_uiBitmap(c, additive, addX, addY, threadRect);
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
                        ls_uiFillRect(c, xPos+slidePos+1, yPos+1, rColorW, h-2,
                                      threadRect, scissor, slider->rColor);
                        
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
                            
                            s32 actualWidth  = slideWidth+2;
                            s32 actualHeight = 4 + h;
                            
                            ls_uiFillRect(c, actualX, actualY, actualWidth, actualHeight,
                                          threadRect, scissor, c->borderColor);
                        }
                        else
                        {
                            ls_uiFillRect(c, xPos+slidePos, yPos, slideWidth, h,
                                          threadRect, scissor, c->borderColor);
                        }
                        
                    }
                    else if(slider->style == SL_LINE)
                    { AssertMsg(FALSE, "Slider style line is not implemented\n"); }
                    
                    //NOTE: Draw the displayed text, and hide through Alpha the slider info.
                    
                    Color rectColor = c->widgetColor;
                    rectColor = SetAlpha(rectColor, opacity);
                    ls_uiBorderedRect(c, xPos, yPos, w, h, threadRect, scissor, rectColor, borderColor);
                    
                    s32 strHeight = pixelHeight;
                    s32 strWidth  = ls_uiGlyphStringRect(c, font, slider->text, pixelHeight).w;
                    s32 xOff      = (w - strWidth) / 2;
                    s32 yOff      = (h - strHeight) + 3; //TODO: @FontDescent
                    
                    Color textColor = c->textColor;
                    textColor = SetAlpha(textColor, opacity);
                    
                    ls_uiGlyphString(c, font, pixelHeight, xPos+xOff, yPos + yOff, threadRect, scissor,
                                     slider->text, textColor);
                } break;
                
                case UI_RC_MENU:
                {
                    UIMenu *menu = curr->menu;
                    ls_uiBorderedRect(c, xPos, yPos, w, h, threadRect, scissor, bkgColor, c->widgetColor);
                    
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
                    ls_uiStretchBitmap(c, threadRect, curr->rect, &curr->bitmap);
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
                        ls_uiCircle(c, picker->pickedX, picker->pickedY, 
                                    picker->radius*0.1f+2, 2, threadRect, scissor, RGBg(0x0));
                        ls_uiCircle(c, picker->pickedX, picker->pickedY, 
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
                
                default: { 
                    char error[128]   = "Unhandled Render Command Type ";
                    u32 cmdTypeStrLen = ls_len((char*)RenderCommandTypeAsString[curr->type]);
                    ls_memcpy((void *)RenderCommandTypeAsString[curr->type], (void *)(error + 30), cmdTypeStrLen);
                    error[30+cmdTypeStrLen] = '\n';
                    
                    AssertMsg(FALSE, (char *)error);
                } break;
            }
        }
    }
    
    c->renderGroups[threadID].isDone = TRUE;
    
#if _DEBUG
    RenderCommandUID = 0;
#endif
    
    return;
}
#endif //LS_UI_OPENGL_BACKEND

#endif //LS_UI_IMPLEMENTATION
