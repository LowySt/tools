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

#include "lsInput.h"

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


const     u32 THREAD_COUNT       = 4;
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


union UIRect
{
    struct { s32 minX, minY, maxX, maxY; };
    struct { s32 x,    y,    w,    h; };
};

struct UILayoutRect
{
    s32 minX, minY, maxX, maxY;
    s32 startX, startY;
};

struct UIGlyph
{
    u8 *data;
    u32 size;
    
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
    UIGlyph *glyph;
    s32 **kernAdvanceTable; //NOTE: Needs to keep this in the heap cause it stack-overflows.
    
    u32 pixelHeight;
    u32 maxCodepoint;
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
};

struct UIContext;

enum UIButtonStyle { UIBUTTON_CLASSIC, UIBUTTON_LINK, UIBUTTON_TEXT_NOBORDER, UIBUTTON_NO_TEXT, UIBUTTON_BMP };

typedef b32(*ButtonProc)(UIContext *c, void *userData);
struct UIButton
{
    //TODO: With the current design I have to select the font in 2 different places.
    //      The best solution is probably to just hold a pointer to the font to be used in the 
    //      Button itself (And all other text widgets as well...)
    UIButtonStyle style;
    
    utf32 name;
    u8 *bmpData;
    s32 w, h;
    
    b32 isHot;
    b32 isHeld;
    
    ButtonProc onClick;
    ButtonProc onHold;
    
    void *data; //TODO: Separate onClick / onHold user data
};

enum UICheckStyle { UICHECK_BMP };

typedef b32(*CheckProc)(UIContext *c, void *userData);
struct UICheck
{
    UICheckStyle style;
    
    b32 isActive;
    
    u8 *bmpActive;
    u8 *bmpInactive;
    s32 w, h;
    
    u8 *bmpAdditive;
    s32 addW, addH;
    
    CheckProc onChange;
    void *data;
};

typedef b32(*TextBoxProc)(UIContext *, void *userData);
struct UITextBox
{
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
    
    TextBoxProc preInput;
    TextBoxProc postInput;
    
    void *data; //TODO: Separate preInput / postInput user data
};

enum UIArrowSide { UIA_LEFT, UIA_RIGHT, UIA_UP, UIA_DOWN };

struct UIListBoxItem
{
    utf32 name;
    Color bkgColor;
    Color textColor;
};

typedef void(*ListBoxProc)(UIContext *, void *);
struct UIListBox
{
    Array<UIListBoxItem> list;
    s32 selectedIndex;
    
    u32 dtOpen;
    b32 isOpening;
    b32 isOpen;
    
    Color arrowBkg;
    
    ListBoxProc onSelect;
    void *data;
};


enum SliderStyle { SL_LINE, SL_BOX };

struct UISlider
{
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
    utf32 name;
    
    b32 isVisible;
    b32 isHot;
    ButtonProc onClick;
    void       *userData;
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


const u32 UI_Z_LAYERS = 4;

struct RenderGroup
{
    stack RenderCommands[UI_Z_LAYERS];
    volatile b32 isDone;
};

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
    
    RenderGroup renderGroups[RENDER_GROUP_COUNT];
    UIRect      renderUIRects[THREAD_COUNT];
    
    HDC  WindowDC;
    HDC  BackBufferDC;
    HBITMAP DibSection;
    
    CONDITION_VARIABLE startRender;
    CRITICAL_SECTION crit;
    
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
    
    onDestroyFunc onDestroy;
};

struct ___threadCtx
{
    UIContext *c;
    u64 ThreadID;
};


//NOTE: Functions

HWND         ls_uiCreateWindow(HINSTANCE MainInstance, UIContext *c);
HWND         ls_uiCreateWindow(UIContext *c);
UIContext *  ls_uiInitDefaultContext(u8 *drawBuffer, u32 width, u32 height, RenderCallback cb);

void         ls_uiFrameBegin(UIContext *c);
void         ls_uiFrameEnd(UIContext *c, u64 frameTimeTargetMs);

void         ls_uiAddOnDestroyCallback(UIContext *c, onDestroyFunc f);

void         ls_uiPushRenderCommand(UIContext *c, RenderCommand command, s32 zLayer);
void         ls_uiStartScrollableRegion(UIContext *c, UIScrollableRegion *scroll);
void         ls_uiEndScrollableRegion(UIContext *c);
void         ls_uiResetScrollableRegion(UIContext *c);

void         ls_uiFocusChange(UIContext *c, u64 *focus);
b32          ls_uiInFocus(UIContext *c, void *p);
b32          ls_uiHasCapture(UIContext *c, void *p);
void         ls_uiSelectFontByPixelHeight(UIContext *cxt, u32 pixelHeight);
s32          ls_uiSelectFontByFontSize(UIContext *cxt, UIFontSize fontSize);

Color        ls_uiDarkenRGB(Color c, f32 percentage);
Color        ls_uiLightenRGB(Color c, f32 percentage);
Color        ls_uiAlphaBlend(Color source, Color dest, u8 alpha);
Color        ls_uiAlphaBlend(Color source, Color dest);
Color        ls_uiRGBAtoARGB(Color c);
Color        ls_uiARGBtoRGBA(Color c);

void         ls_uiRect(UIContext *c, s32 x, s32 y, s32 w, s32 h, Color bkgColor, Color borderColor, s32 zLayer);


void         ls_uiHSeparator(UIContext *c, s32 x, s32 y, s32 width, s32 lineWidth, Color lineColor, s32 zLayer);
void         ls_uiVSeparator(UIContext *c, s32 x, s32 y, s32 height, s32 lineWidth, Color lineColor, s32 zLayer);

UIButton     ls_uiButtonInit(UIContext *c, UIButtonStyle s, ButtonProc onClick, ButtonProc onHold, void *data);
UIButton     ls_uiButtonInit(UIContext *c, UIButtonStyle s, const char32_t *text, ButtonProc onClick,
                             ButtonProc onHold, void *userData);
UIButton     ls_uiButtonInit(UIContext *c, UIButtonStyle s, utf32 text, 
                             ButtonProc onClick, ButtonProc onHold, void *data);
UIButton     ls_uiButtonInit(UIContext *c, UIButtonStyle s, const char32_t *text,
                             ButtonProc onClick, ButtonProc onHold, void *data);
void         ls_uiButtonInit(UIContext *c, UIButton *b, UIButtonStyle s, utf32 t,
                             ButtonProc onClick, ButtonProc onHold, void *data);
void         ls_uiButtonInit(UIContext *c, UIButton *, UIButtonStyle, const char32_t *t,
                             ButtonProc onClick, ButtonProc onHold, void *data);

b32          ls_uiButton(UIContext *c, UIButton *button, s32 xPos, s32 yPos, Color bkgColor, s32 zLayer);
b32          ls_uiButton(UIContext *c, UIButton *button, s32 xPos, s32 yPos, s32 zLayer);


UICheck      ls_uiCheckInit(UIContext *c, UICheckStyle s,
                            u8 *bmpActive, u8 *bmpInactive, s32 w, s32 h, CheckProc onChange, void *data);
UICheck      ls_uiCheckInit(UIContext *c, UICheckStyle s, u8 *bmpInactive, s32 w, s32 h,
                            u8 *bmpAdditive, s32 addW, s32 addH, CheckProc onChange, void *data);

void         ls_uiLabelInRect(UIContext *c, utf8 label, s32 xPos, s32 yPos,
                              Color bkgColor, Color borderColor, Color textColor, s32 zLayer);
void         ls_uiLabelInRect(UIContext *c, utf8 label, s32 xPos, s32 yPos, s32 minWidth, s32 minHeight,
                              Color bkgColor, Color borderColor, Color textColor, s32 zLayer);

void         ls_uiLabel(UIContext *c, utf32 label, f32 xPos, f32 yPos, Color textColor, s32 zLayer);

void         ls_uiLabel(UIContext *c, utf32 label, s32 xPos, s32 yPos, Color textColor, s32 zLayer);
void         ls_uiLabel(UIContext *c, const char32_t *label, s32 xPos, s32 yPos, Color textColor, s32 zLayer);
void         ls_uiLabel(UIContext *c, utf8 label, s32 xPos, s32 yPos, Color textColor, s32 zLayer);
void         ls_uiLabel(UIContext *c, const u8 *label, s32 xPos, s32 yPos, Color textColor, s32 zLayer);

UILayoutRect ls_uiLabelLayout(UIContext *c, utf32 label, UILayoutRect layout, UIRect deltaPos, Color textColor, s32 zLayer);
UILayoutRect ls_uiLabelLayout(UIContext *c, utf32 label, UILayoutRect layout, Color textColor, s32 zLayer);
UILayoutRect ls_uiLabelLayout(UIContext *c, const char32_t *label, UILayoutRect layout, Color textColor, s32 zLayer);

void         ls_uiLabel(UIContext *c, utf32 label, s32 xPos, s32 yPos, s32 zLayer);
void         ls_uiLabel(UIContext *c, const char32_t *label, s32 xPos, s32 yPos, s32 zLayer);
void         ls_uiLabel(UIContext *c, utf8 label, s32 xPos, s32 yPos, s32 zLayer);
void         ls_uiLabel(UIContext *c, const u8 *label, s32 xPos, s32 yPos, s32 zLayer);
UILayoutRect ls_uiLabelLayout(UIContext *c, utf32 label, UILayoutRect layout, s32 zLayer);
UILayoutRect ls_uiLabelLayout(UIContext *c, const char32_t *label, UILayoutRect layout, s32 zLayer);

void         ls_uiTextBoxClear(UIContext *c, UITextBox *box);
void         ls_uiTextBoxSet(UIContext *c, UITextBox *box, const char32_t *s);
void         ls_uiTextBoxSet(UIContext *c, UITextBox *box, utf32 s);
void         ls_uiTextBoxInit(UIContext *c, UITextBox *box, s32 len, s32 maxLen, b32 singleLine, b32 readOnly, TextBoxProc preInput, TextBoxProc postInput);
b32          ls_uiTextBox(UIContext *c, UITextBox *box, s32 xPos, s32 yPos, s32 w, s32 h, s32 zLayer);

u32          ls_uiListBoxAddEntry(UIContext *c, UIListBox *list, char *s);
u32          ls_uiListBoxAddEntry(UIContext *c, UIListBox *list, utf32 s);
void         ls_uiListBoxRemoveEntry(UIContext *c, UIListBox *list, u32 index);
b32          ls_uiListBox(UIContext *c, UIListBox *list, s32 xPos, s32 yPos, s32 w, s32 h, u32 zLayer);

UISlider     ls_uiSliderInit(char32_t *name, s32 maxVal, s32 minVal, f64 currPos, SliderStyle s, Color l, Color r);
void         ls_uiSliderChangeValueBy(UIContext *c, UISlider *f, s32 valueDiff);
s32          ls_uiSliderGetValue(UIContext *c, UISlider *f);
b32          ls_uiSlider(UIContext *c, UISlider *slider, s32 xPos, s32 yPos, s32 w, s32 h);

UIButton     ls_uiMenuButton(ButtonProc onClick, u8 *bitmapData, s32 width, s32 height);
UISubMenu  * ls_uiMenuAddSub(UIContext *c, UIMenu *menu, UISubMenu sub);
UISubMenu  * ls_uiMenuAddSub(UIContext *c, UIMenu *menu, const char32_t *name);
UIMenuItem * ls_uiMenuAddItem(UIContext *c, UIMenu *menu, const char32_t *name, ButtonProc onClick, void *userData);
UIMenuItem * ls_uiSubMenuAddItem(UIContext *c, UISubMenu *sub, const char32_t *name, ButtonProc onClick, void *userData);
UIMenuItem * ls_uiSubMenuAddItem(UIContext *c, UIMenu *menu, u32 subIdx, const char32_t *name, ButtonProc onClick, void *data);
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
    //TODO: Setup an automated arena system for the UI. For right now
    //      We are gonna hook into the program. Which is bad!
    ls_arenaUse(frameArena);
    
    va_list argList;
    va_start(argList, fmt);
    
    const s32 buffSize = 512;
    char *buff = (char *)ls_alloc(buffSize);
    
    s32 len = ls_vlog(fmt, buff, buffSize, &argList);
    
    va_end(argList);
    
    utf8 label = ls_utf8Constant((u8 *)buff, len);
    
    ls_uiLabel(c, label, x, y, RGBg(255), 2);
    ls_uiLabel(c, label, x-1, y, RGBg(0), 2);
    
    ls_arenaUse(globalArena);
}

#endif

void __ls_ui_fillRenderThreadUIRects(UIContext *c)
{
    //TODO: Probably do -1 on the height/width directly here??
    switch(THREAD_COUNT)
    {
        case 0:
        case 1: { return; } break;
        
        case 2:
        {
            c->renderUIRects[0] = {0, 0, (s32)(c->width / 2), (s32)c->height};
            c->renderUIRects[1] = {(s32)(c->width / 2), 0, (s32)(c->width / 2), (s32)c->height};
        } break;
        
        case 4:
        {
            c->renderUIRects[0] = {0, 0, (s32)(c->width / 2), (s32)(c->height/2)};
            c->renderUIRects[1] = {(s32)(c->width / 2), 0, (s32)(c->width / 2), (s32)(c->height/2)};
            c->renderUIRects[2] = {0, (s32)(c->height/2), (s32)(c->width / 2), (s32)(c->height/2)};
            c->renderUIRects[3] = {(s32)(c->width / 2), (s32)(c->height/2), (s32)(c->width / 2),(s32)(c->height/2)};
        } break;
        
        case 8:
        {
            c->renderUIRects[0] = {0, 0, (s32)(c->width / 4), (s32)(c->height/2)};
            c->renderUIRects[1] = {(s32)(c->width / 4), 0, (s32)(c->width / 4), (s32)(c->height/2)};
            c->renderUIRects[2] = {(s32)(c->width / 2), 0, (s32)(c->width / 4), (s32)(c->height/2)};
            c->renderUIRects[3] = {(s32)(3*c->width / 4), 0, (s32)(c->width / 4), (s32)(c->height/2)};
            c->renderUIRects[4] = {0, (s32)(c->height/2), (s32)(c->width / 4), (s32)(c->height/2)};
            c->renderUIRects[5] = {(s32)(c->width / 4), (s32)(c->height/2), (s32)(c->width / 4),(s32)(c->height/2)};
            c->renderUIRects[6] = {(s32)(c->width / 2), (s32)(c->height/2), (s32)(c->width / 4),(s32)(c->height/2)};
            c->renderUIRects[7] = {(s32)(3*c->width / 4),(s32)(c->height/2),(s32)(c->width / 4),(s32)(c->height/2)};
        } break;
        
        default: { AssertMsg(FALSE, "Unhandled Thread Count"); } break;
    }
    
    return;
}


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
            
            //NOTE: Reset the Render UIRect for every Thread.
            __ls_ui_fillRenderThreadUIRects(c);
            
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


void __ui_default_windows_render_callback(UIContext *c)
{
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
    
}

UIContext *ls_uiInitDefaultContext(u8 *backBuffer, u32 width, u32 height, RenderCallback cb = __ui_default_windows_render_callback)
{
    UIContext *uiContext       = (UIContext *)ls_alloc(sizeof(UIContext));
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
    uiContext->backgroundColor = RGBg(0x38);
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

void ls_uiFrameBegin(UIContext *c)
{
    static b32 isStartup = TRUE;
    
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
    
    c->focusWasSetThisFrame = FALSE;
    c->lastFocus            = c->currentFocus;
    if(c->nextFrameFocusChange == TRUE)
    {
        c->currentFocus = c->nextFrameFocus;
        c->lastFocus    = c->currentFocus;
        c->nextFrameFocusChange = FALSE;
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
}

void ls_uiFrameBeginChild(UIContext *c)
{
    static b32 isStartup = TRUE;
    
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
    
    c->focusWasSetThisFrame = FALSE;
    c->lastFocus            = c->currentFocus;
    if(c->nextFrameFocusChange == TRUE)
    {
        c->currentFocus = c->nextFrameFocus;
        c->lastFocus    = c->currentFocus;
        c->nextFrameFocusChange = FALSE;
    }
    
    c->hasReceivedInput = FALSE;
    
    //NOTE: The child frame doesn't need a message pump, because windows
    //      Pumps messages to all windows that were created by this thread.
    //      BUT This means that we must begin the child frame before the main frame
    //      to properly clear input.
    //      TODO: Maybe we want to move the message pump to a separate function
    //      to make the order of function calls more obvious and less error prone!
    
    if(isStartup) { isStartup = FALSE; c->hasReceivedInput = TRUE; }
}

void ls_uiFrameEnd(UIContext *c, u64 frameTimeTargetMs)
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

void ls_uiFrameEndChild(UIContext *c, u64 frameTimeTargetMs)
{
    static u32 lastFrameTime = 0;
    
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
    
    return;
}

inline void ls_uiAddOnDestroyCallback(UIContext *c, onDestroyFunc f)
{ c->onDestroy = f; }

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

b32 ls_uiRectIsInside(UIRect r1, UIRect check)
{
    if((r1.x >= check.x) && ((r1.x + r1.w) <= (check.x + check.w)))
    {
        if((r1.y >= check.y) && ((r1.y + r1.h) <= (check.y + check.h)))
        {
            return TRUE;
        }
    }
    
    return FALSE;
}

b32 ls_uiRectIntersects(UIRect r1, UIRect check)
{
    s32 x0 = r1.x;
    s32 x1 = r1.x + r1.w;
    s32 y0 = r1.y;
    s32 y1 = r1.y + r1.h;
    
    b32 cond = (x1 < check.x || y1 < check.y || x0 > (check.x + check.w) || y0 > (check.y + check.h));
    return !cond;
}

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
    
    switch(THREAD_COUNT)
    {
        case 0:
        case 1:
        {
            command.threadRect.minX = 0;
            command.threadRect.minY = 0;
            command.threadRect.maxX = c->width;
            command.threadRect.maxY = c->height-1;
            
            stack *renderStack = &c->renderGroups[0].RenderCommands[zLayer];
            AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 0\n");
            ls_stackPush(renderStack, (void *)&command);
            return;
        } break;
        
        case 2:
        {
            if(ls_uiRectIsInside(commandRect, c->renderUIRects[0]))
            {
                command.threadRect       = c->renderUIRects[0];
                command.threadRect.maxX -= 1;
                command.threadRect.maxY -= 1;
                
                stack *renderStack = &c->renderGroups[0].RenderCommands[zLayer];
                AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 0\n");
                
                ls_stackPush(renderStack, (void *)&command);
                return;
            }
            else if(ls_uiRectIsInside(commandRect, c->renderUIRects[1]))
            {
                command.threadRect       = c->renderUIRects[1];
                command.threadRect.maxX  = c->width;
                command.threadRect.maxY -= 1;
                
                stack *renderStack = &c->renderGroups[1].RenderCommands[zLayer];
                AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 1\n");
                
                ls_stackPush(renderStack, (void *)&command);
                return;
            }
            else
            {
                //Half in one, half in another.
                
                RenderCommand section = command;
                section.threadRect.minX = 0;
                section.threadRect.minY = 0;
                section.threadRect.maxX = (c->width / 2)-1;
                section.threadRect.maxY = c->height-1;
                
                stack *renderStack = &c->renderGroups[0].RenderCommands[zLayer];
                AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 0\n");
                
                ls_stackPush(renderStack, (void *)&section);
                
                section.threadRect.minX = (c->width / 2);
                section.threadRect.minY = 0;
                section.threadRect.maxX = c->width;
                section.threadRect.maxY = c->height-1;
                
                renderStack = &c->renderGroups[1].RenderCommands[zLayer];
                AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 1\n");
                
                ls_stackPush(renderStack, (void *)&section);
                
                return;
            }
            
        } break;
        
        case 4:
        {
            s32 mask = ls_uiRectIntersects(commandRect, c->renderUIRects[0]);
            mask |= ls_uiRectIntersects(commandRect, c->renderUIRects[1]) << 1;
            mask |= ls_uiRectIntersects(commandRect, c->renderUIRects[2]) << 2;
            mask |= ls_uiRectIntersects(commandRect, c->renderUIRects[3]) << 3;
            
            //NOTE: Drawing outside of the window. No point in pushing a render command
            if(mask == 0) { return; }
            
            switch(mask)
            {
                case 1:
                {
                    command.threadRect       = c->renderUIRects[0];
                    command.threadRect.maxX -= 1;
                    command.threadRect.maxY -= 1;
                    
                    stack *renderStack = &c->renderGroups[0].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 0\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 2:
                {
                    command.threadRect       = c->renderUIRects[1];
                    command.threadRect.maxX  = c->width;
                    command.threadRect.maxY -= 1;
                    
                    stack *renderStack = &c->renderGroups[1].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 1\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 4:
                {
                    command.threadRect       = c->renderUIRects[2];
                    command.threadRect.maxX -= 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    stack *renderStack = &c->renderGroups[2].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 2\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 8:
                {
                    command.threadRect       = c->renderUIRects[3];
                    command.threadRect.maxX  = c->width;
                    command.threadRect.maxY  = c->height-1;
                    
                    stack *renderStack = &c->renderGroups[3].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 3\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 5:
                {
                    //Bottom Left
                    command.threadRect       = c->renderUIRects[0];
                    command.threadRect.maxX -= 1;
                    command.threadRect.maxY -= 1;
                    
                    stack *renderStack = &c->renderGroups[0].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 0\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //Top Left
                    command.threadRect       = c->renderUIRects[2];
                    command.threadRect.maxX -= 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[2].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 2\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 10:
                {
                    //Bottom Right
                    command.threadRect       = c->renderUIRects[1];
                    command.threadRect.maxX  = c->width;
                    command.threadRect.maxY -= 1;
                    
                    stack *renderStack = &c->renderGroups[1].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 1\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //Top Right
                    command.threadRect       = c->renderUIRects[3];
                    command.threadRect.maxX  = c->width;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[3].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 3\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 12:
                {
                    //Top Left
                    command.threadRect       = c->renderUIRects[2];
                    command.threadRect.maxX -= 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    stack *renderStack = &c->renderGroups[2].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 2\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //Top Right
                    command.threadRect       = c->renderUIRects[3];
                    command.threadRect.maxX  = c->width;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[3].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 3\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 3:
                {
                    //Bottom Left
                    command.threadRect       = c->renderUIRects[0];
                    command.threadRect.maxX -= 1;
                    command.threadRect.maxY -= 1;
                    
                    stack *renderStack = &c->renderGroups[0].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 0\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //Bottom Right
                    command.threadRect       = c->renderUIRects[1];
                    command.threadRect.maxX  = c->width;
                    command.threadRect.maxY -= 1;
                    
                    renderStack = &c->renderGroups[1].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 1\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 15:
                {
                    //Bottom Left
                    command.threadRect       = c->renderUIRects[0];
                    command.threadRect.maxX -= 1;
                    command.threadRect.maxY -= 1;
                    
                    stack *renderStack = &c->renderGroups[0].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 0\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //Bottom Right
                    command.threadRect       = c->renderUIRects[1];
                    command.threadRect.maxX  = c->width;
                    command.threadRect.maxY -= 1;
                    
                    renderStack = &c->renderGroups[1].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 1\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //Top Left
                    command.threadRect       = c->renderUIRects[2];
                    command.threadRect.maxX -= 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[2].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 2\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //Top Right
                    command.threadRect       = c->renderUIRects[3];
                    command.threadRect.maxX  = c->width;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[3].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 3\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                default: { AssertMsg(FALSE, "Unhandled mask in 4 threads\n"); return; } break;
            }
        } break;
        
        case 8:
        {
            s32 mask = ls_uiRectIntersects(commandRect, c->renderUIRects[0]);
            mask |= ls_uiRectIntersects(commandRect, c->renderUIRects[1]) << 1;
            mask |= ls_uiRectIntersects(commandRect, c->renderUIRects[2]) << 2;
            mask |= ls_uiRectIntersects(commandRect, c->renderUIRects[3]) << 3;
            mask |= ls_uiRectIntersects(commandRect, c->renderUIRects[4]) << 4;
            mask |= ls_uiRectIntersects(commandRect, c->renderUIRects[5]) << 5;
            mask |= ls_uiRectIntersects(commandRect, c->renderUIRects[6]) << 6;
            mask |= ls_uiRectIntersects(commandRect, c->renderUIRects[7]) << 7;
            
            //NOTE: Drawing outside of the window. No point in pushing a render command
            if(mask == 0) { return; }
            
            switch(mask)
            {
                case 1:
                {
                    command.threadRect       = c->renderUIRects[0];
                    command.threadRect.maxX -= 1;
                    command.threadRect.maxY -= 1;
                    
                    stack *renderStack = &c->renderGroups[0].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 0\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 2:
                {
                    command.threadRect       = c->renderUIRects[1];
                    command.threadRect.maxX  = (s32)(c->width / 2) - 1;
                    command.threadRect.maxY -= 1;
                    
                    stack *renderStack = &c->renderGroups[1].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 1\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 4:
                {
                    command.threadRect       = c->renderUIRects[2];
                    command.threadRect.maxX  = (s32)(3*c->width / 4) - 1;
                    command.threadRect.maxY -= 1;
                    
                    stack *renderStack = &c->renderGroups[2].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 2\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 8:
                {
                    command.threadRect       = c->renderUIRects[3];
                    command.threadRect.maxX  = c->width;
                    command.threadRect.maxY -= 1;
                    
                    stack *renderStack = &c->renderGroups[3].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 3\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 16:
                {
                    command.threadRect       = c->renderUIRects[4];
                    command.threadRect.maxX -= 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    stack *renderStack = &c->renderGroups[4].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 4\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 32:
                {
                    command.threadRect       = c->renderUIRects[5];
                    command.threadRect.maxX  = (s32)(c->width / 2) - 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    stack *renderStack = &c->renderGroups[5].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 5\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 64:
                {
                    command.threadRect       = c->renderUIRects[6];
                    command.threadRect.maxX  = (s32)(3*c->width / 4) - 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    stack *renderStack = &c->renderGroups[6].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 6\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 128:
                {
                    command.threadRect       = c->renderUIRects[7];
                    command.threadRect.maxX  = c->width;
                    command.threadRect.maxY  = c->height-1;
                    
                    stack *renderStack = &c->renderGroups[7].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 7\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 3:
                {
                    //BL
                    command.threadRect       = c->renderUIRects[0];
                    command.threadRect.maxX -= 1;
                    command.threadRect.maxY -= 1;
                    
                    stack *renderStack = &c->renderGroups[0].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 0\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //BCL
                    command.threadRect       = c->renderUIRects[1];
                    command.threadRect.maxX  = (s32)(c->width / 2) - 1;
                    command.threadRect.maxY -= 1;
                    
                    renderStack = &c->renderGroups[1].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 1\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 6:
                {
                    //BCL
                    command.threadRect       = c->renderUIRects[1];
                    command.threadRect.maxX  = (s32)(c->width / 2) - 1;
                    command.threadRect.maxY -= 1;
                    
                    stack *renderStack = &c->renderGroups[1].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 1\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //BCR
                    command.threadRect       = c->renderUIRects[2];
                    command.threadRect.maxX  = (s32)(3*c->width / 4) - 1;
                    command.threadRect.maxY -= 1;
                    
                    renderStack = &c->renderGroups[2].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 2\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 12:
                {
                    //BCR
                    command.threadRect       = c->renderUIRects[2];
                    command.threadRect.maxX  = (s32)(3*c->width / 4) - 1;
                    command.threadRect.maxY -= 1;
                    
                    stack *renderStack = &c->renderGroups[2].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 2\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //BR
                    command.threadRect       = c->renderUIRects[3];
                    command.threadRect.maxX  = c->width;
                    command.threadRect.maxY -= 1;
                    
                    renderStack = &c->renderGroups[3].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 3\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 7:
                {
                    //BL
                    command.threadRect       = c->renderUIRects[0];
                    command.threadRect.maxX -= 1;
                    command.threadRect.maxY -= 1;
                    
                    stack *renderStack = &c->renderGroups[0].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 0\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //BCL
                    command.threadRect       = c->renderUIRects[1];
                    command.threadRect.maxX  = (s32)(c->width / 2) - 1;
                    command.threadRect.maxY -= 1;
                    
                    renderStack = &c->renderGroups[1].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 1\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //BCR
                    command.threadRect       = c->renderUIRects[2];
                    command.threadRect.maxX  = (s32)(3*c->width / 4) - 1;
                    command.threadRect.maxY -= 1;
                    
                    renderStack = &c->renderGroups[2].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 2\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 14:
                {
                    //BCL
                    command.threadRect       = c->renderUIRects[1];
                    command.threadRect.maxX  = (s32)(c->width / 2) - 1;
                    command.threadRect.maxY -= 1;
                    
                    stack *renderStack = &c->renderGroups[1].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 1\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //BCR
                    command.threadRect       = c->renderUIRects[2];
                    command.threadRect.maxX  = (s32)(3*c->width / 4) - 1;
                    command.threadRect.maxY -= 1;
                    
                    renderStack = &c->renderGroups[2].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 2\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //BR
                    command.threadRect       = c->renderUIRects[3];
                    command.threadRect.maxX  = c->width;
                    command.threadRect.maxY -= 1;
                    
                    renderStack = &c->renderGroups[3].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 3\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 15:
                {
                    //BL
                    command.threadRect       = c->renderUIRects[0];
                    command.threadRect.maxX -= 1;
                    command.threadRect.maxY -= 1;
                    
                    stack *renderStack = &c->renderGroups[0].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 0\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //BCL
                    command.threadRect       = c->renderUIRects[1];
                    command.threadRect.maxX  = (s32)(c->width / 2) - 1;
                    command.threadRect.maxY -= 1;
                    
                    renderStack = &c->renderGroups[1].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 1\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //BCR
                    command.threadRect       = c->renderUIRects[2];
                    command.threadRect.maxX  = (s32)(3*c->width / 4) - 1;
                    command.threadRect.maxY -= 1;
                    
                    renderStack = &c->renderGroups[2].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 2\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //BR
                    command.threadRect       = c->renderUIRects[3];
                    command.threadRect.maxX  = c->width;
                    command.threadRect.maxY -= 1;
                    
                    renderStack = &c->renderGroups[3].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 3\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 48:
                {
                    //TL
                    command.threadRect       = c->renderUIRects[4];
                    command.threadRect.maxX -= 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    stack *renderStack = &c->renderGroups[4].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 4\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //TCL
                    command.threadRect       = c->renderUIRects[5];
                    command.threadRect.maxX  = (s32)(c->width / 2) - 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[5].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 5\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 96:
                {
                    //TCL
                    command.threadRect       = c->renderUIRects[5];
                    command.threadRect.maxX  = (s32)(c->width / 2) - 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    stack *renderStack = &c->renderGroups[5].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 5\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //TCR
                    command.threadRect       = c->renderUIRects[6];
                    command.threadRect.maxX  = (s32)(3*c->width / 4) - 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[6].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 6\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 192:
                {
                    //TCR
                    command.threadRect       = c->renderUIRects[6];
                    command.threadRect.maxX  = (s32)(3*c->width / 4) - 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    stack *renderStack = &c->renderGroups[6].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 6\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //TR
                    command.threadRect       = c->renderUIRects[7];
                    command.threadRect.maxX  = c->width;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[7].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 7\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 112:
                {
                    //TL
                    command.threadRect       = c->renderUIRects[4];
                    command.threadRect.maxX -= 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    stack *renderStack = &c->renderGroups[4].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 4\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //TCL
                    command.threadRect       = c->renderUIRects[5];
                    command.threadRect.maxX  = (s32)(c->width / 2) - 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[5].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 5\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //TCR
                    command.threadRect       = c->renderUIRects[6];
                    command.threadRect.maxX  = (s32)(3*c->width / 4) - 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[6].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 6\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 224:
                {
                    //TCL
                    command.threadRect       = c->renderUIRects[5];
                    command.threadRect.maxX  = (s32)(c->width / 2) - 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    stack *renderStack = &c->renderGroups[5].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 5\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //TCR
                    command.threadRect       = c->renderUIRects[6];
                    command.threadRect.maxX  = (s32)(3*c->width / 4) - 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[6].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 6\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //TR
                    command.threadRect       = c->renderUIRects[7];
                    command.threadRect.maxX  = c->width;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[7].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 7\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 240:
                {
                    //TL
                    command.threadRect       = c->renderUIRects[4];
                    command.threadRect.maxX -= 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    stack *renderStack = &c->renderGroups[4].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 4\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //TCL
                    command.threadRect       = c->renderUIRects[5];
                    command.threadRect.maxX  = (s32)(c->width / 2) - 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[5].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 5\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //TCR
                    command.threadRect       = c->renderUIRects[6];
                    command.threadRect.maxX  = (s32)(3*c->width / 4) - 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[6].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 6\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //TR
                    command.threadRect       = c->renderUIRects[7];
                    command.threadRect.maxX  = c->width;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[7].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 7\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 17:
                {
                    //BL
                    command.threadRect       = c->renderUIRects[0];
                    command.threadRect.maxX -= 1;
                    command.threadRect.maxY -= 1;
                    
                    stack *renderStack = &c->renderGroups[0].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 0\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //TL
                    command.threadRect       = c->renderUIRects[4];
                    command.threadRect.maxX -= 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[4].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 4\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 34:
                {
                    //BCL
                    command.threadRect       = c->renderUIRects[1];
                    command.threadRect.maxX  = (s32)(c->width / 2) - 1;
                    command.threadRect.maxY -= 1;
                    
                    stack *renderStack = &c->renderGroups[1].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 1\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //TCL
                    command.threadRect       = c->renderUIRects[5];
                    command.threadRect.maxX  = (s32)(c->width / 2) - 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[5].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 5\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 68:
                {
                    //BCR
                    command.threadRect       = c->renderUIRects[2];
                    command.threadRect.maxX  = (s32)(3*c->width / 4) - 1;
                    command.threadRect.maxY -= 1;
                    
                    stack *renderStack = &c->renderGroups[2].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 2\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //TCR
                    command.threadRect       = c->renderUIRects[6];
                    command.threadRect.maxX  = (s32)(3*c->width / 4) - 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[6].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 6\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 136:
                {
                    //BR
                    command.threadRect       = c->renderUIRects[3];
                    command.threadRect.maxX  = c->width;
                    command.threadRect.maxY -= 1;
                    
                    stack *renderStack = &c->renderGroups[3].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 3\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //TR
                    command.threadRect       = c->renderUIRects[7];
                    command.threadRect.maxX  = c->width;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[7].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 7\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 51:
                {
                    //BL
                    command.threadRect       = c->renderUIRects[0];
                    command.threadRect.maxX -= 1;
                    command.threadRect.maxY -= 1;
                    
                    stack *renderStack = &c->renderGroups[0].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 0\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //BCL
                    command.threadRect       = c->renderUIRects[1];
                    command.threadRect.maxX  = (s32)(c->width / 2) - 1;
                    command.threadRect.maxY -= 1;
                    
                    renderStack = &c->renderGroups[1].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 1\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //TL
                    command.threadRect       = c->renderUIRects[4];
                    command.threadRect.maxX -= 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[4].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 4\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //TCL
                    command.threadRect       = c->renderUIRects[5];
                    command.threadRect.maxX  = (s32)(c->width / 2) - 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[5].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 5\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 102:
                {
                    //BCL
                    command.threadRect       = c->renderUIRects[1];
                    command.threadRect.maxX  = (s32)(c->width / 2) - 1;
                    command.threadRect.maxY -= 1;
                    
                    stack *renderStack = &c->renderGroups[1].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 1\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //BCR
                    command.threadRect       = c->renderUIRects[2];
                    command.threadRect.maxX  = (s32)(3*c->width / 4) - 1;
                    command.threadRect.maxY -= 1;
                    
                    renderStack = &c->renderGroups[2].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 2\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //TCL
                    command.threadRect       = c->renderUIRects[5];
                    command.threadRect.maxX  = (s32)(c->width / 2) - 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[5].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 5\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //TCR
                    command.threadRect       = c->renderUIRects[6];
                    command.threadRect.maxX  = (s32)(3*c->width / 4) - 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[6].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 6\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 204:
                {
                    //BCR
                    command.threadRect       = c->renderUIRects[2];
                    command.threadRect.maxX  = (s32)(3*c->width / 4) - 1;
                    command.threadRect.maxY -= 1;
                    
                    stack *renderStack = &c->renderGroups[2].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 2\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //BR
                    command.threadRect       = c->renderUIRects[3];
                    command.threadRect.maxX  = c->width;
                    command.threadRect.maxY -= 1;
                    
                    renderStack = &c->renderGroups[3].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 3\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //TCR
                    command.threadRect       = c->renderUIRects[6];
                    command.threadRect.maxX  = (s32)(3*c->width / 4) - 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[6].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 6\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //TR
                    command.threadRect       = c->renderUIRects[7];
                    command.threadRect.maxX  = c->width;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[7].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 7\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 119:
                {
                    //BL
                    command.threadRect       = c->renderUIRects[0];
                    command.threadRect.maxX -= 1;
                    command.threadRect.maxY -= 1;
                    
                    stack *renderStack = &c->renderGroups[0].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 0\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //BCL
                    command.threadRect       = c->renderUIRects[1];
                    command.threadRect.maxX  = (s32)(c->width / 2) - 1;
                    command.threadRect.maxY -= 1;
                    
                    renderStack = &c->renderGroups[1].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 1\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //BCR
                    command.threadRect       = c->renderUIRects[2];
                    command.threadRect.maxX  = (s32)(3*c->width / 4) - 1;
                    command.threadRect.maxY -= 1;
                    
                    renderStack = &c->renderGroups[2].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 2\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //TL
                    command.threadRect       = c->renderUIRects[4];
                    command.threadRect.maxX -= 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[4].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 4\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //TCL
                    command.threadRect       = c->renderUIRects[5];
                    command.threadRect.maxX  = (s32)(c->width / 2) - 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[5].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 5\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //TCR
                    command.threadRect       = c->renderUIRects[6];
                    command.threadRect.maxX  = (s32)(3*c->width / 4) - 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[6].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 6\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 238:
                {
                    //BCL
                    command.threadRect       = c->renderUIRects[1];
                    command.threadRect.maxX  = (s32)(c->width / 2) - 1;
                    command.threadRect.maxY -= 1;
                    
                    stack *renderStack = &c->renderGroups[1].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 1\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //BCR
                    command.threadRect       = c->renderUIRects[2];
                    command.threadRect.maxX  = (s32)(3*c->width / 4) - 1;
                    command.threadRect.maxY -= 1;
                    
                    renderStack = &c->renderGroups[2].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 2\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //BR
                    command.threadRect       = c->renderUIRects[3];
                    command.threadRect.maxX  = c->width;
                    command.threadRect.maxY -= 1;
                    
                    renderStack = &c->renderGroups[3].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 3\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //TCL
                    command.threadRect       = c->renderUIRects[5];
                    command.threadRect.maxX  = (s32)(c->width / 2) - 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[5].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 5\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //TCR
                    command.threadRect       = c->renderUIRects[6];
                    command.threadRect.maxX  = (s32)(3*c->width / 4) - 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[6].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 6\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //TR
                    command.threadRect       = c->renderUIRects[7];
                    command.threadRect.maxX  = c->width;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[7].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 7\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                case 255:
                {
                    //BL
                    command.threadRect       = c->renderUIRects[0];
                    command.threadRect.maxX -= 1;
                    command.threadRect.maxY -= 1;
                    
                    stack *renderStack = &c->renderGroups[0].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 0\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //BCL
                    command.threadRect       = c->renderUIRects[1];
                    command.threadRect.maxX  = (s32)(c->width / 2) - 1;
                    command.threadRect.maxY -= 1;
                    
                    renderStack = &c->renderGroups[1].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 1\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //BCR
                    command.threadRect       = c->renderUIRects[2];
                    command.threadRect.maxX  = (s32)(3*c->width / 4) - 1;
                    command.threadRect.maxY -= 1;
                    
                    renderStack = &c->renderGroups[2].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 2\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //BR
                    command.threadRect       = c->renderUIRects[3];
                    command.threadRect.maxX  = c->width;
                    command.threadRect.maxY -= 1;
                    
                    renderStack = &c->renderGroups[3].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 3\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //TL
                    command.threadRect       = c->renderUIRects[4];
                    command.threadRect.maxX -= 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[4].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 4\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //TCL
                    command.threadRect       = c->renderUIRects[5];
                    command.threadRect.maxX  = (s32)(c->width / 2) - 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[5].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 5\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //TCR
                    command.threadRect       = c->renderUIRects[6];
                    command.threadRect.maxX  = (s32)(3*c->width / 4) - 1;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[6].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 6\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    
                    //TR
                    command.threadRect       = c->renderUIRects[7];
                    command.threadRect.maxX  = c->width;
                    command.threadRect.maxY  = c->height-1;
                    
                    renderStack = &c->renderGroups[7].RenderCommands[zLayer];
                    AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 7\n");
                    
                    ls_stackPush(renderStack, (void *)&command);
                    return;
                } break;
                
                default: { AssertMsg(FALSE, "Unhandled mask in 8 threads\n"); return; } break;
            }
            
        } break;
        
        default: { AssertMsg(FALSE, "Thread count not supported\n"); } return;
    }
    
    AssertMsg(FALSE, "Should never reach this case!\n");
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

//TODO: Fix for premultiplied alpha?
Color ls_uiDarkenRGB(Color c, f32 percentage)
{
    u8 *c8 = (u8 *)&c;
    
    u8 highest = 0;
    if(c8[0] > highest) { highest = c8[0]; }
    if(c8[1] > highest) { highest = c8[1]; }
    if(c8[2] > highest) { highest = c8[2]; }
    
    if(highest == 0)  { return c; }
    
    u8 reduction = (255.0f*percentage);
    if(highest < reduction) { reduction = highest; }
    
    f32 realFactor = (f32)(highest - reduction) / highest;
    
    c8[0] -= c8[0] * realFactor;
    c8[1] -= c8[1] * realFactor;
    c8[2] -= c8[2] * realFactor;
    
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
}

void ls_uiFillRect(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h, 
                   UIRect threadRect, UIRect scissor, Color col)
{
    s32 minX = threadRect.minX > scissor.x ? threadRect.minX : scissor.x;
    s32 minY = threadRect.minY > scissor.y ? threadRect.minY : scissor.y;
    s32 maxX = threadRect.maxX < scissor.x+scissor.w ? threadRect.maxX : scissor.x+scissor.w;
    s32 maxY = threadRect.maxY < scissor.y+scissor.h ? threadRect.maxY : scissor.y+scissor.h;
    
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
}

void ls_uiFillCircle(UIContext *c, s32 centerX, s32 centerY, s32 radius,
                     UIRect threadRect, UIRect scissor, Color col)
{
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
}

//TODO: Change with better rasterizer
void ls_uiCircle(UIContext *c, s32 centerX, s32 centerY, s32 radius, s32 thickness,
                 UIRect threadRect, UIRect scissor, Color col)
{
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

void ls_uiBackground(UIContext *c)
{
    AssertMsg((c->height % 4) == 0, "Window Height not divisible by 4 (SIMD)\n");
    AssertMsg((c->width % 4) == 0, "Window Width not divisible by 4 (SIMD)\n");
    
    __m128i color = _mm_set1_epi32 ((int)c->backgroundColor.value);
    
    u32 numIterations = (c->width*c->height) / 4;
    for(u32 i = 0; i < numIterations; i++)
    {
        u32 idx = i*sizeof(s32)*4;
        
        __m128i *At = (__m128i *)(c->drawBuffer + idx);
        _mm_storeu_si128(At, color);
    }
}

void ls_uiStretchBitmap(UIContext *c, UIRect threadRect, UIRect dst, UIBitmap *bmp)
{
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
}

void ls_uiBitmap(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h, UIRect threadRect, u32 *data)
{
    s32 minX = threadRect.minX;
    s32 minY = threadRect.minY;
    s32 maxX = threadRect.maxX;
    s32 maxY = threadRect.maxY;
    
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
}

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

s32 ls_uiGetKernAdvance(UIContext *c, s32 codepoint1, s32 codepoint2)
{
    UIFont *font = c->currFont;
    s32 kernAdvance = font->kernAdvanceTable[codepoint1][codepoint2];
    
    return kernAdvance;
}

s32 ls_uiGetKernAdvance(UIFont *font, s32 codepoint1, s32 codepoint2)
{
    s32 kernAdvance = font->kernAdvanceTable[codepoint1][codepoint2];
    
    return kernAdvance;
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

//TODO: Use font max descent to determine yOffsets globally
//      Maybe instead make glyphstring only do 1 line at a time and push line responsibility outside?
void ls_uiGlyphString(UIContext *c, UIFont *font, s32 xPos, s32 yPos,
                      UIRect threadRect, UIRect scissor, utf32 text, Color textColor)
{
    AssertMsg(c, "Context is null\n");
    LogMsg(font, "Passed font is null\n");
    if(!font) { return; }
    
    s32 currXPos = xPos;
    s32 currYPos = yPos;
    for(u32 i = 0; i < text.len; i++)
    {
        u32 indexInGlyphArray = text.data[i];
        AssertMsgF(indexInGlyphArray <= font->maxCodepoint, "GlyphIndex %d OutOfBounds\n", indexInGlyphArray);
        
        UIGlyph *currGlyph = &font->glyph[indexInGlyphArray];
        ls_uiGlyph(c, currXPos, currYPos, threadRect, scissor, currGlyph, textColor);
        
        s32 kernAdvance = 0;
        if(i < text.len-1) { kernAdvance = ls_uiGetKernAdvance(font, text.data[i], text.data[i+1]); }
        
        currXPos += (currGlyph->xAdv + kernAdvance);
        
        //NOTETODO VERY BAD!! need to determine
        if(indexInGlyphArray == (u32)'\n') { currYPos -= font->pixelHeight; currXPos = xPos; }
    }
}

//TODO: Rename this GlyphString8!
void ls_uiGlyphString_8(UIContext *c, UIFont *font, s32 xPos, s32 yPos,
                        UIRect threadRect, UIRect scissor, utf8 text, Color textColor)
{
    AssertMsg(c, "Context is null\n");
    LogMsg(font, "Passed font is null\n");
    if(!font) { return; }
    
    s32 currXPos = xPos;
    s32 currYPos = yPos;
    for(u32 i = 0; i < text.len; i++)
    {
        u32 indexInGlyphArray = ls_utf32CharFromUtf8(text, i);
        AssertMsgF(indexInGlyphArray <= font->maxCodepoint, "GlyphIndex %d OutOfBounds\n", indexInGlyphArray);
        
        UIGlyph *currGlyph = &font->glyph[indexInGlyphArray];
        ls_uiGlyph(c, currXPos, currYPos, threadRect, scissor, currGlyph, textColor);
        
        s32 kernAdvance = 0;
        if(i < text.len-1) { kernAdvance = ls_uiGetKernAdvance(font, text.data[i], text.data[i+1]); }
        
        currXPos += (currGlyph->xAdv + kernAdvance);
        
        //NOTETODO VERY BAD!! need to determine
        if(indexInGlyphArray == (u32)'\n') { currYPos -= font->pixelHeight; currXPos = xPos; }
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

//NOTE: Occupied pixel length of a glyph string
//TODO: Take into consideration newlines inside a string.?
//      Maybe instead make glyphstring only do 1 line at a time and push line responsibility outside?
s32 ls_uiGlyphStringLen(UIContext *c, UIFont *font, utf32 text)
{
    AssertMsg(c, "Context is null\n");
    LogMsg(font, "Passed font is null\n");
    if(!font) { return 0; }
    
    s32 totalLen = 0;
    for(u32 i = 0; i < text.len; i++)
    {
        u32 indexInGlyphArray = text.data[i];
        AssertMsgF(indexInGlyphArray <= font->maxCodepoint, "GlyphIndex %d OutOfBounds\n", indexInGlyphArray);
        
        UIGlyph *currGlyph = &font->glyph[indexInGlyphArray];
        
        s32 kernAdvance = 0;
        if(i < text.len-1) { kernAdvance = ls_uiGetKernAdvance(font, text.data[i], text.data[i+1]); }
        
        totalLen += (currGlyph->xAdv + kernAdvance);
    }
    
    return totalLen;
}

UIRect ls_uiGlyphStringRect(UIContext *c, UIFont *font, utf32 text)
{
    AssertMsg(c, "Context is null\n");
    LogMsg(font, "Passed font is null\n");
    if(!font) { return {}; }
    
    s32 maxWidth = 0;
    
    s32 totalWidth  = 0;
    s32 totalHeight = font->pixelHeight;
    for(u32 i = 0; i < text.len; i++)
    {
        u32 indexInGlyphArray = text.data[i];
        AssertMsgF(indexInGlyphArray <= font->maxCodepoint, "GlyphIndex %d OutOfBounds\n", indexInGlyphArray);
        
        UIGlyph *currGlyph = &font->glyph[indexInGlyphArray];
        
        s32 kernAdvance = 0;
        if(i < text.len-1) { kernAdvance = ls_uiGetKernAdvance(font, text.data[i], text.data[i+1]); }
        
        if(indexInGlyphArray == (u32)'\n')
        {
            totalHeight += font->pixelHeight;
            totalWidth   = 0;
            continue;
        }
        
        totalWidth += (currGlyph->xAdv + kernAdvance);
        if(totalWidth > maxWidth) { maxWidth = totalWidth; }
    }
    
    UIRect result = {0, 0, maxWidth, totalHeight};
    
    return result;
}

s32 ls_uiGlyphStringLen_8(UIContext *c, UIFont *font, utf8 text)
{
    AssertMsg(c, "Context is null\n");
    LogMsg(font, "Passed font is null\n");
    if(!font) { return 0; }
    
    s32 totalLen = 0;
    for(u32 i = 0; i < text.len; i++)
    {
        u32 indexInGlyphArray = ls_utf32CharFromUtf8(text, i);
        AssertMsgF(indexInGlyphArray <= font->maxCodepoint, "GlyphIndex %d OutOfBounds\n", indexInGlyphArray);
        
        UIGlyph *currGlyph = &font->glyph[indexInGlyphArray];
        
        s32 kernAdvance = 0;
        if(i < text.len-1) { kernAdvance = ls_uiGetKernAdvance(font, text.data[i], text.data[i+1]); }
        
        totalLen += (currGlyph->xAdv + kernAdvance);
    }
    
    return totalLen;
}

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
    if(!c->fonts) { return; }
    
    //TODO: Hardcoded
    b32 found = FALSE;
    for(u32 i = 0; i < 4; i++)
    { if(c->fonts[i].pixelHeight == pixelHeight) { found = TRUE; c->currFont = &c->fonts[i]; } }
    
    AssertMsg(found, "Asked pixelHeight not available\n");
}

inline
s32 ls_uiSelectFontByFontSize(UIContext *c, UIFontSize fontSize)
{ 
    LogMsg(c->fonts, "No fonts were loaded\n");
    if(!c->fonts) { return 0; }
    
    c->currFont = &c->fonts[fontSize]; return c->currFont->pixelHeight;
}

UIButton ls_uiButtonInit(UIContext *c, UIButtonStyle s, ButtonProc onClick, ButtonProc onHold = NULL, void *userData = NULL)
{
    AssertMsg(c, "UI Context is null\n");
    
    UIButton Result = {s, {}, 0, 0, 0, FALSE, FALSE, onClick, onHold, userData};
    return Result;
}

UIButton ls_uiButtonInit(UIContext *c, UIButtonStyle s, const char32_t *text, ButtonProc onClick,
                         ButtonProc onHold = NULL, void *userData = NULL)
{
    AssertMsg(c, "UI Context is null\n");
    AssertMsg(c->currFont, "Font is not selected\n");
    
    utf32 name = ls_utf32FromUTF32(text);
    
    s32 height = c->currFont->pixelHeight + 2; //Add Margin above and below text
    s32 width = ls_uiGlyphStringLen(c, c->currFont, name) + 16; //Add margin on each side
    
    UIButton Result = {s, name, 0, width, height, FALSE, FALSE, onClick, onHold, userData};
    return Result;
}

UIButton ls_uiButtonInit(UIContext *c, UIButtonStyle s, utf32 text, ButtonProc onClick,
                         ButtonProc onHold = NULL, void *userData = NULL)
{
    AssertMsg(c, "UI Context is null\n");
    AssertMsg(c->currFont, "Font is not selected\n");
    
    s32 height = c->currFont->pixelHeight + 2; //Add Margin above and below text
    s32 width = ls_uiGlyphStringLen(c, c->currFont, text) + 16; //Add margin on each side 
    
    UIButton Result = {s, text, 0, width, height, FALSE, FALSE, onClick, onHold, userData};
    return Result;
}

void ls_uiButtonInit(UIContext *c, UIButton *b, UIButtonStyle s, utf32 text, ButtonProc onClick,
                     ButtonProc onHold = NULL, void *userData = NULL)
{
    AssertMsg(c, "UI Context is null\n");
    AssertMsg(c->currFont, "Font is not selected\n");
    
    b->style   = s;
    b->name    = text;
    b->onClick = onClick;
    b->onHold  = onHold;
    b->data    = userData;
    
    s32 height = c->currFont->pixelHeight + 2; //Add Margin above and below text
    s32 width = ls_uiGlyphStringLen(c, c->currFont, text) + 16; //Add margin on each side
    
    b->w = width;
    b->h = height;
}

void ls_uiButtonInit(UIContext *c, UIButton *b, UIButtonStyle s, const char32_t *t, ButtonProc onClick,
                     ButtonProc onHold = NULL, void *data = NULL)
{
    AssertMsg(c, "UI Context is null\n");
    AssertMsg(c->currFont, "Font is not selected\n");
    
    b->style   = s;
    
    //TODO: Should this be a ls_utf32Constant() ??? I've been passed a constant literal...
    b->name    = ls_utf32FromUTF32(t);
    b->onClick = onClick;
    b->onHold  = onHold;
    b->data    = data;
    
    s32 height = c->currFont->pixelHeight + 2; //TODO: This margin doesn't work for multiple pixel height
    s32 width = ls_uiGlyphStringLen(c, c->currFont, b->name) + 16; //Add margin on each side
    
    b->w = width;
    b->h = height;
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
    
    if(MouseInRect(xPos, yPos, button->w, button->h))// && ls_uiInFocus(cxt, 0))
    { 
        button->isHot = TRUE;
        bkgColor = c->highliteColor;
        if(button->style == UIBUTTON_LINK) { textColor = c->highliteColor; }
        
        //b32 noCapture = ls_uiHasCapture(cxt, 0);
        
        if(LeftClick)// && noCapture)
        {
            if(button->onClick) { inputUse |= button->onClick(c, button->data); }
        }
        
        if(LeftHold)//  && noCapture)
        {
            button->isHeld = TRUE;
            bkgColor       = c->pressedColor;
            if(button->onHold) { inputUse |= button->onHold(c, button->data); }
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


b32 ls_uiButton(UIContext *c, UIButton *button, s32 xPos, s32 yPos, s32 zLayer = 0)
{
    Input *UserInput = &c->UserInput;
    
    b32 inputUse = FALSE;
    
    Color bkgColor    = c->widgetColor;
    Color textColor   = c->textColor;
    Color borderColor = c->borderColor;
    
    if(button->style == UIBUTTON_TEXT_NOBORDER) { bkgColor = c->backgroundColor; }
    
    if(MouseInRect(xPos, yPos, button->w, button->h))// && ls_uiInFocus(cxt, 0))
    { 
        button->isHot = TRUE;
        bkgColor = c->highliteColor;
        if(button->style == UIBUTTON_LINK) { textColor = c->highliteColor; }
        
        //b32 noCapture = ls_uiHasCapture(cxt, 0);
        
        if(LeftClick)// && noCapture)
        {
            if(button->onClick) { inputUse |= button->onClick(c, button->data); }
        }
        
        if(LeftHold)//  && noCapture)
        {
            button->isHeld = TRUE;
            bkgColor       = c->pressedColor;
            if(button->onHold) { inputUse |= button->onHold(c, button->data); }
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
                       u8 *bmpActive, u8 *bmpInactive, s32 w, s32 h, CheckProc onChange, void *data)
{
    UICheck result = {};
    
    result.style       = s;
    result.isActive    = FALSE;
    result.bmpActive   = bmpActive;
    result.bmpInactive = bmpInactive;
    result.w           = w;
    result.h           = h;
    result.onChange    = onChange;
    result.data        = data;
    
    return result;
}

UICheck ls_uiCheckInit(UIContext *c, UICheckStyle s, u8 *bmpInactive, s32 w, s32 h,
                       u8 *bmpAdditive, s32 addW, s32 addH, CheckProc onChange, void *data)
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
    result.onChange    = onChange;
    result.data        = data;
    
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
            if(check->onChange) { inputUse |= check->onChange(c, check->data); }
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
    s32 strWidth   = ls_uiGlyphStringLen(c, c->currFont, label);
    s32 rectWidth  = strWidth + 2*marginX;
    s32 rectHeight = c->currFont->pixelHeight + 2*marginY; //TODO: Ascent/Descent, not this bullshit.
    
    return { xPos, yPos, rectWidth, rectHeight };
}

void ls_uiLabelInRect(UIContext *c, utf32 label, s32 xPos, s32 yPos,
                      Color bkgColor, Color borderColor, Color textColor, s32 zLayer = 0)
{
    s32 marginX    = 0.3f*c->currFont->pixelHeight;
    s32 marginY    = 0.25f*c->currFont->pixelHeight;
    s32 strWidth   = ls_uiGlyphStringLen(c, c->currFont, label);
    s32 rectWidth  = strWidth + 2*marginX;
    s32 rectHeight = c->currFont->pixelHeight + 2*marginY; //TODO: Ascent/Descent, not this bullshit.
    
    ls_uiLabel(c, label, xPos + marginX, yPos + 2*marginY, textColor, zLayer);
    ls_uiRect(c, xPos, yPos, rectWidth, rectHeight, bkgColor, borderColor, zLayer);
}

void ls_uiLabelInRect(UIContext *c, utf8 label, s32 xPos, s32 yPos,
                      Color bkgColor, Color borderColor, Color textColor, s32 zLayer = 0)
{
    const s32 marginX = 4;
    const s32 marginY = 4;
    s32 strWidth   = ls_uiGlyphStringLen_8(c, c->currFont, label);
    s32 rectWidth  = strWidth + 2*marginX;
    s32 rectHeight = c->currFont->pixelHeight + 2*marginY; //TODO: Ascent/Descent, not this bullshit.
    
    ls_uiLabel(c, label, xPos + marginX, yPos + 2*marginY, textColor, zLayer);
    ls_uiRect(c, xPos, yPos, rectWidth, rectHeight, bkgColor, borderColor, zLayer);
}

void ls_uiLabelInRect(UIContext *c, utf8 label, s32 xPos, s32 yPos, s32 minWidth, s32 minHeight,
                      Color bkgColor, Color borderColor, Color textColor, s32 zLayer = 0)
{
    s32 marginX = 4;
    s32 marginY = 4;
    s32 strWidth   = ls_uiGlyphStringLen_8(c, c->currFont, label);
    s32 rectWidth  = strWidth + 2*marginX;
    s32 rectHeight = c->currFont->pixelHeight + 2*marginY; //TODO: Ascent/Descent, not this bullshit.
    
    if(rectWidth  < minWidth)  { marginX += (minWidth - rectWidth) / 2; rectWidth = minWidth; }
    if(rectHeight < minHeight) { marginY += (minHeight - rectHeight) / 2; rectHeight = minHeight; }
    
    ls_uiLabel(c, label, xPos + marginX, yPos + 2*marginY, textColor, zLayer);
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
    
    s32 width  = ls_uiGlyphStringLen(c, c->currFont, label);
    s32 height = c->currFont->pixelHeight;
    
    RenderCommand command = { UI_RC_LABEL32, xPos, yPos, width, height };
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
    
    s32 width  = ls_uiGlyphStringLen_8(c, c->currFont, label);
    s32 height = c->currFont->pixelHeight;
    
    RenderCommand command = { UI_RC_LABEL8, xPos, yPos, width, height };
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
}

//TODO: Now that viewEndIdx is deprecated these functions are a lot less usefuk
void ls_uiTextBoxSet(UIContext *c, UITextBox *box, const char32_t *s)
{
    ls_utf32FromUTF32_t(&box->text, s);
}

void ls_uiTextBoxSet(UIContext *c, UITextBox *box, utf32 s)
{
    ls_utf32Set(&box->text, s);
    
}

void ls_uiTextBoxInit(UIContext *c, UITextBox *box, s32 len, s32 maxLen = 0, b32 singleLine = TRUE, b32 readOnly = FALSE, TextBoxProc preInput = NULL, TextBoxProc postInput = NULL)
{
    box->text         = ls_utf32Alloc(len);
    box->maxLen       = maxLen;
    box->isSingleLine = singleLine;
    box->isReadonly   = readOnly;
    box->preInput     = preInput;
    box->postInput    = postInput;
}

//TODO: Text Alignment
b32 ls_uiTextBox(UIContext *c, UITextBox *box, s32 xPos, s32 yPos, s32 w, s32 h, s32 zLayer = 0)
{
    Input *UserInput = &c->UserInput;
    b32 inputUse = FALSE;
    
    if(LeftClickIn(xPos, yPos, w, h) && ls_uiHasCapture(c, 0)) {
        c->currentFocus = (u64 *)box;
        c->focusWasSetThisFrame = TRUE;
        box->isCaretOn = TRUE; 
    }
    
    //TODOHACKHACK
    if(box->lineCount == 0) box->lineCount = 1;
    //TODOHACKHACK
    
    //TODO: Hardcoded values.
    const s32 horzOff      = 12;
    const s32 viewAddWidth = w - 2*horzOff;
    const s32 maxIndexDiff = ls_uiMonoGlyphMaxIndexDiff(c, c->currFont, viewAddWidth);
    
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
        if(box->preInput)
        { inputUse |= box->preInput(c, box->data); }
        
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
        
        
        if(box->postInput && inputUse)
        { box->postInput(c, box->data); }
    }
    
    RenderCommand command = {UI_RC_TEXTBOX, xPos, yPos, w, h };
    command.textBox       = box;
    command.bkgColor      = c->widgetColor;
    command.textColor     = c->textColor;
    ls_uiPushRenderCommand(c, command, zLayer);
    
    return inputUse;
}

void ls_uiDrawArrow(UIContext *c, s32 x, s32 yPos, s32 w, s32 h,
                    UIRect threadRect, UIRect scissor, Color bkgColor, UIArrowSide s)
{
    //TODO: Scissor???
    s32 minX = threadRect.minX;
    s32 minY = threadRect.minY;
    s32 maxX = threadRect.maxX;
    s32 maxY = threadRect.maxY;
    
    u32 *At = (u32 *)c->drawBuffer;
    
    s32 xPos = x-1;
    
    ls_uiBorderedRect(c, xPos, yPos, w, h, threadRect, scissor, bkgColor);
    
    if(s == UIA_DOWN)
    {
        s32 arrowWidth = 8;
        s32 hBearing = (w - arrowWidth)/2;
        s32 xBase = xPos+hBearing;
        s32 xEnd  = xBase + arrowWidth;
        
        s32 arrowHeight = 4;
        s32 vBearing = (h - arrowHeight)/2;
        s32 yStart = (yPos + h - vBearing) - 1;
        s32 yEnd = yStart - arrowHeight;
        
        if(yStart >= maxY) { yStart = maxY; }
        if(xBase  < minX)  { xEnd -= (minX - xBase); xBase = minX; }
        
        for(s32 y = yStart; y >= yEnd; y--)
        {
            if(y < minY) { break; }
            
            for(s32 x = xBase; x < xEnd; x++)
            {
                if(x >= maxX) { break; }
                
                if(x < 0 || x >= c->width)  continue;
                if(y < 0 || y >= c->height) continue;
                
                At[y*c->width + x] = c->borderColor.value;
            }
            
            xBase += 1;
            xEnd  -= 1;
        }
    }
    else if(s == UIA_RIGHT)
    {
        s32 arrowWidth  = 4;
        s32 hBearing    = (w - arrowWidth)/2;
        s32 xBase       = xPos + hBearing;
        s32 xEnd        = xBase+1;
        
        s32 arrowHeight = 8;
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
        s32 arrowWidth  = 4;
        s32 hBearing    = (w - arrowWidth)/2;
        s32 xBase       = xPos + w - hBearing - 1;
        s32 xEnd        = xBase+1;
        
        s32 arrowHeight = 8;
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

//NOTETODO: ListBox manages the data of the entry itself, even when a unistring is already passed.
//          This feels strange, and probably error-prone.

//TODO @MemoryLeak @Leak I really think ListBox shouldn't manage memory. Fix This.
inline u32 ls_uiListBoxAddEntry(UIContext *c, UIListBox *list, char *s)
{ 
    utf32 text = ls_utf32FromAscii(s);
    UIListBoxItem item = { text, c->widgetColor, c->textColor };
    
    return ls_arrayAppendIndex(&list->list, item);
}

//TODO @MemoryLeak @Leak
inline u32 ls_uiListBoxAddEntry(UIContext *c, UIListBox *list, utf32 s)
{
    utf32 copy = ls_utf32Copy(s);
    UIListBoxItem item = { copy, c->widgetColor, c->textColor };
    return ls_arrayAppendIndex(&list->list, item);
}

inline void ls_uiListBoxRemoveEntry(UIContext *c, UIListBox *list, u32 index)
{ 
    //NOTETODO: Is this good????
    if(list->selectedIndex == index) { list->selectedIndex = 0; }
    
    UIListBoxItem val = list->list[index];
    ls_utf32Free(&val.name);
    //list->list.remove(index);
    return ls_arrayRemove(&list->list, index);
}

b32 ls_uiListBox(UIContext *c, UIListBox *list, s32 xPos, s32 yPos, s32 w, s32 h, u32 zLayer = 0)
{
    Input *UserInput = &c->UserInput;
    b32 inputUse = FALSE;
    
    const s32 arrowBoxWidth = 24;
    if(LeftClickIn(xPos+w, yPos, arrowBoxWidth, h) && ls_uiHasCapture(c, 0))
    {
        c->currentFocus = (u64 *)list;
        c->focusWasSetThisFrame = TRUE;
        
        if(list->isOpen) { list->isOpen = FALSE; }
        //else { list->isOpening = TRUE; } //NOTE:TODO: This is because Claudio wanted instant list open. 
        else { list->isOpen = TRUE; }
    }
    
    Color bkgColor = c->widgetColor;
    s32 arrowX = xPos + w - 1;
    if(MouseInRect(arrowX, yPos, arrowBoxWidth, h)) { bkgColor = c->highliteColor; }
    list->arrowBkg = bkgColor;
    
    if(list->isOpening)
    {
        list->dtOpen += c->dt;
        if(list->dtOpen > 70) { list->isOpen = TRUE; list->isOpening = FALSE; list->dtOpen = 0; }
    }
    
    if(ls_uiInFocus(c, list))
    {
        if(list->isOpen)
        {
            for(u32 i = 0; i < list->list.count; i++)
            {
                s32 currY = yPos - (h*(i+1));
                UIListBoxItem *currItem = list->list + i;
                
                //TODO: The constant resetting is kinda stupid. Makes me think I should just not
                //      have listbox items with their own colors. Never even used that feature.
                currItem->bkgColor  = c->widgetColor;
                currItem->textColor = c->textColor;
                if(MouseInRect(xPos+1, currY+1, w-2, h-1)) 
                { 
                    currItem->bkgColor = c->highliteColor;
                    if(LeftClick) { 
                        c->mouseCapture = (u64 *)list;
                        
                        list->selectedIndex = i; list->isOpen = FALSE;
                        inputUse = TRUE;
                        if(list->onSelect) { list->onSelect(c, list->data); }
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
    { list->isOpen = FALSE; }
    
    s32 maxHeight = (list->list.count)*(h);
    //NOTE: Here the maxHeight in the command rect is used to determine the maximum height when expanded
    //      the height passed in the layout rect in minY determines the minimum height when contracted.
    //      This also means that yPos is shifted by maxHeight
    RenderCommand list_command = { UI_RC_LISTBOX, xPos, yPos-maxHeight, w, maxHeight };
    list_command.layout.minY = h;
    list_command.listBox = list;
    ls_uiPushRenderCommand(c, list_command, zLayer);
    
    RenderCommand arr_command = { UI_RC_LISTBOX_ARR, xPos+w, yPos, arrowBoxWidth, h };
    arr_command.listBox = list;
    ls_uiPushRenderCommand(c, arr_command, zLayer);
    
    return inputUse;
}

UISlider ls_uiSliderInit(char32_t *name, s32 maxVal, s32 minVal, f64 currPos, SliderStyle s, Color l, Color r)
{
    UISlider Result = {};
    
    if(name) { Result.text = ls_utf32FromUTF32((const char32_t *)name); }
    else     { Result.text = ls_utf32Alloc(16); }
    
    Result.maxValue = maxVal;
    Result.minValue = minVal;
    Result.currPos  = currPos;
    Result.style    = s;
    Result.lColor   = l;
    Result.rColor   = r;
    
    return Result;
}

void ls_uiSliderChangeValueBy(UIContext *c, UISlider *f, s32 valueDiff)
{
    s32 newValue = f->currValue + valueDiff;
    
    if(newValue <= f->minValue) { newValue = f->minValue; }
    if(newValue >= f->maxValue) { newValue = f->maxValue; }
    
    s32 range = (f->maxValue - f->minValue);
    f->currPos = (f64)(newValue - f->minValue) / (f64)range;
    
    return;
}

s32 ls_uiSliderGetValue(UIContext *c, UISlider *f)
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
        
        slider->currValue = ((slider->maxValue - slider->minValue) * slider->currPos) + slider->minValue;
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
        
        slider->currPos -= fractionMove;
        
        slider->currPos = ls_clamp(slider->currPos, 1.0, 0.0);
        
        hasAnsweredToInput = TRUE;
    }
    
    RenderCommand command = { UI_RC_SLIDER, xPos, yPos, w, h };
    command.slider = slider;
    command.borderColor = c->borderColor;
    
    ls_uiPushRenderCommand(c, command, 0);
    
    return hasAnsweredToInput;
}

UIButton ls_uiMenuButton(ButtonProc onClick, u8 *bitmapData, s32 width, s32 height)
{
    UIButton result = {};
    result.style    = UIBUTTON_BMP;
    result.bmpData  = bitmapData;
    result.w        = width;
    result.h        = height;
    result.onClick  = onClick;
    return result;
}

inline UISubMenu *ls_uiMenuAddSub(UIContext *c, UIMenu *menu, UISubMenu sub)
{ return ls_arrayAppend(&menu->subMenus, sub); }

UISubMenu *ls_uiMenuAddSub(UIContext *c, UIMenu *menu, const char32_t *name)
{ 
    UISubMenu newSub = {};
    newSub.name = ls_utf32FromUTF32(name);
    return ls_arrayAppend(&menu->subMenus, newSub);
}

UIMenuItem *ls_uiMenuAddItem(UIContext *c, UIMenu *menu, const char32_t *name, ButtonProc onClick, void *userData)
{
    UIMenuItem newItem = {};
    newItem.name       = ls_utf32FromUTF32(name);
    newItem.isVisible  = TRUE;
    newItem.onClick    = onClick;
    newItem.userData   = userData;
    return ls_arrayAppend(&menu->items, newItem);
}

UIMenuItem *ls_uiSubMenuAddItem(UIContext *c, UISubMenu *sub, const char32_t *name, ButtonProc onClick, void *userData)
{
    UIMenuItem newItem = {};
    
    newItem.name       = ls_utf32FromUTF32(name);
    newItem.isVisible  = TRUE;
    newItem.onClick    = onClick;
    newItem.userData   = userData;
    return ls_arrayAppend(&sub->items, newItem);
}

UIMenuItem *ls_uiSubMenuAddItem(UIContext *c, UIMenu *menu, u32 subIdx, const char32_t *name, ButtonProc onClick, void *userData)
{
    UIMenuItem newItem = {};
    
    newItem.name       = ls_utf32FromUTF32(name);
    newItem.isVisible  = TRUE;
    newItem.onClick    = onClick;
    newItem.userData   = userData;
    return ls_arrayAppend(&menu->subMenus[subIdx].items, newItem);
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
                        if(currItem->onClick) { currItem->onClick(c, currItem->userData); }
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
                c->currentFocus = (u64 *)menu;
                c->focusWasSetThisFrame = TRUE;
                
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
                inputUse |= item->onClick(c, item->userData);
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
}

void ls_uiFillColorWheel(UIContext *c, s32 centerX, s32 centerY, s32 radius, f32 value,
                         UIRect threadRect, UIRect scissor)
{
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
}

b32 ls_uiColorPicker(UIContext *c, UIColorPicker *picker, s32 x, s32 y, s32 w, s32 h, s32 zLayer = 0)
{
    Input *UserInput = &c->UserInput;
    
    if(LeftClickIn(x, y, w, h) && ls_uiHasCapture(c, 0)) {
        c->currentFocus = (u64 *)picker;
        c->mouseCapture = (u64 *)picker;
        c->focusWasSetThisFrame = TRUE;
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

void ls_uiRender(UIContext *c)
{
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
    
    c->renderFunc(c);
}

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
#if _DEBUG
            c->isTagged = curr->isTagged;
#endif
            
            switch(curr->type)
            {
                
                case UI_RC_LABEL8:
                {
                    //TODO: I don't like this.
                    ls_uiGlyphString_8(c, font, xPos, yPos, threadRect, scissor, curr->label8, textColor);
                } break;
                
                case UI_RC_LABEL32:
                {
                    ls_uiGlyphString(c, font, xPos, yPos, threadRect, scissor, curr->label32, textColor);
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
                    s32 strPixelHeight = font->pixelHeight;
                    
                    ls_uiBorderedRect(c, xPos, yPos, w, h, threadRect, scissor, bkgColor);
                    
                    s32 strX = xPos + horzOff;
                    s32 strY = yPos + h - strPixelHeight;
                    
                    //NOTETODO: For now we double draw for selected strings. We can improve with 3-segment drawing.
                    ls_uiRenderStringOnRect(c, box, strX, strY, w, h, threadRect, scissor, textColor, c->invTextColor);
                    
                } break;
                
                case UI_RC_LISTBOX:
                {
                    UIListBox *list = curr->listBox;
                    
                    s32 h = curr->layout.minY;
                    s32 maxHeight = curr->rect.h;
                    
                    s32 strHeight = font->pixelHeight; 
                    s32 vertOff = ((h - strHeight) / 2) + 4; //TODO: @FontDescent
                    
                    ls_uiBorderedRect(c, xPos, yPos+maxHeight, w, h, threadRect, scissor);
                    
                    if(list->list.count)
                    {
                        utf32 selected = list->list[list->selectedIndex].name;
                        ls_uiGlyphString(c, font, xPos+10, yPos + maxHeight + vertOff, threadRect, scissor, selected, c->textColor);
                    }
                    
                    if(list->isOpening)
                    {
                        s32 height = 0;
                        if(list->dtOpen > 17)  { height = maxHeight*0.10f; }
                        if(list->dtOpen > 34)  { height = maxHeight*0.35f; }
                        if(list->dtOpen > 52)  { height = maxHeight*0.70f; }
                        
                        if(!list->isOpen)
                        { ls_uiFillRect(c, xPos+1, yPos + maxHeight - height, w-2, height,
                                        threadRect, scissor, c->widgetColor); }
                    }
                    
                    if(list->isOpen)
                    {
                        for(u32 i = 0; i < list->list.count; i++)
                        {
                            s32 currY = yPos + maxHeight - (h*(i+1));
                            UIListBoxItem *currItem = list->list + i;
                            
                            ls_uiRect(c, xPos+1, currY, w-2, h, threadRect, scissor, currItem->bkgColor);
                            ls_uiGlyphString(c, font, xPos+10, yPos + maxHeight + vertOff - (h*(i+1)),
                                             threadRect, scissor, currItem->name, currItem->textColor);
                            
                        }
                        
                        ls_uiBorder(c, xPos, yPos, w, maxHeight+1, threadRect, scissor);
                    }
                    
                } break;
                
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
                            s32 strHeight = font->pixelHeight;
                            s32 strWidth  = ls_uiGlyphStringLen(c, font, button->name);
                            s32 xOff      = (w - strWidth) / 2; //TODO: What happens when the string is too long?
                            s32 yOff      = strHeight*0.25; //TODO: @FontDescent
                            
                            ls_uiGlyphString(c, font, xPos+xOff, yPos+yOff, threadRect, scissor, 
                                             button->name, textColor);
                        }
                    }
                    else if(button->style == UIBUTTON_LINK)
                    {
                        if(button->name.data)
                        {
                            s32 strHeight = font->pixelHeight;
                            s32 strWidth  = ls_uiGlyphStringLen(c, font, button->name);
                            s32 xOff      = (w - strWidth) / 2; //TODO: What happens when the string is too long?
                            s32 yOff      = strHeight*0.25; //TODO: @FontDescent
                            
                            ls_uiGlyphString(c, font, xPos+xOff, yPos+yOff, threadRect, scissor,
                                             button->name, textColor);
                        }
                    }
                    else if(button->style == UIBUTTON_TEXT_NOBORDER)
                    {
                        ls_uiRect(c, xPos, yPos, w, h, threadRect, scissor, bkgColor);
                        
                        if(button->name.data)
                        {
                            s32 strHeight = font->pixelHeight;
                            s32 strWidth  = ls_uiGlyphStringLen(c, font, button->name);
                            s32 xOff      = (w - strWidth) / 2; //TODO: What happens when the string is too long?
                            s32 yOff      = strHeight*0.25; //TODO: @FontDescent
                            
                            ls_uiGlyphString(c, font, xPos+xOff, yPos+yOff, threadRect, scissor, 
                                             button->name, textColor);
                        }
                    }
                    else if(button->style == UIBUTTON_NO_TEXT)
                    {
                        ls_uiRect(c, xPos, yPos, w, h, threadRect, scissor, bkgColor);
                    }
                    else if(button->style == UIBUTTON_BMP)
                    {
                        ls_uiBitmap(c, xPos, yPos, button->w, button->h, threadRect, (u32 *)button->bmpData);
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
                            u32 *bmpData = check->isActive ? (u32 *)check->bmpActive : (u32 *)check->bmpInactive;
                            ls_uiBitmap(c, xPos, yPos, w, h, threadRect, bmpData);
                        }
                        else if(check->bmpInactive && check->bmpAdditive)
                        {
                            ls_uiBitmap(c, xPos, yPos, check->w, check->h, threadRect, (u32 *)check->bmpInactive);
                            if(check->isActive)
                            {
                                s32 addX = xPos;
                                s32 addY = yPos;
                                
                                if(check->addW > check->w) { addX -= (check->addW - check->w) / 2; }
                                if(check->addH > check->h) { addY -= (check->addH - check->h) / 2; }
                                ls_uiBitmap(c, addX, addY, check->addW, check->addH,
                                            threadRect, (u32 *)check->bmpAdditive);
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
                        
                        utf32 val = ls_utf32FromInt(slider->currValue);
                        
                        s32 strHeight = font->pixelHeight;
                        
                        u32 textLen = ls_uiGlyphStringLen(c, font, val);
                        s32 strXPos = xPos + slidePos - textLen - 2;
                        Color textBkgC = slider->lColor;
                        
                        if(strXPos < xPos+1) { strXPos = xPos + slidePos + slideWidth + 2; textBkgC = slider->rColor; }
                        
                        Color valueColor = c->borderColor;
                        u8 alpha = 0x00 + (slider->isHeld*0xFF);
                        valueColor = SetAlpha(valueColor, alpha);
                        ls_uiGlyphString(c, font, strXPos, yPos + h - strHeight, threadRect, scissor, val, valueColor);
                        
                        ls_utf32Free(&val);
                        
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
                    
                    s32 strHeight = font->pixelHeight;
                    
                    s32 strWidth  = ls_uiGlyphStringLen(c, font, slider->text);
                    s32 xOff      = (w - strWidth) / 2;
                    s32 yOff      = (h - strHeight) + 3; //TODO: @FontDescent
                    
                    Color textColor = c->textColor;
                    textColor = SetAlpha(textColor, opacity);
                    
                    ls_uiGlyphString(c, font, xPos+xOff, yPos + yOff, threadRect, scissor,
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
                        
                        s32 strWidth = ls_uiGlyphStringLen(c, font, sub->name);
                        s32 xOff = (subW - strWidth) / 2;
                        s32 yOff = 5;
                        
                        Color subColor = sub->isHot ? c->highliteColor : bkgColor;
                        ls_uiBorderedRect(c, subX, subY, subW, subH, threadRect, scissor, subColor, c->widgetColor);
                        ls_uiGlyphString(c, font, subX+xOff, subY+yOff, threadRect, scissor, sub->name, textColor);
                        
                        if(menu->isOpen && (menu->openIdx == subIdx))
                        {
                            u32 openSubHeight = subH*sub->items.count;
                            ls_uiBorderedRect(c, subX, subY-openSubHeight, subW, openSubHeight+1,
                                              threadRect, scissor, bkgColor, c->widgetColor);
                            
                            u32 currY = subY-subH;
                            for(u32 itemIdx = 0; itemIdx < sub->items.count; itemIdx++)
                            {
                                UIMenuItem *item = sub->items + itemIdx;
                                
                                strWidth = ls_uiGlyphStringLen(c, font, item->name);
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
                                
                                ls_uiGlyphString(c, font, subX+xOff, currY+yOff, threadRect, scissor,
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
                        
                        s32 strWidth = ls_uiGlyphStringLen(c, font, item->name);
                        s32 xOff = (subW - strWidth) / 2;
                        s32 yOff = 5;
                        
                        Color itemColor = item->isHot ? c->highliteColor : bkgColor;
                        ls_uiBorderedRect(c, itemX, subY, subW, subH,
                                          threadRect, scissor, itemColor, c->widgetColor);
                        
                        ls_uiGlyphString(c, font, itemX+xOff, subY+yOff, threadRect, scissor,
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
                        
                        ls_uiGlyphString(c, font, rgbX, rgbY, threadRect, scissor,
                                         ls_utf32Constant(U"RGB"), textColor);
                        
                        
                        u32 numberBuff[32] = {};
                        utf32 tmp = { numberBuff, 0, 32 };
                        
                        rgbX += xMargin;// + ls_uiGlyphStringLen(c, font, ls_utf32Constant(U"RGB"));
                        ls_utf32FromInt_t(&tmp, picker->pickedColor.r);
                        ls_uiGlyphString(c, font, rgbX, rgbY, threadRect, scissor, tmp, textColor);
                        
                        rgbX += xMargin;// + ls_uiGlyphStringLen(c, font, tmp);
                        ls_utf32FromInt_t(&tmp, picker->pickedColor.g);
                        ls_uiGlyphString(c, font, rgbX, rgbY, threadRect, scissor, tmp, textColor);
                        
                        rgbX += xMargin;// + ls_uiGlyphStringLen(c, font, tmp);
                        ls_utf32FromInt_t(&tmp, picker->pickedColor.b);
                        ls_uiGlyphString(c, font, rgbX, rgbY, threadRect, scissor, tmp, textColor);
                        
                        //NOTE: Add HSV Label
                        s32 hsvX = picker->centerX - picker->radius;
                        s32 hsvY = picker->centerY - picker->radius - 2*yMargin;
                        ls_uiGlyphString(c, font, hsvX, hsvY, threadRect, scissor,
                                         ls_utf32Constant(U"HSV"), textColor);
                        
                        hsvX += xMargin;// + ls_uiGlyphStringLen(c, font, ls_utf32Constant(U"HSV"));
                        ls_utf32FromInt_t(&tmp, hue);
                        ls_uiGlyphString(c, font, hsvX, hsvY, threadRect, scissor, tmp, textColor);
                        
                        hsvX += xMargin;// + ls_uiGlyphStringLen(c, font, tmp);
                        ls_utf32FromInt_t(&tmp, saturation*100);
                        ls_uiGlyphString(c, font, hsvX, hsvY, threadRect, scissor, tmp, textColor);
                        
                        hsvX += xMargin;// + ls_uiGlyphStringLen(c, font, tmp);
                        ls_utf32FromInt_t(&tmp, picker->value*100);
                        ls_uiGlyphString(c, font, hsvX, hsvY, threadRect, scissor, tmp, textColor);
                        
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


#endif //LS_UI_IMPLEMENTATION
