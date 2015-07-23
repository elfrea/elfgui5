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
	text_align=Align::Top;
	text_offx=0;
	text_offy=0;
	text="";

	show_tex=false;
	tex_align=Align::Top;
	tex_offx=0;
	tex_offy=0;
	tex=NULL;

	
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


	//show tex
	if(show_tex)
		draw_texture_align(image,tex_align,tex_offx,tex_offy,tex);

	//show text
	if(show_text)
	{
		if(enabled)
			draw_text_align(image,text_align,text_offx,text_offy,Theme::font::normal,Theme::color::text,text);
		else
			draw_text_align(image,text_align,text_offx,text_offy,Theme::font::normal,Theme::color::d_text,text);
	}
}







//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//void ePanel::on_event(Event* ev){}

void ePanel::on_mouse_enter(int mx,int my){}
void ePanel::on_mouse_leave(){}
void ePanel::on_mouse_move(int mx,int my){}
void ePanel::on_mouse_down(int but,int mx,int my){}
void ePanel::on_mouse_up(int but,int mx,int my){}
void ePanel::on_mouse_click(int but,int mx,int my){}
void ePanel::on_mouse_doubleclick(int but,int mx,int my){send_event("trigger");}
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


//SET TEXT
void ePanel::set_text(const Str& txt,Align::Type align,int offx,int offy)
{
	text=txt;
	text_align=align;
	text_offx=offx;
	text_offy=offy;
	
	show_text=true;
	draw();
}



//SET TEX
void ePanel::set_tex(Texture* src,Align::Type align,int offx,int offy)
{
	tex=src;
	tex_align=align;
	tex_offx=offx;
	tex_offy=offy;
	
	show_tex=true;
	draw();
}


//SET TEX
void ePanel::set_tex(const Str& filename,Align::Type align,int offx,int offy)
{
	Texture* t=Cache::texture(filename);
	set_tex(t,align,offx,offy);
}






