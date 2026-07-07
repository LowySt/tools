//TODO @UIPos
void ls_uiCircle(UIContext *c, s32 centerX, s32 centerY, s32 radius, s32 thickness, Color col, s32 zLayer = 0)
{
    RenderCommand command = { UI_RC_CIRCLE, centerX, centerY, radius, thickness };
    command.bkgColor = col;
    ls_uiPushRenderCommand(c, command, zLayer);
}

//TODO @UIPos
void ls_uiCircle(UIContext *c, UIPos pos, Color col, s32 zLayer = 0)
{
    RenderCommand command = { UI_RC_CIRCLE };
    command.bkgColor = col;
    command.pos      = pos;
    ls_uiPushRenderCommand(c, command, zLayer);
}

