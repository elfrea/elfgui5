#pragma once

#include <pix5.h>
#include "elfgui5.h"


class eRadiobutton:public Element
{
public:

	//own config vars

	//own internal config vars (use config functions to modify)
	Str group;
	int check_size;
	int check_radius;
	bool show_text;
	bool show_tex;
	bool checked;

	Align::Type text_align;
	int text_offx;
	int text_offy;
	Str text;

	Align::Type tex_align;
	int tex_offx;
	int tex_offy;
	Texture* tex;

	//own internal vars
	bool ready_to_check;
	Texture* custom_box;
	Texture* custom_mark;

	//own elements



	//constructor
	eRadiobutton(const Str& ename,int ex,int ey,int ew,int eh,const Str& txt,const Str& grp="default",bool echecked=false,bool autosize=true);
	//destructor
	~eRadiobutton();



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
//	void on_mouse_wheel_down(int mx,int my);
//	void on_mouse_wheel_up(int mx,int my);
	void on_mouse_drag_out();
	void on_mouse_drag_in(DragPacket* dragpacket);
	void on_key_down(Key& key);
	void on_key_up(Key& key);
	void on_text(const Str& text);
	void on_resize(int width,int height);
	void on_parent_resize();
	void on_select();
	void on_unselect();

	//own config functions
	void shrink();
	void set_text(const Str& txt,Align::Type align=Align::Left,int offx=4,int offy=0,bool autosize=true);
	void set_tex(Texture* src,Align::Type align=Align::Left,int offx=4,int offy=0,bool autosize=true);
	void set_tex(const Str& filename,Align::Type align=Align::Left,int offx=4,int offy=0,bool autosize=true);
	void set_show_text(bool show);
	void set_show_tex(bool show);
	void set_group(const Str& grp);
	void set_checked();
	void set_check_size(int size,bool autosize=true);
	void set_check_radius(int off);
	void set_custom(Texture* box,Texture* mark,bool autosize=true,bool sh_text=true);
	void set_custom(const Str& box,const Str& mark,bool autosize=true,bool sh_text=true);

	//own internal functions


};






