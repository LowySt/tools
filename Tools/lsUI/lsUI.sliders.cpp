#include "lsUI.sliders.h"

UISlider ls_uiSliderInit(UIContext *c, char32_t *name, s32 maxVal, s32 minVal, f64 currPos, SliderStyle s, Color l, Color r)
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
    UIWindow *win = c->currWindow;
    Input *UserInput = &win->UserInput;
    
    if(LeftUp) { slider->isHeld = FALSE; }
    
    if(slider->style == SL_BOX)
    {
        //NOTE: hotness needs to be logically re-checked every frame, else it always stays on.
        slider->isHot = FALSE;
        s32 slidePos = w*slider->currPos;
        
        if(MouseInRect(xPos + slidePos-5, yPos, 10, h) && !(win->mouseCapture != 0 && win->mouseCapture != (u64 *)slider))
        {
            slider->isHot = TRUE;
            if(LeftHold) { slider->isHeld = TRUE; win->mouseCapture = (u64 *)slider; }
        }
    }
    else if(slider->style == SL_LINE)
    { AssertMsg(FALSE, "Slider style line is not implemented\n"); }
    
    b32 hasAnsweredToInput = FALSE;
    
    if(slider->isHeld) { 
        s32 deltaX = (UserInput->Mouse.prevPosX - UserInput->Mouse.currPosX);
        
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
