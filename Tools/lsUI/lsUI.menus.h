#pragma once

struct UIMenuItem
{
    //NOTE: callback1 -> onClick; callback2 -> UNUSED
    UIWidget_Base;
    
    utf32 name;
    
    b32 isVisible;
    b32 isHot;
};

struct UISubMenu
{
    utf32 name;
    Array<UIMenuItem> items;
    
    b32 isHot;
};

//TODO: Very Shitty implementation of Menus
struct UIMenu
{
    UIButton          closeWindow;
    UIButton          minimize;
    UIButton          maximize;
    
    Array<UISubMenu>  subMenus;
    b32               isOpen;
    s32               openIdx;
    
    Array<UIMenuItem> items;
    
    s32               itemWidth;
    
    //TODO: Add bkgColor and textColor
};


UIButton    ls_uiMenuButton(UIContext *c, UICallback onClick, u8 *bitmapData, s32 width, s32 height);
UIButton    ls_uiMenuButton(UIContext *c, UICallback onClick, UIBitmap bmp);
UISubMenu * ls_uiMenuAddSub(UIContext *c, UIMenu *menu, UISubMenu sub);
UISubMenu * ls_uiMenuAddSub(UIContext *c, UIMenu *menu, const char32_t *name);
UIMenuItem* ls_uiMenuAddItem(UIContext *c, UIMenu *menu, const char32_t *name, UICallback onClick, void *userData);
UIMenuItem* ls_uiSubMenuAddItem(UIContext *c, UISubMenu *sub, const char32_t *name, UICallback onClick, void *userData);
UIMenuItem* ls_uiSubMenuAddItem(UIContext *c, UIMenu *menu, u32 subIdx, const char32_t *name, UICallback onClick, void *data);
b32         ls_uiMenu(UIContext *c, UIMenu *menu, s32 x, s32 y, s32 w, s32 h, s32 zLayer);
