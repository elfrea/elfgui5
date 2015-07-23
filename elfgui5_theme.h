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


	void set(const Str& theme);
}
