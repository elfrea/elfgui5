#include <pix5.h>
#include "elfgui5.h"



//constructor
eWindow::eWindow(const Str& ename,int ex,int ey,int ew,int eh,const Str& etitle):Element(ename,ex,ey,ew,eh)
{
	#define DEFAULT_TITLEBAR_H 25
	#define DEFAULT_STATUSBAR_H 15

	//parent class vars
	type="window";
	mouse_down_bring_to_front=true;
	can_be_moved_outside_parent=true;
	can_be_moved=true;
	can_be_resized=true;
	autoscrolling=true;
	children_block_resize=false;
	set_move_area(DEFAULT_TITLEBAR_H,0,ew-DEFAULT_TITLEBAR_H,DEFAULT_TITLEBAR_H);
	//move_area_auto_width=true;
	can_be_dragged=true;
	
	//own config vars
	maximized=false;
	minimized=false;
	shaded=false;

	selectable=false;
	show_button_close=true;
	show_button_maximize=true;
	show_button_minimize=true;
	show_button_shade=true;

	//own internal config vars (use config functions to modify)
	autoscroll_x=0;
	autoscroll_y=0;
	autoscrolling=false;


	//own internal vars
	maximized_x=0;
	maximized_y=0;
	maximized_w=0;
	maximized_h=0;
	shaded_h=0;

	//own elements
	titlebar=new ePanel(ename+".titlebar",0,0,ew,DEFAULT_TITLEBAR_H);
	titlebar->can_be_clicked_through=true;
	add_child_on_window(titlebar);
	titlebar->set_anchor(true,false,true,true);
		
	body=new ePanel(ename+".body",0,DEFAULT_TITLEBAR_H,ew,eh-(DEFAULT_TITLEBAR_H+DEFAULT_STATUSBAR_H));
	add_child_on_window(body);
	body->set_anchor(true,true,true,true);

	statusbar=new ePanel(ename+".statusbar",0,eh-DEFAULT_STATUSBAR_H,ew,DEFAULT_STATUSBAR_H);
	statusbar->can_be_clicked_through=true;
	statusbar->can_be_resized=true;
	statusbar->set_font(Theme::font->small);
	add_child_on_window(statusbar);
	statusbar->set_anchor(false,true,true,true);

	button_close=new eButton(ename+".button_close",0,0,10,10,"");
	button_close->set_show_text(false);
	button_close->set_custom("gfx/elements/window_button_close_normal.png","gfx/elements/window_button_close_pushed.png","gfx/elements/window_button_close_hover.png","gfx/elements/window_button_close_disabled.png");
	button_close->always_on_top=true;
	button_close->selectable=false;
	add_child_on_window(button_close);

	button_maximize=new eButton(ename+".button_maximize",0,0,10,10,"");
	button_maximize->set_show_text(false);
	button_maximize->set_custom("gfx/elements/window_button_maximize_normal.png","gfx/elements/window_button_maximize_pushed.png","gfx/elements/window_button_maximize_hover.png","gfx/elements/window_button_maximize_disabled.png");
	button_maximize->always_on_top=true;
	button_maximize->selectable=false;
	add_child_on_window(button_maximize);

	button_minimize=new eButton(ename+".button_minimize",0,0,10,10,"");
	button_minimize->set_show_text(false);
	button_minimize->set_custom("gfx/elements/window_button_minimize_normal.png","gfx/elements/window_button_minimize_pushed.png","gfx/elements/window_button_minimize_hover.png","gfx/elements/window_button_minimize_disabled.png");
	button_minimize->always_on_top=true;
	button_minimize->selectable=false;
	add_child_on_window(button_minimize);

	button_shade=new eButton(ename+".button_shade",0,0,10,10,"");
	button_shade->set_show_text(false);
	button_shade->set_custom("gfx/elements/window_button_shade_normal.png","gfx/elements/window_button_shade_pushed.png","gfx/elements/window_button_shade_hover.png","gfx/elements/window_button_shade_disabled.png");
	button_shade->always_on_top=true;
	button_shade->selectable=false;
	add_child_on_window(button_shade);

	auto_scrollbar_h=new eScrollbar("auto-scrollbar h",10,10,10,20,0,1,Orientation::Horizontal);
	auto_scrollbar_h->visible=false;
	auto_scrollbar_h->always_on_top=true;
	add_child_on_window(auto_scrollbar_h);

	auto_scrollbar_v=new eScrollbar("auto-scrollbar v",10,10,20,10,0,1,Orientation::Vertical);
	auto_scrollbar_v->visible=false;
	auto_scrollbar_v->always_on_top=true;
	add_child_on_window(auto_scrollbar_v);
	
	auto_scroll_panel=new ePanel("auto-scroll panel",10,10,10,10);
	auto_scroll_panel->visible=false;
	auto_scroll_panel->always_on_top=true;
	add_child_on_window(auto_scroll_panel);
	
	//other
	set_min_size(150,100);
	set_title(etitle);
	set_icon("gfx/elements/icon_window.png");
	refresh_buttons();
	dirty=true;
}



//destructor
eWindow::~eWindow()
{
}








//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void eWindow::loop()
{
}



//***** DRAW
void eWindow::draw()
{
	image->clear(Color(0,0,0,0));

}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//***** ON EVENT
void eWindow::on_event(Event* ev)
{
	//bring to front
	if(mouse_down_bring_to_front)
		bring_to_front();

	//CLOSE BUTTON
	if(ev->sender==button_close && ev->command=="trigger")
	{
		close();
	}

	//MAXIMIZE BUTTON
	else if(ev->sender==button_maximize && ev->command=="trigger")
	{
		maximize();
	}

	//MINIMIZE BUTTON
	else if(ev->sender==button_minimize && ev->command=="trigger")
	{
		minimize();
	}

	//SHADE BUTTON
	else if(ev->sender==button_shade && ev->command=="trigger")
	{
		shade();
	}

	//AUTO SCROLLBAR_H
	else if(ev->sender==auto_scrollbar_h && ev->command=="change")
	{
		body->set_virtual_offset_to_children(auto_scrollbar_h->value,auto_scrollbar_v->value);
	}

	//AUTO SCROLLBAR_V
	else if(ev->sender==auto_scrollbar_v && ev->command=="change")
	{
		body->set_virtual_offset_to_children(auto_scrollbar_h->value,auto_scrollbar_v->value);
	}


	//SEND EVENT TO PARENT
	else
	{
		send_event(ev);
		return;
	}


	delete ev;
}



void eWindow::on_mouse_enter(int mx,int my){}
void eWindow::on_mouse_leave(){}
void eWindow::on_mouse_move(int mx,int my){}



//***** ON MOUSE DOWN
void eWindow::on_mouse_down(int but,int mx,int my)
{
	//shade with middle button
	if(but==2)
	{
		if(button_shade->visible && button_shade->enabled)
			shade();
	}
}



void eWindow::on_mouse_up(int but,int mx,int my){}
//void eWindow::on_mouse_click(int but,int mx,int my){}



//***** ON MOUSE DOUBLECLICK
void eWindow::on_mouse_doubleclick(int but,int mx,int my)
{
	if(button_maximize->enabled && button_maximize->visible)
		maximize();
}



//void eWindow::on_mouse_wheel_down(int mx,int my){}
//void eWindow::on_mouse_wheel_up(int mx,int my){}



//***** OIN MOUSE DRAG OUT
void eWindow::on_mouse_drag_out()
{
	//create drag texture
	int tw=font->len(get_title());
	int th=font->height();
	Texture* ttex=Texture::create(tw,th);
	ttex->print(font,0,0,color->text,get_title());
	Texture* tex=Texture::create(ttex->width()+4,ttex->height()+4,false);
	draw_panel(tex,color,false,true);
	tex->blit(2,2,ttex);
	delete ttex;

	DragPacket* dp=start_drag(tex,0,0);
	dp->command="#move window";
//	dp->element=this;
}



void eWindow::on_mouse_drag_in(DragPacket* dragpacket,int mx,int my){}
void eWindow::on_key_down(Key& key){}
void eWindow::on_key_up(Key& key){}
void eWindow::on_text(const Str& text){}



//***** ON RESIZE
void eWindow::on_resize(int width,int height)
{
	set_move_area(titlebar->h,0,w-titlebar->h,titlebar->h);
	
	//refresh autoscrolling feature
	refresh_autoscrolling();

}



void eWindow::on_parent_resize(){}
void eWindow::on_select(){}
void eWindow::on_unselect(){}
void eWindow::on_resolution_change(int width,int height){}

bool eWindow::on_close(){return true;}
bool eWindow::on_maximize(){return true;}
bool eWindow::on_minimize(){return true;}
bool eWindow::on_shade(){return true;}








//****************************************************************
//FAMILY FUNCTIONS
//****************************************************************


//***** ADD CHILD (ON BODY)
void eWindow::add_child(Element* child)
{
	body->insert_child(child,body->children.size());
}



//***** INSERT CHILD (OVERRIDE)
void eWindow::insert_child(Element* child,int index)
{
	body->insert_child(child,index);
}



//***** REMOVE CHILD (OVERRIDE)
void eWindow::remove_child(Element* child,bool del)
{
	body->remove_child(child,del);
}






//***** ADD CHILD (ON WINDOW)
void eWindow::add_child_on_window(Element* child)
{
	insert_child_on_window(child,children.size());
}



//***** INSERT CHILD (ON WINDOW)
void eWindow::insert_child_on_window(Element* child,int index)
{
	//check if child is NULL
	if(child==NULL)
	{
		#ifdef DBG
			Log::debug("Element '%s' tried to add a child that is NULL!",name.ptr());
		#endif
		return;
	}

	//check if index is valid
	if(index<0 || index>children.size())
	{
		#ifdef DBG
			Log::debug("Element '%s' tried to add a child at an invalid index (%i)!",name.ptr(),index);
		#endif
		return;
	}
	
	//check if child is already added
	if(children.find(child)!=-1)
	{
		#ifdef DBG
			Log::debug("Element '%s' tried to add a child that is already added!",name.ptr());
		#endif
		return;
	}

	//check if child already has a parent
	if(child->parent!=NULL)
	{
		#ifdef DBG
			Log::debug("Element '%s' tried to add a child that already has a parent!",name.ptr());
		#endif
		return;
	}

	//add child
	children.insert(child,index);
	child->parent=this;
}



//***** REMOVE CHILD (ON WINDOW)
void eWindow::remove_child_on_window(Element* child,bool del)
{
	//check if child is NULL
	if(child==NULL)
	{
		#ifdef DBG
			Log::debug("Element '%s' tried to remove a child that is NULL!",name.ptr());
		#endif
		return;
	}
	
	//check if child is not in the list
	int index=children.find(child);
	if(index==-1)
	{
		#ifdef DBG
			Log::debug("Element '%s' tried to remove a child that is not in the list!",name.ptr());
		#endif
		return;
	}

	//remove child
	child->parent=NULL;

	if(del)
		children.remove_del(index);
	else
		children.remove_nodel(index);

}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//***** SHRINK
void eWindow::shrink()
{
}


//***** GET TITLE
Str eWindow::get_title()
{
	return titlebar->text;
}



//***** SET TITLE
void eWindow::set_title(const Str& etitle,Align::Type align,int offx,int offy)
{
	titlebar->set_text(etitle,align,offx,offy);
}



//***** SET ICON
void eWindow::set_icon(Texture* tex,Align::Type align,int offx,int offy)
{
	titlebar->set_tex(tex,align,offx,offy);
}



//***** SET ICON
void eWindow::set_icon(const Str& filename,Align::Type align,int offx,int offy)
{
	titlebar->set_tex(filename,align,offx,offy);
}



//***** SET TITLEBAR HEIGHT
void eWindow::set_titlebar_height(int th)
{
	titlebar->resize(w,th);
	titlebar->set_anchor(true,false,true,true);
	set_move_area(0,0,w,th);
	body->y=th;
	body->resize(w,h-th-statusbar->h);
	body->set_anchor(true,true,true,true);
}



//***** SET STATUSBAR HEIGHT
void eWindow::set_statusbar_height(int sh)
{
	body->resize(w,h-sh-titlebar->h);
	body->set_anchor(true,true,true,true);
	statusbar->y=h-sh;
	statusbar->resize(w,sh);
	statusbar->set_anchor(false,true,true,true);
}



//***** SET STATUSBAR MESSAGE
void eWindow::set_statusbar_message(const Str& msg)
{
	statusbar->set_text(msg,Align::Left,5);
}



//***** SET SHOW BUTTONS
void eWindow::set_show_buttons(bool bclose,bool bmax,bool bmin,bool bshade)
{
	show_button_close=bclose;
	show_button_maximize=bmax;
	show_button_minimize=bmin;
	show_button_shade=bshade;

	refresh_buttons();
}



//***** CLOSE
void eWindow::close()
{
	if(button_close->visible && button_close->enabled)
	{
		if(on_close())
			add_to_dead_list();
	}
}



//***** MAXIMIZE
void eWindow::maximize()
{
	if(button_maximize->visible && button_maximize->enabled)
	{
		if(on_maximize() && parent)
		{
			maximized=!maximized;

			//save current position and size and maximize the window
			if(maximized)
			{
				maximized_x=x;
				maximized_y=y;
				maximized_w=w;
				maximized_h=h;

				x=0;
				y=0;
				resize(parent->w,parent->h);
				can_be_moved=false;
				can_be_resized=false;
			}

			//fetch old position and size and unmaximize the window
			else
			{
				x=maximized_x;
				y=maximized_y;
				resize(maximized_w,maximized_h);
				can_be_moved=true;
				can_be_resized=true;
			}
		}
	}
}



//***** MINIMIZE
void eWindow::minimize()
{
	if(button_minimize->visible && button_minimize->enabled)
	{
		if(on_minimize())
		{
			minimized=!minimized;

			//minimize window
			if(minimized)
			{
				visible=false;
			}

			//unminimize window
			else
			{
				visible=true;
			}
		}
	}
}



//***** SHADE
void eWindow::shade()
{
	if(button_shade->visible && button_shade->enabled)
	{
		if(on_minimize())
		{
			shaded=!shaded;

			//save current height and shade window
			if(shaded)
			{
				shaded_h=h;

				body->visible=false;
				statusbar->visible=false;

				resize(w,titlebar->h);
				can_be_resized=false;

				button_maximize->set_enabled(false);
			}

			//fetch old height and unshade window
			else
			{
				body->visible=true;
				statusbar->visible=true;
				
				resize(w,shaded_h);
				can_be_resized=true;

				button_maximize->set_enabled(true);
			}
		}
	}
}








//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************


//***** REFRESH BUTTONS
void eWindow::refresh_buttons()
{
	int offset=5;
	int buth=(titlebar->h-button_close->h)/2+1;

	//close
	if(show_button_close)
	{
		button_close->visible=true;
		button_close->set_anchor(true,buth,false,0,false,0,true,offset);
		offset+=button_close->w;
	}
	else
		button_close->visible=false;

	//maximize
	if(show_button_maximize)
	{
		button_maximize->visible=true;
		button_maximize->set_anchor(true,buth,false,0,false,0,true,offset);
		offset+=button_maximize->w;
	}
	else
		button_maximize->visible=false;

	//minimize
	if(show_button_minimize)
	{
		button_minimize->visible=true;
		button_minimize->set_anchor(true,buth,false,0,false,0,true,offset);
		offset+=button_minimize->w;
	}
	else
		button_minimize->visible=false;

	//shade
	if(show_button_shade)
	{
		button_shade->visible=true;
		button_shade->set_anchor(true,buth,false,0,false,0,true,offset);
		offset+=button_shade->w;
	}
	else
		button_shade->visible=false;

}



//***** REFRESH AUTOSCROLLING
void eWindow::refresh_autoscrolling()
{
	if(!auto_scrollbar_h->visible)
		auto_scrollbar_h->value=0;
	if(!auto_scrollbar_v->visible)
		auto_scrollbar_v->value=0;

	bool h_seems_visible=false;
	bool v_seems_visible=false;
	int total_w=0;
	int total_h=0;
	int minx=body->w;
	int maxx=0;
	int miny=body->h;
	int maxy=0;
	
	//check if any children is outside window
	for(int a=0;a<body->children.size();a++)
	{
		Element* child=body->children[a];

		//disregard if children use anchor right or bottom
		if(child->use_anchor && (child->anchor->right || child->anchor->bottom))
			continue;

		if(child->y+child->h>=body->h-(auto_scrollbar_h->visible?auto_scrollbar_h->h:0))
			v_seems_visible=true;

		if(child->x+child->w>=body->w-(auto_scrollbar_v->visible?auto_scrollbar_v->w:0))
			h_seems_visible=true;


		//find minx / maxx
		if(child->x<minx)
			minx=child->x;
		if(child->x+child->w-1>maxx)
			maxx=child->x+child->w-1;

		//find miny / maxy
		if(child->y<miny)
			miny=child->y;
		if(child->y+child->h-1>maxy)
			maxy=child->y+child->h-1;
	}

	auto_scrollbar_h->visible=h_seems_visible;
	auto_scrollbar_v->visible=v_seems_visible;

	total_w=maxx+1+(auto_scrollbar_v->visible?auto_scrollbar_v->w:0);
	total_h=maxy+1+(auto_scrollbar_h->visible?auto_scrollbar_h->h:0);

	//check horizontal
	if(auto_scrollbar_h->visible)
	{
		auto_scrollbar_h->x=body->x;
		auto_scrollbar_h->y=body->y+body->h-auto_scrollbar_h->h;
		auto_scrollbar_h->resize(body->w-(auto_scrollbar_v->visible?auto_scrollbar_v->w:0),auto_scrollbar_h->h);
		auto_scrollbar_h->set_page_size(body->w);
		auto_scrollbar_h->set_value_range(0,total_w-body->w);
	}

	//check vertical
	if(auto_scrollbar_v->visible)
	{
		auto_scrollbar_v->x=body->x+body->w-auto_scrollbar_v->w;
		auto_scrollbar_v->y=body->y;
		auto_scrollbar_v->resize(auto_scrollbar_v->w,body->h-(auto_scrollbar_h->visible?auto_scrollbar_h->h:0));
		auto_scrollbar_v->set_page_size(body->h);
		auto_scrollbar_v->set_value_range(0,total_h-body->h);
	}

	//autoscroll panel
	if(auto_scrollbar_h->visible && auto_scrollbar_v->visible)
	{
		auto_scroll_panel->x=body->x+body->w-auto_scrollbar_v->w;
		auto_scroll_panel->y=body->y+body->h-auto_scrollbar_h->h;
		auto_scroll_panel->resize(auto_scrollbar_v->w,auto_scrollbar_h->h);
		auto_scroll_panel->visible=true;
	}
	else
		auto_scroll_panel->visible=false;

	//set virtual mode
	if(auto_scrollbar_h->visible || auto_scrollbar_v->visible)
	{
		body->set_virtual_mode_to_children(true);
		body->set_virtual_offset_to_children(auto_scrollbar_h->value,auto_scrollbar_v->value);
	}
	else
		body->set_virtual_mode_to_children(false);
	
}










