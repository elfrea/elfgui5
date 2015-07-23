#pragma once

#include <pix5.h>
#include "elfgui5.h"


class ePanel:public Element
{
public:
	//own vars
	bool inverted;
	
	bool show_text;
	Align::Type text_align;
	int text_offx;
	int text_offy;
	Str text;

	bool show_tex;
	Align::Type tex_align;
	int tex_offx;
	int tex_offy;
	Texture* tex;

	//constructor
	ePanel(const Str& ename,int ex,int ey,int ew,int eh,bool invert=false);
	//destructor
	~ePanel();

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

	//own functions
	void set_text(const Str& txt,Align::Type align=Align::Top,int offx=0,int offy=0);
	void set_tex(Texture* src,Align::Type align=Align::Top,int offx=0,int offy=0);
	void set_tex(const Str& filename,Align::Type align=Align::Top,int offx=0,int offy=0);
};



