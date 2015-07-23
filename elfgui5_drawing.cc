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
void draw_text_align(Texture* tex,int align,int offx,int offy,Font *font,const Color& col,const Str& text,BlendMode::Type blend)
{
	int w=tex->width();
	int h=tex->height();
	int tw=font->len(text);
	int th=font->height();

	int x=0;
	int y=0;

	//set text coordonates
	switch(align)
	{
		//top left
		case ALIGN_TOPLEFT:
			x=offx;
			y=offy;
		break;

		//top
		case ALIGN_TOP:
			x=(w-tw)/2+offx;
			y=offy;
		break;

		//top right
		case ALIGN_TOPRIGHT:
			x=w-tw+offx;
			y=offy;
		break;

		//left
		case ALIGN_LEFT:
			x=offx;
			y=(h-th)/2+offy;
		break;

		//middle
		case ALIGN_MIDDLE:
			x=(w-tw)/2+offx;
			y=(h-th)/2+offy;
		break;

		//right
		case ALIGN_RIGHT:
			x=w-tw+offx;
			y=(h-th)/2+offy;
		break;

		//bottom left
		case ALIGN_BOTTOMLEFT:
			x=offx;
			y=h-th+offy;
		break;

		//bottom
		case ALIGN_BOTTOM:
			x=(w-tw)/2+offx;
			y=h-th+offy;
		break;

		//bottom right
		case ALIGN_BOTTOMRIGHT:
			x=w-tw+offx;
			y=h-th+offy;
		break;
	}

	//draw text on texture
	tex->print(font,x,y,col,text,blend);
}


