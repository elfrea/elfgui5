#pragma once

#include <pix5.h>
#include "elfgui5.h"


class eMenuSub:public Element
{
public:

	//own config vars

	//own internal config vars (use config functions to modify)
	Str text;
	class eMenu* link;
	bool show_selection;

	//own internal vars
	Texture* arrow;
	bool mouseon;
	int64_t menu_delay;
	int64_t menu_timer;

	//own elements



	//constructor
	eMenuSub(const Str& ename,int ew,int eh,const Str& etext,class eMenu* elink);
	//destructor
	~eMenuSub();



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
	void set_show_selection(bool show);

	//own internal functions


};






