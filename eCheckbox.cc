#include <pix5.h>
#include "elfgui5.h"



//constructor
eCheckbox::eCheckbox(const Str& ename,int ex,int ey,int ew,int eh,const Str& txt,bool echecked):Element(ename,ex,ey,ew,eh)
{
	#define DEFAULT_CHECK_SIZE 13

	//parent class vars
	type="checkbox";
	
	//own vars
	checked=echecked;
	check_size=DEFAULT_CHECK_SIZE;

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

	ready_to_check=false;
	
	//own elements

	//other
	set_text(txt);
	

	
	draw();
}



//destructor
eCheckbox::~eCheckbox()
{
}






//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void eCheckbox::loop()
{
	Mouse m=Input::get_mouse();

	if(ready_to_check && m.button(1)==false)
		ready_to_check=false;
}



//***** DRAW
void eCheckbox::draw()
{
	draw_edit_panel(image,enabled,0,(h-check_size)/2,check_size,check_size);
	
	//show tex
	if(show_tex)
		draw_texture_align(image,tex_align,tex_offx,tex_offy,tex);

	//show text
	if(show_text)
	{
		if(enabled)
			draw_text_align(image,text_align,text_offx,text_offy,Theme::font::normal,Theme::color::text,text,true,BlendMode::Copy);
		else
			draw_text_align(image,text_align,text_offx,text_offy,Theme::font::normal,Theme::color::d_text,text,true,BlendMode::Copy);
	}

	//checked
	if(checked)
	{
		if(enabled)
		{
			image->line(2,(h-check_size)/2+2,check_size-2,(h-check_size)/2+check_size-2,Theme::color::text);
			image->line(2,(h-check_size)/2+check_size-2,check_size-2,(h-check_size)/2+2,Theme::color::text);
		}
		else
		{
			image->line(2,(h-check_size)/2+2,check_size-2,(h-check_size)/2+check_size-2,Theme::color::d_text);
			image->line(2,(h-check_size)/2+check_size-2,check_size-2,(h-check_size)/2+2,Theme::color::d_text);
		}
	}
}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//void eCheckbox::on_event(Event* ev){}

void eCheckbox::on_mouse_enter(int mx,int my)
{
}

void eCheckbox::on_mouse_leave()
{
}

void eCheckbox::on_mouse_move(int mx,int my){}

void eCheckbox::on_mouse_down(int but,int mx,int my)
{
	ready_to_check=true;
}

void eCheckbox::on_mouse_up(int but,int mx,int my)
{
	if(but==1 && ready_to_check)
	{
		checked=!checked;
		send_event("trigger");

		draw();
	}

	ready_to_check=false;
}

void eCheckbox::on_mouse_click(int but,int mx,int my){}
void eCheckbox::on_mouse_doubleclick(int but,int mx,int my){}
void eCheckbox::on_mouse_wheel_down(int mx,int my){}
void eCheckbox::on_mouse_wheel_up(int mx,int my){}
void eCheckbox::on_mouse_drag_out(){}
void eCheckbox::on_mouse_drag_in(DragPacket* dragpacket){}

void eCheckbox::on_key_down(Key& key){}
void eCheckbox::on_key_up(Key& key){}
void eCheckbox::on_text(const Str& text){}

void eCheckbox::on_resize(int width,int height){}
void eCheckbox::on_parent_resize(){}








//****************************************************************
//OWN FUNCTIONS
//****************************************************************




//SET TEXT
void eCheckbox::set_text(const Str& txt,Align::Type align,int offx,int offy)
{
	text=txt;
	text_align=align;
	text_offx=offx;
	text_offy=offy;
	
	show_text=true;
	draw();
}



//SET TEX
void eCheckbox::set_tex(Texture* src,Align::Type align,int offx,int offy)
{
	tex=src;
	tex_align=align;
	tex_offx=offx;
	tex_offy=offy;
	
	show_tex=true;
	draw();
}


//SET TEX
void eCheckbox::set_tex(const Str& filename,Align::Type align,int offx,int offy)
{
	Texture* t=Cache::texture(filename);
	set_tex(t,align,offx,offy);
}








