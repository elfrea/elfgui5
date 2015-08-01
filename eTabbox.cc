#include <pix5.h>
#include "elfgui5.h"



//constructor
eTabbox::eTabbox(const Str& ename,int ex,int ey,int ew,int eh,TabsPosition::Type tabs_pos):Element(ename,ex,ey,ew,eh)
{
	
	#define DEFAULT_TITLE_SIZE 24

	//parent class vars
	type="tabbox";
	selectable=false;
	color->extra=Color::ubyte(150,150,150);
	color->d_extra=Color::ubyte(100,100,100);
	
	//own config vars
	tabs_position=tabs_pos;
	title_size=DEFAULT_TITLE_SIZE;
	selected_tab=NULL;
	
	//own internal config vars (use config functions to modify)

	//own internal vars
	
	//own elements

	//other
	dirty=true;
}



//destructor
eTabbox::~eTabbox()
{
}








//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void eTabbox::loop()
{
}



//***** DRAW
void eTabbox::draw()
{
	//show bg
	draw_panel(image,color,false,enabled,0,title_size,w,h-title_size);

	//show tabs title
	int offset=0;
	for(int a=0;a<children.size();a++)
	{

		//SELECTED
		if(selected_tab==children[a])
		{
			int tw=font->len(children[a]->name);
			int th=font->height();
			int tabw=tw+10;
			int tabh=title_size;

			draw_panel(image,color,false,enabled,offset,0,tabw,tabh);
			image->print(font,offset+5,(tabh-th)/2,color->text,children[a]->name);

			image->line(offset+1,tabh-1,offset+tabw-2,tabh-1,color->medium);
			image->line(offset+1,tabh,offset+tabw-1,tabh,color->medium);
			image->set_pixel_fast(offset,tabh-1,color->light);
		
			offset+=tabw;
		}

		//NOT SELECTED
		else
		{
			int tw=Theme::font->small->len(children[a]->name);
			int th=Theme::font->small->height();
			int tabw=tw+10;
			int tabh=title_size;

			draw_panel(image,offset,5,tabw,tabh-5,false,enabled,color->light,color->extra,color->dark,color->d_light,color->d_extra,color->d_dark);
			image->print(Theme::font->small,offset+5,5+(tabh-5-th)/2,color->text,children[a]->name);
		
			offset+=tabw;
		}

	}
}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//void eTabbox::on_event(Event* ev){}
void eTabbox::on_mouse_enter(int mx,int my){}
void eTabbox::on_mouse_leave(){}
void eTabbox::on_mouse_move(int mx,int my){}
void eTabbox::on_mouse_down(int but,int mx,int my){}
void eTabbox::on_mouse_up(int but,int mx,int my){}
//void eTabbox::on_mouse_click(int but,int mx,int my){}
//void eTabbox::on_mouse_doubleclick(int but,int mx,int my){}
//void eTabbox::on_mouse_wheel_down(int mx,int my){}
//void eTabbox::on_mouse_wheel_up(int mx,int my){}
void eTabbox::on_mouse_drag_out(){}
void eTabbox::on_mouse_drag_in(DragPacket* dragpacket){}
void eTabbox::on_key_down(Key& key){}
void eTabbox::on_key_up(Key& key){}
void eTabbox::on_text(const Str& text){}
void eTabbox::on_resize(int width,int height){}
void eTabbox::on_parent_resize(){}
void eTabbox::on_select(){}
void eTabbox::on_unselect(){}








//****************************************************************
//FAMILY FUNCTIONS
//****************************************************************


//***** ADD CHILD (OVERRIDE)
void eTabbox::add_child(Element* child)
{
	if(child->type!="tab")
	{
		#ifdef DBG
			Log::debug("ERROR: Child '%s' is not supported by the TabBox!",child->name);
		#endif
		return;
	}

	add_tab((eTab*)child);
}



//***** INSERT CHILD (OVERRIDE)
void eTabbox::insert_child(Element* child,int index)
{
	if(child->type!="tab")
	{
		#ifdef DBG
			Log::debug("ERROR: Child '%s' is not supported by the TabBox!",child->name);
		#endif
		return;
	}

	insert_tab((eTab*)child,index);
}



//***** REMOVE CHILD (OVERRIDE)
void eTabbox::remove_child(Element* child,bool del)
{
	if(child->type!="tab")
	{
		#ifdef DBG
			Log::debug("ERROR: Child '%s' is not supported by the TabBox!",child->name);
		#endif
		return;
	}

	remove_tab((eTab*)child,del);
}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//***** INSERT TAB
void eTabbox::insert_tab(eTab* tab,int index)
{
	replace_tab(tab);
	tab->visible=false;
	Element::insert_child(tab,index);

}



//***** ADD TAB
void eTabbox::add_tab(eTab* tab)
{
	insert_tab(tab,children.size());
}



//***** ADD NEW TAB
eTab* eTabbox::add_new_tab(const Str& tname)
{
	eTab* tab=new eTab(tname);
	add_tab(tab);

	return tab;
}



//***** REMOVE TAB
void eTabbox::remove_tab(eTab* tab,bool del)
{
	if(selected_tab==tab)
	{
		int i=get_tab_index(tab);
		if(i>0)
			set_selected(i-1);
		else if(children.size()>1)
			set_selected(i+1);
		else
			set_selected(-1);
	}

	Element::remove_child(tab,del);
}



//***** REMOVE TAB
void eTabbox::remove_tab(int index,bool del)
{
	if(index<0 || index>-children.size())
		return;
	
	remove_tab((eTab*)children[index],del);
}



//***** MOVE TAB
void eTabbox::move_tab(eTab* tab,int index)
{
	int i=get_tab_index(tab);

	if(index==i || index<0 || index>=children.size())
		return;

	if(index>i)
	{
		insert_tab(tab,index);
		remove_tab(i);
	}
	else
	{
		remove_tab(i);
		insert_tab(tab,index);
	}
}



//***** MOVE TAB
void eTabbox::move_tab(int index1,int index2)
{
	if(index1>=0 && index1<children.size())
		move_tab((eTab*)children[index1],index2);
}



//***** SWITCH TAB
void eTabbox::switch_tab(eTab* tab1,eTab* tab2)
{
	int i1=get_tab_index(tab1);
	int i2=get_tab_index(tab2);

	if(i1==-1 || i2==-1)
		return;
	
	remove_tab(i1);
	insert_tab(tab2,i1);

	remove_tab(i2);
	insert_tab(tab1,i2);

}



//***** SWITCH TAB
void eTabbox::switch_tab(int index1,int index2)
{
	if(index1>=0 && index1<children.size() && index2>=0 && index2<children.size())
		switch_tab((eTab*)children[index1],(eTab*)children[index2]);
}



//***** TRANSFER TAB
void eTabbox::transfer_tab(eTab* tab,eTabbox* tabbox)
{
	remove_tab(tab);
	tabbox->add_tab(tab);
}



//***** TRANSFER TAB
void eTabbox::transfer_tab(int index,eTabbox* tabbox)
{
	if(index>=0 && index<children.size())
		transfer_tab((eTab*)children[index],tabbox);
}



//***** UNDOCK TAB
eWindow* eTabbox::undock_tab(eTab* tab,Element* eparent,int ex,int ey)
{
	//add new window
	eWindow* win=new eWindow(Str::build("Window %s",tab->name.ptr()),ex,ey,w,h-title_size,tab->name);
	eparent->add_child(win);
	
	//transfer children
	for(int a=tab->children.size()-1;a>=0;a--)
	{
		Element* child=tab->children[a];

		child->parent=NULL;
		win->add_child(child);
		tab->remove_child(child);
		child->parent=win;
	}
	
	//send tab to die
	tab->add_to_dead_list();

	return win;
}



//***** UNDOCK TAB
eWindow* eTabbox::undock_tab(int index,Element* eparent,int ex,int ey)
{
	if(index>=0 && index<children.size() && eparent)
		return undock_tab((eTab*)children[index],eparent,ex,ey);
	
	return NULL;
}



//***** DOCK TAB
eTab* eTabbox::dock_tab(eWindow* win,int index)
{
	//insert new tab
	eTab* tab=new eTab(win->get_title());
	insert_tab(tab,index);

	//transfer children
	for(int a=win->body->children.size()-1;a>=0;a--)
	{
		Element* child=win->body->children[a];

		child->parent=NULL;
		tab->add_child(child);
		win->remove_child(child);
		child->parent=tab;

	}

	//send window to die
	win->add_to_dead_list();


	return tab;
}



//***** GET TAB INDEX
int eTabbox::get_tab_index(eTab* tab)
{
	int index=-1;

	for(int a=0;a<children.size();a++)
	{
		if(tab==children[a])
			return a;
	}

	return index;
}



//***** SELECT TAB
void eTabbox::select_tab(eTab* tab)
{
	if(children.find(tab)!=-1)
	{
		selected_tab=tab;
		show_tab(tab);

		send_event("change");
		dirty=true;
	}
}



//***** SELECT TAB
void eTabbox::select_tab(int index)
{
	if(index==-1)
		selected_tab=NULL;

	if(index>=0 && index<children.size())
		set_selected((eTab*)children[index]);
		
}



//***** GET SELECTED TAB
eTab* eTabbox::get_selected_tab()
{
	return selected_tab;
}



//***** GET SELECTED INDEX
int eTabbox::get_selected_index()
{
	return children.find(selected_tab);
}



//***** SET TITLE SIZE
void eTabbox::set_title_size(int sz)
{
	title_size=sz;
	dirty=true;
}



//***** SET TABS POSITION
void eTabbox::set_tabs_position(TabsPosition::Type pos)
{
	tabs_position=pos;
	replace_tabs();
	dirty=true;
}








//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************


//***** REPLACE TABS
void eTabbox::replace_tabs()
{
	for(int a=0;a<children.size();a++)
		replace_tab((eTab*)children[a]);
}



//***** REPLACE TAB
void eTabbox::replace_tab(eTab* tab)
{
	switch(tabs_position)
	{
		//TOP
		case TabsPosition::Top:
			tab->x=0;
			tab->y=title_size;
			tab->resize(w,h-title_size);
		break;

		//DOWN
		case TabsPosition::Down:
			tab->x=0;
			tab->y=0;
			tab->resize(w,h-title_size);
		break;

		//LEFT
		case TabsPosition::Left:
			tab->x=title_size;
			tab->y=0;
			tab->resize(w-title_size,h);
		break;

		//RIGHT
		case TabsPosition::Right:
			tab->x=0;
			tab->y=0;
			tab->resize(w-title_size,h);
		break;

	}
}



//***** SHOW TAB
void eTabbox::show_tab(eTab* tab)
{
	for(int a=0;a<children.size();a++)
	{
		if(tab==children[a])
			children[a]->visible=true;
		else
			children[a]->visible=false;
	}
}



//***** SHOW TAB
void eTabbox::show_tab(int index)
{
	if(index>=0 && index<children.size())
		show_tab((eTab*)children[index]);
}



//***** GET TAB TITLE X
int eTabbox::get_tab_tile_x(eTab* tab)
{
	return 0;
}



//***** GET TAB TITLE Y
int eTabbox::get_tab_tile_y(eTab* tab)
{
	return 0;
}



//***** GET TAB TITLE W
int eTabbox::get_tab_tile_w(eTab* tab)
{
	return 0;
}



//***** GET TAB TITLE H
int eTabbox::get_tab_tile_h(eTab* tab)
{
	return 0;
}






