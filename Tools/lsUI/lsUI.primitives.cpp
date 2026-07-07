#include "lsUI.primitives.h"

void ls_uiFillRect(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h, UIRect threadRect, UIRect scissor, Color col)
{
    UIWindow *win = c->currWindow;

#ifdef LS_UI_OPENGL_BACKEND
    
    glUseProgram(c->rectShader);
    glUniform4ui(glGetUniformLocation(c->rectShader, "color"), col.r, col.g, col.b, col.a);
    
    f32 normZ = 1.0f ;//- ((f32)c->zLayer / (f32)(UI_Z_LAYERS-1));
    glUniform1f(glGetUniformLocation(c->rectShader, "zLayer"), normZ);
    
    f64 xf = (f64)xPos;
    f64 yf = (f64)yPos;
    f64 wf = (f64)win->width;
    f64 hf = (f64)win->height;
    
    // Positions need to be adjusted by the width and height... for some reason?
    f64 xp = ((xf + (f64)w / 2.0) / (wf / 2.0)) - 1.0;
    f64 yp = ((yf + (f64)h / 2.0) / (hf / 2.0)) - 1.0;
    Mat4 translate = Translate(vec4(xp, yp, 0.0, 1.0));
    Mat4 scale     = Scale4(vec4((f64)w / wf, (f64)h / hf, 0.0, 1.0));
    Mat4 transform = ls_mat4x4Mul(scale, translate);
    
    glUniformMatrix4fv(glGetUniformLocation(c->rectShader, "transform"), 1, GL_TRUE, (GLfloat *)transform.values);
    
    glBindVertexArray(c->rectVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glBindVertexArray(0);
    glUseProgram(0);
    
#else
    s32 minX = threadRect.minX > scissor.x ? threadRect.minX : scissor.x;
    s32 minY = threadRect.minY > scissor.y ? threadRect.minY : scissor.y;
    s32 maxX = threadRect.maxX < scissor.x+scissor.w ? threadRect.maxX : scissor.x+scissor.w;
    s32 maxY = threadRect.maxY < scissor.y+scissor.h ? threadRect.maxY : scissor.y+scissor.h;
    
    s32 startY = yPos;
    if(startY < minY) { h -= (minY-startY); startY = minY; }
    
    s32 startX = xPos;
    if(startX < minX) { w -= (minX-startX); startX = minX; }
    
    /*Old Thread Rect being confused about inclusive and exclusive regions stuff
    if(startX+w > maxX) { w = maxX-startX+1; }
    if(startY+h > maxY) { h = maxY-startY+1; }
    */
    
    if(startX+w > maxX) { w = maxX-startX; }
    if(startY+h > maxY) { h = maxY-startY; }
    
    s32 diffWidth = (w % 4);
    s32 simdWidth = w - diffWidth;
    
    s32 diffHeight = (h % 4);
    s32 simdHeight = h - diffHeight;
    
    //TODO: Make AlphaBlending happen with SSE!!!
    
    //NOTE: Do the first Sub-Rectangle divisible by 4.
    //__m128i color = _mm_set1_epi32((int)c);
    
    for(s32 y = startY; y < startY+simdHeight; y++)
    {
        AssertMsg(y <= maxY, "Should never happen. Height was precomputed\n");
        //if(y > maxY) { break; }
        
        for(s32 x = startX; x < startX+simdWidth; x+=4)
        {
            AssertMsg(x <= maxX, "Should never happen. Width was precomputed\n");
            
            if(x < 0 || x >= win->width)  continue;
            if(y < 0 || y >= win->height) continue;
            
            u32 idx = ((y*win->width) + x)*sizeof(s32);
            __m128i *At = (__m128i *)(win->drawBuffer + idx);
            
            __m128i val = _mm_loadu_si128(At);
            
            u32 a1 = _mm_cvtsi128_si32(_mm_shuffle_epi32(val, 0b00000000));
            u32 a2 = _mm_cvtsi128_si32(_mm_shuffle_epi32(val, 0b01010101));
            u32 a3 = _mm_cvtsi128_si32(_mm_shuffle_epi32(val, 0b10101010));
            u32 a4 = _mm_cvtsi128_si32(_mm_shuffle_epi32(val, 0b11111111));
            
            Color c1 = ls_uiAlphaBlend(col, {.value = a1});
            Color c2 = ls_uiAlphaBlend(col, {.value = a2});
            Color c3 = ls_uiAlphaBlend(col, {.value = a3});
            Color c4 = ls_uiAlphaBlend(col, {.value = a4});
            
            __m128i color = _mm_setr_epi32(c1.value, c2.value, c3.value, c4.value);
            
            _mm_storeu_si128(At, color);
        }
    }
    
    //NOTE: Complete the 2 remaining Sub-Rectangles at the right and top. (if there are).
    //      We decide to have the right rectangle be full height
    //      And the top one be less-than-full width, to avoid over-drawing the small subrect
    //        in the top right corner.
    u32 *At = (u32 *)win->drawBuffer;
    
    if(diffWidth) 
    {
        for(s32 y = startY; y < startY+h; y++)
        {
            if(y > maxY) { break; }
            
            for(s32 x = startX+simdWidth; x < startX+w; x++)
            {
                if(x > maxX) { 
                    ls_printf("diffSIMDWidth: %d, diffWidth: %d\n", x-maxX, diffWidth);
                    break; 
                }
                
                if(x < 0 || x >= win->width)  continue;
                if(y < 0 || y >= win->height) continue;
                
                Color base = {.value = At[y*win->width + x] };
                Color blendedColor = ls_uiAlphaBlend(col, base);
                At[y*win->width + x] = blendedColor.value;
            }
        }
    }
    
    if(diffHeight)
    {
        for(s32 y = startY+simdHeight; y < startY+h; y++)
        {
            AssertMsg(y <= maxY, "Should never happen. Height was precomputed\n");
            if(y > maxY) { break; }
            
            for(s32 x = startX; x < startX+simdWidth; x++)
            {
                if(x > maxX) { break; }
                
                if(x < 0 || x >= win->width)  continue;
                if(y < 0 || y >= win->height) continue;
                
                Color base = { .value = At[y*win->width + x] };
                Color blendedColor = ls_uiAlphaBlend(col, base);
                At[y*win->width + x] = blendedColor.value;
            }
        }
    }
#endif //LS_UI_OPENGL_BACKEND
}

void ls_uiDrawCircle(UIContext *c, s32 centerX, s32 centerY, s32 radius, s32 thickness,
                 UIRect threadRect, UIRect scissor, Color col)
{
    UIWindow *win = c->currWindow;
#ifdef LS_UI_OPENGL_BACKEND
    
    glUseProgram(c->circleShader);
    
    s32 leftCornerX = centerX - radius;
    s32 leftCornerY = centerY - radius;
    
    f64 xf = (f64)leftCornerX;
    f64 yf = (f64)leftCornerY;
    f64 wf = (f64)win->width;
    f64 hf = (f64)win->height;
    
    s32 w = radius*2;
    s32 h = radius*2;
    
    f64 xp = ((xf + (f64)w / 2.0) / (wf / 2.0)) - 1.0;
    f64 yp = ((yf + (f64)h / 2.0) / (hf / 2.0)) - 1.0;
    
    f64 aspectRatio = wf/hf;
    Mat4 translate = Translate(vec4(xp, yp, 0.0, 1.0));
    Mat4 scale = Scale4(vec4((f64)w / wf, (f64)h / hf, 0.0, 1.0));
    Mat4 transform = ls_mat4x4Mul(scale, translate);
    
    
    glUniformMatrix4fv(glGetUniformLocation(c->circleShader, "transform"), 1, GL_TRUE, (GLfloat *)transform.values);
    glUniform4ui(glGetUniformLocation(c->circleShader, "color"), col.r, col.g, col.b, col.a);
    
    f32 normZ = 1.0f ;//- ((f32)c->zLayer / (f32)(UI_Z_LAYERS-1));
    glUniform1f(glGetUniformLocation(c->circleShader, "zLayer"), normZ);
    
    f32 uvThickness = (f32)thickness / (f32)radius;
    glUniform1f(glGetUniformLocation(c->circleShader, "thickness"), uvThickness); // Full circle in [0..1]
    
    glBindVertexArray(c->circleVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, c->circleVertCount);
    
    glBindVertexArray(0);
    glUseProgram(0);
    
#else
    //TODO: Change with better rasterizer
    s32 minX = threadRect.minX > scissor.x ? threadRect.minX : scissor.x;
    s32 minY = threadRect.minY > scissor.y ? threadRect.minY : scissor.y;
    s32 maxX = threadRect.maxX < scissor.x+scissor.w ? threadRect.maxX : scissor.x+scissor.w;
    s32 maxY = threadRect.maxY < scissor.y+scissor.h ? threadRect.maxY : scissor.y+scissor.h;
    
    s32 startX = centerX - radius;
    s32 startY = centerY - radius;
    
    if(startX < minX) { startX = minX; }
    if(startY < minY) { startY = minY; }
    
    s32 endX   = centerX + radius + 1;
    s32 endY   = centerY + radius + 1;
    
    if(endX > maxX) { endX = maxX; }
    if(endY > maxY) { endY = maxY; }
    
    u32 *At = (u32 *)win->drawBuffer;
    for(s32 y = startY; y < endY; y++)
    {
        for(s32 x = startX; x < endX; x++)
        {
            s32 cX = x - centerX;
            s32 cY = y - centerY;
            
            b32 cond1 = (cY*cY + cX*cX) <= (radius*radius);
            b32 cond2 = (cY*cY + cX*cX) >= ((radius-thickness)*(radius-thickness));
            
            if(cond1 && cond2)
            {
                Color base         = { .value = At[y*win->width + x] };
                Color blendedColor = ls_uiAlphaBlend(col, base);
                At[y*win->width + x] = blendedColor.value;
            }
        }
    }
#endif
}

void ls_uiStretchBitmap(UIContext *c, UIBitmap *bmp, UIRect dst, UIRect threadRect, UIRect scissor)
{
    UIWindow *win = c->currWindow;

#ifdef LS_UI_OPENGL_BACKEND
    
    glUseProgram(c->texturedRectShader);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, bmp->texID);
    
    f64 xf = (f64)dst.x;
    f64 yf = (f64)dst.y;
    f64 wf = (f64)win->width;
    f64 hf = (f64)win->height;
    
    // Positions need to be adjusted by the width and height... for some reason?
    f64 xp = ((xf + (f64)dst.w / 2.0) / (wf / 2.0)) - 1.0;
    f64 yp = ((yf + (f64)dst.h / 2.0) / (hf / 2.0)) - 1.0;
    
    f64 scaleW = (f64)dst.w / wf;
    f64 scaleH = (f64)dst.h / hf;
    
    Mat4 translate = Translate(vec4(xp, yp, 0.0, 1.0));
    Mat4 scale = Scale4(vec4(scaleW, scaleH, 0.0, 1.0));
    Mat4 transform = ls_mat4x4Mul(scale, translate);
    glUniformMatrix4fv(glGetUniformLocation(c->texturedRectShader, "transform"), 1, GL_TRUE, (GLfloat *)transform.values);
    glUniform4ui(glGetUniformLocation(c->texturedRectShader, "color"), 255, 255, 255, 255);
    
    f32 normZ = 1.0f ;//- ((f32)c->zLayer / (f32)(UI_Z_LAYERS-1));
    glUniform1f(glGetUniformLocation(c->texturedRectShader, "zLayer"), normZ);
    
    glBindVertexArray(c->rectVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    
#else
    
    s32 minX = threadRect.minX;
    s32 minY = threadRect.minY;
    s32 maxX = threadRect.maxX;
    s32 maxY = threadRect.maxY;
    
    //NOTE: We multiply the scale factors by 0.99.. to avoid sampling a pixel from 1 off outside
    //      the source bitmap because of rounding inaccuracies with floating point values.
    //TODO: We could probably keep the original scale factors, and correctly round up/down when necessary
    //      to avoid this accuracy problem.
    f32 scaleW   = ((f32)dst.w / (f32)bmp->w) * 0.999999f;
    f32 scaleH   = ((f32)dst.h / (f32)bmp->h) * 0.999999f;
    f32 factorW  = 1.0f / scaleW;
    f32 factorH  = 1.0f / scaleH;
    
    s32 startY = dst.y;
    if(startY < minY) { dst.h -= (minY-startY); startY = minY; }
    
    s32 startX = dst.x;
    if(startX < minX) { dst.w -= (minX-startX); startX = minX; }
    
    if(startX+dst.w > maxX) { dst.w = maxX-startX+1; }
    if(startY+dst.h > maxY) { dst.h = maxY-startY+1; }
    
    u32 *At = (u32 *)win->drawBuffer;
    Color *SrcBmp = (Color *)bmp->data;
    
    f64 bmpY = 0;
    for(s32 y = startY; y < dst.y+dst.h; y++)
    {
        f64 bmpX = 0;
        for(s32 x = startX; x < dst.x+dst.w; x++)
        {
            s32 srcX = (s32)bmpX;
            s32 srcY = (s32)bmpY;
            Color finalColor = {.value = At[y*win->width + x]};
            Color SrcPixel = SrcBmp[srcY*bmp->w + srcX];
            finalColor = ls_uiAlphaBlend(SrcPixel, finalColor);
            At[y*win->width + x] = finalColor.value;
            
            bmpX += factorW;
        }
        bmpY += factorH;
    }

#endif
}


#if defined(LS_UI_OPENGL_BACKEND)
void __ls_uiOGLGlyph(UIContext *c, UIFont *f, s32 cp, s32 x, s32 y, f64 scale, Color col)
{
    UIWindow *win = c->currWindow;
    const s32 verticesPerGlyph = 6;
    
    b32 isSDF = c->fontGroup.isSDF;
    u32 shader = isSDF ? c->sdfTextShader : c->textShader;
    
    glUseProgram(shader);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, c->fontGroup.texID);
    GLint swizzleMask[] = {GL_RED, GL_RED, GL_RED, GL_RED}; // Map red to R, G, B, A
    glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);
    
    glUniform1i(glGetUniformLocation(shader, "tex"), 0); // Texture unit 0
    glUniform4ui(glGetUniformLocation(shader, "textColor"), col.r, col.g, col.b, col.a);
    if (isSDF)
    {
        f64 smoothingValue = 0.05;
        glUniform1f(glGetUniformLocation(c->sdfTextShader, "smoothing"), smoothingValue);
    }
    
    f32 normZ = 1.0f ;//- ((f32)c->zLayer / (f32)(UI_Z_LAYERS-1));
    glUniform1f(glGetUniformLocation(shader, "zLayer"), normZ);
    
    //NOTE: Correctly mapping the glyphs coordinates and dimensions is very annoying
    // We want to limit the amount of computation that needs to happen every frame, so we try to
    // have them be all precomputed when the glyph's position and size is added to the VAO.
    // During that phase, some amount of scaling, mapping and offsetting already happens @GlyphMapping
    //
    // Here, we need to bring the pixel-space xPos and yPos to the same mapping
    // (which *SHOULD* be [-1..1] OpenGL's NDC). Widths/Heights, as far as I currently understand, are *NOT*
    // supposed to be mapped -1..1 as well, because they are not positions in that space, but rather lengths.
    // To map those lengths, it seems the easiest way is to go to a simple fraction (map to 0..1 space)
    // and then just divide by 2 (* 0.5) since a lenght in 0..1 space would be double its equivalent in a -1..1 space
    // (since the space is literally double in range)
    // This lengths halving is already performed when uploading the glyphs info to the GPU, and should not be
    // performed again.
    f64 xf = (f64)x;
    f64 yf = (f64)y;
    f64 wf = (f64)win->width;
    f64 hf = (f64)win->height;
    f64 xp = ((xf - wf/2.0) / wf)*2;
    f64 yp = ((yf - hf/2.0) / hf)*2;
    Mat4 translate = Translate(vec4(xp, yp, 0.0, 1.0));
    Mat4 scaleM = Scale4(vec4(scale, scale, 0.0, 1.0));
    Mat4 transform = ls_mat4x4Mul(scaleM, translate);
    
    glUniformMatrix4fv(glGetUniformLocation(shader, "transform"), 1, GL_TRUE, (GLfloat *)transform.values);
    glUniform2f(glGetUniformLocation(shader, "viewportSize"), (f32)win->width, (f32)win->height);
    
    s32 vaoGlyphIndex = (f->idxInGroup * c->fontGroup.codepointCount) + cp;
    glBindVertexArray(c->fontGroup.atlasVAO);
    glDrawArrays(GL_TRIANGLES, vaoGlyphIndex * verticesPerGlyph, verticesPerGlyph);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

#elif defined(LS_UI_SOFTWARE_BACKEND)

void __ls_uiSoftwareGlyph(UIContext *c, UIGlyph *g, s32 xP, s32 yP, s32 stride, f32 scale, UIRect tRect, UIRect scissor, Color col)
{
    AssertNonNull(c);
    AssertNonNull(g);
    if(g->width == 0 || g->height == 0) { return; }
    
    UIWindow *win = c->currWindow;
    b32 isSDF = c->fontGroup.isSDF;
    
    auto bl_interp = [stride, scale](UIGlyph *glyph, s32 ix, s32 iy, s32 scaledHeight) -> f64 {
        //NOTE: map the output pixel position to the sdf glyph position
        f64 x = (f64)ix / (f64)scale;
        f64 y = (f64)((scaledHeight - 1) - iy) / (f64)scale;
        
        //NOTE: Calculate the Integer and Fractional parts of the coordinates
        s32 x0 = (s32)x;
        s32 x1 = (x0 + 1 < glyph->width) ? x0 + 1 : x0;
        s32 y0 = (s32)y;
        s32 y1 = (y0 + 1 < glyph->height) ? y0 + 1 : y0;
        
        f64 dx = x - x0;
        f64 dy = y - y0;
        
        //NOTE: Get a 4x4 pixel square
        f64 v00 = (f64)glyph->data[y0 * stride + x0] / 255.0;
        f64 v01 = (f64)glyph->data[y1 * stride + x0] / 255.0;
        f64 v10 = (f64)glyph->data[y0 * stride + x1] / 255.0;
        f64 v11 = (f64)glyph->data[y1 * stride + x1] / 255.0;
        
        //NOTE: Bilinear Interpolation (It's just a lerp between two lerps. Hence Bi- Linear!)
        f64 v0 = v00 * (1.0 - dy) + v01 * dy;
        f64 v1 = v10 * (1.0 - dy) + v11 * dy;
        f64 final = v0 * (1.0 - dx) + v1 * dx;
        
        //NOTETODO: Shitty sdf filtering.
        const s32 onEdgeValue = 180;
        const f64 fractOnEdge = (f64)onEdgeValue/255.0;
        f64 realAlpha = final < fractOnEdge ? final : 1.0;
        
        return realAlpha;
    };
    
    u32 *At = (u32 *)win->drawBuffer;
    s32 startY = yP - g->y1*scale;
    s32 startX = xP + g->x0*scale;
    
    //NOTE: Scaled dimensions for the glyph
    s32 scaledHeight = g->height*scale;
    s32 scaledWidth  = g->width*scale;
    
    s32 yOff = 0;
    s32 xOff = 0;

    s32 scissorMaxY = scissor.y+scissor.h;
    s32 maxY        = scaledHeight;
    if(startY + maxY > tRect.maxY)  { maxY -= (startY+maxY) - tRect.maxY; }
    if(startY + maxY > scissorMaxY) { maxY -= (startY+maxY) - scissorMaxY; }
    s32 scissorMaxX = scissor.x+scissor.w;
    s32 maxX = scaledWidth;
    if(startX + maxX > tRect.maxX)  { maxX -= (startX+maxX) - tRect.maxX; }
    if(startX + maxX > scissorMaxX) { maxX -= (startX+maxX) - scissorMaxX; }
    
    s32 minY = tRect.minY > scissor.y ? tRect.minY : scissor.y;
    if(startY < minY) { yOff = minY - startY; maxY -= yOff; startY = minY; }
    s32 minX = tRect.minX > scissor.x ? tRect.minX : scissor.x;
    if(startX < minX) { xOff = minX - startX; maxX -= xOff; startX = minX; }
    
    for(s32 y = 0; y < maxY; ++y)
    {
        s32 backbufferY = startY + y;
        f64 glyphY = ((f64)(y + yOff) / scale);
        
        for(s32 x = 0; x < maxX; ++x)
        {
            s32 backbufferX = startX + x;
            f64 glyphX = ((f64)(x + xOff) / scale);
            
            Color base  = { .value = At[backbufferY*win->width + backbufferX] };
            
            f64 realAlpha = 0.0;
            if(isSDF)
            {
                //NOTE: Fetch the sdf value by doing bilinear interpolation on the sdf bitmap
                //      This is already doing the int->fract coords for interpolation
                realAlpha = bl_interp(g, y+yOff, x+xOff, scaledHeight);
                
                //NOTE: Dynamically adjust the aliasing around the edge. This is important
                // since we want a sharp glyph at large pixel sizes and an aliased glyph 
                // at small pixels sizes to make them more readable and less jagged!
                f32 t = (f32)(scale*64.0) / ((f32)win->height * 0.26);
                if (t > 1.0) { t = 1.0f; }
                u8 alphaCheck = (u8)(255.0 * t);
                if(realAlpha < alphaCheck) { realAlpha = 0.0; }
            }
            else
            {
                s32 flippedY = ((scaledHeight / scale - 1) - (s32)glyphY);
                realAlpha = (f64)g->data[flippedY * stride + (s32)glyphX] / 255.0;
            }
            
            Color actual = {
                .b = (u8)(col.b*realAlpha),
                .g = (u8)(col.g*realAlpha),
                .r = (u8)(col.r*realAlpha),
                .a = (u8)(col.a*realAlpha)
            };
            
            Color final = ls_uiAlphaBlend(actual, base);
            At[backbufferY * win->width + backbufferX] = final.value;
        }
    }
}

#endif

s32 ls_uiGlyph(UIContext *c, UIFont *f, u32 cp, u32 cpNext, s32 x, s32 y, f64 scale, UIRect tRect, UIRect scissor, Color col)
{
#if defined(LS_UI_OPENGL_BACKEND)
    if(f->isAtlas)
    {
        UIAtlasMapEntry *map = ls_uiGetAtlasMapEntry(c, f, cp);
        
        __ls_uiOGLGlyph(c, f, cp, x, y, scale, col);
        return (map->xAdv*scale);
    }
    else
    {
        AssertMsg(FALSE, "Unhandled case: OpenGL uiGlyph without an atlas");
        return 0;
    }
#elif defined(LS_UI_SOFTWARE_BACKEND)
    UIGlyph g   = {};
    s32 stride  = 0;
    s32 advance = 0;
    if(f->isAtlas)
    {
        g = ls_uiGetGlyphFromAtlas(c, f, cp);
        stride = f->atlasWidth;
        advance = g.xAdv*scale;
    }
    else
    {
        g = f->glyph[cp];
        stride = g.width*scale;
        
        s32 kernAdvance = 0;
        if(cpNext != 0xFFFFFFFF) { kernAdvance = ls_uiGetKernAdvance(f, cp, cpNext); }
        
        advance = (g.xAdv + kernAdvance)*scale;
    }
    
    __ls_uiSoftwareGlyph(c, &g, x, y, stride, scale, tRect, scissor, col);
    return advance;
#else
    
#error Unhandled backend in ls_uiGlyph()
    
#endif
}

