#pragma once

#include "Platform\win32.h"
#include "tools\OpenGL\glCore.h"

enum TEXTURE_ENUM
{
	TEX_TEST = 0,
	TEX_TEST_2 = 1,

	TEX_MAX
};

struct Texture
{
	GLuint			*Tex;
	char			**Path;

	s32				texQuantity;
	u32				texIdx;
	TEXTURE_ENUM	*Name;
};

Texture *InitTextureManager(char **Paths, TEXTURE_ENUM *Names, u32 texQuantity);
void FreeTextureManager(Texture *Tex);
void GenAndBindTexture(const char *Path, GameInfo *Game, Texture *TextureManager);