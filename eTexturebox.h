#pragma once

#include <pix5.h>
#include "elfgui5.h"


class eTexturebox:public Element
{
public:

	//own config vars

	//own internal config vars (use config functions to modify)
	bool dynamic;
	int border;
	Color border_color;
	Color bg_color;
	Texture* tex;
	int tex_offx;
	int tex_offy;

	//own internal vars
	bool moving_tex;
	int moving_tex_x;
	int moving_tex_y;

	//own elements



	//constructor
	eTexturebox(const Str& ename,int ex,int ey,int ew,int eh,Texture* texture,int brdr=0,bool autosize=true);
	//destructor
	~eTexturebox();



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
	void set_texture(Texture* texture,int offx=0,int offy=0,bool autosize=true);
	void set_texture(const Str& filename,int offx=0,int offy=0,bool autosize=true);
	void set_texture_offset(int offx,int offy);
	void set_border(int brdr,bool autosize=true);
	void set_border_color(const Color& col);
	void set_bg_color(const Color& col);
	void set_dynamic(bool dyn);

	//own internal functions


};





