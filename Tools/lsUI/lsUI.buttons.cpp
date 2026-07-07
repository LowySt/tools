#include "lsUI.buttons.h"

template<typename T>
UIButton ls_uiButtonInit(UIContext *c, UIButtonStyle s, T text, UICallback onClick = NULL, UICallback onHold = NULL, void *userData = NULL)
{
    AssertNonNull(c);
    AssertMsg(c->currFont, "Font is not selected\n");
    
    //NOTE: Otherwise we calculate the dimensions occupied by the text
    //      and use them to calculate the button's dimensions
    s32 pixelHeight = c->currPixelHeight;
    utf32 name = {};
    if constexpr(typeid(T) == typeid(const char32_t *))
    {
        //If no text pointer is provided, we just return an empty button
        //  (for things like bitmap buttons)
        if(text == NULL)
        {
            UIButton result = {
                {onClick, userData, onHold, userData, NULL, NULL}, 
                s, {}, 0, 0, 0, FALSE, FALSE 
            };
            return result;
        }

        Arena prev = ls_arenaUse(c->widgetArena);
        name = ls_utf32FromUTF32(text);
        ls_arenaUse(prev);
    }
    else if constexpr(typeid(T) == typeid(utf32))
    {
        name = text;
    }
    else
    { AssertMsg(FALSE, "Invalid use of string type. Only utf32 and const char32_t are supported"); }
    
    //Add Margin above and below text and on each side
    s32 height = pixelHeight + 2;
    s32 width = ls_uiGlyphStringRect(c, c->currFont, name, pixelHeight).w + 16;
    
    UIButton result = {
        {onClick, userData, onHold, userData, NULL, NULL}, 
        s, name, 0, width, height, FALSE, FALSE
    };
    
    return result;
}

//TODO:Menus use buttons, but also claim Focus, which means I can't use the global focus trick to avoid input
//     handling between overlapping elements.
//     I don't think the menu should deal with things like this [It shouldn't hold the close button first,
//     and it also shouldn't use 'normal' buttons for its drop down sub-menus, so... basically @MenuIsShit
//     and I wanna redo it completely.

//TODO @UIPos
b32 ls_uiButton(UIContext *c, UIButton *button, s32 xPos, s32 yPos, Color bkgColor, s32 zLayer = 0)
{
    Input *UserInput = &c->currWindow->UserInput;
    
    b32 inputUse = FALSE;
    
    Color textColor   = c->textColor;
    Color borderColor = c->borderColor;
    
    if(button->style == UIBUTTON_TEXT_NOBORDER) { bkgColor = c->backgroundColor; }
    
    if(button->isInactive == TRUE)
    {
        textColor = ls_uiDarkenRGB(textColor, 0.50f);
        bkgColor  = ls_uiDarkenRGB(bkgColor, 0.50f);
        
        RenderCommand command = { UI_RC_BUTTON, xPos, yPos, button->bmp.w, button->bmp.h };
        command.button        = button;
        command.bkgColor      = bkgColor;
        command.borderColor   = borderColor;
        command.textColor     = textColor;
        ls_uiPushRenderCommand(c, command, zLayer);
        
        return FALSE;
    }
    
    if(MouseInRect(xPos, yPos, button->bmp.w, button->bmp.h-1))// && ls_uiInFocus(cxt, 0))
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
    
    RenderCommand command = { UI_RC_BUTTON, xPos, yPos, button->bmp.w, button->bmp.h };
    command.button        = button;
    command.bkgColor      = bkgColor;
    command.borderColor   = borderColor;
    command.textColor     = textColor;
    ls_uiPushRenderCommand(c, command, zLayer);
    
    return inputUse;
}

b32 ls_uiButton(UIContext *c, UIButton *button, s32 xPos, s32 yPos, s32 zLayer = 0)
{
    return ls_uiButton(c, button, xPos, yPos, c->widgetColor, zLayer);
}

b32 ls_uiButton(UIContext *c, UIButton *button, f32 x, f32 y, Color bkgColor, s32 zLayer = 0)
{
    UIWindow *win = c->currWindow;
    s32 xPos      = x*win->width;
    s32 yPos      = y*win->height;
    return ls_uiButton(c, button, xPos, yPos, bkgColor, zLayer);
}

b32 ls_uiButton(UIContext *c, UIButton *button, f32 x, f32 y, s32 zLayer = 0)
{
    return ls_uiButton(c, button, x, y, c->widgetColor, zLayer);
}

b32 ls_uiButton(UIContext *c, UIButton *button, UIPos pos, s32 zLayer = 0)
{
    UIWindow *win = c->currWindow;
    if (pos.kind == UIPosKind::Abs)
    {
        return ls_uiButton(c, button, pos.ix, pos.iy, c->widgetColor, zLayer);
    }
    else if (pos.kind == UIPosKind::Scl)
    {
        s32 xPos = pos.sx*win->width;
        s32 yPos = pos.sy*win->height;
        return ls_uiButton(c, button, xPos, yPos, c->widgetColor, zLayer);
    }

    s32 xPos = pos.fx*win->width;
    s32 yPos = pos.fy*win->height;
    return ls_uiButton(c, button, xPos, yPos, c->widgetColor, zLayer);
}
