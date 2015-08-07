#pragma once

#include <pix5.h>
#include "elfgui5.h"


class eMenuRadio:public Element
{
public:

	//own config vars

	//own internal config vars (use config functions to modify)
	Str text;
	Str group;
	bool checked;

	bool show_text;
	bool show_selection;

	int text_offset;
	int check_size;
	int check_radius;

	//own internal vars
	bool mouse_on;

	//own elements



	//constructor
	eMenuRadio(const Str& ename,int ew,int eh,const Str& etext,const Str& egroup,bool echecked);
	//destructor
	~eMenuRadio();



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
	void on_mouse_drag_in(DragPacket* dragpacket,int mx,int my);
	void on_key_down(Key& key);
	void on_key_up(Key& key);
	void on_text(const Str& text);
	void on_resize(int width,int height);
	void on_parent_resize();
	void on_select();
	void on_unselect();
	void on_resolution_change(int width,int height);

	//own config functions
	void shrink();
	void set_text(const Str& txt);
	void set_group(const Str& grp);
	void set_show_text(bool show);
	void set_show_selection(bool show);
	void set_checked(bool check);
	void set_text_offset(int off);
	void set_check_size(int sz);
	void set_check_radius(int radius);

	//own internal functions


};






