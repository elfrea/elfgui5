#pragma once

#include <pix5.h>
#include "elfgui5.h"


class eListbox:public Element
{
public:

	//own config vars

	//own internal config vars (use config functions to modify)
	ListboxStyle::Type style;
	List<eItem*> items;
	int items_h;
	bool alternate_items_bg;
	bool multi_selection;

	//own internal vars
	class eScrollbar* scrollbar_h;
	class eScrollbar* scrollbar_v;
	int current_pos;
	int selected_base;
	int selected_min;
	int selected_max;
	bool mouse_selecting;

	//own elements



	//constructor
	eListbox(const Str& ename,int ex,int ey,int ew,int eh,ListboxStyle::Type estyle=ListboxStyle::Text);
	//destructor
	~eListbox();



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

	//own config functions
	void set_style(ListboxStyle::Type estyle);
	int get_size();

	void clear(bool del=true);
	void insert_item(eItem* item,int index);
	void add_item(eItem* item);
	void remove_item(eItem* item,bool del=true);
	void remove_item(int index,bool del=true);
	eItem* insert_new_item(const Str& iname,int ival,int index);
	eItem* insert_new_item(const Str& iname,int ival,Texture* ico,int index);
	eItem* insert_new_item(const Str& iname,int ival,const Str& ico,int index);
	eItem* add_new_item(const Str& iname,int ival,Texture* ico=NULL);
	eItem* add_new_item(const Str& iname,int ival,const Str& ico);
	void move_item(eItem* item,int index);
	void move_item(int index1,int index2);
	void switch_item(eItem* item1,eItem* item2);
	void switch_item(int index1,int index2);

	void sort_items_by_name(bool reverse=false);
	void sort_items_by_value(bool reverse=false);

	void select_item(eItem* item);
	void select_item(int index);
	void select_items(int index1,int index2);

	eItem* get_selected_item();
	int get_selected_index();
	List<eItem*> get_selected_items();

	int get_item_index(eItem* item);

	//own internal functions
	int get_view_h();
	void refresh_scrollbars();
	eItem* find_item_at(int mx,int my);
	int find_item_index_at(int mx,int my);

};





