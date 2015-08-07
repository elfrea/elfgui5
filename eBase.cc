#include <pix5.h>
#include "elfgui5.h"



//constructor
eBase::eBase(const Str& ename,int ex,int ey,int ew,int eh):Element(ename,ex,ey,ew,eh)
{
	//parent class vars
	type="base";
	
	//own config vars
	selectable=false;
	
	//own internal config vars (use config functions to modify)
	use_bgcolor=true;
	bgcolor=Color::ubyte(30,60,100);

	//own internal vars
	
	//own elements
	cmenu3=new eMenu("base context menu submenu2",10,10,10,10,NULL);
		cmenu3->add_button("base context menu submenu2 test button",10,20,"This is yet another test");
		cmenu3->add_separator();
	cmenu2=new eMenu("base context menu submenu",10,10,10,10,NULL);
		cmenu2->add_button("base context menu submenu test button",10,20,"This is another test");
		cmenu2->add_separator();
		cmenu2->add_sub("base context menu test submenu2",10,20,"Test Submenu2",cmenu3);
	cmenu=new eMenu("base context menu",10,10,10,10,this);
		cmenu->add_button("base context menu test button",10,20,"This is a test");
		cmenu->add_separator();
		cmenu->add_sub("base context menu test submenu",10,20,"Test Submenu",cmenu2);

	//other
	set_context_menu(cmenu);
	dirty=true;
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


//void eBase::on_event(Event* ev){}
void eBase::on_mouse_enter(int mx,int my){}
void eBase::on_mouse_leave(){}
void eBase::on_mouse_move(int mx,int my){}
void eBase::on_mouse_down(int but,int mx,int my){}
void eBase::on_mouse_up(int but,int mx,int my){}
//void eBase::on_mouse_click(int but,int mx,int my){}
//void eBase::on_mouse_doubleclick(int but,int mx,int my){}
//void eBase::on_mouse_wheel_down(int mx,int my){}
//void eBase::on_mouse_wheel_up(int mx,int my){}
void eBase::on_mouse_drag_out(){}



//*****
void eBase::on_mouse_drag_in(DragPacket* dragpacket,int mx,int my)
{

	//Drag and drop from a tabbox
	if(dragpacket->command=="#move tab")
	{
		eTabbox* tabbox=((eTabbox*)dragpacket->sender);
		tabbox->undock_tab((eTab*)dragpacket->element,(Element*)this,mx,my);
	}
}



void eBase::on_key_down(Key& key){}
void eBase::on_key_up(Key& key){}
void eBase::on_text(const Str& text){}
void eBase::on_resize(int width,int height){}
void eBase::on_parent_resize(){}
void eBase::on_select(){}
void eBase::on_unselect(){}
void eBase::on_resolution_change(int width,int height){}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//***** SHRINK
void eBase::shrink()
{
}








//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************





