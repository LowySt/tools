#pragma once

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
    UIBitmap bmp;
    
    b32 isHot;
    b32 isHeld;
    
    //NOTE: When this is set, the button is drawn greyed out, and
    //      the user can't interact with it.
    b32 isInactive;
};


template<typename T> UIButton ls_uiButtonInit(UIContext *c, UIButtonStyle s, T text, UICallback onClick,
                                              UICallback onHold, void *userData);

b32 ls_uiButton(UIContext *c, UIButton *button, s32 xPos, s32 yPos, Color bkgColor, s32 zLayer);
b32 ls_uiButton(UIContext *c, UIButton *button, s32 xPos, s32 yPos, s32 zLayer);
b32 ls_uiButton(UIContext *c, UIButton *button, f32 x, f32 y, Color bkgColor, s32 zLayer);
b32 ls_uiButton(UIContext *c, UIButton *button, f32 x, f32 y, s32 zLayer);
b32 ls_uiButton(UIContext *c, UIButton *button, UIPos pos, s32 zLayer);
