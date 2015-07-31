#pragma once

#include <pix5.h>
#include "elfgui5.h"


class eTrackbar:public Element
{
	OBJ("eTrackbar")

public:

	//own config vars

	//own internal config vars (use config functions to modify)
	Orientation::Type orientation;

	bool customized;
	Texture* custom_bar;
	Texture* custom_tracker;
	Texture* custom_tracker_disabled;

	bool show_rails;

	int value;
	int value_min;
	int value_max;

	int track_size;
	int tracker_size;

	//own internal vars
	bool ready_to_track;

	//own elements



	//constructor
	eTrackbar(const Str& ename,int ex,int ey,int ew,int eh,int val,int min,int max,Orientation::Type orient=Orientation::Horizontal);
	//destructor
	~eTrackbar();



	//basic functions
	void loop();
	void draw();

	//event functions
	//void on_event(Event* ev);
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
	void on_mouse_drag_in(DragPacket* dragpacket);
	void on_key_down(Key& key);
	void on_key_up(Key& key);
	void on_text(const Str& text);
	void on_resize(int width,int height);
	void on_parent_resize();
	void on_select();
	void on_unselect();

	//own config functions
	void set_orientation(Orientation::Type orient);

	void set_value(int val);
	void set_value_range(int min,int max);

	void set_percent(int percent);
	int get_percent();

	void set_track_size(int size);
	void set_tracker_size(int size);

	void set_customized(bool custom);
	void set_custom(Texture* bar,Texture* tracker,Texture* dtracker,bool autosize=true);
	void set_custom(const Str& bar,const Str& tracker,const Str& dtracker,bool autosize=true);

	void set_show_rails(bool show);

	//own internal functions


};





