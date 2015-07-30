#pragma once

#include <pix5.h>
#include "elfgui5.h"





class Element
{

public:

	//config vars
	Str type;
	Str name;
	Font* font;
	int x,y;
	bool visible;
	bool selectable;
	bool mouse_down_bring_to_front;
	bool can_be_dragged;
	bool can_be_moved;
	bool can_be_moved_outside_parent;
	bool can_be_clicked_through;
	bool can_be_resized;
	bool always_on_bottom;
	bool always_on_top;
	bool send_keyboard_events_to_parent;
	bool forward_event_to_parent;
	
	bool use_custom_cursor;
	bool use_anchor;

	int tab_index;


	//internal config vars (use config functions to modify)
	Colors* color;
	bool enabled;
	int w,h;
	int min_w,max_w;
	int min_h,max_h;
	bool selected;
	Rect move_area;
	Anchor* anchor;
	bool move_area_auto_width;
	bool move_area_auto_height;
	Texture* custom_cursor;
	int custom_cursor_hx;
	int custom_cursor_hy;

	//internal vars
	Texture* image;
	Element* parent;
	List<Element*> children;
	bool dirty;


	
	//constructor
	Element(const Str& ename,int ex,int ey,int ew,int eh);
	//destructor
	virtual ~Element();



	//basic functions
	virtual void loop();
	virtual void draw();

	//event functions
	virtual void on_event(Event* ev);
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
	virtual void on_parent_resize();
	virtual void on_select();
	virtual void on_unselect();
	
	//family functions
	virtual void add_child(Element* child);
	virtual void insert_child(Element* child,int index);
	virtual void remove_child(Element* child);

	//config functions
	void set_selected(bool select);
	void set_font(Font* fnt,bool propagate=false);
	void set_color(Color& col,const Color& newcol);
	void set_colors_enabled(const Color& c_light,const Color& c_medium,const Color& c_dark,const Color& c_text,const Color& c_editing,const Color& c_selection,const Color& c_extra,bool propagate=false);
	void set_colors_disabled(const Color& c_light,const Color& c_medium,const Color& c_dark,const Color& c_text,const Color& c_editing,const Color& c_selection,const Color& c_extra,bool propagate=false);
	void set_theme_colors(bool propagate=false);
	void resize(int width,int height);
	void bring_to_front();
	void send_to_back();
	void set_enabled(bool enbl);
	void set_min_size(int minw,int minh);
	void set_max_size(int maxw,int maxh);
	void set_minmax_size(int minw,int minh,int maxw,int maxh);
	void set_move_area(int mx,int my,int mw,int mh);
	void set_move_area_autosize(bool autow,bool autoh);
	void set_custom_cursor(const Str& filename,int hx,int hy);
	DragPacket* start_drag(const Str& icon_path,int offx=0,int offy=0);
	void send_event(Element* sndr,const Str& cmd);
	void send_event(Event* ev);
	void send_event(const Str& cmd);
	void set_anchor(bool t,bool b,bool l,bool r,bool use=true);
	void set_anchor(bool t,int ty,bool b,int by,bool l,int lx,bool r,int rx,bool use=true);

	//internal functions
	void loops();
	void display();
	void replace_elements();
	int get_true_x();
	int get_true_y();
	Element* find_element_at(int x,int y);
	Element* find_element_under_mouse();
	void apply_anchor();

};
