#pragma once

#include <pix5.h>
#include "elfgui5.h"


class eMenu:public Element
{
public:

	//own config vars

	//own internal config vars (use config functions to modify)
	class Element* link;
	bool auto_size;

	//own internal vars
	bool is_sub_menu;
	bool is_open;
	class eMenuSub* sub_opened;

	//own elements



	//constructor
	eMenu(const Str& ename,int ex,int ey,int ew,int eh,class Element* elink,bool autosz=true,bool issub=false);
	//destructor
	~eMenu();



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

	class eMenuButton* insert_button(const Str& ename,int ew,int eh,const Str& etext,int index);
	class eMenuButton* add_button(const Str& ename,int ew,int eh,const Str& etext);
	class eMenuSeparator* insert_separator(int eh,int index);
	class eMenuSeparator* add_separator(int eh=20);
	class eMenuCheckbox* insert_checkbox(const Str& ename,int ew,int eh,const Str& etext,bool echecked,int index);
	class eMenuCheckbox* add_checkbox(const Str& ename,int ew,int eh,const Str& etext,bool echecked=false);
	class eMenuRadio* insert_radio(const Str& ename,int ew,int eh,const Str& etext,const Str& egroup,bool echecked,int index);
	class eMenuRadio* add_radio(const Str& ename,int ew,int eh,const Str& etext,const Str& egroup="main",bool echecked=false);
	class eMenuSub* insert_sub(const Str& ename,int ew,int eh,const Str& etext,eMenu* elink,int index);
	class eMenuSub* add_sub(const Str& ename,int ew,int eh,const Str& etext,eMenu* elink);

	int get_index(Element* ele);
	void remove_element(Element* ele,bool del=true);
	void remove_element(int index,bool del=true);

	//own internal functions
	void replace_children(bool autosz);
	void open_submenu(class eMenuSub* sub);
	void close_submenu(class eMenuSub* sub,bool propagate=true);


};





