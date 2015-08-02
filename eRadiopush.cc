#include <pix5.h>
#include "elfgui5.h"



//constructor
eRadiopush::eRadiopush(const Str& ename,int ex,int ey,int ew,int eh,const Str& txt,const Str& grp,bool epushed):Element(ename,ex,ey,ew,eh)
{
	//parent class vars
	type="radiopush";
	
	//own config vars
	
	//own internal config vars (use config functions to modify)
	group=grp;
	pushed=epushed;
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
	custom_layout_disabled=NULL;

	//own internal vars
	custom_img=NULL;
	ready_to_push=true;
	
	//own elements

	//other
	set_text(txt);
	dirty=true;
}



//destructor
eRadiopush::~eRadiopush()
{
}








//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void eRadiopush::loop()
{
	Mouse& m=Input::get_mouse();
	Keyboard& kbd=Input::get_keyboard();

	if(ready_to_push && m.button(1)==false && kbd.is_down(KEY_SPACE)==false)
		ready_to_push=false;
	
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
void eRadiopush::draw()
{
	//draw pushbutton
	if(customized)
	{
		image->clear(Color(0,0,0,0));

		if(enabled)
		{
			if(custom_img)
				image->blit(0,0,custom_img,false);
		}
		else
		{
			if(custom_layout_disabled)
				image->blit(0,0,custom_layout_disabled,false);
		}
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


//void eRadiopush::on_event(Event* ev){}
void eRadiopush::on_mouse_enter(int mx,int my){}
void eRadiopush::on_mouse_leave(){}
void eRadiopush::on_mouse_move(int mx,int my){}



//***** ON MOUSE DOWN
void eRadiopush::on_mouse_down(int but,int mx,int my)
{
	if(but==1)
		ready_to_push=true;
}



//***** ON MOUSE UP
void eRadiopush::on_mouse_up(int but,int mx,int my)
{
	if(but==1 && ready_to_push)
		set_pushed(!pushed);
		
	ready_to_push=false;
}



//void eRadiopush::on_mouse_click(int but,int mx,int my){}
//void eRadiopush::on_mouse_doubleclick(int but,int mx,int my){}
//void eRadiopush::on_mouse_wheel_down(int mx,int my){}
//void eRadiopush::on_mouse_wheel_up(int mx,int my){}
void eRadiopush::on_mouse_drag_out(){}
void eRadiopush::on_mouse_drag_in(DragPacket* dragpacket){}



//***** ON KEY DOWN
void eRadiopush::on_key_down(Key& key)
{
	if(key.code==KEY_SPACE)
		ready_to_push=true;
}



//***** ON KEY UP
void eRadiopush::on_key_up(Key& key)
{
	if(key.code==KEY_SPACE && ready_to_push)
	{
		set_pushed(!pushed);
		ready_to_push=false;
	}
}



void eRadiopush::on_text(const Str& text){}
void eRadiopush::on_resize(int width,int height){}
void eRadiopush::on_parent_resize(){}
void eRadiopush::on_select(){}
void eRadiopush::on_unselect(){}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//***** SET PUSHED
void eRadiopush::set_pushed(bool push)
{
	//tell other radiopush of the same parent and group to uncheck
	if(parent && !pushed)
	{
		for(int a=0;a<parent->children.size();a++)
		{
			Element* ele=parent->children[a];

			if(ele->type==type && ((eRadiopush*)ele)->group==group)
			{
				((eRadiopush*)ele)->pushed=false;
				ele->dirty=true;
			}
		}
		
		send_event("trigger");
	}
	
	pushed=true;
	dirty=true;
}



//***** SHRINK
void eRadiopush::shrink()
{
	int tw=font->len(text,true)+4;
	int th=font->height()+4;

	resize(tw,th);
}



//***** SET TEXT
void eRadiopush::set_text(const Str& txt,Align::Type align,int offx,int offy)
{
	text=txt;
	text_align=align;
	text_offx=offx;
	text_offy=offy;
	
	show_text=true;
	dirty=true;
}



//***** SET TEX
void eRadiopush::set_tex(Texture* src,Align::Type align,int offx,int offy)
{
	tex=src;
	tex_align=align;
	tex_offx=offx;
	tex_offy=offy;
	
	show_tex=true;
	dirty=true;
}



//***** SET TEX
void eRadiopush::set_tex(const Str& filename,Align::Type align,int offx,int offy)
{
	Texture* t=Texture::cache(filename);
	set_tex(t,align,offx,offy);
}



//***** SHOW TEXT
void eRadiopush::set_show_text(bool show)
{
	show_text=show;
	dirty=true;
}



//***** SHOW TEX
void eRadiopush::set_show_tex(bool show)
{
	show_tex=show;
	dirty=true;
}



//***** SET GROUP
void eRadiopush::set_group(const Str& grp)
{
	group=grp;
	dirty=true;
}



//***** SET CUSTOMIZED
void eRadiopush::set_customized(bool custom)
{
	customized=custom;
	dirty=true;
}



//***** SET CUSTOM
void eRadiopush::set_custom(Texture* lay,Texture* lay_pushed,Texture* lay_hover,Texture* dlay,bool autosize,bool sh_text,bool sh_tex)
{
	custom_layout=lay;
	custom_layout_pushed=lay_pushed;
	custom_layout_hover=lay_hover;
	custom_layout_disabled=dlay;

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
void eRadiopush::set_custom(const Str& lay,const Str& lay_pushed,const Str& lay_hover,const Str& dlay,bool autosize,bool sh_text,bool sh_tex)
{
	set_custom(Texture::cache(lay),Texture::cache(lay_pushed),Texture::cache(lay_hover),Texture::cache(dlay),autosize,sh_text,sh_tex);
}








//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************








