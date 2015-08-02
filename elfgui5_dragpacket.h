#pragma once

#include <pix5.h>
#include "elfgui5.h"


class DragPacket
{
public:
	//constructor
	DragPacket(Texture* picon,int offx=0,int offy=0);
	DragPacket(const Str& icon_path,int offx=0,int offy=0);

	//destructor
	~DragPacket();

	Texture* icon;
	int offset_x;
	int offset_y;

	Str command;
	int i[5];
	int64_t i64[5];
	float f[5];
	double d[5];
	bool b[5];
	Str s[5];

	class Element* sender;
	class Element* element;
};



