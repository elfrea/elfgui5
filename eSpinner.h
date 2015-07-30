#pragma once

#include <pix5.h>
#include "elfgui5.h"


class eSpinner:public Element
{
public:

	//own config vars

	//own internal config vars (use config functions to modify)
	SpinnerMode::Type mode;

	double value;
	double value_min;
	double value_max;

	double button_value;
	int num_decimals;

	Orientation::Type orientation;

	//own internal vars

	//own elements
	class eButton* button_dec;
	class eButton* button_inc;
	class eEditbox* editbox;



	//constructor
	eSpinner(const Str& ename,int ex,int ey,int ew,int eh,SpinnerMode::Type mod=SpinnerMode::Int,double val=0,double min=0,double max=100000,Orientation::Type orient=Orientation::Horizontal);
	//destructor
	~eSpinner();



	//basic functions
	void loop();
	void draw();

	//event functions
	void on_event(Event* ev);
	void on_mouse_enter(int mx,int my);
	void on_mouse_leave();
	void on_mouse_move(int mx,int my);
	void on_mouse_down(int but,int mx,int my);
	void on_mouse_up(int but,int mx,int my);
//	void on_mouse_click(int but,int mx,int my);
//	void on_mouse_doubleclick(int but,int mx,int my);
//	void on_mouse_wheel_down(int mx,int my);
//	void on_mouse_wheel_up(int mx,int my);
	void on_mouse_drag_out();
	void on_mouse_drag_in(DragPacket* dragpacket);
	void on_key_down(Key& key);
	void on_key_up(Key& key);
	void on_text(const Str& text);
	void on_resize(int width,int height);
	void on_parent_resize();
	void on_select();
	void on_unselect();

	//own config functions
	void set_mode(SpinnerMode::Type mod);
	void set_orientation(Orientation::Type orient);
	void set_value(double val);
	void set_value(float val);
	void set_value(int val);
	void set_value(int64_t val);
	void set_value(bool val);

	void set_value_range(double min,double max);
	void set_value_range(float min,float max);
	void set_value_range(int min,int max);
	void set_value_range(int64_t min,int64_t max);

	double get_double();
	float get_float();
	int get_int();
	int64_t get_int64();
	bool get_bool();

	void set_button_value(double val);
	void set_button_value(float val);
	void set_button_value(int val);
	void set_button_value(int64_t val);

	void set_num_decimals(int num);

	//own internal functions
	double filter_manual_value();


};





