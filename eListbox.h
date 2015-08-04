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
	bool alternate_color;
	bool multi_selection;
	bool show_value;
	int64_t mouse_scroll_delay;

	//own internal vars
	class eScrollbar* scrollbar_v;
	int current_pos;

	List<int> selection;

	int selected_base;
	int selected_min;
	int selected_max;
	bool mouse_selecting;

	int64_t mouse_scroll_timer;

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
	void set_alternate_color(bool alternate);
	void set_show_value(bool show);
	void set_current_pos(int index);

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
	void sort_items_by_text(bool reverse=false);
	void sort_items_by_value(bool reverse=false);

	void select_item(eItem* item);
	void select_item(int index);
	void select_items(int index1,int index2);
	void add_to_selection(eItem* item);
	void add_to_selection(int index);
	void remove_from_selection(eItem* item);
	void remove_from_selection(int index);
	void toggle_item_selection(eItem* item);
	void toggle_item_selection(int index);

	eItem* get_selected_item();
	int get_selected_index();
	List<eItem*> get_selected_items();
	List<int> get_selected_items_index();

	int get_item_index(eItem* item);
	int get_size();


	//own internal functions
	int get_view_h();
	void refresh_scrollbars();
	eItem* find_item_at(int mx,int my);
	int find_item_index_at(int mx,int my);

	bool compare_selection(int index);
	bool compare_selection(int index1,int index2);

};





