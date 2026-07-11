#include "lsUI.primitives.h"

void ls_uiClearRect(UIContext *c, s32 startX, s32 startY, s32 w, s32 h, Color col)
{
    UIWindow *win = c->currWindow;
#ifdef LS_UI_OPENGL_BACKEND
    
    glUseProgram(c->rectProgram.idx);
    glUniform4ui(glGetUniformLocation(c->rectProgram.idx, "color"), col.r, col.g, col.b, col.a);
    
    f32 normZ = 1.0f; //1.0f - ((f32)c->zLayer / (f32)(UI_Z_LAYERS-1));
    glUniform1f(glGetUniformLocation(c->rectProgram.idx, "zLayer"), normZ);
    
    f64 xf = (f64)startY;
    f64 yf = (f64)startY;
    f64 wf = (f64)win->width;
    f64 hf = (f64)win->height;
    
    // Positions need to be adjusted by the width and height... for some reason?
    f64 xp = ((xf + (f64)w / 2.0) / (wf / 2.0)) - 1.0;
    f64 yp = ((yf + (f64)h / 2.0) / (hf / 2.0)) - 1.0;
    Mat4 translate = Translate(vec4(xp, yp, 0.0, 1.0));
    Mat4 scale     = Scale4(vec4((f64)w / wf, (f64)h / hf, 0.0, 1.0));
    Mat4 transform = ls_mat4x4Mul(scale, translate);
    
    glUniformMatrix4fv(glGetUniformLocation(c->rectProgram.idx, "transform"), 1, GL_TRUE, (GLfloat *)transform.values);
    
    glBindVertexArray(c->rectProgram.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glBindVertexArray(0);
    glUseProgram(0);
    
#else
    s32 diffWidth = (w % 4);
    s32 simdWidth = w - diffWidth;
    
    s32 diffHeight = (h % 4);
    s32 simdHeight = h - diffHeight;
    
    //NOTE: Do the first Sub-Rectangle divisible by 4.
    __m128i color = _mm_set1_epi32((int)col.value);
    
    for(s32 y = startY; y < startY+simdHeight; y++)
    {
        for(s32 x = startX; x < startX+simdWidth; x += 4)
        {
            u32 idx = ((y*win->width) + x)*sizeof(s32);
            __m128i *At = (__m128i *)(win->drawBuffer + idx);
            
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
            for(s32 x = startX+simdWidth; x < startX+w; x++)
            {
                At[y*win->width + x] = col.value;
            }
        }
    }
    
    if(diffHeight)
    {
        for(s32 y = startY+simdHeight; y < startY+h; y++)
        {
            for(s32 x = startX; x < startX+simdWidth; x++)
            {
                At[y*win->width + x] = col.value;
            }
        }
    }
#endif
}

void ls_uiFillRect(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h, UIRect threadRect, UIRect scissor, Color col)
{
    UIWindow *win = c->currWindow;

#ifdef LS_UI_OPENGL_BACKEND
    
    glUseProgram(c->rectProgram.idx);
    glUniform4ui(glGetUniformLocation(c->rectProgram.idx, "color"), col.r, col.g, col.b, col.a);
    
    f32 normZ = 1.0f ;//- ((f32)c->zLayer / (f32)(UI_Z_LAYERS-1));
    glUniform1f(glGetUniformLocation(c->rectProgram.idx, "zLayer"), normZ);
    
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
    
    glUniformMatrix4fv(glGetUniformLocation(c->rectProgram.idx, "transform"), 1, GL_TRUE, (GLfloat *)transform.values);
    
    glBindVertexArray(c->rectProgram.VAO);
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

void ls_uiDrawArrow(UIContext *c, s32 x, s32 yPos, s32 w, s32 h,
                    UIRect threadRect, UIRect scissor, Color bkgColor, UIArrowSide s)
{
    UIWindow *win = c->currWindow;

#ifdef LS_UI_OPENGL_BACKEND
    
    ls_uiBorderedRect(c, x-1, yPos, w, h, threadRect, scissor, bkgColor);
    
    //TODO: Customize color?
    Color col = c->borderColor;
    
    f64 arrowWidth  = 0.0;
    f64 arrowHeight = 0.0;
    s32 vaoOffset   = 0;
    
    switch(s)
    {
        case UIA_DOWN:
        {
            arrowWidth  = 0.58f*(f64)w;
            arrowHeight = 0.52f*(f64)h;
            vaoOffset   = 12;
        } break;
        
        case UIA_RIGHT:
        {
            arrowWidth  = 0.52f*w;
            arrowHeight = 0.58f*h;
            vaoOffset   = 9;
        } break;
        
        case UIA_LEFT:
        {
            arrowWidth  = 0.52f*w;
            arrowHeight = 0.58f*h;
            vaoOffset   = 15;
        } break;
    }
    
    s32 startX = x + (w - (s32)arrowWidth)/2 - 1;
    s32 startY = (yPos + (h-(s32)arrowHeight)/2) - 1;
    
    glUseProgram(c->rectProgram.idx);
    glUniform4ui(glGetUniformLocation(c->rectProgram.idx, "color"), col.r, col.g, col.b, col.a);
    
    f32 normZ = 1.0f ;//- ((f32)c->zLayer / (f32)(UI_Z_LAYERS-1));
    glUniform1f(glGetUniformLocation(c->rectProgram.idx, "zLayer"), normZ);
    
    f64 xf = (f64)startX;
    f64 yf = (f64)startY;
    f64 wf = (f64)win->width;
    f64 hf = (f64)win->height;
    
    // Positions need to be adjusted by the width and height... for some reason?
    f64 xp = ((xf + (f64)arrowWidth / 2.0) / (wf / 2.0)) - 1.0;
    f64 yp = ((yf + (f64)arrowHeight / 2.0) / (hf / 2.0)) - 1.0;
    
    Mat4 translate = Translate(vec4(xp, yp, 0.0, 1.0));
    Mat4 scale = Scale4(vec4((f64)arrowWidth / wf, (f64)arrowHeight / hf, 0.0, 1.0));
    Mat4 transform = ls_mat4x4Mul(scale, translate);
    
    glUniformMatrix4fv(glGetUniformLocation(c->rectProgram.idx, "transform"), 1, GL_TRUE, (GLfloat *)transform.values);
    
    glBindVertexArray(c->rectProgram.VAO);
    glDrawArrays(GL_TRIANGLES, vaoOffset, 3);
    
    glBindVertexArray(0);
    glUseProgram(0);
    
#else
    
    //TODO: Scissor???
    s32 minX = threadRect.minX;
    s32 minY = threadRect.minY;
    s32 maxX = threadRect.maxX;
    s32 maxY = threadRect.maxY;
    
    u32 *At = (u32 *)win->drawBuffer;
    
    s32 xPos = x-1;
    
    ls_uiBorderedRect(c, xPos, yPos, w, h, threadRect, scissor, bkgColor);
    
    //TODO: Fix threadRect pre-calculated bounds checks on every arrow direction!
    if(s == UIA_DOWN)
    {
        Color arrowColor = c->borderColor;
        
        s32 arrowWidth = 0.50f*w;
        s32 arrowHeight = 0.40f*h;
        
        f32 scaling = (f32)arrowHeight / (f32)arrowWidth;
        f32 progressiveX = 0.0f;
        
        s32 xBase = xPos  + (w - arrowWidth)/2;
        s32 xEnd  = xBase + arrowWidth;
        s32 xMid  = xBase + arrowWidth/2;
        
        s32 yStart = (yPos + h - (h - arrowHeight)/2) - 1;
        s32 yEnd = yStart - arrowHeight;
        
        //TODO: This is still wrong with multithreaded
        //TODO: Could this every invert base and end?
        if(xBase < minX)   { xBase  = minX; }
        if(xEnd >= maxX)   { xEnd   = maxX-1; }
        if(yStart >= maxY) {
            s32 yAdv = (yStart - maxY + 1);
            f32 fractAdv = yAdv*scaling;
            xBase += (s32)fractAdv; xEnd -= (s32)fractAdv;
            progressiveX = fractAdv - (s32)fractAdv;
            yStart = maxY-1;
        }
        if(yEnd < minY) { yEnd = minY; }
        
        for(s32 y = yStart; y >= yEnd; y--)
        {
            for(s32 x = xBase; x < xEnd; x++)
            {
                AssertMsg(x >= 0 && x < win->width,  "X out of range. Should have been guarded by thread UI Rects?\n");
                AssertMsg(y >= 0 && y < win->height, "Y out of range. Should have been guarded by thread UI Rects?\n");
                
                //TODO: Setting fractional alpha on the rows where progressiveX advances a fractional amount
                //      would allow better `sub-pixel like` blending. Just a tiny thing to make it look better
                //      at small resolutions.
                At[y*win->width + x] = c->borderColor.value;
            }
            
            progressiveX += scaling;
            s32 intProgress = (s32)progressiveX;
            xBase += intProgress;
            xEnd  -= intProgress;
            progressiveX -= intProgress;
        }
        
    }
    else if(s == UIA_RIGHT)
    {
        s32 arrowWidth  = 0.40f*w;
        s32 hBearing    = (w - arrowWidth)/2;
        s32 xBase       = xPos + hBearing;
        s32 xEnd        = xBase+1;
        
        s32 arrowHeight = 0.50f*h;
        s32 vBearing    = (h - arrowHeight)/2;
        s32 yStart1     = (yPos + h - vBearing) - 1;
        s32 yEnd1       = yStart1 - (arrowHeight/2);
        s32 yStart2     = yEnd1;
        s32 yEnd2       = yStart2 - arrowHeight;
        
        if(yStart1 >= maxY) { yStart1 = maxY; }
        if(yStart2 >= maxY) { yStart2 = maxY; }
        if(xBase  < minX)   { xEnd -= (minX - xBase); xBase = minX; }
        
        for(s32 y = yStart1; y >= yEnd1; y--)
        {
            if(y < minY) { break; }
            
            for(s32 x = xBase; x < xEnd; x++)
            {
                if(x >= maxX) { break; }
                
                if(x < 0 || x >= win->width)  continue;
                if(y < 0 || y >= win->height) continue;
                
                At[y*win->width + x] = RGBg(0x00).value;
            }
            
            xEnd  += 1;
        }
        
        xEnd -= 1;
        for(s32 y = yStart2; y >= yEnd2; y--)
        {
            if(y < minY) { break; }
            
            for(s32 x = xBase; x < xEnd; x++)
            {
                if(x >= maxX) { break; }
                
                if(x < 0 || x >= win->width)  continue;
                if(y < 0 || y >= win->height) continue;
                
                At[y*win->width + x] = RGBg(0x00).value;
            }
            
            xEnd  -= 1;
        }
    }
    else if(s == UIA_LEFT)
    {
        s32 arrowWidth  = 0.40f*w;
        s32 hBearing    = (w - arrowWidth)/2;
        s32 xBase       = xPos + w - hBearing - 1;
        s32 xEnd        = xBase+1;
        
        s32 arrowHeight = 0.50f*h;
        s32 vBearing    = (h - arrowHeight)/2;
        s32 yStart1     = (yPos + h - vBearing) - 1;
        s32 yEnd1       = yStart1 - (arrowHeight/2);
        s32 yStart2     = yEnd1;
        s32 yEnd2       = yStart2 - arrowHeight;
        
        if(yStart1 >= maxY) { yStart1 = maxY; }
        if(yStart2 >= maxY) { yStart2 = maxY; }
        if(xBase  < minX)   { xEnd -= (minX - xBase); xBase = minX; }
        
        for(s32 y = yStart1; y >= yEnd1; y--)
        {
            if(y < minY) { break; }
            
            for(s32 x = xBase; x < xEnd; x++)
            {
                if(x >= maxX) { break; }
                
                if(x < 0 || x >= win->width)  continue;
                if(y < 0 || y >= win->height) continue;
                
                At[y*win->width + x] = RGBg(0x00).value;
            }
            
            xBase -= 1;
        }
        
        xBase += 1;
        for(s32 y = yStart2; y >= yEnd2; y--)
        {
            if(y < minY) { break; }
            
            for(s32 x = xBase; x < xEnd; x++)
            {
                if(x >= maxX) { break; }
                
                if(x < 0 || x >= win->width)  continue;
                if(y < 0 || y >= win->height) continue;
                
                At[y*win->width + x] = RGBg(0x00).value;
            }
            
            xBase += 1;
        }
    }
    
#endif
}


void ls_uiDrawCircle(UIContext *c, s32 centerX, s32 centerY, s32 radius, s32 thickness,
                 UIRect threadRect, UIRect scissor, Color col)
{
    UIWindow *win = c->currWindow;
#ifdef LS_UI_OPENGL_BACKEND
    
    glUseProgram(c->circleProgram.idx);
    
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
    
    
    glUniformMatrix4fv(glGetUniformLocation(c->circleProgram.idx, "transform"), 1, GL_TRUE, (GLfloat *)transform.values);
    glUniform4ui(glGetUniformLocation(c->circleProgram.idx, "color"), col.r, col.g, col.b, col.a);
    
    f32 normZ = 1.0f ;//- ((f32)c->zLayer / (f32)(UI_Z_LAYERS-1));
    glUniform1f(glGetUniformLocation(c->circleProgram.idx, "zLayer"), normZ);
    
    f32 uvThickness = (f32)thickness / (f32)radius;
    glUniform1f(glGetUniformLocation(c->circleProgram.idx, "thickness"), uvThickness); // Full circle in [0..1]
    
    glBindVertexArray(c->circleProgram.VAO);
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
    
    glUseProgram(c->texturedRectProgram.idx);
    
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
    glUniformMatrix4fv(glGetUniformLocation(c->texturedRectProgram.idx, "transform"), 1, GL_TRUE, (GLfloat *)transform.values);
    glUniform4ui(glGetUniformLocation(c->texturedRectProgram.idx, "color"), 255, 255, 255, 255);
    
    f32 normZ = 1.0f ;//- ((f32)c->zLayer / (f32)(UI_Z_LAYERS-1));
    glUniform1f(glGetUniformLocation(c->texturedRectProgram.idx, "zLayer"), normZ);
    
    glBindVertexArray(c->rectProgram.VAO);
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
    u32 shader = isSDF ? c->sdfTextProgram.idx : c->textProgram.idx;
    
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
        glUniform1f(glGetUniformLocation(c->sdfTextProgram.idx, "smoothing"), smoothingValue);
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


void ls_uiColorValueRect(UIContext *c, s32 xPos, s32 yPos, s32 w, s32 h, UIRect threadRect, UIRect scissor)
{
    UIWindow *win = c->currWindow;

#ifdef LS_UI_OPENGL_BACKEND
    
    glUseProgram(c->gradientRectProgram.idx);
    glUniform4ui(glGetUniformLocation(c->gradientRectProgram.idx, "color"), 0, 0, 0, 0);
    
    f32 normZ = 1.0f ;//- ((f32)c->zLayer / (f32)(UI_Z_LAYERS-1));
    glUniform1f(glGetUniformLocation(c->gradientRectProgram.idx, "zLayer"), normZ);
    
    f64 xf = (f64)xPos;
    f64 yf = (f64)yPos;
    f64 wf = (f64)win->width;
    f64 hf = (f64)win->height;
    
    // Positions need to be adjusted by the width and height... for some reason?
    f64 xp = ((xf + (f64)w / 2.0) / (wf / 2.0)) - 1.0;
    f64 yp = ((yf + (f64)h / 2.0) / (hf / 2.0)) - 1.0;
    Mat4 translate = Translate(vec4(xp, yp, 0.0, 1.0));
    Mat4 scale = Scale4(vec4((f64)w / wf, (f64)h / hf, 0.0, 1.0));
    Mat4 transform = ls_mat4x4Mul(scale, translate);
    
    glUniformMatrix4fv(glGetUniformLocation(c->gradientRectProgram.idx, "transform"), 1, GL_TRUE, (GLfloat *)transform.values);
    
    glBindVertexArray(c->gradientRectProgram.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glBindVertexArray(0);
    glUseProgram(0);

#else
    
    s32 minX = threadRect.minX > scissor.x ? threadRect.minX : scissor.x;
    s32 minY = threadRect.minY > scissor.y ? threadRect.minY : scissor.y;
    s32 maxX = threadRect.maxX < scissor.x+scissor.w ? threadRect.maxX : scissor.x+scissor.w;
    s32 maxY = threadRect.maxY < scissor.y+scissor.h ? threadRect.maxY : scissor.y+scissor.h;
    
    f32 currGray = 0.0f;
    f32 step     = (f32)h / 255.0f;
    if(yPos < minY) { currGray = ((f32)(minY - yPos) / (f32)h)*255.0f; }
    f32 startGray = currGray;
    
    s32 startY = yPos;
    if(startY < minY) { h -= (minY-startY); startY = minY; }
    
    s32 startX = xPos;
    if(startX < minX) { w -= (minX-startX); startX = minX; }
    
    if(startX+w > maxX) { w = maxX-startX+1; }
    if(startY+h > maxY) { h = maxY-startY+1; }
    
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
        
        Color col = RGBg((u32)currGray);
        
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
        
        currGray += step;
    }
    
    //NOTE: Complete the 2 remaining Sub-Rectangles at the right and top. (if there are).
    //      We decide to have the right rectangle be full height
    //      And the top one be less-than-full width, to avoid over-drawing the small subrect
    //        in the top right corner.
    u32 *At = (u32 *)win->drawBuffer;
    
    if(diffWidth)
    {
        f32 diffGray = startGray;
        
        for(s32 y = startY; y < startY+h; y++)
        {
            if(y > maxY) { break; }
            
            Color col = RGBg((u32)diffGray);
            
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
            
            diffGray += step;
        }
    }
    
    if(diffHeight)
    {
        for(s32 y = startY+simdHeight; y < startY+h; y++)
        {
            if(y > maxY) { break; }
            
            Color col = RGBg((u32)currGray);
            
            for(s32 x = startX; x < startX+simdWidth; x++)
            {
                if(x > maxX) { break; }
                
                if(x < 0 || x >= win->width)  continue;
                if(y < 0 || y >= win->height) continue;
                
                Color base = { .value = At[y*win->width + x] };
                Color blendedColor = ls_uiAlphaBlend(col, base);
                At[y*win->width + x] = blendedColor.value;
            }
            
            currGray += step;
        }
    }
    
#endif
}

void ls_uiFillColorWheel(UIContext *c, s32 centerX, s32 centerY, s32 radius, f32 value,
                         UIRect threadRect, UIRect scissor)
{
    UIWindow *win = c->currWindow;

#ifdef LS_UI_OPENGL_BACKEND
    
    glUseProgram(c->colorWheelProgram.idx);
    
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

    glUniformMatrix4fv(glGetUniformLocation(c->colorWheelProgram.idx, "transform"), 1, GL_TRUE, (GLfloat *)transform.values);
    glUniform2f(glGetUniformLocation(c->colorWheelProgram.idx, "centerInScreenSpace"), (f64)centerX, (f64)centerY);
    glUniform1f(glGetUniformLocation(c->colorWheelProgram.idx, "radiusInScreenSpace"), (f64)radius);
    glUniform1f(glGetUniformLocation(c->colorWheelProgram.idx, "brightness"), value);

    f32 normZ = 1.0f ;//- ((f32)c->zLayer / (f32)(UI_Z_LAYERS-1));
    glUniform1f(glGetUniformLocation(c->colorWheelProgram.idx, "zLayer"), normZ);
    
    glBindVertexArray(c->rectProgram.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glBindVertexArray(0);
    glUseProgram(0);
    
#else
    
    s32 minX = threadRect.minX > scissor.x ? threadRect.minX : scissor.x;
    s32 minY = threadRect.minY > scissor.y ? threadRect.minY : scissor.y;
    s32 maxX = threadRect.maxX < scissor.x+scissor.w ? threadRect.maxX : scissor.x+scissor.w;
    s32 maxY = threadRect.maxY < scissor.y+scissor.h ? threadRect.maxY : scissor.y+scissor.h;
    
    s32 startX = centerX - radius;
    s32 startY = centerY - radius;
    
    if(startX < minX) { startX = minX; }
    if(startY < minY) { startY = minY; }
    
    s32 endX   = centerX + radius;
    s32 endY   = centerY + radius;
    
    if(endX > maxX) { endX = maxX+1; }
    if(endY > maxY) { endY = maxY+1; }
    
    u32 *At = (u32 *)win->drawBuffer;
    for(s32 y = startY; y < endY; y++)
    {
        for(s32 x = startX; x < endX; x++)
        {
            s32 cX = x - centerX;
            s32 cY = y - centerY;
            
            b32 cond = (cY*cY + cX*cX) <= (radius*radius);
            
            if(cond)
            {
                f32 saturation = ls_sqrt(cX*cX + cY*cY) / (f32)radius;
                saturation     = ls_clamp(saturation*1.00f, 1.0f, 0.0f);
                
                f32 angle = ls_atan2((f32)cY, (f32)cX) / PI;
                s32 hue   = (angle*180) + 179;
                
                Color converted = ls_uiHSVtoRGB(hue, saturation, value);
                
                Color base         = { .value = At[y*win->width + x] };
                Color blendedColor = ls_uiAlphaBlend(converted, base);
                At[y*win->width + x] = blendedColor.value;
            }
        }
    }
    
#endif
}

