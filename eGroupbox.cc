#include <pix5.h>
#include "elfgui5.h"



//constructor
eGroupbox::eGroupbox(const Str& ename,int ex,int ey,int ew,int eh,const Str& txt):Element(ename,ex,ey,ew,eh)
{
	//parent class vars
	type="groupbox";
	
	//own config vars
	
	//own internal config vars (use config functions to modify)
	appearance=GroupboxAppearance::Panel3D;
	show_text=true;

	text_align=Align::Top;
	text_offx=0;
	text_offy=0;
	text="";

	//own internal vars
	box_offy=font->height()/2;
	
	//own elements

	//other
	set_text(txt);
	dirty=true;
}



//destructor
eGroupbox::~eGroupbox()
{
}








//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void eGroupbox::loop()
{
}



//***** DRAW
void eGroupbox::draw()
{
	
	//set box offset
	box_offy=font->height()/2;

	//show box
	switch(appearance)
	{
		//PLAIN
		case GroupboxAppearance::Plain:
			image->clear(color->medium);
		break;
		
		//SINGLE
		case GroupboxAppearance::Single:
			image->clear(color->medium);
			image->rect(0,box_offy,w-2,h-2,color->dark);
		break;
		
		//DOUBLE
		case GroupboxAppearance::Double:
			image->clear(color->medium);
			image->rect(1,box_offy+1,w-3,h-3,color->light);
			image->rect(0,box_offy,w-2,h-2,color->dark);
		break;
		
		//TRIPLE
		case GroupboxAppearance::Triple:
			image->clear(color->medium);
			image->rect(0,box_offy,w-2,h-2,color->dark);
			image->rect(1,box_offy+1,w-3,h-3,color->light);
			image->rect(2,box_offy+2,w-4,h-4,color->dark);
		break;
		
		//PANEL3D
		case GroupboxAppearance::Panel3D:
			image->clear(color->medium);
			image->rect(1,box_offy+1,w-2,h-2,color->light);
			image->rect(0,box_offy,w-3,h-3,color->dark);
		break;
		
		//PANEL
		case GroupboxAppearance::Panel:
			draw_panel(image,color,false);
		break;
		
		//INVERTED PANEL
		case GroupboxAppearance::InvertedPanel:
			draw_panel(image,color,true);
		break;
	}


	//show text
	if(show_text)
	{
		int tw=font->len(text,true)+10;
		int th=box_offy*2;
		int tx=(w-tw)/2;
		int ty=0;

		if(enabled)
		{
			image->rect_fill(tx,ty,tx+tw-1,ty+th-1,color->medium);
			draw_text_align(image,text_align,text_offx,text_offy,font,color->text,text);
		}
		else
		{
			image->rect_fill(tx,ty,tw-1,th-1,color->d_medium);
			draw_text_align(image,text_align,text_offx,text_offy,font,color->d_text,text);
		}
	}
	
}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//void eGroupbox::on_event(Event* ev){}
void eGroupbox::on_mouse_enter(int mx,int my){}
void eGroupbox::on_mouse_leave(){}
void eGroupbox::on_mouse_move(int mx,int my){}
void eGroupbox::on_mouse_down(int but,int mx,int my){}
void eGroupbox::on_mouse_up(int but,int mx,int my){}
//void eGroupbox::on_mouse_click(int but,int mx,int my){}
//void eGroupbox::on_mouse_doubleclick(int but,int mx,int my){}
//void eGroupbox::on_mouse_wheel_down(int mx,int my){}
//void eGroupbox::on_mouse_wheel_up(int mx,int my){}
void eGroupbox::on_mouse_drag_out(){}
void eGroupbox::on_mouse_drag_in(DragPacket* dragpacket){}
void eGroupbox::on_key_down(Key& key){}
void eGroupbox::on_key_up(Key& key){}
void eGroupbox::on_text(const Str& text){}
void eGroupbox::on_resize(int width,int height){}
void eGroupbox::on_parent_resize(){}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//***** SET APPEARANCE
void eGroupbox::set_appearance(GroupboxAppearance::Type appear)
{
	appearance=appear;
	dirty=true;
}



//***** SET TEXT
void eGroupbox::set_text(const Str& txt,Align::Type align,int offx,int offy)
{
	text=txt;
	text_align=align;
	text_offx=offx;
	text_offy=offy;

	show_text=true;
	dirty=true;
}



//***** SET SHOW TEXT
void eGroupbox::set_show_text(bool sh_text)
{
	show_text=sh_text;
	dirty=true;
}








//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************







