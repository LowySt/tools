#include "lsUI.rects.h"

inline
void ls_uiBorder(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h,
                 UIRect threadRect, UIRect scissor)
{
    Color C = c->borderColor;
    
    ls_uiFillRect(c, xPos,     yPos,     w, 1, threadRect, scissor, C);
    ls_uiFillRect(c, xPos,     yPos+h-1, w, 1, threadRect, scissor, C);
    ls_uiFillRect(c, xPos,     yPos,     1, h, threadRect, scissor, C);
    ls_uiFillRect(c, xPos+w-1, yPos,     1, h, threadRect, scissor, C);
}

inline
void ls_uiBorder(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h,
                 UIRect threadRect, UIRect scissor, Color borderColor)
{
    Color C = borderColor;
    
    ls_uiFillRect(c, xPos,     yPos,     w, 1, threadRect, scissor, C);
    ls_uiFillRect(c, xPos,     yPos+h-1, w, 1, threadRect, scissor, C);
    ls_uiFillRect(c, xPos,     yPos,     1, h, threadRect, scissor, C);
    ls_uiFillRect(c, xPos+w-1, yPos,     1, h, threadRect, scissor, C);
}

inline
void ls_uiBorderedRect(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h,
                       UIRect threadRect, UIRect scissor)
{
    ls_uiBorder(c, xPos, yPos, w, h, threadRect, scissor);
    ls_uiFillRect(c, xPos+1, yPos+1, w-2, h-2, threadRect, scissor, c->widgetColor);
}

inline
void ls_uiBorderedRect(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h,
                       UIRect threadRect, UIRect scissor, Color widgetColor)
{
    ls_uiBorder(c, xPos, yPos, w, h, threadRect, scissor);
    ls_uiFillRect(c, xPos+1, yPos+1, w-2, h-2, threadRect, scissor, widgetColor);
}

inline
void ls_uiBorderedRect(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h, 
                       UIRect threadRect, UIRect scissor, Color widgetColor, Color borderColor)
{
    ls_uiBorder(c, xPos, yPos, w, h, threadRect, scissor, borderColor);
    ls_uiFillRect(c, xPos+1, yPos+1, w-2, h-2, threadRect, scissor, widgetColor);
}

inline
void ls_uiRect(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h,
               UIRect threadRect, UIRect scissor)
{
    ls_uiFillRect(c, xPos, yPos, w, h, threadRect, scissor, c->widgetColor);
}

inline
void ls_uiRect(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h, 
               UIRect threadRect, UIRect scissor, Color widgetColor)
{
    ls_uiFillRect(c, xPos, yPos, w, h, threadRect, scissor, widgetColor);
}


//TODO @UIPos
void ls_uiRect(UIContext *c, s32 x, s32 y, s32 w, s32 h, Color bkgColor, Color borderColor, s32 zLayer = 0)
{
    RenderCommand command = { UI_RC_RECT, x, y, w, h };
    command.bkgColor      = bkgColor;
    command.borderColor   = borderColor;
    
    ls_uiPushRenderCommand(c, command, zLayer);
}

//TODO @UIPos
void ls_uiRect(UIContext *c, s32 x, s32 y, s32 w, s32 h, s32 zLayer = 0)
{
    RenderCommand command = { UI_RC_RECT, x, y, w, h };
    command.bkgColor    = c->widgetColor;
    command.borderColor = c->borderColor;
    
    ls_uiPushRenderCommand(c, command, zLayer);
}

//TODO @UIPos
void ls_uiRect(UIContext *c, UIPos pos, Color bkgColor, Color borderColor, s32 zLayer = 0)
{
    RenderCommand command = { UI_RC_RECT };
    command.pos           = pos;
    command.bkgColor      = bkgColor;
    command.borderColor   = borderColor;

    ls_uiPushRenderCommand(c, command, zLayer);
}


//TODO @UIPos
void ls_uiHSeparator(UIContext *c, s32 x, s32 y, s32 width, s32 lineWidth, Color lineColor, s32 zLayer = 0)
{
    RenderCommand command = { UI_RC_SEPARATOR, x, y, width, lineWidth };
    command.borderColor   = lineColor;
    ls_uiPushRenderCommand(c, command, zLayer);
    
    //TODO: Do I like this???
    command.rect.y       += 1;
    command.borderColor   = ls_uiDarkenRGB(command.borderColor, 0.10f);
    ls_uiPushRenderCommand(c, command, zLayer);
}

//TODO @UIPos
void ls_uiHSeparator(UIContext *c, UIPos pos, Color lineColor, s32 zLayer = 0)
{
    RenderCommand command = { UI_RC_SEPARATOR }; 
    command.borderColor   = lineColor;
    command.pos           = pos;
    ls_uiPushRenderCommand(c, command, zLayer);
    
    //TODO: Do I like this???
    if (pos.kind == UIPosKind::Abs) { command.pos.iy += 1; }
    else { command.pos.fy += 1.0f / (f32)c->currWindow->height; }

    command.borderColor   = ls_uiDarkenRGB(command.borderColor, 0.10f);
    ls_uiPushRenderCommand(c, command, zLayer);
}

//TODO @UIPos
void ls_uiVSeparator(UIContext *c, s32 x, s32 y, s32 height, s32 lineWidth, Color lineColor, s32 zLayer = 0)
{
    RenderCommand command = { UI_RC_SEPARATOR, x, y, lineWidth, height };
    command.borderColor = lineColor;
    ls_uiPushRenderCommand(c, command, zLayer);
    
    //TODO: Do I like this???
    command.rect.x += 1;
    command.borderColor = ls_uiDarkenRGB(command.borderColor, 0.10f);
    ls_uiPushRenderCommand(c, command, zLayer);
}

//TODO @UIPos
void ls_uiVSeparator(UIContext *c, UIPos pos, Color lineColor, s32 zLayer = 0)
{
    RenderCommand command = { UI_RC_SEPARATOR };
    command.borderColor = lineColor;
    command.pos         = pos;
    ls_uiPushRenderCommand(c, command, zLayer);
    
    //TODO: Do I like this???
    if (pos.kind == UIPosKind::Abs) { command.pos.ix += 1; }
    else { command.pos.fx += 1.0f / (f32)c->currWindow->width; }

    command.borderColor = ls_uiDarkenRGB(command.borderColor, 0.10f);
    ls_uiPushRenderCommand(c, command, zLayer);
}



void ls_uiTexturedRect(UIContext *c, s32 x, s32 y, s32 w, s32 h, void *data, s32 dataW, s32 dataH, s32 zLayer = 0)
{
    RenderCommand command = { UI_RC_TEXTURED_RECT, x, y, w, h };
    command.bitmap = { data, dataW, dataH };
    ls_uiPushRenderCommand(c, command, zLayer);
}


UIRect ls_uiScreenCoordsToUnitSquare(UIContext *c, s32 x, s32 y, s32 w, s32 h)
{
    UIRect result = {};
    result.leftX  = (2.0f*(f32)x / (f32)c->currWindow->width)-1.0f;
    result.botY   = (2.0f*(f32)y / (f32)c->currWindow->height)-1.0f;
    result.rightX = (2.0f*(f32)(x+w) / (f32)c->currWindow->width)-1.0f;
    result.topY   = (2.0f*(f32)(y+h) / (f32)c->currWindow->height)-1.0f;
    return result;
}
