#pragma once

#include <pix5.h>
#include "elfgui5.h"


class eTemplate:public Element
{
public:

	//own config vars

	//own internal config vars (use config functions to modify)

	//own internal vars

	//own elements



	//constructor
	eTemplate(const Str& ename,int ex,int ey,int ew,int eh);
	//destructor
	~eTemplate();



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

	//own config functions

	//own internal functions


};




