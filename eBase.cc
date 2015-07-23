#include <pix5.h>
#include "elfgui5.h"



//constructor
eBase::eBase(const Str& ename,int ex,int ey,int ew,int eh):Element(ename,ex,ey,ew,eh)
{
	//parent class vars
	type="base";
	
	//own vars
	use_bgcolor=true;
	bgcolor=Color::ubyte(30,60,100);
	

	
	draw();
}



//destructor
eBase::~eBase()
{
}






//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void eBase::loop()
{
}



//***** DRAW
void eBase::draw()
{
	if(use_bgcolor)
		image->clear(bgcolor);
}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


void eBase::on_mouse_enter(int mx,int my){}
void eBase::on_mouse_leave(){}
void eBase::on_mouse_move(int mx,int my){}
void eBase::on_mouse_down(int but,int mx,int my){}
void eBase::on_mouse_up(int but,int mx,int my){}
void eBase::on_mouse_click(int but,int mx,int my){}
void eBase::on_mouse_doubleclick(int but,int mx,int my){}
void eBase::on_mouse_wheel_down(int mx,int my){}
void eBase::on_mouse_wheel_up(int mx,int my){}
void eBase::on_mouse_drag_out(){}
void eBase::on_mouse_drag_in(DragPacket* dragpacket){}

void eBase::on_key_down(Key& key){}
void eBase::on_key_up(Key& key){}
void eBase::on_text(const Str& text){}

void eBase::on_resize(int width,int height){}







