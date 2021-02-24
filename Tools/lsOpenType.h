#ifndef OPEN_TYPE_H
#define OPEN_TYPE_H

//NOTE: Utility Byte Manipulation
#define GetByteSwap16(at) ByteSwap16(*(u16*)at); at+=2
#define GetByteSwap32(at) ByteSwap32(*(u32*)at); at+=4
#define GetByteSwap64(at) ByteSwap64(*(u64*)at); at+=8

// 'OTTO' Tag
#define OT_SFNTVERSION_CFFDATA 0x4F54544F
#define OT_SFNTVERSION_OUTLINE 0x00010000

//---------- TAGS -----------//

// Required Tables
#define OT_TAG_CMAP 'cmap'
#define OT_TAG_HEAD 'head'
#define OT_TAG_HHEA 'hhea'
#define OT_TAG_HMTX 'hmtx'
#define OT_TAG_MAXP 'maxp'
#define OT_TAG_NAME 'name'
#define OT_TAG_OS_2 'OS/2'
#define OT_TAG_POST 'post'

//TrueType Outlines
#define OT_TAG_CVT  'cvt '
#define OT_TAG_FPGM 'fpgm'
#define OT_TAG_GLYF 'glyf'
#define OT_TAG_LOCA 'loca'
#define OT_TAG_PREP 'prep'
#define OT_TAG_GASP 'gasp'

//CFF Outlines
#define OT_TAG_CFF  'CFF '
#define OT_TAG_CFF2 'CFF2'
#define OT_TAG_VORG 'VORG'

//SVG Outlines
#define OT_TAG_SVG  'SVG '

//Bitmap Glyphs
#define OT_TAG_EBDT 'EBDT'
#define OT_TAG_EBLC 'EBLC'
#define OT_TAG_EBSC 'EBSC'
#define OT_TAG_CBDT 'CBDT'
#define OT_TAG_CBLC 'CBLC'
#define OT_TAG_SBIX 'sbix'

//Advanced Typograhic Tables
#define OT_TAG_BASE 'BASE'
#define OT_TAG_GDEF 'GDEF'
#define OT_TAG_GPOS 'GPOS'
#define OT_TAG_GSUB 'GSUB'
#define OT_TAG_JSTF 'JSTF'
#define OT_TAG_MATH 'MATH'

//OpenType Font Variations
#define OT_TAG_AVAR 'avar'
#define OT_TAG_CVAR 'cvar'
#define OT_TAG_FVAR 'fvar'
#define OT_TAG_GVAR 'gvar'
#define OT_TAG_HVAR 'HVAR'
#define OT_TAG_MVAR 'MVAR'
#define OT_TAG_STAT 'STAT'
#define OT_TAG_VVAR 'VVAR'

//Color Fonts
#define OT_TAG_COLR 'COLR'
#define OT_TAG_CPAL 'CPAL'

//Other OpenType Tables
#define OT_TAG_DSIG 'DSIG'
#define OT_TAG_LTSH 'LTSH'
#define OT_TAG_MERG 'MERG'
#define OT_TAG_PCLT 'PCLT'
#define OT_TAG_VDMX 'VDMX'
#define OT_TAG_FFTM 'FFTM'
#define OT_TAG_HDMX 'hdmx'
#define OT_TAG_KERN 'kern'
#define OT_TAG_META 'meta'
#define OT_TAG_VHEA 'vhea'
#define OT_TAG_VMTX 'vmtx'
#define OT_TAG_MORX 'morx'
#define OT_TAG_FEAT 'feat'

//--------------------------//




struct OpenType_OffTable
{
    u32 sfntVersion;
    u16 numTables;
    u16 searchRange;
    u16 entrySelector;
    u16 rangeShift;
};

//Tables have to be zero padded to always begin on 4-byte boundaries for the Rasterizer's ease
//The checksum algo assumes 32-bit aligned tables
//      So, ALL tables MUST be 32-bit aligned and zero padded.
struct OpenType_TableRecord
{
    //struct Tag { u8 T[4]; };
    
    u32 tableTag;
    u32 checkSum;
    u32 offset;  //From the start of the file.
    u32 length;
};

struct Index
{
    u16  count;
    u8   name_offSize;
    void *offsets;
    u8   *data;
};

struct OpenType_DictData {
    u16 version;               // 0
    u16 Notice;                // 1
    u16 Copyright;             // 12 0
    u16 FullName;              // 2
    u16 FamilyName;            // 3
    u16 Weight;                // 4
    
    u8 isFixedPitch;           // 12 1
    s8 ItalicAngle[8];         // 12 2
    s8 UnderlinePosition[4];   // 12 3 //TODO: DEFAULT VALUESS!
    s8 UnderlineThickness[4];  // 12 4
    s8 PaintType[4];           // 12 5
    u32 CharstringType;        // 12 6
    
    s8 **FontMatrix;           // 12 7 array
    s8 *UniqueID;              // 13
    s8 **FontBBox;             // 5    array
    
    s8 *StrokeWidth;           // 12 8
    s8 **XUID;                 // 14   array
    
    s8 charset[4];             // 15
    s8 Encoding[4];            // 16
    u32 CharStrings;           // 17
    s8 Private[2][4];          // 18 two numbers
    s8 *SyntheticBase;         // 12 20
    
    u16 PostScript;            // 12 21
    u16 BaseFontName;          // 12 22
    s8 **BaseFontBlend;        // 12 23 delta
    
    u32 FDArrayOff;            // 12 36
    u32 FDSelectOff;           // 12 37
};

struct OpenType_CFF
{
    struct Index {
        union off { u8 o8; u16 o16; u32 o32; }; //Assume there's only 2 u8 offsets in OpenType
        u16 count; u8 offSize; off *offsets; u8 *data;
        u32 dataLen;
    };
    
    //Header
    u8 major;
    u8 minor;
    u8 hdrSize;
    u8 cff_offSize;
    
    //Name Index
    Index Name;
    Index TopDict; OpenType_DictData TopDictData;
    
    Index String;
    Index GlobalSubr;
    
    //NOTE:ASSUME That the next piece in memory is:
    Index Charstrings;
};

struct OpenType_HEAD
{
    struct Fixed { u16 integer; u16 fraction; };
    
    u16   major;
    u16   minor;
    
    Fixed fontRevision;
    u32   checksumAdjustment;
    u32   magicNumber;      //MUST be 0x5F0F3CF5
    u16   flags;            //Bunch of them
    
    u16   unitsPerEm;
    s64   created;
    s64   modified;
    
    s16   xMin;
    s16   yMin;
    s16   xMax;
    s16   yMax;
    
    u16   macStyle;
    u16   lowestRecPPEM;
    s16   fontDirectionHint;  //Deprecated: Set to 2
    
    s16   indexToLocFormat;   // 0 for u16, 1 for u32
    s16   glyphDataFormat;    // 0
};

struct OpenType_SimpleGlyph
{
    s16 numberOfContours; //MUST BE >= 0 TO BE A SIMPLE GLYPH. OTHERWISE IT IS A COMPOSITE GLYPH!
    
    s16 xMin;
    s16 yMin;
    s16 xMax;
    s16 yMax;
    
    u16 *endPtsOfContours;
    
    u16 instructionLength; //If 0 there are NO instruction and the next member is skipped.
    u8  *instructions;
    
    u8 *flags; //TODO: NumberOfFlags MIA
    
    s16 *xCoordinates;
    s16 *yCoordinates; //And they could even be u8... WHO THE FUCK KNOWS!?
};

struct OpenType_LOCA
{
    union
    {
        u16 *offs16;
        u32 *offs32;
    };
    
    u16 numOfOffs;
};

struct OpenType_MAXP
{
    //ONLY u16 numGlyphs for 0.5 (CFF data fonts)
    struct Fixed { u16 integer; u16 fraction; };
    
    Fixed version;
    u16 numGlyphs;
    
    //Version 1.0 defines many more fields
    u16 maxPoints;
    u16 maxContours;
    u16 maxCompositePoints;
    u16 maxCompositeContours;
    u16 maxZones;
    u16 maxTwilightPoints;
    u16 maxStorage;
    u16 maxFunctionDefs;
    u16 maxInstructionDefs;
    u16 maxStackElements;
    u16 maxSizeOfInstructions;
    u16 maxComponentElements;
    u16 maxComponentDepth;
};

enum OpenType_CMAP_FORMAT
{
    CMAP_FORMAT_UNICODE = 4,
};

struct OpenType_CMAP
{
    struct EncodingRecord { u16 platformID; u16 encodingID; u32 offsetFromCMAPBegin; };
    
    u16 version;
    u16 numTables;
    
    EncodingRecord *records; // records[numTables]
    
    u16 format;
    u16 length;
    u16 language;
    
    //Unicode format 4
    u16 segCountX2;
    u16 searchRange;
    u16 entrySelector;
    u16 rangeShift;
    u16 *endCode;    //endCode[segCount] == endCode[segCountX2 / 2]
    
    u16 reservedPad; // Set to Zero
    
    u16 *startCode;  //startCode[segCount] == startCode[segCountX2 / 2]
    s16 *idDelta;    //idDelta[segCount] == idDelta[segCountX2 / 2]
    u16 *idRangeOff; //idRangeOff[segCount] == idRangeOff[segCountX2 / 2]
    
    u16 *glyphIDArr;
};

struct OpenType_Font
{
    struct OpenType_Glyph { u32 glyphSizes; void *data; };
    
    Array<OpenType_Glyph> glyphs;
};

extern "C"
{
    void ls_openTypeLoadFont(string filePath);
};

#endif //End of Header


#ifdef LS_OPENTYPE_IMPLEMENTATION

static
u32 OpenType_Checksum(u32 *table, u32 length)
{
    u32 sum = 0;
    u32 *end = table + ((length+3) & ~3) / sizeof(u32);
    
    while (table < end) { sum += *table++; }
    return sum;
}

static
OpenType_OffTable OpenType_readOffTable(OpenType_OffTable *t)
{
    OpenType_OffTable Res = {};
    
    Res.sfntVersion   = ByteSwap32(t->sfntVersion);
    Res.numTables     = ByteSwap16(t->numTables);
    Res.searchRange   = ByteSwap16(t->searchRange);
    Res.entrySelector = ByteSwap16(t->entrySelector);
    Res.rangeShift    = ByteSwap16(t->rangeShift);
    
    return Res;
}

static
OpenType_TableRecord OpenType_readTableRecord(OpenType_TableRecord *c)
{
    OpenType_TableRecord Res = {};
    
    Res.tableTag = ByteSwap32(c->tableTag);
    Res.checkSum = ByteSwap32(c->checkSum);
    Res.offset   = ByteSwap32(c->offset);
    Res.length   = ByteSwap32(c->length);
    
    return Res;
}

static
OpenType_HEAD OpenType_readHEADTable(u8 *h)
{
    OpenType_HEAD Res = {};
    u8 *At = h;
    
    Res.major                 = GetByteSwap16(At);
    Res.minor                 = GetByteSwap16(At);
    Res.fontRevision.integer  = GetByteSwap16(At);
    Res.fontRevision.fraction = GetByteSwap16(At);
    Res.checksumAdjustment    = GetByteSwap32(At);
    Res.magicNumber           = GetByteSwap32(At);
    Assert(Res.magicNumber == 0x5F0F3CF5);
    
    Res.flags                 = GetByteSwap16(At);
    Res.unitsPerEm            = GetByteSwap16(At);
    Res.created               = GetByteSwap64(At);
    Res.modified              = GetByteSwap64(At);
    
    Res.xMin                  = GetByteSwap16(At);
    Res.yMin                  = GetByteSwap16(At);
    Res.xMax                  = GetByteSwap16(At);
    Res.yMax                  = GetByteSwap16(At);
    
    Res.macStyle              = GetByteSwap16(At);
    Res.lowestRecPPEM         = GetByteSwap16(At);
    Res.fontDirectionHint     = GetByteSwap16(At);   //Deprecated: Set to 2
    Assert(Res.fontDirectionHint == 2);
    
    Res.indexToLocFormat      = GetByteSwap16(At);   // 0 for u16, 1 for u32
    Res.glyphDataFormat       = GetByteSwap16(At);   // 0
    
    return Res;
};

static
OpenType_MAXP OpenType_readMAXPTable(u8 *m)
{
    OpenType_MAXP Res = {};
    u8 *At = m;
    
    //ONLY u16 numGlyphs for 0.5 (CFF data fonts)
    Res.version.integer  = GetByteSwap16(At);
    Res.version.fraction = GetByteSwap16(At);
    Res.numGlyphs        = GetByteSwap16(At);
    
    if((Res.version.integer == 0x0001) && (Res.version.fraction == 0x0000))
    {
        Res.maxPoints             = GetByteSwap16(At);
        Res.maxContours           = GetByteSwap16(At);
        Res.maxCompositePoints    = GetByteSwap16(At);
        Res.maxCompositeContours  = GetByteSwap16(At);
        Res.maxZones              = GetByteSwap16(At);
        Res.maxTwilightPoints     = GetByteSwap16(At);
        Res.maxStorage            = GetByteSwap16(At);
        Res.maxFunctionDefs       = GetByteSwap16(At);
        Res.maxInstructionDefs    = GetByteSwap16(At);
        Res.maxStackElements      = GetByteSwap16(At);
        Res.maxSizeOfInstructions = GetByteSwap16(At);
        Res.maxComponentElements  = GetByteSwap16(At);
        Res.maxComponentDepth     = GetByteSwap16(At);
    }
    
    return Res;
}

static
OpenType_CMAP OpenType_readCMAPTable(u8 *c)
{
    OpenType_CMAP Res = {};
    u8 *At = c;
    
    Res.version   = GetByteSwap16(At);
    Res.numTables = GetByteSwap16(At);
    
    //TODO: Can we make this a fixed size array? Maybe 256 big or something?
    //  I feel like it would be big only for collection files, rather than single font files.
    //  But i don't know for certain.
    Res.records   = (OpenType_CMAP::EncodingRecord *)ls_alloc(sizeof(OpenType_CMAP::EncodingRecord) * Res.numTables);
    
    s32 unicodeTableIdx = -1;
    for(u32 i = 0; i < Res.numTables; i++)
    {
        Res.records[i].platformID = GetByteSwap16(At);
        Res.records[i].encodingID = GetByteSwap16(At);
        Res.records[i].offsetFromCMAPBegin = GetByteSwap32(At);
        
        if(Res.records[i].platformID == 0)
        {
            //NOTE: Found Unicode Encoding
            unicodeTableIdx = i;
        }
    }
    
    if(unicodeTableIdx != -1)
    {
        //Fill Table
        At = c += Res.records[unicodeTableIdx].offsetFromCMAPBegin;
        
        Res.format = GetByteSwap16(At);
        
        switch(Res.format)
        {
            case CMAP_FORMAT_UNICODE:
            {
                Res.length        = GetByteSwap16(At);
                Res.language      = GetByteSwap16(At);
                Res.segCountX2    = GetByteSwap16(At);
                Res.searchRange   = GetByteSwap16(At);
                Res.entrySelector = GetByteSwap16(At);
                Res.rangeShift    = GetByteSwap16(At);
                
                u16 segCount   = Res.segCountX2 / 2;
                Res.endCode    = (u16 *)ls_alloc(sizeof(u16) * segCount);
                Res.startCode  = (u16 *)ls_alloc(sizeof(u16) * segCount);
                Res.idDelta    = (s16 *)ls_alloc(sizeof(s16) * segCount);
                Res.idRangeOff = (u16 *)ls_alloc(sizeof(u16) * segCount);
                
                for(u32 i = 0; i < segCount; i++)
                {
                    Res.endCode[i]    = GetByteSwap16(At);
                }
                
                Res.reservedPad = GetByteSwap16(At);
                
                for(u32 i = 0; i < segCount; i++)
                {
                    Res.startCode[i]  = GetByteSwap16(At);
                    Res.idDelta[i ]   = GetByteSwap16(At);
                    Res.idRangeOff[i] = GetByteSwap16(At);
                }
                
                //TODO: Incomplete
                Assert(FALSE);
                
            } break;
        }
    }
    
    return Res;
}

static
void readCFFTableIndex(OpenType_CFF::Index *I, u8 **data)
{
    
#define READ8(a) *a; a++
#define READ16(a) ByteSwap16(*((u16 *)a)); a += 2
#define READ32(a) ByteSwap32(*((u32 *)a)); a += 4
    
    const size_t offsByteSize = sizeof(OpenType_CFF::Index::off);
    
    u32 dataLen = 0;
    u32 offsNum = 0;
    u8 *h = *data;
    
    I->count = READ16(h);
    
    //TODO:NOTE: I believe this works for every Index??
    //NOTE: Isn't setting data to h a bug here? Why isn't it?
    if(I->count == 0) { *data = h; /*I THINK IT'S A BUG!!!*/ return; }
    
    I->offSize = READ8(h);
    Assert(I->offSize >= 1 && I->offSize <= 4);
    
    offsNum = I->count + 1;
    I->offsets = (OpenType_CFF::Index::off *)ls_alloc(offsByteSize*offsNum);
    
    for(u32 idx = 0; idx < offsNum; idx++)
    {
        switch(I->offSize)
        {
            case 1: I->offsets[idx].o8 = READ8(h); break;
            case 2: I->offsets[idx].o16 = READ16(h); break;
            case 4: I->offsets[idx].o32 = READ32(h); break;
        }
    }
    
    //NOTE: I->offsets[0] is ALWAYS == 1
    switch(I->offSize)
    {
        case 1: dataLen = I->offsets[I->count].o8 - I->offsets[0].o8;   break;
        case 2: dataLen = I->offsets[I->count].o16 - I->offsets[0].o16; break;
        case 4: dataLen = I->offsets[I->count].o32 - I->offsets[0].o32; break;
    }
    
    I->data = (u8 *)ls_alloc(sizeof(u8)*dataLen);
    I->dataLen = dataLen;
    ls_memcpy(h, I->data, dataLen); h += dataLen;
    
    
    //NOTE: 2 Byte Count, 1 Byte OffSize, offsets size, data size
    u32 theoreticalSize = 2 + 1 + (I->offSize * (I->count + 1)) + dataLen;
    
    Assert((h - *data) == theoreticalSize);
    
#undef READ32
#undef READ16
#undef READ8
    
    *data = h;
    return;
}

static
void getIntDictOperand(s8 *output, u8 **data)
{
    u8 *dictData = *data;
    u8 b0 = *dictData; dictData++;
    
    if (b0 >= 32 && b0 <= 246)
    {
        //Size 1
        s8 v = (s8)(b0 - 139);
        Assert((v >= -107) && (v <= 107));
        
        output[0] = v;
    }
    else if(b0 >= 247 && b0 <= 250)
    {
        //Size 2 positive
        u8 b1 = *dictData; dictData++;
        s16 v = (s16)((b0-247)*256+b1+108);
        Assert((v >= 108) && (v <= 1131));
        
        *(s16 *)output = v;
    }
    else if(b0 >= 251 && b0 <= 254)
    {
        //Size 2 negative
        u8 b1 = *dictData; dictData++;
        s16 v = s16(-(b0-251)*256-b1-108);
        Assert((v >= -1131) && (v <= -108));
        
        *(s16 *)output = v;
    }
    else if(b0 == 28)
    {
        //Size 3
        u8 b1 = *dictData; dictData++;
        u8 b2 = *dictData; dictData++;
        s16 v = s16((b1<<8) | b2);
        Assert((v >= -32768) && (v <= 32767));
        
        *(s16 *)output = v;
        
    }
    else if(b0 == 29)
    {
        //Size 5
        u8 b1 = *dictData; dictData++;
        u8 b2 = *dictData; dictData++;
        u8 b3 = *dictData; dictData++;
        u8 b4 = *dictData; dictData++;
        s32 v = s32((b1<<24) | (b2<<16) | (b3<<8) | b4);
        Assert((v >= -(2 << 30)) && ((v <= (2 << 30)-1)));
        
        *(s32 *)output = v;
    }
    
    *data = dictData;
}

static
void getFloatDictOperand(u8 *operand, u8 **dictData)
{
    u8 *data = *dictData;
    u8 operandIdx = 0;
    operand[operandIdx++] = *data; data++;
    
    u8 value = *data; data++;
    u8 currNibble = (value & 0xF0) >> 4;
    u8 nextNibble = (value & 0x0F);
    
    b32 byteBoundary = FALSE;
    u32 operandLen = 0;
    while(currNibble != 0xf)
    {
        operandLen += 1;
        
        currNibble = nextNibble;
        if(byteBoundary == FALSE) { value = *data; data++; nextNibble = (value & 0xF0) >> 4; }
        else                      { nextNibble = (value & 0x0F); }
        byteBoundary = !byteBoundary;
    }
    
    operandLen += (operandLen % 2);
    u32 halfOpLen = operandLen / 2;
    ls_memcpy(data - halfOpLen, operand, halfOpLen);
    
    *dictData = data;
    return;
}

static
OpenType_DictData readDictData(OpenType_CFF::Index *Dict)
{
    
    u8 *dictData = Dict->data;
    u8 *endData = dictData + Dict->dataLen;
    
    OpenType_DictData dD = {};
    
    //TODO: REMEDYBG FIX!!
    //TODO: REMEDYBG FIX!!
    //TODO: REMEDYBG FIX!!
    //TODO: REMEDYBG FIX!!
    //Can't set default member values in structs because then remedy can't set breakpoints there
    dD.CharstringType = 2;
    
    
    while(dictData <= endData)
    {
        u8 b0 = *dictData;
        
        s8 operandInt[64][4] = {};
        u8 operandFloat[64][8] = {};
        
        u8 operandCount = 0;
        while(b0 >= 28) //Still getting operands
        {
            if(b0 != 30) { getIntDictOperand(operandInt[operandCount++], &dictData);   }
            else         { getFloatDictOperand(operandFloat[operandCount++], &dictData); }
            
            b0 = *dictData;
        }
        
        u8 op[2] = {};
        op[0] = *dictData; dictData++;
        Assert((op[0] >= 0) && (op[0] <= 21));
        
        switch(op[0])
        {
            case 0: { dD.version = *((s16 *)(operandInt[0])); } continue;
            case 1: { dD.Notice = *((s16 *)(operandInt[0])); } continue;
            case 2: { dD.FullName = *((s16 *)(operandInt[0])); } continue;
            case 3: { dD.FamilyName = *((s16 *)(operandInt[0])); } continue;
            case 4: { dD.Weight = *((s16 *)(operandInt[0])); } continue;
            
            case 5:
            {
                //NOTE:Assuming array of integers!
                dD.FontBBox = (s8 **)ls_alloc(sizeof(s8 *) * operandCount);
                for(u32 i = 0; i < operandCount; i++)
                {
                    dD.FontBBox[i] = (s8 *)ls_alloc(sizeof(s8)*4);
                    ls_memcpy(operandInt[i], dD.FontBBox[i], sizeof(s8)*4);
                }
                
            } continue;
            
            case 14:
            {
                //NOTE:Assuming array of integers!
                dD.XUID = (s8 **)ls_alloc(sizeof(s8 *) * operandCount);
                for(u32 i = 0; i < operandCount; i++)
                {
                    dD.XUID[i] = (s8 *)ls_alloc(sizeof(s8)*4);
                    ls_memcpy(operandInt[i], dD.XUID[i], sizeof(s8)*4);
                }
                
            } continue;
            
            //NOTE: Assuming Integers
            case 15: { ls_memcpy(operandInt[0], dD.charset, sizeof(s8)*4); } continue;
            case 16: { ls_memcpy(operandInt[0], dD.Encoding, sizeof(s8)*4); } continue;
            case 17: { dD.CharStrings = *((u32 *)(operandInt[0])); } continue;
            case 18:
            {
                ls_memcpy(operandInt[0], dD.Private[0], sizeof(s8)*4);
                ls_memcpy(operandInt[1], dD.Private[1], sizeof(s8)*4);
            } continue;
        }
        Assert(op[0] == 12);
        op[1] = *dictData; dictData++;
        
        switch(op[1])
        {
            case 0: { dD.Copyright = *((u16 *)(operandInt[0])); } continue;
            case 1: { dD.isFixedPitch = operandInt[0][0]; } continue;
            
            //NOTE: Assuming Float
            case 2: { ls_memcpy(operandFloat[0], dD.ItalicAngle, sizeof(u8)*8); } continue;
            
            //NOTE: Assuming Int
            case 3: { ls_memcpy(operandInt[0], dD.UnderlinePosition, sizeof(u8)*4); } continue;
            case 4: { ls_memcpy(operandInt[0], dD.UnderlineThickness, sizeof(u8)*4); } continue;
            case 5: { ls_memcpy(operandInt[0], dD.PaintType, sizeof(u8)*4); } continue;
            case 6: { dD.CharstringType = *((u32 *)(operandInt[0])); } continue;
            
            //NOTE: Assuming Float
            case 7:
            {
                dD.FontMatrix = (s8 **)ls_alloc(sizeof(s8 *) * operandCount);
                for(u32 i = 0; i < operandCount; i++)
                {
                    dD.FontMatrix[i] = (s8 *)ls_alloc(sizeof(s8)*8);
                    ls_memcpy(operandFloat[i], dD.FontMatrix[i], sizeof(s8)*8);
                }
            } continue;
            
            //NOTE: Assuming Int
            case 8: { ls_memcpy(operandInt[0], dD.StrokeWidth, sizeof(u8)*4); } continue;
            case 20: { ls_memcpy(operandInt[0], dD.SyntheticBase, sizeof(u8)*4); } continue;
            case 21: { dD.PostScript = *((u16 *)(operandInt[0])); } continue;
            case 22: { dD.BaseFontName = *((u16 *)(operandInt[0])); } continue;
            case 23:
            {
                dD.BaseFontBlend = (s8 **)ls_alloc(sizeof(s8 *) * operandCount);
                for(u32 i = 0; i < operandCount; i++)
                {
                    dD.BaseFontBlend[i] = (s8 *)ls_alloc(sizeof(s8)*4);
                    ls_memcpy(operandInt[i], dD.BaseFontBlend[i], sizeof(s8)*4);
                }
            } continue;
            
            case 36: { dD.FDArrayOff = *((u32 *)(operandInt[0])); } continue;
            case 37: { dD.FDSelectOff = *((u32 *)(operandInt[0])); } continue;
        }
    }
    
    return dD;
}

static
OpenType_CFF OpenType_readCFFTable(u8 *file, u8 *h)
{
    //offset of the CFF table from the beginning of the file
    const u8 baseCFFOffset = 18728;
    u8 *cffBase = h;
    
    OpenType_CFF Res = {};
    
    // CFF Header
    Res.major   = *h; h++;
    Res.minor   = *h; h++;
    Res.hdrSize = *h; h++;
    Res.cff_offSize = *h; h++;
    
    OpenType_CFF::Index *I;
    
    // Name Index
    u32 nameIdxOff = h - file;
    
    I = &Res.Name;
    readCFFTableIndex(I, &h);
    Assert(I->count == 1);   //Name Index in OpenType Fonts should have only 1 Entry!
    
    // Top Dict Index
    u32 TopDictIdxOff = h - file; //18747
    
    I = &Res.TopDict;
    readCFFTableIndex(I, &h);
    
    //Parse Top Dictionary
    //u32 TopDictOff = Res.TopDict.data - file; //18754
    Res.TopDictData = readDictData(&Res.TopDict);
    
    // String Index
    u32 StringIdxOff = h - file;
    
    I = &Res.String;
    readCFFTableIndex(I, &h);
    
    // Global Subroutines Index
    u32 GSubsOff = h - file; //24779
    
    I = &Res.GlobalSubr;
    readCFFTableIndex(I, &h);
    
    //NOTE:Should also extract the subroutines from the TopDict
    
    if(Res.TopDictData.FDSelectOff != 0)
    {
        Assert(FALSE);
        //Need to implement CID font
    }
    
    // Charstrings Index NOTE:(Indices are always from beginning of CFF)
    h = cffBase + Res.TopDictData.CharStrings;
    
    I = &Res.Charstrings;
    readCFFTableIndex(I, &h);
    
    return Res;
};

void ls_openTypeLoadFont(string filePath)
{
    OpenType_Font Font = {};
    
    char *file = 0;
    
    ls_strNullTerminate(&filePath);
    u64 fileSize = ls_readFile(filePath.data, &file, 0);
    
    char *At = file;
    OpenType_OffTable t = OpenType_readOffTable((OpenType_OffTable *)At);
    At += sizeof(OpenType_OffTable);
    
    Array<OpenType_TableRecord> recs = {};
    OpenType_TableRecord *currRec = (OpenType_TableRecord *)At;
    
    for(u32 tableIdx = 0; tableIdx < t.numTables; tableIdx++)
    {
        recs.push(OpenType_readTableRecord(currRec));
        currRec += 1;
    }
    
    //For every Table:
    OpenType_HEAD head = {};
    OpenType_MAXP maxp = {};
    OpenType_CMAP cmap = {};
    
    for(u32 tableIdx = 0; tableIdx < t.numTables; tableIdx++)
    {
        OpenType_TableRecord curr = recs[tableIdx];
        u8 *tablePtr = (u8 *)(file + curr.offset);
        
        switch(curr.tableTag)
        {
            case OT_TAG_HEAD:
            { head = OpenType_readHEADTable(tablePtr); } break;
            
            case OT_TAG_MAXP:
            { maxp = OpenType_readMAXPTable(tablePtr); } break;
            
            case OT_TAG_CMAP:
            { cmap = OpenType_readCMAPTable(tablePtr); } break;
        }
    }
    
    //NOTE: Understanding CFF
    OpenType_CFF cff = {};
    for(u32 tableIdx = 0; tableIdx < t.numTables; tableIdx++)
    {
        OpenType_TableRecord curr = recs[tableIdx];
        u8 *tablePtr = (u8 *)(file + curr.offset);
        //18728
        if(curr.tableTag == OT_TAG_CFF)
        {
            cff = OpenType_readCFFTable((u8 *)file, tablePtr);
        }
    }
    
    //NOTE: There is NO LOCA :(
    OpenType_LOCA loca = {};
    for(u32 tableIdx = 0; tableIdx < t.numTables; tableIdx++)
    {
        OpenType_TableRecord curr = recs[tableIdx];
        u8 *tablePtr = (u8 *)(file + curr.offset);
        
        if(curr.tableTag == OT_TAG_LOCA)
        {
            u16 numGlyphs = maxp.numGlyphs + 1;
            loca.numOfOffs = numGlyphs;
            
            if(head.indexToLocFormat == 0)
            {
                loca.offs16 = (u16 *)ls_alloc(sizeof(u16)*numGlyphs);
                ls_memcpy(tablePtr, loca.offs16, sizeof(u16)*numGlyphs);
                
                //Question: Can I go in and byteswap every element after the memcpy, or does it HAVE to
                // Happen before?
            }
            
            if(head.indexToLocFormat == 1)
            {
                loca.offs32 = (u32 *)ls_alloc(sizeof(u32)*numGlyphs);
                ls_memcpy(tablePtr, loca.offs32, sizeof(u32)*numGlyphs);
            }
        }
    }
    
    
    for(u32 tableIdx = 0; tableIdx < t.numTables; tableIdx++)
    {
        OpenType_TableRecord curr = recs[tableIdx];
        u8 *tablePtr = (u8 *)(file + curr.offset);
        
        if(curr.tableTag == OT_TAG_GLYF)
        {
            int breakHere = 0;
        }
    }
    
    int a = 0;
    
    ls_free(file);
}

#endif //End of Implementation