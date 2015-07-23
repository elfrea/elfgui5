#include <pix5.h>
#include "elfgui5.h"



//constructor
ePanel::ePanel(const Str& ename,int ex,int ey,int ew,int eh,bool invert):Element(ename,ex,ey,ew,eh)
{
	//parent class vars
	type="panel";
	
	//own vars
	inverted=invert;

	show_text=false;
	text_align=ALIGN_TOP;
	text="";

	
	draw();
}



//destructor
ePanel::~ePanel()
{
}






//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void ePanel::loop()
{
}



//***** DRAW
void ePanel::draw()
{
	draw_panel(image,inverted,enabled);

	if(show_text)
	{
		if(enabled)
			draw_text_align(image,text_align,0,0,Theme::font::normal,Theme::color::text,text);
		else
			draw_text_align(image,text_align,0,0,Theme::font::normal,Theme::color::d_text,text);
	}
}







//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


void ePanel::on_mouse_enter(int mx,int my){}
void ePanel::on_mouse_leave(){}
void ePanel::on_mouse_move(int mx,int my){}
void ePanel::on_mouse_down(int but,int mx,int my){}
void ePanel::on_mouse_up(int but,int mx,int my){}
void ePanel::on_mouse_click(int but,int mx,int my){}
void ePanel::on_mouse_doubleclick(int but,int mx,int my){}
void ePanel::on_mouse_wheel_down(int mx,int my){}
void ePanel::on_mouse_wheel_up(int mx,int my){}
void ePanel::on_mouse_drag_out(){}
void ePanel::on_mouse_drag_in(DragPacket* dragpacket){}

void ePanel::on_key_down(Key& key){}
void ePanel::on_key_up(Key& key){}
void ePanel::on_text(const Str& text){}

void ePanel::on_resize(int width,int height){}









//****************************************************************
//OWN FUNCTIONS
//****************************************************************

void ePanel::set_text(const Str& txt)
{
	show_text=true;
	text=txt;
	draw();
}



