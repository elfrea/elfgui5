#include <pix5.h>
#include "elfgui5.h"



Colors* Theme::color;
Fonts* Theme::font;


void Theme::set(const Str& theme)
{
	if(color)
		delete color;
	if(font)
		delete font;

	color=new Colors();
	font=new Fonts();




	if(theme=="default")
	{
		//colors
		color->light=Color::ubyte(220,220,220);
		color->medium=Color::ubyte(170,170,170);
		color->dark=Color::ubyte(120,120,120);
		color->text=Color::ubyte(0,0,0);
		color->editing=Color::ubyte(240,240,240);
		color->selection=Color::ubyte(110,130,170);
		color->extra=Color::ubyte(255,0,0);

		color->d_light=Color::ubyte(170,170,170);
		color->d_medium=Color::ubyte(120,120,120);
		color->d_dark=Color::ubyte(70,70,70);
		color->d_text=Color::ubyte(70,70,70);
		color->d_editing=Color::ubyte(200,200,200);
		color->d_selection=Color::ubyte(100,100,100);
		color->d_extra=Color::ubyte(255,0,0);




		//fonts
		font->tiny=Cache::font("fonts/Vera.ttf",6);
		font->tiny_mono=Cache::font("fonts/VeraMono.ttf",6);

		font->small=Cache::font("fonts/Vera.ttf",8);
		font->small_mono=Cache::font("fonts/VeraMono.ttf",8);

		font->normal=Cache::font("fonts/Vera.ttf",11);
		font->normal_mono=Cache::font("fonts/VeraMono.ttf",11);

		font->big=Cache::font("fonts/Vera.ttf",16);
		font->big_mono=Cache::font("fonts/VeraMono.ttf",16);
		
		font->huge=Cache::font("fonts/Vera.ttf",22);
		font->huge_mono=Cache::font("fonts/VeraMono.ttf",22);
	}
}





//***** KILL
void Theme::kill()
{
	if(color)
		delete color;
	if(font)
		delete font;
}

