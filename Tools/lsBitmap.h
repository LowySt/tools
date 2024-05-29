#ifndef LS_BITMAP_H
#define LS_BITMAP_H

#include "win32.h"
#include "lsCRT.h"
#include "lsMath.h"
#include "lsBuffer.h"

enum BitmapPixelFormat
{
    BPF_INVALID,
    
    BPF_ARGB,
    BPF_RGBA,
    BPF_ABGR,
    BPF_BGRA,
    
    BPF_COUNT,
};

struct Bitmap
{
    void *data;
    
    u32 width;
    u32 height;
    
    u32 headerSize;
    u32 compression;
    BitmapPixelFormat format;
    u32 pixelBufferSize;
    
    u64 fileSize; //TODO: What's the point??
    
    b32 isTopToBottom;
};

//NOTE: Interface
Bitmap ls_bitmapLoad(string Path);
Bitmap ls_bitmapLoad(string Path, u8 rMask, u8 gMask, u8 bMask, u8 aMask);
void ls_bitmapWrite(string Path, u8 *data, s32 width, s32 height);


#endif //LS_BITMAP_H


#ifdef LS_BITMAP_IMPLEMENTATION

Bitmap ls_bitmapLoad(string Path)
{
    Bitmap bitmap = {};
    
    char *bitmapFile;
    u64 bitmapFileSize = ls_readFile(Path.data, &bitmapFile, 0);
    
    b32 isWindowyfied = FALSE;
    u32 PixelOffset = *((u32 *)((char *)bitmapFile + 10));
    u32 HeaderSize = *((u32 *)((char *)bitmapFile + 14));
    
    s32 Width = *((s32 *)((char *)bitmapFile + 18));
    s32 Height = *((s32 *)((char *)bitmapFile + 22));
    if(Height < 0) { isWindowyfied = TRUE; Height = -Height; }
    
    u32 Compression = *((u32 *)((char *)bitmapFile + 30));
    
    u32 PixelBufferSize = *((u32 *)((char *)bitmapFile + 34));
    
    BitmapPixelFormat format = BPF_INVALID;
    u32 redMask   = *((u32 *)((char *)bitmapFile + 54));
    u32 greenMask = *((u32 *)((char *)bitmapFile + 58));
    u32 blueMask  = *((u32 *)((char *)bitmapFile + 62));
    u32 alphaMask = *((u32 *)((char *)bitmapFile + 66));
    
    if(redMask == 0xFF000000 && greenMask == 0x00FF0000 && blueMask == 0x0000FF00 && alphaMask == 0x000000FF)
    { format = BPF_RGBA; }
    else if(alphaMask == 0xFF000000 && redMask == 0x00FF0000 && greenMask == 0x0000FF00 && blueMask == 0x000000FF)
    { format = BPF_ARGB; }
    else if(alphaMask == 0xFF000000 && blueMask == 0x00FF0000 && greenMask == 0x0000FF00 && redMask == 0x000000FF)
    { format = BPF_ABGR; }
    else if(blueMask == 0xFF000000 && greenMask == 0x00FF0000 && redMask == 0x0000FF00 && alphaMask == 0x000000FF)
    { format = BPF_BGRA; }
    
    bitmap.data            = ((char *)bitmapFile + PixelOffset);
    bitmap.width           = Width;
    bitmap.height          = Height;
    bitmap.headerSize      = HeaderSize;
    bitmap.compression     = Compression;
    bitmap.format          = format;
    bitmap.pixelBufferSize = PixelBufferSize;
    bitmap.fileSize        = bitmapFileSize;
    bitmap.isTopToBottom   = isWindowyfied;
    
    return bitmap;
}

Bitmap ls_bitmapLoad(string Path, BitmapPixelFormat desired)
{
    Bitmap bmp = ls_bitmapLoad(Path);
    
    auto bitmapARGBtoRGBA = [](u32 c) -> u32
    {
        u8 *c8 = (u8 *)&c;
        
        u8 A   = c8[3];
        
        c8[3]  = c8[2];
        c8[2]  = c8[1];
        c8[1]  = c8[0];
        c8[0]  = A;
        
        return c;
    };
    
    auto bitmapRGBAtoARGB = [](u32 c) -> u32
    {
        u8 *c8 = (u8 *)&c;
        
        u8 A = c8[0];
        
        c8[0] = c8[1];
        c8[1] = c8[2];
        c8[2] = c8[3];
        c8[3] = A;
        
        return c;
    };
    
    u32 *End = (u32 *)(((u8 *)bmp.data) + bmp.pixelBufferSize);
    
    if(bmp.format == BPF_RGBA && desired == BPF_ARGB)
    {
        for(u32 *At = (u32 *)bmp.data; At < End; At++)
        {
            u32 currColor = *At;
            u32 converted = bitmapRGBAtoARGB(currColor);
            *At = converted;
        }
    }
    else
    {
        TODO;
    }
    
    return bmp;
}

void ls_bitmapWrite(string Path, u8 *data, s32 width, s32 height)
{
    const u32 bytesPerPixel = 4;
    
    const u32 sizeOfData    = width*height*bytesPerPixel;
    const u32 sizeOfDIB     = sizeof(BITMAPV5HEADER);
    const u32 sizeOfHeader  = 14;
    
    const u32 sizeInFile = sizeOfHeader + sizeOfDIB + sizeOfData;
    const u32 dataOffset = sizeOfHeader + sizeOfDIB;
    
    BITMAPV5HEADER bmpH = {};
    
    bmpH.bV5Size          = sizeof(BITMAPV5HEADER);
    bmpH.bV5Width         = width;
    bmpH.bV5Height        = height;
    bmpH.bV5Planes        = 1;
    bmpH.bV5BitCount      = 32;
    bmpH.bV5Compression   = BI_RGB;
    bmpH.bV5SizeImage     = 0; //May be set to 0 for BI_RGB
    bmpH.bV5XPelsPerMeter = 0;
    bmpH.bV5YPelsPerMeter = 0;
    bmpH.bV5ClrUsed       = 0;
    bmpH.bV5ClrImportant  = 0;
    bmpH.bV5RedMask       = 0;
    bmpH.bV5GreenMask     = 0;
    bmpH.bV5BlueMask      = 0;
    bmpH.bV5AlphaMask     = 0;
    bmpH.bV5CSType        = 0;
    bmpH.bV5Endpoints     = {};
    bmpH.bV5GammaRed      = 0;
    bmpH.bV5GammaGreen    = 0;
    bmpH.bV5GammaBlue     = 0;
    bmpH.bV5Intent        = 0;
    bmpH.bV5ProfileData   = 0;
    bmpH.bV5ProfileSize   = 0;
    bmpH.bV5Reserved      = 0;
    
    buffer buff = ls_bufferInit(MBytes(4));
    
    ls_bufferAddByte(&buff, 'B');
    ls_bufferAddByte(&buff, 'M');
    ls_bufferAddDWord(&buff, sizeInFile);
    ls_bufferAddDWord(&buff, 0);
    ls_bufferAddDWord(&buff, dataOffset);
    ls_bufferAddDataClean(&buff, &bmpH, sizeof(BITMAPV5HEADER));
    ls_bufferAddDataClean(&buff, data, sizeOfData);
    
    ls_writeFile(Path.data, buff.data, buff.cursor, FALSE);
}

#endif //IMPLEMENTATION
