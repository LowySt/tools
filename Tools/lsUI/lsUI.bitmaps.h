#pragma once

struct UIBitmap
{
    void *data;
    s32   w;
    s32   h;
    
#ifdef LS_UI_OPENGL_BACKEND
    GLuint texID;
#endif
};


UIBitmap ls_uiBitmapFromRGBAPixelData(UIContext *c, s32 w, s32 h, void *data);
void     ls_uiBitmap(UIContext *c, UIBitmap bmp, s32 xPos, s32 yPos, s32 w, s32 h, s32 zLayer);
void     ls_uiBitmap(UIContext *c, UIBitmap bmp, UIPos pos, s32 zLayer);
