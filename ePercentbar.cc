#include <pix5.h>
#include "elfgui5.h"



//constructor
ePercentbar::ePercentbar(const Str& ename,int ex,int ey,int ew,int eh,int val,int min,int max,bool show):Element(ename,ex,ey,ew,eh)
{
	//parent class vars
	type="percentbar";
	selectable=false;
	
	//own config vars
	
	//own internal config vars (use config functions to modify)
	customized=false;
	show_percent=show;

	//own internal vars
	
	//own elements

	//other
	set_color(color->extra,Color::ubyte(110,130,170));
	set_value_range(min,max);
	set_value(val);
	dirty=true;
}



//destructor
ePercentbar::~ePercentbar()
{
}








//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void ePercentbar::loop()
{
}



//***** DRAW
void ePercentbar::draw()
{

	//customized
	if(customized)
	{
		image->clear(Color(0,0,0,0));
	}

	//normal
	else
	{
		//clear image
		image->clear(color->editing);

		//show bar
		int bw=w*get_percent()/100;
		image->rect_fill(0,0,bw,h,color->extra);

		//show border
		image->rect(0,0,w-1,h-1,color->text);
	}

	//show percent

	draw_text_align(image,Align::Middle,0,0,font,color->text,Str::build("%i%%",get_percent()));
}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//void ePercentbar::on_event(Event* ev){}
void ePercentbar::on_mouse_enter(int mx,int my){}
void ePercentbar::on_mouse_leave(){}
void ePercentbar::on_mouse_move(int mx,int my){}
void ePercentbar::on_mouse_down(int but,int mx,int my){}
void ePercentbar::on_mouse_up(int but,int mx,int my){}
//void ePercentbar::on_mouse_click(int but,int mx,int my){}
//void ePercentbar::on_mouse_doubleclick(int but,int mx,int my){}
//void ePercentbar::on_mouse_wheel_down(int mx,int my){}
//void ePercentbar::on_mouse_wheel_up(int mx,int my){}
void ePercentbar::on_mouse_drag_out(){}
void ePercentbar::on_mouse_drag_in(DragPacket* dragpacket){}
void ePercentbar::on_key_down(Key& key){set_value(value+3);}
void ePercentbar::on_key_up(Key& key){}
void ePercentbar::on_text(const Str& text){}
void ePercentbar::on_resize(int width,int height){}
void ePercentbar::on_parent_resize(){}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//***** GET PERCENT
int ePercentbar::get_percent()
{
	return 100*(value-value_min)/(value_max-value_min);
}



//***** SET PERCENT
void ePercentbar::set_percent(int val)
{
	set_value(value_min+((value_max-value_min)*val/100));
}



//***** SET VALUE
void ePercentbar::set_value(int val)
{
	//make sur value is in range
	if(val<value_min)
		val=value_min;
	if(val>value_max)
		val=value_max;

	//set value if different from current value
	if(value!=val)
	{
		send_event("trigger");
		value=val;
		dirty=true;
	}
}



//***** SET VALUE RANGE
void ePercentbar::set_value_range(int min,int max)
{
	//set range
	value_min=(min<max?min:max);
	value_max=(max>min?max:min);

	//set value if out of range
	if(value<value_min)
		value=value_min;
	if(value>value_max)
		value=value_max;

	dirty=true;
}



//***** SET SHOW PERCENT
void ePercentbar::set_show_percent(bool show)
{
	show_percent=show;
	dirty=true;
}








//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************







