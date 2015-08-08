#include <pix5.h>
#include "elfgui5.h"



//constructor
eMenuSeparator::eMenuSeparator(int eh):Element("Menu Separator",0,0,10,eh)
{
	//parent class vars
	type="menu_separator";
	selectable=false;
	
	//own config vars
	
	//own internal config vars (use config functions to modify)

	//own internal vars
	
	//own elements

	//other
	dirty=true;
}



//destructor
eMenuSeparator::~eMenuSeparator()
{
}








//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void eMenuSeparator::loop()
{
}



//***** DRAW
void eMenuSeparator::draw()
{
	image->clear(Color(0,0,0,0));
	draw_panel(image,color,true,enabled,0,(h-2)/2,w,2);
}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//void eMenuSeparator::on_event(Event* ev){}



//***** ON MOUSE ENTER
void eMenuSeparator::on_mouse_enter(int mx,int my)
{
	send_event("close submenu");
}



void eMenuSeparator::on_mouse_leave(){}
void eMenuSeparator::on_mouse_move(int mx,int my){}
void eMenuSeparator::on_mouse_down(int but,int mx,int my){}
void eMenuSeparator::on_mouse_up(int but,int mx,int my){}
//void eMenuSeparator::on_mouse_click(int but,int mx,int my){}
//void eMenuSeparator::on_mouse_doubleclick(int but,int mx,int my){}
//void eMenuSeparator::on_mouse_wheel_down(int mx,int my){}
//void eMenuSeparator::on_mouse_wheel_up(int mx,int my){}
void eMenuSeparator::on_mouse_drag_out(){}
void eMenuSeparator::on_mouse_drag_in(DragPacket* dragpacket,int mx,int my){}
void eMenuSeparator::on_key_down(Key& key){}
void eMenuSeparator::on_key_up(Key& key){}
void eMenuSeparator::on_text(const Str& text){}
void eMenuSeparator::on_resize(int width,int height){}
void eMenuSeparator::on_parent_resize(){}
void eMenuSeparator::on_select(){}
void eMenuSeparator::on_unselect(){}
void eMenuSeparator::on_resolution_change(int width,int height){}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//***** SHRINK
void eMenuSeparator::shrink()
{
	resize(10,h);
}









//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************








