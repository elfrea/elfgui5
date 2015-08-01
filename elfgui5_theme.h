#pragma once
#include <pix5.h>
#include "elfgui5.h"





class Colors
{
public:

	//normal
	Color light,medium,dark;
	Color text;
	Color editing;
	Color selection;
	Color extra;

	//disabled
	Color d_light,d_medium,d_dark;
	Color d_text;
	Color d_editing;
	Color d_selection;
	Color d_extra;
};





class Fonts:public Obj
{
	OBJ("Fonts")

public:

	Font* tiny;
	Font* tiny_mono;
	Font* small;
	Font* small_mono;
	Font* normal;
	Font* normal_mono;
	Font* big;
	Font* big_mono;
	Font* huge;
	Font* huge_mono;
};





class Theme:public Obj
{
	OBJ("Theme")
	
public:

	static Colors* color;
	static Fonts* font;

	static void set(const Str& theme);
	static void kill();
};






