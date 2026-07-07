#pragma once

enum UIArrowSide { UIA_LEFT, UIA_RIGHT, UIA_UP, UIA_DOWN };

struct UIListBoxItem
{
    utf32 name;
    Color bkgColor;
    Color textColor;
};

struct UIListBox
{
    //NOTE: callback1 -> onSelect; callback2 -> UNUSED
    UIWidget_Base;
    
    FixedArray<UIListBoxItem> list;
    s32 selectedIndex;
    
    u32 dtOpen;
    b32 isOpening;
    b32 isOpen;
    
    Color arrowBkg;
};


UIListBox ls_uiListBoxInit(UIContext *c, s32 maxItemCount);
//NOTE: This does NOT allocate memory for the string
u32       ls_uiListBoxAddEntry(UIContext *c, UIListBox *list, utf32 s);
//NOTE: This does NOT free the memory of the string
void      ls_uiListBoxRemoveEntry(UIContext *c, UIListBox *list, u32 index);
b32       ls_uiListBox(UIContext *c, UIListBox *list, s32 xPos, s32 yPos, s32 w, s32 h, u32 zLayer);
b32       ls_uiListBox(UIContext *c, UIListBox *lb, UIPos pos, u32 zLayer);
