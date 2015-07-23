#pragma once
#include <pix5.h>
#include "elfgui5.h"

namespace Theme
{

	class color
	{
	public:

		//normal
		static Color light,medium,dark;
		static Color text;
		static Color editing;
		static Color selection;
		static Color extra;

		//disabled
		static Color d_light,d_medium,d_dark;
		static Color d_text;
		static Color d_editing;
		static Color d_selection;
		static Color d_extra;
	};



	class font
	{
	public:
		static Font* tiny;
		static Font* tiny_mono;
		static Font* small;
		static Font* small_mono;
		static Font* normal;
		static Font* normal_mono;
		static Font* big;
		static Font* big_mono;
		static Font* huge;
		static Font* huge_mono;
	};



	void set(const Str& theme);
}
