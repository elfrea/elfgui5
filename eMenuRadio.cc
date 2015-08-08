#include <pix5.h>
#include "elfgui5.h"



//constructor
eMenuRadio::eMenuRadio(const Str& ename,int ew,int eh,const Str& etext,const Str& egroup,bool echecked):Element(ename,0,0,ew,eh)
{

	#define DEFAULT_CHECK_SIZE 15
	#define DEFAULT_CHECK_RADIUS 3
	#define DEFAULT_TEXT_OFFSET 3
	
	//parent class vars
	type="menu_radio";
	selectable=false;
	
	//own config vars
	
	//own internal config vars (use config functions to modify)
	text="";
	group=egroup;
	checked=echecked;
	show_text=true;
	show_selection=true;
	
	text_offset=DEFAULT_TEXT_OFFSET;
	check_size=DEFAULT_CHECK_SIZE;
	check_radius=DEFAULT_CHECK_RADIUS;

	//own internal vars
	mouse_on=false;
	
	//own elements

	//other
	set_text(etext);
	dirty=true;
}



//destructor
eMenuRadio::~eMenuRadio()
{
}








//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void eMenuRadio::loop()
{
}



//***** DRAW
void eMenuRadio::draw()
{
	//show bg
	if(mouse_on && show_selection)
		image->clear(color->selection);
	else
		image->clear(Color(0,0,0,0));

	//show box
	image->circle_fill(check_size/2,(check_size/2)+(h-check_size)/2,check_size/2,color->editing);
	image->circle(check_size/2,(check_size/2)+(h-check_size)/2,check_size/2,color->dark);

	//show checkmark
	if(checked)
	{
		if(enabled)
			image->circle_fill(check_size/2,(check_size/2)+(h-check_size)/2,check_radius,color->text);
		else
			image->circle_fill(check_size/2,(check_size/2)+(h-check_size)/2,check_radius,color->d_text);
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


//void eMenuRadio::on_event(Event* ev){}



//***** ON MOUSE ENTER
void eMenuRadio::on_mouse_enter(int mx,int my)
{
	mouse_on=true;
	dirty=true;
	send_event("close submenu");
}



//***** ON MOUSE LEAVE
void eMenuRadio::on_mouse_leave()
{
	mouse_on=false;
	dirty=true;
}



void eMenuRadio::on_mouse_move(int mx,int my){}



//***** ON MOUSE DOWN
void eMenuRadio::on_mouse_down(int but,int mx,int my)
{
	if(but==1)
	{
		set_checked(!checked);
	}
}



void eMenuRadio::on_mouse_up(int but,int mx,int my){}
//void eMenuRadio::on_mouse_click(int but,int mx,int my){}
//void eMenuRadio::on_mouse_doubleclick(int but,int mx,int my){}
//void eMenuRadio::on_mouse_wheel_down(int mx,int my){}
//void eMenuRadio::on_mouse_wheel_up(int mx,int my){}
void eMenuRadio::on_mouse_drag_out(){}
void eMenuRadio::on_mouse_drag_in(DragPacket* dragpacket,int mx,int my){}
void eMenuRadio::on_key_down(Key& key){}
void eMenuRadio::on_key_up(Key& key){}
void eMenuRadio::on_text(const Str& text){}
void eMenuRadio::on_resize(int width,int height){}
void eMenuRadio::on_parent_resize(){}
void eMenuRadio::on_select(){}
void eMenuRadio::on_unselect(){}
void eMenuRadio::on_resolution_change(int width,int height){}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//***** SHRINK
void eMenuRadio::shrink()
{
	int width=check_size;
	if(show_text)
		width+=text_offset+font->len(text);
	
	resize(width,h);
}



//***** SET TEXT
void eMenuRadio::set_text(const Str& txt)
{
	text=txt;
	show_text=true;
	dirty=true;
}



//***** SET GROUP
void eMenuRadio::set_group(const Str& grp)
{
	group=grp;
	dirty=true;
}



//***** SHOW TEXT
void eMenuRadio::set_show_text(bool show)
{
	show_text=show;
	dirty=true;
}



//***** SET CHECKED
void eMenuRadio::set_checked(bool check)
{
	//tell other radiobuttons of the same parent and group to uncheck
	if(parent && !checked)
	{
		for(int a=0;a<parent->children.size();a++)
		{
			Element* ele=parent->children[a];

			if(ele->type==type && ((eMenuRadio*)ele)->group==group)
			{
				((eMenuRadio*)ele)->checked=false;
				ele->dirty=true;
			}
		}
	
		send_event("trigger");
	}

	checked=true;
	dirty=true;
}



//***** SET TEXT OFFSET
void eMenuRadio::set_text_offset(int off)
{
	text_offset=off;
	dirty=true;
}



//***** SET CHECK SIZE
void eMenuRadio::set_check_size(int sz)
{
	check_size=sz;
	dirty=true;
}



//***** SET CHECK RADIUS
void eMenuRadio::set_check_radius(int radius)
{
	check_radius=radius;
	dirty=true;
}









//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************








