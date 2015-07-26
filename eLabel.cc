#include <pix5.h>
#include "elfgui5.h"



//constructor
eLabel::eLabel(const Str& ename,int ex,int ey,int ew,int eh,const Str& txt):Element(ename,ex,ey,ew,eh)
{
	//parent class vars
	type="label";
	
	//own config vars
	
	//own internal config vars (use config functions to modify)
	text_align=Align::Middle;
	text_offx=0;
	text_offy=0;
	text="";

	//own internal vars
	
	//own elements

	//other
	set_text(txt);
	dirty=true;
}



//destructor
eLabel::~eLabel()
{
}








//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void eLabel::loop()
{
}



//***** DRAW
void eLabel::draw()
{
	image->clear(Color(0,0,0,0));
	//show text
	if(enabled)
		draw_text_align(image,text_align,text_offx,text_offy,font,color->text,text,true);
	else
		draw_text_align(image,text_align,text_offx,text_offy,font,color->d_text,text,true);
}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//void eLabel::on_event(Event* ev){}
void eLabel::on_mouse_enter(int mx,int my){}
void eLabel::on_mouse_leave(){}
void eLabel::on_mouse_move(int mx,int my){}
void eLabel::on_mouse_down(int but,int mx,int my){}
void eLabel::on_mouse_up(int but,int mx,int my){}
//void eLabel::on_mouse_click(int but,int mx,int my){}
//void eLabel::on_mouse_doubleclick(int but,int mx,int my){}
//void eLabel::on_mouse_wheel_down(int mx,int my){}
//void eLabel::on_mouse_wheel_up(int mx,int my){}
void eLabel::on_mouse_drag_out(){}
void eLabel::on_mouse_drag_in(DragPacket* dragpacket){}
void eLabel::on_key_down(Key& key){}
void eLabel::on_key_up(Key& key){}
void eLabel::on_text(const Str& text){}
void eLabel::on_resize(int width,int height){}
void eLabel::on_parent_resize(){}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//***** SET TEXT
void eLabel::set_text(const Str& txt,bool autosize,Align::Type align,int offx,int offy)
{
	text=txt;
	text_align=align;
	text_offx=offx;
	text_offy=offy;

	//resize label if autosize is enabled
	if(autosize)
	{
		int tw=font->len(text,true)+offx;
		int th=font->height()+offy;

		resize(tw,th);
	}
	
	dirty=true;
}








//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************







