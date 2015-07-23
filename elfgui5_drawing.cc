#include <pix5.h>
#include "elfgui5.h"


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



void draw_panel(Texture* tex,bool inverted,bool disabled)
{
	if(tex==NULL)
		return;

	int w=tex->width();
	int h=tex->height();

	draw_panel(tex,0,0,w,h,inverted,disabled);
}





