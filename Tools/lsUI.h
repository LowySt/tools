#ifndef LS_UI_H
#define LS_UI_H

#include "lsWindows.h"
#include "lsGraphics.h"
#include "lsCRT.h"
#include "lsMath.h"
#include "lsString.h"
#include "lsInput.h"
#include "lsStack.h"

#define RGBA(r,g,b,a)  (u32)((a<<24)|(r<<16)|(g<<8)|b)
#define RGB(r,g,b)     (u32)((0xFF<<24)|(r<<16)|(g<<8)|b)
#define RGBg(v)        (u32)((0xFF<<24)|(v<<16)|(v<<8)|v)
#define SetAlpha(v, a) (u32)((v & 0x00FFFFFF) | (((u32)a)<<24))
#define GetAlpha(v)    ( u8)(((v) & 0xFF000000) >> 24)

const     u32 THREAD_COUNT       = 2;
constexpr u32 RENDER_GROUP_COUNT = THREAD_COUNT == 0 ? 1 : THREAD_COUNT;

typedef u32 Color;

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

struct UIScissor
{
    struct UIRect { s32 x, y, w, h; };
    stack rects;
    
    UIRect *currRect;
};

struct UILPane
{
    u32 dtOpen;
    b32 isOpening;
    b32 isOpen;
};

struct UIContext;

enum UIButtonStyle { UIBUTTON_TEXT, UIBUTTON_TEXT_NOBORDER, UIBUTTON_BMP };

typedef b32(*ButtonProc)(UIContext *cxt, void *data);
struct UIButton
{
    UIButtonStyle style;
    
    unistring name;
    u8 *bmpData;
    s32 bmpW, bmpH;
    
    b32 isHot;
    b32 isHeld;
    
    ButtonProc onClick;
    ButtonProc onHold;
    
    void *data; //TODO: Separate onClick / onHold user data
};


typedef b32(*TextBoxProc)(UIContext *, void *);
struct UITextBox
{
    unistring text;
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
    unistring name;
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
    
    unistring text;
    
    s32 currValue;
    s32 maxValue;
    s32 minValue;
    
    f64 currPos;
    
    SliderStyle style;
    Color lColor;
    Color rColor;
};


//TODO: Very Shitty implementation of Menus
struct UIMenu
{
    UIButton  closeWindow;
    UIButton  minimize;
    
    b32 isOpen;
    s32 openIdx;
    Array<UIButton> items;
    
    UIMenu *sub;            //NOTE: There is 1 sub for every item
    u32     maxSub;
};
struct __UImenuDataPass { UIMenu *menu; s32 idx; };

enum RenderCommandExtra
{
    UI_RCE_NULL,
    
    UI_RCE_LEFT,
    UI_RCE_RIGHT,
    UI_RCE_TOP,
    UI_RCE_BOT,
    
    UI_RCE_TL,
    UI_RCE_TR,
    UI_RCE_BL,
    UI_RCE_BR,
};

const char* RenderCommandTypeAsString[] = {
    "UI_RC_INVALID",
    "UI_RC_TEXTBOX",
    "UI_RC_BUTTON",
    "UI_RC_LISTBOX",
    "UI_RC_LISTBOX_ARR",
    "UI_RC_SLIDER",
    "UI_RC_RECT",
    "UI_RC_MENU",
    "UI_RC_BACKGROUND",
    
    "UI_RC_FRAG_OFF",
    
    "UI_RC_FRAG_TEXTBOX",
    "UI_RC_FRAG_BUTTON",
    "UI_RC_FRAG_LISTBOX",
    "UI_RC_FRAG_LISTBOX_ARR",
    "UI_RC_FRAG_SLIDER",
    "UI_RC_FRAG_RECT",
    "UI_RC_FRAG_MENU",
    "UI_RC_FRAG_BACKGROUND",
};

enum RenderCommandType
{
    UI_RC_TESTBOX = 990,
    
    UI_RC_INVALID = 0,
    
    UI_RC_TEXTBOX = 1,
    UI_RC_LABEL,
    UI_RC_BUTTON,
    UI_RC_LISTBOX,
    UI_RC_LISTBOX_ARR,
    UI_RC_SLIDER,
    UI_RC_RECT,
    UI_RC_MENU,
    UI_RC_BACKGROUND,
    
    UI_RC_FRAG_OFF,
    
    UI_RC_FRAG_TEXTBOX,
    UI_RC_FRAG_LABEL,
    UI_RC_FRAG_BUTTON,
    UI_RC_FRAG_LISTBOX,
    UI_RC_FRAG_LISTBOX_ARR,
    UI_RC_FRAG_SLIDER,
    UI_RC_FRAG_RECT,
    UI_RC_FRAG_MENU,
    UI_RC_FRAG_BACKGROUND,
};

struct RenderCommand
{
    RenderCommandType  type;
    
    s32 x, y, w, h;
    s32 minX, minY, maxX, maxY;
    
    union
    {
        UITextBox *textBox;
        char32_t  *label;
        UIButton  *button;
        UIListBox *listBox;
        UISlider  *slider;
        UIMenu    *menu;
    };
    
    Color bkgColor;
    Color textColor;
    
    RenderCommandExtra extra;
    s32 oX, oY, oW, oH;
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
    
    UIScissor scissor;
    
    u64 *currentFocus;
    u64 *lastFocus;
    b32 focusWasSetThisFrame;
    
    b32 nextFrameFocusChange;
    u64 *nextFrameFocus;
    
    u64 *mouseCapture;
    
    RenderGroup renderGroups[RENDER_GROUP_COUNT];
    
    CONDITION_VARIABLE startRender;
    CRITICAL_SECTION crit;
    
    RenderCallback renderFunc = NULL;
    u32 dt;
    RegionTimer frameTime = {};
    
    HWND MainWindow;
    
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



HWND       ls_uiCreateWindow(HINSTANCE MainInstance, u8 *drawBuffer, UIContext *c);
UIContext *ls_uiInitDefaultContext(u8 *drawBuffer, u32 width, u32 height, RenderCallback cb);

void       ls_uiFrameBegin(UIContext *c);
void       ls_uiFrameEnd(UIContext *c, u64 frameTimeTargetMs);

void       ls_uiAddOnDestroyCallback(UIContext *c, onDestroyFunc f);

void       ls_uiPushRenderCommand(UIContext *c, RenderCommand command, s32 zLayer);

void       ls_uiFocusChange(UIContext *cxt, u64 *focus);
b32        ls_uiInFocus(UIContext *cxt, void *p);
b32        ls_uiHasCapture(UIContext *cxt, void *p);
void       ls_uiSelectFontByPixelHeight(UIContext *cxt, u32 pixelHeight);
s32        ls_uiSelectFontByFontSize(UIContext *cxt, UIFontSize fontSize);

void       ls_uiPushScissor(UIContext *cxt, s32 x, s32 y, s32 w, s32 h);
void       ls_uiPopScissor(UIContext *cxt);

Color      ls_uiDarkenRGB(Color c, u32 factor);
Color      ls_uiLightenRGB(Color c, u32 factor);
Color      ls_uiAlphaBlend(Color source, Color dest, u8 alpha);
Color      ls_uiAlphaBlend(Color source, Color dest);
Color      ls_uiRGBAtoARGB(Color c);

b32        ls_uiButton(UIContext *c, UIButton *button, s32 xPos, s32 yPos, s32 w, s32 h, s32 zLayer);

void       ls_uiLabel(UIContext *cxt, unistring label, s32 xPos, s32 yPos, s32 zLayer);
void       ls_uiLabel(UIContext *cxt, const char32_t *label, s32 xPos, s32 yPos, s32 zLayer);

void       ls_uiTextBoxClear(UIContext *cxt, UITextBox *box);
void       ls_uiTextBoxSet(UIContext *cxt, UITextBox *box, unistring s);
b32        ls_uiTextBox(UIContext *cxt, UITextBox *box, s32 xPos, s32 yPos, s32 w, s32 h);

void       ls_uiDrawArrow(UIContext *cxt, s32 x, s32 yPos, s32 w, s32 h, Color bkgColor, UIArrowSide s);
u32        ls_uiListBoxAddEntry(UIContext *cxt, UIListBox *list, char *s);
u32        ls_uiListBoxAddEntry(UIContext *cxt, UIListBox *list, unistring s);
void       ls_uiListBoxRemoveEntry(UIContext *cxt, UIListBox *list, u32 index);
b32        ls_uiListBox(UIContext *c, UIListBox *list, s32 xPos, s32 yPos, s32 w, s32 h, u32 zLayer);

UISlider   ls_uiSliderInit(char32_t *name, s32 maxVal, s32 minVal, f64 currPos, SliderStyle s, Color l, Color r);
void       ls_uiSliderChangeValueBy(UIContext *cxt, UISlider *f, s32 valueDiff);
s32        ls_uiSliderGetValue(UIContext *cxt, UISlider *f);
b32        ls_uiSlider(UIContext *cxt, UISlider *slider, s32 xPos, s32 yPos, s32 w, s32 h);

b32        ls_uiMenuDefaultOnClick(UIContext *cxt, void *data);
void       ls_uiMenuAddItem(UIMenu *menu, UIButton b);
void       ls_uiMenuAddSub(UIMenu *menu, UIMenu sub, s32 idx);
b32        ls_uiMenu(UIContext *c, UIMenu *menu, s32 x, s32 y, s32 w, s32 h);

void       ls_uiRender(UIContext *c);

#endif


#ifdef LS_UI_IMPLEMENTATION


//IMPORTANT NOTE:
//
// As of right now lsUI DEPENDS on Input.
// I don't know if this is the right choice. I guess I'll discover it.
//
//IMPORTANT NOTE
Input UserInput = {};

HBITMAP  closeButton;
HDC      closeButtonDC;
void    *closeButtBackbuff;

HDC  WindowDC;
HDC  BackBufferDC;

LRESULT ls_uiWindowProc(HWND h, UINT msg, WPARAM w, LPARAM l)
{
    LRESULT Result = 0;
    
    MouseInput *Mouse = &UserInput.Mouse;
    UIContext *c = 0;
    
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
        } break;
        
        case WM_PAINT:
        {
            c = (UIContext *)GetWindowLongPtrA(h, GWLP_USERDATA);
            
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
            
            StretchDIBits(BackBufferDC, 0, 0, c->windowWidth, c->windowHeight,
                          0, 0, c->windowWidth, c->windowHeight,
                          c->drawBuffer, &BitmapInfo, DIB_RGB_COLORS, SRCCOPY);
            
            Result = BitBlt(WindowDC, r.left, r.top, r.right, r.bottom,
                            BackBufferDC, 0, 0, SRCCOPY);
            
            if(Result == 0) {
                DWORD Err = GetLastError();
                int breakHere = 0;
            }
            
            EndPaint(h, &ps);
        } break;
        
        case WM_CHAR:
        {
            c = (UIContext *)GetWindowLongPtrA(h, GWLP_USERDATA);
            
            c->hasReceivedInput = TRUE;
            
            b32 wasPressed = (l >> 30) & 0x1;
            u16 repeat     = (u16)l;
            
            b32 asciiRange  = ((w >= 32) && (w <= 126));
            b32 plane0Latin = ((w >= 0x00A1) && (w <= 0x024F));
            
            if(asciiRange || plane0Latin)
            {
                if(!wasPressed || repeat > 0)
                {
                    UserInput.Keyboard.hasPrintableKey = TRUE;
                    UserInput.Keyboard.keyCodepoint    = w;
                }
            }
            else if(w == 13) //NOTETODO: Hack to input a '\n' when Enter ('\r') is pressed.
            {
                if(!wasPressed || repeat > 0)
                {
                    UserInput.Keyboard.hasPrintableKey = TRUE;
                    UserInput.Keyboard.keyCodepoint    = 10;
                }
            }
            
        } break;
        
        case WM_KEYDOWN:
        {
            c = (UIContext *)GetWindowLongPtrA(h, GWLP_USERDATA);
            
            c->hasReceivedInput = TRUE;
            
            //Repeat is the first 16 bits of the LPARAM. Bits [0-15];
            u16 rep = (u16)l;
            
            switch(w)
            { 
                case VK_F1:      KeySetAndRepeat(keyMap::F1, rep);        break;
                case VK_F2:      KeySetAndRepeat(keyMap::F2, rep);        break;
                case VK_F3:      KeySetAndRepeat(keyMap::F3, rep);        break;
                case VK_F12:     KeySetAndRepeat(keyMap::F12, rep);       break;
                
                case VK_DOWN:    KeySetAndRepeat(keyMap::DArrow, rep);    break;
                case VK_UP:      KeySetAndRepeat(keyMap::UArrow, rep);    break;
                case VK_LEFT:    KeySetAndRepeat(keyMap::LArrow, rep);    break;
                case VK_RIGHT:   KeySetAndRepeat(keyMap::RArrow, rep);    break;
                
                case VK_RETURN:  KeySetAndRepeat(keyMap::Enter, rep);     break;
                case VK_BACK:    KeySetAndRepeat(keyMap::Backspace, rep); break;
                case VK_DELETE:  KeySetAndRepeat(keyMap::Delete, rep);    break;
                case VK_HOME:    KeySetAndRepeat(keyMap::Home, rep);      break;
                case VK_END:     KeySetAndRepeat(keyMap::End, rep);       break;
                case VK_CONTROL: KeySetAndRepeat(keyMap::Control, rep);   break;
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
            c = (UIContext *)GetWindowLongPtrA(h, GWLP_USERDATA);
            
            c->hasReceivedInput = TRUE;
            
            switch(w)
            { 
                case VK_F1:      KeyUnset(keyMap::F1);        break;
                case VK_F2:      KeyUnset(keyMap::F2);        break;
                case VK_F3:      KeyUnset(keyMap::F3);        break;
                case VK_F12:     KeyUnset(keyMap::F12);       break;
                
                case VK_DOWN:    KeyUnset(keyMap::DArrow);    break;
                case VK_UP:      KeyUnset(keyMap::UArrow);    break;
                case VK_LEFT:    KeyUnset(keyMap::LArrow);    break;
                case VK_RIGHT:   KeyUnset(keyMap::RArrow);    break;
                
                case VK_RETURN:  KeyUnset(keyMap::Enter);     break;
                case VK_BACK:    KeyUnset(keyMap::Backspace); break;
                case VK_DELETE:  KeyUnset(keyMap::Delete);    break;
                case VK_HOME:    KeyUnset(keyMap::Home);      break;
                case VK_END:     KeyUnset(keyMap::End);       break;
                case VK_CONTROL: KeyUnset(keyMap::Control);   break;
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
            c = (UIContext *)GetWindowLongPtrA(h, GWLP_USERDATA);
            
            c->hasReceivedInput = TRUE;
            
            Mouse->isLeftPressed = TRUE;
        } break;
        
        case WM_LBUTTONUP:
        {
            c = (UIContext *)GetWindowLongPtrA(h, GWLP_USERDATA);
            
            c->hasReceivedInput = TRUE;
            
            Mouse->isLeftPressed = FALSE;
            
            c->isDragging = FALSE;
            BOOL success = ReleaseCapture();
        } break;
        
        case WM_RBUTTONDOWN:
        { 
            c = (UIContext *)GetWindowLongPtrA(h, GWLP_USERDATA);
            
            c->hasReceivedInput = TRUE;
            Mouse->isRightPressed = TRUE; 
        } break;
        
        case WM_RBUTTONUP:
        { 
            c = (UIContext *)GetWindowLongPtrA(h, GWLP_USERDATA);
            
            c->hasReceivedInput = TRUE; 
            Mouse->isRightPressed = FALSE; 
        } break;
        
        case WM_MOUSEMOVE:
        {
            c = (UIContext *)GetWindowLongPtrA(h, GWLP_USERDATA);
            
            POINTS currMouseClient = *((POINTS *)&l);
            Mouse->currPosX = currMouseClient.x;
            Mouse->currPosY = c->windowHeight - currMouseClient.y;
            
            c->hasReceivedInput = TRUE;
            
            //TODO:NOTE: Page says to return 0, but DO i HAVE to?
        } break;
        
        case WM_DESTROY:
        {
            c = (UIContext *)GetWindowLongPtrA(h, GWLP_USERDATA);
            if(c->onDestroy) { c->onDestroy(c); }
            ExitProcess(0);
        } break;
        
        default: { return DefWindowProcA(h, msg, w, l); }
    }
    
    return Result;
}

void __ui_RegisterWindow(HINSTANCE MainInstance)
{
    
    u32 prop = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
    
    HCURSOR cursor = LoadCursorA(NULL, IDC_ARROW);
    
    WNDCLASSA WindowClass = { 0 };
    WindowClass.style = prop;
    WindowClass.lpfnWndProc = ls_uiWindowProc;
    WindowClass.hInstance = MainInstance;
    WindowClass.lpszClassName = "WndClass";
    WindowClass.hCursor = cursor;
    
    if (!RegisterClassA(&WindowClass))
    {
        DWORD Error = GetLastError();
        ls_printf("When Registering WindowClass in Win32_SetupScreen got error: %d", Error);
    }
}

HWND __ui_CreateWindow(HINSTANCE MainInstance, UIContext *c)
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
    
    HWND WindowHandle;
    if ((WindowHandle = CreateWindowExA(0, "WndClass",
                                        "PCMan", style,
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
    
    WindowDC           = GetDC(WindowHandle);
    BackBufferDC       = CreateCompatibleDC(WindowDC);
    HBITMAP DibSection = CreateDIBSection(BackBufferDC, &BackBufferInfo,
                                          DIB_RGB_COLORS, (void **)&(c->drawBuffer), NULL, 0);
    SelectObject(BackBufferDC, DibSection);
    
    c->windowPosX = (s16)spaceX;
    c->windowPosY = (s16)spaceY; //NOTE:TODO: Hardcoded!!
    
    return WindowHandle;
}

HWND ls_uiCreateWindow(HINSTANCE MainInstance, UIContext *c)
{
    __ui_RegisterWindow(MainInstance);
    
    UserInput.Keyboard.getClipboard = windows_GetClipboard;
    UserInput.Keyboard.setClipboard = windows_SetClipboard;
    
    c->MainWindow = __ui_CreateWindow(MainInstance, c);
    
    return c->MainWindow;
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
    InvalidateRect(c->MainWindow, NULL, TRUE);
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
    
    if(THREAD_COUNT != 0)
    {
        for(u32 i = 0; i < THREAD_COUNT; i++)
        {
            uiContext->renderGroups[i].RenderCommands[0] = ls_stackInit(sizeof(RenderCommand), 384);
            uiContext->renderGroups[i].RenderCommands[1] = ls_stackInit(sizeof(RenderCommand), 64);
            uiContext->renderGroups[i].RenderCommands[2] = ls_stackInit(sizeof(RenderCommand), 64);
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
        uiContext->renderGroups[0].RenderCommands[1] = ls_stackInit(sizeof(RenderCommand), 64);
        uiContext->renderGroups[0].RenderCommands[2] = ls_stackInit(sizeof(RenderCommand), 64);
    }
    
    
    //NOTETODO This is initializing the first scissor, but is this good?
    //         Is this even necessary?
    ls_uiPushScissor(uiContext, 0, 0, uiContext->windowWidth, uiContext->windowHeight);
    
    //NOTETODO: Should this be here? Should we have another function 
    //          that specifically takes care of initialization of these global things??
    windows_initRegionTimer();
    
    return uiContext;
}

void ls_uiFrameBegin(UIContext *c)
{
    static b32 isStartup = TRUE;
    
    RegionTimerBegin(c->frameTime);
    
    UserInput.Keyboard.prevState = UserInput.Keyboard.currentState;
    UserInput.Keyboard.repeatState = {};
    
    UserInput.Keyboard.hasPrintableKey = FALSE;
    UserInput.Keyboard.keyCodepoint    = 0;
    
    UserInput.Mouse.prevPosX         = UserInput.Mouse.currPosX;
    UserInput.Mouse.prevPosY         = UserInput.Mouse.currPosY;
    UserInput.Mouse.wasLeftPressed   = UserInput.Mouse.isLeftPressed;
    UserInput.Mouse.wasRightPressed  = UserInput.Mouse.isRightPressed;
    UserInput.Mouse.wasMiddlePressed = UserInput.Mouse.isMiddlePressed;
    
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
    {
        TranslateMessage(&Msg);
        DispatchMessageA(&Msg);
    }
    
    //NOTE: Window starts hidden, and then is shown after the first frame, 
    //      to avoid flashing because initially the frame buffer is all white.
    if(isStartup) { ShowWindow(c->MainWindow, SW_SHOW); isStartup = FALSE; c->hasReceivedInput = TRUE; }
}

void ls_uiFrameEnd(UIContext *c, u64 frameTimeTargetMs)
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
    c->dt = RegionTimerGet(c->frameTime); //frameTimeMs;
    lastFrameTime = c->dt;
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
    AssertMsg(command.type != UI_RC_FRAG_OFF, "Offset as Render Command?\n");
    
    __ls_RenderRect commandRect = { command.x, command.y, command.w, command.h };
    
    switch(THREAD_COUNT)
    {
        case 0:
        case 1:
        {
            command.minX = 0;
            command.minY = 0;
            command.maxX = c->windowWidth;
            command.maxY = c->windowHeight;
            ls_stackPush(&c->renderGroups[0].RenderCommands[zLayer], (void *)&command);
            return;
        } break;
        
        case 2:
        {
            if(ls_uiRectIsInside(commandRect, {0, 0, (s32)(c->width / 2), (s32)c->height}))
            {
                command.minX = 0;
                command.minY = 0;
                command.maxX = c->windowWidth / 2;
                command.maxY = c->windowHeight / 2;
                
                ls_stackPush(&c->renderGroups[0].RenderCommands[zLayer], (void *)&command);
                return;
            }
            else if(ls_uiRectIsInside(commandRect, {(s32)(c->width / 2), 0, (s32)(c->width / 2), (s32)c->height}))
            {
                command.minX = c->windowWidth / 2;
                command.minY = c->windowHeight / 2;
                command.maxX = c->windowWidth;
                command.maxY = c->windowHeight;
                
                ls_stackPush(&c->renderGroups[1].RenderCommands[zLayer], (void *)&command);
                return;
            }
            else
            {
                //Half in one, half in another.
                
                RenderCommand section = command;
                section.extra = UI_RCE_LEFT;
                section.minX = 0;
                section.minY = 0;
                section.maxX = c->width / 2;
                section.maxY = c->height;
                ls_stackPush(&c->renderGroups[0].RenderCommands[zLayer], (void *)&section);
                
                section.extra = UI_RCE_RIGHT;
                section.minX = c->width / 2;
                section.minY = 0;
                section.maxX = c->width;
                section.maxY = c->height;
                
                ls_stackPush(&c->renderGroups[1].RenderCommands[zLayer], (void *)&section);
#if 0
                section.type  = (RenderCommandType)(command.type);// + UI_RC_FRAG_OFF);
                section.extra = UI_RCE_LEFT;
                section.oX = command.x;
                section.oY = command.y;
                section.oW = command.w;
                section.oH = command.h;
                
                section.x     = command.x;
                section.w     = command.w;//(c->width/2) - command.x;
                
                section.minX = 0;
                section.minY = 0;
                section.maxX = c->windowWidth / 2;
                section.maxY = c->windowHeight / 2;
                
                ls_stackPush(&c->renderGroups[0].RenderCommands[zLayer], (void *)&section);
                
                section.extra = UI_RCE_RIGHT;
                section.x     = command.x;//c->width/2;
                section.w     = command.w;//command.w - section.w;
                
                section.minX = c->windowWidth / 2;
                section.minY = c->windowHeight / 2;
                section.maxX = c->windowWidth;
                section.maxY = c->windowHeight;
                
                ls_stackPush(&c->renderGroups[1].RenderCommands[zLayer], (void *)&section);
#endif
                return;
            }
            
        } break;
        
        case 4:
        {
            u32 i1, i2, i3, i4;
            __ls_RenderRect p1 = ls_uiQuadrantFromPoint(c, command.x,             command.y,             &i1);
            __ls_RenderRect p2 = ls_uiQuadrantFromPoint(c, command.x + command.w, command.y,             &i2);
            __ls_RenderRect p3 = ls_uiQuadrantFromPoint(c, command.x,             command.y + command.h, &i3);
            __ls_RenderRect p4 = ls_uiQuadrantFromPoint(c, command.x + command.w, command.y + command.h, &i4);
            
            //NOTE: The command is not fragged and lives in a single rect.
            if((p1 == p2) && (p2 == p3) && (p3 == p4))
            { ls_stackPush(&c->renderGroups[i1].RenderCommands[zLayer], (void *)&command); return; }
            
            //NOTE: Left Half, Right Half
            else if((p1 == p3) && (p2 == p4))
            {
                RenderCommand section = command;
                
                section.type  = (RenderCommandType)(command.type + UI_RC_FRAG_OFF);
                section.extra = UI_RCE_LEFT;
                section.oX = command.x;
                section.oY = command.y;
                section.oW = command.w;
                section.oH = command.h;
                
                section.x     = command.x;
                section.w     = (c->width/2) - command.x;
                
                ls_stackPush(&c->renderGroups[i1].RenderCommands[zLayer], (void *)&section);
                
                section.extra = UI_RCE_RIGHT;
                section.x     = c->width/2;
                section.w     = command.w - section.w;
                
                ls_stackPush(&c->renderGroups[i2].RenderCommands[zLayer], (void *)&section);
                return;
            }
            
            //NOTE: Top Half, Bottom Half
            else if((p1 == p2) && (p3 == p4))
            {
                RenderCommand section = command;
                
                section.type  = (RenderCommandType)(command.type + UI_RC_FRAG_OFF);
                section.extra = UI_RCE_TOP;
                section.oX = command.x;
                section.oY = command.y;
                section.oW = command.w;
                section.oH = command.h;
                
                section.x     = command.x;
                section.w     = command.w;
                section.y     = c->height/2;
                section.h     = command.h - (section.y - command.y);
                
                ls_stackPush(&c->renderGroups[i3].RenderCommands[zLayer], (void *)&section);
                
                section.extra = UI_RCE_BOT;
                
                section.x     = command.x;
                section.w     = command.w;
                section.y     = command.y;
                section.h     = (c->height/2) - command.y;
                
                ls_stackPush(&c->renderGroups[i1].RenderCommands[zLayer], (void *)&section);
                return;
            }
            
            //NOTE: Final case where all quadrants share the quad.
            else
            {
                RenderCommand section = command;
                
                section.type  = (RenderCommandType)(command.type + UI_RC_FRAG_OFF);
                section.extra = UI_RCE_TL;
                section.oX = command.x;
                section.oY = command.y;
                section.oW = command.w;
                section.oH = command.h;
                
                section.x     = command.x;
                section.w     = (c->width/2) - section.x;
                section.y     = c->height/2;
                section.h     = command.h - (section.y - command.y);
                
                ls_stackPush(&c->renderGroups[2].RenderCommands[zLayer], (void *)&section);
                
                section.extra = UI_RCE_TR;
                section.x     = c->width/2;
                section.w     = command.w - section.w;
                section.y     = c->height/2;
                section.h     = command.h - (section.y - command.y);
                
                ls_stackPush(&c->renderGroups[3].RenderCommands[zLayer], (void *)&section);
                
                section.extra = UI_RCE_BL;
                section.x     = command.x;
                section.w     = (c->width/2) - section.x;
                section.y     = command.y;
                section.h     = (c->height/2) - command.y;
                
                ls_stackPush(&c->renderGroups[0].RenderCommands[zLayer], (void *)&section);
                
                section.extra = UI_RCE_BR;
                section.x     = c->width/2;
                section.w     = command.w - section.w;
                section.y     = command.y;
                section.h     = (c->height/2) - command.y;
                
                ls_stackPush(&c->renderGroups[1].RenderCommands[zLayer], (void *)&section);
                return;
            }
            
        } break;
        
        default: { AssertMsg(FALSE, "Thread count not supported\n"); } return;
    }
    
    AssertMsg(FALSE, "Should never reach this case!\n");
}

//TODO:NOTE: Scissors are busted. A smaller scissor doesn't check if it is inside it's own parent!
void ls_uiPushScissor(UIContext *cxt, s32 x, s32 y, s32 w, s32 h)
{
    UIScissor *scissor = &cxt->scissor;
    
    if(!scissor->rects.data) { scissor->rects = ls_stackInit(sizeof(UIScissor::UIRect), 8); }
    UIScissor::UIRect rect = { x, y, w, h };
    
    ls_stackPush(&scissor->rects, (void *)&rect);
    scissor->currRect = (UIScissor::UIRect *)ls_stackTop(&scissor->rects);
}

void ls_uiPopScissor(UIContext *cxt)
{
    UIScissor *scissor = &cxt->scissor;
    AssertMsg(scissor->rects.data,      "Scissor stack is null\n");
    AssertMsg(scissor->rects.count > 0, "Scissor stack is already empty\n");
    
    ls_stackPop(&scissor->rects);
    if(scissor->rects.count > 0) //TODO: Top doesn't care if the count == 0
    {
        scissor->currRect = (UIScissor::UIRect *)ls_stackTop(&scissor->rects);
    }
    else
    {
        scissor->currRect = NULL;
    }
    
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
                   s32 minX, s32 maxX, s32 minY, s32 maxY, Color col)
{
    s32 startY = yPos;
    if(startY < minY) { h -= (minY-startY); startY = minY; }
    
    s32 startX = xPos;
    if(startX < minX) { w -= (minX-startX); startX = minX; }
    
    s32 diffWidth = (w % 4);
    s32 simdWidth = w - diffWidth;
    
    s32 diffHeight = (h % 4);
    s32 simdHeight = h - diffHeight;
    
    //TODO: Make AlphaBlending happen with SSE!!!
    
    //NOTE: Do the first Sub-Rectangle divisible by 4.
    //__m128i color = _mm_set1_epi32((int)c);
    
    for(s32 y = startY; y < startY+simdHeight; y++)
    {
        if(y > maxY) { break; }
        
        for(s32 x = startX; x < startX+simdWidth; x+=4)
        {
            if(x > maxX) { break; }
            
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
                if(x > maxX) { break; }
                
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
void ls_uiBorder(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h, s32 minX, s32 maxX, s32 minY, s32 maxY)
{
    Color C = c->borderColor;
    
    ls_uiFillRect(c, xPos,     yPos,     w, 1, minX, maxX, minY, maxY, C);
    ls_uiFillRect(c, xPos,     yPos+h-1, w, 1, minX, maxX, minY, maxY, C);
    ls_uiFillRect(c, xPos,     yPos,     1, h, minX, maxX, minY, maxY, C);
    ls_uiFillRect(c, xPos+w-1, yPos,     1, h, minX, maxX, minY, maxY, C);
}

inline
void ls_uiBorder(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h, s32 minX, s32 maxX, s32 minY, s32 maxY, Color borderColor)
{
    Color C = borderColor;
    
    ls_uiFillRect(c, xPos,     yPos,     w, 1, minX, maxX, minY, maxY, C);
    ls_uiFillRect(c, xPos,     yPos+h-1, w, 1, minX, maxX, minY, maxY, C);
    ls_uiFillRect(c, xPos,     yPos,     1, h, minX, maxX, minY, maxY, C);
    ls_uiFillRect(c, xPos+w-1, yPos,     1, h, minX, maxX, minY, maxY, C);
}

inline
void ls_uiBorderedRect(UIContext *cxt, s32 xPos, s32 yPos, s32 w, s32 h,
                       s32 minX, s32 maxX, s32 minY, s32 maxY)
{
    ls_uiBorder(cxt, xPos, yPos, w, h, minX, maxX, minY, maxY);
    ls_uiFillRect(cxt, xPos+1, yPos+1, w-2, h-2, minX, maxX, minY, maxY, cxt->widgetColor);
}

inline
void ls_uiBorderedRect(UIContext *cxt, s32 xPos, s32 yPos, s32 w, s32 h, 
                       s32 minX, s32 maxX, s32 minY, s32 maxY, Color widgetColor)
{
    ls_uiBorder(cxt, xPos, yPos, w, h, minX, maxX, minY, maxY);
    ls_uiFillRect(cxt, xPos+1, yPos+1, w-2, h-2, minX, maxX, minY, maxY, widgetColor);
}

inline
void ls_uiBorderedRect(UIContext *cxt, s32 xPos, s32 yPos, s32 w, s32 h, 
                       s32 minX, s32 maxX, s32 minY, s32 maxY, Color widgetColor, Color borderColor)
{
    ls_uiBorder(cxt, xPos, yPos, w, h, minX, maxX, minY, maxY, borderColor);
    ls_uiFillRect(cxt, xPos+1, yPos+1, w-2, h-2, minX, maxX, minY, maxY, widgetColor);
}


#if 0
inline
void ls_uiBorderFrag(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h, RenderCommandExtra rce)
{
    Color C = c->borderColor;
    
    switch(rce)
    {
        case UI_RCE_LEFT:
        {
            ls_uiFillRect(c, xPos,     yPos,     w, 1, C);
            ls_uiFillRect(c, xPos,     yPos+h-1, w, 1, C);
            ls_uiFillRect(c, xPos,     yPos,     1, h, C);
        } break;
        
        case UI_RCE_RIGHT:
        {
            ls_uiFillRect(c, xPos,     yPos,     w, 1, C);
            ls_uiFillRect(c, xPos,     yPos+h-1, w, 1, C);
            ls_uiFillRect(c, xPos+w-1, yPos,     1, h, C);
        } break;
        
        case UI_RCE_TOP:
        {
            ls_uiFillRect(c, xPos,     yPos+h-1, w, 1, C);
            ls_uiFillRect(c, xPos,     yPos,     1, h, C);
            ls_uiFillRect(c, xPos+w-1, yPos,     1, h, C);
        } break;
        
        case UI_RCE_BOT:
        {
            ls_uiFillRect(c, xPos,     yPos,     1, h, C);
            ls_uiFillRect(c, xPos+w-1, yPos,     1, h, C);
            ls_uiFillRect(c, xPos,     yPos,     w, 1, C);
        } break;
        
        case UI_RCE_TL:
        {
            ls_uiFillRect(c, xPos,     yPos+h-1, w, 1, C);
            ls_uiFillRect(c, xPos,     yPos,     1, h, C);
        } break;
        
        case UI_RCE_TR:
        {
            ls_uiFillRect(c, xPos,     yPos+h-1, w, 1, C);
            ls_uiFillRect(c, xPos+w-1, yPos,     1, h, C);
        } break;
        
        case UI_RCE_BL:
        {
            ls_uiFillRect(c, xPos,     yPos,     w, 1, C);
            ls_uiFillRect(c, xPos,     yPos,     1, h, C);
        } break;
        
        case UI_RCE_BR:
        {
            ls_uiFillRect(c, xPos,     yPos,     w, 1, C);
            ls_uiFillRect(c, xPos+w-1, yPos,     1, h, C);
        } break;
        
        default: { AssertMsg(FALSE, "Unhandled rce case\n"); } break;
    }
}

inline
void ls_uiBorderedRectFrag(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h, 
                           Color widgetColor, Color borderColor, RenderCommandExtra rce)
{
    Color C = borderColor;
    Color W = widgetColor;
    
    switch(rce)
    {
        case UI_RCE_LEFT:
        {
            ls_uiFillRect(c, xPos,     yPos,     w,   1,   C);
            ls_uiFillRect(c, xPos,     yPos+h-1, w,   1,   C);
            ls_uiFillRect(c, xPos,     yPos,     1,   h,   C);
            ls_uiFillRect(c, xPos+1,   yPos+1,   w-1, h-2, W);
        } break;
        
        case UI_RCE_RIGHT:
        {
            ls_uiFillRect(c, xPos,     yPos,     w,   1,   C);
            ls_uiFillRect(c, xPos,     yPos+h-1, w,   1,   C);
            ls_uiFillRect(c, xPos+w-1, yPos,     1,   h,   C);
            ls_uiFillRect(c, xPos,     yPos+1,   w-1, h-2, W);
        } break;
        
        case UI_RCE_TOP:
        {
            ls_uiFillRect(c, xPos,     yPos+h-1, w,   1,   C);
            ls_uiFillRect(c, xPos,     yPos,     1,   h,   C);
            ls_uiFillRect(c, xPos+w-1, yPos,     1,   h,   C);
            ls_uiFillRect(c, xPos+1,   yPos,     w-2, h-1, W);
        } break;
        
        case UI_RCE_BOT:
        {
            ls_uiFillRect(c, xPos,     yPos,     w,   1,   C);
            ls_uiFillRect(c, xPos,     yPos,     1,   h,   C);
            ls_uiFillRect(c, xPos+w-1, yPos,     1,   h,   C);
            ls_uiFillRect(c, xPos+1,   yPos+1,   w-2, h-1, W);
        } break;
        
        case UI_RCE_TL:
        {
            ls_uiFillRect(c, xPos,     yPos+h-1, w,   1,   C);
            ls_uiFillRect(c, xPos,     yPos,     1,   h,   C);
            ls_uiFillRect(c, xPos+1,   yPos,     w-1, h-2, W);
        } break;
        
        case UI_RCE_TR:
        {
            ls_uiFillRect(c, xPos,     yPos+h-1, w,   1,   C);
            ls_uiFillRect(c, xPos+w-1, yPos,     1,   h,   C);
            ls_uiFillRect(c, xPos,     yPos,     w-2, h-2, W);
        } break;
        
        case UI_RCE_BL:
        {
            ls_uiFillRect(c, xPos,     yPos,     w,   1,   C);
            ls_uiFillRect(c, xPos,     yPos,     1,   h,   C);
            ls_uiFillRect(c, xPos+1,   yPos+1,   w-1, h-1, W);
        } break;
        
        case UI_RCE_BR:
        {
            ls_uiFillRect(c, xPos,     yPos,     w,   1,   C);
            ls_uiFillRect(c, xPos+w-1, yPos,     1,   h,   C);
            ls_uiFillRect(c, xPos,     yPos+1,   w-1, h-1, W);
        } break;
        
        default: { AssertMsg(FALSE, "Unhandled rce case\n"); } break;
    }
}

inline
void ls_uiBorderedRectFrag(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h, Color widgetColor, RenderCommandExtra rce)
{
    Color C = c->borderColor;
    Color W = widgetColor;
    
    ls_uiBorderedRectFrag(c, xPos, yPos, w, h, W, C, rce);
}

inline
void ls_uiBorderedRectFrag(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h, RenderCommandExtra rce)
{
    Color C = c->borderColor;
    Color W = c->widgetColor;
    
    ls_uiBorderedRectFrag(c, xPos, yPos, w, h, W, C, rce);
}

inline
void ls_uiRect(UIContext *cxt, s32 xPos, s32 yPos, s32 w, s32 h)
{
    ls_uiFillRect(cxt, xPos, yPos, w, h, cxt->widgetColor);
}

inline
void ls_uiRect(UIContext *cxt, s32 xPos, s32 yPos, s32 w, s32 h, Color widgetColor)
{
    ls_uiFillRect(cxt, xPos, yPos, w, h, widgetColor);
}


//NOTETODO Circle is not good. Not even working.
void _ls_uiCircle(UIContext *cxt, s32 xPos, s32 yPos, s32 selRadius)
{
    s32 radSq = selRadius*selRadius;
    
    auto getBest = [radSq](s32 x, s32 y, s32 *bX, s32 *bY)
    {
        s32 bestX = 0, bestY = 0, bestSum = 0;
        
        s32 rx = x+1;
        s32 ry = y;
        s32 sum = (rx*rx) + (ry*ry);
        if(sum <= radSq) { bestX = rx; bestY = ry; bestSum = sum; }
        
        rx = x;
        ry = y-1;
        sum = (rx*rx) + (ry*ry);
        if((sum <= radSq) && sum > bestSum) { bestX = rx; bestY = ry; bestSum = sum; }
        
        rx = x+1;
        ry = y-1;
        sum = (rx*rx) + (ry*ry);
        if((sum <= radSq) && sum > bestSum) { bestX = rx; bestY = ry; bestSum = sum; }
        
        *bX = bestX;
        *bY = bestY;
    };
    
    f64 sin = 0, cos = 0;
    
    //NOTE: Everything is done relative to (0,0) until when drawing happens
    //NOTE: We start at the top middle pixel of the Circle
    s32 startX = 0;
    s32 startY = selRadius;
    
    //NOTE: And end at the first octant swept going clockwise.
    ls_sincos(PI/4.0, &sin, &cos);
    s32 endX = (cos*selRadius);
    s32 endY = (sin*selRadius);
    
    s32 currX = startX;
    s32 currY = startY;
    
    UIScissor::UIRect *scRect = cxt->scissor.currRect;
    u32 *At = (u32 *)cxt->drawBuffer;
    
    Color bCol   = cxt->borderColor;
    
    //TODO: Should be SIMDable
    b32 Running = TRUE;
    while(Running)
    {
        if((currX == endX) || (currY == endY)) { Running = FALSE; }
        
        s32 drawX1 = xPos + currX; s32 drawY1 = yPos + currY;
        s32 drawX2 = xPos - currX; s32 drawY2 = yPos + currY;
        s32 drawX3 = xPos + currY; s32 drawY3 = yPos + currX;
        s32 drawX4 = xPos - currY; s32 drawY4 = yPos + currX;
        s32 drawX5 = xPos + currX; s32 drawY5 = yPos - currY;
        s32 drawX6 = xPos - currX; s32 drawY6 = yPos - currY;
        s32 drawX7 = xPos + currY; s32 drawY7 = yPos - currX;
        s32 drawX8 = xPos - currY; s32 drawY8 = yPos - currX;
        
        
        s32 nextX = 0, nextY = 0;
        
        getBest(currX, currY, &nextX, &nextY);
        
        currX = nextX;
        currY = nextY;
        
#define CIRCLE_DRAW_BORD(xP, yP, r, c) \
if((xP) >= r->x && (xP) < r->x+r->w && (yP) >= r->y && (yP) < r->y+r->h) \
{ At[(yP)*cxt->width + (xP)] = c; }
        
        CIRCLE_DRAW_BORD(drawX1, drawY1,   scRect, bCol);
        //CIRCLE_DRAW_BORD(drawX1, drawY1-1, scRect, bCol);
        CIRCLE_DRAW_BORD(drawX2, drawY2,   scRect, bCol);
        //CIRCLE_DRAW_BORD(drawX2, drawY2-1, scRect, bCol);
        
        //ls_uiFillRect(cxt, drawX2+1, drawY2-1, (drawX1-drawX2)-1, 1, cxt->widgetColor);
        ls_uiFillRect(cxt, drawX2+1, drawY2, (drawX1-drawX2)-1, 1, cxt->widgetColor);
        
        
        CIRCLE_DRAW_BORD(drawX3,   drawY3, scRect, bCol);
        //CIRCLE_DRAW_BORD(drawX3-1, drawY3, scRect, bCol);
        CIRCLE_DRAW_BORD(drawX4,   drawY4, scRect, bCol);
        //CIRCLE_DRAW_BORD(drawX4+1, drawY4, scRect, bCol);
        
        //ls_uiFillRect(cxt, drawX4+2, drawY4, (drawX3-drawX4)-3, 1, cxt->widgetColor);
        ls_uiFillRect(cxt, drawX4+1, drawY4, (drawX3-drawX4)-1, 1, cxt->widgetColor);
        
        CIRCLE_DRAW_BORD(drawX5, drawY5,   scRect, bCol);
        //CIRCLE_DRAW_BORD(drawX5, drawY5+1, scRect, bCol);
        CIRCLE_DRAW_BORD(drawX6, drawY6,   scRect, bCol);
        //CIRCLE_DRAW_BORD(drawX6, drawY6+1, scRect, bCol);
        
        //ls_uiFillRect(cxt, drawX6+1, drawY6+1, (drawX5-drawX6)-1, 1, cxt->widgetColor);
        ls_uiFillRect(cxt, drawX6+1, drawY6, (drawX5-drawX6)-1, 1, cxt->widgetColor);
        
        CIRCLE_DRAW_BORD(drawX7,   drawY7, scRect, bCol);
        //CIRCLE_DRAW_BORD(drawX7-1, drawY7, scRect, bCol);
        CIRCLE_DRAW_BORD(drawX8,   drawY8, scRect, bCol);
        //CIRCLE_DRAW_BORD(drawX8+1, drawY8, scRect, bCol);
        
        //ls_uiFillRect(cxt, drawX8+2, drawY8, (drawX7-drawX8)-3, 1, cxt->widgetColor);
        ls_uiFillRect(cxt, drawX8+1, drawY8, (drawX7-drawX8)-1, 1, cxt->widgetColor);
    }
#undef CIRCLE_DRAW_BORD
}


//NOTETODO Circle is not good. Not even working
void _ls_uiCircleFloat(UIContext *cxt, s32 xPos, s32 yPos, s32 selRadius)
{
    f64 radSq = selRadius*selRadius;
    f64 sin = 0, cos = 0;
    
    //NOTE: Everything is done relative to (0,0) until when drawing happens
    //NOTE: We start at the top middle pixel of the Circle
    f64 startX = 0.0;
    f64 startY = selRadius;
    
    //NOTE: And end at the first octant swept going clockwise.
    
    f64 currX = startX;
    f64 currY = startY;
    
    UIScissor::UIRect *scRect = cxt->scissor.currRect;
    u32 *At = (u32 *)cxt->drawBuffer;
    
    for(f64 Angle = 0.0; Angle < TAU; Angle += TAU/360.0)
    {
        ls_sincos(Angle, &sin, &cos);
        
        startX = cos*selRadius;
        startY = sin*selRadius;
        
        s32 x1  = ls_floor(startX);
        f64 floatXA1 = 1.0 - ls_fabs(startX - x1);
        
        s32 x2 = ls_ceil(startX);
        f64 floatXA2 = 1.0 - ls_fabs(startX - x2);
        
        s32 y1 = ls_floor(startY);
        f64 floatYA1 = 1.0 - ls_fabs(startY - y1);
        
        s32 y2 = ls_ceil(startY);
        f64 floatYA2 = 1.0 - ls_fabs(startY - y2);
        
        s32 alpha1 = (s32)((floatXA1*floatYA1)*255);
        s32 alpha2 = (s32)((floatXA2*floatYA2)*255);
        
        s32 alpha3 = (s32)((floatXA1*floatYA2)*255);
        s32 alpha4 = (s32)((floatXA2*floatYA1)*255);
        
        Color c1 = ls_uiAlphaBlend(cxt->borderColor, cxt->backgroundColor, alpha1);
        Color c2 = ls_uiAlphaBlend(cxt->borderColor, cxt->backgroundColor, alpha2);
        
        Color c3 = ls_uiAlphaBlend(cxt->borderColor, cxt->backgroundColor, alpha3);
        Color c4 = ls_uiAlphaBlend(cxt->borderColor, cxt->backgroundColor, alpha4);
        
#define CIRCLE_DRAW_BORD(xP, yP, r, c) \
if((xP) >= r->x && (xP) < r->x+r->w && (yP) >= r->y && (yP) < r->y+r->h) \
{ At[(yP)*cxt->width + (xP)] = c; }
        
        CIRCLE_DRAW_BORD(xPos+x1, yPos+y1, scRect, c1);
        CIRCLE_DRAW_BORD(xPos+x2, yPos+y2, scRect, c2);
        
        CIRCLE_DRAW_BORD(xPos+x1, yPos+y2, scRect, c3);
        CIRCLE_DRAW_BORD(xPos+x2, yPos+y1, scRect, c4);
        
#undef CIRCLE_DRAW_BORD
    }
    
}
#endif //if 0 from border

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

void ls_uiBitmap(UIContext *cxt, s32 xPos, s32 yPos, u32 *data, s32 w, s32 h)
{
    UIScissor::UIRect *scRect = cxt->scissor.currRect;
    
    u32 *At = (u32 *)cxt->drawBuffer;
    
    for(s32 y = yPos, eY = 0; y < yPos+h; y++, eY++)
    {
        for(s32 x = xPos, eX = 0; x < xPos+w; x++, eX++)
        {
            if(x < 0 || x >= cxt->width)  continue;
            if(y < 0 || y >= cxt->height) continue;
            
            if(x < scRect->x || x >= scRect->x+scRect->w) continue;
            if(y < scRect->y || y >= scRect->y+scRect->h) continue;
            
            At[y*cxt->width + x] = data[eY*w + eX];
        }
    }
}

void ls_uiGlyph(UIContext *c, s32 xPos, s32 yPos, s32 minX, s32 minY, s32 maxX, s32 maxY, UIGlyph *glyph, Color textColor)
{
    u32 *At = (u32 *)c->drawBuffer;
    
    s32 startY = yPos-glyph->y1;
    s32 eY = glyph->height-1;
    if(startY < minY) { eY -= (minY - startY); startY = minY; }
    
    for(s32 y = startY; eY >= 0; y++, eY--)
    {
        if(y > maxY) break;
        
        s32 startX = xPos+glyph->x0;
        s32 eX = 0;
        if(startX < minX) { eX += (minX - startX); startX = minX; }
        
        for(s32 x = startX; eX < glyph->width; x++, eX++)
        {
            if(x > maxX) break;
            
            if(x < 0 || x >= c->width)  continue;
            if(y < 0 || y >= c->height) continue;
            
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


s32 ls_uiGetKernAdvance(UIContext *cxt, s32 codepoint1, s32 codepoint2)
{
    UIFont *font = cxt->currFont;
    s32 kernAdvance = font->kernAdvanceTable[codepoint1][codepoint2];
    
    return kernAdvance;
}

void ls_uiRenderStringOnRect(UIContext *c, UITextBox *box, s32 xPos, s32 yPos, s32 w, s32 h, 
                             s32 minX, s32 maxX, s32 minY, s32 maxY,
                             s32 cIdx, Color textColor, Color invTextColor)
{
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
    
    u32 i = 0;
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
    
    unistring realString = { box->text.data + i, box->text.len - i, box->text.size - i };
    uview lineView = ls_uviewCreate(realString);
    
    for(u32 lineIdx = 0; lineIdx < (box->lineCount+1-yOffset); lineIdx++)
    {
        lineView = ls_uviewNextLine(lineView);
        unistring line = lineView.s;
        
        i += xOffset;
        u32 lIdx = xOffset;
        s32 caretX = currXPos-3;
        for(; lIdx < line.len; lIdx++, i++)
        {
            if((lineIdx == box->caretLineIdx) && (cIdx == lIdx)) { caretX = currXPos-3; }
            if(currXPos >= strMaxX) { i += line.len - lIdx; break; }
            
            code = line.data[lIdx];
            AssertMsg(code <= c->currFont->maxCodepoint, "GlyphIndex OutOfBounds\n");
            
#ifdef _DEBUG
            if(code == (char32_t)'\n')
            {
                ls_uiFillRect(c, currXPos+4, currYPos-2, 10, 14, minX, maxX, minY, maxY, RGB(200, 10, 10));
            }
            else
#endif
            {
                Color actualColor = textColor;
                UIGlyph *currGlyph = &c->currFont->glyph[code];
                
                //TODO: Pretty inefficient to keep redrawing the background all the time.
                if(box->isSelecting && (box->selectBeginLine <= lineIdx) && (box->selectEndLine >= lineIdx)
                   && (box->selectBeginIdx <= i) && (box->selectEndIdx > i))
                { 
                    actualColor = invTextColor;
                    ls_uiFillRect(c, currXPos, currYPos, currGlyph->xAdv, lineHeight-vertGlyphOff, 
                                  minX, maxX, minY, maxY, c->invWidgetColor);
                }
                
                ls_uiGlyph(c, currXPos, currYPos+vertGlyphOff, minX, minY, maxX, maxY, currGlyph, actualColor);
                
                s32 kernAdvance = 0;
                if(lIdx < line.len-1) { kernAdvance = ls_uiGetKernAdvance(c, line.data[lIdx], line.data[lIdx+1]); }
                currXPos += (currGlyph->xAdv + kernAdvance);
            }
        }
        
        if(((lineIdx == box->caretLineIdx) && cIdx == line.len)) { caretX = currXPos-3; }
        
        if((cIdx != -1) && (lineIdx == box->caretLineIdx))
        {
            UIGlyph *currGlyph = &c->currFont->glyph[(char32_t)'|'];
            ls_uiGlyph(c, caretX, currYPos+vertGlyphOff, minX, minY, maxX, maxY, currGlyph, textColor);
        }
        
        
        currYPos -= lineHeight;
        currXPos  = xPos;
    }
    
}

#if 0
//TODO: Use font max descent to determine yOffsets globally
void ls_uiGlyphString(UIContext *c, s32 xPos, s32 yPos, unistring text, Color textColor)
{
    s32 currXPos = xPos;
    for(u32 i = 0; i < text.len; i++)
    {
        u32 indexInGlyphArray = text.data[i];
        AssertMsg(indexInGlyphArray <= c->currFont->maxCodepoint, "GlyphIndex OutOfBounds\n");
        
        UIGlyph *currGlyph = &c->currFont->glyph[indexInGlyphArray];
        ls_uiGlyph(c, currXPos, yPos, currGlyph, textColor);
        
        s32 kernAdvance = 0;
        if(i < text.len-1) { kernAdvance = ls_uiGetKernAdvance(c, text.data[i], text.data[i+1]); }
        
        currXPos += (currGlyph->xAdv + kernAdvance);
    }
}

void ls_uiGlyphStringFrag(UIContext *c, s32 xPos, s32 yPos, s32 oX, s32 oY, 
                          s32 minX, s32 minY, s32 maxX, s32 maxY, 
                          unistring text, Color textColor)
{
    //TODO: Pre-skip the glyphs that appear before (minX,minY)
    s32 currXPos = xPos;
    for(u32 i = 0; i < text.len; i++)
    {
        u32 indexInGlyphArray = text.data[i];
        AssertMsg(indexInGlyphArray <= c->currFont->maxCodepoint, "GlyphIndex OutOfBounds\n");
        
        UIGlyph *currGlyph = &c->currFont->glyph[indexInGlyphArray];
        ls_uiGlyphFrag(c, currXPos, yPos, oX, oY, minX, minY, maxX, maxY, currGlyph, textColor);
        
        s32 kernAdvance = 0;
        if(i < text.len-1) { kernAdvance = ls_uiGetKernAdvance(c, text.data[i], text.data[i+1]); }
        
        currXPos += (currGlyph->xAdv + kernAdvance);
    }
}
#endif

s32 ls_uiGlyphStringLen(UIContext *c, unistring text)
{
    s32 totalLen = 0;
    for(u32 i = 0; i < text.len; i++)
    {
        u32 indexInGlyphArray = text.data[i];
        AssertMsg(indexInGlyphArray <= c->currFont->maxCodepoint, "GlyphIndex OutOfBounds\n");
        
        UIGlyph *currGlyph = &c->currFont->glyph[indexInGlyphArray];
        
        s32 kernAdvance = 0;
        if(i < text.len-1) { kernAdvance = ls_uiGetKernAdvance(c, text.data[i], text.data[i+1]); }
        
        totalLen += (currGlyph->xAdv + kernAdvance);
    }
    
    return totalLen;
}

s32 ls_uiGlyphStringFit(UIContext *c, unistring text, s32 maxLen)
{
    s32 totalLen = 0;
    for(s32 i = text.len-1; i > 0; i--)
    {
        u32 indexInGlyphArray = text.data[i];
        AssertMsg(indexInGlyphArray <= c->currFont->maxCodepoint, "GlyphIndex OutOfBounds\n");
        
        UIGlyph *currGlyph = &c->currFont->glyph[indexInGlyphArray];
        
        s32 kernAdvance = 0;
        if(i > 0) { kernAdvance = ls_uiGetKernAdvance(c, text.data[i-1], text.data[i]); }
        
        totalLen += (currGlyph->xAdv + kernAdvance);
        if(totalLen >= maxLen) { return i; }
    }
    
    return 0;
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

//TODO:Button autosizing width
//TODO:Menus use buttons, but also claim Focus, which means I can't use the global focus trick to avoid input
//     handling between overlapping elements.
//     I don't think the menu should deal with things like this [It shouldn't hold the close button first,
//     and it also shouldn't use 'normal' buttons for its drop down sub-menus, so... basically @MenuIsShit
//     and I wanna redo it completely.
b32 ls_uiButton(UIContext *c, UIButton *button, s32 xPos, s32 yPos, s32 w, s32 h, s32 zLayer = 0)
{
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

void ls_uiLabel(UIContext *c, unistring label, s32 xPos, s32 yPos, u32 zLayer = 0)
{
    
    RenderCommand command = { UI_RC_LABEL, xPos, yPos };
    command.label = (char32_t*)label.data;
    command.textColor = c->textColor;
    ls_uiPushRenderCommand(c, command, zLayer);
    
#if 0
    s32 strPixelHeight = ls_uiSelectFontByFontSize(c, FS_SMALL);
    
    s32 strWidth = ls_uiGlyphStringLen(c, label);
    
    ls_uiPushScissor(c, xPos, yPos-4, strWidth, strPixelHeight+8);
    
    ls_uiGlyphString(c, xPos, yPos, label, c->textColor);
    
    ls_uiPopScissor(c);
#endif
}

void ls_uiLabel(UIContext *c, const char32_t *label, s32 xPos, s32 yPos, u32 zLayer = 0)
{
    unistring lab = ls_unistrConstant(label);
    ls_uiLabel(c, lab, xPos, yPos, zLayer);
}

void ls_uiTextBoxClear(UIContext *c, UITextBox *box)
{
    ls_unistrClear(&box->text);
    
    box->caretIndex     = 0;
    box->isReadonly     = FALSE;
    box->selectBeginIdx = 0;
    box->selectEndIdx   = 0;
    box->isSelecting    = FALSE;
    box->viewBeginIdx   = 0;
    box->viewEndIdx     = 0;
}

void ls_uiTextBoxSet(UIContext *c, UITextBox *box, unistring s)
{
    ls_unistrSet(&box->text, s);
    box->viewEndIdx = box->text.len;
}

//TODO: Text Alignment
//TODO: Apron when moving Left/Right
//TODO: When moving left/right special characters (like newlines) should be skipped.
//TODO: In small boxes the newline fucks up rendering of the caret
b32 ls_uiTextBox(UIContext *c, UITextBox *box, s32 xPos, s32 yPos, s32 w, s32 h)
{
    b32 inputUse = FALSE;
    
    if(LeftClickIn(xPos, yPos, w, h) && (box->isReadonly == FALSE) && ls_uiHasCapture(c, 0)) {
        c->currentFocus = (u64 *)box;
        c->focusWasSetThisFrame = TRUE;
        box->isCaretOn = TRUE; 
    }
    
    const s32 horzOff   = 8;
    const s32 viewAddWidth    = w - 2*horzOff;
    //ls_uiPushScissor(cxt, xPos+4, yPos, scissorWidth, h);
    
    auto setIndices = [c, box, viewAddWidth](s32 index) -> u32 {
        
        if(index <= 0) { 
            box->viewBeginIdx = 0; 
            box->viewEndIdx = 0;
            
            //TODONOTE: Very wrong.
            if(box->text.data[0] == (char32_t)'\n') return 1;
            return 0;
        }
        
        u32 beginOffset    = ls_unistrRightFind(box->text, index, (char32_t)'\n');
        
        s32 realOffset = beginOffset+1;
        if(beginOffset == -1) { realOffset = 0; }
        
        u32 lineLength     = index-realOffset;
        
        unistring currLine = { box->text.data + realOffset, lineLength, lineLength };
        u32 maxBeginIndex  = ls_uiGlyphStringFit(c, currLine, viewAddWidth);
        
        box->viewBeginIdx  = maxBeginIndex;
        
        //NOTE:TODO: As of right now viewEndIdx does absolutely nothing.
        box->viewEndIdx    = 0xFEFEFE; // = lineLength; //TODONOTE Strange that an idx == lenght.
        
        return realOffset;
    };
    
    auto handleSelection = [box](s32 direction) {
        
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
        
        ls_unistrRmSubstr(&box->text, box->selectBeginIdx, box->selectEndIdx-1);
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
            
            if(box->caretIndex == box->text.len) { ls_unistrAppendChar(&box->text, GetPrintableKey()); }
            else { ls_unistrInsertChar(&box->text, GetPrintableKey(), box->caretIndex); }
            
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
                
                if(box->caretIndex == box->text.len) { ls_unistrTrimRight(&box->text, 1); }
                else { ls_unistrRmIdx(&box->text, box->caretIndex-1); }
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
                
                if(box->caretIndex == box->text.len-1) { ls_unistrTrimRight(&box->text, 1); }
                else { ls_unistrRmIdx(&box->text, box->caretIndex); }
                
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
            
            u32 realCopyLen = copiedLen;
            
            //NOTE: maxLen == 0 means there's no max len.
            if(box->maxLen != 0) 
            {
                if(box->text.len + copiedLen > box->maxLen) {
                    if(box->text.len < box->maxLen) { realCopyLen = box->maxLen - box->text.len; }
                    else { realCopyLen = 0; }
                }
            }
            
            u32 addedLines = ls_unistrCountOccurrences({buff, realCopyLen, realCopyLen}, (u32)'\n');
            
            //NOTE: Skip if box is single line and you're trying to paste a multiline text.
            if(addedLines > 0 && box->isSingleLine) { goto goto_skip_to_post_input; }
            
            if(box->caretIndex == box->text.len) { ls_unistrAppendBuffer(&box->text, buff, realCopyLen); }
            else { ls_unistrInsertBuffer(&box->text, buff, realCopyLen, box->caretIndex); }
            
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
        
        
        if(box->postInput) 
        { inputUse |= box->postInput(c, box->data); }
    }
    
    RenderCommand command = {UI_RC_TESTBOX, xPos, yPos, w, h, 0, 0, 0, 0, box, c->widgetColor, c->textColor};
    //RenderCommand command = {UI_RC_TEXTBOX, xPos, yPos, w, h, box, c->widgetColor, c->textColor};
    ls_uiPushRenderCommand(c, command, 0);
    
    return inputUse;
}

#if 0
void ls_uiDrawArrow(UIContext *cxt, s32 x, s32 yPos, s32 w, s32 h, Color bkgColor, UIArrowSide s)
{
    UIScissor::UIRect *scRect = cxt->scissor.currRect;
    u32 *At = (u32 *)cxt->drawBuffer;
    
    s32 xPos = x-1;
    
    ls_uiBorderedRect(cxt, xPos, yPos, w, h, bkgColor);
    
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
        
        for(s32 y = yStart; y >= yEnd; y--)
        {
            for(s32 x = xBase; x < xEnd; x++)
            {
                if(x < 0 || x >= cxt->width)  continue;
                if(y < 0 || y >= cxt->height) continue;
                
                if(x < scRect->x || x >= scRect->x+scRect->w) continue;
                if(y < scRect->y || y >= scRect->y+scRect->h) continue;
                
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
        
        for(s32 y = yStart1; y >= yEnd1; y--)
        {
            for(s32 x = xBase; x < xEnd; x++)
            {
                if(x < 0 || x >= cxt->width)  continue;
                if(y < 0 || y >= cxt->height) continue;
                
                if(x < scRect->x || x >= scRect->x+scRect->w) continue;
                if(y < scRect->y || y >= scRect->y+scRect->h) continue;
                
                At[y*cxt->width + x] = RGBg(0x00);
            }
            
            xEnd  += 1;
        }
        
        xEnd -= 1;
        for(s32 y = yStart2; y >= yEnd2; y--)
        {
            for(s32 x = xBase; x < xEnd; x++)
            {
                if(x < 0 || x >= cxt->width)  continue;
                if(y < 0 || y >= cxt->height) continue;
                
                if(x < scRect->x || x >= scRect->x+scRect->w) continue;
                if(y < scRect->y || y >= scRect->y+scRect->h) continue;
                
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
        
        for(s32 y = yStart1; y >= yEnd1; y--)
        {
            for(s32 x = xBase; x < xEnd; x++)
            {
                if(x < 0 || x >= cxt->width)  continue;
                if(y < 0 || y >= cxt->height) continue;
                
                if(x < scRect->x || x >= scRect->x+scRect->w) continue;
                if(y < scRect->y || y >= scRect->y+scRect->h) continue;
                
                At[y*cxt->width + x] = RGBg(0x00);
            }
            
            xBase -= 1;
        }
        
        xBase += 1;
        for(s32 y = yStart2; y >= yEnd2; y--)
        {
            for(s32 x = xBase; x < xEnd; x++)
            {
                if(x < 0 || x >= cxt->width)  continue;
                if(y < 0 || y >= cxt->height) continue;
                
                if(x < scRect->x || x >= scRect->x+scRect->w) continue;
                if(y < scRect->y || y >= scRect->y+scRect->h) continue;
                
                At[y*cxt->width + x] = RGBg(0x00);
            }
            
            xBase += 1;
        }
    }
}


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
    unistring text = ls_unistrFromAscii(s);
    UIListBoxItem item = { text, cxt->widgetColor, cxt->textColor };
    
    return list->list.push(item);
}

inline u32 ls_uiListBoxAddEntry(UIContext *cxt, UIListBox *list, unistring s)
{
    UIListBoxItem item = { s, cxt->widgetColor, cxt->textColor };
    return list->list.push(item); 
}

inline void ls_uiListBoxRemoveEntry(UIContext *cxt, UIListBox *list, u32 index)
{ 
    //NOTETODO: Is this good????
    if(list->selectedIndex == index) { list->selectedIndex = 0; }
    
    UIListBoxItem val = list->list[index];
    ls_unistrFree(&val.name);
    list->list.remove(index);
}

b32 ls_uiListBox(UIContext *c, UIListBox *list, s32 xPos, s32 yPos, s32 w, s32 h, u32 zLayer = 0)
{
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
                UIListBoxItem *currItem = list->list.getPointer(i);
                
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
    
    if(name) { Result.text = ls_unistrFromUTF32((const char32_t *)name); }
    else     { Result.text = ls_unistrAlloc(16); }
    
    Result.maxValue = maxVal;
    Result.minValue = minVal;
    Result.currPos  = currPos;
    Result.style    = s;
    Result.lColor   = l;
    Result.rColor   = r;
    
    return Result;
}

void ls_uiSliderChangeValueBy(UIContext *cxt, UISlider *f, s32 valueDiff)
{
    s32 newValue = f->currValue + valueDiff;
    
    if(newValue <= f->minValue) { newValue = f->minValue; }
    if(newValue >= f->maxValue) { newValue = f->maxValue; }
    
    s32 range = (f->maxValue - f->minValue);
    f->currPos = (f64)(newValue - f->minValue) / (f64)range;
    
    return;
}

s32 ls_uiSliderGetValue(UIContext *cxt, UISlider *f)
{
    return ((f->maxValue - f->minValue) * f->currPos) + f->minValue;
}

//TODO: The things are rendered in a logical order, but that makes the function's flow very annoying
//      going in and out of if blocks to check hot/held and style.
b32 ls_uiSlider(UIContext *cxt, UISlider *slider, s32 xPos, s32 yPos, s32 w, s32 h)
{
    if(LeftUp) { slider->isHeld = FALSE; }
    
    if(slider->style == SL_BOX)
    {
        slider->currValue = ((slider->maxValue - slider->minValue) * slider->currPos) + slider->minValue;
        s32 slidePos = w*slider->currPos;
        
        if(MouseInRect(xPos + slidePos-5, yPos, 10, h) && !(cxt->mouseCapture != 0 && cxt->mouseCapture != (u64 *)slider))
        {
            slider->isHot = TRUE;
            if(LeftHold) { slider->isHeld = TRUE; cxt->mouseCapture = (u64 *)slider; }
        }
    }
    else if(slider->style == SL_LINE)
    { AssertMsg(FALSE, "Slider style line is not implemented\n"); }
    
    b32 hasAnsweredToInput = FALSE;
    
    if(slider->isHeld) { 
        s32 deltaX = (UserInput.Mouse.prevPosX - UserInput.Mouse.currPosX);//*cxt->dt;
        
        f64 fractionMove = (f64)deltaX / (f64)w;
        
        slider->currPos -= fractionMove;
        
        slider->currPos = ls_mathClamp(slider->currPos, 1.0, 0.0);
        
        hasAnsweredToInput = TRUE;
    }
    
    RenderCommand command = { UI_RC_SLIDER, xPos, yPos, w, h };
    command.slider = slider;
    
    ls_uiPushRenderCommand(cxt, command, 0);
    
    return hasAnsweredToInput;
}


//NOTETODO: This is bad. Either it's a real default, then it should be auto set, or it's not
//          then it shouldn't be here!
b32 ls_uiMenuDefaultOnClick(UIContext *cxt, void *data)
{
    b32 inputUse = FALSE;
    
    __UImenuDataPass *pass = (__UImenuDataPass *)data;
    
    UIMenu *menu  = pass->menu;
    
    menu->isOpen  = !menu->isOpen;
    menu->openIdx = pass->idx;
    
    return inputUse;
}

void ls_uiMenuAddItem(UIMenu *menu, UIButton b)
{
    if(b.onClick == ls_uiMenuDefaultOnClick)
    {
        //TODO: I hate having to allocate data for this. I also need a way to deallocate it!
        //      @Leak @Memory
        __UImenuDataPass *pass = (__UImenuDataPass *)ls_alloc(sizeof(__UImenuDataPass));
        pass->menu = menu;
        pass->idx = menu->items.count;
        b.data = pass;
    }
    
    menu->items.push(b);
}

//TODO This is completely unnecessary
void ls_uiMenuAddSub(UIMenu *menu, UIMenu sub, s32 idx)
{ menu->sub[idx] = sub; }

//TODO: @MenuIsShit it shouldn't use buttons like this, and shouldn't hold the close button hostage.
b32 ls_uiMenu(UIContext *c, UIMenu *menu, s32 x, s32 y, s32 w, s32 h)
{
    b32 inputUse = FALSE;
    
    if(LeftClickIn(x, y, w, h)) {
        c->currentFocus = (u64 *)menu;
        c->focusWasSetThisFrame = TRUE;
    }
    
    if(c->currentFocus != (u64 *)menu) { menu->isOpen = FALSE; }
    
    RenderCommand commandFirst = { UI_RC_RECT, x, y, w, h };
    commandFirst.bkgColor  = c->backgroundColor;
    commandFirst.textColor = RGBg(110); //TODO: Hardcoded
    ls_uiPushRenderCommand(c, commandFirst, 1);
    
    ls_uiButton(c, &menu->closeWindow, x+w-20, y+2, 16, 16, 2);
    
    s32 xOff = 100;
    for(u32 i = 0; i < menu->items.count; i++)
    {
        UIButton *currItem = &menu->items[i];
        ls_uiButton(c, currItem, x+xOff, y+1, 100, 19, 2);
        xOff += 100;
    }
    
    if(menu->isOpen == TRUE)
    {
        UIButton *openItem = &menu->items[menu->openIdx];
        UIMenu *openSub = menu->sub + menu->openIdx;
        
        AssertMsg(openItem, "The item doesn't exist\n");
        AssertMsg(openSub, "The sub-menu doesn't exist\n");
        
        s32 yPos      = y-20;
        s32 height = openSub->items.count*20;
        
        RenderCommand command = { UI_RC_RECT, 100 + x + 100*menu->openIdx, y-height-2, 102, height+3 };
        command.bkgColor  = c->backgroundColor;
        command.textColor = c->borderColor;
        ls_uiPushRenderCommand(c, command, 1);
        
        //TODO: Store the xPos of every menu item.
        for(u32 i = 0; i < openSub->items.count; i++)
        {
            UIButton *currItem = &openSub->items[i];
            inputUse = ls_uiButton(c, currItem, 100 + 100*menu->openIdx, yPos, 100, 20, 2);
            yPos -= 21;
        }
    }
    
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
            s32 xPos        = curr->x;
            s32 yPos        = curr->y;
            s32 w           = curr->w;
            s32 h           = curr->h;
            
            s32 minX        = curr->minX;
            s32 maxX        = curr->maxX;
            s32 minY        = curr->minY;
            s32 maxY        = curr->maxY;
            
            Color bkgColor  = curr->bkgColor;
            Color textColor = curr->textColor;
            
            switch(curr->type)
            {
#if 0
                case UI_RC_LABEL:
                {
                    
                    unistring label = ls_unistrConstant(curr->label);
                    
                    s32 strPixelHeight = ls_uiSelectFontByFontSize(c, FS_SMALL);
                    
                    ls_uiGlyphString(c, xPos, yPos, label, textColor);
                    
                } break;
#endif
                case UI_RC_TESTBOX:
                {
                    UITextBox *box = curr->textBox;
                    
                    Color caretColor = textColor;
                    const s32 horzOff = 4;
                    
                    //TODO: Make the font selection more of a global thing??
                    s32 strPixelHeight = ls_uiSelectFontByFontSize(c, FS_SMALL);
                    
                    ls_uiBorderedRect(c, xPos, yPos, w, h, minX, maxX, minY, maxY, bkgColor);
                    
                    s32 strX = xPos + horzOff;
                    s32 strY = yPos + h - strPixelHeight;
                    
                    //NOTETODO: For now we double draw for selected strings. We can improve with 3-segment drawing.
                    if(box->isCaretOn && c->currentFocus == (u64 *)box)
                    { ls_uiRenderStringOnRect(c, box, strX, strY, w, h,
                                              minX, maxX, minY, maxY,
                                              box->caretIndex-box->currLineBeginIdx, textColor, c->invTextColor); }
                    else
                    { ls_uiRenderStringOnRect(c, box, strX, strY, w, h,
                                              minX, maxX, minY, maxY,
                                              -1, textColor, c->invTextColor); }
                    
                } break;
#if 0
                case UI_RC_TEXTBOX:
                {
                    UITextBox *box = curr->textBox;
                    
                    Color caretColor = textColor;
                    const s32 horzOff = 4;
                    
                    //TODO: Make the font selection more of a global thing??
                    s32 strPixelHeight = ls_uiSelectFontByFontSize(c, FS_SMALL);
                    
                    ls_uiBorderedRect(c, xPos, yPos, w, h, bkgColor);
                    
                    s32 vertOff = ((h - strPixelHeight) / 2) + 5; //TODO: @FontDescent
                    u32 viewLen = box->viewEndIdx - box->viewBeginIdx;
                    u32 actualViewLen = viewLen <= box->text.len ? viewLen : box->text.len;
                    unistring viewString = {box->text.data + box->viewBeginIdx, actualViewLen, actualViewLen};
                    
                    //NOTE: Finally draw the entire string.
                    ls_uiGlyphString(c, xPos + horzOff, yPos + vertOff, viewString, textColor);
                    
                    if(box->isSelecting)
                    {
                        //TODO: Draw this more efficiently by drawing text in 3 different non-overlapping calls??
                        s32 viewSelBegin = box->selectBeginIdx;
                        if(viewSelBegin <= box->viewBeginIdx) { viewSelBegin = box->viewBeginIdx; }
                        
                        s32 viewSelEnd = box->selectEndIdx;
                        if(box->viewEndIdx != 0 && viewSelEnd >= box->viewEndIdx) { viewSelEnd = box->viewEndIdx; }
                        
                        u32 selLen = viewSelEnd -  viewSelBegin;
                        unistring selString = {box->text.data + viewSelBegin, selLen, selLen};
                        s32 selStringWidth  = ls_uiGlyphStringLen(c, selString);
                        
                        u32 diffLen = 0;
                        if(box->selectBeginIdx > box->viewBeginIdx) { diffLen = box->selectBeginIdx - box->viewBeginIdx; }
                        
                        unistring diffString = { box->text.data + box->viewBeginIdx, diffLen, diffLen };
                        s32 diffStringWidth = ls_uiGlyphStringLen(c, diffString);
                        
                        ls_uiFillRect(c, xPos + horzOff + diffStringWidth, yPos+1, selStringWidth, h-2, c->invWidgetColor);
                        ls_uiGlyphString(c, xPos + horzOff + diffStringWidth, yPos + vertOff, selString, c->invTextColor);
                        
                        if(box->caretIndex == box->selectBeginIdx)
                        { caretColor = c->invTextColor; }
                    }
                    
                    //NOTE: Draw the Caret
                    if(box->isCaretOn && c->currentFocus == (u64 *)box)
                    {
                        UIGlyph *caretGlyph = &c->currFont->glyph['|'];
                        
                        u32 caretIndexInView = box->caretIndex - box->viewBeginIdx;
                        unistring tmp = {viewString.data, caretIndexInView, caretIndexInView};
                        
                        u32 stringLen = ls_uiGlyphStringLen(c, tmp);
                        
                        const s32 randffset = 4; //TODO: Maybe try to remove this?
                        ls_uiGlyph(c, xPos + horzOff + stringLen - randffset, yPos+vertOff, caretGlyph, caretColor);
                    }
                    
                } break;
                
                case UI_RC_LISTBOX:
                {
                    UIListBox *list = curr->listBox;
                    
                    s32 strHeight = ls_uiSelectFontByFontSize(c, FS_SMALL);
                    s32 vertOff = ((h - strHeight) / 2) + 4; //TODO: @FontDescent
                    
                    ls_uiBorderedRect(c, xPos, yPos, w, h);
                    
                    if(list->list.count)
                    {
                        unistring selected = list->list[list->selectedIndex].name;
                        ls_uiGlyphString(c, xPos+10, yPos + vertOff, selected, c->textColor);
                    }
                    
                    
                    s32 maxHeight = (list->list.count)*h;
                    if(list->isOpening)
                    {
                        s32 height = 0;
                        if(list->dtOpen > 17)  { height = maxHeight*0.10f; }
                        if(list->dtOpen > 34)  { height = maxHeight*0.35f; }
                        if(list->dtOpen > 52)  { height = maxHeight*0.70f; }
                        
                        if(!list->isOpen)
                        { ls_uiFillRect(c, xPos+1, yPos-height, w-2, height, c->widgetColor); }
                    }
                    
                    if(list->isOpen)
                    {
                        for(u32 i = 0; i < list->list.count; i++)
                        {
                            s32 currY = yPos - (h*(i+1));
                            UIListBoxItem *currItem = list->list.getPointer(i);
                            
                            ls_uiRect(c, xPos+1, currY, w-2, h, currItem->bkgColor);
                            ls_uiGlyphString(c, xPos+10, yPos + vertOff - (h*(i+1)),
                                             currItem->name, currItem->textColor);
                            
                        }
                        
                        ls_uiBorder(c, xPos, yPos-maxHeight, w, maxHeight+1);
                    }
                    
                } break;
                
                case UI_RC_LISTBOX_ARR:
                {
                    ls_uiDrawArrow(c, xPos, yPos, w, h, curr->listBox->arrowBkg, UIA_DOWN);
                } break;
                
                case UI_RC_BUTTON:
                {
                    UIButton *button = curr->button;
                    
                    s32 strHeight = ls_uiSelectFontByFontSize(c, FS_SMALL);
                    
                    if(button->style == UIBUTTON_TEXT)
                    {
                        ls_uiBorderedRect(c, xPos, yPos, w, h, bkgColor);
                        
                        s32 strWidth = ls_uiGlyphStringLen(c, button->name);
                        s32 xOff      = (w - strWidth) / 2; //TODO: What happens when the string is too long?
                        s32 strHeight = c->currFont->pixelHeight;
                        s32 yOff      = strHeight*0.25; //TODO: @FontDescent
                        
                        ls_uiGlyphString(c, xPos+xOff, yPos+yOff, button->name, c->textColor);
                    }
                    else if(button->style == UIBUTTON_TEXT_NOBORDER)
                    {
                        ls_uiRect(c, xPos, yPos, w, h, bkgColor);
                        
                        s32 strWidth = ls_uiGlyphStringLen(c, button->name);
                        s32 xOff      = (w - strWidth) / 2; //TODO: What happens when the string is too long?
                        s32 strHeight = c->currFont->pixelHeight;
                        s32 yOff      = strHeight*0.25; //TODO: @FontDescent
                        
                        ls_uiGlyphString(c, xPos+xOff, yPos+yOff, button->name, c->textColor);
                    }
                    else if(button->style == UIBUTTON_BMP)
                    {
                        ls_uiBitmap(c, xPos, yPos, (u32 *)button->bmpData, button->bmpW, button->bmpH);
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
                        
                        ls_uiBorder(c, xPos, yPos, w, h);
                        
                        s32 slidePos = w*slider->currPos;
                        
                        ls_uiFillRect(c, xPos+1, yPos+1, slidePos, h-2, slider->lColor);
                        ls_uiFillRect(c, xPos+slidePos, yPos+1, w-slidePos-1, h-2, slider->rColor);
                        
                        unistring val = ls_unistrFromInt(slider->currValue);
                        
                        s32 strHeight = ls_uiSelectFontByFontSize(c, FS_SMALL);
                        
                        u32 textLen = ls_uiGlyphStringLen(c, val);
                        s32 strXPos = xPos + slidePos - textLen - 2;
                        Color textBkgC = slider->lColor;
                        
                        if(strXPos < xPos+1) { strXPos = xPos + slidePos + slideWidth + 2; textBkgC = slider->rColor; }
                        
                        Color valueColor = c->borderColor;
                        u8 alpha = 0x00 + (slider->isHeld*0xFF);
                        valueColor = SetAlpha(valueColor, alpha);
                        ls_uiGlyphString(c, strXPos, yPos + h - strHeight, val, valueColor);
                        
                        ls_unistrFree(&val);
                        
                        if(slider->isHot)
                        {
                            s32 actualX = (xPos + slidePos) - 1;
                            s32 actualY = yPos - 2;
                            
                            s32 actualWidth  = slideWidth+2;
                            s32 actualHeight = 4 + h;
                            
                            ls_uiFillRect(c, actualX, actualY, actualWidth, actualHeight, c->borderColor);
                        }
                        else
                        {
                            ls_uiFillRect(c, xPos+slidePos, yPos, slideWidth, h, c->borderColor);
                        }
                        
                    }
                    else if(slider->style == SL_LINE)
                    { AssertMsg(FALSE, "Slider style line is not implemented\n"); }
                    
                    //NOTE: Draw the displayed text, and hide through Alpha the slider info.
                    
                    Color rectColor = c->widgetColor;
                    rectColor = SetAlpha(rectColor, opacity);
                    ls_uiBorderedRect(c, xPos, yPos, w, h, rectColor);
                    
                    s32 strHeight = ls_uiSelectFontByFontSize(c, FS_SMALL);
                    
                    s32 strWidth  = ls_uiGlyphStringLen(c, slider->text);
                    s32 xOff      = (w - strWidth) / 2;
                    s32 yOff      = (h - strHeight) + 3; //TODO: @FontDescent
                    
                    Color textColor = c->textColor;
                    textColor = SetAlpha(textColor, opacity);
                    
                    ls_uiGlyphString(c, xPos+xOff, yPos + yOff, slider->text, textColor);
                    
                    //NOTETODO: The isHot is a hack to grow the slider as long as
                    //          the mouse is on top of it. Is it fine for logic to be here in render?
                    slider->isHot = FALSE;
                    
                } break;
                
                case UI_RC_RECT:
                {
                    //NOTE: here current text color is being used improperly for the border color
                    ls_uiBorderedRect(c, xPos, yPos, w, h, c->backgroundColor, curr->textColor);
                } break;
                
                case UI_RC_FRAG_LABEL:
                {
                    unistring label = ls_unistrConstant(curr->label);
                    
                    s32 strPixelHeight = ls_uiSelectFontByFontSize(c, FS_SMALL);
                    s32 strWidth = ls_uiGlyphStringLen(c, label);
                    
                    ls_uiGlyphStringFrag(c, curr->oX, yPos, curr->oX, curr->oY, 
                                         xPos, yPos, xPos+strWidth, yPos, label, textColor);
                } break;
                
                
                case UI_RC_FRAG_TEXTBOX:
                {
                    UITextBox *box = curr->textBox;
                    
                    Color caretColor = textColor;
                    const s32 horzOff = 4;
                    
                    //TODO: Make the font selection more of a global thing??
                    s32 strPixelHeight = ls_uiSelectFontByFontSize(c, FS_SMALL);
                    
                    ls_uiBorderedRectFrag(c, xPos, yPos, w, h, bkgColor, curr->extra);
                    
                    s32 vertOff = ((h - strPixelHeight) / 2) + 5; //TODO: @FontDescent
                    u32 viewLen = box->viewEndIdx - box->viewBeginIdx;
                    u32 actualViewLen = viewLen <= box->text.len ? viewLen : box->text.len;
                    unistring viewString = {box->text.data + box->viewBeginIdx, actualViewLen, actualViewLen};
                    
                    //NOTE: Finally draw the entire string.
                    ls_uiGlyphStringFrag(c, curr->oX + horzOff, yPos + vertOff, curr->oX, curr->oY, 
                                         xPos, yPos, xPos+w, yPos+h, viewString, textColor);
                    
                    if(box->isSelecting)
                    {
                        //TODO: Draw this more efficiently by drawing text in 3 different non-overlapping calls??
                        s32 viewSelBegin = box->selectBeginIdx;
                        if(viewSelBegin <= box->viewBeginIdx) { viewSelBegin = box->viewBeginIdx; }
                        
                        s32 viewSelEnd = box->selectEndIdx;
                        if(box->viewEndIdx != 0 && viewSelEnd >= box->viewEndIdx) { viewSelEnd = box->viewEndIdx; }
                        
                        u32 selLen = viewSelEnd -  viewSelBegin;
                        unistring selString = {box->text.data + viewSelBegin, selLen, selLen};
                        s32 selStringWidth  = ls_uiGlyphStringLen(c, selString);
                        
                        u32 diffLen = 0;
                        if(box->selectBeginIdx > box->viewBeginIdx) 
                        { diffLen = box->selectBeginIdx - box->viewBeginIdx; }
                        
                        unistring diffString = { box->text.data + box->viewBeginIdx, diffLen, diffLen };
                        s32 diffStringWidth = ls_uiGlyphStringLen(c, diffString);
                        
                        s32 startX = curr->oX + horzOff + diffStringWidth;
                        
                        ls_uiFillRectFrag(c, startX, curr->oY+1, selStringWidth, strPixelHeight, xPos, xPos+w, yPos, yPos+h, c->invWidgetColor, curr->extra);
                        
                        ls_uiGlyphStringFrag(c, curr->oX + horzOff + diffStringWidth, curr->oY + vertOff, curr->oX, curr->oY, xPos, yPos, xPos+w, yPos+h, selString, c->invTextColor);
                        
                        if(box->caretIndex == box->selectBeginIdx)
                        { caretColor = c->invTextColor; }
                    } 
                    
                    //NOTE: Draw the Caret
                    if(box->isCaretOn && c->currentFocus == (u64 *)box)
                    {
                        UIGlyph *caretGlyph = &c->currFont->glyph['|'];
                        
                        u32 caretIndexInView = box->caretIndex - box->viewBeginIdx;
                        unistring tmp = {viewString.data, caretIndexInView, caretIndexInView};
                        
                        u32 stringLen = ls_uiGlyphStringLen(c, tmp);
                        const s32 randffset = 4; //TODO: Maybe try to remove this?
                        
                        s32 finalXPos = curr->oX + horzOff + stringLen - randffset;
                        
                        ls_uiGlyphFrag(c, finalXPos, curr->oY+vertOff,
                                       curr->oX, curr->oY, xPos, yPos, xPos+w, yPos+h, caretGlyph, caretColor);
                    }
                    
                } break;
                
                case UI_RC_FRAG_BUTTON:
                {
                    UIButton *button       = curr->button;
                    RenderCommandExtra rce = curr->extra;
                    
                    s32 strHeight = ls_uiSelectFontByFontSize(c, FS_SMALL);
                    
                    if(button->style == UIBUTTON_TEXT)
                    {
                        ls_uiBorderedRectFrag(c, xPos, yPos, w, h, bkgColor, rce);
                        
                        s32 strWidth = ls_uiGlyphStringLen(c, button->name);
                        s32 xOff     = (curr->oW - strWidth) / 2; //TODO: What happens when string is too long?
                        s32 strHeight = c->currFont->pixelHeight;
                        s32 yOff      = strHeight*0.25; //TODO: @FontDescent
                        
                        ls_uiGlyphStringFrag(c, curr->oX+xOff, yPos+yOff, curr->oX, curr->oY,
                                             xPos, yPos, xPos+w, yPos+h, button->name, c->textColor);
                    }
                    else if(button->style == UIBUTTON_TEXT_NOBORDER)
                    {
                        ls_uiRect(c, xPos, yPos, w, h, bkgColor);
                        
                        s32 strWidth = ls_uiGlyphStringLen(c, button->name);
                        s32 xOff      = (curr->oW - strWidth) / 2; //TODO: What happens when the string is too long?
                        s32 strHeight = c->currFont->pixelHeight;
                        s32 yOff      = strHeight*0.25; //TODO: @FontDescent
                        
                        ls_uiGlyphStringFrag(c, curr->oX+xOff, yPos+yOff, curr->oX, curr->oY,
                                             xPos, yPos, xPos+w, yPos+h, button->name, c->textColor);
                    }
                    else if(button->style == UIBUTTON_BMP)
                    {
                        AssertMsg(FALSE, "button style BMP is not implemented yet.");
                        ls_uiBitmap(c, xPos, yPos, (u32 *)button->bmpData, button->bmpW, button->bmpH);
                    }
                    else { AssertMsg(FALSE, "Unhandled button style"); }
                    
                } break;
                
                case UI_RC_FRAG_SLIDER:
                {
                    UISlider *slider = curr->slider;
                    
                    //NOTE: Box Slider Branchless Opacity Check
                    //u8 opacity = 0xEE - (0xB0*slider->isHeld);
                    u8 opacity = 0xC0 - (0xB0*slider->isHeld);
                    
                    if(slider->style == SL_BOX)
                    {
                        s32 slideWidth = 3;
                        
                        ls_uiBorderFrag(c, xPos, yPos, w, h, curr->extra);
                        
                        s32 slidePos  = curr->oW*slider->currPos;
                        
                        //AssertMsg(FALSE, "All fucked\n");
#if 0
                        if(curr->extra == UI_RCE_LEFT)
                        {
                            s32 startX = curr->oX+1;
                            s32 fragW  = (xPos+w) < curr->oX+slidePos ? w : slidePos;
                            
                            ls_uiFillRect(c, startX, curr->oY+1, fragW-1, h-2, slider->lColor);
                            
                            if((curr->oX+slidePos) < (xPos+w))
                            {
                                ls_uiFillRect(c, curr->oX+slidePos, curr->oY+1, w-slidePos, h-2, slider->rColor);
                            }
                        }
                        else if(curr->extra == UI_RCE_RIGHT)
                        {
                            if((curr->oX+slidePos) > (xPos+1))
                            {
                                s32 fragWLeft = curr->oX + slidePos - xPos;
                                ls_uiFillRect(c, xPos, curr->oY+1, fragWLeft, h-2, slider->lColor);
                            }
                            
                            s32 startX     = xPos > (curr->oX+slidePos) ? xPos : (curr->oX+slidePos);
                            s32 fragWRight = xPos > (curr->oX+slidePos) ? w : (w - (curr->oX+slidePos - xPos));
                            ls_uiFillRect(c, startX, curr->oY+1, fragWRight-1, h-2, slider->rColor);
                        }
#else
                        s32 leftX  = curr->oX + 1;
                        s32 rightX = leftX + slidePos;
                        s32 leftW  = slidePos;
                        s32 rightW = curr->oW - slidePos - 2;
                        ls_uiFillRectFrag(c, leftX,  curr->oY+1, leftW,  h-2, 
                                          xPos, xPos+w, yPos, yPos+h, slider->lColor, curr->extra);
                        ls_uiFillRectFrag(c, rightX, curr->oY+1, rightW, h-2,
                                          xPos, xPos+w, yPos, yPos+h, slider->rColor, curr->extra);
#endif
                        
                        unistring val = ls_unistrFromInt(slider->currValue);
                        
                        s32 strHeight = ls_uiSelectFontByFontSize(c, FS_SMALL);
                        
                        u32 textLen = ls_uiGlyphStringLen(c, val);
                        s32 strXPos = curr->oX + slidePos - textLen - 2;
                        Color textBkgC = slider->lColor;
                        
                        if(strXPos < curr->oX+1)
                        { strXPos = curr->oX + slidePos + slideWidth + 2; textBkgC = slider->rColor; }
                        
                        Color valueColor = c->borderColor;
                        u8 alpha = 0x00 + (slider->isHeld*0xFF);
                        valueColor = SetAlpha(valueColor, alpha);
                        ls_uiGlyphStringFrag(c, strXPos, curr->oY + h - strHeight, curr->oX, curr->oY, xPos, yPos, xPos+w, yPos+h, val, valueColor);
                        
                        ls_unistrFree(&val);
                        
#if 0
                        s32 actualX = (curr->oX + slidePos) - 1;
                        s32 hotX = actualX - 1;
                        //s32 actualY = curr->oY;
                        //s32 hotY = actualY - 2;
                        
                        s32 actualWidth = slideWidth+2;
                        s32 hotWidth    = actualWidth+2;
                        
                        s32 actualHeight = curr->oH;
                        s32 hotHeight    = actualHeight + 4;
                        
                        if(slider->isHot)
                        {
                            ls_uiFillRectFrag(c, hotX, curr->oY-2, hotWidth, hotHeight,
                                              xPos, xPos+w+hotWidth, yPos-2, yPos+h+2, c->borderColor, curr->extra);
                        }
                        else
                        {
                            ls_uiFillRectFrag(c, actualX, curr->oY, actualWidth, actualHeight,
                                              xPos, xPos+w+actualWidth, yPos, yPos+h, c->borderColor, curr->extra);
                        }
#else
                        s32 actualX = (curr->oX + slidePos) - 1;
                        s32 actualY = curr->oY;
                        s32 actualWidth = slideWidth+2;
                        s32 actualHeight = curr->oH + 4;
                        
                        if(slider->isHot)
                        {
                            if((actualX-1) < (xPos+w))
                            { ls_uiFillRect(c, actualX-1, actualY, actualWidth+2, actualHeight, c->borderColor); }
                            
                        }
                        else
                        {
                            if(actualX < (xPos+w))
                            { ls_uiFillRect(c, actualX, curr->oY, actualWidth, curr->oH, c->borderColor); }
                        }
#endif
                        
                    }
                    else if(slider->style == SL_LINE)
                    { AssertMsg(FALSE, "Slider style line is not implemented\n"); }
                    
                    //NOTE: Draw the displayed text, and hide through Alpha the slider info.
                    
                    Color rectColor = c->widgetColor;
                    rectColor = SetAlpha(rectColor, opacity);
                    
                    if(curr->extra == UI_RCE_LEFT)       { ls_uiFillRect(c, xPos+1, yPos+1, w-1, h-2, rectColor); }
                    else if(curr->extra == UI_RCE_RIGHT) { ls_uiFillRect(c, xPos,   yPos+1, w-1, h-2, rectColor); }
                    
                    s32 strHeight = ls_uiSelectFontByFontSize(c, FS_SMALL);
                    
                    s32 strWidth  = ls_uiGlyphStringLen(c, slider->text);
                    s32 xOff      = (curr->oW - strWidth) / 2;
                    s32 yOff      = (curr->oH - strHeight) + 3; //TODO: @FontDescent
                    
                    Color textColor = c->textColor;
                    textColor = SetAlpha(textColor, opacity);
                    
                    ls_uiGlyphStringFrag(c, curr->oX+xOff, curr->oY + yOff, curr->oX, curr->oY, xPos, yPos, xPos+w, yPos+h, slider->text, textColor);
                    
                    //NOTETODO: The isHot is a hack to grow the slider as long as
                    //          the mouse is on top of it. Is it fine for logic to be here in render?
                    slider->isHot = FALSE;
                    
                } break;
                
                case UI_RC_FRAG_LISTBOX:
                {
                    UIListBox *list = curr->listBox;
                    
                    s32 strHeight = ls_uiSelectFontByFontSize(c, FS_SMALL);
                    s32 vertOff = ((curr->oH - strHeight) / 2) + 4; //TODO: @FontDescent
                    
                    ls_uiBorderedRectFrag(c, xPos, yPos, w, h, curr->extra);
                    
                    if(list->list.count)
                    {
                        unistring selected = list->list[list->selectedIndex].name;
                        ls_uiGlyphStringFrag(c, curr->oX+10, curr->oY + vertOff, curr->oX, curr->oY, xPos, yPos, xPos+w, yPos+h, selected, c->textColor);
                    }
                    
                    s32 maxHeight = (list->list.count)*h;
                    if(list->isOpening)
                    {
                        s32 height = 0;
                        if(list->dtOpen > 17)  { height = maxHeight*0.10f; }
                        if(list->dtOpen > 34)  { height = maxHeight*0.35f; }
                        if(list->dtOpen > 52)  { height = maxHeight*0.70f; }
                        
                        if(!list->isOpen)
                        { 
                            if(curr->extra == UI_RCE_LEFT)
                            { ls_uiFillRect(c, xPos+1, yPos-height, w, height, c->widgetColor); }
                            else if(curr->extra == UI_RCE_RIGHT)
                            { ls_uiFillRect(c, xPos, yPos-height, w-1, height, c->widgetColor); }
                        }
                    }
                    
                    if(list->isOpen)
                    {
                        for(u32 i = 0; i < list->list.count; i++)
                        {
                            s32 iOff = (h*(i+1));
                            s32 currY = yPos - iOff;
                            UIListBoxItem *currItem = list->list.getPointer(i);
                            
                            ls_uiFillRect(c, xPos, currY, w, h, currItem->bkgColor);
                            
                            ls_uiGlyphStringFrag(c, curr->oX+10, curr->oY + vertOff - iOff,
                                                 curr->oX, curr->oY - iOff, xPos, yPos - iOff, xPos+w, yPos+h,
                                                 currItem->name, currItem->textColor);
                            
                        }
                        
                        ls_uiBorderFrag(c, xPos, yPos-maxHeight, w, maxHeight+1, curr->extra);
                    }
                    
                } break;
                
                case UI_RC_FRAG_LISTBOX_ARR:
                {
                    UIScissor::UIRect *scRect = c->scissor.currRect;
                    u32 *At = (u32 *)c->drawBuffer;
                    
                    s32 arrowX = curr->oX - 1;
                    
                    ls_uiBorderedRectFrag(c, xPos-1, yPos, w, h, curr->listBox->arrowBkg, curr->extra);
                    
                    s32 arrowWidth = 8;
                    s32 hBearing = (curr->oW - arrowWidth)/2;
                    s32 xBase = arrowX + hBearing;
                    s32 xEnd  = xBase + arrowWidth;
                    
                    s32 arrowHeight = 4;
                    s32 vBearing = (curr->oH - arrowHeight)/2;
                    s32 yStart = (curr->oY + curr->oH - vBearing) - 1;
                    s32 yEnd = yStart - arrowHeight;
                    
                    for(s32 y = yStart; y >= yEnd; y--)
                    {
                        for(s32 x = xBase; x < xEnd; x++)
                        {
                            if((x < xPos-1) || (x > xPos+w)) continue;
                            if((y < yPos)   || (y > yPos+h)) continue;
                            
                            if(x < 0 || x >= c->width)  continue;
                            if(y < 0 || y >= c->height) continue;
                            
                            if(x < scRect->x || x >= scRect->x+scRect->w) continue;
                            if(y < scRect->y || y >= scRect->y+scRect->h) continue;
                            
                            At[y*c->width + x] = c->borderColor;
                        }
                        
                        xBase += 1;
                        xEnd  -= 1;
                    }
                    
                } break;
                
                case UI_RC_FRAG_RECT:
                {
                    //NOTE: here current text color is being used improperly for the border color
                    ls_uiBorderedRectFrag(c, xPos, yPos, w, h, c->backgroundColor, curr->textColor, curr->extra);
                } break;
#endif
                
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
    
    //c->renderFunc();
    
    return;
}


#endif //LS_UI_IMPLEMENTATION
