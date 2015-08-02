#include <pix5.h>
#include "elfgui5.h"



//constructor
eTabbox::eTabbox(const Str& ename,int ex,int ey,int ew,int eh,TabsPosition::Type tabs_pos):Element(ename,ex,ey,ew,eh)
{
	
	#define DEFAULT_TITLE_SIZE 20

	//parent class vars
	type="tabbox";
	selectable=false;
	can_be_dragged=true;
	color->extra=Color::ubyte(150,150,150);
	color->d_extra=Color::ubyte(100,100,100);
	
	//own config vars
	ready_to_grab=false;
	can_move_tabs=false;
	can_drag_tabs=false;
	
	//own internal config vars (use config functions to modify)
	tabs_position=tabs_pos;
	title_size=DEFAULT_TITLE_SIZE;
	selected_tab=NULL;

	//own internal vars
	grabbing_tab=NULL;
	
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
	image->clear(Color(0,0,0,0));

	//show bg
	switch(tabs_position)
	{
		//TOP
		case TabsPosition::Top:
			draw_panel(image,color,false,enabled,0,title_size,w,h-title_size);
		break;

		//BOTTOM
		case TabsPosition::Bottom:
			draw_panel(image,color,false,enabled,0,0,w,h-title_size);
		break;

		//LEFT
		case TabsPosition::Left:
			draw_panel(image,color,false,enabled,title_size,0,w-title_size,h);
		break;

		//Right
		case TabsPosition::Right:
			draw_panel(image,color,false,enabled,0,0,w-title_size,h);
		break;
	}

	//show tabs title
	for(int a=0;a<children.size();a++)
	{
		int tx=get_tab_title_x((eTab*)children[a]);
		int ty=get_tab_title_y((eTab*)children[a]);
		int tw=get_tab_title_w((eTab*)children[a]);
		int th=get_tab_title_h((eTab*)children[a]);
		Color tcol=get_tab_color((eTab*)children[a]);
		Color tdcol=get_tab_dcolor((eTab*)children[a]);
		Texture* ttext=get_tab_text((eTab*)children[a]);

		//draw panel and hide stuff
		draw_panel(image,tx,ty,tw,th,false,enabled,color->light,(children[a]==selected_tab?color->medium:tcol),color->dark,color->d_light,(children[a]==selected_tab?color->d_medium:tdcol),color->d_dark);
		if(children[a]==selected_tab)
		{
			switch(tabs_position)
			{
				//TOP
				case TabsPosition::Top:
					image->line(tx+1,th-1,tx+tw-2,th-1,color->medium);
					image->line(tx+1,th,tx+tw-2,th,color->medium);
					image->set_pixel(tx,th-1,color->light);
				break;

				//BOTTOM
				case TabsPosition::Bottom:
					image->line(tx+1,ty-1,tx+tw-2,ty-1,color->medium);
					image->line(tx+1,ty,tx+tw-2,ty,color->medium);
					image->set_pixel(tx,ty-1,color->light);
					image->set_pixel(tx+tw-1,ty,color->dark);
				break;

				//LEFT
				case TabsPosition::Left:
					image->line(tx+tw-1,ty+1,tx+tw-1,ty+th-2,color->medium);
					image->line(tx+tw,ty+1,tx+tw,ty+th-2,color->medium);
					image->set_pixel(tx+tw,ty+th-1,color->dark);
				break;

				//Right
				case TabsPosition::Right:
					image->line(tx-1,ty+1,tx-1,ty+th-2,color->medium);
					image->line(tx,ty+1,tx,ty+th-2,color->medium);
					image->set_pixel(tx-1,ty,color->light);
				break;
			}
		}

		//show text
		image->blit(tx+(tw-ttext->width())/2,ty+(th-ttext->height())/2,ttext);
		delete ttext;

	}

	//show indications to where the dragging would go
	DragPacket* dp=ElfGui5::current_dragpacket;
	if(dp)
	{
		if(dp->command=="#move tab" || dp->command=="#move window")
		{
			Mouse& m=Input::get_mouse();
			eTab* tab=find_tab_at(m.x-get_true_x(),m.y-get_true_y());
			if(tab)
			{
				int tx=get_tab_title_x(tab);
				int ty=get_tab_title_y(tab);
				int tw=get_tab_title_w(tab);
				int th=get_tab_title_h(tab);
				image->rect(tx,ty,tx+tw-1,ty+th-1,color->text);
			}
			else
			{
			}
		}
	}
}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//void eTabbox::on_event(Event* ev){}
void eTabbox::on_mouse_enter(int mx,int my){}



//***** ON MOUSE LEAVE
void eTabbox::on_mouse_leave()
{
	ready_to_grab=false;
	dirty=true;
}



//***** ON MOUSE MOVE
void eTabbox::on_mouse_move(int mx,int my)
{
	grab_tab(mx,my);

	if(ElfGui5::current_dragpacket!=NULL)
		dirty=true;
}



//***** ON MOUSE DOWN
void eTabbox::on_mouse_down(int but,int mx,int my)
{
	if(but==1)
	{
		eTab* tab=find_tab_at(mx,my);
		if(tab)
		{
			select_tab(tab);
			ready_to_grab=true;
			grabbing_tab=tab;
		}
		else
		{
			ready_to_grab=false;
			grabbing_tab=NULL;
		}
	}
}



//***** ON MOUSE UP
void eTabbox::on_mouse_up(int but,int mx,int my)
{
	ready_to_grab=false;
	grabbing_tab=NULL;
}



//void eTabbox::on_mouse_click(int but,int mx,int my){}
//void eTabbox::on_mouse_doubleclick(int but,int mx,int my){}



//***** ON MOUSE WHEEL DOWN
void eTabbox::on_mouse_wheel_down(int mx,int my)
{
	if(children.size()<2)
		return;

	int index=get_selected_index()+1;

	if(index>=children.size())
		index=0;
	
	select_tab(index);

}



//***** ON MOUSE WHEEL UP
void eTabbox::on_mouse_wheel_up(int mx,int my)
{
	if(children.size()<2)
		return;

	int index=get_selected_index()-1;

	if(index<0)
		index=children.size()-1;
	
	select_tab(index);
}



//***** ON MOUSE DRAG OUT
void eTabbox::on_mouse_drag_out()
{
	ready_to_grab=true;
	grab_tab(-1,-1);
}



//***** ON MOUSE DRAG IN
void eTabbox::on_mouse_drag_in(DragPacket* dragpacket,int mx,int my)
{
	//MOVE TAB
	if(dragpacket->command=="#move tab")
	{
		//local tab drag and drop
		if(dragpacket->sender==this)
		{
			eTab* tab=find_tab_at(mx,my);

			if(tab)
				move_tab((eTab*)dragpacket->element,get_tab_index(tab));
			else
				move_tab((eTab*)dragpacket->element,children.size()-1);
		}

		//tab drag and drop from another tabbox
		else
		{
		}
	}
	
	//MOVE WINDOW
	else if(dragpacket->command=="#move window")
	{
		//make sure window is not a parent
		bool ok=true;
		Element* p=this;
		while(p!=NULL)
		{
			if(p->parent==dragpacket->sender)
			{
				ok=false;
				break;
			}

			p=p->parent;
		}

		//dock window
		if(ok)
		{
			int index=get_tab_index(find_tab_at(mx,my));
			if(index==-1)
				index=children.size();
			eTab* tab=dock_tab((eWindow*)dragpacket->sender,index);
			select_tab(tab);
		}
	}
}



//***** ON KEY DOWN
void eTabbox::on_key_down(Key& key)
{
	if(children.size()<2)
		return;

	//LEFT,UP
	if(key.code==KEY_LEFT || key.code==KEY_UP)
	{
		int index=get_selected_index()-1;

		if(index<0)
			index=children.size()-1;
		
		select_tab(index);
	}

	//RIGHT,DOWN
	if(key.code==KEY_RIGHT || key.code==KEY_DOWN)
	{
		int index=get_selected_index()+1;

		if(index>=children.size())
			index=0;
		
		select_tab(index);
	}
}



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
			Log::debug("ERROR: Child '%s' is not supported by the TabBox!",child->name.ptr());
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
			Log::debug("ERROR: Child '%s' is not supported by the TabBox!",child->name.ptr());
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
			Log::debug("ERROR: Child '%s' is not supported by the TabBox!",child->name.ptr());
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
		remove_tab(tab);
		tab->parent=NULL;
		insert_tab(tab,index-1);
	}
	else
	{
		remove_tab(tab);
		tab->parent=NULL;
		insert_tab(tab,index);
	}

	select_tab(tab);
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

	tab1->parent=NULL;
	tab2->parent=NULL;

	remove_tab(tab1);
	insert_tab(tab1,i2);
	remove_tab(tab2);
	insert_tab(tab2,i1);

	dirty=true;
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
	tab->parent=NULL;
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

		tab->remove_child(child);
		child->parent=NULL;
		win->add_child(child);
		//child->parent=win->body;
	}
	
	//send tab to die
	tab->add_to_dead_list();

	select_tab(0);

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
		select_tab((eTab*)children[index]);
		
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

		//BOTTOM
		case TabsPosition::Bottom:
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
int eTabbox::get_tab_title_x(eTab* tab)
{
	int val=0;

	switch(tabs_position)
	{
		//TOP
		//DOWN
		case TabsPosition::Top:
		case TabsPosition::Bottom:
		{
			for(int a=0;a<children.size();a++)
			{
				if(tab==children[a])
					return val;
				else
					val+=get_tab_font((eTab*)children[a])->len(children[a]->name)+10;
			}
		}
		break;

		//LEFT
		case TabsPosition::Left:
			if(tab==selected_tab)
				return 0;
			else
				return title_size-get_tab_title_w(tab);
		break;

		//RIGHT
		case TabsPosition::Right:
			return w-title_size;
		break;

	}

	return val;
}



//***** GET TAB TITLE Y
int eTabbox::get_tab_title_y(eTab* tab)
{
	int val=0;

	switch(tabs_position)
	{
		//TOP
		case TabsPosition::Top:
			if(tab==selected_tab)
				return 0;
			else
				return title_size-get_tab_title_h(tab);
		break;

		//DOWN
		case TabsPosition::Bottom:
			return h-title_size;
		break;

		//LEFT
		//RIGHT
		case TabsPosition::Left:
		case TabsPosition::Right:
			for(int a=0;a<children.size();a++)
			{
				if(tab==children[a])
					return val;
				else
					val+=get_tab_font((eTab*)children[a])->len(children[a]->name)+10;
			}
		break;

	}

	return val;
}



//***** GET TAB TITLE W
int eTabbox::get_tab_title_w(eTab* tab)
{
	Font* tfont=get_tab_font(tab);

	switch(tabs_position)
	{
		//TOP
		//DOWN
		case TabsPosition::Top:
		case TabsPosition::Bottom:
			return tfont->len(tab->name)+10;
		break;

		//LEFT
		//RIGHT
		case TabsPosition::Left:
		case TabsPosition::Right:
			if(tab==selected_tab)
				return title_size;
			else
				return tfont->height();
		break;

	}

	return 0;
}



//***** GET TAB TITLE H
int eTabbox::get_tab_title_h(eTab* tab)
{
	Font* tfont=get_tab_font(tab);

	switch(tabs_position)
	{
		//TOP
		//DOWN
		case TabsPosition::Top:
		case TabsPosition::Bottom:
			if(tab==selected_tab)
				return title_size;
			else
				return tfont->height();
		break;

		//LEFT
		//RIGHT
		case TabsPosition::Left:
		case TabsPosition::Right:
			return tfont->len(tab->name)+10;
		break;

	}
	
	return 0;
}



//***** GET TAB COLOR
Color eTabbox::get_tab_color(eTab* tab)
{
	return color->extra;
}



//***** GET TAB DCOLOR
Color eTabbox::get_tab_dcolor(eTab* tab)
{
	return color->d_extra;
}



//***** GET TAB FONT
Font* eTabbox::get_tab_font(eTab* tab)
{
	if(tab==selected_tab)
		return font;
	else
		return Theme::font->small;
}



//***** GET TAB TEXT
Texture* eTabbox::get_tab_text(eTab* tab)
{
	int tw=get_tab_title_w(tab);
	int th=get_tab_title_h(tab);
	Texture* tex=NULL;
	Font* tfont=get_tab_font(tab);

	int textw=tfont->len(tab->name);
	int texth=tfont->height();
	Texture* t=Texture::create(textw,texth);
	t->clear(Color(0,0,0,0));
	t->print(tfont,0,0,color->text,tab->name);

	Texture* rotated_t=NULL;

	switch(tabs_position)
	{
		//TOP
		//DOWN
		case TabsPosition::Top:
		case TabsPosition::Bottom:
			rotated_t=Texture::create(tw,th);
			rotated_t->blit((tw-textw)/2,(th-texth)/2,t,false);
			tex=Texture::create(tw,th);
		break;

		//LEFT
		case TabsPosition::Left:
			rotated_t=rotate_tex90(t,true);
			tex=Texture::create(tw,th);
		break;
		
		//RIGHT
		case TabsPosition::Right:
			rotated_t=rotate_tex90(t);
			tex=Texture::create(tw,th);
		break;

	}

	tex->blit((tw-rotated_t->width())/2,(th-rotated_t->height())/2,rotated_t,false);

	delete t;
	delete rotated_t;

	return tex;
}



//***** FIND TAB AT
eTab* eTabbox::find_tab_at(int mx,int my)
{
	for(int a=0;a<children.size();a++)
	{
		int tx=get_tab_title_x((eTab*)children[a]);
		int ty=get_tab_title_y((eTab*)children[a]);
		int tw=get_tab_title_w((eTab*)children[a]);
		int th=get_tab_title_h((eTab*)children[a]);

		if(mx>=tx && mx<tx+tw && my>=ty && my<ty+th)
			return (eTab*)children[a];
	}

	return NULL;
}



//***** GRAB TAB
void eTabbox::grab_tab(int mx,int my)
{
	//check for grabbing
	if(ready_to_grab)
	{
		eTab* tab=find_tab_at(mx,my);
		if(grabbing_tab)
		{
			if(!tab || tab!=grabbing_tab)
			{
				//create grab texture
				Texture* ttex=get_tab_text(grabbing_tab);
				Texture* tex=Texture::create(ttex->width()+4,ttex->height()+4,false);
				draw_panel(tex,color,false,true);
				tex->blit(2,2,ttex);
				delete ttex;

				//start drag
				DragPacket* dp=start_drag(tex,0,0);
				dp->command="#move tab";
				dp->element=grabbing_tab;

				ready_to_grab=false;
				grabbing_tab=NULL;
			}
		}
	}
}



