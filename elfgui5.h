#pragma once

#include <pix5.h>

#include "elfgui5_enums.h"

#include "elfgui5_drawing.h"
#include "elfgui5_theme.h"
#include "elfgui5_dragpacket.h"
#include "elfgui5_event.h"
#include "elfgui5_anchor.h"

#include "elfgui5_element.h"
#include "eBase.h"
#include "eWindow.h"
#include "ePanel.h"







//***** MY EVENT HANDLER
class MyEventHandler:public EventHandler
{
public:

	void on_mouse_down(int but,Mouse& mouse);
	void on_mouse_up(int but,Mouse& mouse);
	void on_mouse_wheel_down(Mouse& mouse);
	void on_mouse_wheel_up(Mouse& mouse);
	void on_mouse_move(Mouse& mouse);
	void on_key_down(Key& key);
	void on_key_up(Key& key);
	void on_text(const Str& text);
	void on_window_resize(int width, int height);
	void on_quit();
};






class ElfGui5
{
public:
	
	static bool ready_to_quit;
	static MyEventHandler event_handler;
	static TexRenderer texture_renderer;
	static List<Event*> events;
	
	static eBase* base;

	static int64_t doubleclick_timer;
	static int64_t doubleclick_delay;

	static Element* element_under_mouse;
	static int mouse_is_down;
	static int last_mouse_click_but;
	static Element* current_element;
	static DragPacket* current_dragpacket;

	static bool current_element_is_moving;
	static int moving_offx;
	static int moving_offy;
	
	static bool current_element_is_resizing;
	static int resizing_offx;
	static int resizing_offy;
	static int resizing_w;
	static int resizing_h;

	static Str current_cursor_type;
	static int cursor_custom_hx;
	static int cursor_custom_hy;

	//gfx
	static Texture* resize_gizmo;
	static Texture* cursor_arrow;
	static Texture* cursor_resize;
	static Texture* cursor_move;
	static Texture* cursor_custom;

	//main functions
	static void init();
	static int loop();
	static void draw();
	static void shutdown();

	//functions
	static void set_mouse_cursor(const Str& cursor);
	static Event* fetch_event();
};





