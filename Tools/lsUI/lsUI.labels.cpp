#include "lsUI.labels.h"

//NOTE: ls_uiGlyphStringLayout calculates the height of the rectangle of the layout text 
//      (finalLayout.w, finalLayout.h in the return value).
//      It also returns the coordinates of where the next character would go, if you were to keep writing.
//      (finalLayout.x, finalLayout.y in the return value).
//
//      This is done to allow automatic layout of multiple strings inside a given rect (UILayoutRect).
UIRect ls_uiGlyphStringLayout(UIContext *c, UIFont *font, UILayoutRect layout, utf32 text)
{
    //TODO: Only one quirk remains, the y offset is determined based on the font height of the current element, 
    //      which obviously generates too large gaps when the font becomes smaller from one call to the 
    //      other and too small gaps when the font becomes bigger. The solution to this is to consider 
    //      the y Position when rendering a glyph the top left of the glyph (rather than the bottom left), 
    //      and subtract the font height to obtain the baseline. This way the y offset in layouting will 
    //      correctly move the y coordinate of the next line below the current line, regardless of font size.
    //      P.S.
    //      The baseline should already be present in the font, so why should I compute it?
    AssertMsg(c, "Context is null\n");
    LogMsg(font, "Passed font is null\n");
    if(!font) { return {}; }
    
    s32 currX          = layout.startX;
    s32 currY          = layout.startY;
    s32 currLineHeight = font->pixelHeight;
    const f64 scaling  = (f64)c->currPixelHeight / (f64)font->pixelHeight;
    for(u32 i = 0; i < text.len; i++)
    {
        u32 cp = text.data[i];
        u32 cpNext = 0xFFFFFFFF;
        if(i < text.len-1) {
            cpNext = text.data[i+1];
        }
        AssertMsgF(cp <= c->fontGroup.maxCodepoint, "GlyphIndex %d OutOfBounds\n", cp);
        AssertMsgF(cpNext == 0xFFFFFFFF || cpNext <= c->fontGroup.maxCodepoint, "CPN GlyphIndex %d OutOfBounds\n", cpNext);
        
        if(cp == (u32)'\n')
        { currX = layout.minX; currY -= font->pixelHeight; currLineHeight += font->pixelHeight; continue; }
        
        s32 advance = ls_uiGlyphAdv(c, font, cp, cpNext, scaling);
        if(currX + advance > layout.maxX)
        { currX = layout.minX; currY -= font->pixelHeight; currLineHeight += font->pixelHeight; continue; }
        
        currX += advance;
    }
    
    //UIRect finalLayout = { currX, currY, layout.maxX, currLineHeight };
    UIRect finalLayout = { currX, currY, layout.maxX, layout.startY - currY + (s32)font->pixelHeight };
    
    return finalLayout;
}


//TODO: Why do I need this?
UIRect ls_uiLabelRect(UIContext *c, utf32 label, s32 xPos, s32 yPos)
{
    s32 marginX    = 0.3f*c->currFont->pixelHeight;
    s32 marginY    = 0.3f*c->currFont->pixelHeight;
    
    UIRect rect = ls_uiGlyphStringRect(c, c->currFont, label, c->currFont->pixelHeight);
    s32 rectWidth  = rect.w + 2*marginX;
    s32 rectHeight = rect.h + 2*marginY; //TODO: Ascent/Descent, not this bullshit.
    
    return { xPos, yPos, rectWidth, rectHeight };
}

template<typename T>
void ls_uiLabelInRect(UIContext *c, T label, s32 x, s32 y, s32 minW, s32 minH, Color bkg, Color border, Color text, s32 zLayer = 0)
{
    s32 pixelHeight = c->currPixelHeight;
    s32 marginX     = 0.3f*pixelHeight;
    s32 marginY     = 0.25f*pixelHeight;
    
    UIRect rect    = ls_uiGlyphStringRect(c, c->currFont, label, pixelHeight);
    s32 rectWidth  = rect.w + 2*marginX;
    s32 rectHeight = rect.h + 2*marginY;
    
    if(rectWidth  < minW) { marginX += (minW - rectWidth) / 2;  rectWidth  = minW; }
    if(rectHeight < minH) { marginY += (minH - rectHeight) / 2; rectHeight = minH; }
    
    s32 labelOffset = rect.h - pixelHeight;
    ls_uiLabel(c, label, x + marginX, y + 2*marginY + labelOffset, text, zLayer);
    ls_uiRect(c, x, y, rectWidth, rectHeight, bkg, border, zLayer);
}

template<typename T>
void ls_uiLabelInRect(UIContext *c, T label, s32 x, s32 y, Color bkg, Color border, Color text, s32 zLayer = 0)
{
    const s32 max_positive = 0x7FFFFFFF;
    return ls_uiLabelInRect(c, label, x, y, max_positive, max_positive, bkg, border, text, zLayer);
}

void ls_uiLabel(UIContext *c, utf32 label, f32 relX, f32 relY, Color textColor, s32 zLayer = 0)
{
    UIWindow *win = c->currWindow;
    s32 xPos = win->width * relX;
    s32 yPos = win->height * relY;
    
    ls_uiLabel(c, label, xPos, yPos, textColor, zLayer);
}

//TODO: Think about memory management. constant literal values are accepted and not re-allocated
// Which must happen otherwise the memory would be constantly leaked (unless we used the frameArena)
// So it works, BUT ONLY FOR LITERALS!
// Nothing is stopping the user from constructing a string programmatically and passing
// a manually casted const char32_t or const u8 pointer. And fucking up memory.
template<typename T>
void ls_uiLabel(UIContext *c, T label, s32 x, s32 y, Color textColor, s32 zLayer = 0)
{
    AssertMsg(c, "Context pointer was null");
    AssertMsg(c->currFont, "No font was selected before sizing a label\n");
    
    RenderCommand command = {};
    if constexpr(typeid(T) == typeid(utf32))
    {
        s32 pixelHeight = c->currPixelHeight;
        UIRect rect = ls_uiGlyphStringRect(c, c->currFont, label, pixelHeight);
        s32 yBaseOff = rect.h - pixelHeight;
        command = { UI_RC_LABEL32, x, y - yBaseOff, rect.w, rect.h };
        command.textColor = textColor;

        if(label.len == 0) { return; }
        command.label32 = label;
    }
    else if constexpr(typeid(T) == typeid(utf8))
    {
        s32 pixelHeight = c->currPixelHeight;
        UIRect rect = ls_uiGlyphStringRect(c, c->currFont, label, pixelHeight);
        s32 yBaseOff = rect.h - pixelHeight;
        command = { UI_RC_LABEL32, x, y - yBaseOff, rect.w, rect.h };
        command.textColor = textColor;

        if(label.len == 0) { return; }
        command.type = UI_RC_LABEL8;
        command.label8 = label;
    }
    else if constexpr(typeid(T) == typeid(const char32_t*))
    {
        utf32 lab = ls_utf32Constant(label);

        s32 pixelHeight = c->currPixelHeight;
        UIRect rect = ls_uiGlyphStringRect(c, c->currFont, lab, pixelHeight);
        s32 yBaseOff = rect.h - pixelHeight;
        command = { UI_RC_LABEL32, x, y - yBaseOff, rect.w, rect.h };
        command.textColor = textColor;
        
        if(lab.len == 0) { return; }
        command.label32 = lab;
    }
    else if constexpr(typeid(T) == typeid(const u8*))
    {
        utf8 lab = ls_utf8Constant(label);

        s32 pixelHeight = c->currPixelHeight;
        UIRect rect = ls_uiGlyphStringRect(c, c->currFont, lab, pixelHeight);
        s32 yBaseOff = rect.h - pixelHeight;
        command = { UI_RC_LABEL32, x, y - yBaseOff, rect.w, rect.h };
        command.textColor = textColor;
        
        if(lab.len == 0) { return; }
        command.type = UI_RC_LABEL8;
        command.label8 = lab;
    }
    
    ls_uiPushRenderCommand(c, command, zLayer);
}

template<typename T>
void ls_uiLabel(UIContext *c, T label, s32 x, s32 y, s32 zLayer = 0)
{
    return ls_uiLabel(c, label, x, y, c->textColor, zLayer);
}


UILayoutRect ls_uiLabelLayout(UIContext *c, utf32 label, UILayoutRect layout, UIRect deltaPos,
                              Color textColor, s32 zLayer = 0)
{
    AssertMsg(c, "Context pointer was null");
    AssertMsg(c->currFont, "No font was selected before sizing a label\n");
    
    if(label.len == 0) { return {}; }
    
    //NOTE: layoutRegion.y refers to the top of the string, which grows downward
    //      The rect containing it has the y growing up, thus we offset it by it's height, deltaPos.h
    RenderCommand command = { UI_RC_LABEL_LAYOUT, layout.minX, deltaPos.y, layout.maxX-layout.minX, deltaPos.h };
    command.layout = { layout.minX, layout.minY, layout.maxX, deltaPos.h, layout.startX, layout.startY-deltaPos.h };
    command.label32       = label;
    command.textColor     = textColor;
    ls_uiPushRenderCommand(c, command, zLayer);
    
    UILayoutRect newLayout = { layout.minX, layout.minY, layout.maxX, deltaPos.h, deltaPos.x, deltaPos.y };
    return newLayout;
}

UILayoutRect ls_uiLabelLayout(UIContext *c, utf32 label, UILayoutRect layout, Color textColor, s32 zLayer = 0)
{
    AssertMsg(c, "Context pointer was null");
    AssertMsg(c->currFont, "No font was selected before sizing a label\n");
    
    if(label.len == 0) { return {}; }
    
    UIRect deltaPos = ls_uiGlyphStringLayout(c, c->currFont, layout, label);
    
    //NOTE: layoutRegion.y refers to the top of the string, which grows downward
    //      The rect containing it has the y growing up, thus we offset it by it's height, deltaPos.h
    RenderCommand command = { UI_RC_LABEL_LAYOUT, layout.minX, deltaPos.y, layout.maxX-layout.minX, deltaPos.h };
    command.layout = { layout.minX, layout.minY, layout.maxX, deltaPos.h, layout.startX, layout.startY-deltaPos.h };
    command.label32       = label;
    command.textColor     = textColor;
    ls_uiPushRenderCommand(c, command, zLayer);
    
    UILayoutRect newLayout = { layout.minX, layout.minY, layout.maxX, deltaPos.h, deltaPos.x, deltaPos.y };
    return newLayout;
}

UILayoutRect ls_uiLabelLayout(UIContext *c, const char32_t *label, UILayoutRect layout, 
                              Color textColor, s32 zLayer = 0)
{
    utf32 lab = ls_utf32Constant(label);
    return ls_uiLabelLayout(c, lab, layout, textColor, zLayer);
}

UILayoutRect ls_uiLabelLayout(UIContext *c, utf32 label, UILayoutRect layout, s32 zLayer = 0)
{
    return ls_uiLabelLayout(c, label, layout, c->textColor, zLayer);
}

UILayoutRect ls_uiLabelLayout(UIContext *c, const char32_t *label, UILayoutRect layout, s32 zLayer = 0)
{
    utf32 lab = ls_utf32Constant(label);
    return ls_uiLabelLayout(c, lab, layout, c->textColor, zLayer);
}

