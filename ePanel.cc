#include <pix5.h>
#include "elfgui5.h"



//constructor
ePanel::ePanel(const Str& ename,int ex,int ey,int ew,int eh,bool invert):Element(ename,ex,ey,ew,eh)
{
	//parent class vars
	type="panel";
	
	//own config vars
	selectable=false;
	
	//own internal config vars (use config functions to modify)
	customized=false;
	inverted=invert;
	show_text=false;
	show_tex=false;

	plain=false;
	plain_color=0;

	text_align=Align::Top;
	text_offx=0;
	text_offy=0;
	text="";

	tex_align=Align::Top;
	tex_offx=0;
	tex_offy=0;
	tex=NULL;

	custom_layout=NULL;

	//own internal vars

	//own elements

	//other
	dirty=true;
}



//destructor
ePanel::~ePanel()
{
}








//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void ePanel::loop()
{
}



//***** DRAW
void ePanel::draw()
{
	if(customized)
	{
		image->clear(Color(0,0,0,0));
		if(custom_layout)
			image->blit(0,0,custom_layout,false);
	}
	else if(plain)
		image->clear(plain_color);
	else
		draw_panel(image,color,inverted,enabled);


	//show tex
	if(show_tex)
		draw_texture_align(image,tex_align,tex_offx,tex_offy,tex);

	//show text
	if(show_text)
	{
		if(enabled)
			draw_text_align(image,text_align,text_offx,text_offy,font,color->text,text);
		else
			draw_text_align(image,text_align,text_offx,text_offy,font,color->d_text,text);
	}
}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//void ePanel::on_event(Event* ev){}
void ePanel::on_mouse_enter(int mx,int my){}
void ePanel::on_mouse_leave(){}
void ePanel::on_mouse_move(int mx,int my){}
void ePanel::on_mouse_down(int but,int mx,int my){}
void ePanel::on_mouse_up(int but,int mx,int my){}
//void ePanel::on_mouse_click(int but,int mx,int my){}
//void ePanel::on_mouse_doubleclick(int but,int mx,int my){}
//void ePanel::on_mouse_wheel_down(int mx,int my){}
//void ePanel::on_mouse_wheel_up(int mx,int my){}
void ePanel::on_mouse_drag_out(){}
void ePanel::on_mouse_drag_in(DragPacket* dragpacket){}
void ePanel::on_key_down(Key& key){}
void ePanel::on_key_up(Key& key){}
void ePanel::on_text(const Str& text){}
void ePanel::on_resize(int width,int height){}
void ePanel::on_parent_resize(){}
void ePanel::on_select(){}
void ePanel::on_unselect(){}









//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//***** SET TEXT
void ePanel::set_text(const Str& txt,Align::Type align,int offx,int offy)
{
	text=txt;
	text_align=align;
	text_offx=offx;
	text_offy=offy;
	
	show_text=true;
	dirty=true;
}



//***** SET TEX
void ePanel::set_tex(Texture* src,Align::Type align,int offx,int offy)
{
	tex=src;
	tex_align=align;
	tex_offx=offx;
	tex_offy=offy;

	show_tex=true;
	dirty=true;
}



//***** SET TEX
void ePanel::set_tex(const Str& filename,Align::Type align,int offx,int offy)
{
	Texture* t=Cache::texture(filename);
	set_tex(t,align,offx,offy);
}



//***** SHOW TEXT
void ePanel::set_show_text(bool show)
{
	show_text=show;
	dirty=true;
}



//***** SHOW TEX
void ePanel::set_show_tex(bool show)
{
	show_tex=show;
	dirty=true;
}



//***** SET INVERTED
void ePanel::set_inverted(bool invert)
{
	inverted=invert;
	dirty=true;
}



//***** SET PLAIN
void ePanel::set_plain(bool show,const Color& col)
{
	plain_color=col;
	plain=show;
	dirty=true;
}



//***** SET CUSTOMIZED
void ePanel::set_customized(bool custom)
{
	customized=custom;
	dirty=true;
}



//***** SET CUSTOM
void ePanel::set_custom(Texture* lay,bool autosize,bool sh_text,bool sh_tex)
{
	custom_layout=lay;

	show_text=sh_text;
	show_tex=sh_tex;

	//check if we need to resize the panel
	if(autosize)
		resize(lay->width(),lay->height());

	customized=true;

	dirty=true;
}



//***** SET CUSTOM
void ePanel::set_custom(const Str& lay,bool autosize,bool sh_text,bool sh_tex)
{
	set_custom(Cache::texture(lay),autosize,sh_text,sh_tex);
}








//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************








