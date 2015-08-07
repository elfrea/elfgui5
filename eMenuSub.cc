#include <pix5.h>
#include "elfgui5.h"



//constructor
eMenuSub::eMenuSub(const Str& ename,int ew,int eh,const Str& etext,eMenu* elink):Element(ename,0,0,ew,eh)
{
	//parent class vars
	type="menu_sub";
	selectable=false;
	
	//own config vars
	text=etext;
	link=elink;
	
	//own internal config vars (use config functions to modify)

	//own internal vars
	
	//own elements

	//other
	dirty=true;
}



//destructor
eMenuSub::~eMenuSub()
{
	if(!link->parent)
		delete link;
}








//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void eMenuSub::loop()
{
}



//***** DRAW
void eMenuSub::draw()
{
	draw_panel(image,color,false,enabled);
}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//void eMenuSub::on_event(Event* ev){}
void eMenuSub::on_mouse_enter(int mx,int my){}
void eMenuSub::on_mouse_leave(){}
void eMenuSub::on_mouse_move(int mx,int my){}



//***** ON MOUSE DOWN
void eMenuSub::on_mouse_down(int but,int mx,int my)
{
	if(but==1)
		send_event("open submenu");
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
}








//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************








