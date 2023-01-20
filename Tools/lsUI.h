#ifndef LS_UI_H
#define LS_UI_H

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



#define RGBA(r,g,b,a)  (u32)((a<<24)|(r<<16)|(g<<8)|b)
#define RGB(r,g,b)     (u32)((0xFF<<24)|(r<<16)|(g<<8)|b)
#define RGBg(v)        (u32)((0xFF<<24)|(v<<16)|(v<<8)|v)
#define SetAlpha(v, a) (u32)((v & 0x00FFFFFF) | (((u32)a)<<24))
#define GetAlpha(v)    ( u8)(((v) & 0xFF000000) >> 24)

const     u32 THREAD_COUNT       = 2;
constexpr u32 RENDER_GROUP_COUNT = THREAD_COUNT == 0 ? 1 : THREAD_COUNT;

typedef u32 Color;

union UIRect
{
    struct { s32 minX, minY, maxX, maxY; };
    struct { s32 x,    y,    w,    h; };
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

struct UIContext;

enum UIButtonStyle { UIBUTTON_TEXT, UIBUTTON_TEXT_NOBORDER, UIBUTTON_NO_TEXT, UIBUTTON_BMP };

typedef b32(*ButtonProc)(UIContext *c, void *userData);
struct UIButton
{
    UIButtonStyle style;
    
    utf32 name;
    u8 *bmpData;
    s32 bmpW, bmpH;
    
    b32 isHot;
    b32 isHeld;
    
    ButtonProc onClick;
    ButtonProc onHold;
    
    void *data; //TODO: Separate onClick / onHold user data
};


typedef b32(*TextBoxProc)(UIContext *, void *userData);
struct UITextBox
{
    utf32 text;
    u32 maxLen;
    
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
    
    //TODO: @Deprecated this
    s32 viewEndIdx;
    
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
    "UI_RC_LISTBOX",
    "UI_RC_LISTBOX_ARR",
    "UI_RC_SLIDER",
    "UI_RC_RECT",
    "UI_RC_MENU",
    "UI_RC_SCROLLBAR",
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
    UI_RC_LISTBOX,
    UI_RC_LISTBOX_ARR,
    UI_RC_SLIDER,
    UI_RC_RECT,
    UI_RC_SEPARATOR,
    UI_RC_MENU,
    UI_RC_BACKGROUND,
    UI_RC_SCROLLBAR,
};

//TODO: RenderCommand is getting big.
struct RenderCommand
{
    RenderCommandType  type;
    
    //NOTE: The render coord. after threaded dispatch
    UIRect rect;
    
    //TODO: Can we make this happen at compile time and just globally assign it to each
    //      Render Thread by ThreadID?
    //      Maybe just match the ThreadID to the threadRect index in an array?
    UIRect threadRect;
    
    //TODO: Should I pass the strings as pointers as well?
    union
    {
        UITextBox *textBox;
        utf32      label32;
        utf8       label8;
        UIButton  *button;
        UIListBox *listBox;
        UISlider  *slider;
        UIMenu    *menu;
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
    
    //NOTE: Scissor for the current command.
    UIRect scissor;
};


const u32 UI_Z_LAYERS = 3;

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
    u8 *drawBuffer;
    u32 width;
    u32 height;
    
    UIFont *fonts;
    u32 numFonts;
    
    UIFont *currFont;
    
    Color backgroundColor;
    Color borderColor;
    
    Color highliteColor;
    Color pressedColor;
    
    Color widgetColor;
    Color textColor;
    Color invWidgetColor;
    Color invTextColor;
    
    UIRect scissor;
    
    UIScrollableRegion scroll;
    
    u64 *currentFocus;
    u64 *lastFocus;
    b32 focusWasSetThisFrame;
    
    b32 nextFrameFocusChange;
    u64 *nextFrameFocus;
    
    u64 *mouseCapture;
    
    RenderGroup renderGroups[RENDER_GROUP_COUNT];
    
    HDC  WindowDC;
    HDC  BackBufferDC;
    
    CONDITION_VARIABLE startRender;
    CRITICAL_SECTION crit;
    
    //IMPORTANT NOTE:
    // As of right now lsUI DEPENDS on Input.
    // I don't know if this is the right choice. I guess I'll discover it.
    Input UserInput = {};
    
    
    RenderCallback renderFunc = NULL;
    u32 dt;
    RegionTimer frameTime = {};
    
    HWND Window;
    
    s32 windowPosX, windowPosY;
    s32 windowWidth = 1280, windowHeight = 860;
    b32 isDragging = FALSE;
    s32 prevMousePosX = 0, prevMousePosY = 0;
    
    b32 hasReceivedInput = FALSE;
    
    onDestroyFunc onDestroy = NULL;
};

struct ___threadCtx
{
    UIContext *c;
    u64 ThreadID;
};



HWND       ls_uiCreateWindow(HINSTANCE MainInstance, UIContext *c);
HWND       ls_uiCreateWindow(UIContext *c);
UIContext *ls_uiInitDefaultContext(u8 *drawBuffer, u32 width, u32 height, RenderCallback cb);

void       ls_uiFrameBegin(UIContext *c);
void       ls_uiFrameEnd(UIContext *c, u64 frameTimeTargetMs);

void       ls_uiAddOnDestroyCallback(UIContext *c, onDestroyFunc f);

void       ls_uiPushRenderCommand(UIContext *c, RenderCommand command, s32 zLayer);
void       ls_uiStartScrollableRegion(UIContext *c, UIScrollableRegion *scroll);
void       ls_uiEndScrollableRegion(UIContext *c);

void       ls_uiFocusChange(UIContext *c, u64 *focus);
b32        ls_uiInFocus(UIContext *c, void *p);
b32        ls_uiHasCapture(UIContext *c, void *p);
void       ls_uiSelectFontByPixelHeight(UIContext *cxt, u32 pixelHeight);
s32        ls_uiSelectFontByFontSize(UIContext *cxt, UIFontSize fontSize);

Color      ls_uiDarkenRGB(Color c, u32 factor);
Color      ls_uiLightenRGB(Color c, u32 factor);
Color      ls_uiAlphaBlend(Color source, Color dest, u8 alpha);
Color      ls_uiAlphaBlend(Color source, Color dest);
Color      ls_uiRGBAtoARGB(Color c);

void       ls_uiRect(UIContext *c, s32 x, s32 y, s32 w, s32 h, Color bkgColor, Color borderColor, s32 zLayer);
void       ls_uiHSeparator(UIContext *c, s32 x, s32 y, s32 width, s32 lineWidth, Color lineColor, s32 zLayer);

UIButton   ls_uiButtonInit(UIButtonStyle s, ButtonProc onClick, ButtonProc onHold, void *data);
UIButton   ls_uiButtonInit(UIButtonStyle s, utf32 text, ButtonProc onClick, ButtonProc onHold, void *data);
UIButton   ls_uiButtonInit(UIButtonStyle s, const char32_t *text, ButtonProc onClick, ButtonProc onHold, void *data);
void       ls_uiButtonInit(UIButton *b, UIButtonStyle s, utf32 t, ButtonProc onClick, ButtonProc onHold, void *data);
void       ls_uiButtonInit(UIButton *, UIButtonStyle, const char32_t *t, ButtonProc onClick, ButtonProc onHold, void *data);
b32        ls_uiButton(UIContext *c, UIButton *button, s32 xPos, s32 yPos, s32 w, s32 h, s32 zLayer);

void       ls_uiLabel(UIContext *c, utf32 label, s32 xPos, s32 yPos, Color textColor, s32 zLayer);
void       ls_uiLabel(UIContext *c, const char32_t *label, s32 xPos, s32 yPos, Color textColor, s32 zLayer);
void       ls_uiLabel(UIContext *c, utf8 label, s32 xPos, s32 yPos, Color textColor, s32 zLayer);
void       ls_uiLabel(UIContext *c, const u8 *label, s32 xPos, s32 yPos, Color textColor, s32 zLayer);
UIRect     ls_uiLabelLayout(UIContext *c, utf32 label, UIRect layoutRegion, Color textColor, s32 zLayer);
UIRect     ls_uiLabelLayout(UIContext *c, const char32_t *label, UIRect layoutRegion, Color textColor, s32 zLayer);

void       ls_uiLabel(UIContext *c, utf32 label, s32 xPos, s32 yPos, s32 zLayer);
void       ls_uiLabel(UIContext *c, const char32_t *label, s32 xPos, s32 yPos, s32 zLayer);
void       ls_uiLabel(UIContext *c, utf8 label, s32 xPos, s32 yPos, s32 zLayer);
void       ls_uiLabel(UIContext *c, const u8 *label, s32 xPos, s32 yPos, s32 zLayer);
UIRect     ls_uiLabelLayout(UIContext *c, utf32 label, UIRect layoutRegion, s32 zLayer);
UIRect     ls_uiLabelLayout(UIContext *c, const char32_t *label, UIRect layoutRegion, s32 zLayer);

void       ls_uiTextBoxClear(UIContext *c, UITextBox *box);
void       ls_uiTextBoxSet(UIContext *c, UITextBox *box, const char32_t *s);
void       ls_uiTextBoxSet(UIContext *c, UITextBox *box, utf32 s);
b32        ls_uiTextBox(UIContext *c, UITextBox *box, s32 xPos, s32 yPos, s32 w, s32 h);

u32        ls_uiListBoxAddEntry(UIContext *c, UIListBox *list, char *s);
u32        ls_uiListBoxAddEntry(UIContext *c, UIListBox *list, utf32 s);
void       ls_uiListBoxRemoveEntry(UIContext *c, UIListBox *list, u32 index);
b32        ls_uiListBox(UIContext *c, UIListBox *list, s32 xPos, s32 yPos, s32 w, s32 h, u32 zLayer);

UISlider   ls_uiSliderInit(char32_t *name, s32 maxVal, s32 minVal, f64 currPos, SliderStyle s, Color l, Color r);
void       ls_uiSliderChangeValueBy(UIContext *c, UISlider *f, s32 valueDiff);
s32        ls_uiSliderGetValue(UIContext *c, UISlider *f);
b32        ls_uiSlider(UIContext *c, UISlider *slider, s32 xPos, s32 yPos, s32 w, s32 h);

UIButton   ls_uiMenuButton(ButtonProc onClick, u8 *bitmapData, s32 width, s32 height);
void       ls_uiMenuAddSub(UIContext *c, UIMenu *menu, UISubMenu sub);
void       ls_uiMenuAddSub(UIContext *c, UIMenu *menu, const char32_t *name);
void       ls_uiMenuAddItem(UIContext *c, UIMenu *menu, const char32_t *name, ButtonProc onClick, void *userData);
void       ls_uiSubMenuAddItem(UIContext *c, UISubMenu *sub, const char32_t *name, ButtonProc onClick, void *userData);
void       ls_uiSubMenuAddItem(UIContext *c, UIMenu *menu, u32 subIdx, const char32_t *name, ButtonProc onClick, void *data);
b32        ls_uiMenu(UIContext *c, UIMenu *menu, s32 x, s32 y, s32 w, s32 h, s32 zLayer);

void       ls_uiRender(UIContext *c);

#endif


#ifdef LS_UI_IMPLEMENTATION


#if _DEBUG
static u64 __debug_frameNumber = 0;
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
            BitmapInfo.bmiHeader.biWidth = c->windowWidth;
            BitmapInfo.bmiHeader.biHeight = c->windowHeight;
            BitmapInfo.bmiHeader.biPlanes = 1;
            BitmapInfo.bmiHeader.biBitCount = 32;
            BitmapInfo.bmiHeader.biCompression = BI_RGB;
            
            StretchDIBits(c->BackBufferDC, 0, 0, c->windowWidth, c->windowHeight,
                          0, 0, c->windowWidth, c->windowHeight,
                          c->drawBuffer, &BitmapInfo, DIB_RGB_COLORS, SRCCOPY);
            
            Result = BitBlt(c->WindowDC, r.left, r.top, r.right, r.bottom,
                            c->BackBufferDC, 0, 0, SRCCOPY);
            
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
                case 'V':        KeySetAndRepeat(keyMap::V, rep);         break;
                case 'G':        KeySetAndRepeat(keyMap::G, rep);         break;
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
                case 'V':        KeyUnset(keyMap::V);         break;
                case 'G':        KeyUnset(keyMap::G);         break;
                case 'Y':        KeyUnset(keyMap::Y);         break;
                case 'Z':        KeyUnset(keyMap::Z);         break;
            }
        } break;
        
        case WM_LBUTTONDOWN:
        {
            c->hasReceivedInput  = TRUE;
            Mouse->isLeftPressed = TRUE;
        } break;
        
        case WM_LBUTTONUP:
        {
            c->hasReceivedInput  = TRUE;
            Mouse->isLeftPressed = FALSE;
        } break;
        
        case WM_RBUTTONDOWN:
        { 
            c->hasReceivedInput   = TRUE;
            Mouse->isRightPressed = TRUE; 
        } break;
        
        case WM_RBUTTONUP:
        { 
            c->hasReceivedInput   = TRUE; 
            Mouse->isRightPressed = FALSE; 
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
            Mouse->currPosY = c->windowHeight - currMouseClient.y;
            
            c->hasReceivedInput = TRUE;
            
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
    
    u32 prop = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
    
    HCURSOR cursor = LoadCursorA(NULL, IDC_ARROW);
    
    WNDCLASSA WindowClass = { 0 };
    WindowClass.style = prop;
    WindowClass.lpfnWndProc = ls_uiWindowProc;
    WindowClass.hInstance = MainInstance;
    WindowClass.lpszClassName = name;
    WindowClass.hCursor = cursor;
    
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
    
    int spaceX = (screenWidth - c->windowWidth) / 2;
    int spaceY = ((screenHeight - c->windowHeight) / 2);// - taskbarHeight;
    if(spaceX < 0) { spaceX = 0; }
    if(spaceY < 0) { spaceY = 0; }
    
    //NOTE: We repliacate windowName in both the windowClass name and the actual window name, to avoid conflict
    //      when creating multiple windows under the same process.
    HWND WindowHandle;
    if ((WindowHandle = CreateWindowExA(0, windowName,
                                        windowName, style,
                                        spaceX, spaceY, //CW_USEDEFAULT, CW_USEDEFAULT,
                                        c->windowWidth, c->windowHeight,
                                        0, 0, MainInstance, c)) == nullptr)
    {
        DWORD Error = GetLastError();
        ls_printf("When Retrieving a WindowHandle in Win32_SetupScreen got error: %d", Error);
    }
    
    
    BITMAPINFO BackBufferInfo = {};
    BackBufferInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    BackBufferInfo.bmiHeader.biWidth = c->windowWidth;
    BackBufferInfo.bmiHeader.biHeight = c->windowHeight;
    BackBufferInfo.bmiHeader.biPlanes = 1;
    BackBufferInfo.bmiHeader.biBitCount = 32;
    BackBufferInfo.bmiHeader.biCompression = BI_RGB;
    
    c->WindowDC           = GetDC(WindowHandle);
    c->BackBufferDC       = CreateCompatibleDC(c->WindowDC);
    HBITMAP DibSection = CreateDIBSection(c->BackBufferDC, &BackBufferInfo,
                                          DIB_RGB_COLORS, (void **)&(c->drawBuffer), NULL, 0);
    SelectObject(c->BackBufferDC, DibSection);
    
    c->windowPosX = (s16)spaceX;
    c->windowPosY = (s16)spaceY; //NOTE:TODO: Hardcoded!!
    
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
    InvalidateRect(c->Window, NULL, TRUE);
}


UIContext *ls_uiInitDefaultContext(u8 *drawBuffer, u32 width, u32 height, RenderCallback cb = __ui_default_windows_render_callback)
{
    UIContext *uiContext       = (UIContext *)ls_alloc(sizeof(UIContext));
    uiContext->drawBuffer      = drawBuffer;
    
    //NOTETODO Redundant? Maybe not?
    uiContext->width           = width;
    uiContext->height          = height;
    uiContext->windowWidth     = width;
    uiContext->windowHeight    = height;
    uiContext->renderFunc      = cb;
    uiContext->backgroundColor = RGBg(0x38);
    uiContext->highliteColor   = RGBg(0x65);
    uiContext->pressedColor    = RGBg(0x75);
    uiContext->widgetColor     = RGBg(0x45);
    uiContext->borderColor     = RGBg(0x22);
    uiContext->textColor       = RGBg(0xCC);
    uiContext->invWidgetColor  = RGBg(0xBA);
    uiContext->invTextColor    = RGBg(0x33);
    uiContext->scroll          = {};
    uiContext->scissor         = UIRect { 0, 0, s32(width), s32(height) };
    
    if(THREAD_COUNT != 0)
    {
        for(u32 i = 0; i < THREAD_COUNT; i++)
        {
            uiContext->renderGroups[i].RenderCommands[0] = ls_stackInit(sizeof(RenderCommand), 512);
            uiContext->renderGroups[i].RenderCommands[1] = ls_stackInit(sizeof(RenderCommand), 256);
            uiContext->renderGroups[i].RenderCommands[2] = ls_stackInit(sizeof(RenderCommand), 256);
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
        uiContext->renderGroups[0].RenderCommands[1] = ls_stackInit(sizeof(RenderCommand), 256);
        uiContext->renderGroups[0].RenderCommands[2] = ls_stackInit(sizeof(RenderCommand), 256);
    }
    
    
    //NOTETODO: Should this be here? Should we have another function 
    //          that specifically takes care of initialization of these global things??
    windows_initRegionTimer();
    
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
    //while (PeekMessageA(&Msg, NULL, 0, 0, PM_REMOVE))
    while (PeekMessageA(&Msg, c->Window, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&Msg);
        DispatchMessageA(&Msg);
    }
    
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
    
    MSG Msg;
    while (PeekMessageA(&Msg, c->Window, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&Msg);
        DispatchMessageA(&Msg);
    }
    
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

void ls_uiFocusChange(UIContext *cxt, u64 *focus)
{
    cxt->nextFrameFocusChange = TRUE;
    cxt->nextFrameFocus = focus;
}

b32 ls_uiInFocus(UIContext *cxt, void *p)
{
    if(cxt->currentFocus == (u64 *)p) { return TRUE; }
    return FALSE;
}

b32 ls_uiHasCapture(UIContext *cxt, void *p)
{
    if(cxt->mouseCapture == (u64 *)p) { return TRUE; }
    return FALSE;
}

//TODO: Maybe remove this??
struct __ls_RenderRect { s32 x,y,w,h; };
b32 operator==(const __ls_RenderRect& lhs, const __ls_RenderRect& rhs)
{
    if(lhs.x != rhs.x) { return FALSE; }
    if(lhs.y != rhs.y) { return FALSE; }
    if(lhs.w != rhs.w) { return FALSE; }
    if(lhs.h != rhs.h) { return FALSE; }
    
    return TRUE;
}

b32 ls_uiRectIsInside(__ls_RenderRect r1, __ls_RenderRect check)
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

b32 ls_uiPointInRect(s32 x, s32 y, __ls_RenderRect r)
{
    if((x >= r.x) && (x <= (r.x+r.w)))
    {
        if((y >= r.y) && (y <= (r.y+r.h)))
        {
            return TRUE;
        }
    }
    
    return FALSE;
}

__ls_RenderRect ls_uiQuadrantFromPoint(UIContext *c, s32 x, s32 y, u32 *idx)
{
    s32 w = (s32)(c->width / 2);
    s32 h = (s32)(c->height / 2);
    
    const __ls_RenderRect BL = {0,                   0,                    w, h};
    const __ls_RenderRect BR = {(s32)(c->width / 2), 0,                    w, h};
    const __ls_RenderRect TL = {0,                   (s32)(c->height / 2), w, h};
    const __ls_RenderRect TR = {(s32)(c->width / 2), (s32)(c->height / 2), w, h};
    
    if(ls_uiPointInRect(x, y, BL))      { *idx = 0; return BL; }
    else if(ls_uiPointInRect(x, y, BR)) { *idx = 1; return BR; }
    else if(ls_uiPointInRect(x, y, TL)) { *idx = 2; return TL; }
    else if(ls_uiPointInRect(x, y, TR)) { *idx = 3; return TR; }
    
    AssertMsg(FALSE, "Either invalid point or invalidly defined quadrant. Shouldn't be reachable.\n");
    return {};
}

void ls_uiPushRenderCommand(UIContext *c, RenderCommand command, s32 zLayer)
{
    AssertMsg(command.type != UI_RC_INVALID,  "Uninitialized Render Command?\n");
    AssertMsg(zLayer < 3, "zLayer is invalid. A function call did an oopsie\n");
    
    
    __ls_RenderRect commandRect = { command.rect.x, command.rect.y, command.rect.w, command.rect.h };
    
    command.selectedFont = c->currFont;
    command.scroll       = c->scroll;
    command.scissor      = c->scissor;
    
    switch(THREAD_COUNT)
    {
        case 0:
        case 1:
        {
            command.threadRect.minX = 0;
            command.threadRect.minY = 0;
            command.threadRect.maxX = c->windowWidth;
            command.threadRect.maxY = c->windowHeight-1;
            
            stack *renderStack = &c->renderGroups[0].RenderCommands[zLayer];
            AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 0\n");
            ls_stackPush(renderStack, (void *)&command);
            return;
        } break;
        
        case 2:
        {
            if(ls_uiRectIsInside(commandRect, {0, 0, (s32)(c->width / 2), (s32)c->height}))
            {
                command.threadRect.minX = 0;
                command.threadRect.minY = 0;
                command.threadRect.maxX = (c->width / 2)-1;
                command.threadRect.maxY = c->height-1;
                
                stack *renderStack = &c->renderGroups[0].RenderCommands[zLayer];
                AssertMsg(renderStack->used < renderStack->capacity, "Out of space in RenderGroup 0\n");
                
                ls_stackPush(renderStack, (void *)&command);
                return;
            }
            else if(ls_uiRectIsInside(commandRect, {(s32)(c->width / 2), 0, (s32)(c->width / 2), (s32)c->height}))
            {
                command.threadRect.minX = (c->width / 2);
                command.threadRect.minY = 0;
                command.threadRect.maxX = c->width;
                command.threadRect.maxY = c->height-1;
                
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
        
        default: { AssertMsg(FALSE, "Thread count not supported\n"); } return;
    }
    
    AssertMsg(FALSE, "Should never reach this case!\n");
}

void ls_uiStartScrollableRegion(UIContext *c, UIScrollableRegion *scroll)
{ 
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
    if(!scroll->isHeld && WheelRotatedIn(scroll->x, scroll->y, scroll->w, scroll->h)) { deltaY += WheelDeltaInPixels; }
    else if(scroll->isHeld)
    {
        s32 mouseDeltaY = (c->UserInput.Mouse.prevPosY - c->UserInput.Mouse.currPosY);
        s32 scaledDeltaY = (s32)(((f64)mouseDeltaY / (f64)scroll->h)*(f64)totalHeight);
        
        deltaY = -scaledDeltaY;
    }
    
    scroll->deltaY += deltaY;
    scroll->maxX    = scroll->maxX;
    scroll->minY    = scroll->minY;
    
    if(scroll->deltaY < -totalHeight) scroll->deltaY = -totalHeight;
    if(scroll->deltaY > 0)            scroll->deltaY = 0;
    
    c->scroll    = *scroll;
    c->scissor   = UIRect { scroll->x, scroll->y, scroll->w, scroll->h-2 };
    
    RenderCommand command = { UI_RC_SCROLLBAR, scroll->x, scroll->y, scroll->w, scroll->h };
    ls_uiPushRenderCommand(c, command, 0);
}

void ls_uiEndScrollableRegion(UIContext *c)
{ 
    c->scroll  = {};
    c->scissor = UIRect { 0, 0, s32(c->width), s32(c->height) };
}

Color ls_uiDarkenRGB(Color c, u32 factor)
{
    u8 *c8 = (u8 *)&c;
    c8[0] -= factor;
    c8[1] -= factor;
    c8[2] -= factor;
    
    return c;
}

Color ls_uiLightenRGB(Color c, u32 factor)
{
    u8 *c8 = (u8 *)&c;
    c8[0] += factor;
    c8[1] += factor;
    c8[2] += factor;
    
    return c;
}

Color ls_uiAlphaBlend(Color source, Color dest, u8 alpha)
{
    u8 *c8 = (u8 *)&source;
    u8 bS = c8[0];
    u8 gS = c8[1];
    u8 rS = c8[2];
    u8 aS = alpha;
    
    c8 = (u8 *)&dest;
    u8 bD = c8[0];
    u8 gD = c8[1];
    u8 rD = c8[2];
    u8 aD = c8[3];
    
    f32 factor = (f32)(255 - aS) / 255.0f;
    f32 aMulti = (f32)aS / 255.0f;
    
    Color Result = 0;
    c8 = (u8 *)&Result;
    
    c8[0] = bS*aMulti + bD*factor;
    c8[1] = gS*aMulti + gD*factor;
    c8[2] = rS*aMulti + rD*factor;
    c8[3] = aS + aD*factor;
    
    return Result;
}

Color ls_uiAlphaBlend(Color source, Color dest)
{
    u8 Alpha = (u8)((source >> 24) & 0x000000FF);
    return ls_uiAlphaBlend(source, dest, Alpha);
}

Color ls_uiRGBAtoARGB(Color c)
{
    u8 *c8 = (u8 *)&c;
    
    u8 A = c8[0];
    
    c8[0] = c8[1];
    c8[1] = c8[2];
    c8[2] = c8[3];
    c8[3] = A;
    
    return c;
}

//NOTE Probably Deprecated??
void _ls_uiFillGSColorTable(Color c, Color baseColor, u8 darkenFactor, Color *table, u32 tableSize)
{
    table[0] = baseColor;
    
    u8 alphaCurr = (u32)ls_ceil((( 1.0f / (f32) tableSize ) * 255.0f));
    Color currColor = ls_uiAlphaBlend(c, baseColor, alphaCurr);
    table[1] = currColor;
    
    for(u32 i = 2; i < tableSize-1; i++)
    {
        table[i] = currColor;
        
        alphaCurr = (u32)ls_ceil((((f32)i / (f32) tableSize) * 255.0f));
        currColor = ls_uiAlphaBlend(c, baseColor, alphaCurr);
    }
    
    table[tableSize-1] = c;
    
    return;
}

void ls_uiFillRect(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h, 
                   UIRect threadRect, UIRect scissor, UIScrollableRegion scroll, Color col)
{
    s32 minX = threadRect.minX > scissor.x ? threadRect.minX : scissor.x;
    s32 minY = threadRect.minY > scissor.y ? threadRect.minY : scissor.y;
    s32 maxX = threadRect.maxX < scissor.x+scissor.w ? threadRect.maxX : scissor.x+scissor.w;
    s32 maxY = threadRect.maxY < scissor.y+scissor.h ? threadRect.maxY : scissor.y+scissor.h;
    
    s32 startY = yPos - scroll.deltaY;
    if(startY < minY) { h -= (minY-startY); startY = minY; }
    
    s32 startX = xPos - scroll.deltaX;
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
            
            Color c1 = ls_uiAlphaBlend(col, a1);
            Color c2 = ls_uiAlphaBlend(col, a2);
            Color c3 = ls_uiAlphaBlend(col, a3);
            Color c4 = ls_uiAlphaBlend(col, a4);
            
            __m128i color = _mm_setr_epi32(c1, c2, c3, c4);
            
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
                
                Color base = At[y*c->width + x];
                Color blendedColor = ls_uiAlphaBlend(col, base);
                At[y*c->width + x] = blendedColor;
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
                
                Color base = At[y*c->width + x];
                Color blendedColor = ls_uiAlphaBlend(col, base);
                At[y*c->width + x] = blendedColor;
            }
        }
    }
}

inline
void ls_uiBorder(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h,
                 UIRect threadRect, UIRect scissor, UIScrollableRegion scroll)
{
    Color C = c->borderColor;
    
    ls_uiFillRect(c, xPos,     yPos,     w, 1, threadRect, scissor, scroll, C);
    ls_uiFillRect(c, xPos,     yPos+h-1, w, 1, threadRect, scissor, scroll, C);
    ls_uiFillRect(c, xPos,     yPos,     1, h, threadRect, scissor, scroll, C);
    ls_uiFillRect(c, xPos+w-1, yPos,     1, h, threadRect, scissor, scroll, C);
}

inline
void ls_uiBorder(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h,
                 UIRect threadRect, UIRect scissor, UIScrollableRegion scroll, Color borderColor)
{
    Color C = borderColor;
    
    ls_uiFillRect(c, xPos,     yPos,     w, 1, threadRect, scissor, scroll, C);
    ls_uiFillRect(c, xPos,     yPos+h-1, w, 1, threadRect, scissor, scroll, C);
    ls_uiFillRect(c, xPos,     yPos,     1, h, threadRect, scissor, scroll, C);
    ls_uiFillRect(c, xPos+w-1, yPos,     1, h, threadRect, scissor, scroll, C);
}

inline
void ls_uiBorderedRect(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h,
                       UIRect threadRect, UIRect scissor, UIScrollableRegion scroll)
{
    ls_uiBorder(c, xPos, yPos, w, h, threadRect, scissor, scroll);
    ls_uiFillRect(c, xPos+1, yPos+1, w-2, h-2, threadRect, scissor, scroll, c->widgetColor);
}

inline
void ls_uiBorderedRect(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h,
                       UIRect threadRect, UIRect scissor, UIScrollableRegion scroll, Color widgetColor)
{
    ls_uiBorder(c, xPos, yPos, w, h, threadRect, scissor, scroll);
    ls_uiFillRect(c, xPos+1, yPos+1, w-2, h-2, threadRect, scissor, scroll, widgetColor);
}

inline
void ls_uiBorderedRect(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h, 
                       UIRect threadRect, UIRect scissor, UIScrollableRegion scroll,
                       Color widgetColor, Color borderColor)
{
    ls_uiBorder(c, xPos, yPos, w, h, threadRect, scissor, scroll, borderColor);
    ls_uiFillRect(c, xPos+1, yPos+1, w-2, h-2, threadRect, scissor, scroll, widgetColor);
}

inline
void ls_uiRect(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h,
               UIRect threadRect, UIRect scissor, UIScrollableRegion scroll)
{
    ls_uiFillRect(c, xPos, yPos, w, h, threadRect, scissor, scroll, c->widgetColor);
}

inline
void ls_uiRect(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h, 
               UIRect threadRect, UIRect scissor, UIScrollableRegion scroll, Color widgetColor)
{
    ls_uiFillRect(c, xPos, yPos, w, h, threadRect, scissor, scroll, widgetColor);
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
    command.borderColor = lineColor;
    
    ls_uiPushRenderCommand(c, command, zLayer);
}

void ls_uiBackground(UIContext *c)
{
    AssertMsg((c->height % 4) == 0, "Window Height not divisible by 4 (SIMD)\n");
    AssertMsg((c->width % 4) == 0, "Window Width not divisible by 4 (SIMD)\n");
    
    __m128i color = _mm_set1_epi32 ((int)c->backgroundColor);
    
    u32 numIterations = (c->width*c->height) / 4;
    for(u32 i = 0; i < numIterations; i++)
    {
        u32 idx = i*sizeof(s32)*4;
        
        __m128i *At = (__m128i *)(c->drawBuffer + idx);
        _mm_storeu_si128(At, color);
    }
}

void ls_uiBitmap(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h, UIRect threadRect, u32 *data)
{
    s32 minX = threadRect.minX;
    s32 minY = threadRect.minY;
    s32 maxX = threadRect.maxX;
    s32 maxY = threadRect.maxY;
    
    s32 startY = yPos;
    if(startY < minY) { h -= (minY-startY); startY = minY; }
    
    s32 startX = xPos;
    if(startX < minX) { w -= (minX-startX); startX = minX; }
    
    if(startX+w > maxX) { w = maxX-startX+1; }
    if(startY+h > maxY) { h = maxY-startY+1; }
    
    u32 *At = (u32 *)c->drawBuffer;
    
    for(s32 y = startY, eY = 0; y < yPos+h; y++, eY++)
    {
        AssertMsg(y <= maxY, "Should never happen. Height was precomputed\n");
        
        for(s32 x = startX, eX = 0; x < xPos+w; x++, eX++)
        {
            AssertMsg(x <= maxX, "Should never happen. Width was precomputed\n");
            
            if(x < 0 || x >= c->width)  continue;
            if(y < 0 || y >= c->height) continue;
            
            //At[y*c->width + x] = data[eY*w + eX];
            
            Color src = data[eY*w + eX];
            Color base = At[y*c->width + x];
            
            u8 sourceA = GetAlpha(src);
            
            Color blendedColor = ls_uiAlphaBlend(src, base, sourceA);
            At[y*c->width + x] = blendedColor;
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
            
            Color base = At[y*c->width + x];
            
            u8 sourceA = GetAlpha(textColor);
            u8 dstA = glyph->data[eY*glyph->width + eX];
            
            f64 sA = (f64)sourceA / 255.0;
            f64 dA = (f64)dstA / 255.0;
            
            u8 Alpha = (sA * dA) * 255;
            
            Color blendedColor = ls_uiAlphaBlend(textColor, base, Alpha);
            At[y*c->width + x] = blendedColor;
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
                             UIRect threadRect, UIRect scissor, UIScrollableRegion scroll,
                             s32 cIdx, Color textColor, Color invTextColor)
{
    AssertMsg(c, "Context is null\n");
    AssertMsg(box, "TextBox is null\n");
    AssertMsg(c->currFont, "Current Font is null\n");
    
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
            AssertMsg(code <= c->currFont->maxCodepoint, "GlyphIndex OutOfBounds\n");
            
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
            if(currXPos >= strMaxX) { i += line.len - lIdx; break; }
            
            code = line.data[lIdx];
            AssertMsg(code <= c->currFont->maxCodepoint, "GlyphIndex OutOfBounds\n");
            
            Color actualColor = textColor;
            UIGlyph *currGlyph = &c->currFont->glyph[code];
            
            //TODO: Pretty inefficient to keep redrawing the background all the time.
            if(box->isSelecting && (box->selectBeginLine <= lineIdx) && (box->selectEndLine >= lineIdx)
               && (box->selectBeginIdx <= i) && (box->selectEndIdx > i))
            { 
                actualColor = invTextColor;
                ls_uiFillRect(c, currXPos, currYPos, currGlyph->xAdv, lineHeight-vertGlyphOff, 
                              threadRect, scissor, scroll, c->invWidgetColor);
            }
            
            ls_uiGlyph(c, currXPos, currYPos+vertGlyphOff, threadRect, scissor, currGlyph, actualColor);
            
            s32 kernAdvance = 0;
            if(lIdx < line.len-1) { kernAdvance = ls_uiGetKernAdvance(c, line.data[lIdx], line.data[lIdx+1]); }
            currXPos += (currGlyph->xAdv + kernAdvance);
            
        }
        
        if(((lineIdx == box->caretLineIdx) && cIdx == line.len)) { caretX = currXPos-3; }
        
        if((cIdx != -1) && (lineIdx == box->caretLineIdx))
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
                      UIRect threadRect, UIRect scissor, UIScrollableRegion scroll, utf32 text, Color textColor)
{
    AssertMsg(c, "Context is null\n");
    AssertMsg(font, "Passed font is null\n");
    
    //TODO: If we are in a scrollable region, can we pre-skip things outside the region???
    s32 currXPos = xPos - scroll.deltaX;
    s32 currYPos = yPos - scroll.deltaY;
    for(u32 i = 0; i < text.len; i++)
    {
        u32 indexInGlyphArray = text.data[i];
        AssertMsg(indexInGlyphArray <= font->maxCodepoint, "GlyphIndex OutOfBounds\n");
        
        UIGlyph *currGlyph = &font->glyph[indexInGlyphArray];
        ls_uiGlyph(c, currXPos, currYPos, threadRect, scissor, currGlyph, textColor);
        
        s32 kernAdvance = 0;
        if(i < text.len-1) { kernAdvance = ls_uiGetKernAdvance(font, text.data[i], text.data[i+1]); }
        
        currXPos += (currGlyph->xAdv + kernAdvance);
        
        //NOTETODO VERY BAD!! need to determine
        if(indexInGlyphArray == (u32)'\n') { currYPos -= font->pixelHeight; currXPos = xPos + scroll.deltaX; }
    }
}

void ls_uiGlyphString_8(UIContext *c, UIFont *font, s32 xPos, s32 yPos,
                        UIRect threadRect, UIRect scissor, UIScrollableRegion scroll, utf8 text, Color textColor)
{
    AssertMsg(c, "Context is null\n");
    AssertMsg(font, "Passed font is null\n");
    
    //TODO: If we are in a scrollable region, can we pre-skip things outside the region???
    s32 currXPos = xPos - scroll.deltaX;
    s32 currYPos = yPos - scroll.deltaY;
    for(u32 i = 0; i < text.len; i++)
    {
        u32 indexInGlyphArray = ls_utf32CharFromUtf8(text, i);
        AssertMsg(indexInGlyphArray <= font->maxCodepoint, "GlyphIndex OutOfBounds\n");
        
        UIGlyph *currGlyph = &font->glyph[indexInGlyphArray];
        ls_uiGlyph(c, currXPos, currYPos, threadRect, scissor, currGlyph, textColor);
        
        s32 kernAdvance = 0;
        if(i < text.len-1) { kernAdvance = ls_uiGetKernAdvance(font, text.data[i], text.data[i+1]); }
        
        currXPos += (currGlyph->xAdv + kernAdvance);
        
        //NOTETODO VERY BAD!! need to determine
        if(indexInGlyphArray == (u32)'\n') { currYPos -= font->pixelHeight; currXPos = xPos + scroll.deltaX; }
    }
}

//TODO: Should I always pass a layout, and maybe only keep an helper when I want no layout, so the layout region
//      would just be the entire window???
void ls_uiGlyphStringInLayout(UIContext *c, UIFont *font, UIRect layout,
                              UIRect threadRect, UIRect scissor, UIScrollableRegion scroll,
                              utf32 text, Color textColor)
{
    AssertMsg(c, "Context is null\n");
    AssertMsg(font, "Passed font is null\n");
    
    //TODO: If we are in a scrollable region, can we pre-skip things outside the region???
    s32 currXPos = layout.x - scroll.deltaX;
    s32 currYPos = layout.y - scroll.deltaY;
    for(u32 i = 0; i < text.len; i++)
    {
        u32 indexInGlyphArray = text.data[i];
        AssertMsg(indexInGlyphArray <= font->maxCodepoint, "GlyphIndex OutOfBounds\n");
        
        if(indexInGlyphArray == (u32)'\n') {
            currYPos -= font->pixelHeight;
            currXPos = layout.x - scroll.deltaX;
            continue;
        }
        
        UIGlyph *currGlyph = &font->glyph[indexInGlyphArray];
        ls_uiGlyph(c, currXPos, currYPos, threadRect, scissor, currGlyph, textColor);
        
        s32 kernAdvance = 0;
        if(i < text.len-1) { kernAdvance = ls_uiGetKernAdvance(font, text.data[i], text.data[i+1]); }
        
        s32 newAdvance = currGlyph->xAdv + kernAdvance;
        if((currXPos + newAdvance) > (layout.x + layout.w))
        { 
            currYPos -= font->pixelHeight; 
            currXPos = layout.x - scroll.deltaX;
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
    AssertMsg(font, "Passed Font is null\n");
    
    s32 totalLen = 0;
    for(u32 i = 0; i < text.len; i++)
    {
        u32 indexInGlyphArray = text.data[i];
        AssertMsg(indexInGlyphArray <= font->maxCodepoint, "GlyphIndex OutOfBounds\n");
        
        UIGlyph *currGlyph = &font->glyph[indexInGlyphArray];
        
        s32 kernAdvance = 0;
        if(i < text.len-1) { kernAdvance = ls_uiGetKernAdvance(font, text.data[i], text.data[i+1]); }
        
        totalLen += (currGlyph->xAdv + kernAdvance);
    }
    
    return totalLen;
}

s32 ls_uiGlyphStringLen_8(UIContext *c, UIFont *font, utf8 text)
{
    AssertMsg(c, "Context is null\n");
    AssertMsg(font, "Passed Font is null\n");
    
    s32 totalLen = 0;
    for(u32 i = 0; i < text.len; i++)
    {
        u32 indexInGlyphArray = ls_utf32CharFromUtf8(text, i);
        AssertMsg(indexInGlyphArray <= font->maxCodepoint, "GlyphIndex OutOfBounds\n");
        
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
    AssertMsg(font, "Current Font is null\n");
    
    s32 totalLen = 0;
    for(s32 i = text.len-1; i > 0; i--)
    {
        u32 indexInGlyphArray = text.data[i];
        AssertMsg(indexInGlyphArray <= font->maxCodepoint, "GlyphIndex OutOfBounds\n");
        
        UIGlyph *currGlyph = &font->glyph[indexInGlyphArray];
        
        s32 kernAdvance = 0;
        if(i > 0) { kernAdvance = ls_uiGetKernAdvance(font, text.data[i-1], text.data[i]); }
        
        totalLen += (currGlyph->xAdv + kernAdvance);
        if(totalLen >= maxLen) { return i; }
    }
    
    return 0;
}

UIRect ls_uiGlyphStringLayout(UIContext *c, UIFont *font, utf32 text, s32 maxXOff)
{
    //TODO: Only one quirk remains, the y offset is determined based on the font height of the current element, 
    //      which obviously generates too large gaps when the font becomes smaller from one call to the 
    //      other and too small gaps when the font becomes bigger. The solution to this is to consider 
    //      the y Position when rendering a glyph the top left of the glyph (rather than the bottom left), 
    //      and subtract the font height to obtain the baseline. This way the y offset in layouting will 
    //      correctly move the y coordinate of the next line below the current line, regardless of font size.
    AssertMsg(c, "Context is null\n");
    AssertMsg(font, "Passed Font is null\n");
    
    s32 largestXOff = 0;
    s32 currXOff = 0;
    s32 currYOff = 0;
    for(u32 i = 0; i < text.len; i++)
    {
        u32 indexInGlyphArray = text.data[i];
        AssertMsg(indexInGlyphArray <= font->maxCodepoint, "GlyphIndex OutOfBounds\n");
        
        if(indexInGlyphArray == (u32)'\n') { currXOff = 0; currYOff -= font->pixelHeight; continue; }
        
        UIGlyph *currGlyph = &font->glyph[indexInGlyphArray];
        
        s32 kernAdvance = 0;
        if(i < text.len-1) { kernAdvance = ls_uiGetKernAdvance(font, text.data[i], text.data[i+1]); }
        
        s32 newAdvance = currGlyph->xAdv + kernAdvance;
        if(currXOff + newAdvance > maxXOff) { currXOff = 0; currYOff -= font->pixelHeight; continue; }
        
        currXOff += newAdvance;
        if(largestXOff < currXOff) { largestXOff = currXOff; }
    }
    
    s32 firstLineRemoved = currYOff - font->pixelHeight;
    
    UIRect finalLayout = { currXOff, -currYOff, largestXOff, -firstLineRemoved};
    
    return finalLayout;
}

void ls_uiSelectFontByPixelHeight(UIContext *c, u32 pixelHeight)
{
    AssertMsg(c->fonts, "No fonts were loaded\n");
    
    //TODO: Hardcoded
    b32 found = FALSE;
    for(u32 i = 0; i < 4; i++)
    { if(c->fonts[i].pixelHeight == pixelHeight) { found = TRUE; c->currFont = &c->fonts[i]; } }
    
    AssertMsg(found, "Asked pixelHeight not available\n");
}

inline
s32 ls_uiSelectFontByFontSize(UIContext *c, UIFontSize fontSize)
{ 
    AssertMsg(c->fonts, "No fonts were loaded\n");
    c->currFont = &c->fonts[fontSize]; return c->currFont->pixelHeight;
}

UIButton ls_uiButtonInit(UIButtonStyle s, ButtonProc onClick, ButtonProc onHold = NULL, void *userData = NULL)
{
    UIButton Result = {s, {}, 0, 0, 0, FALSE, FALSE, onClick, onHold, userData};
    return Result;
}

UIButton ls_uiButtonInit(UIButtonStyle s, const char32_t *text, ButtonProc onClick,
                         ButtonProc onHold = NULL, void *userData = NULL)
{
    UIButton Result = {s, ls_utf32FromUTF32(text), 0, 0, 0, FALSE, FALSE, onClick, onHold, userData};
    return Result;
}

UIButton ls_uiButtonInit(UIButtonStyle s, utf32 text, ButtonProc onClick,
                         ButtonProc onHold = NULL, void *userData = NULL)
{
    UIButton Result = {s, text, 0, 0, 0, FALSE, FALSE, onClick, onHold, userData};
    return Result;
}

void ls_uiButtonInit(UIButton *b, UIButtonStyle s, utf32 text, ButtonProc onClick,
                     ButtonProc onHold = NULL, void *userData = NULL)
{
    b->style   = s;
    b->name    = text;
    b->onClick = onClick;
    b->onHold  = onHold;
    b->data    = userData;
}

void ls_uiButtonInit(UIButton *b, UIButtonStyle s, const char32_t *t, ButtonProc onClick,
                     ButtonProc onHold = NULL, void *data = NULL)
{
    b->style   = s;
    b->name    = ls_utf32FromUTF32(t);
    b->onClick = onClick;
    b->onHold  = onHold;
    b->data    = data;
}

//TODO:Button autosizing width

//TODO:Menus use buttons, but also claim Focus, which means I can't use the global focus trick to avoid input
//     handling between overlapping elements.
//     I don't think the menu should deal with things like this [It shouldn't hold the close button first,
//     and it also shouldn't use 'normal' buttons for its drop down sub-menus, so... basically @MenuIsShit
//     and I wanna redo it completely.

//TODO:Ways to force buttons to stay selected. Maybe make a versatile checkbox?
b32 ls_uiButton(UIContext *c, UIButton *button, s32 xPos, s32 yPos, s32 w, s32 h, s32 zLayer = 0)
{
    Input *UserInput = &c->UserInput;
    
    b32 inputUse = FALSE;
    
    Color bkgColor = c->widgetColor;
    
    if(button->style == UIBUTTON_TEXT_NOBORDER) { bkgColor = c->backgroundColor; }
    
    if(MouseInRect(xPos, yPos, w, h) && ls_uiHasCapture(c, 0))// && ls_uiInFocus(cxt, 0))
    { 
        button->isHot = TRUE;
        bkgColor = c->highliteColor;
        
        //b32 noCapture = ls_uiHasCapture(cxt, 0);
        
        if(button->onClick && LeftClick)// && noCapture)
        {
            inputUse |= button->onClick(c, button->data);
        }
        if(LeftHold)//  && noCapture)
        {
            button->isHeld = TRUE;
            bkgColor = c->pressedColor;
            if(button->onHold) { inputUse |= button->onHold(c, button->data); }
        }
    }
    
    RenderCommand command = { UI_RC_BUTTON, xPos, yPos, w, h };
    command.button        = button;
    command.bkgColor      = bkgColor;
    command.textColor     = c->textColor;
    ls_uiPushRenderCommand(c, command, zLayer);
    
    return inputUse;
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

//TODO: To be fixed the layout system has to use a 6 point bound, rather than just 4 points
//      So that we have a minimumX and a baseX, to know where to position the newline. @NewLayout
UIRect ls_uiLabelLayout(UIContext *c, utf32 label, UIRect layoutRegion, Color textColor, s32 zLayer = 0)
{
    AssertMsg(c, "Context pointer was null");
    AssertMsg(c->currFont, "No font was selected before sizing a label\n");
    
    if(label.len == 0) { return {}; }
    
    //TODO: We are not using the layoutRegion.h value 
    //      (Which is actually inverted from the meaning in the struct 
    //       because text grows downward and Y grows upward)
    //      So BE CAREFUL!!! the Y value in layoutRegion.h /layoutRegion.maxY is actually the MINIMUM Y!!!
    s32 maxXOff = layoutRegion.w - layoutRegion.x;
    UIRect deltaPos = ls_uiGlyphStringLayout(c, c->currFont, label, maxXOff);
    
    RenderCommand command = { UI_RC_LABEL_LAYOUT, layoutRegion.x, layoutRegion.y, maxXOff, deltaPos.h };
    command.label32 = label;
    command.textColor = textColor;
    ls_uiPushRenderCommand(c, command, zLayer);
    
    UIRect correctedDelta = { layoutRegion.x + deltaPos.x, layoutRegion.y - deltaPos.y, deltaPos.w, deltaPos.h };
    return correctedDelta;
}

UIRect ls_uiLabelLayout(UIContext *c, const char32_t *label, UIRect layoutRegion, Color textColor, s32 zLayer = 0)
{
    utf32 lab = ls_utf32Constant(label);
    return ls_uiLabelLayout(c, lab, layoutRegion, textColor, zLayer);
}

UIRect ls_uiLabelLayout(UIContext *c, utf32 label, UIRect layoutRegion, s32 zLayer = 0)
{
    return ls_uiLabelLayout(c, label, layoutRegion, c->textColor, zLayer);
}

UIRect ls_uiLabelLayout(UIContext *c, const char32_t *label, UIRect layoutRegion, s32 zLayer = 0)
{
    utf32 lab = ls_utf32Constant(label);
    return ls_uiLabelLayout(c, lab, layoutRegion, c->textColor, zLayer);
}

void ls_uiTextBoxClear(UIContext *c, UITextBox *box)
{
    AssertMsg(c, "Context pointer was null");
    
    ls_utf32Clear(&box->text);
    
    box->caretIndex     = 0;
    box->isReadonly     = FALSE;
    box->selectBeginIdx = 0;
    box->selectEndIdx   = 0;
    box->isSelecting    = FALSE;
    box->viewBeginIdx   = 0;
    box->viewEndIdx     = 0;
}

void ls_uiTextBoxSet(UIContext *c, UITextBox *box, const char32_t *s)
{
    ls_utf32FromUTF32_t(&box->text, s);
    box->viewEndIdx = box->text.len;
}

void ls_uiTextBoxSet(UIContext *c, UITextBox *box, utf32 s)
{
    ls_utf32Set(&box->text, s);
    box->viewEndIdx = box->text.len;
}

//TODO: Text Alignment
//TODO: Apron when moving Left/Right
//TODO: When moving left/right special characters (like newlines) should be skipped.
//TODO: In small boxes the newline fucks up rendering of the caret
b32 ls_uiTextBox(UIContext *c, UITextBox *box, s32 xPos, s32 yPos, s32 w, s32 h)
{
    Input *UserInput = &c->UserInput;
    b32 inputUse = FALSE;
    
    if(LeftClickIn(xPos, yPos, w, h) && (box->isReadonly == FALSE) && ls_uiHasCapture(c, 0)) {
        c->currentFocus = (u64 *)box;
        c->focusWasSetThisFrame = TRUE;
        box->isCaretOn = TRUE; 
    }
    
    const s32 horzOff   = 8;
    const s32 viewAddWidth    = w - 2*horzOff;
    
    auto setIndices = [c, box, viewAddWidth](s32 index) -> u32 {
        
        if(index <= 0) { 
            box->viewBeginIdx = 0; 
            box->viewEndIdx = 0;
            
            //TODONOTE: Very wrong.
            if(box->text.data[0] == (char32_t)'\n') return 1;
            return 0;
        }
        
        u32 beginOffset    = ls_utf32RightFind(box->text, index, (char32_t)'\n');
        
        s32 realOffset = beginOffset+1;
        if(beginOffset == -1) { realOffset = 0; }
        
        s32 lineLength     = index-realOffset;
        
        utf32 currLine    = { box->text.data + realOffset, lineLength, lineLength };
        u32 maxBeginIndex = ls_uiGlyphStringFit(c, c->currFont, currLine, viewAddWidth);
        
        box->viewBeginIdx = maxBeginIndex;
        
        //NOTE:TODO: As of right now viewEndIdx does absolutely nothing.
        box->viewEndIdx   = 0xFEFEFE; // = lineLength; //TODONOTE Strange that an idx == lenght.
        
        return realOffset;
    };
    
    auto handleSelection = [UserInput, box](s32 direction) {
        
        AssertMsg((direction == -1) || (direction == 1) || (direction == -2) || (direction == 2), 
                  "Invalid direction passed to handleSelection\n");
        
        if(KeyHeld(keyMap::Shift))
        {
            if(!box->isSelecting) 
            { 
                box->isSelecting = TRUE;
                
                switch(direction)
                {
                    case -1:
                    case  1:
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
                    
                    
                    case -2:
                    {
                        if(box->caretIndex == 0) { box->isSelecting = FALSE; break; }
                        
                        box->selectBeginLine = 0;
                        box->selectEndLine   = box->caretLineIdx;
                        box->selectBeginIdx  = 0;
                        box->selectEndIdx    = box->caretIndex;
                    } break;
                    
                    case  2:
                    {
                        if(box->caretIndex >= box->text.len) { box->isSelecting = FALSE; break; }
                        
                        box->selectBeginLine = box->caretLineIdx;
                        box->selectEndLine   = box->lineCount;
                        box->selectBeginIdx  = box->caretIndex;
                        box->selectEndIdx    = box->text.len;
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
                            if(box->text.data[box->caretIndex] == (char32_t)'\n') { box->selectBeginLine += direction;}
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
        if(HasPrintableKey() && (GetPrintableKey() == (char32_t)'\n') && (box->isSingleLine == TRUE))
        { ls_uiFocusChange(c, 0); }
        
        //NOTE: Draw characters. (box->maxLen == 0 means there's no max len)
        else if(HasPrintableKey() && (box->text.len < box->maxLen || box->maxLen == 0))
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
            
            setIndices(box->caretIndex);
            
            inputUse = TRUE;
        }
        
        else if(KeyPressOrRepeat(keyMap::Backspace) && box->text.len > 0 && box->caretIndex >= 0) 
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
        
        else if(KeyPressOrRepeat(keyMap::Delete) && box->text.len > 0 && box->caretIndex <= box->text.len)
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
                
                if((box->text.len < box->viewEndIdx) && !isCR) { box->viewEndIdx -= 1; }
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
            
            s32 newLineBeginIdx = -1;
            
            /* NOTETODO: Why did I even need this?
            if(box->text.data[box->caretIndex] == (char32_t)'\n')
            { newLineBeginIdx = setIndices(box->caretIndex-1); }
            else
            { newLineBeginIdx = setIndices(box->caretIndex); }
            */
            newLineBeginIdx = setIndices(box->caretIndex);
            
            AssertMsg(newLineBeginIdx != -1, "Fucked Up line index in LArrow\n");
            
            if(newLineBeginIdx < box->currLineBeginIdx)
            {
                box->caretLineIdx    -= 1;
                box->currLineBeginIdx = newLineBeginIdx;
            }
            
        }
        
        else if(KeyPressOrRepeat(keyMap::RArrow) && box->caretIndex < box->text.len)
        { 
            handleSelection(1);
            
            box->isCaretOn      = TRUE;
            box->dtCaret        = 0;
            box->caretIndex    += 1;
            
            s32 newLineBeginIdx = -1;
            
            /* NOTETODO: Why did I even need this?
            if(box->text.data[box->caretIndex] == (char32_t)'\n')
            { newLineBeginIdx = setIndices(box->caretIndex-1); }
            else
            { newLineBeginIdx = setIndices(box->caretIndex); }
            */
            newLineBeginIdx = setIndices(box->caretIndex);
            
            AssertMsg(newLineBeginIdx != -1, "Fucked Up line index in RArrow");
            
            if(newLineBeginIdx > box->currLineBeginIdx)
            {
                box->caretLineIdx    += 1;
                box->currLineBeginIdx = newLineBeginIdx;
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
            box->caretLineIdx = box->lineCount;
            
            box->currLineBeginIdx = setIndices(box->caretIndex);
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
        
        else if(KeyHeld(keyMap::Control) && KeyPress(keyMap::V))
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
            box->currLineBeginIdx = setIndices(box->caretIndex);
            
            inputUse = TRUE;
        }
        
        //NOTE: GOTO label to skip here.
        goto_skip_to_post_input:
        
        box->dtCaret += c->dt;
        if(box->dtCaret >= 400) { box->dtCaret = 0; box->isCaretOn = !box->isCaretOn; }
        
        
        if(box->postInput && inputUse)
        { box->postInput(c, box->data); }
    }
    
    RenderCommand command = {UI_RC_TEXTBOX, xPos, yPos, w, h, 0, 0, 0, 0, box, c->widgetColor, c->textColor};
    ls_uiPushRenderCommand(c, command, 0);
    
    return inputUse;
}

void ls_uiDrawArrow(UIContext *cxt, s32 x, s32 yPos, s32 w, s32 h,
                    UIRect threadRect, UIRect scissor, UIScrollableRegion scroll, Color bkgColor, UIArrowSide s)
{
    //TODO: Scissor???
    s32 minX = threadRect.minX;
    s32 minY = threadRect.minY;
    s32 maxX = threadRect.maxX;
    s32 maxY = threadRect.maxY;
    
    u32 *At = (u32 *)cxt->drawBuffer;
    
    s32 xPos = x-1;
    
    ls_uiBorderedRect(cxt, xPos, yPos, w, h, threadRect, scissor, scroll, bkgColor);
    
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
        if(xBase  < minX) { xEnd -= (minX - xBase); xBase = minX; }
        
        for(s32 y = yStart; y >= yEnd; y--)
        {
            if(y < minY) { break; }
            
            for(s32 x = xBase; x < xEnd; x++)
            {
                if(x >= maxX) { break; }
                
                if(x < 0 || x >= cxt->width)  continue;
                if(y < 0 || y >= cxt->height) continue;
                
                At[y*cxt->width + x] = cxt->borderColor;
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
        if(xBase  < minX) { xEnd -= (minX - xBase); xBase = minX; }
        
        for(s32 y = yStart1; y >= yEnd1; y--)
        {
            if(y < minY) { break; }
            
            for(s32 x = xBase; x < xEnd; x++)
            {
                if(x >= maxX) { break; }
                
                if(x < 0 || x >= cxt->width)  continue;
                if(y < 0 || y >= cxt->height) continue;
                
                At[y*cxt->width + x] = RGBg(0x00);
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
                
                if(x < 0 || x >= cxt->width)  continue;
                if(y < 0 || y >= cxt->height) continue;
                
                At[y*cxt->width + x] = RGBg(0x00);
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
        if(xBase  < minX) { xEnd -= (minX - xBase); xBase = minX; }
        
        for(s32 y = yStart1; y >= yEnd1; y--)
        {
            if(y < minY) { break; }
            
            for(s32 x = xBase; x < xEnd; x++)
            {
                if(x >= maxX) { break; }
                
                if(x < 0 || x >= cxt->width)  continue;
                if(y < 0 || y >= cxt->height) continue;
                
                At[y*cxt->width + x] = RGBg(0x00);
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
                
                if(x < 0 || x >= cxt->width)  continue;
                if(y < 0 || y >= cxt->height) continue;
                
                At[y*cxt->width + x] = RGBg(0x00);
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

//TODO I really think ListBox shouldn't manage memory. Fix This.
inline u32 ls_uiListBoxAddEntry(UIContext *cxt, UIListBox *list, char *s)
{ 
    utf32 text = ls_utf32FromAscii(s);
    UIListBoxItem item = { text, cxt->widgetColor, cxt->textColor };
    
    return ls_arrayAppend(&list->list, item);
}

inline u32 ls_uiListBoxAddEntry(UIContext *cxt, UIListBox *list, utf32 s)
{
    UIListBoxItem item = { s, cxt->widgetColor, cxt->textColor };
    return ls_arrayAppend(&list->list, item);
}

inline void ls_uiListBoxRemoveEntry(UIContext *cxt, UIListBox *list, u32 index)
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
    
    RenderCommand list_command = { UI_RC_LISTBOX, xPos, yPos, w, h };
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
        
        slider->currPos = ls_mathClamp(slider->currPos, 1.0, 0.0);
        
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
    result.bmpW     = width;
    result.bmpH     = height;
    result.onClick  = onClick;
    return result;
}

inline void ls_uiMenuAddSub(UIContext *c, UIMenu *menu, UISubMenu sub)
{ ls_arrayAppend(&menu->subMenus, sub); }

void ls_uiMenuAddSub(UIContext *c, UIMenu *menu, const char32_t *name)
{ 
    UISubMenu newSub = {};
    newSub.name = ls_utf32FromUTF32(name);
    ls_arrayAppend(&menu->subMenus, newSub);
}

void ls_uiMenuAddItem(UIContext *c, UIMenu *menu, const char32_t *name, ButtonProc onClick, void *userData)
{
    UIMenuItem newItem = {};
    newItem.name       = ls_utf32FromUTF32(name);
    newItem.isVisible  = TRUE;
    newItem.onClick    = onClick;
    newItem.userData   = userData;
    ls_arrayAppend(&menu->items, newItem);
}

void ls_uiSubMenuAddItem(UIContext *c, UISubMenu *sub, const char32_t *name, ButtonProc onClick, void *userData)
{
    UIMenuItem newItem = {};
    
    newItem.name       = ls_utf32FromUTF32(name);
    newItem.isVisible  = TRUE;
    newItem.onClick    = onClick;
    newItem.userData   = userData;
    ls_arrayAppend(&sub->items, newItem);
}

void ls_uiSubMenuAddItem(UIContext *c, UIMenu *menu, u32 subIdx, const char32_t *name, ButtonProc onClick, void *userData)
{
    UIMenuItem newItem = {};
    
    newItem.name       = ls_utf32FromUTF32(name);
    newItem.isVisible  = TRUE;
    newItem.onClick    = onClick;
    newItem.userData   = userData;
    ls_arrayAppend(&menu->subMenus[subIdx].items, newItem);
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
    
    s32 closeX    = x + w - menu->closeWindow.bmpW - 6;
    s32 minimizeX = closeX - menu->closeWindow.bmpW - 6;
    
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
        inputUse |= ls_uiButton(c, &menu->closeWindow, closeX, y + 2, 
                                menu->closeWindow.bmpW, menu->closeWindow.bmpH, 2);
    
    if(menu->minimize.bmpData)
        inputUse |= ls_uiButton(c, &menu->minimize, minimizeX, y + 2, 
                                menu->closeWindow.bmpW, menu->closeWindow.bmpH, 2);
    
    
    RenderCommand command = { UI_RC_MENU, x, y, w, h };
    command.menu          = menu;
    command.bkgColor      = c->backgroundColor;
    command.textColor     = c->textColor;
    ls_uiPushRenderCommand(c, command, zLayer);
    
    return inputUse;
}

void ls_uiRender(UIContext *c)
{
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
            allDone &= c->renderGroups[i].isDone;
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
    //NOTE: First clear the background?
    switch(THREAD_COUNT)
    {
        case 0:
        case 1:
        {
            AssertMsg((c->height % 4) == 0, "Window Height not divisible by 4 (SIMD)\n");
            AssertMsg((c->width % 4) == 0, "Window Width not divisible by 4 (SIMD)\n");
            
            __m128i color = _mm_set1_epi32 ((int)c->backgroundColor);
            
            u32 numIterations = (c->width*c->height) / 4;
            for(u32 i = 0; i < numIterations; i++)
            {
                u32 idx = i*sizeof(s32)*4;
                
                __m128i *At = (__m128i *)(c->drawBuffer + idx);
                _mm_storeu_si128(At, color);
            }
        } break;
        
        case 2:
        {
            
            AssertMsg((c->height % 4) == 0, "Window Height not divisible by 4 (SIMD)\n");
            AssertMsg((c->width % 4) == 0, "Window Width not divisible by 4 (SIMD)\n");
            
            s32 halfWidth = c->width/2;
            s32 xStart = (halfWidth*threadID);
            __m128i color = _mm_set1_epi32 ((int)c->backgroundColor);
            
            for(s32 y = 0; y < c->height; y++)
            {
                for(s32 x = xStart; x < xStart+halfWidth; x += 4)
                {
                    u32 idx = ((y*c->width) + x)*sizeof(s32);
                    __m128i *At = (__m128i *)(c->drawBuffer + idx);
                    _mm_storeu_si128(At, color);
                }
            }
            
        } break;
        
        case 4:
        {
            AssertMsg((c->height % 4) == 0, "Window Height not divisible by 4 (SIMD)\n");
            AssertMsg((c->width % 4) == 0, "Window Width not divisible by 4 (SIMD)\n");
            
            s32 halfWidth  = c->width/2;
            s32 halfHeight = c->height/2;
            s32 xStart = (halfWidth*(threadID%2));
            s32 yStart = (halfHeight*(threadID/2));
            
            __m128i color = _mm_set1_epi32 ((int)c->backgroundColor);
            
            for(s32 y = yStart; y < yStart+halfHeight; y++)
            {
                for(s32 x = xStart; x < xStart+halfWidth; x += 4)
                {
                    u32 idx = ((y*c->width) + x)*sizeof(s32);
                    __m128i *At = (__m128i *)(c->drawBuffer + idx);
                    _mm_storeu_si128(At, color);
                }
            }
            
        } break;
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
            
            UIScrollableRegion scroll = curr->scroll;
            
            switch(curr->type)
            {
                
                case UI_RC_LABEL8:
                {
                    //TODO: I don't like this.
                    ls_uiGlyphString_8(c, font, xPos, yPos, threadRect, scissor, scroll, curr->label8, textColor);
                } break;
                
                case UI_RC_LABEL32:
                {
                    ls_uiGlyphString(c, font, xPos, yPos, threadRect, scissor, scroll, curr->label32, textColor);
                } break;
                
                case UI_RC_LABEL_LAYOUT:
                {
                    UIRect layoutRegion = { xPos, yPos, w, h };
                    ls_uiGlyphStringInLayout(c, font, layoutRegion, threadRect, scissor, scroll, curr->label32, textColor);
                } break;
                
                case UI_RC_TEXTBOX:
                {
                    UITextBox *box = curr->textBox;
                    
                    Color caretColor = textColor;
                    const s32 horzOff = 4;
                    
                    //TODO: Make the font selection more of a global thing??
                    s32 strPixelHeight = font->pixelHeight;
                    
                    ls_uiBorderedRect(c, xPos, yPos, w, h, threadRect, scissor, scroll, bkgColor);
                    
                    s32 strX = xPos + horzOff;
                    s32 strY = yPos + h - strPixelHeight;
                    
                    //NOTETODO: For now we double draw for selected strings. We can improve with 3-segment drawing.
                    if(box->isCaretOn && c->currentFocus == (u64 *)box)
                    { ls_uiRenderStringOnRect(c, box, strX, strY, w, h, threadRect, scissor, scroll,
                                              box->caretIndex-box->currLineBeginIdx, textColor, c->invTextColor); }
                    else
                    { ls_uiRenderStringOnRect(c, box, strX, strY, w, h, threadRect, scissor, scroll,
                                              -1, textColor, c->invTextColor); }
                    
                } break;
                
                case UI_RC_LISTBOX:
                {
                    UIListBox *list = curr->listBox;
                    
                    s32 strHeight = font->pixelHeight; 
                    s32 vertOff = ((h - strHeight) / 2) + 4; //TODO: @FontDescent
                    
                    ls_uiBorderedRect(c, xPos, yPos, w, h, threadRect, scissor, scroll);
                    
                    if(list->list.count)
                    {
                        utf32 selected = list->list[list->selectedIndex].name;
                        ls_uiGlyphString(c, font, xPos+10, yPos + vertOff, threadRect, scissor, scroll, selected, c->textColor);
                    }
                    
                    
                    s32 maxHeight = (list->list.count)*h;
                    if(list->isOpening)
                    {
                        s32 height = 0;
                        if(list->dtOpen > 17)  { height = maxHeight*0.10f; }
                        if(list->dtOpen > 34)  { height = maxHeight*0.35f; }
                        if(list->dtOpen > 52)  { height = maxHeight*0.70f; }
                        
                        if(!list->isOpen)
                        { ls_uiFillRect(c, xPos+1, yPos-height, w-2, height,
                                        threadRect, scissor, scroll, c->widgetColor); }
                    }
                    
                    if(list->isOpen)
                    {
                        for(u32 i = 0; i < list->list.count; i++)
                        {
                            s32 currY = yPos - (h*(i+1));
                            UIListBoxItem *currItem = list->list + i;
                            
                            ls_uiRect(c, xPos+1, currY, w-2, h, threadRect, scissor, scroll, currItem->bkgColor);
                            ls_uiGlyphString(c, font, xPos+10, yPos + vertOff - (h*(i+1)),
                                             threadRect, scissor, scroll, currItem->name, currItem->textColor);
                            
                        }
                        
                        ls_uiBorder(c, xPos, yPos-maxHeight, w, maxHeight+1, threadRect, scissor, scroll);
                    }
                    
                } break;
                
                case UI_RC_LISTBOX_ARR:
                {
                    ls_uiDrawArrow(c, xPos, yPos, w, h,
                                   threadRect, scissor, scroll, curr->listBox->arrowBkg, UIA_DOWN);
                } break;
                
                case UI_RC_BUTTON:
                {
                    UIButton *button = curr->button;
                    
                    if(button->style == UIBUTTON_TEXT)
                    {
                        ls_uiBorderedRect(c, xPos, yPos, w, h, threadRect, scissor, scroll, bkgColor);
                        
                        if(button->name.data)
                        {
                            s32 strHeight = font->pixelHeight;
                            s32 strWidth  = ls_uiGlyphStringLen(c, font, button->name);
                            s32 xOff      = (w - strWidth) / 2; //TODO: What happens when the string is too long?
                            s32 yOff      = strHeight*0.25; //TODO: @FontDescent
                            
                            ls_uiGlyphString(c, font, xPos+xOff, yPos+yOff, threadRect, scissor, scroll,
                                             button->name, textColor);
                        }
                    }
                    else if(button->style == UIBUTTON_TEXT_NOBORDER)
                    {
                        ls_uiRect(c, xPos, yPos, w, h, threadRect, scissor, scroll, bkgColor);
                        
                        if(button->name.data)
                        {
                            s32 strHeight = font->pixelHeight;
                            s32 strWidth  = ls_uiGlyphStringLen(c, font, button->name);
                            s32 xOff      = (w - strWidth) / 2; //TODO: What happens when the string is too long?
                            s32 yOff      = strHeight*0.25; //TODO: @FontDescent
                            
                            ls_uiGlyphString(c, font, xPos+xOff, yPos+yOff, threadRect, scissor, scroll,
                                             button->name, textColor);
                        }
                    }
                    else if(button->style == UIBUTTON_NO_TEXT)
                    {
                        ls_uiRect(c, xPos, yPos, w, h, threadRect, scissor, scroll, bkgColor);
                    }
                    else if(button->style == UIBUTTON_BMP)
                    {
                        ls_uiBitmap(c, xPos, yPos, button->bmpW, button->bmpH, threadRect, (u32 *)button->bmpData);
                    }
                    else { AssertMsg(FALSE, "Unhandled button style"); }
                    
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
                        ls_uiFillRect(c, xPos+1, yPos+1, lColorW, h-2, threadRect, scissor, scroll, slider->lColor);
                        ls_uiFillRect(c, xPos+slidePos+1, yPos+1, rColorW, h-2,
                                      threadRect, scissor, scroll, slider->rColor);
                        
                        utf32 val = ls_utf32FromInt(slider->currValue);
                        
                        s32 strHeight = font->pixelHeight;
                        
                        u32 textLen = ls_uiGlyphStringLen(c, font, val);
                        s32 strXPos = xPos + slidePos - textLen - 2;
                        Color textBkgC = slider->lColor;
                        
                        if(strXPos < xPos+1) { strXPos = xPos + slidePos + slideWidth + 2; textBkgC = slider->rColor; }
                        
                        Color valueColor = c->borderColor;
                        u8 alpha = 0x00 + (slider->isHeld*0xFF);
                        valueColor = SetAlpha(valueColor, alpha);
                        ls_uiGlyphString(c, font, strXPos, yPos + h - strHeight, threadRect, scissor, scroll,
                                         val, valueColor);
                        
                        ls_utf32Free(&val);
                        
                        if(slider->isHot)
                        {
                            s32 actualX = (xPos + slidePos) - 1;
                            s32 actualY = yPos - 2;
                            
                            s32 actualWidth  = slideWidth+2;
                            s32 actualHeight = 4 + h;
                            
                            ls_uiFillRect(c, actualX, actualY, actualWidth, actualHeight,
                                          threadRect, scissor, scroll, c->borderColor);
                        }
                        else
                        {
                            ls_uiFillRect(c, xPos+slidePos, yPos, slideWidth, h,
                                          threadRect, scissor, scroll, c->borderColor);
                        }
                        
                    }
                    else if(slider->style == SL_LINE)
                    { AssertMsg(FALSE, "Slider style line is not implemented\n"); }
                    
                    //NOTE: Draw the displayed text, and hide through Alpha the slider info.
                    
                    Color rectColor = c->widgetColor;
                    rectColor = SetAlpha(rectColor, opacity);
                    ls_uiBorderedRect(c, xPos, yPos, w, h, threadRect, scissor, scroll, rectColor, borderColor);
                    
                    s32 strHeight = font->pixelHeight;
                    
                    s32 strWidth  = ls_uiGlyphStringLen(c, font, slider->text);
                    s32 xOff      = (w - strWidth) / 2;
                    s32 yOff      = (h - strHeight) + 3; //TODO: @FontDescent
                    
                    Color textColor = c->textColor;
                    textColor = SetAlpha(textColor, opacity);
                    
                    ls_uiGlyphString(c, font, xPos+xOff, yPos + yOff, threadRect, scissor, scroll,
                                     slider->text, textColor);
                } break;
                
                case UI_RC_MENU:
                {
                    UIMenu *menu = curr->menu;
                    ls_uiBorderedRect(c, xPos, yPos, w, h, threadRect, scissor, scroll, bkgColor, c->widgetColor);
                    
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
                        ls_uiBorderedRect(c, subX, subY, subW, subH,
                                          threadRect, scissor, scroll, subColor, c->widgetColor);
                        ls_uiGlyphString(c, font, subX+xOff, subY+yOff, threadRect, scissor, scroll,
                                         sub->name, textColor);
                        
                        if(menu->isOpen && (menu->openIdx == subIdx))
                        {
                            u32 openSubHeight = subH*sub->items.count;
                            ls_uiBorderedRect(c, subX, subY-openSubHeight, subW, openSubHeight+1,
                                              threadRect, scissor, scroll, bkgColor, c->widgetColor);
                            
                            u32 currY = subY-subH;
                            for(u32 itemIdx = 0; itemIdx < sub->items.count; itemIdx++)
                            {
                                UIMenuItem *item = sub->items + itemIdx;
                                
                                strWidth = ls_uiGlyphStringLen(c, font, item->name);
                                xOff = (subW - strWidth) / 2;
                                
                                if(item->isHot) {
                                    ls_uiRect(c, subX, currY, subW, subH,
                                              threadRect, scissor, scroll, c->highliteColor);
                                }
                                
                                ls_uiGlyphString(c, font, subX+xOff, currY+yOff, threadRect, scissor, scroll,
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
                                          threadRect, scissor, scroll, itemColor, c->widgetColor);
                        
                        ls_uiGlyphString(c, font, itemX+xOff, subY+yOff, threadRect, scissor, scroll,
                                         item->name, c->textColor);
                    }
                    
                } break;
                
                case UI_RC_RECT:
                {
                    ls_uiBorderedRect(c, xPos, yPos, w, h, threadRect, scissor, scroll, bkgColor, borderColor);
                } break;
                
                case UI_RC_SEPARATOR:
                {
                    ls_uiFillRect(c, xPos, yPos, w, h, threadRect, scissor, scroll, borderColor);
                } break;
                
                case UI_RC_SCROLLBAR:
                {
                    //TODO: Differentiate between horizontal and vertical scrollbars
                    s32 scrollRectX = xPos + w - 16;
                    ls_uiBorderedRect(c, scrollRectX, yPos, 16, h-1, threadRect, scissor, {});
                    
                    //NOTE: Calculate current scrollbar position
                    s32 scrollBarH   = 30;
                    s32 usableHeight = h - 4 - scrollBarH;
                    s32 totalHeight  = scroll.y - scroll.minY;
                    
                    s32 scrollBarYOff = ((f32)-scroll.deltaY / (f32)totalHeight) * usableHeight;
                    s32 scrollBarY    = (yPos + h - 4) - scrollBarYOff - scrollBarH;
                    
                    if(scrollBarY < yPos+2)   scrollBarY = yPos+2;
                    if(scrollBarY > yPos+h-2-scrollBarH) scrollBarY = yPos+h-2-scrollBarH;
                    
                    ls_uiFillRect(c, scrollRectX+2, scrollBarY, 12, scrollBarH,
                                  threadRect, scissor, {}, c->borderColor);
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
    
    return;
}


#endif //LS_UI_IMPLEMENTATION
