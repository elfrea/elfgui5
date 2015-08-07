#include <pix5.h>
#include "elfgui5.h"



//constructor
eModal::eModal(const Str& ename,int ex,int ey,int ew,int eh,bool eclose_with_mouse,bool tint,Element* elink):Element(ename,ex,ey,ew,eh)
{
	//parent class vars
	type="modal";
	selectable=true;
	always_on_top=true;
	visible=false;
	use_tint=tint;
	do_not_draw=!tint;
	do_not_hide_elements_under=true;
	
	//own config vars
	close_with_mouse=eclose_with_mouse;
	link=elink;
	
	//own internal config vars (use config functions to modify)

	//own internal vars
	
	//own elements

	//other
	dirty=true;
}



//destructor
eModal::~eModal()
{
}








//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void eModal::loop()
{
}



//***** DRAW
void eModal::draw()
{
	image->clear(Color::ubyte(255,255,255,255));
}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//***** ON EVENT
void eModal::on_event(Event* ev)
{
	//forward event to link
	if(link)
		send_event_to(link,ev);

	//forward to parent
	else
		send_event(ev);
}



void eModal::on_mouse_enter(int mx,int my){}
void eModal::on_mouse_leave(){}
void eModal::on_mouse_move(int mx,int my){}



//***** ON MOUSE DOWN
void eModal::on_mouse_down(int but,int mx,int my)
{
	if(close_with_mouse)
		close();
}



void eModal::on_mouse_up(int but,int mx,int my){}
//void eModal::on_mouse_click(int but,int mx,int my){}
//void eModal::on_mouse_doubleclick(int but,int mx,int my){}
//void eModal::on_mouse_wheel_down(int mx,int my){}
//void eModal::on_mouse_wheel_up(int mx,int my){}
void eModal::on_mouse_drag_out(){}
void eModal::on_mouse_drag_in(DragPacket* dragpacket,int mx,int my){}
void eModal::on_key_down(Key& key){}
void eModal::on_key_up(Key& key){}
void eModal::on_text(const Str& text){}
void eModal::on_resize(int width,int height){}
void eModal::on_parent_resize(){}
void eModal::on_select(){}
void eModal::on_unselect(){}



//***** ON RESOLUTION CHANGE
void eModal::on_resolution_change(int width,int height)
{
	resize(width,height);
}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//***** SHRINK
void eModal::shrink()
{
}



//***** OPEN
void eModal::open()
{
	visible=true;
	ElfGui5::base->add_child(this);
	set_as_selected(true);

	ElfGui5::event_handler.on_mouse_move(Input::get_mouse());
}



//***** CLOSE
void eModal::close()
{
	clear_children(false);
	visible=false;
	ElfGui5::base->remove_child(this,false);
	send_event_to(link,"close");
	if(link)
		link->set_as_selected(true);
	else
		set_as_selected(false);

	ElfGui5::event_handler.on_mouse_move(Input::get_mouse());
}







//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************







