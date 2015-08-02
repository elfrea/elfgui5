#pragma once

#include <pix5.h>
#include "elfgui5.h"


class eScrollbar:public Element
{
public:

	//own config vars
	int wheel_value;

	//own internal config vars (use config functions to modify)
	int value;
	int value_min;
	int value_max;
	Orientation::Type orientation;
	int page_size;
	int slider_bar_size;

	//own internal vars
	int min_slider_size;
	bool ready_to_slide;
	int sliding_mx;
	int sliding_my;

	//own elements
	eButton* button_dec;
	eButton* button_inc;



	//constructor
	eScrollbar(const Str& ename,int ex,int ey,int ew,int eh,int min=0,int max=10,Orientation::Type orient=Orientation::Horizontal);
	//destructor
	~eScrollbar();



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
	void on_mouse_wheel_down(int mx,int my);
	void on_mouse_wheel_up(int mx,int my);
	void on_mouse_drag_out();
	void on_mouse_drag_in(DragPacket* dragpacket,int mx,int my);
	void on_key_down(Key& key);
	void on_key_up(Key& key);
	void on_text(const Str& text);
	void on_resize(int width,int height);
	void on_parent_resize();
	void on_select();
	void on_unselect();

	//own config functions
	void set_value(int val);
	void set_value_range(int min,int max);
	void set_orientation(Orientation::Type orient);
	void set_slider_bar_size(int sz);
	void set_page_size(int sz);

	//own internal functions
	int get_slider_size();
	int get_slider_position();
	int get_value_from_mouse();

};





