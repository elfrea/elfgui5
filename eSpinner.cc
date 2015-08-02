#include <pix5.h>
#include "elfgui5.h"



//constructor
eSpinner::eSpinner(const Str& ename,int ex,int ey,int ew,int eh,SpinnerMode::Type mod,double val,double min,double max,Orientation::Type orient):Element(ename,ex,ey,ew,eh)
{
	//parent class vars
	type="spinner";
	selectable=true;
	
	//own config vars
	
	//own internal config vars (use config functions to modify)
	value=val;
	value_min=min;
	value_max=max;

	button_value=1;
	num_decimals=2;

	//own internal vars
	
	//own elements
	button_dec=new eButton("button_dec",0,0,10,10,"");
	button_dec->set_show_text(false);
	add_child(button_dec);

	editbox=new eEditbox("editbox",0,0,10,10,"");
	add_child(editbox);

	button_inc=new eButton("button_inc",0,0,10,10,"");
	button_inc->set_show_text(false);
	add_child(button_inc);

	//other
	set_orientation(orient);
	set_value(val);
	set_value_range(min,max);
	set_mode(mod);
	dirty=true;
}



//destructor
eSpinner::~eSpinner()
{
}








//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void eSpinner::loop()
{
}



//***** DRAW
void eSpinner::draw()
{
}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//***** ON EVENT
void eSpinner::on_event(Event* ev)
{

	//***** BUTTON DEC TRIGGER
	if(ev->sender==button_dec && ev->command=="trigger")
	{
		if(mode==SpinnerMode::Bool)
			set_value(!value);
		else
			set_value(value-button_value);
	}

	//***** BUTTON INC TRIGGER
	else if(ev->sender==button_inc && ev->command=="trigger")
	{
		if(mode==SpinnerMode::Bool)
			set_value(!value);
		else
			set_value(value+button_value);
	}

	//***** EDITBOX WHEEL DOWN
	else if(ev->sender==editbox && ev->command=="wheel down")
	{
		if(mode==SpinnerMode::Bool)
			set_value(!value);
		else
			set_value(value-button_value);
	}

	//***** EDITBOX WHEEL UP
	else if(ev->sender==editbox && ev->command=="wheel up")
	{
		if(mode==SpinnerMode::Bool)
			set_value(!value);
		else
			set_value(value+button_value);
	}

	//***** EDITBOX TRIGGER
	else if(ev->sender==editbox && ev->command=="trigger")
	{
		set_value(filter_manual_value());
	}

	//SEND EVENT TO PARENT
	else
	{
		send_event(ev);
		return;
	}

	delete ev;
}



void eSpinner::on_mouse_enter(int mx,int my){}
void eSpinner::on_mouse_leave(){}
void eSpinner::on_mouse_move(int mx,int my){}
void eSpinner::on_mouse_down(int but,int mx,int my){}
void eSpinner::on_mouse_up(int but,int mx,int my){}
//void eSpinner::on_mouse_click(int but,int mx,int my){}
//void eSpinner::on_mouse_doubleclick(int but,int mx,int my){}
//void eSpinner::on_mouse_wheel_down(int mx,int my){}
//void eSpinner::on_mouse_wheel_up(int mx,int my){}
void eSpinner::on_mouse_drag_out(){}
void eSpinner::on_mouse_drag_in(DragPacket* dragpacket,int mx,int my){}
void eSpinner::on_key_down(Key& key){}
void eSpinner::on_key_up(Key& key){}
void eSpinner::on_text(const Str& text){}



//***** ON RESIZE
void eSpinner::on_resize(int width,int height)
{
	replace_elements();
}



void eSpinner::on_parent_resize(){}



//***** ON SELECT
void eSpinner::on_select()
{
	editbox->set_selected(true);
}



void eSpinner::on_unselect(){}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//***** SET MODE
void eSpinner::set_mode(SpinnerMode::Type mod)
{
	mode=mod;
	set_value(value);
	
	switch(mode)
	{
		//DOUBLE,FLOAT
		case SpinnerMode::Double:
		case SpinnerMode::Float:
			editbox->set_filter(EditboxFilter::Float);
			editbox->set_readonly(false);
		break;

		//INT,INT64
		case SpinnerMode::Int:
		case SpinnerMode::Int64:
			editbox->set_filter(EditboxFilter::Int);
			editbox->set_readonly(false);
		break;

		//BOOL
		case SpinnerMode::Bool:
			editbox->set_filter(EditboxFilter::Alpha);
			editbox->set_readonly(true);
		break;

	}
}



//***** SET ORIENTATION
void eSpinner::set_orientation(Orientation::Type orient)
{
	orientation=orient;
	replace_elements();
}



//***** SET VALUE (double)
void eSpinner::set_value(double val)
{
	value=val;
	if(value<value_min)
		value=value_min;
	if(value>value_max)
		value=value_max;

	switch(mode)
	{
		//DOUBLE,FLOAT
		case SpinnerMode::Double:
		case SpinnerMode::Float:
			editbox->set_text(Str::build("%.*f",num_decimals,value));
		break;

		//INT
		case SpinnerMode::Int:
			editbox->set_text(Str::build("%i",(int)value));
		break;

		//INT64
		case SpinnerMode::Int64:
			editbox->set_text(Str::build("%lld",(int64_t)value));
		break;

		//BOOL
		case SpinnerMode::Bool:
			editbox->set_text(Str::build("%s",value?"True":"False"),true);
		break;

	}
	send_event("change");
}



//***** SET VALUE (float)
void eSpinner::set_value(float val)
{
	set_value((double)val);
}



//***** SET VALUE (int)
void eSpinner::set_value(int val)
{
	set_value((double)val);
}



//***** SET VALUE (int64)
void eSpinner::set_value(int64_t val)
{
	set_value((double)val);
}



//***** SET VALUE (bool)
void eSpinner::set_value(bool val)
{
	set_value((double)val);
}



//***** SET VALUE RANGE (double)
void eSpinner::set_value_range(double min,double max)
{
	value_min=min;
	value_max=max;

	set_value(value);
}



//***** SET VALUE RANGE (float)
void eSpinner::set_value_range(float min,float max)
{
	set_value_range((double)min,(double)max);
}



//***** SET VALUE RANGE (int)
void eSpinner::set_value_range(int min,int max)
{
	set_value_range((double)min,(double)max);
}



//***** SET VALUE RANGE (int64)
void eSpinner::set_value_range(int64_t min,int64_t max)
{
	set_value_range((double)min,(double)max);
}



//***** GET DOUBLE
inline double eSpinner::get_double()
{
	return value;
}



//***** GET FLOAT
inline float eSpinner::get_float()
{
	return (float)value;
}



//***** GET INT
inline int eSpinner::get_int()
{
	return (int)value;
}



//***** GET INT64
inline int64_t eSpinner::get_int64()
{
	return (int64_t)value;
}



//***** GET BOOL
inline bool eSpinner::get_bool()
{
	return (bool)value;
}



//***** SET BUTTON VALUE (double)
inline void eSpinner::set_button_value(double val)
{
	button_value=val;
}



//***** SET BUTTON VALUE (float)
inline void eSpinner::set_button_value(float val)
{
	set_button_value((double)val);
}



//***** SET BUTTON VALUE (int)
void eSpinner::set_button_value(int val)
{
	set_button_value((double)val);
}



//***** SET BUTTON VALUE (int64)
void eSpinner::set_button_value(int64_t val)
{
	set_button_value((double)val);
}



//***** SET NUM DECIMALS
void eSpinner::set_num_decimals(int num)
{
	num_decimals=num;
	set_value(value);
}








//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************


//***** FILTER MANUAL VALUE
double eSpinner::filter_manual_value()
{
	Str txt=editbox->text;

	switch(mode)
	{
		//DOUBLE,FLOAT
		case SpinnerMode::Double:
		case SpinnerMode::Float:
			return atof(txt);
		break;

		//INT
		case SpinnerMode::Int:
			return atoi(txt);
		break;

		//INT64
		case SpinnerMode::Int64:
			return atoll(txt);
		break;

		//BOOL
		case SpinnerMode::Bool:
			return (txt=="True"?1:0);
		break;

	}

	return 0;
}



//***** REPLACE ELEMENTS
void eSpinner::replace_elements()
{
	//horizontal
	if(orientation==Orientation::Horizontal)
	{
		button_dec->resize(h,h);
		button_dec->x=0;
		button_dec->y=0;
		button_dec->set_tex("gfx/elements/arrow_left.png");

		button_inc->resize(h,h);
		button_inc->x=w-h;
		button_inc->y=0;
		button_inc->set_tex("gfx/elements/arrow_right.png");

		editbox->resize(w-(h*2),h);
		editbox->x=h;
		editbox->y=0;

	}

	//vertical
	else
	{
		button_dec->resize(h,h/2);
		button_dec->x=w-h;
		button_dec->y=h/2;
		button_dec->set_tex("gfx/elements/arrow_down.png");

		button_inc->resize(h,h/2);
		button_inc->x=w-h;
		button_inc->y=0;
		button_inc->set_tex("gfx/elements/arrow_up.png");

		editbox->resize(w-h,h);
		editbox->x=0;
		editbox->y=0;

	}

}






