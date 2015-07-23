#include <pix5.h>
#include "elfgui5.h"



Color Theme::color::light;
Color Theme::color::medium;
Color Theme::color::dark;
Color Theme::color::text;
Color Theme::color::editing;
Color Theme::color::selection;
Color Theme::color::extra;

Color Theme::color::d_light;
Color Theme::color::d_medium;
Color Theme::color::d_dark;
Color Theme::color::d_text;
Color Theme::color::d_editing;
Color Theme::color::d_selection;
Color Theme::color::d_extra;

Font* Theme::font::tiny;
Font* Theme::font::tiny_mono;
Font* Theme::font::small;
Font* Theme::font::small_mono;
Font* Theme::font::normal;
Font* Theme::font::normal_mono;
Font* Theme::font::big;
Font* Theme::font::big_mono;
Font* Theme::font::huge;
Font* Theme::font::huge_mono;


namespace Theme
{
	void set(const Str& theme)
	{
		if(theme=="default")
		{
			//colors
			Theme::color::light=Color::ubyte(220,220,220);
			Theme::color::medium=Color::ubyte(170,170,170);
			Theme::color::dark=Color::ubyte(120,120,120);
			Theme::color::text=Color::ubyte(0,0,0);
			Theme::color::editing=Color::ubyte(240,240,240);
			Theme::color::selection=Color::ubyte(50,50,150);
			Theme::color::extra=Color::ubyte(255,0,0);

			Theme::color::d_light=Color::ubyte(170,170,170);
			Theme::color::d_medium=Color::ubyte(120,120,120);
			Theme::color::d_dark=Color::ubyte(70,70,70);
			Theme::color::d_text=Color::ubyte(30,30,30);
			Theme::color::d_editing=Color::ubyte(200,200,200);
			Theme::color::d_selection=Color::ubyte(50,50,50);
			Theme::color::d_extra=Color::ubyte(120,0,0);




			//fonts
			font::tiny=Cache::font("fonts/DejaVuSans.ttf",6);
			font::tiny_mono=Cache::font("fonts/DejaVuSansMono.ttf",6);

			font::small=Cache::font("fonts/DejaVuSans.ttf",8);
			font::small_mono=Cache::font("fonts/DejaVuSansMono.ttf",8);

			font::normal=Cache::font("fonts/DejaVuSans.ttf",11);
			font::normal_mono=Cache::font("fonts/DejaVuSansMono.ttf",11);

			font::big=Cache::font("fonts/DejaVuSans.ttf",16);
			font::big_mono=Cache::font("fonts/DejaVuSansMono.ttf",16);
			
			font::huge=Cache::font("fonts/DejaVuSans.ttf",22);
			font::huge_mono=Cache::font("fonts/DejaVuSansMono.ttf",22);
		}
	}

}


