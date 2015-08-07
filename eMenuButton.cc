#include <pix5.h>
#include "elfgui5.h"



//constructor
eMenuButton::eMenuButton(const Str& ename,int ew,int eh,const Str& etext):Element(ename,0,0,ew,eh)
{
	//parent class vars
	type="menu_button";
	selectable=false;
	
	//own config vars
	show_text=true;
	show_tex=false;
	show_selection=true;

	text_align=Align::Middle;
	text_offx=0;
	text_offy=0;
	text="";

	tex_align=Align::Middle;
	tex_offx=0;
	tex_offy=0;
	tex=NULL;
	
	//own internal config vars (use config functions to modify)

	//own internal vars
	mouse_on=false;
	
	//own elements

	//other
	set_text(etext);
	dirty=true;
}



//destructor
eMenuButton::~eMenuButton()
{
}








//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void eMenuButton::loop()
{
}



//***** DRAW
void eMenuButton::draw()
{
	//show bg
	if(mouse_on && show_selection)
		image->clear(color->selection);
	else
		image->clear(Color(0,0,0,0));
	
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


//void eMenuButton::on_event(Event* ev){}



//***** ON MOUSE ENTER
void eMenuButton::on_mouse_enter(int mx,int my)
{
	mouse_on=true;
	dirty=true;
}



//ON MOUSE LEAVE
void eMenuButton::on_mouse_leave()
{
	mouse_on=false;
	dirty=true;
}



void eMenuButton::on_mouse_move(int mx,int my){}



//***** ON MOUSE DOWN
void eMenuButton::on_mouse_down(int but,int mx,int my)
{
	if(but==1)
		send_event("trigger");
}



void eMenuButton::on_mouse_up(int but,int mx,int my){}
//void eMenuButton::on_mouse_click(int but,int mx,int my){}
//void eMenuButton::on_mouse_doubleclick(int but,int mx,int my){}
//void eMenuButton::on_mouse_wheel_down(int mx,int my){}
//void eMenuButton::on_mouse_wheel_up(int mx,int my){}
void eMenuButton::on_mouse_drag_out(){}
void eMenuButton::on_mouse_drag_in(DragPacket* dragpacket,int mx,int my){}
void eMenuButton::on_key_down(Key& key){}
void eMenuButton::on_key_up(Key& key){}
void eMenuButton::on_text(const Str& text){}
void eMenuButton::on_resize(int width,int height){}
void eMenuButton::on_parent_resize(){}
void eMenuButton::on_select(){}
void eMenuButton::on_unselect(){}
void eMenuButton::on_resolution_change(int width,int height){}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//***** SHRINK
void eMenuButton::shrink()
{
	int width=0;
	int textw=0;
	int texw=0;
	
	if(show_text)
		textw=font->len(text);
	if(show_tex && tex)
		texw=tex->width();
	
	if(texw>textw)
		width=texw;
	else
		width=textw;
		
	resize(width>0?width:10,h);
}



//***** SET TEXT
void eMenuButton::set_text(const Str& txt,Align::Type align,int offx,int offy)
{
	text=txt;
	text_align=align;
	text_offx=offx;
	text_offy=offy;
	
	show_text=true;
	dirty=true;
}



//***** SET TEX
void eMenuButton::set_tex(Texture* src,Align::Type align,int offx,int offy)
{
	tex=src;
	tex_align=align;
	tex_offx=offx;
	tex_offy=offy;
	
	show_tex=true;
	dirty=true;
}



//***** SET TEX
void eMenuButton::set_tex(const Str& filename,Align::Type align,int offx,int offy)
{
	Texture* t=Texture::cache(filename);
	set_tex(t,align,offx,offy);
}



//***** SHOW TEXT
void eMenuButton::set_show_text(bool show)
{
	show_text=show;
	dirty=true;
}



//***** SHOW TEX
void eMenuButton::set_show_tex(bool show)
{
	show_tex=show;
	dirty=true;
}



//***** SHOW SELECTION
void eMenuButton::set_show_selection(bool show)
{
	show_selection=show;
	dirty=true;
}









//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************








