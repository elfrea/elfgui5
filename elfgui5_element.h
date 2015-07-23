#pragma once

#include <pix5.h>
#include "elfgui5.h"


//namespace ElementLayer { enum Layer
//{
//	Bottom,Normal,Top
//};}
#define LAYER_BOTTOM 0
#define LAYER_NORMAL 1
#define LAYER_TOP 2




class Element
{

public:

	Str type;
	Str name;

	bool enabled;
	bool visible;
	int x,y;
	int w,h;
	int min_w,max_w;
	int min_h,max_h;
	Rect move_area;

	bool mouse_down_bring_to_front;
	bool can_be_dragged;
	bool can_be_moved;
	bool can_be_moved_outside_parent;
	bool can_be_clicked_through;
	bool can_be_resized;
	bool send_keyboard_events_to_parent;
	bool always_on_bottom;
	bool always_on_top;
	bool use_custom_cursor;
	bool move_area_auto_width;
	bool move_area_auto_height;

	Texture* image;
	Texture* custom_cursor;

	int custom_cursor_hx;
	int custom_cursor_hy;

	Element* parent;
	List<Element*> children;


	

	//constructor
	Element(const Str& ename,int ex,int ey,int ew,int eh);
	//destructor
	virtual ~Element();
	
	//basic functions
	virtual void loop();
	virtual void draw();

	//event functions
	virtual void on_mouse_enter(int mx,int my);
	virtual void on_mouse_leave();
	virtual void on_mouse_move(int mx,int my);
	virtual void on_mouse_down(int but,int mx,int my);
	virtual void on_mouse_up(int but,int mx,int my);
	virtual void on_mouse_click(int but,int mx,int my);
	virtual void on_mouse_doubleclick(int but,int mx,int my);
	virtual void on_mouse_wheel_down(int mx,int my);
	virtual void on_mouse_wheel_up(int mx,int my);
	virtual void on_mouse_drag_out();
	virtual void on_mouse_drag_in(DragPacket* dragpacket);
	
	virtual void on_key_down(Key& key);
	virtual void on_key_up(Key& key);
	virtual void on_text(const Str& text);

	virtual void on_resize(int width,int height);
	
	//family functions
	void add_child(Element* child);
	void insert_child(Element* child,int index);
	void remove_child(Element* child);

	//functions
	void display();
	void replace_elements();
	void resize(int width,int height);
	int get_true_x();
	int get_true_y();
	void bring_to_front();
	void send_to_back();
	void set_enabled(bool enbl);
	void set_min_size(int minw,int minh);
	void set_max_size(int maxw,int maxh);
	void set_minmax_size(int minw,int minh,int maxw,int maxh);
	void set_move_area(int mx,int my,int mw,int mh);
	void set_custom_cursor(const Str& filename,int hx,int hy);

	Element* find_element_at(int x,int y);
	Element* find_element_under_mouse();

	DragPacket* start_drag(const Str& icon_path,int offx=0,int offy=0);
};
