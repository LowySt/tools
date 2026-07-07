#pragma once

enum UICheckStyle { UICHECK_BMP };
struct UICheck
{
    //NOTE: callback1 -> onClick; callback2 -> UNUSED
    UIWidget_Base;
    
    UICheckStyle style;
    
    b32 isActive;
    UIBitmap bmpActive;
    UIBitmap bmpInactive;
    UIBitmap bmpAdditive;
    s32 w,h; //TODO: This are duplicated with the bmpActive and bmpInactive bitmaps... which is bad
};


UICheck ls_uiCheckInit(UIContext *c, UICheckStyle s, UIBitmap inactive, UIBitmap additive, UICallback onChange, void *data);
UICheck ls_uiCheckInit(UIContext *c, UICheckStyle s,
                            u8 *bmpActive, u8 *bmpInactive, s32 w, s32 h, UICallback onChange, void *data);
UICheck ls_uiCheckInit(UIContext *c, UICheckStyle s, u8 *bmpInactive, s32 w, s32 h,
                            u8 *bmpAdditive, s32 addW, s32 addH, UICallback onChange, void *data);
b32     ls_uiCheck(UIContext *c, UICheck *check, s32 x, s32 y, s32 zLayer);
