#include "lsUI.checks.h"

UICheck ls_uiCheckInit(UIContext *c, UICheckStyle s, UIBitmap inactive, UIBitmap additive, UICallback onChange, void *data)
{
    UICheck result       = {};
    result.style         = s;
    result.isActive      = FALSE;
    result.bmpInactive   = inactive;
    result.bmpAdditive   = additive;
    result.w             = inactive.w;
    result.h             = inactive.h;
    result.callback1     = onChange;
    result.callback1Data = data;
    
    return result;
}

//NOTE TODO: The following 2 functions ALLOCATE VRAM for the bitmaps EACH time they are called!
UICheck ls_uiCheckInit(UIContext *c, UICheckStyle s,
                       u8 *bmpActive, u8 *bmpInactive, s32 w, s32 h, UICallback onChange, void *data)
{
    UICheck result       = {};
    result.style         = s;
    result.isActive      = FALSE;
    result.bmpActive     = ls_uiBitmapFromRGBAPixelData(c, w, h, bmpActive);
    result.bmpInactive   = ls_uiBitmapFromRGBAPixelData(c, w, h, bmpInactive);
    result.w             = w;
    result.h             = h;
    result.callback1     = onChange;
    result.callback1Data = data;
    
    return result;
}

UICheck ls_uiCheckInit(UIContext *c, UICheckStyle s, u8 *bmpInactive, s32 w, s32 h,
                       u8 *bmpAdditive, s32 addW, s32 addH, UICallback onChange, void *data)
{
    UICheck result       = {};
    result.style         = s;
    result.isActive      = FALSE;
    result.bmpInactive   = ls_uiBitmapFromRGBAPixelData(c, w, h, bmpInactive);
    result.bmpAdditive   = ls_uiBitmapFromRGBAPixelData(c, addW, addH, bmpAdditive);
    result.w             = w;
    result.h             = h;
    result.callback1     = onChange;
    result.callback1Data = data;
    
    return result;
}

b32 ls_uiCheck(UIContext *c, UICheck *check, s32 x, s32 y, s32 zLayer = 0)
{
    Input *UserInput = &c->currWindow->UserInput;
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
