#pragma once

#include <pix5.h>
#include "elfgui5.h"


class eMenubar:public Element
{
public:

	//own config vars

	//own internal config vars (use config functions to modify)
	List<class eMenu*> menus;
	class eMenu* selected_menu;
	int menu_offset;
	int menu_spacing;

	//own internal vars

	//own elements
	class eModal* menus_modal;



	//constructor
	eMenubar(const Str& ename,int ex,int ey,int ew,int eh);
	//destructor
	~eMenubar();



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
	void set_menu_offset(int offx);
	void set_menu_spacing(int spacing);

	void add_menu(class eMenu* menu);

	void select_menu(class eMenu* menu);

	//own internal functions
	class eMenu* find_menu_at(int mx,int my);
	int get_menu_x(class eMenu* menu);

};





