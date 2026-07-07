#pragma once

template<typename T>
void ls_uiLabelInRect(UIContext *c, T label, s32 x, s32 y, s32 minW, s32 minH, Color bkg, Color border, Color text, s32 zLayer);
template<typename T>
void ls_uiLabelInRect(UIContext *c, T label, s32 x, s32 y, Color bkg, Color border, Color text, s32 zLayer);

void                      ls_uiLabel(UIContext *c, utf32 label, f32 relX, f32 relY, Color textColor, s32 zLayer);
template<typename T> void ls_uiLabel(UIContext *c, T label, s32 x, s32 y, Color textColor, s32 zLayer);
template<typename T> void ls_uiLabel(UIContext *c, T label, s32 x, s32 y, s32 zLayer);

UILayoutRect ls_uiLabelLayout(UIContext *c, utf32 label, UILayoutRect layout, UIRect deltaPos, Color textColor, s32 zLayer);
UILayoutRect ls_uiLabelLayout(UIContext *c, utf32 label, UILayoutRect layout, Color textColor, s32 zLayer);
UILayoutRect ls_uiLabelLayout(UIContext *c, const char32_t *label, UILayoutRect layout, Color textColor, s32 zLayer);
UILayoutRect ls_uiLabelLayout(UIContext *c, utf32 label, UILayoutRect layout, s32 zLayer);
UILayoutRect ls_uiLabelLayout(UIContext *c, const char32_t *label, UILayoutRect layout, s32 zLayer);
