#pragma once

#include "Platform\win32.h"
#include "tools\OpenGL\glCore.h"
#include "tools\lsCRT.h"
#include "tools\Maths\Maths.h"

struct Texture;

struct Shader
{
	GLuint Program;

	GLuint VertexShader;
	GLuint FragmentShader;

	GLchar *vertexShaderPath;
	GLchar *vertexShaderName;
	GLchar *fragmentShaderPath;
	GLchar *fragmentShaderName;

	void setTexture(const char* name, Texture* Texture, s32 idx);
	void setVec3(const char* name, v3 v);
	void setVec3(const char* name, f32 x, f32 y, f32 z);
	void setMat4(const char* name, f32 *values);
	void setFloat(const char* name, f32 value);
	void setInt(const char* name, int value);
};

Shader *CreateShaderProgram(GLchar *vertexShaderPath, GLchar *fragmentShaderPath);
void UseShader(GLuint Program);