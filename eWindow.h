#pragma once

#include <pix5.h>
#include "elfgui5.h"


class eWindow:public Element
{
public:

	//own config vars

	//own internal config vars (use config functions to modify)
	bool maximized;
	bool minimized;
	bool shaded;

	bool show_button_close;
	bool show_button_maximize;
	bool show_button_minimize;
	bool show_button_shade;

	//own internal vars
	int maximized_x;
	int maximized_y;
	int maximized_w;
	int maximized_h;
	int shaded_h;

	//own elements
	class ePanel* titlebar;
	class eButton* button_close;
	class eButton* button_maximize;
	class eButton* button_minimize;
	class eButton* button_shade;
	
	class ePanel* body;
	class ePanel* statusbar;
	
	class eScrollbar* auto_scrollbar_h;
	class eScrollbar* auto_scrollbar_v;
	class ePanel* auto_scroll_panel;



	//constructor
	eWindow(const Str& ename,int ex,int ey,int ew,int eh,const Str& etitle);
	//destructor
	~eWindow();



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
	void on_resolution_change(int width,int height);
	virtual bool on_close();
	virtual bool on_maximize();
	virtual bool on_minimize();
	virtual bool on_shade();

	//family functions
	void add_child(Element* child);
	void insert_child(Element* child,int index);
	void remove_child(Element* child,bool del=false);

	void add_child_on_window(Element* child);
	void insert_child_on_window(Element* child,int index);
	void remove_child_on_window(Element* child,bool del=false);

	//own config functions
	void shrink();
	Str get_title();
	void set_title(const Str& etitle,Align::Type align=Align::Left,int offx=25,int offy=0);
	void set_icon(Texture* tex,Align::Type align=Align::Left,int offx=3,int offy=0);
	void set_icon(const Str& filename,Align::Type align=Align::Left,int offx=3,int offy=0);
	void set_titlebar_height(int th);
	void set_statusbar_height(int sh);
	void set_statusbar_message(const Str& msg);
	void set_show_buttons(bool bclose,bool bmax,bool bmin,bool bshade);

	void close();
	void maximize();
	void minimize();
	void shade();

	//own internal functions
	void refresh_buttons();
	void refresh_autoscrolling();

	
};



