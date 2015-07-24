#include <pix5.h>
#include "elfgui5.h"



//constructor
eButton::eButton(const Str& ename,int ex,int ey,int ew,int eh,const Str& txt):Element(ename,ex,ey,ew,eh)
{
	//parent class vars
	type="button";
	
	//own vars
	pushed=false;

	show_text=true;
	text_align=Align::Middle;
	text_offx=0;
	text_offy=0;
	text="";

	show_tex=false;
	tex_align=Align::Middle;
	tex_offx=0;
	tex_offy=0;
	tex=NULL;

	pushed_and_left=false;
	
	//own elements

	//other
	set_text(txt);
	

	
	draw();
}



//destructor
eButton::~eButton()
{
}






//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void eButton::loop()
{
	Mouse m=Input::get_mouse();

	if(pushed_and_left && m.button(1)==false)
		pushed_and_left=false;
}



//***** DRAW
void eButton::draw()
{
	draw_panel(image,pushed,enabled);
	
	//show tex
	if(show_tex)
		draw_texture_align(image,tex_align,tex_offx+(pushed?1:0),tex_offy+(pushed?1:0),tex);

	//show text
	if(show_text)
	{
		if(enabled)
			draw_text_align(image,text_align,text_offx+(pushed?1:0),text_offy+(pushed?1:0),Theme::font::normal,Theme::color::text,text);
		else
			draw_text_align(image,text_align,text_offx+(pushed?1:0),text_offy+(pushed?1:0),Theme::font::normal,Theme::color::d_text,text);
	}
}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//void eButton::on_event(Event* ev){}

void eButton::on_mouse_enter(int mx,int my)
{
	Mouse m=Input::get_mouse();

	if(pushed_and_left && m.button(1))
	{
		pushed=true;
		draw();
	}

	pushed_and_left=false;
}

void eButton::on_mouse_leave()
{
	if(pushed)
	{
		pushed_and_left=true;
		pushed=false;
		draw();
	}
}

void eButton::on_mouse_move(int mx,int my){}

void eButton::on_mouse_down(int but,int mx,int my)
{
	if(but==1)
	{
		pushed=true;
		draw();
	}
}

void eButton::on_mouse_up(int but,int mx,int my)
{
	if(but==1)
	{
		if(pushed)
		{
			send_event("trigger");
		}

		pushed=false;
		draw();
	}
}

void eButton::on_mouse_click(int but,int mx,int my){}
void eButton::on_mouse_doubleclick(int but,int mx,int my){}
void eButton::on_mouse_wheel_down(int mx,int my){}
void eButton::on_mouse_wheel_up(int mx,int my){}
void eButton::on_mouse_drag_out(){}
void eButton::on_mouse_drag_in(DragPacket* dragpacket){}

void eButton::on_key_down(Key& key){}
void eButton::on_key_up(Key& key){}
void eButton::on_text(const Str& text){}

void eButton::on_resize(int width,int height){}
void eButton::on_parent_resize(){}








//****************************************************************
//OWN FUNCTIONS
//****************************************************************




//SET TEXT
void eButton::set_text(const Str& txt,Align::Type align,int offx,int offy)
{
	text=txt;
	text_align=align;
	text_offx=offx;
	text_offy=offy;
	
	show_text=true;
	draw();
}



//SET TEX
void eButton::set_tex(Texture* src,Align::Type align,int offx,int offy)
{
	tex=src;
	tex_align=align;
	tex_offx=offx;
	tex_offy=offy;
	
	show_tex=true;
	draw();
}


//SET TEX
void eButton::set_tex(const Str& filename,Align::Type align,int offx,int offy)
{
	Texture* t=Cache::texture(filename);
	set_tex(t,align,offx,offy);
}







