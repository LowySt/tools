#ifndef LS_PNG_H
#define LS_PNG_H

#include "lsCRT.h"

struct PNG_v3
{
    f32 x, y, z;
};

struct PNG_v3i
{
    s32 x, y, z;
};

struct PNG_v2
{
    f32 x, y;
};

struct PNG
{
    char *compressedData;
    
    u32 width;				//In pixels
    u32 height;				//In pixels
    
    /*n° of bits per sample (or per palette index, not per pixel) i.e. 1, 2, 4, 8, 16 (only some are possible per colorType)*/
    u8 bitDepth;
    
    /*
      Valid values (with associated bitDepth possible values) are
      0 - Greyscale			(bitDepth = 1, 2, 4, 8, 16)
      2 - Truecolor			(bitDepth = 8, 16)
      3 - IndexedColor		 (bitDepth = 1, 2, 4, 8)
      4 - Greyscale & Alpha	(bitDepth = 8, 16)
      6 - Truecolor & alpha	(bitDepth = 8, 16) */
    u8 colorType;
    
    /*Will always be 0 (Deflate / Inflate compression method is the International Standard*/
    u8 compressionMethod;
    
    /*Indicates the preprocessing method applied before compression.
 Will always be 0 (adaptive filtering with 5 basic filter types is the International Standard)*/
    u8 filterMethod;
    
    /*0 - No interlace, 1 - Adam7 interlace*/
    u8 interlaceMethod;
    
    /*Contains from 1 to 256 pallete entries*/
    PNG_v3 *palette;
    
    /*Information used in optional blocks*/
    
    /*bKGD*/
    u8 defaultBackgroundIndex;
    u16 defaultBackgroundGreyscale;
    PNG_v3i defaultBackgroundColor;
    
    /*cHRM*/
    PNG_v2 whitePoint;
    PNG_v2 redChrom;
    PNG_v2 greenChrom;
    PNG_v2 blueChrom;
    
    /*gAMA*/
    f32 gamma;
    
    /*pHYs*/
    u32 pixelsPerUnit_X;
    u32 pixelsPerUnit_Y;
    u8 unitSpecifier; // 0 is Unkown, 1 is one metre;
    
    u64 size;
};

extern "C"
{
    void ls_loadCompressedPNG(char *Path, PNG *png);
};


#endif //LS_PNG_H


#ifdef LS_PNG_IMPLEMENTATION

void ls_loadCompressedPNG(char *Path, PNG *png)
{
    char *pngFile;
    u64 pngFileSize = ls_readFile(Path, &pngFile, 0);
    
    png->compressedData = (char *)ls_alloc(sizeof(char)*pngFileSize);
    
    u8 *At = (u8 *)pngFile;
    
    //Checks the png file is "valid" with the first 4 bytes, 1 check byte and a "PNG" signature.
    Assert((*At == 0x89) && (*(At + 1) == 0x50) && (*(At + 2) == 0x4E) && (*(At + 3) == 0x47));
    At += 8;
    
    char chunkType[5];
    
    u32 chunkSize = btol32(At); At += 4;
    //ls_memcpy(At, chunkType, 4); At += 4;
    //chunkType[4] = 0;
    ls_strncpy(At, chunkType, 4); At += 4;
    
    while (ls_strcmp(chunkType, (char *)"IEND") != 0)
    {
        if (ls_strcmp(chunkType, (char *)"IHDR") == 0)
        {
            png->width				= btol32(At); At += 4;
            png->height				= btol32(At); At += 4;
            png->bitDepth			= *At; At++;
            png->colorType			= *At; At++;
            png->compressionMethod	= *At; At++;
            png->filterMethod		= *At; At++;
            png->interlaceMethod	= *At; At++;
        }
        else if (ls_strcmp(chunkType, (char *)"PLTE") == 0)
        {
            Assert((chunkSize % 3) == 0);
            u32 numOfEntries = chunkSize / 3;
            
            png->palette = (v3 *)ls_alloc(sizeof(v3)*numOfEntries);
            
            for (u32 i = 0; i < numOfEntries; i++)
            {
                png->palette[i].r = *At; At++;
                png->palette[i].g = *At; At++;
                png->palette[i].b = *At; At++;
            }
        }
        else if (ls_strcmp(chunkType, (char *)"IDAT") == 0)
        {
            ls_memcpy(At, png->compressedData + png->size, chunkSize); At += chunkSize;
            png->size += chunkSize;
        }
        else if (ls_strcmp(chunkType, "bKGD") == 0)
        {
            if (png->colorType == 3) { png->defaultBackgroundIndex = *At; At++; }
            
            else if ((png->colorType == 0) || (png->colorType == 4))
            { png->defaultBackgroundGreyscale = btol16(At); At += 2; }
            
            else
            {
                png->defaultBackgroundColor.x = btol16(At); At += 2;
                png->defaultBackgroundColor.y = btol16(At); At += 2;
                png->defaultBackgroundColor.z = btol16(At); At += 2;
            }
        }
        else if (ls_strcmp(chunkType, "cHRM") == 0)
        {
            png->whitePoint.x = (f32)btol32(At) / 100000.0f; At += 4;
            png->whitePoint.y = (f32)btol32(At) / 100000.0f; At += 4;
            png->redChrom.x = (f32)btol32(At) / 100000.0f; At += 4;
            png->redChrom.y = (f32)btol32(At) / 100000.0f; At += 4;
            png->greenChrom.x = (f32)btol32(At) / 100000.0f; At += 4;
            png->greenChrom.y = (f32)btol32(At) / 100000.0f; At += 4;
            png->blueChrom.x = (f32)btol32(At) / 100000.0f; At += 4;
            png->blueChrom.y = (f32)btol32(At) / 100000.0f; At += 4;
        }
        else if (ls_strcmp(chunkType, "gAMA") == 0)
        {
            png->gamma = (f32)btol32(At) / 100000.0f; At += 4;
        }
        else if (ls_strcmp(chunkType, "pHYs") == 0)
        {
            png->pixelsPerUnit_X = btol32(At); At += 4;
            png->pixelsPerUnit_Y = btol32(At); At += 4;
            png->unitSpecifier = *At; At++;
        }
        /*else if (ls_strcmp(chunkType, "tRNS") == 0)
        {
        
        }*/
        else
        {
            At += chunkSize;
        }
        
        //Jump CRC
        At += 4;
        
        chunkSize = btol32(At); At += 4;
        ls_strncpy(At, chunkType, 4); At += 4;
    }
    
    return;
}

/*------DEFLATE HELPERS------*/
#define MAXBITS 15              /* maximum bits in a code */
#define MAXLCODES 286           /* maximum number of literal/length codes */
#define MAXDCODES 30            /* maximum number of distance codes */
#define MAXCODES (MAXLCODES+MAXDCODES)  /* maximum codes lengths to read */
#define FIXLCODES 288           /* number of fixed literal/length codes */

struct deflate_state
{
    char *in;
    u32 bytesRead;
    u64 inSize;
    
    char *out;
    u64 outSize;
    
    u8 bitBuffer;
    u8 bitCount;
};

struct deflate_CodeTree
{
    u16 table[16];
    u16 symbols[288];
};

static u8 deflate_getBits(deflate_state *s, u8 n)
{
    u8 Result = 0;
    Assert(s->bitCount <= 8);
    
    if (s->bitCount)
    {
        if (s->bitCount >= n)
        {
            Result = s->bitBuffer;
            Result <<= (8 - n);
            Result >>= (8 - n);
            s->bitCount -= n;
            s->bitBuffer >>= n;
            
            return Result;
        }
        else
        {
            u8 left = n - s->bitCount;
            Result = s->bitBuffer;
            Result <<= left;
            s->bitBuffer = s->in[s->bytesRead++];
            
            u8 partial = s->bitBuffer;
            partial <<= (8 - left);
            partial >>= (8 - left);
            Result |= partial;
            
            s->bitCount = 8 - left;
            s->bitBuffer >>= left;
            
            return Result;
        }
    }
    else
    {
        s->bitBuffer = s->in[s->bytesRead++];
        
        Result = s->bitBuffer;
        Result <<= (8 - n);
        Result >>= (8 - n);
        
        s->bitCount = 8 - n;
        s->bitBuffer >>= n;
        
        return Result;
    }
    
    return Result;
}

static void decompressUncompressedBlock()
{
    return;
}

static void decompressHuffmanBlock(u32, u32)
{
    return;
}

static void decodeHuffmanCodes()
{
    return;
}

static void deflate_buildTree(deflate_CodeTree *t, u8 *lengths, u32 amount)
{
    u16 offsets[16];
    
    /* scan symbol lengths, and sum code length counts */
    for (u32 i = 0; i < amount; i++) { t->table[lengths[i]]++; }
    t->table[0] = 0;
    
    /* compute offset table for distribution sort */
    //The two methods are the same
    offsets[1] = 0;
    //for (u32 sum = 0, i = 0; i < 16; i++)
    for(u32 len = 1; len < 15; len++)
    {
        //offsets[i] = sum;
        //sum += t->table[i];
        offsets[len + 1] = offsets[len] + t->table[len];
    }
    
    /* create code->symbol translation table (symbols sorted by code) */
    for (u32 i = 0; i < amount; i++)
    {
        if (lengths[i]) { t->symbols[offsets[lengths[i]]++] = i; }
    }
}

static s32 deflate_decodeSym(deflate_state *s, deflate_CodeTree *t)
{
    s32 sum = 0, cur = 0, len = 0;
    
    do
    {
        cur = 2 * cur + deflate_getBits(s, 1);
        len++;
        
        sum += t->table[len];
        cur -= t->table[len];
    } while (cur >= 0);
    
    return t->symbols[sum + cur];
}

static void ls_Deflate(char *data, u64 inputSize, char *out)
{
    /*Setup the deflate state structure*/
    deflate_state state = {};
    state.in = data;
    state.inSize = inputSize;
    state.out = out;
    
    /*---Parse zlib header---*/
    u8 cmf = state.in[state.bytesRead++]; u8 flag = state.in[state.bytesRead++];
    if ((cmf & 0x0F) != 8 || (cmf >> 4) != 7 || (u32)(cmf*256 + flag) % 31 != 0)
    { Assert(false); } 	//Not a png or corrupted?
    
    u32 dict = 0;
    if ((flag & 0b00100000) != 0)
    { dict = btol32((u8 *)(&state.in[state.bytesRead])); state.bytesRead += 4; }
    
    // Process the stream of blocks
    do {
        // Read the block header
        //u8 byte = state.in[state.bytesRead++];
        //u8 type = (byte & 0x06) >> 1;
        u8 BFINAL = deflate_getBits(&state, 1);
        u8 BTYPE = deflate_getBits(&state, 2);
        
        // Decompress rest of block based on the type
        if (BTYPE == 0)		{ decompressUncompressedBlock(); }
        else if (BTYPE == 1) { decompressHuffmanBlock(FIXLCODES, MAXDCODES); }
        else if (BTYPE == 2)
        {
            u16 HLIT = (u16)deflate_getBits(&state, 5) + 257;
            u8 HDIST = deflate_getBits(&state, 5) + 1;
            u8 HCLEN = deflate_getBits(&state, 4) + 4;
            
            /* Enough to fit HLIT + HDIST amount of codes */
            u8 codeLengths[288+32] = {};
            
            /* Get Code Lengths used in the "Code Length Alphabet" in the order:
            * 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 */
            u8 order[] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };
            for (u32 i = 0; i < HCLEN; i++)
            { codeLengths[order[i]] = deflate_getBits(&state, 3); }
            
            /* Build the code tree.       ????? 19 because it's the max value for HCLEN ????? */
            deflate_CodeTree codeTree = {};
            deflate_buildTree(&codeTree, codeLengths, 19);
            
            /* Decode code lengths for dynamic trees
            * (HLIT amount for literal/length alphabet, HDIST amount for distance alphabet) */
            {
                u32 repeat = 0;
                u8 prev = 0;
                for (u32 num = 0; num < (u16)(HLIT + HDIST); )
                {
                    s32 sym = deflate_decodeSym(&state, &codeTree);
                    
                    switch (sym)
                    {
                        case 16:
                        {
                            /* copy previous code length 3-6 times (read 2 bits) */
                            prev = codeLengths[num - 1];
                            for (repeat = deflate_getBits(&state, 2) + 3; repeat; repeat--)
                            { codeLengths[num++] = prev; }
                        }
                        break;
                        
                        case 17:
                        {
                            /* repeat code length 0 for 3-10 times (read 3 bits) */
                            for (repeat = deflate_getBits(&state, 3) + 3; repeat; repeat--)
                            { codeLengths[num++] = 0; }
                        }
                        break;
                        
                        case 18:
                        {
                            /* repeat code length 0 for 11-138 times (read 7 bits) */
                            for (repeat = deflate_getBits(&state, 7) + 11; repeat; repeat--)
                            { codeLengths[num++] = 0; }
                        }
                        break;
                        default:
                        {
                            /* values 0-15 represent the actual code lengths */
                            codeLengths[num++] = sym;
                        }
                        break;
                    }
                }
            }
            
            /* Build Dynamic Trees*/
            deflate_CodeTree lenTree, distTree;
            deflate_buildTree(&lenTree, codeLengths, HLIT);
            deflate_buildTree(&distTree, codeLengths + HLIT, HDIST);
            
            int a = 0;
        }
        else if (BTYPE == 3) { Assert(FALSE); }
        else { Assert(FALSE); }
    } while (state.bytesRead < inputSize);
    
    return;
    
#undef MAXBITS
#undef MAXLCODES
#undef MAXDCODES
#undef MAXCODES
#undef FIXLCODES
}

#endif //IMPLEMENTATION
