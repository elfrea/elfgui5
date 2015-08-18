#include <pix5.h>
#include "elfgui5.h"



//constructor
eMenuSub::eMenuSub(const Str& ename,int ew,int eh,const Str& etext,eMenu* elink):Element(ename,0,0,ew,eh)
{

	#define DEFAULT_MENU_DELAY 500

	//parent class vars
	type="menu_sub";
	selectable=false;
	
	//own config vars
	text=etext;
	link=elink;
	
	//own internal config vars (use config functions to modify)
	show_selection=true;

	//own internal vars
	arrow=Texture::cache("gfx/elements/arrow_right.png");
	mouseon=false;
	menu_delay=DEFAULT_MENU_DELAY;
	menu_timer=0;
	
	//own elements

	//other
	dirty=true;
}



//destructor
eMenuSub::~eMenuSub()
{
	if(link)
		delete link;
}








//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void eMenuSub::loop()
{
	if(mouseon)
	{
		int64_t ms=get_ms();
		if(ms>=menu_timer+menu_delay)
		{
			menu_timer=ms;
			if(!link->is_open)
				send_event("open submenu");
		}
	}

	if(!link->parent)
		link->is_open=false;
}



//***** DRAW
void eMenuSub::draw()
{
	if(mouseon && show_selection)
		image->clear(color->selection);
	else
		image->clear(Color(0,0,0,0));

	//show text
	if(enabled)
		draw_text_align(image,Align::Left,0,0,font,color->text,text);
	else
		draw_text_align(image,Align::Left,0,0,font,color->d_text,text);

	//show arrow icon
	image->blit(w-arrow->width(),(h-arrow->height())/2,arrow);
}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//void eMenuSub::on_event(Event* ev){}



//***** ON MOUSE ENTER
void eMenuSub::on_mouse_enter(int mx,int my)
{
	menu_timer=get_ms();
	mouseon=true;
	dirty=true;
}



//***** ON MOUSE LEAVE
void eMenuSub::on_mouse_leave()
{
	mouseon=false;
	dirty=true;
}



void eMenuSub::on_mouse_move(int mx,int my){}



//***** ON MOUSE DOWN
void eMenuSub::on_mouse_down(int but,int mx,int my)
{
	if(but==1)
	{
		menu_timer=get_ms();

		if(!link->is_open)
			send_event("open submenu");
	}
}



void eMenuSub::on_mouse_up(int but,int mx,int my){}
//void eMenuSub::on_mouse_click(int but,int mx,int my){}
//void eMenuSub::on_mouse_doubleclick(int but,int mx,int my){}
//void eMenuSub::on_mouse_wheel_down(int mx,int my){}
//void eMenuSub::on_mouse_wheel_up(int mx,int my){}
void eMenuSub::on_mouse_drag_out(){}
void eMenuSub::on_mouse_drag_in(DragPacket* dragpacket,int mx,int my){}
void eMenuSub::on_key_down(Key& key){}
void eMenuSub::on_key_up(Key& key){}
void eMenuSub::on_text(const Str& text){}
void eMenuSub::on_resize(int width,int height){}
void eMenuSub::on_parent_resize(){}
void eMenuSub::on_select(){}
void eMenuSub::on_unselect(){}
void eMenuSub::on_resolution_change(int width,int height){}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//***** SHRINK
void eMenuSub::shrink()
{
	resize(font->len(text)+10+arrow->width(),h);
}



//***** SET TEXT
void eMenuSub::set_text(const Str& txt)
{
	text=txt;
	dirty=true;
}



//***** SHOW SELECTION
void eMenuSub::set_show_selection(bool show)
{
	show_selection=show;
	dirty=true;
}








//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************








