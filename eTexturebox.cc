#include <pix5.h>
#include "elfgui5.h"



//constructor
eTexturebox::eTexturebox(const Str& ename,int ex,int ey,int ew,int eh,Texture* texture,int brdr,bool autosize):Element(ename,ex,ey,ew,eh)
{
	//parent class vars
	type="texturebox";
	selectable=false;
	
	//own config vars
	
	//own internal config vars (use config functions to modify)
	dynamic=false;
	tex=texture;
	tex_offx=0;
	tex_offy=0;
	border=brdr;
	border_color=color->text;
	bg_color=Color(0,0,0,0);

	//own internal vars
	moving_tex=false;
	moving_tex_x=0;
	moving_tex_y=0;
	
	//own elements

	//other
	if(autosize)
		shrink();
	set_custom_cursor("gfx/elements/cursor_hand.png",8,8);
	use_custom_cursor=false;
	dirty=true;
}



//destructor
eTexturebox::~eTexturebox()
{
}








//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void eTexturebox::loop()
{
	Mouse& m=Input::get_mouse();

	if(m.left()==false && moving_tex)
		moving_tex=false;
}



//***** DRAW
void eTexturebox::draw()
{
	//clear image
	image->clear(bg_color);

	//draw texture
	image->blit(border+tex_offx,border+tex_offy,tex);

	//draw border
	for(int a=0;a<border;a++)
		image->rect(a,a,w-1-a,h-1-a,border_color);
}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//void eTexturebox::on_event(Event* ev){}
void eTexturebox::on_mouse_enter(int mx,int my){}
void eTexturebox::on_mouse_leave(){}



//***** ON MOUSE MOVE
void eTexturebox::on_mouse_move(int mx,int my)
{
	if(dynamic && moving_tex)
	{
		tex_offx=mx-moving_tex_x;
		tex_offy=my-moving_tex_y;

		//make sure image stays within range
		if(tex_offx<=-tex->width())
			tex_offx=-tex->width()+1;
		if(tex_offx>=w-(border*2))
			tex_offx=w-(border*2)-1;

		if(tex_offy<=-tex->height())
			tex_offy=-tex->height()+1;
		if(tex_offy>=h-(border*2))
			tex_offy=h-(border*2)-1;

		dirty=true;
	}
}



//***** ON MOUSE DOWN
void eTexturebox::on_mouse_down(int but,int mx,int my)
{
	if(but==1 && dynamic)
	{
		moving_tex=true;
		moving_tex_x=mx-tex_offx;
		moving_tex_y=my-tex_offy;
	}
}



void eTexturebox::on_mouse_up(int but,int mx,int my){}
//void eTexturebox::on_mouse_click(int but,int mx,int my){}
//void eTexturebox::on_mouse_doubleclick(int but,int mx,int my){}
//void eTexturebox::on_mouse_wheel_down(int mx,int my){}
//void eTexturebox::on_mouse_wheel_up(int mx,int my){}
void eTexturebox::on_mouse_drag_out(){}
void eTexturebox::on_mouse_drag_in(DragPacket* dragpacket,int mx,int my){}
void eTexturebox::on_key_down(Key& key){}
void eTexturebox::on_key_up(Key& key){}
void eTexturebox::on_text(const Str& text){}
void eTexturebox::on_resize(int width,int height){}
void eTexturebox::on_parent_resize(){}
void eTexturebox::on_select(){}
void eTexturebox::on_unselect(){}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//***** SHRINK
void eTexturebox::shrink()
{
	int tw=border*2;
	int th=border*2;

	if(tex)
	{
		tw+=tex->width();
		th+=tex->height();
	}

	resize(tw,th);
}



//***** SET TEXTURE
void eTexturebox::set_texture(Texture* texture,int offx,int offy,bool autosize)
{
	tex=texture;
	tex_offx=offx;
	tex_offy=offy;

	if(autosize)
		resize(tex->width()+(border*2),tex->height()+(border*2));

	dirty=true;
}



//***** SET TEXTURE
void eTexturebox::set_texture(const Str& filename,int offx,int offy,bool autosize)
{
	set_texture(Texture::cache(filename),offx,offy,autosize);
}



//***** SET TEXTURE OFFSET
void eTexturebox::set_texture_offset(int offx,int offy)
{
	tex_offx=offx;
	tex_offy=offy;
	dirty=true;
}



//***** SET BORDER
void eTexturebox::set_border(int brdr,bool autosize)
{
	border=brdr;
	
	if(autosize)
		resize(tex->width()+(border*2),tex->height()+(border*2));

	dirty=true;
}



//***** SET BORDER COLOR
void eTexturebox::set_border_color(const Color& col)
{
	border_color=Color(col);
	dirty=true;
}



//***** SET BG COLOR
void eTexturebox::set_bg_color(const Color& col)
{
	bg_color=Color(col);
	dirty=true;
}



//***** SET DYNAMIC
void eTexturebox::set_dynamic(bool dyn)
{
	use_custom_cursor=dyn;
	dynamic=dyn;
}








//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************







