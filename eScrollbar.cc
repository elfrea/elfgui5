#include <pix5.h>
#include "elfgui5.h"



//constructor
eScrollbar::eScrollbar(const Str& ename,int ex,int ey,int ew,int eh,int min,int max,Orientation::Type orient):Element(ename,ex,ey,ew,eh)
{
	#define DEFAULT_SLIDER_BAR_SIZE 4
	#define DEFAULT_PAGE_SIZE 1
	#define DEFAULT_WHEEL_VALUE 3

	//parent class vars
	type="scrollbar";
	selectable=false;
	
	//own config vars
	wheel_value=DEFAULT_WHEEL_VALUE;
	
	//own internal config vars (use config functions to modify)
	value_min=(min<max?min:max);
	value_max=(max>min?max:min);
	value=value_min;

	slider_bar_size=DEFAULT_SLIDER_BAR_SIZE;
	page_size=DEFAULT_PAGE_SIZE;

	//own internal vars
	min_slider_size=4;
	ready_to_slide=false;
	sliding_mx=0;
	sliding_my=0;
	
	//own elements
	button_dec=new eButton("button decrease",0,0,10,10,"");
	button_dec->set_show_text(false);
	add_child(button_dec);

	button_inc=new eButton("button increase",0,0,10,10,"");
	button_inc->set_show_text(false);
	add_child(button_inc);

	//other
	set_orientation(orient);
	set_color(color->extra,Color::ubyte(155,155,155));
	dirty=true;
}



//destructor
eScrollbar::~eScrollbar()
{
}








//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void eScrollbar::loop()
{
	Mouse& m=Input::get_mouse();

	if(ready_to_slide)
	{
		if(m.left())
		{
			set_value(get_value_from_mouse());
		}
		else
			ready_to_slide=false;
	}
}



//***** DRAW
void eScrollbar::draw()
{
	Texture* slider;
	int slider_x;
	int slider_y;
	int slider_w;
	int slider_h;

	image->clear(color->extra);

	//HORIZONTAL
	if(orientation==Orientation::Horizontal)
	{
		//draw slider bar
		draw_panel(image,0,(h-slider_bar_size)/2,w,slider_bar_size,false,enabled,color->light,color->medium,color->dark,color->d_light,color->d_medium,color->d_dark);

		//calculate slider size and position
		slider_w=get_slider_size();
		slider_h=h;
		slider_x=get_slider_position();
		slider_y=0;
	}

	//VERTICAL
	else
	{
		//draw slider bar
		draw_panel(image,(w-slider_bar_size)/2,0,slider_bar_size,h,false,enabled,color->light,color->medium,color->dark,color->d_light,color->d_medium,color->d_dark);
		
		//calculate slider size and position
		slider_w=w;
		slider_h=get_slider_size();
		slider_x=0;
		slider_y=get_slider_position();		
	}

	//create slider texture
	slider=Texture::create(slider_w,slider_h);
	draw_panel(slider,color,false,enabled);

	//draw slider
	image->blit(slider_x,slider_y,slider);

	delete slider;
}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//***** ON EVENT
void eScrollbar::on_event(Event* ev)
{

	//button dec
	if(ev->sender==button_dec && ev->command=="trigger")
		set_value(value-1);

	//button inc
	else if(ev->sender==button_inc && ev->command=="trigger")
		set_value(value+1);

	//SEND EVENT TO PARENT
	else
	{
		send_event(ev);
		return;
	}

	delete ev;
}



void eScrollbar::on_mouse_enter(int mx,int my){}
void eScrollbar::on_mouse_leave(){}
void eScrollbar::on_mouse_move(int mx,int my){}



//***** ON MOUSE DOWN
void eScrollbar::on_mouse_down(int but,int mx,int my)
{
	if(but==1)
	{
		int ss=get_slider_size();
		int sp=get_slider_position();

		//HORIZONTAL
		if(orientation==Orientation::Horizontal)
		{
			if(mx<sp)
				set_value(value-page_size);
			else if(mx>=sp+ss)
				set_value(value+page_size);
			else
			{
				ready_to_slide=true;
				sliding_mx=get_true_x()+mx;
				sliding_my=get_true_y()+my;
			}
		}

		//VERTICAL
		else
		{
			if(my<sp)
				set_value(value-page_size);
			else if(my>=sp+ss)
				set_value(value+page_size);
			else
			{
				ready_to_slide=true;
				sliding_mx=get_true_x()+mx;
				sliding_my=get_true_y()+my;
			}
		}
	}
}



void eScrollbar::on_mouse_up(int but,int mx,int my){}
//void eScrollbar::on_mouse_click(int but,int mx,int my){}
//void eScrollbar::on_mouse_doubleclick(int but,int mx,int my){}



//***** ON MOUSE WHEEL UP
void eScrollbar::on_mouse_wheel_down(int mx,int my)
{
	set_value(value+wheel_value);
}



//***** ON MOUSE WHEEL DOWN
void eScrollbar::on_mouse_wheel_up(int mx,int my)
{
	set_value(value-wheel_value);
}



void eScrollbar::on_mouse_drag_out(){}
void eScrollbar::on_mouse_drag_in(DragPacket* dragpacket,int mx,int my){}



//***** ON KEY DOWN
void eScrollbar::on_key_down(Key& key)
{
	if(key.code==KEY_LEFT || key.code==KEY_UP)
		set_value(value-1);
	else if(key.code==KEY_RIGHT || key.code==KEY_DOWN)
		set_value(value+1);
}



void eScrollbar::on_key_up(Key& key){}
void eScrollbar::on_text(const Str& text){}
void eScrollbar::on_resize(int width,int height){}
void eScrollbar::on_parent_resize(){}
void eScrollbar::on_select(){}
void eScrollbar::on_unselect(){}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//***** SET VALUE
void eScrollbar::set_value(int val)
{
	if(val<value_min)
		val=value_min;
	if(val>value_max)
		val=value_max;

	if(value!=val)
	{
		send_event("trigger");
		value=val;
		dirty=true;
	}
}



//***** SET VALUE RANGE
void eScrollbar::set_value_range(int min,int max)
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



//***** SET ORIENTATION
void eScrollbar::set_orientation(Orientation::Type orient)
{
	orientation=orient;

	//HORIZONTAL
	if(orientation==Orientation::Horizontal)
	{
		button_dec->set_tex("gfx/elements/arrow_left.png");
		button_dec->resize(h,h);
		button_dec->x=0;
		button_dec->y=0;

		button_inc->set_tex("gfx/elements/arrow_right.png");
		button_inc->resize(h,h);
		button_inc->x=w-h;
		button_inc->y=0;
	}

	//VERTICAL
	else
	{
		button_dec->set_tex("gfx/elements/arrow_up.png");
		button_dec->resize(w,w);
		button_dec->x=0;
		button_dec->y=0;

		button_inc->set_tex("gfx/elements/arrow_down.png");
		button_inc->resize(w,w);
		button_inc->x=0;
		button_inc->y=h-w;
	}

	dirty=true;
}



//***** SET SLIDER SIZE
void eScrollbar::set_slider_bar_size(int sz)
{
	slider_bar_size=sz;
	dirty=true;
}



//***** SET PAGE SIZE
void eScrollbar::set_page_size(int sz)
{
	page_size=sz;
	dirty=true;
}








//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************



//***** GET SLIDER SIZE
int eScrollbar::get_slider_size()
{
	//calculate slider space
	int spc;
	if(orientation==Orientation::Horizontal)
		spc=w-(h*2);
	else
		spc=h-(w*2);

	//calculate slider size
	int ss;
	ss=page_size*spc/(value_max-value_min+1+page_size);
	if(ss<min_slider_size)
		ss=min_slider_size;


	return ss;
}



//***** GET SLIDER POSITION
int eScrollbar::get_slider_position()
{
	int sp;
	int ss=get_slider_size();
	int bs;
	int spc;

	//calculate slider space and button size
	if(orientation==Orientation::Horizontal)
	{
		spc=w-(h*2);
		bs=h;
	}
	else
	{
		spc=h-(w*2);
		bs=w;
	}

	//calculate slider position
	sp=bs+((value-value_min)*(spc-ss)/(value_max-value_min));
	if(sp<(0+bs))
		sp=(0+bs);
	else if(sp>(bs+spc-ss))
		sp=(bs+spc-ss);


	return sp;
}



//***** GET VALUE FROM MOUSE
int eScrollbar::get_value_from_mouse()
{
	Mouse& m=Input::get_mouse();

	int ss=get_slider_size();
	int spc;
	int v;

	if(orientation==Orientation::Horizontal)
	{
		int mx=m.x-get_true_x()-h-(ss/2);
		spc=w-(h*2);
		v=(value_min+mx*(value_max-value_min+1)/(spc-ss));
	}
	else
	{
		int my=m.y-get_true_y()-w-(ss/2);
		spc=h-(w*2);
		v=(value_min+my*(value_max-value_min+1)/(spc-ss));
	}


	return v;

}


