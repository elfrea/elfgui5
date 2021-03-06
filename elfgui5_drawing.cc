#include <pix5.h>
#include "elfgui5.h"





//***** DRAW PANEL
void draw_panel(Texture* tex,int x,int y,int w,int h,bool inverted,bool enabled,const Color& clight,const Color& cmedium,const Color& cdark,const Color& cdlight,const Color& cdmedium,const Color& cddark)
{
	if(tex==NULL)
		return;
	
	//set proper color
	Color col[3];
	if(enabled==false)
	{
		if(inverted)
		{
			col[0]=cddark;
			col[1]=cdmedium;
			col[2]=cdlight;
		}
		else
		{
			col[0]=cdlight;
			col[1]=cdmedium;
			col[2]=cddark;
		}
	}
	else
	{
		if(inverted)
		{
			col[0]=cdark;
			col[1]=cmedium;
			col[2]=clight;
		}
		else
		{
			col[0]=clight;
			col[1]=cmedium;
			col[2]=cdark;
		}
	}


	//draw panel
	tex->rect_fill(Rect(x,y,w,h),col[1]);
	tex->line(x,y,x+w-1,y,col[0]);
	tex->line(x,y,x,y+h-2,col[0]);
	tex->line(x,y+h-1,x+w-1,y+h-1,col[2]);
	tex->line(x+w-1,y+1,x+w-1,y+h-1,col[2]);

}



//***** DRAW PANEL
void draw_panel(Texture* tex,Colors* colors,bool inverted,bool enabled,int x,int y,int w,int h)
{
	if(tex==NULL)
		return;

	if(w==0)
		w=tex->width();
	if(h==0)
		h=tex->height();

	draw_panel(tex,x,y,w,h,inverted,enabled,colors->light,colors->medium,colors->dark,colors->d_light,colors->d_medium,colors->d_dark);
}



//***** DRAW EDIT PANEL
void draw_edit_panel(Texture* tex,Colors* colors,bool enabled,int x,int y,int w,int h)
{
	if(tex==NULL)
		return;

	if(w==0)
		w=tex->width();
	if(h==0)
		h=tex->height();

	draw_panel(tex,x,y,w,h,true,enabled,colors->light,colors->editing,colors->dark,colors->d_light,colors->d_editing,colors->d_dark);
}










//***** DRAW TEXT ALIGN
void draw_text_align(Texture* tex,Align::Type align,int offx,int offy,Font *font,const Color& col,const Str& text,bool kerning)
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
	tex->print(font,x,y,col,text,kerning);
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



//DRAW DOTTED HLINE
void draw_dotted_hline(Texture* tex,int x,int y,int w,const Color& col,int len,int spacing)
{
	int tw=tex->width();
	int th=tex->height();

	if(x>=0 && y>=0 && (x+w)<=tw && y<th)
	{
		bool draw=true;
		int c=1;
		for(int a=x;a<(x+w);a++)
		{
			if(draw)
				tex->set_pixel_fast(a,y,col);

			c++;
			if(draw && c>len)
			{
				c=1;
				draw=false;
			}
			else if(draw==false && c>spacing)
			{
				c=1;
				draw=true;
			}
		}
	}
}



//DRAW DOTTED VLINE
void draw_dotted_vline(Texture* tex,int x,int y,int h,const Color& col,int len,int spacing)
{
	int tw=tex->width();
	int th=tex->height();

	if(x>=0 && y>=0 && x<tw && (y+h)<=th)
	{
		bool draw=true;
		int c=1;
		for(int a=y;a<(y+h);a++)
		{
			if(draw)
				tex->set_pixel_fast(x,a,col);

			c++;
			if(draw && c>len)
			{
				c=1;
				draw=false;
			}
			else if(draw==false && c>spacing)
			{
				c=1;
				draw=true;
			}
		}
	}
}



//DRAW DOTTED BOX
void draw_dotted_box(Texture* tex,int x,int y,int w,int h,const Color& col,int len,int spacing)
{
	draw_dotted_hline(tex,x,y,w,col,len,spacing);
	draw_dotted_hline(tex,x,y+h-1,w,col,len,spacing);

	draw_dotted_vline(tex,x,y,h,col,len,spacing);
	draw_dotted_vline(tex,x+w-1,y,h,col,len,spacing);
}



//ROTATE TEX 90
Texture* rotate_tex90(Texture* src,bool reverse)
{
	Texture* dest=Texture::create(src->height(),src->width());
	//dest->add_cache("Rotated Texture 90");

	for(int y=0;y<src->height();y++)
	{
		for(int x=0;x<src->width();x++)
		{
			if(reverse)
				dest->set_pixel_fast(y,dest->height()-1-x,src->get_pixel_fast(x,y));
			else
				dest->set_pixel_fast(dest->width()-1-y,x,src->get_pixel_fast(x,y));
		}
	}

	return dest;
}



//ROTATE TEX 90
Texture* rotate_tex90(const Str& filename,bool reverse)
{
	return rotate_tex90(Texture::cache(filename),reverse);
}



//ROTATE TEX 180
Texture* rotate_tex180(Texture* src)
{
	Texture* dest=Texture::create(src->height(),src->width());
	//dest->add_cache("Rotated Texture 180");

	for(int y=0;y<src->height();y++)
	{
		for(int x=0;x<src->width();x++)
		{
			dest->set_pixel_fast(dest->width()-1-x,dest->height()-1-y,src->get_pixel_fast(x,y));
		}
	}

	return dest;
}



//ROTATE TEX 90
Texture* rotate_tex180(const Str& filename)
{
	return rotate_tex180(Texture::cache(filename));
}








