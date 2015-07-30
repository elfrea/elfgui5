#include <pix5.h>
#include "elfgui5.h"



//constructor
eLabel::eLabel(const Str& ename,int ex,int ey,int ew,int eh,const Str& txt,bool autowidth,bool autoheight):Element(ename,ex,ey,ew,eh)
{
	//parent class vars
	type="label";
	
	//own config vars
	selectable=false;
	
	//own internal config vars (use config functions to modify)

	//own internal vars
	
	//own elements

	//other
	set_text(txt,color->text,font,autowidth,autoheight);
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

	//clear image
	image->clear(Color(0,0,0,0));

	//show text
	text_format.render(image);
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



//***** ON RESIZE
void eLabel::on_resize(int width,int height)
{
	text_format.calc(w);
}



void eLabel::on_parent_resize(){}
void eLabel::on_select(){}
void eLabel::on_unselect(){}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//SET TEXT
void eLabel::set_text(const Str& txt,const Color& col,Font* fnt,bool autowidth,bool autoheight,TextAlign::Type align,VertTextAlign::Type valign)
{
	TextFormat tf;
	tf.set_font(fnt);
	tf.set_color(col);
	tf.set_align(align);
	tf.set_valign(valign);
	tf.add_text(txt);

	set_text_format(tf,autowidth,autoheight);

}



//SET TEXT FORMAT
void eLabel::set_text_format(TextFormat& tf,bool autowidth,bool autoheight)
{
	text_format=tf;

	//calculate text format
	text_format.calc(autowidth?0:w);
	
	//resize element if necessary
	resize(autowidth?text_format.get_width():w,50);//autoheight?text_format.get_height():h);

	dirty=true;
}





//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************







