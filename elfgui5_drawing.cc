#include <pix5.h>
#include "elfgui5.h"





//***** DRAW PANEL
void draw_panel(Texture* tex,int x,int y,int w,int h,bool inverted,bool enabled)
{
	if(tex==NULL)
		return;
	
	//set proper color
	Color col[3];
	if(enabled==false)
	{
		if(inverted)
		{
			col[0]=Theme::color::d_dark;
			col[1]=Theme::color::d_medium;
			col[2]=Theme::color::d_light;
		}
		else
		{
			col[0]=Theme::color::d_light;
			col[1]=Theme::color::d_medium;
			col[2]=Theme::color::d_dark;
		}
	}
	else
	{
		if(inverted)
		{
			col[0]=Theme::color::dark;
			col[1]=Theme::color::medium;
			col[2]=Theme::color::light;
		}
		else
		{
			col[0]=Theme::color::light;
			col[1]=Theme::color::medium;
			col[2]=Theme::color::dark;
		}
	}


	//draw panel
	tex->clear(col[1]);
	tex->line(x,y,x+w-1,y,col[0]);
	tex->line(x,y,x,y+h-2,col[0]);
	tex->line(x,y+h-1,x+w-1,y+h-1,col[2]);
	tex->line(x+w-1,y+1,x+w-1,y+h-1,col[2]);
}



//***** DRAW PANEL
void draw_panel(Texture* tex,bool inverted,bool disabled)
{
	if(tex==NULL)
		return;

	int w=tex->width();
	int h=tex->height();

	draw_panel(tex,0,0,w,h,inverted,disabled);
}










//***** DRAW TEXT ALIGN
void draw_text_align(Texture* tex,Align::Type align,int offx,int offy,Font *font,const Color& col,const Str& text,bool kerning,BlendMode::Type blend)
{
	int w=tex->width();
	int h=tex->height();
	int tw=font->len(text,kerning);
	int th=font->height();

	int x=0;
	int y=0;

	//set text coordonates
	switch(align)
	{
		//top left
		case Align::TopLeft:
			x=offx;
			y=offy;
		break;

		//top
		case Align::Top:
			x=(w-tw)/2+offx;
			y=offy;
		break;

		//top right
		case Align::TopRight:
			x=w-tw+offx;
			y=offy;
		break;

		//left
		case Align::Left:
			x=offx;
			y=(h-th)/2+offy;
		break;

		//middle
		case Align::Middle:
			x=(w-tw)/2+offx;
			y=(h-th)/2+offy;
		break;

		//right
		case Align::Right:
			x=w-tw+offx;
			y=(h-th)/2+offy;
		break;

		//bottom left
		case Align::BottomLeft:
			x=offx;
			y=h-th+offy;
		break;

		//bottom
		case Align::Bottom:
			x=(w-tw)/2+offx;
			y=h-th+offy;
		break;

		//bottom right
		case Align::BottomRight:
			x=w-tw+offx;
			y=h-th+offy;
		break;
	}

	//draw text on texture
	tex->print(font,x,y,col,text,kerning,blend);
}








//***** DRAW TEXTURE ALIGN
void draw_texture_align(Texture* dest,Align::Type align,int offx,int offy,Texture* src,bool alpha)
{
	int w=dest->width();
	int h=dest->height();
	int tw=src->width();
	int th=src->height();

	int x=0;
	int y=0;

	//set text coordonates
	switch(align)
	{
		//top left
		case Align::TopLeft:
			x=offx;
			y=offy;
		break;

		//top
		case Align::Top:
			x=(w-tw)/2+offx;
			y=offy;
		break;

		//top right
		case Align::TopRight:
			x=w-tw+offx;
			y=offy;
		break;

		//left
		case Align::Left:
			x=offx;
			y=(h-th)/2+offy;
		break;

		//middle
		case Align::Middle:
			x=(w-tw)/2+offx;
			y=(h-th)/2+offy;
		break;

		//right
		case Align::Right:
			x=w-tw+offx;
			y=(h-th)/2+offy;
		break;

		//bottom left
		case Align::BottomLeft:
			x=offx;
			y=h-th+offy;
		break;

		//bottom
		case Align::Bottom:
			x=(w-tw)/2+offx;
			y=h-th+offy;
		break;

		//bottom right
		case Align::BottomRight:
			x=w-tw+offx;
			y=h-th+offy;
		break;
	}

	//draw text on texture
	dest->blit(x,y,src,alpha);
}



