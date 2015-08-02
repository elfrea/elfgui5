#include <pix5.h>
#include "elfgui5.h"



//constructor
eTimer::eTimer(const Str& ename,int64_t edelay,bool enable):Element(ename,0,0,10,10)
{
	//parent class vars
	type="timer";
	visible=false;
	selectable=false;
	enabled=enable;
	
	//own config vars
	delay=edelay;
	
	//own internal config vars (use config functions to modify)
	timer=0;

	//own internal vars
	
	//own elements

	//other
	dirty=true;
}



//destructor
eTimer::~eTimer()
{
}








//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void eTimer::loop()
{
	int64_t ms=get_ms();

	if(ms>=timer+delay)
	{
		timer=ms;
		send_event("trigger");
	}
}



//***** DRAW
void eTimer::draw()
{
}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//void eTimer::on_event(Event* ev){}
void eTimer::on_mouse_enter(int mx,int my){}
void eTimer::on_mouse_leave(){}
void eTimer::on_mouse_move(int mx,int my){}
void eTimer::on_mouse_down(int but,int mx,int my){}
void eTimer::on_mouse_up(int but,int mx,int my){}
//void eTimer::on_mouse_click(int but,int mx,int my){}
//void eTimer::on_mouse_doubleclick(int but,int mx,int my){}
//void eTimer::on_mouse_wheel_down(int mx,int my){}
//void eTimer::on_mouse_wheel_up(int mx,int my){}
void eTimer::on_mouse_drag_out(){}
void eTimer::on_mouse_drag_in(DragPacket* dragpacket,int mx,int my){}
void eTimer::on_key_down(Key& key){}
void eTimer::on_key_up(Key& key){}
void eTimer::on_text(const Str& text){}
void eTimer::on_resize(int width,int height){}
void eTimer::on_parent_resize(){}
void eTimer::on_select(){}
void eTimer::on_unselect(){}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************








//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************







