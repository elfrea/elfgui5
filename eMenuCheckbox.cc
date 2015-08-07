#include <pix5.h>
#include "elfgui5.h"



//constructor
eMenuCheckbox::eMenuCheckbox(const Str& ename,int ew,int eh,const Str& etext,bool echecked):Element(ename,0,0,ew,eh)
{

	#define DEFAULT_CHECK_SIZE 13
	#define DEFAULT_CHECK_OFFSET 3
	#define DEFAULT_TEXT_OFFSET 3

	//parent class vars
	type="menu_checkbox";
	selectable=false;
	
	//own config vars
	
	//own internal config vars (use config functions to modify)
	text="";
	checked=echecked;
	show_text=true;
	show_selection=true;

	text_offset=DEFAULT_TEXT_OFFSET;
	check_size=DEFAULT_CHECK_SIZE;
	check_offset=DEFAULT_CHECK_OFFSET;

	//own internal vars
	mouse_on=false;
	
	//own elements

	//other
	set_text(etext);
	dirty=true;
}



//destructor
eMenuCheckbox::~eMenuCheckbox()
{
}








//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void eMenuCheckbox::loop()
{
}



//***** DRAW
void eMenuCheckbox::draw()
{
	
	//show bg
	if(mouse_on && show_selection)
		image->clear(color->selection);
	else
		image->clear(Color(0,0,0,0));

	//show box
	draw_edit_panel(image,color,enabled,0,(h-check_size)/2,check_size,check_size);

	//show checkmark
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

	//show text
	if(show_text)
	{
		if(enabled)
			draw_text_align(image,Align::Left,check_size+text_offset,0,font,color->text,text);
		else
			draw_text_align(image,Align::Left,check_size+text_offset,0,font,color->d_text,text);
	}
}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//void eMenuCheckbox::on_event(Event* ev){}



//***** ON MOUSE ENTER
void eMenuCheckbox::on_mouse_enter(int mx,int my)
{
	mouse_on=true;
	dirty=true;
}



//***** ON MOUSE LEAVE
void eMenuCheckbox::on_mouse_leave()
{
	mouse_on=false;
	dirty=true;
}



void eMenuCheckbox::on_mouse_move(int mx,int my){}



//***** ON MOUSE DOWN
void eMenuCheckbox::on_mouse_down(int but,int mx,int my)
{
	if(but==1)
	{
		set_checked(!checked);
	}
}



void eMenuCheckbox::on_mouse_up(int but,int mx,int my){}
//void eMenuCheckbox::on_mouse_click(int but,int mx,int my){}
//void eMenuCheckbox::on_mouse_doubleclick(int but,int mx,int my){}
//void eMenuCheckbox::on_mouse_wheel_down(int mx,int my){}
//void eMenuCheckbox::on_mouse_wheel_up(int mx,int my){}
void eMenuCheckbox::on_mouse_drag_out(){}
void eMenuCheckbox::on_mouse_drag_in(DragPacket* dragpacket,int mx,int my){}
void eMenuCheckbox::on_key_down(Key& key){}
void eMenuCheckbox::on_key_up(Key& key){}
void eMenuCheckbox::on_text(const Str& text){}
void eMenuCheckbox::on_resize(int width,int height){}
void eMenuCheckbox::on_parent_resize(){}
void eMenuCheckbox::on_select(){}
void eMenuCheckbox::on_unselect(){}
void eMenuCheckbox::on_resolution_change(int width,int height){}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//***** SHRINK
void eMenuCheckbox::shrink()
{
	int width=check_size;
	if(show_text)
		width+=text_offset+font->len(text);
	
	resize(width,h);
}



//***** SET TEXT
void eMenuCheckbox::set_text(const Str& txt)
{
	text=txt;
	show_text=true;
	dirty=true;
}



//***** SHOW TEXT
void eMenuCheckbox::set_show_text(bool show)
{
	show_text=show;
	dirty=true;
}



//***** SET CHECKED
void eMenuCheckbox::set_checked(bool check)
{
	checked=check;
	send_event("trigger");
	dirty=true;
}



//***** SET TEXT OFFSET
void eMenuCheckbox::set_text_offset(int off)
{
	text_offset=off;
	dirty=true;
}



//***** SET CHECK SIZE
void eMenuCheckbox::set_check_size(int sz)
{
	check_size=sz;
	dirty=true;
}



//***** SET CHECK OFFSET
void eMenuCheckbox::set_check_offset(int off)
{
	check_offset=off;
	dirty=true;
}








//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************








