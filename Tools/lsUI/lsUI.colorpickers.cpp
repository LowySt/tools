#include "lsUI.colorpickers.h"

UIColorPicker ls_uiColorPickerInit(UIContext *c, void *userData)
{
    UIColorPicker result = {};
    result.value = 1.0f;
    result.apply = ls_uiButtonInit(c, UIBUTTON_CLASSIC, U"Apply", NULL, NULL, userData);
    
    return result;
}


b32 ls_uiColorPicker(UIContext *c, UIColorPicker *picker, s32 x, s32 y, s32 w, s32 h, s32 zLayer = 0)
{
    UIWindow *win = c->currWindow;
    Input *UserInput = &win->UserInput;
    
    if(LeftClickIn(x, y, w, h) && ls_uiHasCapture(c, 0)) {
        ls_uiFocusChangeSameFrame(c, (u64 *)picker);
        win->mouseCapture = (u64 *)picker;
    }
    
    s32 xMargin = w*0.1f;
    s32 yMargin = h*0.1f;
    
    s32 valueRectX = x + xMargin;
    s32 valueRectY = y + yMargin;
    s32 valueRectW = w*0.1f;
    s32 valueRectH = h*0.8f;
    
    s32 buttonH = picker->apply.bmp.h;
    
    s32 radius  = w*0.30f;
    s32 centerX = x + 2*xMargin + valueRectW + radius;
    s32 centerY = y + 3*yMargin + buttonH + radius;
    
    s32 buttonX = centerX - picker->apply.bmp.w/2;
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

