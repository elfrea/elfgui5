#include <pix5.h>
#include "elfgui5.h"



//constructor
eTabbox::eTabbox(const Str& ename,int ex,int ey,int ew,int eh):Element(ename,ex,ey,ew,eh)
{
	//parent class vars
	type="tabbox";
	selectable=false;
	
	//own config vars
	
	//own internal config vars (use config functions to modify)

	//own internal vars
	
	//own elements

	//other
	dirty=true;
}



//destructor
eTabbox::~eTabbox()
{
}








//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void eTabbox::loop()
{
}



//***** DRAW
void eTabbox::draw()
{
	image->clear(Color(0,0,0,0));
}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//void eTabbox::on_event(Event* ev){}
void eTabbox::on_mouse_enter(int mx,int my){}
void eTabbox::on_mouse_leave(){}
void eTabbox::on_mouse_move(int mx,int my){}
void eTabbox::on_mouse_down(int but,int mx,int my){}
void eTabbox::on_mouse_up(int but,int mx,int my){}
//void eTabbox::on_mouse_click(int but,int mx,int my){}
//void eTabbox::on_mouse_doubleclick(int but,int mx,int my){}
//void eTabbox::on_mouse_wheel_down(int mx,int my){}
//void eTabbox::on_mouse_wheel_up(int mx,int my){}
void eTabbox::on_mouse_drag_out(){}
void eTabbox::on_mouse_drag_in(DragPacket* dragpacket){}
void eTabbox::on_key_down(Key& key){}
void eTabbox::on_key_up(Key& key){}
void eTabbox::on_text(const Str& text){}
void eTabbox::on_resize(int width,int height){}
void eTabbox::on_parent_resize(){}
void eTabbox::on_select(){}
void eTabbox::on_unselect(){}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************








//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************







