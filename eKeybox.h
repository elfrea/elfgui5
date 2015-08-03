#pragma once

#include <pix5.h>
#include "elfgui5.h"


class eKeybox:public Element
{
public:

	//own config vars
	KShortcut* shortcut;

	//own internal config vars (use config functions to modify)

	//own internal vars
	bool record_mode;

	//own elements



	//constructor
	eKeybox(const Str& ename,int ex,int ey,int ew,int eh);
	//destructor
	~eKeybox();



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
	void on_mouse_doubleclick(int but,int mx,int my);
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
	void set_shortcut(bool c,bool a,bool s,bool g,KeyCode k);
	void clear_shortcut();
	KShortcut* clone_shortcut(bool enable=true);
	KShortcut* clone_shortcut(const Str& sname,const Str& stype,bool enable=true);

	void stop_recording();
	void start_recording();

	//own internal functions


};





