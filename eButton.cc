#include <pix5.h>
#include "elfgui5.h"



//constructor
eButton::eButton(const Str& ename,int ex,int ey,int ew,int eh,const Str& txt):Element(ename,ex,ey,ew,eh)
{
	//parent class vars
	type="button";
	
	//own config vars

	//own internal config vars (use config functions to modify)
	customized=false;
	show_text=true;
	show_tex=false;

	text_align=Align::Middle;
	text_offx=0;
	text_offy=0;
	text="";

	tex_align=Align::Middle;
	tex_offx=0;
	tex_offy=0;
	tex=NULL;

	custom_layout=NULL;
	custom_layout_pushed=NULL;
	custom_layout_hover=NULL;

	//own internal vars
	pushed=false;
	pushed_and_left=false;
	custom_img=NULL;
	
	//own elements

	//other
	set_text(txt);
	dirty=true;
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
	Mouse& m=Input::get_mouse();

	if(pushed_and_left && m.button(1)==false)
		pushed_and_left=false;
	
	//set custom img
	if(customized)
	{
		//pushed
		if(pushed)
		{
			if(custom_img!=custom_layout_pushed)
			{
				custom_img=custom_layout_pushed;
				dirty=true;
			}
		}

		//hover
		else if(ElfGui5::base->find_element_under_mouse()==this)
		{
			if(custom_img!=custom_layout_hover)
			{
				custom_img=custom_layout_hover;
				dirty=true;
			}
		}

		//normal
		else if(custom_img!=custom_layout)
		{
			custom_img=custom_layout;
			dirty=true;
		}
	}
}



//***** DRAW
void eButton::draw()
{
	
	//draw button
	if(customized)
	{
		image->clear(Color(0,0,0,0));
		if(custom_img)
			image->blit(0,0,custom_img,false);
	}
	else
		draw_panel(image,color,pushed,enabled);
	
	//show tex
	if(show_tex)
		draw_texture_align(image,tex_align,tex_offx+(pushed?1:0),tex_offy+(pushed?1:0),tex);

	//show text
	if(show_text)
	{
		if(enabled)
			draw_text_align(image,text_align,text_offx+(pushed?1:0),text_offy+(pushed?1:0),font,color->text,text);
		else
			draw_text_align(image,text_align,text_offx+(pushed?1:0),text_offy+(pushed?1:0),font,color->d_text,text);
	}

	//selected
	if(selected)
		draw_dotted_box(image,2,2,w-4,h-4,color->dark,1,1);
}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//void eButton::on_event(Event* ev){}



//***** ON MOUSE ENTER
void eButton::on_mouse_enter(int mx,int my)
{
	Mouse& m=Input::get_mouse();

	if(pushed_and_left && m.button(1))
	{
		pushed=true;
		dirty=true;
	}

	pushed_and_left=false;
}



//***** ON MOUSE LEAVE
void eButton::on_mouse_leave()
{
	Keyboard& kbd=Input::get_keyboard();

	if(pushed && kbd.is_down(KEY_SPACE)==false)
	{
		pushed_and_left=true;
		pushed=false;
		dirty=true;
	}
}



void eButton::on_mouse_move(int mx,int my){}



//***** ON MOUSE DOWN
void eButton::on_mouse_down(int but,int mx,int my)
{
	if(but==1)
	{
		pushed=true;
		dirty=true;
	}
}



//***** ON MOUSE UP
void eButton::on_mouse_up(int but,int mx,int my)
{
	Keyboard& kbd=Input::get_keyboard();

	if(but==1 && kbd.is_down(KEY_SPACE)==false)
	{
		if(pushed)
			send_event("trigger");

		pushed=false;
		dirty=true;
	}
}



//void eButton::on_mouse_click(int but,int mx,int my){}
//void eButton::on_mouse_doubleclick(int but,int mx,int my){}
//void eButton::on_mouse_wheel_down(int mx,int my){}
//void eButton::on_mouse_wheel_up(int mx,int my){}
void eButton::on_mouse_drag_out(){}
void eButton::on_mouse_drag_in(DragPacket* dragpacket){}



//***** ON KEY DOWN
void eButton::on_key_down(Key& key)
{
	if(key.code==KEY_SPACE)
	{
		pushed=true;
		dirty=true;
	}
}



//***** ON KEY UP
void eButton::on_key_up(Key& key)
{
	if(key.code==KEY_SPACE)
	{
		pushed=false;
		send_event("trigger");
		dirty=true;
	}
}



void eButton::on_text(const Str& text){}
void eButton::on_resize(int width,int height){}
void eButton::on_parent_resize(){}
void eButton::on_select(){}
void eButton::on_unselect(){}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//***** SHRINK
void eButton::shrink()
{
	int tw=font->len(text,true)+4;
	int th=font->height()+4;

	resize(tw,th);
}



//***** SET TEXT
void eButton::set_text(const Str& txt,Align::Type align,int offx,int offy)
{
	text=txt;
	text_align=align;
	text_offx=offx;
	text_offy=offy;
	
	show_text=true;
	dirty=true;
}



//***** SET TEX
void eButton::set_tex(Texture* src,Align::Type align,int offx,int offy)
{
	tex=src;
	tex_align=align;
	tex_offx=offx;
	tex_offy=offy;
	
	show_tex=true;
	dirty=true;
}



//***** SET TEX
void eButton::set_tex(const Str& filename,Align::Type align,int offx,int offy)
{
	Texture* t=Cache::texture(filename);
	set_tex(t,align,offx,offy);
}



//***** SHOW TEXT
void eButton::set_show_text(bool show)
{
	show_text=show;
	dirty=true;
}



//***** SHOW TEX
void eButton::set_show_tex(bool show)
{
	show_tex=show;
	dirty=true;
}



//***** SET CUSTOMIZED
void eButton::set_customized(bool custom)
{
	customized=custom;
	dirty=true;
}



//***** SET CUSTOM
void eButton::set_custom(Texture* lay,Texture* lay_pushed,Texture* lay_hover,bool autosize,bool sh_text,bool sh_tex)
{
	custom_layout=lay;
	custom_layout_pushed=lay_pushed;
	custom_layout_hover=lay_hover;

	show_text=sh_text;
	show_tex=sh_tex;

	//check if we need to resize the button
	if(autosize)
		resize(lay->width(),lay->height());

	customized=true;
	custom_img=custom_layout;

	dirty=true;
}



//***** SET CUSTOM
void eButton::set_custom(const Str& lay,const Str& lay_pushed,const Str& lay_hover,bool autosize,bool sh_text,bool sh_tex)
{
	set_custom(Cache::texture(lay),Cache::texture(lay_pushed),Cache::texture(lay_hover),autosize,sh_text,sh_tex);
}








//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************








