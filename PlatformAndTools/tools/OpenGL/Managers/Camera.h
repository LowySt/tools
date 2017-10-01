#pragma once

#include "tools\Maths\Maths.h"
#include "tools\lsCRT.h"

struct Camera
{
	v4 pos;
	v4 target;
	
	f32 speed;
	union
	{
		struct
		{
			v3 xDir;
			v3 yDir;
			v3 zDir;
		};
		CoordSys CameraSys;		
	};
	
	union
	{
		struct
		{
			v3 worldX;
			v3 worldY;
			v3 worldZ;
		};
		CoordSys WorldSys;
	};
};

Camera *createCamera(MemoryArena *Memory, v4 pos, v4 target);
Mat4 LookAt(CoordSys Sys, v4 cameraPos);
Mat4 LookAt(Camera Camera);