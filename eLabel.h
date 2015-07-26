#pragma once

#include <pix5.h>
#include "elfgui5.h"


class eLabel:public Element
{
public:

	//own config vars

	//own internal config vars (use config functions to modify)
	Str text;
	Align::Type text_align;
	int text_offx;
	int text_offy;

	//own internal vars

	//own elements



	//constructor
	eLabel(const Str& ename,int ex,int ey,int ew,int eh,const Str& txt);
	//destructor
	~eLabel();



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

	//own config functions
	void set_text(const Str& txt,bool autosize=true,Align::Type align=Align::Middle,int offx=0,int offy=0);

	//own internal functions


};





