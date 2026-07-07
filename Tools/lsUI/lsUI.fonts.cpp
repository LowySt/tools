#include "lsUI.fonts.h"

void ls_uiLoadPackedFontAtlas(UIContext *c, char *path)
{
    //TODO: If I'm working with the GPU, do I actually need the Atlas Data to be kept in RAM?
    // After we upload it, can't it just stay on the GPU?
    
    Arena prev = ls_arenaUse(c->scratchArena);
    
    u8 *bitmapFile = NULL;
    u64 bytesRead = ls_readFile(path, (char **)&bitmapFile, 0);
    
    ls_arenaUse(c->contextArena);
    
    b32 isWindowyfied = FALSE;
    u32 PixelOffset   = *((u32 *)((char *)bitmapFile + 10));
    u32 HeaderSize    = *((u32 *)((char *)bitmapFile + 14));
    
    s32 Width  = *((s32 *)((char *)bitmapFile + 18));
    s32 Height = *((s32 *)((char *)bitmapFile + 22));
    if(Height < 0) { isWindowyfied = TRUE; Height = -Height; }
    
    u32 Compression     = *((u32 *)((char *)bitmapFile + 30));
    u32 PixelBufferSize = *((u32 *)((char *)bitmapFile + 34));
    u8 *atlasData       = (u8 *)((char *)bitmapFile + PixelOffset);
    
    s32 *metaInfo = ((s32*)(atlasData + ((Width*Height) - sizeof(s32))));
    c->fontGroup.fontCount      = metaInfo[-1];
    c->fontGroup.isSDF          = metaInfo[-2];
    c->fontGroup.codepointCount = metaInfo[-3];
    c->fontGroup.maxCodepoint   = metaInfo[-3];

    //TODO: If ls_uiLoadPackedFontAtlas is called multiple times, it leaks memory
    // because of this allocation being put in the contextArena without ever being freed
    // first...
    // For development it may be nice to test different fonts quickly, but it's a possible problem!
    c->fontGroup.fonts          = (UIFont *)ls_alloc(sizeof(UIFont)*c->fontGroup.fontCount);
    
    metaInfo -= 3;
    for(s32 sizesIdx = c->fontGroup.fontCount-1; sizesIdx >= 0; sizesIdx--)
    {
        UIFont *f = c->fontGroup.fonts + sizesIdx;
        
        f->fontAtlas   = atlasData;
        f->atlasWidth  = Width;
        f->atlasHeight = Height;
        f->isAtlas     = TRUE;
        
        f->pixelHeight = metaInfo[-1];
        f->lineGap     = metaInfo[-2];
        f->descent     = metaInfo[-3];
        f->ascent      = metaInfo[-4];
        metaInfo      -= 4;
        
        //TODO: Why am I not generating kernAdvanceTable??
        f->kernAdvanceTable = NULL;
        f->idxInGroup       = sizesIdx;
    }
    
    c->currFont                   = c->fontGroup.fonts;
    c->currPixelHeight            = c->fontGroup.fonts[0].pixelHeight;
    
#ifdef LS_UI_OPENGL_BACKEND
    // -------------------------------------------
    //NOTE: Generate and load to the gpu the Atlas
    //
    glGenTextures(1, &c->fontGroup.texID);
    GLenum err = glGetError();
    if(err != GL_NO_ERROR) {
        AssertMsgF(FALSE, "Coldn't Gen Textures for Font Atlas, Error: %d", err);
    }
    
    glBindTexture(GL_TEXTURE_2D, c->fontGroup.texID);
    
    err = glGetError();
    if(err != GL_NO_ERROR) {
        AssertMsgF(FALSE, "Couldn't Bind Generated Textures for Font Atlas, Error: %d", err);
    }
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, Width, Height, 0, GL_RED, GL_UNSIGNED_BYTE, c->fontGroup.fonts[0].fontAtlas);
    
    err = glGetError();
    if(err != GL_NO_ERROR) {
        AssertMsgF(FALSE, "Couldn't TexImage2D for Font Atlas, Error: %d", err);
    }
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // -------------------------------------------
    //NOTE: Setup VAO/VBO to have the correct UV for each glyph in the atlas
    //
    
    ls_arenaUse(c->scratchArena);
    
    s32 glyphCountPerSize = c->fontGroup.codepointCount;
    s32 totalGlyphCount   = c->fontGroup.codepointCount*c->fontGroup.fontCount;
    
    const s32 verticesPerGlyph        = 6;
    const s32 floatsPerVertex         = 6;
    const s32 sizeOfSingleGlyphVertex = verticesPerGlyph * floatsPerVertex * sizeof(f32);
    s32 sizeOfVertexMap = totalGlyphCount * sizeOfSingleGlyphVertex;
    f32 *glyphVertexMap = (f32 *)ls_alloc(sizeOfVertexMap);
    s32 glyphVertMapIdx = 0;
    
    UIAtlasIterator atlasIt = ls_uiAtlasIterStart(&c->fontGroup);
    UIFont *font = c->fontGroup.fonts + atlasIt.sizeIdx;
    font->baselineOffset = (s32)(((f32)font->ascent - (f32)font->descent) * 0.5);
    for(; !ls_uiAtlasIterDone(atlasIt); ls_uiAtlasIterNext(&atlasIt))
    {
        if(ls_uiAtlasIterSizeChanged(atlasIt))
        {
            font = c->fontGroup.fonts + atlasIt.sizeIdx;
            font->baselineOffset = (s32)(((f32)font->ascent - (f32)font->descent) * 0.5);
        }
        
        UIAtlasMapEntry *map = atlasIt.curr;
        
        f32 texelLeft  = (f32)map->atlasX / (f32)font->atlasWidth;
        f32 texelRight = (f32)(map->atlasX+map->width) / (f32)font->atlasWidth;
        f32 texelBot   = (f32)map->atlasY / (f32)font->atlasHeight;
        f32 texelTop   = (f32)(map->atlasY+map->height) / (f32)font->atlasHeight;
        
        //NOTE: To avoid headaches, all glyphs are positioned in the center of the unit square
        // the x/y coordinates of the final glyph would have needed to be mapped to floats anyway,
        // so going from 0..c->width/c->height -> -1..1 is not that big of a deal.
        
        //NOTE: Map lengths
        //map->xAdv   = (f32)map->xAdv * 0.5;
        //map->yAdv   = (f32)map->yAdv * 0.5;
        
        //NOTE:
        // To align a glyph to the baseline, if the glyph extends below the baseline
        // it needs to be adjusted by the amount it extends (either y0 or y1 based on if we measure y-up or y-down)
        // BUT: The Normalized Device Unit of OpenGL should go from -1.0..1.0
        // Which means, to normalize y1 to -1..1, we would need to:
        //    divide by the max y1/height -> range 0..1
        //    multiply by 2.0             -> range 0..2
        //    subtract 1.0                -> range -1..1
        //
        // *BUT* I presume, that being a baseline-relative measurement, it is indipendent of a -1..1 range, and only
        // cares about the 'fraction' of height of the glyph it needs to move below.
        // So we are not mapping to a -1..1 range here. Just taking the right fraction.
        
        //NOTE: To make sure glyphs are resolution-indipendent, we are passing the glyph's dimensions
        // to the shader (and the viewport's dimensions as a uniform) and we map in the vertex shader itself.
        //NOTE: I guess... instead of dividing lenghts (like xAdv and yAdv) by 2, we can multiply widths/height by 2?
        f32 mw = (f32)map->width * 2.0;
        f32 mh = (f32)map->height * 2.0;
        f32 y0 = (f32)map->y0;
        f32 y1 = (f32)map->y1;
        
        //Vertex Data (localX, localY, texU, texV, y0, y1)
        f32 verticesCurrent[verticesPerGlyph][floatsPerVertex] =
        {
            { 0.0, 0.0, texelLeft,  texelTop, y0, y1 },  // Bottom-left
            { 0.0,  mh, texelLeft,  texelBot, y0, y1 },  // Top-left
            {  mw, 0.0, texelRight, texelTop, y0, y1 },  // Bot-right
            
            {  mw, 0.0, texelRight, texelTop, y0, y1 },  // Bot-right
            { 0.0,  mh, texelLeft,  texelBot, y0, y1 },  // Top-left
            {  mw,  mh, texelRight, texelBot, y0, y1 }   // Top-right
        };
        
        ls_memcpy(verticesCurrent, glyphVertexMap + glyphVertMapIdx, sizeOfSingleGlyphVertex);
        glyphVertMapIdx += (verticesPerGlyph * floatsPerVertex);
    }
    
    GLuint VBO;
    glGenVertexArrays(1, &c->fontGroup.atlasVAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(c->fontGroup.atlasVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    //NOTE: Since you can free the underling buffer after the call to glBufferData, this means
    // that glBufferData will copy over the data right here. I'm not sure if it uploads it to the gpu
    // or create a temporary copy in RAM (which would be undesirable)
    // TODO: Look into glMapBufferRange() which apparently does things a little different
    glBufferData(GL_ARRAY_BUFFER, sizeOfVertexMap, glyphVertexMap, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(float), (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(float), (void *)(4 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    ls_arenaClear(c->scratchArena);
#endif
    
    ls_arenaUse(prev);
    return;
}


s32 ls_uiGetKernAdvance(UIContext *c, s32 codepoint1, s32 codepoint2)
{
    AssertNonNull(c);
    AssertNonNull(c->currFont);
    AssertNonNull(c->currFont->kernAdvanceTable);
    
    UIFont *font = c->currFont;
    s32 kernAdvance = font->kernAdvanceTable[codepoint1][codepoint2];
    
    return kernAdvance;
}

s32 ls_uiGetKernAdvance(UIFont *font, s32 codepoint1, s32 codepoint2)
{
    AssertNonNull(font);
    AssertNonNull(font->kernAdvanceTable);
    
    s32 kernAdvance = font->kernAdvanceTable[codepoint1][codepoint2];
    
    return kernAdvance;
}

s32 ls_uiGlyphAdv(UIContext *c, UIFont *f, u32 cp, u32 cpNext, f64 scale)
{
#if defined(LS_UI_OPENGL_BACKEND)
    if(f->isAtlas)
    {
        UIAtlasMapEntry *map = ls_uiGetAtlasMapEntry(c, f, cp);
        return (map->xAdv*scale);
    }
    else { AssertMsg(FALSE, "Unhandled case: OpenGL uiGlyph without an atlas"); return 0; }
#elif defined(LS_UI_SOFTWARE_BACKEND)
    s32 advance = 0;
    if(f->isAtlas)
    {
        UIGlyph g = ls_uiGetGlyphFromAtlas(c, f, cp);
        advance = g.xAdv*scale;
        return advance;
    }
    else
    {
        UIGlyph g = f->glyph[cp];
        s32 kernAdvance = 0;
        if(cpNext != 0xFFFFFFFF) { kernAdvance = ls_uiGetKernAdvance(f, cp, cpNext); }
        advance = (g.xAdv + kernAdvance)*scale;
        return advance;
    }
    
    AssertMsg(FALSE, "Unreachable");
    return 0;
#else
    
#error Unhandled backend in ls_uiGlyph()
    
#endif
}


UIAtlasMapEntry *ls_uiGetAtlasMapEntry(UIContext *c, UIFont *font, u32 codepoint)
{
    AssertNonNull(c);
    AssertNonNull(font);
    AssertNonNull(font->fontAtlas);
    AssertMsgF(codepoint <= c->fontGroup.maxCodepoint, "Codepoint %d is not present in the Atlas. Max Codepoint is: %d\n", codepoint, c->fontGroup.maxCodepoint);
    
    s32 mapSize    = *((s32*)(font->fontAtlas + ((font->atlasWidth*font->atlasHeight) - sizeof(s32))));
    s32 glyphCount = c->fontGroup.codepointCount;
    s32 sizeCount  = c->fontGroup.fontCount;
    s32 index = 0;
    
    s32 wantedSizeIdx = -1;
    for(s32 i = 0; i < sizeCount; i++)
    {
        UIFont *curr = c->fontGroup.fonts + i;
        wantedSizeIdx = i;
        if(curr == font) { break; }
    }
    AssertMsg(wantedSizeIdx >= 0, "Could not find matching font when looking for Codepoint Map Entry!\n");
    
    //TODO: Keep this offset around in the UIFontGroup...
    UIAtlasMapEntry *mapBegin = (UIAtlasMapEntry *)(font->fontAtlas + ((font->atlasWidth*font->atlasHeight) - mapSize));
    UIAtlasMapEntry *wanted_map = mapBegin + (wantedSizeIdx*glyphCount) + codepoint;
    
    AssertMsg(wanted_map->codepoint == codepoint, "Internal Discrepancy. Wanted codepoint does not match map.\n");
    
    return wanted_map;
}

UIGlyph ls_uiGetGlyphFromAtlas(UIContext *c, UIFont *font, u32 codepoint)
{
    AssertNonNull(c);
    AssertNonNull(font);
    AssertNonNull(font->fontAtlas);
    
    UIAtlasMapEntry *map = ls_uiGetAtlasMapEntry(c, font, codepoint);
    UIGlyph result = { 
        .data      = &font->fontAtlas[map->atlasY*font->atlasWidth + map->atlasX],
        .codepoint = codepoint,
        .width     = map->width,
        .height    = map->height,
        .x0        = map->x0,
        .y0        = map->y0,
        .x1        = map->x1,
        .y1        = map->y1,
        .xAdv      = map->xAdv,
        .yAdv      = map->yAdv,
        .leftSB    = map->leftSB,
    };
    
    return result;
}

UIAtlasIterator ls_uiAtlasIterStart(UIFontGroup *fontGroup)
{
    AssertNonNull(fontGroup);
    AssertNonNull(fontGroup->fonts[0].fontAtlas);
    
    UIFont *f = fontGroup->fonts;
    
    s32 mapSize    = *((s32*)(f->fontAtlas + ((f->atlasWidth*f->atlasHeight) - sizeof(s32))));
    s32 glyphCount = fontGroup->codepointCount;
    s32 sizesCount = fontGroup->fontCount;
    UIAtlasMapEntry *map  = (UIAtlasMapEntry *)(f->fontAtlas + ((f->atlasWidth*f->atlasHeight) - mapSize));
    UIAtlasMapEntry *last = map + (glyphCount*sizesCount);
    UIAtlasIterator iter = { fontGroup, map, last, glyphCount*sizesCount, 0, f->pixelHeight, 0 };
    return iter;
}

void ls_uiAtlasIterNext(UIAtlasIterator *iter)
{
    AssertNonNull(iter);
    AssertNonNull(iter->curr);
    AssertNonNull(iter->last);
    AssertMsg(iter->idx < iter->count, "Going past last index in Atlas Iterator");
    AssertMsg(iter->curr != iter->last, "Going past last entry in Atlas Iterator");
    
    iter->curr += 1;
    iter->idx  += 1;
    
    s32 prevSizeIdx = iter->sizeIdx;
    
    //NOTETODO: We could do this branchless, just always setting the the currSizeIdx, rather than checking
    s32 currSizeIdx = iter->idx / iter->fontGroup->codepointCount;
    if(currSizeIdx != iter->sizeIdx)
    {
        AssertMsgF(iter->sizeIdx+1 == currSizeIdx, "Expected size idx: %d, Calculated: %d", currSizeIdx, iter->sizeIdx+1);
        
        iter->sizeIdx += 1;
    }
    
    //NOTE: If it's the same, it will be 0, so FALSE
    // Otherwise it will not be 0 (should be 1), so TRUE
    iter->sizeChanged = iter->sizeIdx - prevSizeIdx;
    
    return;
}

b32 ls_uiAtlasIterSizeChanged(UIAtlasIterator iter)
{
    AssertNonNull(iter.curr);
    AssertNonNull(iter.last);
    
    return iter.sizeChanged;
}

b32 ls_uiAtlasIterDone(UIAtlasIterator iter)
{
    AssertNonNull(iter.curr);
    AssertNonNull(iter.last);
    
    if(iter.curr >= iter.last) { return TRUE; }
    return FALSE;
}


u32 ls_uiSelectFontByPixelHeight(UIContext *c, u32 pixelHeight)
{
    LogMsg(c->fontGroup.fonts, "No fonts were loaded\n");
    //AssertMsg(c->currFont, "The currFont was not selected!\n");

    u32 prevPixelHeight = c->currPixelHeight;
    if(!c->fontGroup.fonts) { return prevPixelHeight; }
    c->currPixelHeight = pixelHeight;
    
    if(c->currFont->isAtlas)
    {
        //NOTE: The first font in the group is always the largest one!
        UIFont *bestMatch = c->fontGroup.fonts + (c->fontGroup.fontCount-1);
        s32 bestMatchDiff = bestMatch->pixelHeight - pixelHeight;
        if(bestMatchDiff < 0)
        {
            c->currFont = bestMatch;
            return prevPixelHeight;
        }
        
        for(s32 sizesIdx = c->fontGroup.fontCount-2; sizesIdx >= 0; sizesIdx--)
        {
            UIFont *curr = c->fontGroup.fonts + sizesIdx;
            s32 diff = curr->pixelHeight - pixelHeight;
            
            //NOTETODO: This always picks the closest, but maybe I want to pick the
            // biggest pixelHeight that is closest, because shrinking is better than
            // enlarging without applying filters?
            if(diff < 0) { return prevPixelHeight; }
            
            if(curr->pixelHeight == pixelHeight)
            { 
                c->currFont = curr;
                return prevPixelHeight;
            }
            
            if(diff < bestMatchDiff) { bestMatch = curr; bestMatchDiff = diff; }
        }
        
        c->currFont = bestMatch;
        return prevPixelHeight;
    }
    else
    {
        for(u32 i = 0; i < 4; i++)
        { if(c->fontGroup.fonts[i].pixelHeight == pixelHeight) { c->currFont = &c->fontGroup.fonts[i]; return prevPixelHeight; } }
    }
    
    AssertMsgF(FALSE, "Asked pixelHeight %d not available\n", pixelHeight);
    return 0;
}


//TODO: Should actually have totalWidth and totalHeight be floating point instead of ints
//      Because of scaling, the intermediate values will probably be fractional, and flooring
//        at the end should yield more accurate results, especially in long strings!
template<typename T>
UIRect ls_uiGlyphStringRect(UIContext *c, UIFont *font, T text, s32 pixelHeight)
{
    AssertMsg(c, "Context is null\n");
    LogMsg(font, "Passed font is null\n");
    if(!font) { return {}; }
    
    s32 maxWidth = 0;
    s32 totalWidth  = 0;
    s32 totalHeight = pixelHeight;
    
    f64 scaling = (f64)pixelHeight / (f64)font->pixelHeight;
    s32 lineSpace = font->ascent*scaling - font->descent*scaling + font->lineGap*scaling;
    
    for(u32 i = 0; i < text.len; i++)
    {
        u32 cp = 0xFFFFFFFF, cpNext = 0xFFFFFFFF;
        if constexpr(typeid(T) == typeid(utf32))
        { cp = text.data[i]; cpNext = i < text.len-1 ? text.data[i+1] : 0xFFFFFFFF; }
        else if constexpr(typeid(T) == typeid(utf8))
        { cp = ls_utf32CharFromUtf8(text, i); cpNext = i < text.len-1 ? ls_utf32CharFromUtf8(text, i+1) : 0xFFFFFFFF; }
        else
        { AssertMsg(FALSE, "Invalid use of string type. Only utf32 and utf8 are supported"); }
        
        AssertMsgF(cp <= c->fontGroup.maxCodepoint, "CP GlyphIndex %d OutOfBounds\n", cp);
        AssertMsgF(cpNext == 0xFFFFFFFF || cpNext <= c->fontGroup.maxCodepoint, "CPN GlyphIndex %d OutOfBounds\n", cpNext);
        
        totalWidth += ls_uiGlyphAdv(c, font, cp, cpNext, scaling);
        if(cp == (u32)'\n')       { totalWidth = 0; totalHeight += lineSpace; }
        if(totalWidth > maxWidth) { maxWidth = totalWidth; }
    }
    
    UIRect result = {0, 0, maxWidth, totalHeight};
    return result;
}

template<typename T>
void ls_uiGlyphString(UIContext *c, UIFont *font, s32 pixelHeight, s32 xPos, s32 yPos,
                      UIRect threadRect, UIRect scissor, T text, Color textColor)
{
    AssertMsg(c, "Context is null\n");
    LogMsg(font, "Passed font is null\n");
    if(!font) { return; }
    
    //TODO: Does it ever make sense to use LeftSideBearing on the left edge of the viewport?
    // Seems easier to just keep an healthy pad. It's not `font-indipendent` but who cares?
    s32 currXPos  = xPos;
    s32 currYPos  = yPos;
    f64 scaling   = (f64)pixelHeight / (f64)font->pixelHeight;
    s32 lineSpace = font->ascent*scaling - font->descent*scaling + font->lineGap*scaling;
    
    for(u32 i = 0; i < text.len; i++)
    {
        u32 cp = 0xFFFFFFFF;
        u32 cpNext = 0xFFFFFFFF;
        if constexpr(typeid(T) == typeid(utf32))
        { cp = text.data[i]; cpNext = i < text.len-1 ? text.data[i+1] : 0xFFFFFFFF; }
        else if constexpr(typeid(T) == typeid(utf8))
        { cp = ls_utf32CharFromUtf8(text, i); cpNext = i < text.len-1 ? ls_utf32CharFromUtf8(text, i+1) : 0xFFFFFFFF; }
        else
        { AssertMsg(FALSE, "Invalid use of string type. Only utf32 and utf8 are supported"); }
        AssertMsgF(cp <= c->fontGroup.maxCodepoint, "GlyphIndex %d OutOfBounds\n", cp);
        AssertMsgF(cpNext == 0xFFFFFFFF || cpNext <= c->fontGroup.maxCodepoint, "CPN GlyphIndex %d OutOfBounds\n", cpNext);
        
        s32 xAdvance = ls_uiGlyph(c, font, cp, cpNext, currXPos, currYPos, scaling, threadRect, scissor, textColor);
        currXPos += xAdvance;
        if(cp == (u32)'\n') { currXPos = xPos; currYPos -= lineSpace; }
    }
}


//TODO: Should I always pass a layout, and maybe only keep an helper when I want no layout, so the layout region
//      would just be the entire window???
void ls_uiGlyphStringInLayout(UIContext *c, UIFont *font, UILayoutRect layout,
                              UIRect threadRect, UIRect scissor, utf32 text, Color textColor)
{
    AssertMsg(c, "Context is null\n");
    LogMsg(font, "Passed font is null\n");
    if(!font) { return; }
    
    s32 currXPos = layout.startX;
    s32 currYPos = layout.startY + layout.maxY;
    for(u32 i = 0; i < text.len; i++)
    {
        u32 cp = text.data[i];
        u32 cpNext = i < text.len - 1 ? text.data[i+1] : 0xFFFFFFFF;
        AssertMsgF(cp <= c->fontGroup.maxCodepoint, "GlyphIndex %d OutOfBounds\n", cp);
        AssertMsgF(cpNext == 0xFFFFFFFF || cpNext <= c->fontGroup.maxCodepoint, "CPN GlyphIndex %d OutOfBounds\n", cpNext);
        
        if(cp == (u32)'\n') {
            currYPos -= font->pixelHeight;
            currXPos = layout.minX;
            continue;
        }
        
        s32 newAdvance = ls_uiGlyph(c, font, cp, cpNext, currXPos, currYPos, 1.0, threadRect, scissor, textColor);
        if((currXPos + newAdvance) > (layout.maxX))
        { 
            currYPos -= font->pixelHeight; 
            currXPos = layout.minX;
            continue;
        }
        
        currXPos += newAdvance;
    }
}

