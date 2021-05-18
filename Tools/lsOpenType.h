#ifndef OPEN_TYPE_H
#define OPEN_TYPE_H

#include "lsCRT.h"
#include "lsStack.h"
#include "lsMath.h"   //TODO: REMOVE THIS.
#include "lsBitmap.h" //TODO: REMOVE THIS.


//NOTE: Utility Byte Manipulation
#define GetByte(at) *at; at+=1
#define GetByteSwap16(at)  ByteSwap16(*(u16*)at); at+=2
#define GetByteSwapS16(at) ByteSwap16(*(s16*)at); at+=2
#define GetByteSwap32(at)  ByteSwap32(*(u32*)at); at+=4
#define GetByteSwapS32(at) ByteSwap32(*(s32*)at); at+=4
#define GetByteSwap64(at)  ByteSwap64(*(u64*)at); at+=8
#define GetByteSwapS64(at) ByteSwap64(*(s64*)at); at+=8

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

struct OpenType_DictData {
    u16 version;                  // 0
    u16 Notice;                   // 1
    u16 Copyright;                // 12 0
    u16 FullName;                 // 2
    u16 FamilyName;               // 3
    u16 Weight;                   // 4
    
    s32 isFixedPitch = FALSE;     // 12 1
    f64 ItalicAngle;              // 12 2 float
    s32 UnderlinePosition = -100; // 12 3
    s32 UnderlineThickness = 50;  // 12 4
    s32 PaintType;                // 12 5
    u32 CharstringType = 2;       // 12 6
    
    f64 *FontMatrix;              // 12 7 array
    u32 fontMatrixCount;
    
    s32 UniqueID;                 // 13
    s32 *FontBBox;                // 5    array
    u32 fontBBoxCount;
    
    s32 StrokeWidth;              // 12 8
    s32 *XUID;                    // 14   array
    u32 XUIDCount;
    
    s32 charset;                  // 15
    s32 encoding;                 // 16
    s32 CharStrings;              // 17
    s32 Private[2];               // 18 two numbers
    s32 SyntheticBase;            // 12 20
    
    u16 PostScript;               // 12 21
    u16 BaseFontName;             // 12 22
    s32 *BaseFontBlend;           // 12 23 delta
    u32 BaseFontBlendCount;
    
    //TODO: Missing CIDFont Operator Extension!!
    u32 FDArrayOff;               // 12 36
    u32 FDSelectOff;              // 12 37
    
    
    //NOTE: PRIVATE DICT
    s32 *BlueValues;              // 6     delta
    u32 BlueValuesCount;
    
    s32 *OtherBlues;              // 7     delta
    u32 OtherBluesCount;
    
    s32 *FamilyBlues;             // 8     delta
    u32 FamilyBluesCount;
    
    s32 *FamilyOtherBlues;        // 9     delta
    u32 FamilyOtherCount;
    
    f64 BlueScale = 0.039625L;    // 12 9  float
    s32 BlueShift = 7;            // 12 10
    s32 BlueFuzz = 1;             // 12 11
    
    s32 StdHW;                    // 10
    s32 StdVW;                    // 11
    
    s32 *StemSnapH;               // 12 12 delta
    u32 StemSnapHCount;
    s32 *StemSnapV;               // 12 13 delta
    u32 StemSnapVCount;
    
    b32 ForceBold = FALSE;        // 12 14 bool
    s32 LanguageGroup;            // 12 17
    f64 ExpansionFactor = 0.06L;  // 12 18
    s32 InitialRandomSeed;        // 12 19
    
    s32 Subrs;                    // 19
    
    s32 defaultWidthX;            // 20
    s32 nominalWidthX;            // 21
}; 

struct OpenType_CFF
{
    struct Index {
        u16 count; u32 *offsets; u8 *data;
        u32 dataLen;
    };
    
    struct Charset {
        struct Range1 { u16 first; u8  nLeft; };
        struct Range2 { u16 first; u16 nLeft; };
        
        u8 format;
        u16 *glyphs;  //FORMAT 0 SID Glyph Name Array 
        Range1 *rng1; //FORMAT 1 Lenght is obtain by preprocessing every glyph.
        Range2 *rng2; //FORMAT 2 Lenght is obtain by preprocessing every glyph.
    };
    
    struct Encoding {
        struct Range1 { u8 first; u8 nLeft; };
        struct Supplement { u8 code; u16 glyph; };
        u8 format;
        
        //FORMAT 0
        u8 nCodes;
        u8 *codes;
        
        //FORMAT 1
        u8 nRanges;
        Range1 *ranges;
        
        //SUPPLEMENT (if high-order bit in format is set)
        u8 nSups;
        Supplement *sups;
    };
    
    //Header
    u8 major;
    u8 minor;
    u8 hdrSize;
    u8 cff_offSize;
    
    Index Name; //NOTE:NOT USED IN OPENTYPE
    
    Index TopDict; OpenType_DictData TopDictData;
    
    Index String; //NOTE:NOT USED IN OPENTYPE
    Index GlobalSubr;
    
    Charset  set;
    Encoding enc;
    
    Index Charstrings;
    
    OpenType_DictData PrivateDict;
    Index LocalSubr;
};


struct OpenType_NAME
{
    struct NameRecord 
    {
        u16 platformID;
        u16 encodingID;
        u16 languageID;
        u16 nameID;
        u16 length;
        u16 stringOff;
    };
    
    struct LangTagRecord
    {
        u16 length;
        u16 langTagOff;
    };
    
    //Version 0
    u16 version;
    u16 count;
    u16 storageOff;
    NameRecord *nameRecord;       //nameRecord[count]
    
    //Version 1
    u16 langTagCount;
    LangTagRecord *langTagRecord; //langTagRecord[langTagCount]
    
    void *data;
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

struct OpenType_HHEA
{
    u16 majorVersion;
    u16 minorVersion;
    
    s16 ascender;
    s16 descender;
    s16 lineGap;
    u16 advanceWidthMax;
    s16 minLeftSideBearing;
    s16 minRightSideBearing;
    s16 xMaxExtent;
    
    s16 caretSlopeRise;
    s16 caretSlopeRun;
    s16 caretOffset;
    
    s16 metricDataFormat;
    u16 numberOfHMetrics;
};

struct OpenType_HMTX
{
    struct LongHorMetric { u16 advanceWidth; s16 lsb; };
    
    LongHorMetric *hMetrics; // hMetrics[numberOfHMetrics] -> HHEA table
    s16 *leftSideBearings;   // leftSideBearings[numGlyphs - numberOfHMetrics] -> MAXP & HHEA table
    u32 bearingsCount;
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
    CMAP_FORMAT_UNICODE_1       = 0, //NOTE: DEPRECATED
    CMAP_FORMAT_UNICODE_2_FULL  = 4,
    CMAP_FORMAT_UNICODE_FULL_13 = 6,
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
    
    u16 *startCode;  //startCode[segCount] == startCode[segCountX2 / 2]
    s16 *idDelta;    //idDelta[segCount] == idDelta[segCountX2 / 2]
    u16 *idRangeOff; //idRangeOff[segCount] == idRangeOff[segCountX2 / 2]
    
    u16 *glyphIDArr;
};

struct OpenType_KERN_Subtable_0
{
    struct Pairs { u16 left; u16 right; s16 value; };
    
    u16 version;
    u16 length;
    u16 coverage;  //Bitwise interpretation
    
    u16 numPairs;
    u16 searchRange;
    u16 entrySelector;
    u16 rangeShift;
    
    Pairs *pairs;
};

struct OpenType_KERN
{
    u16 version;
    u16 numTables;
    
    OpenType_KERN_Subtable_0 *format0;
    //TODONOTE: Format 2 not implemented, since it's not supported in Windows
    //OpenType_KERN_Subtable_2 *format2;
};

enum GPOS_LookupFlag
{
    RIGHT_TO_LEFT             = 0x1,  //Only used in GPOS type 3 lookups
    IGNORE_BASE_GLYPHS        = 0x2,
    IGNORE_LIGATURES          = 0x4,
    IGNORE_MARKS              = 0x8,
    USE_MARK_FILTERING_SET    = 0x10,
    MARK_ATTACHMENT_TYPE_MASK = 0xFF00
};

enum GPOS_ValueFormat : u16
{
    X_PLACEMENT = 0x0001,
    Y_PLACEMENT = 0x0002,
    X_ADVANCE = 0x0004,
    Y_ADVANCE = 0x0008,
    X_PLACEMENT_DEVICE = 0x0010,
    Y_PLACEMENT_DEVICE = 0x0020,
    X_ADVANCE_DEVICE = 0x0040,
    Y_ADVANCE_DEVICE = 0x0080
};

struct GPOS_ValueRecord
{
    s16 xPlacement;
    s16 yPlacement;
    s16 xAdvance;
    s16 yAdvance;
    s16 xPlaDeviceOffset;
    s16 yPlaDeviceOffset;
    s16 xAdvDeviceOffset;
    s16 yAdvDeviceOffset;
};

struct GPOS_AnchorTable
{
    u16 anchorFormat;
    s16 xCoordinate;
    s16 yCoordinate;
    
    //NOTE: Format 2 only
    u16 anchorPoint;
    
    //NOTE: Format 3 only
    s16 xDeviceOffset;
    s16 yDeviceOffset;
};

struct MarkRecord
{ 
    u16 markClass; 
    s16 markAnchorOffset;
};

struct GPOS_LookupSub1
{
    //NOTE: Single Adjustment
    u16              posFormat;
    s16              coverageOffset;
    GPOS_ValueFormat valueFormat;
    
    //NOTE: If posFormat == 1, then there will be just 1 record, and count is implicit.
    u16 valueCount;
    GPOS_ValueRecord *records;
};

struct GPOS_LookupSub2
{
    struct PairValueRecord 
    { u16 secondGlyph; GPOS_ValueRecord record1, record2; };
    
    struct ClassRecord
    { GPOS_ValueRecord record1, record2; };
    
    //NOTE: Pair Adjustment
    u16 posFormat;
    s16 coverageOffset;
    u16 valueFormat1;
    u16 valueFormat2;
    
    //NOTE: ONLY FORMAT 1
    
    /* NOTE: Instead of keeping the offsets, I'll keep the actual tables
        s16 *pairSetOffsets; //pairSetOffets[pairSetCount]
    */
    u16 pairSetCount;
    u16 pairValueCount;
    PairValueRecord *tables; //NOTE: Flattened Array
    
    //NOTE: ONLY FORMAT 2
    s16 classDef1Offset;
    s16 classDef2Offset;
    u16 class1Count;
    u16 class2Count;
    ClassRecord *records;    //NOTE: Flattened Array
};

struct GPOS_LookupSub3
{
    struct EntryExitRecord
    { s16 entryAnchorOffset, exitAnchorOffset; };
    
    //NOTE: Cursive Attachment
    u16 posFormat;
    s16 coverageFormat;
    u16 entryExitCount;
    EntryExitRecord *records;
};

//NOTETODO: This is probably the wrong way to handle the mark/base anchor stuff.
// it probably doesn't use indices, but offsets to grab the right anchor.
// which means saving them separately will require either a hack to grab the right anchor
// or I'll have to save the pointer into the anchor array.... Everything's bad!
struct GPOS_LookupSub4
{
    struct BaseRecord
    { s16 *baseAnchorOffset; /*baseAnchorOffset[markClassCount]*/ };
    
    //NOTE: Mark to Base
    u16 posFormat;
    s16 markCoverageOffset;
    s16 baseCoverageOffset;
    u16 markClassCount;
    
    /*
    NOTE: Ignore the offsets, just get the table
        s16 markArrayOffset;
        s16 baseArrayOffset;*/
    
    u16         baseCount;
    BaseRecord  *baseRecords;
    GPOS_AnchorTable *anchors;
    
    u16         markCount;
    MarkRecord  *markRecords;
};

struct GPOS_LookupSub5
{
    struct LigatureAttach
    { 
        struct ComponentRecord
        { s16 *ligatureAnchorOffsets; /*ligatureAnchorOffsets[markClassCount]*/ };
        u16 componentCount; 
        ComponentRecord *records; 
    };
    
    //NOTE: Mark to Ligature
    u16 posFormat;
    s16 markCoverageOffset;
    s16 ligatureCoverageOffset;
    u16 markClassCount;
    
    /*
    NOTE: Ignore the offsets, just get the table
    s16 markArrayOffset;
    s16 ligatureArrayOffset; */
    
    u16 ligatureCount;
    s16 *ligatureAttachOffsets;
    LigatureAttach *attachTables;
    
    u16         markCount;
    MarkRecord  *markRecords;
};

struct GPOS_LookupSub6
{
    struct Mark2Record
    { s16 *mark2AnchorOffsets; /*mark2AnchorOffsets[markClassCount]*/ };
    //NOTE: Mark to Mark
    u16 posFormat;
    s16 mark1CoverageOffset;
    s16 mark2CoverageOffset;
    u16 markClassCount;
    
    /*
NOTE: Ignore the offsets, just get the table
s16 mark1ArrayOffset;
s16 mark2ArrayOffset; */
    
    u16         mark1Count;
    MarkRecord  *mark1Records;
    
    u16         mark2Count;
    Mark2Record  *mark2Records;
};

struct GPOS_LookupSub7
{
    //NOTE: Contextual Positioning
    //TODO: To be implemented
};

struct GPOS_LookupSub8
{
    //NOTE: Chained Context Positioning
    //TODO: To be implemented
};

struct GPOS_LookupSub9
{
    //NOTE: Extension Positioning
    
    u16 posFormat;
    u16 extensionLookupType;
    s32 extensionOffset;
};

struct GPOS_LangSysTable
{
    s16 lookupOrderOffset;    // = NULL (reserved)
    u16 requiredFeatureIndex;
    u16 featureIndexCount;
    u16 *featureIndices;       //featureIndices[featureIndexCount]
};

struct GPOS_ScriptTable
{
    struct LangSysRecord { u32 tag; GPOS_LangSysTable langSys; /*s16 offset replaced by table*/};
    
    s16 defaultLangSysOffset;
    u16 langSysCount;
    
    LangSysRecord *records; // records[langSysCount]
};

struct GPOS_FeatureTable
{
    struct CharacterVariantFeature
    {
        struct unicodeScalar { u8 ch[3]; };
        
        u16 format;
        u16 featUILabelNameID;
        u16 featUITooltipTextNameID;
        u16 sampleTextNameID;
        u16 numNamedParameters;
        u16 firstParamUILabelNameID;
        
        u16           charCount;
        unicodeScalar *character;
    };
    
    struct SizeFeature
    {
        u16 designSize;
        u16 ID;          //NOTE: If zero, the rest is ignored
        u16 nameTableCorrispondance;
        u16 rangeMin;
        u16 rangeMax;
    };
    
    struct StyleSetFeature
    {
        u16 version;
        u16 UINameID;
    };
    
    //s16 featureParamsOffset; //if NULL undefined
    union
    {
        CharacterVariantFeature charFeat;
        SizeFeature             sizeFeat;
        StyleSetFeature         styleFeat;
    } featureParamTable;
    
    u16 lookupIndexCount;
    u16 *lookupListIndices;  // lookupListIndices[lookupIndexCount]
};

struct GPOS_LookupTable
{
    enum LookupType : u16 {
        SINGLE_ADJUSTMENT           = 1,
        PAIR_ADJUSTMENT             = 2,
        CURSIVE_ATTACHMENT          = 3,
        MARKTOBASE_ATTACHMENT       = 4,
        MARKTOLIGATURE_ATTACHMENT   = 5,
        MARKTOMARK_ATTACHMENT       = 6,
        CONTEXT_POSITIONING         = 7,
        CHAINED_CONTEXT_POSITIONING = 8,
        EXTENSION_POSITIONING       = 9
    };
    
    LookupType type;
    u16        lookupFlag;
    u16        subTableCount;
    
    //NOTE: Instead of keeping the offsets, keep the tables themselves
    // s16        *subTableOffsets; // subTableOffsets[subTableCount]
    union {
        GPOS_LookupSub1 *type1;
        GPOS_LookupSub2 *type2;
        GPOS_LookupSub3 *type3;
        GPOS_LookupSub4 *type4;
        GPOS_LookupSub5 *type5;
        GPOS_LookupSub6 *type6;
        GPOS_LookupSub7 *type7;
        GPOS_LookupSub8 *type8;
        GPOS_LookupSub9 *type9;
    } subtable;
    
    u16        markFilteringSet; // Present only if USE_MARK_FILTERING_SET lookupFlag is set
};

struct GPOS_FeatureVarsList
{
};

struct OpenType_GPOS
{
    struct ScriptRecord { u32 tag; GPOS_ScriptTable script; /*s16 scriptOffset;*/ };
    struct FeatureRecord { u32 tag; GPOS_FeatureTable features; /*s16 featureOffset;*/ };
    
    //NOTE: First the GPOS header
    u16 majorVersion, minorVersion;
    
    // Version 1.0/1.1
    
    //NOTE: Instead of the offset we get the table itself
    //s16 scriptListOffset;
    //s16 featureListOffset;
    //s16 lookupListOffset;
    
    u16 scriptCount;
    ScriptRecord *scriptRecords;
    
    u16 featureCount;
    FeatureRecord *featRecords;
    
    u16 lookupCount;
    s16 *lookupOffsets;
    GPOS_LookupTable *lookups;
    
    // Version 1.1
    
    //s32 featureVariationsOffset;
};

struct OpenType_OS_2
{
    struct Tag { u8 t[4]; };
    
    u16 version;
    
    //Version 0
    s16 xAvgCharWidth;
    u16 usWeightClass;
    u16 usWidthClass;
    u16 fsType;
    s16 ySubscriptXSize;
    s16 ySubscriptYSize;
    s16 ySubscriptXOffset;
    s16 ySubscriptYOffset;
    s16 ySuperscriptXSize;
    s16 ySuperscriptYSize;
    s16 ySuperscriptXOffset;
    s16 ySuperscriptYOffset;
    s16 yStrikeoutSize;
    s16 yStrikeoutPosition;
    s16 sFamilyClass;
    u8  panose[10];
    
    u32 ulUnicodeRange1; //Bits 0-31
    u32 ulUnicodeRange2; //Bits 31-63
    u32 ulUnicodeRange3; //Bits 64-95
    u32 ulUnicodeRange4; //Bits 96-127
    
    Tag achVendID;
    u16 fsSelection;
    u16 usFirstCharIndex;
    u16 usLastCharIndex;
    s16 sTypoAscender;
    s16 sTypoDescender;
    s16 sTypoLineGap;
    u16 usWinAscent;
    u16 usWinDescent;
    
    //Version 1/2
    u32 ulCodePageRange1; //Bits 0–31
    u32 ulCodePageRange2; //Bits 32–63
    
    //Version 4/3
    s16 sxHeight;
    s16 sCapHeight;
    u16 usDefaultChar;
    u16 usBreakChar;
    u16 usMaxContext;
    
    //Version 5 only
    u16 usLowerOpticalPointSize;
    u16 usUpperOpticalPointSize;
};

struct OpenType_POST
{
    u16 versionMajor;
    u16 versionMinor;
    
    s32 italicAngle;
    s16 underlinePosition;
    s16 underlineTickness;
    
    u32 isFixedPitch;
    u32 minMemType42;
    u32 maxMemType42;
    u32 minMemType1;
    u32 maxMemType1;
    
    //Only version 2.0
    //TODO: Don't wanna support this...
    u16 numGlyphs;
    u16 *glyphNameIndex;
    u8  *stringData;
};

struct OpenType_Font
{
    OpenType_CMAP cmap;
    OpenType_HEAD head;
    OpenType_HHEA hhea;
    OpenType_HMTX hmtx;
    OpenType_MAXP maxp;
    OpenType_KERN kern;
    OpenType_NAME name;
    OpenType_OS_2 os2;
    OpenType_POST post;
    OpenType_CFF  cff;
    //OpenType_GPOS gpos;
    
    struct OpenType_Glyph { u32 glyphSizes; void *data; };
    
    Array<OpenType_Glyph> glyphs;
};


extern "C"
{
    OpenType_Font ls_openTypeLoadFont(string filePath);
    u16           ls_openTypeGetGlyphID(OpenType_CMAP *cmap, u16 codepoint);
    
    //TODO: This bullshit is debug code. Should not need to memcpy this stuff...
    u32  ls_openTypeGetGlyphCharstring(OpenType_Font *font, u16 glyphID, char *buf, u32 bufMaxSize);
    void ls_openTypeCharstringToImage(OpenType_Font *font, char *charstring, 
                                      u32 charLen, char *outBuf, u32 bufMaxSize);
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
OpenType_OffTable OpenType_readOffTable(u8 *t)
{
    OpenType_OffTable Res = {};
    u8 *At = t;
    
    Res.sfntVersion   = GetByteSwap32(At);
    Res.numTables     = GetByteSwap16(At);
    Res.searchRange   = GetByteSwap16(At);
    Res.entrySelector = GetByteSwap16(At);
    Res.rangeShift    = GetByteSwap16(At);
    
    return Res;
}

static
OpenType_TableRecord OpenType_readTableRecord(u8 *c)
{
    OpenType_TableRecord Res = {};
    u8 *At = c;
    
    Res.tableTag = GetByteSwap32(At);
    Res.checkSum = GetByteSwap32(At);
    Res.offset   = GetByteSwap32(At);
    Res.length   = GetByteSwap32(At);
    
    return Res;
}

static
void OpenType_readHEADTable(OpenType_Font *font, u8 *h)
{
    OpenType_HEAD *head = &font->head;
    u8 *At = h;
    
    head->major                 = GetByteSwap16(At);
    head->minor                 = GetByteSwap16(At);
    head->fontRevision.integer  = GetByteSwap16(At);
    head->fontRevision.fraction = GetByteSwap16(At);
    head->checksumAdjustment    = GetByteSwap32(At);
    head->magicNumber           = GetByteSwap32(At);
    Assert(head->magicNumber == 0x5F0F3CF5);
    
    head->flags                 = GetByteSwap16(At);
    head->unitsPerEm            = GetByteSwap16(At);
    head->created               = GetByteSwapS64(At);
    head->modified              = GetByteSwapS64(At);
    
    head->xMin                  = GetByteSwapS16(At);
    head->yMin                  = GetByteSwapS16(At);
    head->xMax                  = GetByteSwapS16(At);
    head->yMax                  = GetByteSwapS16(At);
    
    head->macStyle              = GetByteSwap16(At);
    head->lowestRecPPEM         = GetByteSwap16(At);
    head->fontDirectionHint     = GetByteSwap16(At);   //Deprecated: Set to 2
    Assert(head->fontDirectionHint == 2);
    
    head->indexToLocFormat      = GetByteSwapS16(At);   // 0 for u16, 1 for u32
    head->glyphDataFormat       = GetByteSwapS16(At);   // 0
};

static
void OpenType_readHHEATable(OpenType_Font *font, u8 *h)
{
    OpenType_HHEA *hhea = &font->hhea;
    u8 *At = h;
    
    hhea->majorVersion        = GetByteSwap16(At);
    hhea->minorVersion        = GetByteSwap16(At);
    
    hhea->ascender            = GetByteSwapS16(At);
    hhea->descender           = GetByteSwapS16(At);
    hhea->lineGap             = GetByteSwapS16(At);
    hhea->advanceWidthMax     = GetByteSwap16(At);
    hhea->minLeftSideBearing  = GetByteSwapS16(At);
    hhea->minRightSideBearing = GetByteSwapS16(At);
    hhea->xMaxExtent          = GetByteSwapS16(At);
    
    hhea->caretSlopeRise      = GetByteSwapS16(At);
    hhea->caretSlopeRun       = GetByteSwapS16(At);
    hhea->caretOffset         = GetByteSwapS16(At);
    
    //Skip reserved
    At += (4 * sizeof(s16));
    
    hhea->metricDataFormat    = GetByteSwap16(At);
    hhea->numberOfHMetrics    = GetByteSwap16(At);
}

static
void OpenType_readHMTXTable(OpenType_Font *font, u8 *h)
{
    OpenType_HMTX *hmtx = &font->hmtx;
    u8 *At = h;
    
    u32 numMetrics = font->hhea.numberOfHMetrics;
    u32 numGlyphs  = font->maxp.numGlyphs;
    
    hmtx->hMetrics = (OpenType_HMTX::LongHorMetric *)ls_alloc(sizeof(OpenType_HMTX::LongHorMetric) * numMetrics);
    hmtx->leftSideBearings = (s16 *)ls_alloc(sizeof(s16) * (numGlyphs - numMetrics));
    hmtx->bearingsCount = (numGlyphs - numMetrics);
    
    for(u32 i = 0; i < numMetrics; i++)
    {
        hmtx->hMetrics[i].advanceWidth = GetByteSwap16(At);
        hmtx->hMetrics[i].lsb          = GetByteSwap16(At);
    }
    
    for(u32 i = 0; i < (numGlyphs - numMetrics); i++)
    {
        hmtx->leftSideBearings[i]       = GetByteSwapS16(At);
    }
    
    return;
}

static
void OpenType_readNAMETable(OpenType_Font *font, u8 *n)
{
    OpenType_NAME *name = &font->name;
    u8 *At = n;
    
    name->version    = GetByteSwap16(At);
    name->count      = GetByteSwap16(At);
    name->storageOff = GetByteSwap16(At);
    
    name->nameRecord = (OpenType_NAME::NameRecord *)ls_alloc(sizeof(OpenType_NAME::NameRecord) * name->count);
    
    u32 totalStringData = 0;
    for(u32 i = 0; i < name->count; i++)
    {
        OpenType_NAME::NameRecord *curr = &name->nameRecord[i];
        
        curr->platformID = GetByteSwap16(At);
        curr->encodingID = GetByteSwap16(At);
        curr->languageID = GetByteSwap16(At);
        curr->nameID     = GetByteSwap16(At);
        curr->length     = GetByteSwap16(At);
        curr->stringOff  = GetByteSwap16(At);
        
        totalStringData += curr->length;
    }
    
    if(name->version == 0) 
    { 
        name->data = ls_alloc(totalStringData);
        ls_memcpy(At, name->data, totalStringData);
        return;
    }
    else if(name->version == 1)
    {
        name->langTagCount = GetByteSwap16(At);
        
        name->langTagRecord = (OpenType_NAME::LangTagRecord *)
            ls_alloc(sizeof(OpenType_NAME::LangTagRecord) * name->langTagCount);
        
        for(u32 i = 0; i < name->langTagCount; i++)
        {
            name->langTagRecord[i].length     = GetByteSwap16(At);
            name->langTagRecord[i].langTagOff = GetByteSwap16(At);
            
            totalStringData += name->langTagRecord[i].length;
        }
        
        name->data = ls_alloc(totalStringData);
        ls_memcpy(At, name->data, totalStringData);
    }
    else
    {
        ls_printf("Error in NAME table. Version is %d\n", name->version);
        Assert(FALSE);
    }
}

static
void OpenType_readOS_2Table(OpenType_Font *font, u8 *o)
{
    OpenType_OS_2 *os2 = &font->os2;
    u8 *At = o;
    
    os2->version = GetByteSwap16(At);
    
    Assert((os2->version >= 0) && (os2->version <= 5));
    
    os2->xAvgCharWidth = GetByteSwapS16(At);
    os2->usWeightClass = GetByteSwap16(At);
    os2->usWidthClass  = GetByteSwap16(At);
    os2->fsType        = GetByteSwap16(At);
    
    os2->ySubscriptXSize     = GetByteSwapS16(At);
    os2->ySubscriptYSize     = GetByteSwapS16(At);
    os2->ySubscriptXOffset   = GetByteSwapS16(At);
    os2->ySubscriptYOffset   = GetByteSwapS16(At);
    os2->ySuperscriptXSize   = GetByteSwapS16(At);
    os2->ySuperscriptYSize   = GetByteSwapS16(At);
    os2->ySuperscriptXOffset = GetByteSwapS16(At);
    os2->ySuperscriptYOffset = GetByteSwapS16(At);
    os2->yStrikeoutSize      = GetByteSwapS16(At);
    os2->yStrikeoutPosition  = GetByteSwapS16(At);
    
    for(u32 i = 0; i < 10; i++) { os2->panose[i] = *At; At += 1; }
    
    os2->ulUnicodeRange1 = GetByteSwap32(At);
    os2->ulUnicodeRange2 = GetByteSwap32(At);
    os2->ulUnicodeRange3 = GetByteSwap32(At);
    os2->ulUnicodeRange4 = GetByteSwap32(At);
    
    for(u32 i = 0; i < 4; i++) { os2->achVendID.t[i] = *At; At += 1; }
    
    os2->fsSelection      = GetByteSwap16(At);
    os2->usFirstCharIndex = GetByteSwap16(At);
    os2->usLastCharIndex  = GetByteSwap16(At);
    os2->sTypoAscender    = GetByteSwapS16(At);
    os2->sTypoDescender   = GetByteSwapS16(At);
    os2->sTypoLineGap     = GetByteSwapS16(At);
    os2->usWinAscent      = GetByteSwap16(At);
    os2->usWinDescent     = GetByteSwap16(At);
    
    if(os2->version > 0)
    {
        os2->ulCodePageRange1 = GetByteSwap32(At);
        os2->ulCodePageRange2 = GetByteSwap32(At);
        
        if(os2->version > 2)
        {
            os2->sxHeight   = GetByteSwapS16(At);
            os2->sCapHeight = GetByteSwapS16(At);
            
            os2->usDefaultChar = GetByteSwap16(At);
            os2->usBreakChar   = GetByteSwap16(At);
            os2->usMaxContext  = GetByteSwap16(At);
            
            if(os2->version > 4)
            {
                os2->usLowerOpticalPointSize = GetByteSwap16(At);
                os2->usUpperOpticalPointSize = GetByteSwap16(At);
            }
        }
    }
}

static
void OpenType_readPOSTTable(OpenType_Font *font, u8 *p)
{
    OpenType_POST *post = &font->post;
    u8 *At = p;
    
    post->versionMajor = GetByteSwap16(At);
    post->versionMinor = GetByteSwap16(At);
    
    if(post->versionMajor == 2) { return; }
    
    post->italicAngle       = GetByteSwapS32(At);
    post->underlinePosition = GetByteSwapS16(At);
    post->underlineTickness = GetByteSwapS16(At);
    
    post->isFixedPitch = GetByteSwap32(At);
    
    post->minMemType42 = GetByteSwap32(At);
    post->maxMemType42 = GetByteSwap32(At);
    post->minMemType1  = GetByteSwap32(At);
    post->maxMemType1  = GetByteSwap32(At);
    
}

static
void OpenType_readKERNTable(OpenType_Font *font, u8 *k)
{
    OpenType_KERN *kern = &font->kern;
    u8 *At = k;
    
    kern->version   = GetByteSwap16(At);
    kern->numTables = GetByteSwap16(At);
    
    kern->format0   = (OpenType_KERN_Subtable_0 *)ls_alloc(sizeof(OpenType_KERN_Subtable_0)*kern->numTables);
    
    for(u32 i = 0; i < kern->numTables; i++)
    {
        OpenType_KERN_Subtable_0 *sub = &kern->format0[i];
        
        sub->version       = GetByteSwap16(At);
        sub->length        = GetByteSwap16(At);
        sub->coverage      = GetByteSwap16(At);
        
        //TODONOTE: Only windows format 0 is implemented.
        u8 subFormat = (sub->coverage & 0xFF00) >> 8;
        Assert(subFormat == 0);
        
        
        sub->numPairs      = GetByteSwap16(At);
        sub->searchRange   = GetByteSwap16(At);
        sub->entrySelector = GetByteSwap16(At);
        sub->rangeShift    = GetByteSwap16(At);
        
        sub->pairs = (OpenType_KERN_Subtable_0::Pairs *)
            ls_alloc(sizeof(OpenType_KERN_Subtable_0::Pairs)*sub->numPairs);
        
        for(u32 j = 0; j < sub->numPairs; j++)
        {
            sub->pairs[j].left  = GetByteSwap16(At);
            sub->pairs[j].right = GetByteSwap16(At);
            sub->pairs[j].value = GetByteSwapS16(At);
        }
    }
}

/*
static
void OpenType_readGPOSTable(OpenType_Font *font, u8 *g)
{
    OpenType_GPOS *gpos = &font->gpos;
    u8 *At = g;
    
    //NOTE: REMEMBER!! In LookupSub2 Both PariValueRecord and ClassRecord are flattened Arrays!!!
    gpos->majorVersion = GetByteSwap16(At);
    gpos->minorVersion = GetByteSwap16(At);
    
    s16 scriptListOffset  = GetByteSwapS16(At);
    s16 featureListOffset = GetByteSwapS16(At);
    s16 lookupListOffset  = GetByteSwapS16(At);
    
    if(gpos->majorVersion == 1 && gpos->minorVersion == 1)
    { s32 featureVariationsOffset = GetByteSwapS32(At); }
    
    //NOTE: Get the ScriptList
    u8 *sList = At = g + scriptListOffset;
    
    gpos->scriptCount = GetByteSwap16(At);
    gpos->scriptRecords = (OpenType_GPOS::ScriptRecord *)
        ls_alloc(sizeof(OpenType_GPOS::ScriptRecord) * gpos->scriptCount);
    
    u8 *Bt = 0;
    u8 *Ct = 0;
    for(u32 i = 0; i < gpos->scriptCount; i++)
    {
        OpenType_GPOS::ScriptRecord *rec = &gpos->scriptRecords[i];
        
        rec->tag = GetByteSwap32(At);
        s16 scriptTableOffset = GetByteSwapS16(At);
        
        Bt = sList + scriptTableOffset;
        rec->script.defaultLangSysOffset = GetByteSwapS16(Bt);
        rec->script.langSysCount         = GetByteSwap16(Bt);
        
        rec->script.records = (GPOS_ScriptTable::LangSysRecord *)
            ls_alloc(sizeof(GPOS_ScriptTable::LangSysRecord) * rec->script.langSysCount);
        
        for(u32 j = 0; j < rec->script.langSysCount; j++)
        {
            GPOS_ScriptTable::LangSysRecord *langRec = &rec->script.records[j];
            
            langRec->tag        = GetByteSwap32(Bt);
            s16 langSysTableOff = GetByteSwapS16(Bt);
            
            Ct = sList + scriptTableOffset + langSysTableOff;
            langRec->langSys.lookupOrderOffset = GetByteSwapS16(Ct);
            Assert(langRec->langSys.lookupOrderOffset == NULL); //NOTE: Reserved
            
            langRec->langSys.requiredFeatureIndex = GetByteSwap16(Ct);
            langRec->langSys.featureIndexCount    = GetByteSwap16(Ct);
            langRec->langSys.featureIndices = (u16 *)ls_alloc(sizeof(u16) * langRec->langSys.featureIndexCount);
            
            for(u32 k = 0; k < langRec->langSys.featureIndexCount; k++)
            {
                langRec->langSys.featureIndices[k] = GetByteSwap16(Ct);
            }
        }
    }
    
    //NOTE: Get the ScriptList
    u8 *featList = At = g + featureListOffset;
    
    gpos->featureCount = GetByteSwap16(At);
    gpos->featRecords  = (OpenType_GPOS::FeatureRecord *)
        ls_alloc(sizeof(OpenType_GPOS::FeatureRecord) * gpos->featureCount);
    
    Bt = 0;
    Ct = 0;
    for(u32 i = 0; i < gpos->featureCount; i++)
    {
        OpenType_GPOS::FeatureRecord *rec = &gpos->featRecords[i];
        
        rec->tag            = GetByteSwap32(At);
        s16 featTableOffset = GetByteSwapS16(At);
        
        Bt = featList + featTableOffset;
        
        s16 featureParamOffset = GetByteSwapS16(Bt);
        
        
        Assert(FALSE); //TODO: Get Feature Param Table
    }
    
    Assert(FALSE);
}
*/

static
void OpenType_readMAXPTable(OpenType_Font *font, u8 *m)
{
    OpenType_MAXP *maxp = &font->maxp;
    u8 *At = m;
    
    //ONLY u16 numGlyphs for 0.5 (CFF data fonts)
    maxp->version.integer  = GetByteSwap16(At);
    maxp->version.fraction = GetByteSwap16(At);
    maxp->numGlyphs        = GetByteSwap16(At);
    
    if((maxp->version.integer == 0x0001) && (maxp->version.fraction == 0x0000))
    {
        maxp->maxPoints             = GetByteSwap16(At);
        maxp->maxContours           = GetByteSwap16(At);
        maxp->maxCompositePoints    = GetByteSwap16(At);
        maxp->maxCompositeContours  = GetByteSwap16(At);
        maxp->maxZones              = GetByteSwap16(At);
        maxp->maxTwilightPoints     = GetByteSwap16(At);
        maxp->maxStorage            = GetByteSwap16(At);
        maxp->maxFunctionDefs       = GetByteSwap16(At);
        maxp->maxInstructionDefs    = GetByteSwap16(At);
        maxp->maxStackElements      = GetByteSwap16(At);
        maxp->maxSizeOfInstructions = GetByteSwap16(At);
        maxp->maxComponentElements  = GetByteSwap16(At);
        maxp->maxComponentDepth     = GetByteSwap16(At);
    }
}

static
s32 OpenType_findEndCode(u16 *endC, u16 size, u16 character)
{
    for(u32 i = 0; i < size; i++)
    {
        if(endC[i] >= character) { return i; }
    }
    return -1;
}

u16 ls_openTypeGetGlyphID(OpenType_CMAP *cmap, u16 codepoint)
{
    u32 segCount = cmap->segCountX2 / 2;
    
    s32 idx = OpenType_findEndCode(cmap->endCode, segCount, codepoint);
    if(cmap->startCode[idx] > codepoint) 
    { 
        //NOTE: Missing Glyph
        return 0x0000;
    }
    else
    {
        if(cmap->idRangeOff[idx] == 0)
        {
            return cmap->idDelta[idx] + codepoint;
        }
        else
        {
            //u16 glyphIndex = *((u16 *)idRangeOffStart + idx + (Res.idRangeOff[idx] / 2) + (codepoint - Res.startCode[idx]));
            
            //NOTE: What I can do to avoid this annoying trick, and actually work on stored values (Which I may actually want to avoid doing, but for now we will do it) is:
            // Start from the address of glyphIDArr[0].
            
            u32 glyphIndex = (idx + (cmap->idRangeOff[idx] / 2) + (codepoint - cmap->startCode[idx])) - (segCount);
            return cmap->glyphIDArr[glyphIndex];
            
        }
    }
    
    Assert(FALSE);
}

//TODO: REMOVE THIS. DEBUG ONLY!

void __printIndent(u32 depth) {
    char buff[32] = {};
    for(u32 i = 0; i < depth*2; i++)
    { buff[i] = ' ';  }
    
    ls_printf("%cs", buff); 
}


//TODO: This bullshit is debug code. Should not need to memcpy this stuff...
//      Actually, this stuff should be useless to a user.
u32 ls_openTypeGetGlyphCharstring(OpenType_Font *font, u16 glyphID, char *charstringBuff, u32 buffMaxSize)
{
    //NOTE: -1 because offsets are 1-index arrays
    u32 size = font->cff.Charstrings.offsets[glyphID+1] - font->cff.Charstrings.offsets[glyphID];
    u32 offFromData = font->cff.Charstrings.offsets[glyphID] - 1;
    
    u8 *GlyphCharstring = font->cff.Charstrings.data + offFromData;
    
    if(size > buffMaxSize) { ls_printf("Couldn't return glyph charstring. Buffer too small.\n"); return 0; }
    
    ls_memcpy(GlyphCharstring, charstringBuff, size);
    return size;
}

u32 ls_openTypeGetSubroutine(OpenType_Font *font, u16 subrNumber, char *subrBuff, u32 srBuffMax)
{
    u32 size = font->cff.LocalSubr.offsets[subrNumber+1] - font->cff.LocalSubr.offsets[subrNumber];
    u32 offFromData = font->cff.LocalSubr.offsets[subrNumber] - 1;
    
    u8 *Subroutine = font->cff.LocalSubr.data + offFromData;
    
    if(size > srBuffMax) { ls_printf("Couldn't return Subroutine charstring. Buffer too small.\n"); return 0; }
    
    ls_memcpy(Subroutine, subrBuff, size);
    return size;
}

static
b32 OpenType_CharstringIsOperator(u8 v)
{
    if((v >= 0) && (v <= 27)) { return TRUE; }
    if((v >= 29) && (v <= 31)) { return TRUE; }
    
    return FALSE;
}

static
void ls_openTypeDrawLine(v2i start, v2i diff, u8 *buff, u32 width, u32 height)
{
    s32 incY = 0;
    if(diff.y > 0) incY =  1;
    if(diff.y < 0) incY = -1;
    
    s32 incX = 0;
    if(diff.x > 0) incX =  1;
    if(diff.x < 0) incX = -1;
    
    
    const u32 bytesPerPixel = 4;
    
    f32 l = LengthV2i(diff);
    v2 unit = { diff.x / l, diff.y / l };
    
    v2 curr = { (f32)start.x, (f32)start.y };
    for(u32 i = 0; i < l; i++)
    {
        s32 x = curr.x;
        s32 y = curr.y;
        
        s32 idx = (y*width + x)*bytesPerPixel;
        buff[idx]   = 0x00; //B
        buff[idx+1] = 0x00; //G
        buff[idx+2] = 0x00; //R
        buff[idx+3] = 0x00; //A
        
        curr = {curr.x + unit.x, curr.y + unit.y};
    }
    
    return;
}

static
void ls_openTypeDrawBezier4(v2i P0, v2i P1, v2i P2, v2i P3, u8 *buff, u32 width, u32 height)
{
    const u32 bytesPerPixel = 4;
    
    f32 t = 0.001f;
    
    for(u32 i = 0; i < 1000; i++)
    {
        f32 compl = (1.0f-t);
        f32 compl2 = compl*compl;
        f32 compl3 = compl2*compl;
        
        s32 Y = (compl3*P0.y) + (3.0f*compl2*t*P1.y) + (3.0f*compl*t*t*P2.y) + (t*t*t*P3.y);
        s32 X = (compl3*P0.x) + (3.0f*compl2*t*P1.x) + (3.0f*compl*t*t*P2.x) + (t*t*t*P3.x);
        
        if(Y == UINT32_MAX) { Y = 0; }
        if(X == UINT32_MAX) { X = 0; }
        
        s32 idx = (Y*width + X)*bytesPerPixel;
        buff[idx]   = 0x00; //B
        buff[idx+1] = 0x00; //G
        buff[idx+2] = 0x00; //R
        buff[idx+3] = 0x00; //A
        
        t += 0.001f;
    }
}

static
void ls_openTypeDrawBezier(v2i P0, v2i P1, v2i P2, u8 *buff, u32 width, u32 height)
{
    const u32 bytesPerPixel = 4;
    
    f32 t = 0.001f;
    
    for(u32 i = 0; i < 1000; i++)
    {
        f32 lineOneX = (1.0f - t)*P0.x + t*P1.x;
        f32 lineTwoX = (1.0f - t)*P1.x + t*P2.x;
        u32 X = (u32)((1.0f - t)*lineOneX + t*lineTwoX);
        
        f32 lineOneY = (1.0f - t)*P0.y + t*P1.y;
        f32 lineTwoY = (1.0f - t)*P1.y + t*P2.y;
        u32 Y = (u32)((1.0f - t)*lineOneY + t*lineTwoY);
        
        u32 idx = (Y*width + X)*bytesPerPixel;
        buff[idx]   = 0x00; //B
        buff[idx+1] = 0x00; //G
        buff[idx+2] = 0x00; //R
        buff[idx+3] = 0x00; //A
        
        t += 0.001f;
    }
}


static u32 __debug_indentation = 0;
static u32 __debug_counter = 0;


static
void ls_openTypeMoveTo(v2i *pos, s32 dx, s32 dy)
{
    pos->x += dx;
    pos->y += dy;
    
    __printIndent(__debug_indentation);
    if(dx == 0)      { ls_printf("(0, %d) vmoveto\n", dy); }
    else if(dy == 0) { ls_printf("(%d, 0) hmoveto\n", dx); }
    else             { ls_printf("(%d, %d) rmoveto\n", dx, dy); }
}

static
void ls_openTypeCurveTo(stack *args, v2i *pos, u8 *outBuf, s32 w, s32 h, b32 isVertical = FALSE)
{
#define PullVal() *((s32 *)ls_stackPull(args))
    
    v2i p0 = {};
    v2i p1 = {};
    v2i p2 = {};
    v2i p3 = {};
    
    b32 horizontal = (((args->count & 0xFE) % 4) == 0);
    if(isVertical) { horizontal = !horizontal; }
    
    __printIndent(__debug_indentation);
    while(args->count > 0)
    {
        if(horizontal)
        {
            p0 = *pos;
            p1.x = pos->x + PullVal();
            p1.y = pos->y;
            p2.x = p1.x + PullVal();
            p2.y = p1.y + PullVal();
            p3.y = p2.y + PullVal();
            
            
            if(args->count == 1) { p3.x = p2.x + PullVal(); }
            else                 { p3.x = p2.x; }
            
            pos->x = p3.x;
            pos->y = p3.y;
            
            //NOTE: Curve 1
            ls_printf("[(%d, %d) (%d, %d) (%d, %d)] ", p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
            
            ls_openTypeDrawBezier4(p0, p1, p2, p3, outBuf, w, h);
            
            //DEBUG
            char fileName[64] = {};
            ls_sprintf(fileName, "test%d.bmp", __debug_counter);
            __debug_counter += 1;
            
            string pathTest = ls_strConst(fileName);
            ls_bitmapWrite(pathTest, outBuf, w, h);
            //DEBUG
            
            horizontal = !horizontal;
        }
        else
        {
            
            p0 = *pos;
            p1.x = pos->x;
            p1.y = pos->y + PullVal();
            p2.x = p1.x + PullVal();
            p2.y = p1.y + PullVal();
            p3.x = p2.x + PullVal();
            
            if(args->count == 1) { p3.y = p2.y + PullVal(); }
            else                 { p3.y = p2.y; }
            
            pos->x = p3.x;
            pos->y = p3.y;
            
            //NOTE: Curve 2
            ls_printf("[(%d, %d) (%d, %d) (%d, %d)] ", p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
            
            ls_openTypeDrawBezier4(p0, p1, p2, p3, (u8 *)outBuf, w, h);
            
            //DEBUG
            char fileName[64] = {};
            ls_sprintf(fileName, "test%d.bmp", __debug_counter);
            __debug_counter += 1;
            
            string pathTest = ls_strConst(fileName);
            ls_bitmapWrite(pathTest, (u8 *)outBuf, w, h);
            //DEBUG
            
            horizontal = !horizontal;
        }
    }
    
    if(!isVertical) { ls_printf("hvcurveto\n"); }
    else { ls_printf("vhcurveto\n"); }
    
#undef PullVal
}

static
void ls_openTypeLineTo(stack *args, v2i *pos, u8 *outBuf, s32 w, s32 h, b32 isVLine = FALSE)
{
#define PullVal() *((s32 *)ls_stackPull(args))
    
    v2i diff1 = {};
    v2i diff2 = {};
    
    s32 extraV = 0;
    
    b32 hasSolo = ((args->count % 2) != 0);
    b32 isVertical = isVLine;
    
    if(hasSolo)
    {
        extraV = PullVal();
        if(isVertical) { diff1 = {0, extraV}; }
        else           { diff1 = {extraV, 0}; }
        
        ls_openTypeDrawLine(*pos, diff1, outBuf, w, h);
        pos->x += diff1.x;
        pos->y += diff1.y;
        
        ls_printf("[%d] ", extraV);
        
        //DEBUG
        char fileName[64] = {};
        ls_sprintf(fileName, "test%d.bmp", __debug_counter);
        __debug_counter += 1;
        
        string pathTest = ls_strConst(fileName);
        ls_bitmapWrite(pathTest, outBuf, w, h);
        //DEBUG
        
        isVertical = !isVertical;
    }
    
    diff1 = {};
    diff2 = {};
    
    while(args->count > 0)
    {
        if(!isVertical)
        {
            diff1.x = PullVal();
            diff2.y = PullVal();
        }
        else
        {
            diff1.y = PullVal();
            diff2.x = PullVal();
        }
        
        ls_printf("[%d %d] ", diff1.x, diff1.y);
        
        
        ls_openTypeDrawLine(*pos, diff1, outBuf, w, h);
        pos->x += diff1.x;
        pos->y += diff1.y;
        
        //DEBUG
        char fileName[64] = {};
        ls_sprintf(fileName, "test%d.bmp", __debug_counter);
        __debug_counter += 1;
        
        string pathTest = ls_strConst(fileName);
        ls_bitmapWrite(pathTest, outBuf, w, h);
        //DEBUG
        
        
        ls_openTypeDrawLine(*pos, diff2, outBuf, w, h);
        pos->x += diff2.x;
        pos->y += diff2.y;
        
        //DEBUG
        ls_zeroMem(fileName, 64);
        ls_sprintf(fileName, "test%d.bmp", __debug_counter);
        __debug_counter += 1;
        
        pathTest = ls_strConst(fileName);
        ls_bitmapWrite(pathTest, outBuf, w, h);
        //DEBUG
    }
    
    if(isVLine) { ls_printf("vlineto\n"); }
    else        { ls_printf("hlineto\n"); }
#undef PullVal
}

//TODO: This bullshit is debug code. Should not need to memcpy this stuff...
//      Actually, this stuff should be useless to a user.
void ls_openTypeCharstringToImage(OpenType_Font *font, char *charstring, u32 charLen, v2i *pos, char *outBuf, u32 w, u32 h)
{
    //NOTE:NOTE:NOTE:
    // Documentation can be found here:
    //            https://wwwimages2.adobe.com/content/dam/acom/en/devnet/font/pdfs/5177.Type2.pdf
    //
    // Other useful links:
    //            https://docs.rs/cff/0.5.0/src/cff/glyphs/charstring/mod.rs.html#15-955
    //            https://fontdrop.info/#/?darkmode=true
    //            https://github.com/caryll/otfcc/tree/235d1bd6fb81c8daeaa5232aa840c1e37f07fa86/lib/libcff
    //
    
#define PullVal() *((s32 *)ls_stackPull(&args))
    
    u8 *At = (u8 *)charstring;
    stack args = ls_stackInit(sizeof(s32), 16); 
    
    u32 width = 0;
    u32 numHints = 0;
    
    auto __maybePullWidth = [font, &width, &args]() {
        if((args.used % 2) != 0)
        {
            width = font->cff.PrivateDict.nominalWidthX + PullVal();
            
            __printIndent(__debug_indentation);
            ls_printf("width %d\n", width);
        }
    };
    
    
    while(((u64)At - (u64)charstring) < charLen)
    {
        if(charLen > 100000)
        { 
            ls_printf("Error in charstring processing, charLen wrapped around zero.\n");
            Assert(FALSE);
        }
        
        while(!OpenType_CharstringIsOperator(*At))
        {
            u8 currVal = *At;
            if(currVal == 28) // next two bytes as s16
            {
                s32 v = *((s16 *)(At+1));
                ls_stackPush(&args, &v);
                
                At += 3;
                continue;
            }
            
            if((currVal >= 32) && (currVal <= 246))
            {
                s32 v = (currVal - 139);
                ls_stackPush(&args, &v);
                
                At += 1;
                continue;
            }
            
            if((currVal >= 247) && (currVal <= 250))
            {
                u8 secondVal = *(At+1);
                s32 v = ((currVal-247) * 256) + secondVal + 108;
                ls_stackPush(&args, &v);
                
                At += 2;
                continue;
            }
            
            if((currVal >= 251) && (currVal <= 254))
            {
                u8 secondVal = *(At+1);
                s32 v = -((currVal - 251)*256) - secondVal - 108;
                ls_stackPush(&args, &v);
                
                At += 2;
                continue;
            }
            
            if(currVal == 255)
            {
                s32 v = *((s32 *)(At+1));
                ls_stackPush(&args, &v);
                
                At += 5;
                continue;
            }
            
            
        }
        
        u8 oneByte = *At; At += 1;
        
        switch(oneByte)
        {
            case 12: break;
            
            
            case 1: //hstem
            {
                __maybePullWidth();
                
                s32 yA = 0;
                s32 yB = 0;
                
                __printIndent(__debug_indentation);
                //while(args.bot <= args.top)
                while(args.count > 0)
                {
                    yA = PullVal();
                    yB = PullVal();
                    numHints += 1;
                    
                    ls_printf("[%d %d] ", yA, yB);
                }
                
                ls_printf("hstem\n");
                
            } break;
            
            case 3: //vstem
            {
                __maybePullWidth();
                
                s32 yA = 0;
                s32 yB = 0;
                
                __printIndent(__debug_indentation);
                //while(args.bot <= args.top)
                while(args.count > 0)
                {
                    yA = PullVal();
                    yB = PullVal();
                    numHints += 1;
                    
                    ls_printf("[%d %d] ", yA, yB);
                }
                
                ls_printf("vstem\n");
            } break;
            
            case 4: //vmoveto
            {
                __maybePullWidth();
                ls_openTypeMoveTo(pos, 0, PullVal());
            } break;
            
            case 5: //rlineto
            {
                s32 dx = 0;
                s32 dy = 0;
                
                __printIndent(__debug_indentation);
                //while(args.bot <= args.top)
                while(args.count > 0)
                {
                    dx = PullVal();
                    dy = PullVal();
                    
                    ls_printf("[%d %d] ", dx, dy);
                    
                    v2i diff = {dx, dy};
                    
                    ls_openTypeDrawLine(*pos, diff, (u8 *)outBuf, w, h);
                    
                    pos->x += dx;
                    pos->y += dy;
                    
                    //DEBUG
                    char fileName[64] = {};
                    ls_sprintf(fileName, "test%d.bmp", __debug_counter);
                    __debug_counter += 1;
                    
                    string pathTest = ls_strConst(fileName);
                    
                    ls_bitmapWrite(pathTest, (u8 *)outBuf, w, h);
                    //DEBUG
                    
                }
                
                ls_printf("rlineto\n");
            } break;
            
            case 6: //hlineto
            { ls_openTypeLineTo(&args, pos, (u8 *)outBuf, w, h, FALSE); } break;
            
            case 7: //vlineto
            { ls_openTypeLineTo(&args, pos, (u8 *)outBuf, w, h, TRUE);  } break;
            
            case 8: //rrcurveto
            {
                v2i p0 = {};
                v2i p1 = {};
                v2i p2 = {};
                v2i p3 = {};
                
                __printIndent(__debug_indentation);
                //while(args.bot <= args.top)
                while(args.count > 0)
                {
                    p0 = *pos;
                    p1.x = pos->x + PullVal();
                    p1.y = pos->y + PullVal();
                    p2.x = p1.x   + PullVal();
                    p2.y = p1.y   + PullVal();
                    p3.x = p2.x   + PullVal();
                    p3.y = p2.y   + PullVal();
                    
                    ls_printf("[(%d, %d) (%d, %d) (%d, %d)] ", p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
                    
                    pos->x = p3.x;
                    pos->y = p3.y;
                    
                    ls_openTypeDrawBezier4(p0, p1, p2, p3, (u8 *)outBuf, w, h);
                    
                    //DEBUG
                    char fileName[64] = {};
                    ls_sprintf(fileName, "test%d.bmp", __debug_counter);
                    __debug_counter += 1;
                    
                    string pathTest = ls_strConst(fileName);
                    ls_bitmapWrite(pathTest, (u8 *)outBuf, w, h);
                    //DEBUG
                    
                }
                
                ls_printf("rrcurveto\n");
                
            } break;
            
            case 10: //callsubr
            {
                u32 numSubr = font->cff.LocalSubr.count;
                u32 bias = 0;
                if(numSubr < 1240) bias = 107;
                else if(numSubr < 33900) bias = 1131;
                else bias = 32768;
                
                s32 subrNumber = *((s32 *)ls_stackPull(&args)) + bias;
                
                const u32 srBuffMax = 1024;
                char subrBuff[srBuffMax] = {};
                u32 subrSize = ls_openTypeGetSubroutine(font, subrNumber, subrBuff, srBuffMax);
                
                __printIndent(__debug_indentation);
                ls_printf("callsubr %d\n\n", subrNumber);
                __debug_indentation += 1;
                ls_openTypeCharstringToImage(font, subrBuff, subrSize, pos, outBuf, w, h);
                __debug_indentation -= 1;
                ls_printf("\n");
                
            } break;
            
            case 11: //return
            {
                
                //NOTE: Can I just go back?
                __printIndent(__debug_indentation);
                ls_printf("return\n");
                Assert(args.count == 0);
                return;
            } break;
            
            case 14: //endchar
            {
                __printIndent(__debug_indentation);
                ls_printf("endchar\n");
                Assert(args.count == 0);
            } break;
            
            case 18: //hstemhm
            {
                __maybePullWidth();
                
                s32 yA = 0;
                s32 yB = 0;
                
                __printIndent(__debug_indentation);
                //while(args.bot <= args.top)
                while(args.count > 0)
                {
                    yA = PullVal();
                    yB = PullVal();
                    numHints += 1;
                    
                    ls_printf("[%d %d] ", yA, yB);
                }
                
                ls_printf("hstemhm\n");
                
            } break;
            
            case 19: //hintmask
            {
                //Process any implict vstem hints
                if(args.used != 0)
                {
                    s32 yA = 0;
                    s32 yB = 0;
                    
                    __printIndent(__debug_indentation);
                    //while(args.bot <= args.top)
                    while(args.count > 0)
                    {
                        yA = PullVal();
                        yB = PullVal();
                        numHints += 1;
                        
                        ls_printf("[%d %d] ", yA, yB);
                    }
                    
                    ls_printf("vstem_impl\n");
                }
                
                u32 numBytes = (numHints + 7) / 8;
                
                //TODONOTE DO I NEED TO BYTESWAP HERE!?!?!?
                u64 mask = 0;
                switch(numBytes)
                {
                    case 1: mask = GetByte(At); break;
                    case 2: mask = GetByteSwap16(At); break;
                    
                    default:
                    Assert(FALSE);
                    break;
                }
                
                //numHints = 0;
                __printIndent(__debug_indentation);
                ls_printf("hintmask %bd\n", mask);
                
            } break;
            
            case 21: //rmoveto
            {
                //TODO: How to lamda?
                if(args.used == 3)
                {
                    width = font->cff.PrivateDict.nominalWidthX + PullVal();
                    
                    __printIndent(__debug_indentation);
                    ls_printf("width %d\n", width);
                }
                
                s32 dx = PullVal();
                s32 dy = PullVal();
                ls_openTypeMoveTo(pos, dx, dy);
                
            } break;
            
            case 22: //hmoveto
            {
                if(args.used == 2)
                {
                    width = font->cff.PrivateDict.nominalWidthX + PullVal();
                    
                    __printIndent(__debug_indentation);
                    ls_printf("width %d\n", width);
                }
                
                ls_openTypeMoveTo(pos, PullVal(), 0);
            } break;
            
            case 23: //vstemhm
            {
                __maybePullWidth();
                
                s32 yA = 0;
                s32 yB = 0;
                
                __printIndent(__debug_indentation);
                //while(args.bot <= args.top)
                while(args.count > 0)
                {
                    yA = PullVal();
                    yB = PullVal();
                    numHints += 1;
                    
                    ls_printf("[%d %d] ", yA, yB);
                }
                
                ls_printf("vstemhm\n");
            } break;
            
            case 30: //vhcurveto
            { ls_openTypeCurveTo(&args, pos, (u8 *)outBuf, w, h, TRUE);  } break;
            
            case 31: //hvcurveto
            { ls_openTypeCurveTo(&args, pos, (u8 *)outBuf, w, h, FALSE); } break;
            
            default:
            {
                ls_printf("Unhandled operator in Charstring: %d\n", oneByte);
                Assert(FALSE);
            } break;
        }
        
        if(oneByte == 12) 
        {
            u8 twoByte = *At; At += 1;
            
            switch(twoByte)
            {
                default:
                {
                    ls_printf("Unhandled operator in Charstring: %d %d\n", oneByte, twoByte);
                    Assert(FALSE);
                } break;
            }
        }
        
        //Assert(args.count == 0);
        if(args.count == 0) { ls_stackClear(&args); }
    }
    
#undef PullVal
}




static
void OpenType_readCMAPTable(OpenType_Font *font, u8 *c)
{
    OpenType_CMAP *cmap = &font->cmap;
    u8 *At = c;
    
    cmap->version   = GetByteSwap16(At);
    cmap->numTables = GetByteSwap16(At);
    
    //TODO: Can we make this a fixed size array? Maybe 256 big or something?
    //  I feel like it would be big only for collection files, rather than single font files.
    //  But i don't know for certain.
    cmap->records   = (OpenType_CMAP::EncodingRecord *)ls_alloc(sizeof(OpenType_CMAP::EncodingRecord) * cmap->numTables);
    
    s32 unicodeTableIdx = -1;
    for(u32 i = 0; i < cmap->numTables; i++)
    {
        cmap->records[i].platformID = GetByteSwap16(At);
        cmap->records[i].encodingID = GetByteSwap16(At);
        cmap->records[i].offsetFromCMAPBegin = GetByteSwap32(At);
        
        if(cmap->records[i].platformID == 0)
        {
            //NOTE: Found Unicode Encoding
            unicodeTableIdx = i;
        }
    }
    
    if(unicodeTableIdx != -1)
    {
        //Fill Table
        At = c + cmap->records[unicodeTableIdx].offsetFromCMAPBegin;
        u8 *Begin = At;
        
        cmap->format = GetByteSwap16(At);
        
        switch(cmap->format)
        {
            //TODO: Add a way to return that we do not support this format.
            case CMAP_FORMAT_UNICODE_1: Assert(FALSE); break; //NOTE: DEPRECATED
            
            case CMAP_FORMAT_UNICODE_2_FULL:
            {
                cmap->length        = GetByteSwap16(At);
                cmap->language      = GetByteSwap16(At);
                cmap->segCountX2    = GetByteSwap16(At);
                cmap->searchRange   = GetByteSwap16(At);
                cmap->entrySelector = GetByteSwap16(At);
                cmap->rangeShift    = GetByteSwap16(At);
                
                u16 segCount   = cmap->segCountX2 / 2;
                cmap->endCode    = (u16 *)ls_alloc(sizeof(u16) * segCount);
                cmap->startCode  = (u16 *)ls_alloc(sizeof(u16) * segCount);
                cmap->idDelta    = (s16 *)ls_alloc(sizeof(s16) * segCount);
                cmap->idRangeOff = (u16 *)ls_alloc(sizeof(u16) * segCount);
                
                for(u32 i = 0; i < segCount; i++)
                {
                    cmap->endCode[i]   = GetByteSwap16(At);
                }
                
                //NOTE: Skip reserved
                At += sizeof(u16);
                
                for(u32 i = 0; i < segCount; i++)
                {
                    cmap->startCode[i]  = GetByteSwap16(At);
                }
                
                for(u32 i = 0; i < segCount; i++)
                {
                    cmap->idDelta[i]    = GetByteSwapS16(At);
                }
                
                for(u32 i = 0; i < segCount; i++)
                {
                    cmap->idRangeOff[i] = GetByteSwap16(At);
                }
                
                // NOTE: Total length of subtable, minus everything that's not in the glyphIDArr.
                //       This gives the total number of bytes in the glyphIDArr.
                //       Divide that by 2 to obtain the number of 16bit words.
                u32 numOfGlyphIDs = (cmap->length - (u32)(At - Begin)) / 2;
                cmap->glyphIDArr = (u16 *)ls_alloc(sizeof(u16) * numOfGlyphIDs);
                for(u32 i = 0; i < numOfGlyphIDs; i++)
                {
                    cmap->glyphIDArr[i]    = GetByteSwap16(At);
                }
                
            } break;
            
            case CMAP_FORMAT_UNICODE_FULL_13:
            {
                //TODO: Implement this.
                Assert(FALSE);
            } break;
            
            default: Assert(FALSE); break;
        }
    }
}

static
void readCFFTableIndex(OpenType_CFF::Index *I, u8 **data)
{
    //const size_t offsByteSize = sizeof(OpenType_CFF::Index::off);
    
    u32 dataLen = 0;
    u32 offsNum = 0;
    u8 *At = *data;
    
    I->count = GetByteSwap16(At);
    
    //TODO:NOTE: I believe this works for every Index??
    //NOTE: Isn't setting data to At a bug here? Why isn't it?
    if(I->count == 0) { *data = At; /*I THINK IT'S A BUG!!!*/ return; }
    
    //I->offSize = GetByte(At);
    u32 offSize = GetByte(At);
    Assert(offSize >= 1 && offSize <= 4);
    
    offsNum = I->count + 1;
    //I->offsets = (OpenType_CFF::Index::off *)ls_alloc(offsByteSize*offsNum);
    I->offsets = (u32 *)ls_alloc(sizeof(u32)*offsNum);
    
    for(u32 idx = 0; idx < offsNum; idx++)
    {
        switch(offSize)
        {
            case 1: I->offsets[idx] = GetByte(At);       break;
            case 2: I->offsets[idx] = GetByteSwap16(At); break;
            case 4: I->offsets[idx] = GetByteSwap32(At); break;
        }
    }
    
    /*
    //NOTE: I->offsets[0] is ALWAYS == 1
    switch(I->offSize)
    {
        case 1: dataLen = I->offsets[I->count].o8  - I->offsets[0].o8;  break;
        case 2: dataLen = I->offsets[I->count].o16 - I->offsets[0].o16; break;
        case 4: dataLen = I->offsets[I->count].o32 - I->offsets[0].o32; break;
    }
    */
    dataLen = I->offsets[I->count] - I->offsets[0];
    I->data = (u8 *)ls_alloc(sizeof(u8)*dataLen);
    I->dataLen = dataLen;
    ls_memcpy(At, I->data, dataLen); At += dataLen;
    
    
    //NOTE: 2 Byte Count, 1 Byte OffSize, offsets size, data size
    u32 theoreticalSize = 2 + 1 + (offSize * (I->count + 1)) + dataLen;
    
    Assert((At - *data) == theoreticalSize);
    
    *data = At;
    return;
}

static
u32 getIntDictOperand(s8 *output, u8 **data)
{
    u8 *dictData = *data;
    u8 b0 = *dictData; dictData++;
    u32 opLen = 0;
    
    if (b0 >= 32 && b0 <= 246)
    {
        //Size 1
        s8 v = (s8)(b0 - 139);
        Assert((v >= -107) && (v <= 107));
        
        output[0] = v;
        opLen = 1;
    }
    else if(b0 >= 247 && b0 <= 250)
    {
        //Size 2 positive
        u8 b1 = *dictData; dictData++;
        s16 v = (s16)((b0-247)*256+b1+108);
        Assert((v >= 108) && (v <= 1131));
        
        *(s16 *)output = v;
        opLen = 2;
    }
    else if(b0 >= 251 && b0 <= 254)
    {
        //Size 2 negative
        u8 b1 = *dictData; dictData++;
        s16 v = s16(-(b0-251)*256-b1-108);
        Assert((v >= -1131) && (v <= -108));
        
        *(s16 *)output = v;
        opLen = 2;
    }
    else if(b0 == 28)
    {
        //Size 3
        u8 b1 = *dictData; dictData++;
        u8 b2 = *dictData; dictData++;
        s16 v = s16((b1<<8) | b2);
        Assert((v >= -32768) && (v <= 32767));
        
        *(s16 *)output = v;
        opLen = 2;
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
        opLen = 4;
    }
    
    *data = dictData;
    return opLen;
}

static
u32 getFloatDictOperand(u8 *operand, u8 **dictData)
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
    return operandLen;
}

static
OpenType_DictData readDictData(u8 *data, u32 dataLen) //OpenType_CFF::Index *Dict)
{
    
    auto makeDeltaOrArray = [](s32 **a, u8 opCount, s8 opInt[64][4], u32 lens[64]) {
        *a = (s32 *)ls_alloc(sizeof(s32) * opCount);
        for(u32 i = 0; i < opCount; i++)
        { ls_memcpy(opInt[i], &((*a)[i]), lens[i]); }
    };
    
    u8 *dictData = data;
    u8 *endData = dictData + dataLen;
    
    OpenType_DictData dD = {};
    
    while(dictData <= endData)
    {
        u8 b0 = *dictData;
        
        s8 operandInt[64][4] = {};
        u8 operandFloat[64][8] = {};
        
        u32 intLens[64] = {};
        u32 floatLens[64] = {};
        
        u8 operandCount = 0;
        while(b0 >= 28) //Still getting operands
        {
            if(b0 != 30) 
            { 
                intLens[operandCount] = getIntDictOperand(operandInt[operandCount], &dictData); 
                operandCount += 1; 
            }
            else
            { 
                floatLens[operandCount] = getFloatDictOperand(operandFloat[operandCount], &dictData);
                operandCount += 1;
            }
            
            b0 = *dictData;
        }
        
        u8 op[2] = {};
        op[0] = *dictData; dictData++;
        Assert((op[0] >= 0) && (op[0] <= 21));
        
        switch(op[0])
        {
            case 0: { dD.version = *((u16 *)(operandInt[0])); } continue;
            case 1: { dD.Notice = *((u16 *)(operandInt[0])); } continue;
            case 2: { dD.FullName = *((u16 *)(operandInt[0])); } continue;
            case 3: { dD.FamilyName = *((u16 *)(operandInt[0])); } continue;
            case 4: { dD.Weight = *((u16 *)(operandInt[0])); } continue;
            
            case 5: 
            { 
                makeDeltaOrArray(&dD.FontBBox, operandCount, operandInt, intLens);
                dD.fontBBoxCount = operandCount;
            } continue;
            
            case 6: 
            { 
                makeDeltaOrArray(&dD.BlueValues, operandCount, operandInt, intLens); 
                dD.BlueValuesCount = operandCount;
            } continue;
            case 7: 
            { 
                makeDeltaOrArray(&dD.OtherBlues, operandCount, operandInt, intLens); 
                dD.OtherBluesCount = operandCount;
            } continue;
            case 8: 
            { 
                makeDeltaOrArray(&dD.FamilyBlues, operandCount, operandInt, intLens); 
                dD.FamilyBluesCount = operandCount;
            } continue;
            case 9: 
            { 
                makeDeltaOrArray(&dD.FamilyOtherBlues, operandCount, operandInt, intLens); 
                dD.FamilyOtherCount = operandCount;
            } continue;
            
            case 10: { ls_memcpy(operandInt[0], &dD.StdHW, intLens[0]); } continue;
            case 11: { ls_memcpy(operandInt[0], &dD.StdVW, intLens[0]); } continue;
            
            case 13: { ls_memcpy(operandInt[0], &dD.UniqueID, intLens[0]); } continue;
            case 14: 
            { 
                makeDeltaOrArray(&dD.XUID, operandCount, operandInt, intLens); 
                dD.XUIDCount = operandCount;
            } continue;
            
            //NOTE: Assuming Integers
            case 15: { ls_memcpy(operandInt[0], &dD.charset, intLens[0]); } continue;
            case 16: { ls_memcpy(operandInt[0], &dD.encoding, intLens[0]); } continue;
            case 17: { ls_memcpy(operandInt[0], &dD.CharStrings, intLens[0]); } continue;
            case 18:
            {
                ls_memcpy(operandInt[0], &dD.Private[0], intLens[0]);
                ls_memcpy(operandInt[1], &dD.Private[1], intLens[1]);
            } continue;
            
            
            //TODO: Is this even correct? I think this is wrong.
            case 19: { ls_memcpy(operandInt[0], &dD.Subrs, intLens[0]); } continue;
            
            
            case 20: { ls_memcpy(operandInt[0], &dD.defaultWidthX, intLens[0]); } continue;
            case 21: { ls_memcpy(operandInt[0], &dD.nominalWidthX, intLens[0]); } continue;
            
        }
        Assert(op[0] == 12);
        op[1] = *dictData; dictData++;
        
        switch(op[1])
        {
            case 0: { dD.Copyright = *((u16 *)(operandInt[0])); } continue;
            case 1: { ls_memcpy(operandInt[0], &dD.isFixedPitch, intLens[0]); } continue;
            
            //NOTE: Assuming Float
            case 2: { ls_memcpy(operandFloat[0], &dD.ItalicAngle, floatLens[0]); } continue;
            
            //NOTE: Assuming Int
            case 3: { ls_memcpy(operandInt[0], &dD.UnderlinePosition, intLens[0]); } continue;
            case 4: { ls_memcpy(operandInt[0], &dD.UnderlineThickness, intLens[0]); } continue;
            case 5: { ls_memcpy(operandInt[0], &dD.PaintType, intLens[0]); } continue;
            case 6: { ls_memcpy(operandInt[0], &dD.CharStrings, intLens[0]); } continue;
            
            //NOTE: Assuming Float
            case 7:
            {
                dD.FontMatrix = (f64 *)ls_alloc(sizeof(f64) * operandCount);
                for(u32 i = 0; i < operandCount; i++)
                { ls_memcpy(operandFloat[i], &dD.FontMatrix[i], floatLens[i]); }
            } continue;
            
            //NOTE: Assuming Int
            case 8:  { ls_memcpy(operandInt[0], &dD.StrokeWidth, intLens[0]); } continue;
            
            case 9:  { ls_memcpy(operandFloat[0], &dD.BlueScale, floatLens[0]); } continue;
            case 10: { ls_memcpy(operandInt[0], &dD.BlueShift, intLens[0]); } continue;
            case 11: { ls_memcpy(operandInt[0], &dD.BlueFuzz, intLens[0]); } continue;
            
            case 12: 
            { 
                makeDeltaOrArray(&dD.StemSnapH, operandCount, operandInt, intLens); 
                dD.StemSnapHCount = operandCount;
            } continue;
            case 13: 
            { 
                makeDeltaOrArray(&dD.StemSnapV, operandCount, operandInt, intLens);
                dD.StemSnapVCount = operandCount;
            } continue;
            
            case 14: { ls_memcpy(operandInt[0], &dD.ForceBold, intLens[0]); } continue;
            case 17: { ls_memcpy(operandInt[0], &dD.LanguageGroup, intLens[0]); } continue;
            case 18: { ls_memcpy(operandFloat[0], &dD.ExpansionFactor, floatLens[0]); } continue;
            
            case 19: { ls_memcpy(operandInt[0], &dD.InitialRandomSeed, intLens[0]); } continue;
            
            case 20: { ls_memcpy(operandInt[0], &dD.SyntheticBase, intLens[0]); } continue;
            case 21: { dD.PostScript = *((u16 *)(operandInt[0])); } continue;
            case 22: { dD.BaseFontName = *((u16 *)(operandInt[0])); } continue;
            case 23: 
            { 
                makeDeltaOrArray(&dD.BaseFontBlend, operandCount, operandInt, intLens); 
                dD.BaseFontBlendCount = operandCount;
            } continue;
            
            case 36: { ls_memcpy(operandInt[0], &dD.FDArrayOff, intLens[0]); } continue;
            case 37: { ls_memcpy(operandInt[0], &dD.FDSelectOff, intLens[0]); } continue;
        }
    }
    
    return dD;
}

static
void OpenType_readCFFTable(OpenType_Font *font, u8 *file, u8 *h)
{
    //offset of the CFF table from the beginning of the file
    //const u8 baseCFFOffset = 18728;
    u8 *cffBase = h;
    u8 *At = h;
    
    OpenType_CFF *Res = &font->cff;
    
    // CFF Header
    Res->major       = GetByte(At);
    Res->minor       = GetByte(At);
    Res->hdrSize     = GetByte(At);
    Res->cff_offSize = GetByte(At);
    
    OpenType_CFF::Index *I;
    
    // Name Index
    u32 nameIdxOff = At - file; //TODO Debug Value
    
    I = &Res->Name;
    readCFFTableIndex(I, &At);
    Assert(I->count == 1);   //Name Index in OpenType Fonts should have only 1 Entry!
    
    // Top Dict Index
    u32 TopDictIdxOff = At - file; //18747  //TODO Debug Value
    
    I = &Res->TopDict;
    readCFFTableIndex(I, &At);
    
    //Parse Top Dictionary
    //u32 TopDictOff = Res.TopDict.data - file; //18754
    Res->TopDictData = readDictData(Res->TopDict.data, Res->TopDict.dataLen);
    
    if(Res->Name.count != Res->TopDict.count) //TODO: Make it a Debug Only Assert.
    {
        ls_printf("Name Index and TopDict Index counts in CFF Table don't match. Bad Font?\n");
        Assert(FALSE);
    }
    
    // String Index
    u32 StringIdxOff = At - file;  //TODO Debug Value
    
    I = &Res->String;
    readCFFTableIndex(I, &At);
    
    // Global Subroutines Index
    u32 GSubsOff = At - file; //24779  //TODO Debug Value
    
    I = &Res->GlobalSubr;
    readCFFTableIndex(I, &At);
    
    if(Res->TopDict.data != 0)
    {
        // Charstrings Index NOTE:(Indices are always from beginning of CFF)
        At = cffBase + Res->TopDictData.CharStrings;
        
        I = &Res->Charstrings;
        readCFFTableIndex(I, &At);
        
        
        //Charsets
        At = cffBase + Res->TopDictData.charset;
        Res->set.format = GetByte(At);
        if(Res->set.format == 0)
        {
            
            u32 numGlyphs = Res->Charstrings.count - 1; //NOTE: Ignore null-glyp
            Res->set.glyphs = (u16 *)ls_alloc(sizeof(u16) * numGlyphs);
            
            for(u32 i = 0; i < numGlyphs; i++)
            { Res->set.glyphs[i] = GetByteSwap16(At); }
            
        }
        else if((Res->set.format == 1) || (Res->set.format == 2))
        { 
            ls_printf("Charset format 1/2 not implemented yet\n");
            Assert(FALSE);
        }
        
        //Encodings
        At = cffBase + Res->TopDictData.encoding;
        Res->enc.format = GetByte(At);
        
        if(Res->enc.format == 0x0)
        {
            Res->enc.nCodes = GetByte(At);
            Res->enc.codes = (u8 *)ls_alloc(sizeof(u8) * Res->enc.nCodes);
            
            for(u32 i = 0; i < Res->enc.nCodes; i++) 
            { Res->enc.codes[i] = GetByte(At); }
        }
        else if(Res->enc.format == 0x1) 
        {
            Res->enc.nRanges = GetByte(At);
            if(Res->enc.nRanges != 0)
            {
                Res->enc.ranges  = (OpenType_CFF::Encoding::Range1 *)
                    ls_alloc(sizeof(OpenType_CFF::Encoding::Range1) * Res->enc.nRanges);
                
                for(u32 i = 0; i < Res->enc.nRanges; i++) 
                { 
                    Res->enc.ranges[i].first = GetByte(At);
                    Res->enc.ranges[i].nLeft = GetByte(At);
                }
            }
            
            //NOTE: If there's no encoding it means it's a CID Font
        }
        else if(Res->enc.format == 0b10000000)
        {
            
        }
        
        
        //TODO: How to deal with Private DICT with lenght != 0
        //      This means it has non-default values.
        //Private Data
        At = cffBase + Res->TopDictData.Private[1];
        u32 privateLen = Res->TopDictData.Private[0];
        
        Res->PrivateDict = readDictData(At, privateLen);
        
        if(Res->PrivateDict.Subrs)
        {
            At = cffBase + Res->TopDictData.Private[1] + Res->PrivateDict.Subrs;
            
            I = &Res->LocalSubr;
            readCFFTableIndex(I, &At);
        }
        
    }
    
};

OpenType_Font ls_openTypeLoadFont(string filePath)
{
    OpenType_Font Font = {};
    
    char *file = 0;
    
    ls_strNullTerminate(&filePath);
    u64 fileSize = ls_readFile(filePath.data, &file, 0);
    
    u8 *At = (u8 *)file;
    OpenType_OffTable t = OpenType_readOffTable(At);
    At += sizeof(OpenType_OffTable);
    
    u8 *head = 0, *maxp = 0, *cmap = 0, *hhea = 0, *hmtx = 0;
    u8 *kern = 0, *gpos = 0, *name = 0, *os2 = 0, *post = 0;
    u8 *cff = 0;
    
    for(u32 tableIdx = 0; tableIdx < t.numTables; tableIdx++)
    {
        //recs.push(OpenType_readTableRecord(At));
        u32 tableTag = ByteSwap32(*((u32 *)At));
        u32 tableOff = ByteSwap32(*((u32 *)(At + 8)));
        
        switch(tableTag)
        {
            case OT_TAG_HEAD: head = (u8 *)file + tableOff; break;
            case OT_TAG_MAXP: maxp = (u8 *)file + tableOff; break;
            case OT_TAG_CMAP: cmap = (u8 *)file + tableOff; break;
            case OT_TAG_HHEA: hhea = (u8 *)file + tableOff; break;
            case OT_TAG_HMTX: hmtx = (u8 *)file + tableOff; break;
            case OT_TAG_KERN: kern = (u8 *)file + tableOff; break;
            case OT_TAG_NAME: name = (u8 *)file + tableOff; break;
            case OT_TAG_OS_2: os2  = (u8 *)file + tableOff; break;
            case OT_TAG_POST: post = (u8 *)file + tableOff; break;
            
            case OT_TAG_CFF:  cff  = (u8 *)file + tableOff; break;
            
            
            case OT_TAG_GPOS: gpos = (u8 *)file + tableOff; break;
        }
        At += sizeof(OpenType_TableRecord);
    }
    
    //NOTE: Required Tables
    OpenType_readHEADTable(&Font, head);
    OpenType_readMAXPTable(&Font, maxp);
    OpenType_readCMAPTable(&Font, cmap);
    OpenType_readHHEATable(&Font, hhea);
    OpenType_readHMTXTable(&Font, hmtx); 
    OpenType_readNAMETable(&Font, name);
    OpenType_readOS_2Table(&Font, os2);
    OpenType_readPOSTTable(&Font, post);
    
    OpenType_readCFFTable(&Font, (u8 *)file, cff);
    
    OpenType_readKERNTable(&Font, kern); 
    //OpenType_readGPOSTable(&Font, gpos); 
    
    
    //NOTE:TODO: Debugging
    return Font;
#if 0
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
#endif
    ls_free(file);
}

#undef GetByte
#undef GetByteSwap16
#undef GetByteSwapS16
#undef GetByteSwap32
#undef GetByteSwapS32
#undef GetByteSwap64
#undef GetByteSwapS64

#endif //End of Implementation