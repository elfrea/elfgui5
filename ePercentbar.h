#pragma once

#include <pix5.h>
#include "elfgui5.h"


class ePercentbar:public Element
{
public:

	//own config vars

	//own internal config vars (use config functions to modify)
	bool customized;
	
	int value;
	int value_min;
	int value_max;

	bool show_percent;
	bool show_value;
	bool show_border;

	Texture* custom_bg;
	Texture* custom_bar;
	Texture* custom_border;

	//own internal vars

	//own elements



	//constructor
	ePercentbar(const Str& ename,int ex,int ey,int ew,int eh,int val=0,int min=0,int max=100,bool show=true);
	//destructor
	~ePercentbar();



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
	int get_percent();
	void set_percent(int val);
	void set_value(int val);
	void set_value_range(int min,int max);
	void set_show_percent(bool show);
	void set_show_value(bool show);
	void set_show_border(bool show);
	void set_bar_color(const Color& col);

	void set_customized(bool custom);
	void set_custom(Texture* bg,Texture* bar,Texture* border,bool autosize=true);
	void set_custom(const Str& bg,const Str& bar,const Str& border,bool autosize=true);

	//own internal functions


};





