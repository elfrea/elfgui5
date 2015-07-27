#include <pix5.h>
#include "elfgui5.h"



bool ElfGui5::ready_to_quit;

TexRenderer ElfGui5::texture_renderer;
MyEventHandler ElfGui5::event_handler;

List<Event*> ElfGui5::events;

eBase* ElfGui5::base;

int64_t ElfGui5::doubleclick_timer;
int64_t ElfGui5::doubleclick_delay;

Element* ElfGui5::last_selected;
Element* ElfGui5::element_under_mouse;
int ElfGui5::mouse_is_down;
int ElfGui5::last_mouse_click_but;
Element* ElfGui5::current_element;
DragPacket* ElfGui5::current_dragpacket;

bool ElfGui5::current_element_is_moving;
int ElfGui5::moving_offx;
int ElfGui5::moving_offy;

bool ElfGui5::current_element_is_resizing;
int ElfGui5::resizing_offx;
int ElfGui5::resizing_offy;
int ElfGui5::resizing_w;
int ElfGui5::resizing_h;

Str ElfGui5::current_cursor_type;
int ElfGui5::cursor_custom_hx;
int ElfGui5::cursor_custom_hy;

//gfx
Texture* ElfGui5::resize_gizmo;
Texture* ElfGui5::cursor_arrow;
Texture* ElfGui5::cursor_resize;
Texture* ElfGui5::cursor_move;
Texture* ElfGui5::cursor_custom;








//****************************************************************
//MAIN FUNCTIONS
//****************************************************************


//***** INIT
void ElfGui5::init()
{
	#ifdef DBG
	Log::debug("ElfGui5 initializing...");
	#endif

	//config vars
	ready_to_quit=false;
	doubleclick_delay=250;

	//internal vars
	last_selected=NULL;
	element_under_mouse=NULL;
	mouse_is_down=0;
	last_mouse_click_but=0;
	doubleclick_timer=0;
	current_element=NULL;
	current_dragpacket=NULL;

	current_element_is_moving=false;
	moving_offx=0;
	moving_offy=0;
	
	current_element_is_resizing=false;
	resizing_offx=0;
	resizing_offy=0;
	resizing_w=0;
	resizing_h=0;

	current_cursor_type="";
	cursor_custom_hx=0;
	cursor_custom_hy=0;
	
	//internal gfx vars
	resize_gizmo=Cache::texture("gfx/resize_gizmo.png");
	cursor_arrow=Cache::texture("gfx/cursor_arrow.png");	//hotspot=0,0
	cursor_resize=Cache::texture("gfx/cursor_resize.png");	//hotspot=8,8
	cursor_move=Cache::texture("gfx/cursor_move.png");		//hotspot=8,8
	cursor_custom=NULL;

	//init code
	VideoMode vm=Display::get_mode();
	Theme::set("default");
	set_mouse_cursor("arrow");
	base=new eBase("root base",0,0,vm.width,vm.height);


	#ifdef DBG
	Log::debug("ElfGui5 initialization complete!");
	#endif
}



//***** LOOP
int ElfGui5::loop()
{
	//process events
	event_handler.process_events();

	//loop elements
	base->loops();

	//check if quit has been requested
	if(ready_to_quit)
		return 1;

	return 0;
}



//***** DRAW
void ElfGui5::draw()
{
	//draw base
	base->display();

	//draw image under the mouse if currently mouse dragging
	if(current_dragpacket)
	{
		Mouse& m=Input::get_mouse();
		texture_renderer.add(current_dragpacket->icon,m.x+current_dragpacket->offset_x,m.y+current_dragpacket->offset_y);
	}

	
	texture_renderer.draw();
}



//***** SHUTDOWN
void ElfGui5::shutdown()
{
	#ifdef DBG
	Log::debug("ElfGui5 shutting down...");
	#endif

	delete base;
	events.clear_del();
	Theme::kill();

	#ifdef DBG
	Log::debug("ElfGui5 shutdown complete!");
	#endif
}



//***** FETCH EVENT
Event* ElfGui5::fetch_event()
{
	Event* ev=NULL;

	//check if there is any events in the list
	if(events.size()>0)
	{
		ev=events[0];
		events.remove_nodel(0);
	}

	return ev;
}








//****************************************************************
//EVENT FUNCTIONS
//****************************************************************


//***** ON MOUSE DOWN
void MyEventHandler::on_mouse_down(int but,Mouse& mouse)
{
	//set mouse_is_down for on_click event
	ElfGui5::mouse_is_down=but;


	Element* eum=ElfGui5::element_under_mouse;
	if(eum && eum->enabled)
	{
		int mx=mouse.x-eum->get_true_x();
		int my=mouse.y-eum->get_true_y();

		//check if we need to bring to front the element
		if(eum->mouse_down_bring_to_front)
			eum->bring_to_front();
			
		//unselect last element
		if(ElfGui5::current_element && ElfGui5::last_selected && ElfGui5::last_selected!=eum)
		{
			ElfGui5::last_selected->set_selected(false);
			if(eum->selectable==false)
				ElfGui5::last_selected=NULL;
		}

		//set current active element
		ElfGui5::current_element=eum;

		if(eum->selectable)
			eum->set_selected(true);

		//check if element can be resized
		if(eum->can_be_resized && mx>=eum->w-ElfGui5::resize_gizmo->width() && my>=eum->h-ElfGui5::resize_gizmo->height() && but==1)
		{
			//start resizing the element
			ElfGui5::current_element_is_resizing=true;
			ElfGui5::resizing_offx=mouse.x;
			ElfGui5::resizing_offy=mouse.y;
			ElfGui5::resizing_w=eum->w;
			ElfGui5::resizing_h=eum->h;
		}

		//check if element can be moved
		else if(eum->can_be_moved && but==1)
		{
			//make sure the mouse is in the move area of the element
			if(eum->move_area.contains(mx,my))
			{
				//start moving the element
				ElfGui5::current_element_is_moving=true;
				ElfGui5::moving_offx=mx;
				ElfGui5::moving_offy=my;
			}
		}
		
		//send on_mouse_down event
		else
			eum->on_mouse_down(but,mx,my);

	}
	
}



//***** ON MOUSE UP
void MyEventHandler::on_mouse_up(int but,Mouse& mouse)
{
	
	Element* eum=ElfGui5::element_under_mouse;

	//stop moving/resizing element
	ElfGui5::current_element_is_moving=false;
	ElfGui5::current_element_is_resizing=false;

	//send mouse_up/mouse_click/mouse_doubleclick events
	if(eum && eum->enabled)
	{
		//send on_mouse_up event to element
		eum->on_mouse_up(but,mouse.x-eum->get_true_x(),mouse.y-eum->get_true_y());
	
		//check if it's a mouse_click event
		if(ElfGui5::mouse_is_down==but)
		{
			//check if it's a doubleclick event
			int64_t ms=get_ms();
			if(but==1 && (ms-ElfGui5::doubleclick_timer)<=ElfGui5::doubleclick_delay && ElfGui5::last_mouse_click_but==but)
			{
				//send mouse_doubleclick event
				eum->on_mouse_doubleclick(but,mouse.x-eum->get_true_x(),mouse.y-eum->get_true_y());
				ElfGui5::doubleclick_timer=0;
			}

			//it's a mouse_click event
			else
			{
				//send mouse_click event
				eum->on_mouse_click(but,mouse.x-eum->get_true_x(),mouse.y-eum->get_true_y());
				ElfGui5::last_mouse_click_but=but;
				ElfGui5::doubleclick_timer=ms;
			}

		}
	}

	//send mouse_drag_in event
	if(ElfGui5::current_dragpacket)
	{
		if(eum && eum->enabled)
			eum->on_mouse_drag_in(ElfGui5::current_dragpacket);
			
		delete ElfGui5::current_dragpacket;
		ElfGui5::current_dragpacket=NULL;
	}

	//set mouse_is_down for on_click event
	ElfGui5::mouse_is_down=0;

}



//***** ON MOUSE WHEEL DOWN
void MyEventHandler::on_mouse_wheel_down(Mouse& mouse)
{
	Element* eum=ElfGui5::element_under_mouse;
	
	if(eum && eum->enabled)
		eum->on_mouse_wheel_down(mouse.x-eum->get_true_x(),mouse.y-eum->get_true_y());
}



//***** ON MOUSE WHEEL UP
void MyEventHandler::on_mouse_wheel_up(Mouse& mouse)
{
	Element* eum=ElfGui5::element_under_mouse;
	
	if(eum && eum->enabled)
		eum->on_mouse_wheel_up(mouse.x-eum->get_true_x(),mouse.y-eum->get_true_y());
}



//***** ON MOUSE MOVE
void MyEventHandler::on_mouse_move(Mouse& mouse)
{
	Element* eum=ElfGui5::base->find_element_under_mouse();

	//set appropriate mouse cursor
	//resize cursor
	if(ElfGui5::current_element_is_resizing || (eum->enabled && eum->can_be_resized && mouse.x-eum->get_true_x()>=eum->w-ElfGui5::resize_gizmo->width() && mouse.y-eum->get_true_y()>=eum->h-ElfGui5::resize_gizmo->height()))
		ElfGui5::set_mouse_cursor("resize");

	//move cursor
	else if(ElfGui5::current_element_is_moving || (eum->enabled && eum->can_be_moved && eum->move_area.contains(mouse.x-eum->get_true_x(),mouse.y-eum->get_true_y())))
		ElfGui5::set_mouse_cursor("move");

	//custom cursor
	else if(eum->use_custom_cursor && eum->custom_cursor && eum->enabled)
	{
		ElfGui5::cursor_custom=eum->custom_cursor;
		ElfGui5::cursor_custom_hx=eum->custom_cursor_hx;
		ElfGui5::cursor_custom_hy=eum->custom_cursor_hy;
		ElfGui5::set_mouse_cursor("custom");
	}

	//arrow
	else
		ElfGui5::set_mouse_cursor("arrow");


	//check if current element is resizing
	if(ElfGui5::current_element_is_resizing)
	{
		Element* ele=ElfGui5::current_element;
		int nw=ElfGui5::resizing_w+mouse.x-ElfGui5::resizing_offx;
		int nh=ElfGui5::resizing_h+mouse.y-ElfGui5::resizing_offy;

		//make sure the element stays within it's parent
		if(ElfGui5::current_element->can_be_moved_outside_parent==false)
		{
			if(ele->parent)
			{
				if(ele->x+nw>=ele->parent->w)
					nw=ele->parent->w-ele->x;
				if(ele->y+nh>=ele->parent->h)
					nh=ele->parent->h-ele->y;
			}
		}

		//make sure there is enough room for children
		int maxx=0;
		int maxy=0;
		List<Element*> ch;
		if(ele->type=="window")
			ch=((eWindow*)ele)->body->children;
		else
			ch=ele->children;

		for(int a=0;a<ch.size();a++)
		{
			//disregard if child use an anchor
			if(ch[a]->use_anchor)
				continue;

			int cx=ch[a]->x+ch[a]->w;
			int cy=ch[a]->y+ch[a]->h+(ele->type=="window"?((eWindow*)ele)->titlebar->h+((eWindow*)ele)->statusbar->h:0);

			if(cx>maxx)
				maxx=cx;
			if(cy>maxy)
				maxy=cy;
		}
		if(nw<maxx)
			nw=maxx;
		if(nh<maxy)
			nh=maxy;

		ch.clear_nodel();

		//make sure element's size is within min/max size
		if(nw<ele->min_w)
			nw=ele->min_w;
		if(ele->max_w>0)
			if(nw>ele->max_w)
				nw=ele->max_w;

		if(nh<ele->min_h)
			nh=ele->min_h;
		if(ele->max_h>0)
			if(nh>ele->max_h)
				nh=ele->max_h;

		//resize element
		ele->resize(nw,nh);
	}

	//check if current element is moving
	else if(ElfGui5::current_element_is_moving)
	{
		Element* ele=ElfGui5::current_element;
		int px=mouse.x-ElfGui5::moving_offx;
		int py=mouse.y-ElfGui5::moving_offy;

		//adjust coords if element has a parent
		if(ElfGui5::current_element->parent)
		{
			px-=ele->parent->get_true_x();
			py-=ele->parent->get_true_y();

			//make sure the element stays within it's parent
			if(ElfGui5::current_element->can_be_moved_outside_parent==false)
			{
				if(px<0)
					px=0;
				if(px+ele->w>=ele->parent->w)
					px=ele->parent->w-ele->w;
				if(py<0)
					py=0;
				if(py+ele->h>=ele->parent->h)
					py=ele->parent->h-ele->h;
			}
		}

		//set new element's coords
		ElfGui5::current_element->x=px;
		ElfGui5::current_element->y=py;
	}

	else
	{
		//set mouse_is_down for on_click event
		ElfGui5::mouse_is_down=0;

		//check for mouse_enter and mouse_leave events
		if(eum!=ElfGui5::element_under_mouse)
		{
			//call on mouse leave
			if(ElfGui5::element_under_mouse && ElfGui5::element_under_mouse->enabled)
			{
				ElfGui5::element_under_mouse->on_mouse_leave();

				//check for mouse dragging
				if(ElfGui5::element_under_mouse->can_be_dragged && mouse.left() && ElfGui5::current_dragpacket==NULL)
					ElfGui5::element_under_mouse->on_mouse_drag_out();
			}

			//call on mouse enter
			if(eum && eum->enabled)
				eum->on_mouse_enter(mouse.x-eum->get_true_x(),mouse.y-eum->get_true_y());
		}

		//set new element under mouse
		ElfGui5::element_under_mouse=eum;

		//call on_mouse_move
		if(eum && eum->enabled)
			eum->on_mouse_move(mouse.x-eum->get_true_x(),mouse.y-eum->get_true_y());
	}
}



//***** ON KEY DOWN
void MyEventHandler::on_key_down(Key& key)
{
	//catch TAB key
	if(key.code==KEY_TAB)
	{
		
		Element* e=NULL;

		//fetch selected element
		if(ElfGui5::last_selected)
			e=ElfGui5::last_selected;

		//else fetch current element last selectable children
		else if(ElfGui5::current_element)
		{
			int index=-1;
			for(int a=0;a<ElfGui5::current_element->children.size();a++)
			{
				if(ElfGui5::current_element->children[a]->selectable)
				{
					if(ElfGui5::current_element->children[a]->tab_index>index)
						index=a;
				}
			}

			if(index>-1)
				e=ElfGui5::current_element->children[index];
		}
		

		//switch selected element
		if(e && e->parent)
		{
			bool backward=Input::get_keyboard().shift();
			Element* first=e;
			Element* next=e;

			//calculate next and first
			for(int a=0;a<e->parent->children.size();a++)
			{
				Element* child=e->parent->children[a];

				if(child->selectable)
				{
					//forward
					if(backward==false)
					{
						//set first
						if(child->tab_index<first->tab_index)
							first=child;

						//set next
						if(child->tab_index>e->tab_index)
						{
							if((next->tab_index==e->tab_index && child->tab_index>next->tab_index) || child->tab_index<next->tab_index)
								next=child;
						}
					}

					//backward
					else
					{
						//set first
						if(child->tab_index>first->tab_index)
							first=child;

						//set next
						if(child->tab_index<e->tab_index)
						{
							if((next->tab_index==e->tab_index && child->tab_index<next->tab_index) || child->tab_index>next->tab_index)
								next=child;
						}
					}
				}
			}
			
			//set next selected element
			if((backward==false && next->tab_index>e->tab_index) || (backward && next->tab_index<e->tab_index))
				next->set_selected(true);
			else
				first->set_selected(true);

		}

	}
	
	else
	{
		Element* ele=ElfGui5::last_selected;
		if(ele==NULL)
			return;

		//check if we need to send keyboard events to parent
		while(ele)
		{

			//send event
			if(ele->enabled && ele->send_keyboard_events_to_parent==false)
			{
				//send on_key_down
				ele->on_key_down(key);
				break;
			}

			ele=ele->parent;
		}
	}

}



//***** ON KEY UP
void MyEventHandler::on_key_up(Key& key)
{
	Element* ele=ElfGui5::last_selected;
	if(ele==NULL)
		return;

	//check if we need to send keyboard events to parent
	while(ele)
	{
		if(ele->enabled && ele->send_keyboard_events_to_parent==false)
		{
			//send on_key_up
			ele->on_key_up(key);
			break;
		}

		ele=ele->parent;
	}

}



//***** ON TEXT
void MyEventHandler::on_text(const Str& text)
{
	Element* ele=ElfGui5::last_selected;
	if(ele==NULL)
		return;

	//check if we need to send keyboard events to parent
	while(ele)
	{
		if(ele->enabled && ele->send_keyboard_events_to_parent==false)
		{
			//send on_text
			ele->on_text(text);
			break;
		}

		ele=ele->parent;
	}
}



//***** ON WINDOW RESIZE
void MyEventHandler::on_window_resize(int width, int height)
{
	ElfGui5::base->resize(width,height);
}



//***** ON QUIT
void MyEventHandler::on_quit()
{
	ElfGui5::ready_to_quit=true;
}








//****************************************************************
//INTERNAL FUNCTIONS
//****************************************************************


//***** SET MOUSE CURSOR
void ElfGui5::set_mouse_cursor(const Str& cursor)
{
	//resize
	if(cursor=="resize")
	{
		if(ElfGui5::current_cursor_type!="resize")
		{
			Input::set_cursor(ElfGui5::cursor_resize,8,8,true);
			ElfGui5::current_cursor_type="resize";
		}
	}

	//move
	else if(cursor=="move")
	{
		if(ElfGui5::current_cursor_type!="move")
		{
			Input::set_cursor(ElfGui5::cursor_move,8,8,true);
			ElfGui5::current_cursor_type="move";
		}
	}

	//custom
	else if(cursor=="custom")
	{
		if(ElfGui5::current_cursor_type!="custom")
		{
			Input::set_cursor(ElfGui5::cursor_custom,ElfGui5::cursor_custom_hx,ElfGui5::cursor_custom_hy,true);
			ElfGui5::current_cursor_type="custom";
		}
	}

	//arrow
	else if(ElfGui5::current_cursor_type!="arrow")
	{
		Input::set_cursor(ElfGui5::cursor_arrow,0,0,true);
		ElfGui5::current_cursor_type="arrow";
	}
}






