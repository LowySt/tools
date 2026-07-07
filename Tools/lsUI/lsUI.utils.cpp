#include "lsUI.utils.h"

UIPos TEMPORARY_REMOVE_TO_ABS(s32 width, s32 height, UIPos p)
{
    if (p.kind == UIPosKind::Abs) { return p; }
    s32 x = (s32)(p.fx * width);
    s32 y = (s32)(p.fy * height);
    s32 w = (s32)(p.fw * width);
    s32 h = (s32)(p.fh * height);
    UIPos res = {UIPosKind::Abs, x, y, w, h};
    return res;
}

f32 ls_uiLerp(f32 base, f32 towards, f32 step)
{
    return base + step * (towards - base);
    //return (1.0f - step) * base + step * towards;
}

Color RGBA(u8 r, u8 g, u8 b, u8 a)
{ 
    f32 floatAlpha = (f32)a / 255.0f;
    Color res      = { .b = (u8)(b*floatAlpha), .g = (u8)(g*floatAlpha), .r = (u8)(r*floatAlpha), .a = a };
    return res;
}

Color RGB(u8 r, u8 g, u8 b)
{ 
    Color res = { .b = b, .g = g, .r = r, .a = 0xFF };
    return res;
}

Color RGBg(u8 v)
{ 
    Color res = { .b = v, .g = v, .r = v, .a = 0xFF };
    return res;
}

Color ls_uiAlphaPremultiply(Color source)
{
    f32 fAlpha = (f32)source.a / 255.0f;
    Color Result = {
        .b = (u8)(source.b*fAlpha),
        .g = (u8)(source.g*fAlpha),
        .r = (u8)(source.r*fAlpha),
        .a = source.a
    };
    return Result;
}

Color ls_uiAlphaUnmultiply(Color source)
{
    f32 fAlpha = (f32)source.a / 255.0f;
    Color Result = {
        .b = (u8)(source.b/fAlpha),
        .g = (u8)(source.g/fAlpha),
        .r = (u8)(source.r/fAlpha),
        .a = source.a
    };
    return Result;
}

Color SetAlpha(Color v, u8 a)
{ 
    f32 alphaConv = ((f32)a / (f32)v.a);
    Color res     = { .b = (u8)(v.b*alphaConv), .g = (u8)(v.g*alphaConv), .r = (u8)(v.r*alphaConv), .a = a };
    return res;
}

u8 GetAlpha(Color v)
{ return v.a; }


Color ls_uiDarkenRGB(Color c, f32 percentage)
{
    //NOTE: Ensure the percentage is within valid bounds
    if (percentage < 0.0)
    { percentage = 0.0; }
    else if (percentage > 1.0)
    { percentage = 1.0; }
    
    /*TODO: I can't currently apply gamma correction, since I don't have a good log(a) and pow(f32, f32)
 *       implementation, which are required to properly handle the inv gamma
    //NOTE: Apply Gamma Correction (perceptual weighting)
    f32 gamma    = 2.2; //NOTE: Typical gamma value for Display Devices
    f32 invGamma = 1.0 / gamma;
    */
    
    //NOTE Convert Premultiplied Color to Linear Color
    f64 invAlpha = (f64)c.a / 255.0;
    f64 rLinear  = ((f64)c.r / invAlpha);
    f64 gLinear  = ((f64)c.g / invAlpha);
    f64 bLinear  = ((f64)c.b / invAlpha);
    
    //NOTE: Darken the Linear Color
    rLinear *= (1.0 - percentage);
    gLinear *= (1.0 - percentage);
    bLinear *= (1.0 - percentage);
    
    c.r = (u8)(rLinear * invAlpha);
    c.g = (u8)(gLinear * invAlpha);
    c.b = (u8)(bLinear * invAlpha);
    
    /*TODO: Gamma Correction when log(a) and pow(f32, f32) are implemented and good.
    //NOTE: Convert back to premultiplied RGBA, and apply inverse gamma.
    *r = (int)(pow(rLinear, invGamma) * alpha);
    *g = (int)(pow(gLinear, invGamma) * alpha);
    *b = (int)(pow(bLinear, invGamma) * alpha);
*/
    
    return c;
}


//TODO: Fix for premultiplied alpha?
Color ls_uiLightenRGB(Color c, f32 percentage)
{
    u8 *c8 = (u8 *)&c;
    
    u8 lowest = 255;
    if(c8[0] < lowest) { lowest = c8[0]; }
    if(c8[1] < lowest) { lowest = c8[1]; }
    if(c8[2] < lowest) { lowest = c8[2]; }
    
    if(lowest == 255)  { return c; }
    
    u8 diffFactor  = 255 - lowest;
    u8  sum        = diffFactor * percentage;
    f32 realFactor = (f32)sum / (f32)diffFactor;
    
    c8[0] += (255 - c8[0]) * realFactor;
    c8[1] += (255 - c8[1]) * realFactor;
    c8[2] += (255 - c8[2]) * realFactor;
    
    return c;
}

//TODO: This feels wrong. In the backbuffer I'm storing the pixels *emissions* rather then the color.
//      Why am I not un-multiplying the alpha before writing into the backbuffer, and why does it look
//      correct?? @Alpha-Un-Multiply
Color ls_uiAlphaBlend(Color source, Color dest, u8 alpha)
{
    //NOTE: If the alpha was premultiplied
    //f32 factor = (f32)(255 - source.a) / 255.0f;
    f32 factor = (f32)(255 - alpha) / 255.0f;
    
    Color Result = {};
    Result.b = source.b + dest.b*factor;
    Result.g = source.g + dest.g*factor;
    Result.r = source.r + dest.r*factor;
    Result.a = alpha + dest.a*factor;
    
    return Result;
}

Color ls_uiAlphaBlend(Color source, Color dest)
{
    return ls_uiAlphaBlend(source, dest, source.a);
}

Color ls_uiRGBAtoARGB(Color c)
{
    u8 *c8 = (u8 *)&c;
    u8 A   = c8[0];
    
    c8[0]  = c8[1];
    c8[1]  = c8[2];
    c8[2]  = c8[3];
    c8[3]  = A;
    
    return c;
}

Color ls_uiARGBtoRGBA(Color c)
{
    u8 *c8 = (u8 *)&c;
    u8 A   = c8[3];
    
    c8[3]  = c8[2];
    c8[2]  = c8[1];
    c8[1]  = c8[0];
    c8[0]  = A;
    
    return c;
}

//TODO: Should *MAYBE* convert to floating point colors, rather than u8 colors.
//      Better for converting into different color spaces.
Color ls_uiHSVtoRGB(u32 h, f32 s, f32 v)
{
    f32 cFactor = s * v;
    
    f32 fmodded = ls_fmod(((f32)h / 60.0f), 2.0f);
    
    f32 xFactor = cFactor * (1.0f - ls_fabs(fmodded - 1.0f));
    f32 mFactor = v - cFactor;
    
    f32 rPrime = 0.0f;
    f32 gPrime = 0.0f;
    f32 bPrime = 0.0f;
    
    //NOTE: Answer changes depending on which Hectant we are in
    if(h < 60)
    {
        rPrime = cFactor;
        gPrime = xFactor;
    }
    else if(h < 120)
    {
        rPrime = xFactor;
        gPrime = cFactor;
    }
    else if(h < 180)
    {
        gPrime = cFactor;
        bPrime = xFactor;
    }
    else if(h < 240)
    {
        gPrime = xFactor;
        bPrime = cFactor;
    }
    else if(h < 300)
    {
        rPrime = xFactor;
        bPrime = cFactor;
    }
    else if(h < 360)
    {
        rPrime = cFactor;
        bPrime = xFactor;
    }
    
    u8 finalR = (rPrime+mFactor)*255;
    u8 finalG = (gPrime+mFactor)*255;
    u8 finalB = (bPrime+mFactor)*255;
    
    Color final = RGB(finalR, finalG, finalB);
    return final;
}

