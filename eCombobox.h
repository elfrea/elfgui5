#pragma once

#include <pix5.h>
#include "elfgui5.h"


class eCombobox:public Element
{
public:

	//own config vars

	//own internal config vars (use config functions to modify)

	//own internal vars

	//own elements
	class eEditbox* editbox;
	class eButton* button;
	class eListbox* listbox;
	class eModal* modal;



	//constructor
	eCombobox(const Str& ename,int ex,int ey,int ew,int eh,const Str& txt="");
	//destructor
	~eCombobox();



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
	void set_text(const Str& txt);
	void set_readonly(bool ronly);
	void set_show_value(bool show);

	void clear_items(bool del=true);
	class eItem* insert_item(const Str& txt,int val,Texture* ico,int index);
	class eItem* insert_item(const Str& txt,int val,const Str& ico,int index);
	class eItem* add_item(const Str& txt,int val=0);
	class eItem* add_item(const Str& txt,int val,Texture* ico);
	class eItem* add_item(const Str& txt,int val,const Str& ico);
	void remove_item(eItem* item,bool del=true);
	void remove_item(int index,bool del=true);
	void sort_items_by_text();
	void sort_items_by_value();

	Str get_text();
	int get_value();
	class eItem* get_item();

	//own internal functions
	void refresh_gui();
	void open_list();
	void close_list();


};





