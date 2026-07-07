#include "lsUI.textboxes.h"

void ls_uiTextBoxClear(UIContext *c, UITextBox *box)
{
    Arena prev = ls_arenaUse(c->widgetArena);
    
    AssertMsg(c, "Context pointer was null");
    
    ls_utf32Clear(&box->text);
    
    box->isReadonly       = FALSE;
    box->caretIndex       = 0;
    box->caretLineIdx     = 0;
    box->lineCount        = 1;
    box->currLineBeginIdx = 0;
    
    box->selectBeginLine  = 0;
    box->selectEndLine    = 0;
    box->selectBeginIdx   = 0;
    box->selectEndIdx     = 0;
    box->isSelecting      = FALSE;
    box->viewBeginIdx     = 0;
    
    ls_arenaUse(prev);
}

//TODO: Now that viewEndIdx is deprecated these functions are a lot less useful
void ls_uiTextBoxSet(UIContext *c, UITextBox *box, const char32_t *s)
{
    Arena prev = ls_arenaUse(c->widgetArena);
    ls_utf32FromUTF32_t(&box->text, s);
    ls_arenaUse(prev);
}

void ls_uiTextBoxSet(UIContext *c, UITextBox *box, utf32 s)
{
    Arena prev = ls_arenaUse(c->widgetArena);
    ls_utf32Set(&box->text, s);
    ls_arenaUse(prev);
}

void ls_uiTextBoxInit(UIContext *c, UITextBox *box, s32 initialCap, s32 maxLen = 0, b32 singleLine = TRUE,
                      b32 readOnly = FALSE, UICallback preInput = NULL, UICallback postInput = NULL)
{
    Arena prev = ls_arenaUse(c->widgetArena);
    box->text         = ls_utf32Alloc(initialCap);
    box->maxLen       = maxLen;
    box->isSingleLine = singleLine;
    box->isReadonly   = readOnly;
    box->align        = UI_TB_ALIGN_LEFT;
    
    box->callback1    = preInput;
    box->callback2    = postInput;
    ls_arenaUse(prev);
}


//TODO: This is only used in a lambda inside ls_uiTextBox()
//      So, maybe either find a way to remove this, or just fit it inside ls_uiTextBox() instead!
s32 ls_uiGlyphStringFit(UIContext *c, UIFont *font, utf32 text, s32 maxLen)
{
    AssertMsg(c, "Context is null\n");
    LogMsg(font, "Passed font is null\n");
    if(!font) { return 0; }
    
    s32 totalLen = 0;
    for(s32 i = text.len-1; i > 0; i--)
    {
        u32 codepoint = text.data[i];
        AssertMsgF(codepoint <= c->fontGroup.maxCodepoint, "GlyphIndex %d OutOfBounds\n", codepoint);
        
        if(font->isAtlas)
        {
            //TODO: Annoying c->currPixelHeight
            f64 scaling = (f64)c->currPixelHeight / (f64)font->pixelHeight;
            UIAtlasMapEntry *map = ls_uiGetAtlasMapEntry(c, font, codepoint);
            totalLen += map->xAdv*scaling;
        }
        else
        {
            UIGlyph *currGlyph = &font->glyph[codepoint];
            
            s32 kernAdvance = 0;
            if(i > 0) { kernAdvance = ls_uiGetKernAdvance(font, text.data[i-1], text.data[i]); }
            
            totalLen += (currGlyph->xAdv + kernAdvance);
        }
        
        if(totalLen >= maxLen) { return i; }
    }
    
    return 0;
}

//TODO: Text Alignment
//TODO: NonLethal display (like all maxLen numerical displays) is asymmetrical in the value range
//      it can represent.
//
//      I.E.  A maxLen = 4 textBox can represent: [-999, 9999]
//            Instead of the more correct:        [-999, 999]
b32 ls_uiTextBox(UIContext *c, UITextBox *box, s32 xPos, s32 yPos, s32 w, s32 h, s32 zLayer = 0)
{
    Arena prev = ls_arenaUse(c->widgetArena);
    
    Input *UserInput = &c->currWindow->UserInput;
    b32 inputUse = FALSE;
    
    if(LeftClickIn(xPos, yPos, w, h-1) && ls_uiHasCapture(c, 0)) {
        ls_uiFocusChangeSameFrame(c, (u64 *)box);
        box->isCaretOn = TRUE;
    }
    
    //TODOHACKHACK
    if(box->lineCount == 0) box->lineCount = 1;
    //TODOHACKHACK
    
    //TODO: Hardcoded values.
    const s32 horzOff      = 12;
    const s32 viewAddWidth = w - 2*horzOff;
    const s32 maxIndexDiff = c->currPixelHeight;
    
    auto lineBeginIdx = [box](s32 index) -> u32 {
        if(index <= 0) { 
            box->viewBeginIdx = 0;
            
            //TODONOTE: Very wrong.
            //if(box->text.data[0] == (char32_t)'\n') { return 1; }
            return 0;
        }
        
        u32 beginOffset    = ls_utf32RightFind(box->text, index, (char32_t)'\n');
        
        s32 realOffset = beginOffset+1;
        if(beginOffset == -1) { realOffset = 0; }
        return realOffset;
    };
    
    auto setIndices = [c, box, viewAddWidth, lineBeginIdx](s32 index) -> u32 {
        
        u32 realOffset    = lineBeginIdx(index);
        s32 lineLength    = index-realOffset;
        utf32 currLine    = { box->text.data + realOffset, lineLength, lineLength };
        u32 maxBeginIndex = ls_uiGlyphStringFit(c, c->currFont, currLine, viewAddWidth);
        
        box->viewBeginIdx = maxBeginIndex;
        
        return realOffset;
    };
    
    auto handleSelection = [UserInput, box](s32 direction, s32 prevCI, s32 prevCLI, s32 currCI, s32 currCLI) {
        
        AssertMsg((direction == -1) || (direction == 1) || (direction == -2) || (direction == 2) ||
                  (direction == -3) || (direction == 3), "Invalid direction passed to handleSelection\n");
        
        if(KeyHeld(keyMap::Shift))
        {
            if(!box->isSelecting) 
            { 
                box->isSelecting = TRUE;
                
                switch(direction)
                {
                    case -1:
                    case  1: //NOTE: Left/Right Arrow
                    {
                        box->selectBeginLine = prevCLI;
                        box->selectEndLine   = prevCLI;
                        
                        if(direction == -1)
                        {
                            box->selectBeginLine = currCLI;
                            box->selectBeginIdx  = currCI;
                            box->selectEndIdx    = prevCI;
                        }
                        else
                        {
                            box->selectEndLine   = currCLI;
                            box->selectBeginIdx  = prevCI;
                            box->selectEndIdx    = currCI;
                        }
                    } break;
                    
                    
                    case -2: //NOTE: Home
                    {
                        if(prevCI == 0) { box->isSelecting = FALSE; break; }
                        
                        box->selectBeginLine = 0;
                        box->selectEndLine   = prevCLI;
                        box->selectBeginIdx  = 0;
                        box->selectEndIdx    = prevCI;
                    } break;
                    
                    case  2: //NOTE: End
                    {
                        if(prevCI >= box->text.len) { box->isSelecting = FALSE; break; }
                        
                        box->selectBeginLine = prevCLI;
                        box->selectEndLine   = currCLI; //box->lineCount; TODO: which is better, more clear?
                        box->selectBeginIdx  = prevCI;
                        box->selectEndIdx    = currCI; //box->text.len; TODO: which is better, more clear?
                    } break;
                    
                    case -3: //NOTE: Up Arrow
                    { 
                        
                    } break;
                    
                    case 3: //NOTE: Down Arrow
                    { 
                        
                    } break;
                }
            }
            else
            {
                switch(direction)
                {
                    case -1: //NOTE: Left
                    case  1: //NOTE: Right
                    {
                        if(prevCI == box->selectBeginIdx)
                        { 
                            box->selectBeginIdx += direction;
                            box->selectBeginLine = currCLI;
                            /*
                            if(box->text.data[box->caretIndex + direction] == (char32_t)'\n')
                            { box->selectBeginLine += direction;}*/
                        }
                        else if(prevCI == box->selectEndIdx)
                        { 
                            box->selectEndIdx += direction;
                            box->selectEndLine = currCLI;
                            /*
                            if(box->text.data[box->caretIndex] == (char32_t)'\n') { box->selectEndLine += direction; }
*/
                        }
                        else
                        { AssertMsg(FALSE, "Arrow Left Or Right -> Caret is not aligned with select anymore\n"); }
                        
                    } break;
                    
                    case -2: //NOTE: Home
                    {
                        if(prevCI == box->selectBeginIdx)
                        { box->selectBeginIdx = 0; box->selectBeginLine = 0; }
                        else if(prevCI == box->selectEndIdx)
                        { 
                            box->selectEndIdx    = box->selectBeginIdx; box->selectBeginIdx = 0; 
                            box->selectBeginLine = 0; box->selectEndLine = prevCLI; //box->caretLineIdx;
                        }
                        else
                        { AssertMsg(FALSE, "Home -> Caret is not aligned with select anymore\n"); }
                        
                    } break;
                    
                    case  2: //NOTE: End
                    {
                        if(prevCI == box->selectBeginIdx)
                        { 
                            box->selectBeginIdx  = box->selectEndIdx; box->selectEndIdx  = currCI;//box->text.len; 
                            box->selectBeginLine = prevCLI;           box->selectEndLine = currCLI;//box->lineCount;
                        }
                        else if(prevCI == box->selectEndIdx)
                        { 
                            box->selectEndIdx  = currCI;  //box->text.len; 
                            box->selectEndLine = currCLI; //box->lineCount;
                        }
                        else
                        { AssertMsg(FALSE, "End -> Caret is not aligned with select anymore\n"); }
                        
                    } break;
                }
                
                if(box->selectBeginIdx == box->selectEndIdx) 
                { box->isSelecting = FALSE; }
            }
        }
        else 
        { 
            if(box->isSelecting)
            { 
                box->isSelecting     = FALSE;
                box->selectEndIdx    = 0; box->selectBeginIdx  = 0; 
                box->selectBeginLine = 0; box->selectEndLine   = 0;
            }
        }
    };
    
    auto removeSelection = [=]() {
        box->lineCount   -= (box->selectEndLine - box->selectBeginLine);
        box->caretIndex   = box->selectBeginIdx;
        box->caretLineIdx = box->selectBeginLine;
        box->isSelecting  = FALSE;
        
        ls_utf32RmSubstr(&box->text, box->selectBeginIdx, box->selectEndIdx-1);
        box->currLineBeginIdx = setIndices(box->caretIndex);
    };
    
    if(ls_uiInFocus(c, box))
    {
        s32 prevCI  = box->caretIndex;
        s32 prevCLI = box->caretLineIdx;
        
        //NOTE: box->preInput
        if(box->callback1)
        { inputUse |= box->callback1(c, box->callback1Data); }
        
        //NOTE: Unset Focus on "Enter" press when textBox is single line.
        if(HasPrintableKey() && (GetPrintableKey() == (char32_t)'\n') &&
           ((box->isSingleLine == TRUE) || box->isReadonly == TRUE))
        { ls_uiFocusChange(c, 0); }
        
        //NOTE: Draw characters. (box->maxLen == 0 means there's no max len)
        else if(HasPrintableKey() && (box->text.len < box->maxLen || box->maxLen == 0) && (box->isReadonly == FALSE))
        {
            if(box->isSelecting) { removeSelection(); }
            
            if(box->caretIndex == box->text.len) { ls_utf32AppendChar(&box->text, GetPrintableKey()); }
            else { ls_utf32InsertChar(&box->text, GetPrintableKey(), box->caretIndex); }
            
            //NOTE We changed line, so we reset the view (Which is always relative caret curret line)
            if(GetPrintableKey() == (char32_t)'\n') {
                box->lineCount        += 1;
                box->caretLineIdx     += 1;
                box->currLineBeginIdx  = box->caretIndex+1;
            }
            
            box->caretIndex += 1;
            box->isCaretOn = TRUE; box->dtCaret = 0;
            
            setIndices(box->caretIndex-1);
            
            inputUse = TRUE;
        }
        
        else if(KeyPressOrRepeat(keyMap::Backspace) && box->text.len > 0 && box->caretIndex >= 0
                && (box->isReadonly == FALSE) ) 
        {
            if(box->caretIndex == 0 && !box->isSelecting) { goto goto_skip_to_post_input; }
            
            if(box->isSelecting) 
            { 
                removeSelection();
            }
            else
            {
                if(box->text.data[box->caretIndex-1] == (char32_t)'\n')
                { 
                    u32 beginOffset = setIndices(box->caretIndex-2);
                    
                    box->lineCount        -= 1;
                    box->caretLineIdx     -= 1;
                    box->currLineBeginIdx  = beginOffset;
                    
                }
                else { setIndices(box->caretIndex-1); }
                
                if(box->caretIndex == box->text.len) { ls_utf32TrimRight(&box->text, 1); }
                else { ls_utf32RmIdx(&box->text, box->caretIndex-1); }
                box->caretIndex -= 1;
            }
            
            box->isCaretOn = TRUE; box->dtCaret = 0;
            inputUse = TRUE;
        }
        
        else if(KeyPressOrRepeat(keyMap::Delete) && (box->text.len > 0) && (box->caretIndex <= box->text.len)
                && (box->isReadonly == FALSE) )
        {
            if(box->caretIndex == box->text.len && !box->isSelecting) { goto goto_skip_to_post_input; }
            
            if(box->isSelecting) 
            { 
                removeSelection();
            }
            else
            {
                b32 isCR = (box->text.data[box->caretIndex] == (char32_t)'\n');
                
                if(box->caretIndex == box->text.len-1) { ls_utf32TrimRight(&box->text, 1); }
                else { ls_utf32RmIdx(&box->text, box->caretIndex); }
                
                if(isCR) { box->lineCount -= 1; }
            }
            
            box->isCaretOn = TRUE; box->dtCaret = 0;
            inputUse = TRUE;
        }
        
        else if(KeyPressOrRepeat(keyMap::LArrow) && box->caretIndex > 0)
        {
            box->isCaretOn      = TRUE;
            box->dtCaret        = 0;
            box->caretIndex    -= 1;
            
            if(box->text.data[box->caretIndex] == (char32_t)'\n')
            {
                if(box->caretIndex == 0)
                {
                    box->caretLineIdx     = 0;
                    box->currLineBeginIdx = 0;
                    box->viewBeginIdx     = 0;
                }
                else
                {
                    s32 newLineBeginIdx = setIndices(box->caretIndex-1);
                    if(newLineBeginIdx < box->currLineBeginIdx)
                    {
                        box->caretLineIdx    -= 1;
                        box->currLineBeginIdx = newLineBeginIdx;
                    }
                }
            }
            else
            { 
                s32 lineIdx = box->caretIndex - box->currLineBeginIdx;
                if(lineIdx < box->viewBeginIdx) { box->viewBeginIdx -= 1; }
            }
            
            handleSelection(-1, prevCI, prevCLI, box->caretIndex, box->caretLineIdx);
        }
        
        else if(KeyPressOrRepeat(keyMap::RArrow) && box->caretIndex < box->text.len)
        { 
            if(box->text.data[box->caretIndex] == (char32_t)'\n')
            { 
                box->caretLineIdx    += 1;
                box->currLineBeginIdx = box->caretIndex+1;
                box->viewBeginIdx     = 0;
            }
            else
            { 
                s32 lineIdx = box->caretIndex+1 - box->currLineBeginIdx;
                if(lineIdx - box->viewBeginIdx > maxIndexDiff) { box->viewBeginIdx += 1; }
            }
            
            box->isCaretOn      = TRUE;
            box->dtCaret        = 0;
            box->caretIndex    += 1;
            
            handleSelection(1, prevCI, prevCLI, box->caretIndex, box->caretLineIdx);
        }
        
        else if(KeyPressOrRepeat(keyMap::UArrow) && box->caretLineIdx > 0)
        {
            box->isCaretOn = TRUE; box->dtCaret = 0;
            
            s32 oldCaretIndex = box->caretIndex;
            s32 lineRelativeCaretIndex = box->caretIndex - box->currLineBeginIdx;
            s32 oldLineBeginIdx = box->currLineBeginIdx;
            
            box->caretLineIdx    -= 1;
            box->currLineBeginIdx = lineBeginIdx(oldLineBeginIdx - 2);
            
            s32 newLineLen = oldLineBeginIdx-1 - box->currLineBeginIdx;
            
            if(lineRelativeCaretIndex > newLineLen)
            { box->caretIndex = newLineLen + box->currLineBeginIdx; }
            else
            { box->caretIndex = lineRelativeCaretIndex + box->currLineBeginIdx; }
            
            s32 lineIdx = box->caretIndex - box->currLineBeginIdx;
            s32 diff = lineIdx - box->viewBeginIdx;
            if(diff > maxIndexDiff) { box->viewBeginIdx = diff; }
            else                    { box->viewBeginIdx = 0; }
            
            //TODO: Handle Selection is a mess.
            //TODO: Move to the handleSelection lambda...
            if(KeyHeld(keyMap::Shift))
            {
                if(!box->isSelecting)
                {
                    box->isSelecting     = TRUE;
                    box->selectBeginLine = box->caretLineIdx;
                    box->selectEndLine   = box->caretLineIdx+1;
                    box->selectBeginIdx  = box->caretIndex;
                    box->selectEndIdx    = oldCaretIndex;
                }
                else
                {
                    if(oldCaretIndex == box->selectBeginIdx)
                    {
                        box->selectBeginLine -= 1;
                        box->selectBeginIdx   = box->caretIndex;
                    }
                    else if(oldCaretIndex == box->selectEndIdx)
                    {
                        if(box->selectEndLine > box->selectBeginLine) { box->selectEndLine   -= 1; }
                        else                                          { box->selectBeginLine -= 1; }
                        
                        if(box->caretIndex > box->selectBeginIdx)
                        { box->selectEndIdx = box->caretIndex; }
                        else
                        {
                            box->selectEndIdx   = box->selectBeginIdx;
                            box->selectBeginIdx = box->caretIndex;
                        }
                    }
                    else { AssertMsg(FALSE, "Arrow Up -> Caret is not aligned with select anymore\n"); }
                }
            }
            else
            {
                if(box->isSelecting)
                { 
                    box->isSelecting     = FALSE;
                    box->selectEndIdx    = 0; box->selectBeginIdx  = 0; 
                    box->selectBeginLine = 0; box->selectEndLine   = 0;
                }
            }
        }
        
        else if(KeyPressOrRepeat(keyMap::DArrow) && box->caretLineIdx < box->lineCount-1)
        {
            //TODO: handleSelection()
            
            box->isCaretOn = TRUE; box->dtCaret = 0;
            
            s32 oldCaretIndex = box->caretIndex;
            s32 lineRelativeCaretIndex = box->caretIndex - box->currLineBeginIdx;
            
            box->caretLineIdx    += 1;
            box->currLineBeginIdx = ls_utf32LeftFind(box->text, box->caretIndex, (char32_t)'\n') + 1;
            
            AssertMsg(box->currLineBeginIdx != -1, "No \\n Found, but there HAVE to be more lines ??");
            
            s32 nextLineIdx = ls_utf32LeftFind(box->text, box->currLineBeginIdx, (char32_t)'\n');
            s32 nextLineLen = nextLineIdx - box->currLineBeginIdx;
            
            if(nextLineIdx != -1)
            {
                if(lineRelativeCaretIndex > nextLineLen)
                { box->caretIndex = box->currLineBeginIdx + nextLineLen; }
                else
                { box->caretIndex = lineRelativeCaretIndex + box->currLineBeginIdx; }
            }
            else
            {
                if(box->currLineBeginIdx + lineRelativeCaretIndex > box->text.len)
                { box->caretIndex = box->text.len; }
                else
                { box->caretIndex = lineRelativeCaretIndex + box->currLineBeginIdx; }
            }
            
            s32 lineIdx = box->caretIndex - box->currLineBeginIdx;
            s32 diff = lineIdx - box->viewBeginIdx;
            if(diff > maxIndexDiff) { box->viewBeginIdx = diff; }
            else                    { box->viewBeginIdx = 0; }
            
            //TODO: Handle Selection is a mess.
            //TODO: Move to the handleSelection lambda...
            if(KeyHeld(keyMap::Shift))
            {
                if(!box->isSelecting)
                {
                    box->isSelecting     = TRUE;
                    box->selectBeginLine = box->caretLineIdx-1;
                    box->selectEndLine   = box->caretLineIdx;
                    box->selectBeginIdx  = oldCaretIndex;
                    box->selectEndIdx    = box->caretIndex;
                }
                else
                {
                    if(oldCaretIndex == box->selectBeginIdx)
                    {
                        if(box->selectBeginLine < box->selectEndLine) { box->selectBeginLine += 1; }
                        else                                          { box->selectEndLine   += 1; }
                        
                        if(box->caretIndex <= box->selectEndIdx)
                        { box->selectBeginIdx = box->caretIndex; }
                        else
                        { 
                            box->selectBeginIdx = box->selectEndIdx;
                            box->selectEndIdx   = box->caretIndex;
                        }
                    }
                    else if(oldCaretIndex == box->selectEndIdx)
                    {
                        box->selectEndLine += 1;
                        box->selectEndIdx   = box->caretIndex;
                    }
                    else { AssertMsg(FALSE, "Arrow Down -> Caret is not aligned with select anymore\n"); }
                }
            }
            else
            {
                if(box->isSelecting)
                { 
                    box->isSelecting     = FALSE;
                    box->selectEndIdx    = 0; box->selectBeginIdx  = 0; 
                    box->selectBeginLine = 0; box->selectEndLine   = 0;
                }
            }
        }
        
        else if(KeyPress(keyMap::Home))
        { 
            box->isCaretOn = TRUE; box->dtCaret = 0;
            box->caretIndex       = 0;
            box->currLineBeginIdx = 0;
            box->caretLineIdx     = 0;
            
            setIndices(0);
            handleSelection(-2, prevCI, prevCLI, box->caretIndex, box->caretLineIdx);
        }
        
        else if(KeyPress(keyMap::End))
        {
            box->isCaretOn    = TRUE; box->dtCaret = 0; 
            box->caretIndex   = box->text.len;
            box->caretLineIdx = box->lineCount-1;
            
            box->currLineBeginIdx = setIndices(box->caretIndex-1);
            
            handleSelection(2, prevCI, prevCLI, box->caretIndex, box->caretLineIdx);
        }
        
        else if(KeyHeld(keyMap::Control) && KeyPress(keyMap::A))
        {
            box->isSelecting     = TRUE;
            box->selectBeginIdx  = 0;
            box->selectEndIdx    = box->text.len;
            box->selectBeginLine = 0;
            box->selectEndLine   = box->lineCount;
        }
        
        else if(KeyHeld(keyMap::Control) && KeyPress(keyMap::C) && box->isSelecting)
        { 
            u32 *data = box->text.data + box->selectBeginIdx;;
            u32 selectionLen = box->selectEndIdx - box->selectBeginIdx;
            
            SetClipboard(data, selectionLen);
        }
        
        else if(KeyHeld(keyMap::Control) && KeyPress(keyMap::V) && (box->isReadonly == FALSE))
        {
            if(box->isSelecting) { removeSelection(); }
            
            u32 buff[4096] = {};
            u32 copiedLen = GetClipboard(buff, 4096);
            
            s32 realCopyLen = copiedLen;
            
            //NOTE: maxLen == 0 means there's no max len.
            if(box->maxLen != 0) 
            {
                if(box->text.len + copiedLen > box->maxLen) {
                    if(box->text.len < box->maxLen) { realCopyLen = box->maxLen - box->text.len; }
                    else { realCopyLen = 0; }
                }
            }
            
            u32 addedLines = ls_utf32CountOccurrences({buff, realCopyLen, realCopyLen}, (u32)'\n');
            
            //NOTE: Skip if box is single line and you're trying to paste a multiline text.
            if(addedLines > 0 && box->isSingleLine) { goto goto_skip_to_post_input; }
            
            if(box->caretIndex == box->text.len) { ls_utf32AppendBuffer(&box->text, buff, realCopyLen); }
            else { ls_utf32InsertBuffer(&box->text, buff, realCopyLen, box->caretIndex); }
            
            box->caretIndex      += realCopyLen;
            box->lineCount       += addedLines;
            box->caretLineIdx    += addedLines;
            box->currLineBeginIdx = setIndices(box->caretIndex-1);
            
            inputUse = TRUE;
        }
        
        //NOTE: GOTO label to skip here.
        goto_skip_to_post_input:
        
        box->dtCaret += c->dt;
        if(box->dtCaret >= 400) { box->dtCaret = 0; box->isCaretOn = !box->isCaretOn; }
        
        //NOTE: box->postInput
        if(box->callback2 && inputUse)
        { box->callback2(c, box->callback2Data); }
    }
    
#if 0
    //TODONOTE: DEBUG Info On Textbox -------------
    
    Arena prev2 = ls_arenaUse(c->frameArena);
    
    utf32 lineCountStr        = ls_utf32FromInt(box->lineCount);
    utf32 currLineBeginIdxStr = ls_utf32FromInt(box->currLineBeginIdx);
    utf32 caretIndexStr       = ls_utf32FromInt(box->caretIndex);
    utf32 caretLineIdxStr     = ls_utf32FromInt(box->caretLineIdx);
    utf32 viewBeginIdxStr     = ls_utf32FromInt(box->viewBeginIdx);
    utf32 selectBeginLineStr  = ls_utf32FromInt(box->selectBeginLine);
    utf32 selectEndLineStr    = ls_utf32FromInt(box->selectEndLine);
    utf32 selectBeginIdxStr   = ls_utf32FromInt(box->selectBeginIdx);
    utf32 selectEndIdxStr     = ls_utf32FromInt(box->selectEndIdx);
    utf32 isSelectingStr      = ls_utf32FromAscii(box->isSelecting == TRUE ? 
                                                  (char *)"Is Selecting: True" : 
                                                  (char *)"Is Selecting: False");
    
    ls_utf32Prepend(&lineCountStr, U"Line Count: "_W);
    ls_utf32Prepend(&currLineBeginIdxStr, U"Curr Line Begin Idx: "_W);
    ls_utf32Prepend(&caretIndexStr, U"Caret Index: "_W);
    ls_utf32Prepend(&caretLineIdxStr, U"Caret Line Idx: "_W);
    ls_utf32Prepend(&viewBeginIdxStr, U"View Begin Idx: "_W);
    ls_utf32Prepend(&selectBeginLineStr, U"Select Begin Line: "_W);
    ls_utf32Prepend(&selectEndLineStr, U"Select End Line: "_W);
    ls_utf32Prepend(&selectBeginIdxStr, U"Select Begin Idx: "_W);
    ls_utf32Prepend(&selectEndIdxStr, U"Select End Idx: "_W);
    
    ls_uiLabel(c, lineCountStr, 400, 600);
    ls_uiLabel(c, currLineBeginIdxStr, 400, 580);
    ls_uiLabel(c, caretIndexStr, 400, 560);
    ls_uiLabel(c, caretLineIdxStr, 400, 540);
    ls_uiLabel(c, viewBeginIdxStr, 400, 520);
    ls_uiLabel(c, selectBeginLineStr, 400, 500);
    ls_uiLabel(c, selectEndLineStr, 400, 480);
    ls_uiLabel(c, selectBeginIdxStr, 400, 460);
    ls_uiLabel(c, selectEndIdxStr, 400, 440);
    ls_uiLabel(c, isSelectingStr, 400, 420);
    
    ls_arenaUse(prev2);
    
    //TODONOTE: DEBUG Info On Textbox -------------
#endif
    
    RenderCommand command = {UI_RC_TEXTBOX, xPos, yPos, w, h };
    command.textBox       = box;
    command.bkgColor      = c->widgetColor;
    command.textColor     = c->textColor;
    ls_uiPushRenderCommand(c, command, zLayer);
    
    ls_arenaUse(prev);
    return inputUse;
}

b32 ls_uiTextBox(UIContext *c, UITextBox *box, UIPos pos, s32 zLayer = 0)
{
    UIWindow *win = c->currWindow;

    if (pos.kind == UIPosKind::Abs)
    {
        return ls_uiTextBox(c, box, pos.ix, pos.iy, pos.iw, pos.ih, zLayer);
    }
    else if (pos.kind == UIPosKind::Scl)
    {
        s32 xPos  = pos.sx*win->width;
        s32 yPos  = pos.sy*win->height;
        return ls_uiTextBox(c, box, xPos, yPos, pos.sw, pos.sh, zLayer);
    }

    s32 xPos = pos.fx*win->width;
    s32 yPos = pos.fy*win->height;
    s32 w    = pos.fw*win->width;
    s32 h    = pos.fh*win->height;
    return ls_uiTextBox(c, box, xPos, yPos, w, h, zLayer);
}
