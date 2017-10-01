#pragma once

#include "tools\Maths\Maths.h"
#include "tools\OpenGL\Managers\Camera.h"
#include "tools\lsCRT.h"

struct TransformManager
{
	Mat4 ModelMatrix;
	Mat4 ViewMatrix;
	Mat4 ProjectionMatrix;

	Mat4 Transform;
};

TransformManager *createTransform(MemoryArena *Memory);

void SetTransform(TransformManager *Manager);
void SetModel(TransformManager *Manager, v4 translate, v4 scale, f32 RotateX, f32 RotateY);
void SetModel(TransformManager *Manager, Mat4 Translation, Mat4 Scale, Mat4 Rotate);
void SetView(TransformManager *Manager, Camera Camera);
void SetStandardProjection(TransformManager *Manager);
void SetProjection(TransformManager *Manager, f32 FOV, f32 AspectRatio, f32 Near, f32 Far);
