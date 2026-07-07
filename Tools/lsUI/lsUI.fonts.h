#pragma once

struct UIContext;
struct UIGlyph
{
    u8 *data;
    
    u32 codepoint;
    
    s32 width;
    s32 height;
    
    //TODO: Make these u16, since I doubt I'll have a single atlas larger than 65x65K pixels.
    s32 atlasX;
    s32 atlasY;
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;
    
    s32 xAdv;
    s32 yAdv;
    s32 leftSB;
};

struct UIAtlasMapEntry
{
    //NOTE: Since the Atlas goes from codepoint 0..N
    // the codepoint counts as an index in the Atlas.
    u32 codepoint;
    s32 atlasX;
    s32 atlasY;
    s32 width;
    s32 height;
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;
    s32 xAdv;
    s32 yAdv;
    s32 leftSB;
};

struct UIFontGroup;
struct UIAtlasIterator
{
    UIFontGroup *fontGroup;
    
    UIAtlasMapEntry *curr;
    UIAtlasMapEntry *last;
    s32 count;
    s32 idx;
    
    s32 currSize;
    s32 sizeIdx;
    
    b32 sizeChanged;
};

//TODO: Add max descent of font to adjust text vertical position in text boxes.
struct UIFont
{
    //NOTE: Either the font is loaded as a collection of glyph bitmaps at a specific size
    //      Or it's loaded as a single large bitmap, the font atlas, which right now can only be in SDF format
    union {
        UIGlyph *glyph;
        u8 *fontAtlas;
    };
    
    s32 pixelHeight;
    s32 ascent;
    s32 descent;
    s32 lineGap;
    
    s32 baselineOffset;
    
    //NOTE: The kernAdvanceTable may be null!
    s32 **kernAdvanceTable;
    
    //NOTETODO: Currently we determine if we're working with an atlas or a glyph array through this boolean
    //          Tagged unions would be cool.
    b32 isAtlas;
    s32 atlasWidth;
    s32 atlasHeight;
    
    s32 idxInGroup;
};

struct UIFontGroup
{
    UIFont *fonts;
    s32 fontCount;
    
    s32 codepointCount;
    s32 maxCodepoint;
    b32 isSDF;
    
#ifdef LS_UI_OPENGL_BACKEND
    //NOTE: As of right now OpenGL expects the font to be loaded as an SDFAtlas, 
    // uploaded to the gpu as a single large bitmap, represented by this texture ID.
    GLuint texID;
    GLuint atlasVAO;
#endif
};


void             ls_uiLoadPackedFontAtlas(UIContext *c, char *path);

s32              ls_uiGetKernAdvance(UIContext *c, s32 codepoint1, s32 codepoint2);
s32              ls_uiGetKernAdvance(UIFont *font, s32 codepoint1, s32 codepoint2);
s32              ls_uiGlyphAdv(UIContext *c, UIFont *f, u32 cp, u32 cpNext, f64 scale);

UIGlyph          ls_uiGetGlyphFromAtlas(UIContext *c, UIFont *font, u32 codepoint);
UIAtlasMapEntry *ls_uiGetAtlasMapEntry(UIContext *c, UIFont *font, u32 codepoint);
UIAtlasIterator  ls_uiAtlasIterStart(UIFontGroup *fontGroup);
void             ls_uiAtlasIterNext(UIAtlasIterator *iter);
b32              ls_uiAtlasIterSizeChanged(UIAtlasIterator iter);
b32              ls_uiAtlasIterDone(UIAtlasIterator iter);

u32              ls_uiSelectFontByPixelHeight(UIContext *c, u32 pixelHeight);
