#pragma once

#include <pix5.h>
#include "elfgui5.h"


class eWindow:public Element
{
public:

	//own config vars

	//own internal config vars (use config functions to modify)

	//own internal vars

	//own elements
	class ePanel* titlebar;
	class ePanel* statusbar;
	class ePanel* body;



	//constructor
	eWindow(const Str& ename,int ex,int ey,int ew,int eh,const Str& etitle);
	//destructor
	~eWindow();



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
	void on_mouse_click(int but,int mx,int my);
	void on_mouse_doubleclick(int but,int mx,int my);
	void on_mouse_wheel_down(int mx,int my);
	void on_mouse_wheel_up(int mx,int my);
	void on_mouse_drag_out();
	void on_mouse_drag_in(DragPacket* dragpacket);
	void on_key_down(Key& key);
	void on_key_up(Key& key);
	void on_text(const Str& text);
	void on_resize(int width,int height);
	void on_parent_resize();

	//family functions
	void add_child(Element* child);
	void insert_child(Element* child,int index);
	void remove_child(Element* child);

	void add_child_on_window(Element* child);
	void insert_child_on_window(Element* child,int index);
	void remove_child_on_window(Element* child);

	//own config functions
	void set_title(const Str& etitle,Align::Type align=Align::Left,int offx=25,int offy=0);
	void set_icon(Texture* tex,Align::Type align=Align::Left,int offx=3,int offy=0);
	void set_icon(const Str& filename,Align::Type align=Align::Left,int offx=3,int offy=0);
	void set_titlebar_height(int th);
	void set_statusbar_height(int sh);

	//own internal functions

};



