#pragma once

enum UITextBoxAlignment : u8
{
    UI_TB_ALIGN_LEFT = 0,
    UI_TB_ALIGN_RIGHT,
    UI_TB_ALIGN_CENTER
};

struct UITextBox
{
    //NOTE: callback1 -> preInput; callback2 -> postInput
    UIWidget_Base;
    
    UITextBoxAlignment align;
    
    utf32 text;
    u32 maxLen; // maxLen == 0 means it is ignored. No max Len.
    
    b32 isSingleLine;
    b32 isReadonly;
    
    s32 lineCount;
    s32 currLineBeginIdx;
    
    u32 dtCaret;
    b32 isCaretOn;
    s32 caretIndex;
    s32 caretLineIdx;
    
    //NOTE:TODO: Call this viewMinIdx;
    s32 viewBeginIdx;
    
    s32 selectBeginLine;
    s32 selectEndLine;
    s32 selectBeginIdx;
    s32 selectEndIdx;
    b32 isSelecting;
};


void ls_uiTextBoxClear(UIContext *c, UITextBox *box);
void ls_uiTextBoxSet(UIContext *c, UITextBox *box, const char32_t *s);
void ls_uiTextBoxSet(UIContext *c, UITextBox *box, utf32 s);
void ls_uiTextBoxInit(UIContext *c, UITextBox *box, s32 initialCap, s32 maxLen, b32 singleLine, 
                      b32 readOnly, UICallback preInput, UICallback postInput);
b32  ls_uiTextBox(UIContext *c, UITextBox *box, s32 xPos, s32 yPos, s32 w, s32 h, s32 zLayer);
b32  ls_uiTextBox(UIContext *c, UITextBox *box, UIPos pos, s32 zLayer);
//b32  ls_uiTextBox(UIContext *c, UITextBox *box, f32 x, f32 y, f32 relW, f32 relH, s32 zLayer);
