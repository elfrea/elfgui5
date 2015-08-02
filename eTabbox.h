#pragma once

#include <pix5.h>
#include "elfgui5.h"


class eTabbox:public Element
{
public:

	//own config vars
	bool can_move_tabs;
	bool can_drag_tabs;

	//own internal config vars (use config functions to modify)
	TabsPosition::Type tabs_position;
	int title_size;
	class eTab* selected_tab;
	Color color_dragin;

	//own internal vars
	bool ready_to_grab;
	eTab* grabbing_tab;

	//own elements



	//constructor
	eTabbox(const Str& ename,int ex,int ey,int ew,int eh,TabsPosition::Type tabs_pos=TabsPosition::Top);
	//destructor
	~eTabbox();



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
	void on_mouse_drag_in(DragPacket* dragpacket,int mx,int my);
	void on_key_down(Key& key);
	void on_key_up(Key& key);
	void on_text(const Str& text);
	void on_resize(int width,int height);
	void on_parent_resize();
	void on_select();
	void on_unselect();

	//family functions
	void add_child(Element* child);
	void insert_child(Element* child,int index);
	void remove_child(Element* child,bool del=false);

	//own config functions
	void insert_tab(class eTab* tab,int index);
	void add_tab(class eTab* tab);
	class eTab* add_new_tab(const Str& tname);
	void remove_tab(class eTab* tab,bool del=false);
	void remove_tab(int index,bool del=false);
	void move_tab(class eTab* tab,int index);
	void move_tab(int index1,int index2);
	void switch_tab(class eTab* tab1,class eTab* tab2);
	void switch_tab(int index1,int index2);
	void transfer_tab(class eTab* tab,eTabbox* tabbox);
	void transfer_tab(int index,eTabbox* tabbox);
	class eWindow* undock_tab(class eTab* tab,class Element* eparent,int ex,int ey);
	class eWindow* undock_tab(int index,class Element* eparent,int ex,int ey);
	class eTab* dock_tab(class eWindow* win,int index);
	int get_tab_index(class eTab* tab);
	void select_tab(class eTab* tab);
	void select_tab(int index);
	class eTab* get_selected_tab();
	int get_selected_index();

	void set_title_size(int sz);
	void set_tabs_position(TabsPosition::Type pos);

	//own internal functions
	void replace_tabs();
	void replace_tab(eTab* tab);
	void show_tab(eTab* tab);
	void show_tab(int index);
	int get_tab_title_x(eTab* tab);
	int get_tab_title_y(eTab* tab);
	int get_tab_title_w(eTab* tab);
	int get_tab_title_h(eTab* tab);
	Color get_tab_color(eTab* tab);
	Color get_tab_dcolor(eTab* tab);
	Font* get_tab_font(eTab* tab);
	Texture* get_tab_text(eTab* tab);

	class eTab* find_tab_at(int mx,int my);

	void grab_tab(int mx=-1,int my=-1);

};





