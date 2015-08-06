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
		color->d_editing=Color::ubyte(140,140,140);
		color->d_selection=Color::ubyte(100,100,100);
		color->d_extra=Color::ubyte(255,0,0);

		color->tint[0]=Color::ubyte(255,255,255,100);
		color->tint[1]=Color::ubyte(255,255,255,100);
		color->tint[2]=Color::ubyte(255,255,255,100);
		color->tint[3]=Color::ubyte(255,255,255,100);




		//fonts
		font->tiny=Font::cache("fonts/Vera.ttf",6);
		font->tiny_mono=Font::cache("fonts/VeraMono.ttf",6);

		font->small=Font::cache("fonts/Vera.ttf",8);
		font->small_mono=Font::cache("fonts/VeraMono.ttf",8);

		font->normal=Font::cache("fonts/Vera.ttf",10);
		font->normal_mono=Font::cache("fonts/VeraMono.ttf",11);

		font->big=Font::cache("fonts/Vera.ttf",16);
		font->big_mono=Font::cache("fonts/VeraMono.ttf",16);
		
		font->huge=Font::cache("fonts/Vera.ttf",22);
		font->huge_mono=Font::cache("fonts/VeraMono.ttf",22);
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

