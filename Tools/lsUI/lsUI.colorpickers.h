#pragma once

struct UIColorPicker
{
    //NOTE: callback1 -> onClick; callback2 -> UNUSED
    UIWidget_Base;
    
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



UIColorPicker ls_uiColorPickerInit(UIContext *c, void *userData);
b32           ls_uiColorPicker(UIContext *c, UIColorPicker *picker, s32 x, s32 y, s32 w, s32 h, s32 zLayer);
