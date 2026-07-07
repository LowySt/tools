#pragma once

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


UISlider ls_uiSliderInit(UIContext *c, char32_t *name, s32 maxVal, s32 minVal, f64 currPos, SliderStyle s, Color l, Color r);
void     ls_uiSliderChangeValueBy(UIContext *c, UISlider *f, s32 valueDiff);
s32      ls_uiSliderCalculateValueFromPosition(UIContext *c, UISlider *f);
b32      ls_uiSlider(UIContext *c, UISlider *slider, s32 xPos, s32 yPos, s32 w, s32 h);
