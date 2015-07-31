#pragma once

#include <pix5.h>
#include "elfgui5.h"


class eEditbox:public Element
{
	OBJ("eEditbox")

public:

	//own config vars
	bool cursor_blink;
	int64_t cursor_blink_delay;
	int64_t mouse_scroll_delay;

	//own internal config vars (use config functions to modify)
	bool customized;
	Texture* custom_bg;

	bool readonly;
	bool insert_mode;
	bool password_mode;
	Str password_char;
	Str text;

	int border_w;
	int min_right_view;

	int cursor_pos;
	int view_pos;

	EditboxFilter::Type filter;

	//own internal vars
	int64_t cursor_blink_timer;
	bool cursor_is_gone;
	bool key_repeat;
	int64_t mouse_scroll_timer;

	bool selecting;
	int selection_start;
	int selection_end;

	bool mouse_is_down;
	int mouse_down_at_pos;

	//own elements



	//constructor
	eEditbox(const Str& ename,int ex,int ey,int ew,int eh,const Str& txt);
	//destructor
	~eEditbox();



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
	void on_mouse_doubleclick(int but,int mx,int my);
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
	void set_text(const Str& txt,bool override_readonly=false);
	void set_custom(Texture* tex,int borderw=5,bool autosize=true);
	void set_custom(const Str& filename,int borderw=5,bool autosize=true);
	void set_customized(bool custom);
	void set_border_width(int bw);
	void set_cursor_position(int pos);
	void set_view_pos(int pos);
	void set_min_right_view(int amount);
	void set_insert_mode(bool insert);
	void select_text(int pos1=-1,int pos2=-1);
	void set_password_mode(bool pass,const Str& chr="*");
	void set_password_char(const Str& chr);
	Str get_selected_text();
	void set_readonly(bool read);

	void copy_text(const Str& txt,Str& dest=Clipboard::text);
	void copy_selected_text(Str& dest=Clipboard::text);
	void cut_selected_text(Str& dest=Clipboard::text);
	void paste_text(const Str& txt);
	void paste_text_from_clipboard();

	void set_filter(EditboxFilter::Type f);

	//own internal functions
	Str get_text();
	Str get_visible_text();
	Str reduce_string_to_fit(const Str& str,int width,int charmore=0);
	int get_cursor_x();
	int get_char_w(const Str& str,int pos);
	int get_view_w();
	int get_view_last();
	int get_last_pos();
	int get_next_space_pos(bool backward);

	void add_chars(int pos,Str chars);
	void remove_chars(int pos,int len,bool backward=false);
	void remove_chars_range(int pos1,int pos2);

	int get_selection_x();
	int get_selection_w();
	void add_selection(int pos1,int pos2);
	void del_selection(int pos1,int pos2);
	void remove_selection();

	int find_pos_at(int mx);

	Str apply_filter(const Str& str);
	Str filter_char(const Str& ch);

};




