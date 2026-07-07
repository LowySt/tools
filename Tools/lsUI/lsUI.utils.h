#pragma once

#define ColorComponentToFloat(color, comp) ((f32)color.comp / 255.0f)
union Color
{
    struct { u32 value; };
    struct { u8 b, g, r, a; };
};



//TODO Implement this for every widget?
#define UIAbsPos(a,b,c,d) {.kind=UIPosKind::Abs, .ix=a, .iy=b, .iw=c, .ih=d}
#define UIRelPos(a,b,c,d) {.kind=UIPosKind::Rel, .fx=a, .fy=b, .fw=c, .fh=d}
#define UISclPos(a,b,c,d) {.kind=UIPosKind::Scl, .sx=a, .sy=b, .sw=c, .sh=d}
enum UIPosKind : u8 { Abs = 0, Rel = 1, Scl = 2 };
struct UIPos
{
    UIPosKind kind;
    union {
        struct { s32 ix, iy, iw, ih; };
        struct { f32 fx, fy, fw, fh; };
        struct { f32 sx, sy; s32 sw, sh; };
    };
};

f32 ls_uiLerp(f32 base, f32 towards, f32 step);

//TODO: Do I want all these to be only exposed as implementation?
//TODO: Rename to ls_uiXXXX() for all of them...
Color RGBA(u8 r, u8 g, u8 b, u8 a);
Color RGB(u8 r, u8 g, u8 b);
Color RGBg(u8 v);
Color ls_uiAlphaPremultiply(Color source);
Color ls_uiAlphaUnmultiply(Color source);
Color SetAlpha(Color v, u8 a);
u8    GetAlpha(Color v);


Color ls_uiDarkenRGB(Color c, f32 percentage);
Color ls_uiLightenRGB(Color c, f32 percentage);
Color ls_uiAlphaBlend(Color source, Color dest, u8 alpha);
Color ls_uiAlphaBlend(Color source, Color dest);
Color ls_uiRGBAtoARGB(Color c);
Color ls_uiARGBtoRGBA(Color c);
Color ls_uiHSVtoRGB(u32 h, f32 s, f32 v);
