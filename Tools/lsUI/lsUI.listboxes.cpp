#include "lsUI.listboxes.h"

UIListBox ls_uiListBoxInit(UIContext *c, FixedArray<UIListBoxItem> container)
{
    UIListBox lb = {};
    lb.list = container;
    return lb;
}

inline u32 ls_uiListBoxAddEntry(UIContext *c, UIListBox *lb, utf32 s)
{
    AssertNonNull(c);
    AssertNonNull(lb);
    AssertNonNull(lb->list.data);
    
    UIListBoxItem item = { s, c->widgetColor, c->textColor };
    return ls_fixedArrayAppendIndex(&lb->list, item);
}

//NOTE: This does NOT free the memory of the string
inline void ls_uiListBoxRemoveEntry(UIContext *c, UIListBox *lb, u32 index)
{ 
    AssertNonNull(c);
    AssertNonNull(lb);
    AssertNonNull(lb->list.data);
    
    //NOTETODO: Is this good????
    if(lb->selectedIndex == index) { lb->selectedIndex = 0; }
    
    UIListBoxItem val = lb->list[index];
    ls_fixedArrayRemove(&lb->list, index);
}

//TODO: Currently the renderer doesn't care if the item's name is too long, and just renders it in full
b32 ls_uiListBox(UIContext *c, UIListBox *lb, s32 xPos, s32 yPos, s32 w, s32 h, u32 zLayer = 0)
{
    Input *UserInput = &c->currWindow->UserInput;
    b32 inputUse = FALSE;

    //TODO: Why is this constant?
    const s32 arrowBoxWidth = 24;
    if(LeftClickIn(xPos+w, yPos, arrowBoxWidth, h) && ls_uiHasCapture(c, 0))
    {
        ls_uiFocusChangeSameFrame(c, (u64 *)lb);
        
        if(lb->isOpen) { lb->isOpen = FALSE; }
        //else { lb->isOpening = TRUE; } //NOTE:TODO: This is because Claudio wanted instant list open. 
        else { lb->isOpen = TRUE; }
    }
    
    Color bkgColor = c->widgetColor;
    s32 arrowX = xPos + w - 1;
    if(MouseInRect(arrowX, yPos, arrowBoxWidth, h)) { bkgColor = c->highliteColor; }
    lb->arrowBkg = bkgColor;
    
    if(lb->isOpening)
    {
        lb->dtOpen += c->dt;
        if(lb->dtOpen > 70) { lb->isOpen = TRUE; lb->isOpening = FALSE; lb->dtOpen = 0; }
    }
    
    if(ls_uiInFocus(c, lb))
    {
        if(lb->isOpen)
        {
            for(u32 i = 0; i < lb->list.count; i++)
            {
                s32 currY = yPos - (h*(i+1));
                UIListBoxItem *currItem = lb->list + i;
                
                //TODO: The constant resetting is kinda stupid. Makes me think I should just not
                //      have listbox items with their own colors. Never even used that feature.
                currItem->bkgColor  = c->widgetColor;
                currItem->textColor = c->textColor;
                if(MouseInRect(xPos+1, currY+1, w-2, h-1)) 
                { 
                    currItem->bkgColor = c->highliteColor;
                    if(LeftClick) { 
                        c->currWindow->mouseCapture = (u64 *)lb;
                        
                        lb->selectedIndex = i; lb->isOpen = FALSE;
                        inputUse = TRUE;
                        
                        //NOTE: lb->onSelect
                        if(lb->callback1) { lb->callback1(c, lb->callback1Data); }
                    }
                    
                    //TODO: Lost the ability to hold because of mouse capture.
                    //      Should be able to regain it if capture is handled deferred?
                    //if(LeftHold) { currItem->bkgColor = cxt->pressedColor; }
                    //if(LeftUp) { ls_printf("here\n");  }
                }
            }
        }
    }
    else
    { lb->isOpen = FALSE; }
    
    //TODO: I think it *should* be fine if the count is 0, since the height of the box is set to maxHeight+h
    //      But i need to test it!
    s32 maxHeight = (lb->list.count)*(h);
    //NOTE: Here the maxHeight in the command rect is used to determine the maximum height when expanded
    //      the height passed in the layout rect in minY determines the minimum height when contracted.
    //      This also means that yPos is shifted by maxHeight
    RenderCommand list_command = { UI_RC_LISTBOX, xPos, yPos-maxHeight, w, maxHeight+h };
    list_command.layout.minY = h;
    list_command.listBox = lb;
    ls_uiPushRenderCommand(c, list_command, zLayer);
    
    RenderCommand arr_command = { UI_RC_LISTBOX_ARR, xPos+w, yPos, arrowBoxWidth, h };
    arr_command.listBox = lb;
    ls_uiPushRenderCommand(c, arr_command, zLayer);
    
    return inputUse;
}

b32 ls_uiListBox(UIContext *c, UIListBox *lb, UIPos pos, u32 zLayer = 0)
{
    UIWindow *win = c->currWindow;
    if (pos.kind == UIPosKind::Abs)
    {
        return ls_uiListBox(c, lb, pos.ix, pos.iy, pos.iw, pos.ih, zLayer);
    }
    else if (pos.kind == UIPosKind::Scl)
    {
        s32 xPos = pos.sx*win->width;
        s32 yPos = pos.sy*win->height;
        return ls_uiListBox(c, lb, xPos, yPos, pos.sw, pos.sh, zLayer);
    }

    s32 xPos = pos.fx*win->width;
    s32 yPos = pos.fy*win->height;
    s32 w    = pos.fw*win->width;
    s32 h    = pos.fh*win->height;
    return ls_uiListBox(c, lb, xPos, yPos, w, h, zLayer);
}
