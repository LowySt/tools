#include "lsUI.bitmaps.h"

UIBitmap ls_uiBitmapFromRGBAPixelData(UIContext *c, s32 w, s32 h, void *data)
{
    UIBitmap result = { data, w, h };
    
#ifdef LS_UI_OPENGL_BACKEND
    glGenTextures(1, &result.texID);
    glBindTexture(GL_TEXTURE_2D, result.texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    GLenum err = glGetError();
    if(err != GL_NO_ERROR)
    {
        ls_log("OpenGL Error When Loading Bitmap from RGBA Pixel Data: {s32}", err);
    }
#endif
    
    return result;
}


//TODO @UIPos
void ls_uiBitmap(UIContext *c, UIBitmap bmp, s32 xPos, s32 yPos, s32 w, s32 h, s32 zLayer = 0)
{
    RenderCommand command = { UI_RC_BITMAP, xPos, yPos, w, h };
    command.bitmap        = bmp;
    ls_uiPushRenderCommand(c, command, zLayer);
}

//TODO @UIPos
void ls_uiBitmap(UIContext *c, UIBitmap bmp, UIPos pos, s32 zLayer = 0)
{
    RenderCommand command = { UI_RC_BITMAP };
    command.bitmap        = bmp;
    command.pos           = pos;
    ls_uiPushRenderCommand(c, command, zLayer);
}
