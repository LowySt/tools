#pragma once

#include "Platform\win32.h"
#include "tools\OpenGL\glCore.h"
#include "tools\lsCRT.h"
#include "tools\Maths\Maths.h"

struct Shader
{
	GLuint Program;

	GLuint VertexShader;
	GLuint FragmentShader;

	GLchar *vertexShaderPath;
	GLchar *vertexShaderName;
	GLchar *fragmentShaderPath;
	GLchar *fragmentShaderName;

	void setVec3(const char* name, v3 v);
	void setVec3(const char* name, f32 x, f32 y, f32 z);
	void setFloat(const char* name, f32 value);
};

Shader *CreateShaderProgram(GLchar *vertexShaderPath, GLchar *fragmentShaderPath);
void UseShader(GLuint Program);