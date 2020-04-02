#ifndef LS_BITMAP_H
#define LS_BITMAP_H

#include "lsCRT.h"

struct Bitmap
{
    void *data;
    
    u32 width;
    u32 height;
    
    u32 headerSize;
    u32 compression;
    u32 pixelBufferSize;
    
    u64 size;
};

extern "C"
{
    void ls_loadBitmap(string Path, Bitmap *bitmap);
};

#endif //LS_BITMAP_H


#ifdef LS_BITMAP_IMPLEMENTATION

void ls_loadBitmap(string Path, Bitmap *bitmap)
{
    char *bitmapFile;
    u64 bitmapFileSize = ls_readFile(Path, &bitmapFile, 0);
    
    u32 PixelOffset = *((u32 *)((char *)bitmapFile + 10));
    u32 HeaderSize = *((u32 *)((char *)bitmapFile + 14));
    
    s32 Width = *((s32 *)((char *)bitmapFile + 18));
    s32 Height = *((s32 *)((char *)bitmapFile + 22));
    Height = ls_abs(Height);
    
    u32 Compression = *((u32 *)((char *)bitmapFile + 30));
    
    u32 PixelBufferSize = *((u32 *)((char *)bitmapFile + 34));
    
    bitmap->data = ((char *)bitmapFile + PixelOffset);
    bitmap->width = Width;
    bitmap->height = Height;
    bitmap->headerSize = HeaderSize;
    bitmap->compression = Compression;
    bitmap->pixelBufferSize = PixelBufferSize;
    bitmap->size = bitmapFileSize;
    
    return;
}

#endif //IMPLEMENTATION
