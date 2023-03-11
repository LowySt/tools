#ifndef LS_GRAPHICS_H
#define LS_GRAPHICS_H

#ifdef LS_PLAT_WINDOWS

/*Window Class Properties*/
#define LS_X_BYTEALIGN_CLIENT    CS_BYTEALIGNCLIENT
#define LS_X_BYTEALIGN_WINDOW    CS_BYTEALIGNWINDOW
#define LS_SHAREDC               CS_CLASSDC
#define LS_DBLCLKMSG             CS_DBLCLKS
#define LS_DROPSHADOW            CS_DROPSHADOW
#define LS_HREDRAW               CS_HREDRAW
#define LS_VREDRAW               CS_VREDRAW
#define LS_NO_CLOSEBUTTON        CS_NOCLOSE
#define LS_UNIQUEDC              CS_OWNDC
#define LS_DRAW_ON_PARENT        CS_PARENTDC
#define LS_CACHE_HIDDEN_SECTION  CS_SAVEBITS

/*Window Style*/
#define LS_THIN_BORDER		WS_BORDER
#define LS_THICK_BORDER	   WS_THICKFRAME
#define LS_TITLE_BAR		  WS_CAPTION
#define LS_CHILD			  WS_CHILD
#define LS_CLIP_CHILD		 WS_CLIPCHILDREN
#define LS_CLIP_SIBLINGS	  WS_CLIPSIBLINGS
#define LS_DISABLED		   WS_DISABLED
#define LS_DIALOG_BOX_FRAME   WS_DLGFRAME
#define LS_HSCROLL_BAR		WS_HSCROLL
#define LS_VSCROLL_BAR		WS_VSCROLL
#define LS_MINIMIZE		   WS_MINIMIZE
#define LS_MAXIMIZE		   WS_MAXIMIZE
#define LS_SYS_MENU		   WS_SYSMENU
#define LS_MAXIMIZE_BUTTON	WS_MAXIMIZEBOX
#define LS_MINIMIZE_BUTTON	WS_MINIMIZEBOX
#define LS_OVERLAPPED		 WS_OVERLAPPED
#define LS_OVERLAPPEDWINDOW   WS_OVERLAPPEDWINDOW
#define LS_POPUP			  WS_POPUP
#define LS_POPUPWINDOW		WS_POPUPWINDOW
#define LS_VISIBLE			WS_VISIBLE
#define LS_RESIZE             WS_SIZEBOX

#endif

struct WindowInfo
{
	s32 Height;
	s32 Width;
    
    b32 AspectRatioChanged;
    
	u32 properties;
	u32 style;
    
	char *menuName;
	char *className;
	char *windowName;
    
#ifdef LS_PLAT_WINDOWS
	HWND  WindowHandle;
	HDC   DeviceContext;
	HGLRC RenderingContext;
    
	LRESULT(*WindowProc)(HWND, UINT, WPARAM, LPARAM);
#endif
    
};


#endif