#include <pix5.h>
#include "elfgui5.h"



//constructor
eTab::eTab(const Str& ename):Element(ename,0,0,10,10)
{
	//parent class vars
	type="tab";
	selectable=false;
	
	//own config vars
	
	//own internal config vars (use config functions to modify)

	//own internal vars
	
	//own elements

	//other
	dirty=true;
}



//destructor
eTab::~eTab()
{
}








//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void eTab::loop()
{
}



//***** DRAW
void eTab::draw()
{
	image->clear(Color(0,0,0,0));
}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//void eTab::on_event(Event* ev){}
void eTab::on_mouse_enter(int mx,int my){}
void eTab::on_mouse_leave(){}
void eTab::on_mouse_move(int mx,int my){}
void eTab::on_mouse_down(int but,int mx,int my){}
void eTab::on_mouse_up(int but,int mx,int my){}
//void eTab::on_mouse_click(int but,int mx,int my){}
//void eTab::on_mouse_doubleclick(int but,int mx,int my){}
//void eTab::on_mouse_wheel_down(int mx,int my){}
//void eTab::on_mouse_wheel_up(int mx,int my){}
void eTab::on_mouse_drag_out(){}
void eTab::on_mouse_drag_in(DragPacket* dragpacket,int mx,int my){}
void eTab::on_key_down(Key& key){}
void eTab::on_key_up(Key& key){}
void eTab::on_text(const Str& text){}
void eTab::on_resize(int width,int height){}
void eTab::on_parent_resize(){}
void eTab::on_select(){}
void eTab::on_unselect(){}
void eTab::on_resolution_change(int width,int height){}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//***** SHRINK
void eTab::shrink()
{
}









//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************







