#include "lsUI.menus.h"

UIButton ls_uiMenuButton(UIContext *c, UICallback onClick, u8 *bitmapData, s32 width, s32 height)
{
    UIBitmap bmp     = ls_uiBitmapFromRGBAPixelData(c, width, height, bitmapData);

    UIButton result  = {};
    result.style     = UIBUTTON_BMP;
    result.bmp       = bmp;
    result.callback1 = onClick;
    return result;
}

UIButton ls_uiMenuButton(UIContext *c, UICallback onClick, UIBitmap bmp)
{
    UIButton result  = {};
    result.style     = UIBUTTON_BMP;
    result.bmp       = bmp;
    result.callback1 = onClick;
    return result;
}

inline UISubMenu *ls_uiMenuAddSub(UIContext *c, UIMenu *menu, UISubMenu sub)
{
    Arena prev = ls_arenaUse(c->widgetArena);
    UISubMenu *result = ls_arrayAppend(&menu->subMenus, sub);
    ls_arenaUse(prev);
    return result;
}

UISubMenu *ls_uiMenuAddSub(UIContext *c, UIMenu *menu, const char32_t *name)
{ 
    Arena prev = ls_arenaUse(c->widgetArena);
    UISubMenu newSub = {};
    newSub.name = ls_utf32FromUTF32(name);
    UISubMenu *result = ls_arrayAppend(&menu->subMenus, newSub);
    ls_arenaUse(prev);
    return result;
}

UIMenuItem *ls_uiMenuAddItem(UIContext *c, UIMenu *menu, const char32_t *name, UICallback onClick, void *userData)
{
    Arena prev = ls_arenaUse(c->widgetArena);
    
    UIMenuItem newItem    = {};
    newItem.name          = ls_utf32FromUTF32(name);
    newItem.isVisible     = TRUE;
    newItem.callback1     = onClick;
    newItem.callback1Data = userData;
    UIMenuItem *result = ls_arrayAppend(&menu->items, newItem);
    
    ls_arenaUse(prev);
    return result;
}

UIMenuItem *ls_uiSubMenuAddItem(UIContext *c, UISubMenu *sub, const char32_t *name, 
                                UICallback onClick, void *userData)
{
    Arena prev = ls_arenaUse(c->widgetArena);
    
    UIMenuItem newItem    = {};
    newItem.name          = ls_utf32FromUTF32(name);
    newItem.isVisible     = TRUE;
    newItem.callback1     = onClick;
    newItem.callback1Data = userData;
    UIMenuItem *result = ls_arrayAppend(&sub->items, newItem);
    
    ls_arenaUse(prev);
    return result;
}

UIMenuItem *ls_uiSubMenuAddItem(UIContext *c, UIMenu *menu, u32 subIdx, 
                                const char32_t *name, UICallback onClick, void *userData)
{
    Arena prev = ls_arenaUse(c->widgetArena);
    
    UIMenuItem newItem    = {};
    newItem.name          = ls_utf32FromUTF32(name);
    newItem.isVisible     = TRUE;
    newItem.callback1     = onClick;
    newItem.callback1Data = userData;
    UIMenuItem *result = ls_arrayAppend(&menu->subMenus[subIdx].items, newItem);
    
    ls_arenaUse(prev);
    return result;
}

b32 ls_uiMenu(UIContext *c, UIMenu *menu, s32 x, s32 y, s32 w, s32 h, s32 zLayer = 2)
{
    UIWindow *win = c->currWindow;
    Input *UserInput = &win->UserInput;
    b32 inputUse = FALSE;
    
    if(win->currentFocus != (u64 *)menu) { menu->isOpen = FALSE; }
    
    s32 subY = y;
    s32 subW = menu->itemWidth;
    s32 subH = h;
    
    s32 subCount  = menu->subMenus.count;
    s32 itemCount = menu->items.count;
    
    s32 closeX    = x + w - menu->closeWindow.bmp.w - 6;
    s32 maximizeX = closeX - menu->closeWindow.bmp.w - 6;
    s32 minimizeX = maximizeX - menu->maximize.bmp.w - 6;
    
    s32 dragX = x + ((subCount+itemCount)*subW);
    s32 dragH = h - 4; //NOTE: We are padding from the top to avoid drag+resize combo which can result in annoying behaviour
    
    if(LeftClickIn(dragX, y, minimizeX-dragX, dragH))
    {
        win->isDragging = TRUE;
        ls_uiFocusChange(c, 0);
        
        //NOTETODO: Maybe find a way to move platform specific code away?
        POINT currMouse = {};
        GetCursorPos(&currMouse);
        win->prevMousePosX = currMouse.x;
        win->prevMousePosY = currMouse.y;
        
        goto uiMenuRenderLabel;
    }
    
    for(u32 i = 0; i < subCount; i++)
    {
        UISubMenu *sub = menu->subMenus + i;
        sub->isHot = FALSE;
        
        s32 subX = x + (i*menu->itemWidth);
        
        if(menu->isOpen && menu->openIdx == i)
        {
            for(u32 j = 0; j < sub->items.count; j++)
            {
                UIMenuItem *currItem = sub->items + j;
                if(!currItem->isVisible) continue; 
                
                currItem->isHot = FALSE;
                
                s32 itemX = subX;
                s32 itemY = subY - (subH*(j+1));
                
                if(MouseInRect(itemX, itemY, menu->itemWidth, subH-1)) 
                { 
                    currItem->isHot = TRUE;
                    
                    if(LeftClick) {
                        //NOTETODO: mouseCapture vs focus????
                        win->mouseCapture = (u64 *)menu;
                        
                        //NOTE: currItem->onClick
                        if(currItem->callback1) { currItem->callback1(c, currItem->callback1Data); }
                        inputUse = TRUE;
                        
                        ls_uiFocusChange(c, 0);
                        menu->isOpen = FALSE;
                        
                    }
                }
            }
        }
        
        if(MouseInRect(subX, subY, subW, subH))
        {
            sub->isHot = TRUE;
            if(LeftClick) {
                ls_uiFocusChangeSameFrame(c, (u64 *)menu);
                
                menu->isOpen  = TRUE;
                menu->openIdx = i;
                break;
            }
        }
    }
    
    //NOTE: Items HAVE to come after submenus
    for(u32 i = 0; i < itemCount; i++)
    {
        UIMenuItem *item = menu->items + i;
        if(!item->isVisible) continue;
        
        item->isHot   = FALSE;
        s32 realIndex = i + subCount;
        s32 subX      = x + (realIndex*menu->itemWidth);
        
        if(MouseInRect(subX, subY, subW, subH)) {
            item->isHot = TRUE;
            
            if(LeftClick)
            {
                ls_uiFocusChange(c, 0);
                menu->isOpen = FALSE;
                
                //NOTE: item->onClick
                if(item->callback1) { inputUse |= item->callback1(c, item->callback1Data); }
            }
        }
    }
    
    //NOTE: goto label jump to avoid annoying mega-nesting ifs.
    uiMenuRenderLabel:
    
    
    //NOTE: Only render when the bitmap is set!
    if(menu->closeWindow.bmp.data)
        inputUse |= ls_uiButton(c, &menu->closeWindow, closeX, y + 2, 3);
    
    if(menu->maximize.bmp.data)
        inputUse |= ls_uiButton(c, &menu->maximize, maximizeX, y + 2, 3);

    if(menu->minimize.bmp.data)
        inputUse |= ls_uiButton(c, &menu->minimize, minimizeX, y + 2, 3);
    
    RenderCommand command = { UI_RC_MENU, x, y, w, h };
    command.menu          = menu;
    command.bkgColor      = c->menuBarColor;
    command.textColor     = c->textColor;
    ls_uiPushRenderCommand(c, command, zLayer);
    
    return inputUse;
}
