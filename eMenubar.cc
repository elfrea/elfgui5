#include <pix5.h>
#include "elfgui5.h"



//constructor
eMenubar::eMenubar(const Str& ename,int ex,int ey,int ew,int eh):Element(ename,ex,ey,ew,eh)
{
	#define DEFAULT_MENU_OFFSET 10
	#define DEFAULT_MENU_SPACING 15

	//parent class vars
	type="menubar";
	selectable=false;
	
	//own config vars
	
	//own internal config vars (use config functions to modify)
	selected_menu=NULL;
	menu_offset=DEFAULT_MENU_OFFSET;
	menu_spacing=DEFAULT_MENU_SPACING;

	//own internal vars
	
	//own elements
	VideoMode vm=Display::get_mode();
	menus_modal=new eModal(Str::build("%s menus modal",name.ptr()),0,0,vm.width,vm.height,true,false,this);

	//other
	dirty=true;
}



//destructor
eMenubar::~eMenubar()
{
	if(!menus_modal->parent)
		delete menus_modal;
	menus.clear_del();
	
}








//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void eMenubar::loop()
{
	if(menus_modal->parent)
	{
		Mouse &m=Input::get_mouse();
		int mx=m.x-get_true_x();
		int my=m.y-get_true_y();
		eMenu* menu=find_menu_at(mx,my);
		if(menu && menu!=selected_menu)
			menus_modal->close();
	}
}



//***** DRAW
void eMenubar::draw()
{
	//show bg
	draw_panel(image,color,false,enabled);

	//show selected menu
	Mouse &m=Input::get_mouse();
	int mx=m.x-get_true_x();
	int my=m.y-get_true_y();
	eMenu* menu=find_menu_at(mx,my);

	if(menu)
	{
		int menux=get_menu_x(menu);
		int menuw=font->len(menu->name)+10;
		int menuh=font->height();

		draw_panel(image,menux,(h-menuh)/2-3,menuw,menuh+6,true,true,color->light,color->medium,color->dark,color->d_light,color->d_medium,color->d_dark);
	}

	//show menus
	int offx=menu_offset;
	for(int a=0;a<menus.size();a++)
	{
		int tw=font->len(menus[a]->name);
		int th=font->height();
		image->print(font,offx,(h-th)/2,color->text,menus[a]->name);
		offx+=tw+menu_spacing;
	}
}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


void eMenubar::on_event(Event* ev)
{
	//CLOSE
	if(ev->command=="close")
	{
		dirty=true;
		Mouse &m=Input::get_mouse();
		int mx=m.x-get_true_x();
		int my=m.y-get_true_y();
		select_menu(find_menu_at(mx,my));
	}

	//SEND EVENT TO PARENT
	else if(ev->command=="touched" || ev->command=="trigger")
	{
		send_event(ev);
		return;
	}

	delete ev;
}



void eMenubar::on_mouse_enter(int mx,int my){}



//***** ON MOUSE LEAVE
void eMenubar::on_mouse_leave()
{
	select_menu(NULL);
}



//***** ON MOUSE MOVE
void eMenubar::on_mouse_move(int mx,int my)
{
	//eMenu* m=find_menu_at(mx,my);
	//if(selected_menu!=m)
		dirty=true;
}



//***** ON MOUSE DOWN
void eMenubar::on_mouse_down(int but,int mx,int my)
{
	if(but==1)
	{
		eMenu* m=find_menu_at(mx,my);
		select_menu(m);
	}
}



void eMenubar::on_mouse_up(int but,int mx,int my){}
//void eMenubar::on_mouse_click(int but,int mx,int my){}
//void eMenubar::on_mouse_doubleclick(int but,int mx,int my){}
//void eMenubar::on_mouse_wheel_down(int mx,int my){}
//void eMenubar::on_mouse_wheel_up(int mx,int my){}
void eMenubar::on_mouse_drag_out(){}
void eMenubar::on_mouse_drag_in(DragPacket* dragpacket,int mx,int my){}
void eMenubar::on_key_down(Key& key){}
void eMenubar::on_key_up(Key& key){}
void eMenubar::on_text(const Str& text){}
void eMenubar::on_resize(int width,int height){}
void eMenubar::on_parent_resize(){}
void eMenubar::on_select(){}
void eMenubar::on_unselect(){}



//***** ON RESOLUTION CHANGE
void eMenubar::on_resolution_change(int width,int height)
{
	menus_modal->resize(width,height);
}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//***** SHRINK
void eMenubar::shrink()
{
}



//***** SET MENU OFFSET
void eMenubar::set_menu_offset(int offx)
{
	menu_offset=offx;
	dirty=true;
}



//***** SET MENU SPACING
void eMenubar::set_menu_spacing(int spacing)
{
	menu_spacing=spacing;
	dirty=true;
}



//***** ADD MENU
void eMenubar::add_menu(eMenu* menu)
{
	menu->link=this;
	menus.add(menu);
}



//***** SELECT MENU
void eMenubar::select_menu(eMenu* menu)
{
	//if(selected_menu!=menu)
//	{
		selected_menu=menu;

		if(!menus_modal->parent)
		{
			if(menu)
			{
				menu->x=get_true_x()+get_menu_x(menu);
				menu->y=get_true_y()+h;
				menus_modal->open();
				menus_modal->add_child(menu);
			}
		}
//	}

	dirty=true;
}








//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************


//***** FIND MENU AT
eMenu* eMenubar::find_menu_at(int mx,int my)
{
	int offx=menu_offset;
	for(int a=0;a<menus.size();a++)
	{
		int tw=font->len(menus[a]->name);
		if(mx>=offx-5 && mx<offx+tw+5 && my>=0 && my<h)
			return menus[a];

		offx+=tw+menu_spacing;
	}

	return NULL;
}



//***** GET MENU X
int eMenubar::get_menu_x(eMenu* menu)
{
	int offx=menu_offset;
	for(int a=0;a<menus.size();a++)
	{
		int tw=font->len(menus[a]->name);
		if(menus[a]==menu)
			return offx-5;

		offx+=tw+menu_spacing;
	}

	return 0;
}







