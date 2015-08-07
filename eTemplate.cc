#include <pix5.h>
#include "elfgui5.h"



//constructor
eTemplate::eTemplate(const Str& ename,int ex,int ey,int ew,int eh):Element(ename,ex,ey,ew,eh)
{
	//parent class vars
	type="template";
	selectable=false;
	
	//own config vars
	
	//own internal config vars (use config functions to modify)

	//own internal vars
	
	//own elements

	//other
	dirty=true;
}



//destructor
eTemplate::~eTemplate()
{
}








//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void eTemplate::loop()
{
}



//***** DRAW
void eTemplate::draw()
{
	image->clear(Color(0,0,0,0));
}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//void eTemplate::on_event(Event* ev){}
void eTemplate::on_mouse_enter(int mx,int my){}
void eTemplate::on_mouse_leave(){}
void eTemplate::on_mouse_move(int mx,int my){}
void eTemplate::on_mouse_down(int but,int mx,int my){}
void eTemplate::on_mouse_up(int but,int mx,int my){}
//void eTemplate::on_mouse_click(int but,int mx,int my){}
//void eTemplate::on_mouse_doubleclick(int but,int mx,int my){}
//void eTemplate::on_mouse_wheel_down(int mx,int my){}
//void eTemplate::on_mouse_wheel_up(int mx,int my){}
void eTemplate::on_mouse_drag_out(){}
void eTemplate::on_mouse_drag_in(DragPacket* dragpacket,int mx,int my){}
void eTemplate::on_key_down(Key& key){}
void eTemplate::on_key_up(Key& key){}
void eTemplate::on_text(const Str& text){}
void eTemplate::on_resize(int width,int height){}
void eTemplate::on_parent_resize(){}
void eTemplate::on_select(){}
void eTemplate::on_unselect(){}
void eTemplate::on_resolution_change(int width,int height){}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//***** SHRINK
void eTemplate::shrink()
{
}








//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************






