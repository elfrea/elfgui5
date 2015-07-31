#pragma once

#include <pix5.h>
#include "elfgui5.h"


class DragPacket:public Obj
{
	OBJ("DragPacket")
	
public:
	//constructor
	DragPacket(const Str& icon_path,int offx=0,int offy=0);

	Texture* icon;
	int offset_x;
	int offset_y;

	int i[5];
	int64_t i64[5];
	float f[5];
	double d[5];
	bool b[5];
	Str s[5];
};



