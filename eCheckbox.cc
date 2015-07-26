#include <pix5.h>
#include "elfgui5.h"



//constructor
eCheckbox::eCheckbox(const Str& ename,int ex,int ey,int ew,int eh,const Str& txt,bool echecked):Element(ename,ex,ey,ew,eh)
{
	#define DEFAULT_CHECK_SIZE 13
	#define DEFAULT_CHECK_OFFSET 3

	//parent class vars
	type="checkbox";
	
	//own config vars
	
	//own internal config vars (use config functions to modify)
	checked=echecked;
	check_size=DEFAULT_CHECK_SIZE;
	check_offset=DEFAULT_CHECK_OFFSET;
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

	//own internal vars
	ready_to_check=false;
	custom_box=NULL;
	custom_mark=NULL;
	
	//own elements

	//other
	set_text(txt);
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

	//check box
	if(custom_box)
	{
		image->clear(Color(0,0,0,0));
		image->blit(0,(h-custom_box->height())/2,custom_box,false);
	}
	else
	{
		draw_edit_panel(image,color,enabled,0,(h-check_size)/2,check_size,check_size);
	}

	//check mark
	if(custom_mark)
	{
		if(checked)
		{
			image->blit(0,(h-custom_mark->height())/2,custom_mark,true);
		}
	}
	else
	{
		if(checked)
		{
			if(enabled)
			{
				image->line(check_offset,(h-check_size)/2+check_offset,check_size-check_offset,(h-check_size)/2+check_size-check_offset,color->text);
				image->line(check_offset,(h-check_size)/2+check_size-check_offset,check_size-check_offset,(h-check_size)/2+check_offset,color->text);
			}
			else
			{
				image->line(check_offset,(h-check_size)/2+check_offset,check_size-check_offset,(h-check_size)/2+check_size-check_offset,color->d_text);
				image->line(check_offset,(h-check_size)/2+check_size-check_offset,check_size-check_offset,(h-check_size)/2+check_offset,color->d_text);
			}
		}
	}
	
	//show tex
	if(show_tex)
		draw_texture_align(image,tex_align,tex_offx,tex_offy,tex);

	//show text
	if(show_text)
	{
		if(enabled)
			draw_text_align(image,text_align,check_size+text_offx,text_offy,font,color->text,text,true);
		else
			draw_text_align(image,text_align,check_size+text_offx,text_offy,font,color->d_text,text,true);
	}


}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//void eCheckbox::on_event(Event* ev){}



void eCheckbox::on_mouse_enter(int mx,int my){}
void eCheckbox::on_mouse_leave(){}
void eCheckbox::on_mouse_move(int mx,int my){}



//***** ON MOUSE DOWN
void eCheckbox::on_mouse_down(int but,int mx,int my)
{
	ready_to_check=true;
}



//***** ON MOUSE UP
void eCheckbox::on_mouse_up(int but,int mx,int my)
{
	if(but==1 && ready_to_check)
	{
		checked=!checked;
		send_event("trigger");

		dirty=true;
	}

	ready_to_check=false;
}



//void eCheckbox::on_mouse_click(int but,int mx,int my){}
//void eCheckbox::on_mouse_doubleclick(int but,int mx,int my){}
//void eCheckbox::on_mouse_wheel_down(int mx,int my){}
//void eCheckbox::on_mouse_wheel_up(int mx,int my){}
void eCheckbox::on_mouse_drag_out(){}
void eCheckbox::on_mouse_drag_in(DragPacket* dragpacket){}
void eCheckbox::on_key_down(Key& key){}
void eCheckbox::on_key_up(Key& key){}
void eCheckbox::on_text(const Str& text){}
void eCheckbox::on_resize(int width,int height){}
void eCheckbox::on_parent_resize(){}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//***** SET TEXT
void eCheckbox::set_text(const Str& txt,Align::Type align,int offx,int offy)
{
	text=txt;
	text_align=align;
	text_offx=offx;
	text_offy=offy;
	
	show_text=true;
	dirty=true;
}



//***** SET TEX
void eCheckbox::set_tex(Texture* src,Align::Type align,int offx,int offy)
{
	tex=src;
	tex_align=align;
	tex_offx=offx;
	tex_offy=offy;
	
	show_tex=true;
	dirty=true;
}


//***** SET TEX
void eCheckbox::set_tex(const Str& filename,Align::Type align,int offx,int offy)
{
	Texture* t=Cache::texture(filename);
	set_tex(t,align,offx,offy);
}



//***** SHOW TEXT
void eCheckbox::set_show_text(bool show)
{
	show_text=show;
	dirty=true;
}



//***** SHOW TEX
void eCheckbox::set_show_tex(bool show)
{
	show_tex=show;
	dirty=true;
}



//***** SET CHECKED
void eCheckbox::set_checked(bool check)
{
	checked=check;
	dirty=true;
}



//***** SET CHECK SIZE
void eCheckbox::set_check_size(int size)
{
	check_size=size;
	dirty=true;
}



//***** SET CHECK OFFSET
void eCheckbox::set_check_offset(int off)
{
	check_offset=off;
	dirty=true;
}



//***** SET CUSTOM
void eCheckbox::set_custom(Texture* box,Texture* mark,bool autosize,bool sh_text)
{
	custom_box=box;
	custom_mark=mark;

	show_text=sh_text;

	//adjust checksize if needed
	if(box)
		check_size=box->width();

	
	//check if we need to resize the checkbox
	if(autosize)
	{
		//set width
		int tw=check_size+(sh_text?text_offx+font->len(text):0);

		//set height
		int th=(sh_text?font->height():(box?box->height():check_size));
		if(box && th<box->height())
			th=box->height();
		if(mark && th<mark->height())
			th=mark->height();

		resize(tw,th);
	}
	dirty=true;
}



//***** SET CUSTOM
void eCheckbox::set_custom(const Str& box,const Str& mark,bool autosize,bool sh_text)
{
	set_custom(Cache::texture(box),Cache::texture(mark),autosize,sh_text);
}








//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************







