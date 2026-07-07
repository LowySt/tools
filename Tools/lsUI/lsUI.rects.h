#pragma once

//TODO: The difference between how the command rect and the thread rect's members are used is confusing
//      and error prone. One uses x,y,w,h. The other uses minX,minY,maxX,maxY. @ConfusingUnion
//      Should probably have 2 different types:
//      UIRect       should use (x,y,w,h)
//      UIRectRange? should use (minX,minY,maxX,maxY) 
union UIRect
{
    struct { s32 minX, minY, maxX, maxY; };
    struct { s32 x,    y,    w,    h; };
    struct { f32 leftX, botY, rightX, topY; };
};

struct UILayoutRect
{
    s32 minX, minY, maxX, maxY;
    s32 startX, startY;
};


void   ls_uiBorder(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h, UIRect threadRect, UIRect scissor, Color col);
void   ls_uiRect(UIContext *c, s32 x, s32 y, s32 w, s32 h, Color bkgColor, Color borderColor, s32 zLayer);
void   ls_uiRect(UIContext *c, UIPos pos, Color bkgColor, Color borderColor, s32 zLayer);
void   ls_uiHSeparator(UIContext *c, s32 x, s32 y, s32 width, s32 lineWidth, Color lineColor, s32 zLayer);
void   ls_uiHSeparator(UIContext *c, UIPos pos, Color lineColor, s32 zLayer);
void   ls_uiVSeparator(UIContext *c, s32 x, s32 y, s32 height, s32 lineWidth, Color lineColor, s32 zLayer);
void   ls_uiVSeparator(UIContext *c, UIPos pos, Color lineColor, s32 zLayer);
void   ls_uiTexturedRect(UIContext *c, s32 x, s32 y, s32 w, s32 h, void *data, s32 dataW, s32 dataH, s32 zLayer);
UIRect ls_uiScreenCoordsToUnitSquare(UIContext *c, s32 x, s32 y, s32 w, s32 h);
