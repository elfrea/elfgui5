#include <pix5.h>
#include "elfgui5.h"



//constructor
eCheckbox::eCheckbox(const Str& ename,int ex,int ey,int ew,int eh,const Str& txt,bool echecked,bool autosize):Element(ename,ex,ey,ew,eh)
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
	custom_box_disabled=NULL;
	
	//own elements

	//other
	set_text(txt,Align::Left,4,0,autosize);
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
	Keyboard& kbd=Input::get_keyboard();

	if(ready_to_check && m.button(1)==false && kbd.is_down(KEY_SPACE)==false)
		ready_to_check=false;
}



//***** DRAW
void eCheckbox::draw()
{

	image->clear(Color(0,0,0,0));

	//check box
	if(custom_box)
	{
		if(enabled)
			image->blit(0,(h-custom_box->height())/2,custom_box,false);
		else
			image->blit(0,(h-custom_box_disabled->height())/2,custom_box_disabled,false);
	}
	else
		draw_edit_panel(image,color,enabled,0,(h-check_size)/2,check_size,check_size);

	//check mark
	if(custom_mark)
	{
		if(checked)
			image->blit(0,(h-custom_mark->height())/2,custom_mark,true);
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


	//selected
	if(selected)
		draw_dotted_box(image,0,0,w,h,color->dark,1,1);

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
		set_checked(!checked);

	ready_to_check=false;
}



//void eCheckbox::on_mouse_click(int but,int mx,int my){}
//void eCheckbox::on_mouse_doubleclick(int but,int mx,int my){}
//void eCheckbox::on_mouse_wheel_down(int mx,int my){}
//void eCheckbox::on_mouse_wheel_up(int mx,int my){}
void eCheckbox::on_mouse_drag_out(){}
void eCheckbox::on_mouse_drag_in(DragPacket* dragpacket,int mx,int my){}



//***** ON KEY DOWN
void eCheckbox::on_key_down(Key& key)
{
	if(key.code==KEY_SPACE)
		ready_to_check=true;
}



//***** ON KEY UP
void eCheckbox::on_key_up(Key& key)
{
	if(key.code==KEY_SPACE && ready_to_check)
	{
		set_checked(!checked);
		ready_to_check=false;
	}
}



void eCheckbox::on_text(const Str& text){}
void eCheckbox::on_resize(int width,int height){}
void eCheckbox::on_parent_resize(){}
void eCheckbox::on_select(){}
void eCheckbox::on_unselect(){}
void eCheckbox::on_resolution_change(int width,int height){}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//***** SHRINK
void eCheckbox::shrink()
{
	//set width
	int tw=check_size+(show_text?text_offx+font->len(text):0);

	//set height
	int th=(show_text?font->height():check_size);
	if(th<check_size)
		th=check_size;
	if(custom_box && th<custom_box->height())
		th=custom_box->height();
	if(custom_mark && th<custom_mark->height())
		th=custom_mark->height();

	resize(tw,th);
}



//***** SET TEXT
void eCheckbox::set_text(const Str& txt,Align::Type align,int offx,int offy,bool autosize)
{
	text=txt;
	text_align=align;
	text_offx=offx;
	text_offy=offy;

	if(autosize)
		shrink();
	
	show_text=true;
	dirty=true;
}



//***** SET TEX
void eCheckbox::set_tex(Texture* src,Align::Type align,int offx,int offy,bool autosize)
{
	tex=src;
	tex_align=align;
	tex_offx=offx;
	tex_offy=offy;
	
	if(autosize)
		shrink();
	
	show_tex=true;
	dirty=true;
}


//***** SET TEX
void eCheckbox::set_tex(const Str& filename,Align::Type align,int offx,int offy,bool autosize)
{
	Texture* t=Texture::cache(filename);
	set_tex(t,align,offx,offy);
	
	if(autosize)
		shrink();
	
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
	send_event("trigger");
	dirty=true;
}



//***** SET CHECK SIZE
void eCheckbox::set_check_size(int size,bool autosize)
{
	check_size=size;
	if(autosize)
		shrink();
		
	dirty=true;
}



//***** SET CHECK OFFSET
void eCheckbox::set_check_offset(int off)
{
	check_offset=off;
	dirty=true;
}



//***** SET CUSTOM
void eCheckbox::set_custom(Texture* box,Texture* mark,Texture* dbox,bool autosize,bool sh_text)
{
	custom_box=box;
	custom_mark=mark;
	custom_box_disabled=dbox;

	show_text=sh_text;

	//adjust checksize if needed
	if(box)
		check_size=box->width();

	
	//check if we need to resize the checkbox
	if(autosize)
		shrink();

	dirty=true;
}



//***** SET CUSTOM
void eCheckbox::set_custom(const Str& box,const Str& mark,const Str& dbox,bool autosize,bool sh_text)
{
	set_custom(Texture::cache(box),Texture::cache(mark),Texture::cache(dbox),autosize,sh_text);
}








//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************







