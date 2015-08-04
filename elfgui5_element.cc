#include <pix5.h>
#include "elfgui5.h"





//constructor
Element::Element(const Str& ename,int ex,int ey,int ew,int eh)
{
	//config vars
	type="unknown";
	name=ename;
	selectable=true;
	font=Theme::font->normal;
	x=ex;
	y=ey;
	visible=true;
	mouse_down_bring_to_front=false;
	can_be_dragged=false;
	can_be_moved=false;
	can_be_moved_outside_parent=false;
	can_be_clicked_through=false;
	can_be_resized=false;
	send_keyboard_events_to_parent=false;
	always_on_top=false;
	always_on_bottom=false;
	use_custom_cursor=false;
	forward_event_to_parent=true;
	use_anchor=false;

	tab_index=-1;

	//internal config vars (use config functions to modify)
	color=new Colors();
	enabled=true;
	min_w=10;
	max_w=0;
	min_h=10;
	max_h=0;
	selected=false;
	move_area=Rect(0,0,ew,eh);
	anchor=new Anchor();
	move_area_auto_width=false;
	move_area_auto_height=false;
	custom_cursor=NULL;
	custom_cursor_hx=0;
	custom_cursor_hy=0;

	//internal vars
	image=NULL;
	parent=NULL;
	dirty=false;

	//other
	resize(ew,eh);
	set_theme_colors();

	#ifdef DBG
	Log::debug("##### New element created: %s",name.ptr());
	#endif
}



//destructor
Element::~Element()
{
	//free non-cached textures
	delete image;

	//free lists
	children.clear_del();

	//free misc
	delete anchor;
	delete color;

	#ifdef DBG
	Log::debug("##### Element deleted: %s",name.ptr());
	#endif
}








//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void Element::loop()
{
}



//***** DRAW
void Element::draw()
{
	image->clear(Color(0,0,0));
}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//***** ON EVENT
void Element::on_event(Event* ev)
{
	send_event(ev);
}



void Element::on_mouse_enter(int mx,int my){}
void Element::on_mouse_leave(){}
void Element::on_mouse_move(int mx,int my){}
void Element::on_mouse_down(int but,int mx,int my){}
void Element::on_mouse_up(int but,int mx,int my){}



//***** ON MOUSE CLICK
void Element::on_mouse_click(int but,int mx,int my)
{
	if(but==1)
		send_event("left click");
	else if(but==2)
		send_event("middle click");
	else if(but==3)
		send_event("right click");
}



//***** ON MOUSE DOUBLECLICK
void Element::on_mouse_doubleclick(int but,int mx,int my)
{
	if(but==1)
		send_event("left doubleclick");
	else if(but==2)
		send_event("middle doubleclick");
	else if(but==3)
		send_event("right doubleclick");
}



//***** ON MOUSE WHEEL DOWN
void Element::on_mouse_wheel_down(int mx,int my)
{
	send_event("wheel down");
}



//***** ON MOUSE WHEEL UP
void Element::on_mouse_wheel_up(int mx,int my)
{
	send_event("wheel up");
}



void Element::on_mouse_drag_out(){}
void Element::on_mouse_drag_in(DragPacket* dragpacket,int mx,int my){}
void Element::on_key_down(Key& key){}
void Element::on_key_up(Key& key){}
void Element::on_text(const Str& text){}
void Element::on_resize(int width,int height){}
void Element::on_parent_resize(){}
void Element::on_select(){}
void Element::on_unselect(){}








//****************************************************************
//FAMILY FUNCTIONS
//****************************************************************


//***** ADD CHILD
void Element::add_child(Element* child)
{
	insert_child(child,children.size());
}



//***** INSERT CHILD
void Element::insert_child(Element* child,int index)
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

	//set child tab index if necessary
	if(child->selectable && child->tab_index==-1)
		child->tab_index=index;
}



//***** REMOVE CHILD
void Element::remove_child(Element* child,bool del)
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
//CONFIG FUNCTIONS
//****************************************************************


//***** SET SELECTED
void Element::set_as_selected(bool select)
{
	if(selected!=select && selectable)
	{
		if(ElfGui5::last_selected && ElfGui5::last_selected!=this)
			ElfGui5::last_selected->set_as_selected(false);

		selected=select;
		ElfGui5::last_selected=this;
		
		//send on_select and on_unselect event
		if(select)
			on_select();
		else
			on_unselect();

		dirty=true;
	}
}



//***** SET FONT
void Element::set_font(Font* fnt,bool propagate)
{
	font=fnt;
	dirty=true;

	//check if we change the font of all children
	if(propagate)
	{
		for(int a=0;a<children.size();a++)
			children[a]->set_font(fnt,true);
	}
}



//***** SET COLOR
void Element::set_color(Color& col,const Color& newcol)
{
	col=Color(newcol);
	dirty=true;
}



//***** SET COLORS ENABLED
void Element::set_colors_enabled(const Color& c_light,const Color& c_medium,const Color& c_dark,const Color& c_text,const Color& c_editing,const Color& c_selection,const Color& c_extra,bool propagate)
{
	color->light=c_light;
	color->medium=c_medium;
	color->dark=c_dark;
	color->text=c_text;
	color->editing=c_editing;
	color->selection=c_selection;
	color->extra=c_extra;

	dirty=true;
	
	//check if we change the colors of all children
	if(propagate)
	{
		for(int a=0;a<children.size();a++)
			children[a]->set_colors_enabled(Color(c_light),Color(c_medium),Color(c_dark),Color(c_text),Color(c_editing),Color(c_selection),Color(c_extra),true);
	}
}



//***** SET COLORS DISABLED
void Element::set_colors_disabled(const Color& c_light,const Color& c_medium,const Color& c_dark,const Color& c_text,const Color& c_editing,const Color& c_selection,const Color& c_extra,bool propagate)
{
	color->d_light=c_light;
	color->d_medium=c_medium;
	color->d_dark=c_dark;
	color->d_text=c_text;
	color->d_editing=c_editing;
	color->d_selection=c_selection;
	color->d_extra=c_extra;
	
	dirty=true;
	
	//check if we change the colors of all children
	if(propagate)
	{
		for(int a=0;a<children.size();a++)
			children[a]->set_colors_disabled(Color(c_light),Color(c_medium),Color(c_dark),Color(c_text),Color(c_editing),Color(c_selection),Color(c_extra),true);
	}
}



//***** SET THEME COLORS
void Element::set_theme_colors(bool propagate)
{
	color->light=Color(Theme::color->light);
	color->medium=Color(Theme::color->medium);
	color->dark=Color(Theme::color->dark);
	color->text=Color(Theme::color->text);
	color->editing=Color(Theme::color->editing);
	color->selection=Color(Theme::color->selection);
	color->extra=Color(Theme::color->extra);

	color->d_light=Color(Theme::color->d_light);
	color->d_medium=Color(Theme::color->d_medium);
	color->d_dark=Color(Theme::color->d_dark);
	color->d_text=Color(Theme::color->d_text);
	color->d_editing=Color(Theme::color->d_editing);
	color->d_selection=Color(Theme::color->d_selection);
	color->d_extra=Color(Theme::color->d_extra);

	dirty=true;

	//check if we change the colors of all children
	if(propagate)
	{
		for(int a=0;a<children.size();a++)
			children[a]->set_theme_colors(true);
	}
}



//***** RESIZE
void Element::resize(int width,int height)
{
	//check if new size is too small
	if(width<1 || height<1)
		return;
	
	//check if new size is the same as current size
	if(width==w && height==h)
		return;

	//set move area width if necessary
	if(move_area_auto_width)
		move_area.w=width;

	//set move area height if necessary
	if(move_area_auto_height)
		move_area.h=height;

	//resize texture
	if(image!=NULL)
		delete image;
	image=Texture::create(width,height,false);
	w=width;
	h=height;

	//call on_resize
	on_resize(width,height);

	//apply children anchors and send on_parent_resize
	for(int a=0;a<children.size();a++)
	{
		children[a]->apply_anchor();
		children[a]->on_parent_resize();
	}

	//redraw texture
	dirty=true;
}



//***** BRING TO FRONT
void Element::bring_to_front()
{
	if(parent==NULL)
		return;

	Element* p=parent;
	
	p->remove_child(this);
	p->add_child(this);
}



//***** SEND TO BACK
void Element::send_to_back()
{
	if(parent==NULL)
		return;

	Element* p=parent;
	
	p->remove_child(this);
	p->insert_child(this,0);
}



//***** SET ENABLED
void Element::set_enabled(bool enbl,bool send_to_children)
{
	enabled=enbl;
	dirty=true;

	//send it to children
	if(send_to_children)
	{
		for(int a=0;a<children.size();a++)
			children[a]->set_enabled(enbl,true);
	}
}



//***** SET MIN SIZE
void Element::set_min_size(int minw,int minh)
{
	if(max_w!=0 && minw>max_w)
		minw=max_w;
	if(max_h!=0 && minh>max_h)
		minh=max_h;
	
	min_w=minw;
	min_h=minh;
}



//***** SET MAX SIZE
void Element::set_max_size(int maxw,int maxh)
{
	if(maxw>0)
		if(maxw<min_w)
			maxw=min_w;
	if(maxh>0)
		if(maxh<min_h)
			maxh=min_h;
	
	max_w=maxw;
	max_h=maxh;
}



//***** SET MINMAX SIZE
void Element::set_minmax_size(int minw,int minh,int maxw,int maxh)
{
	if(maxw>0)
		if(maxw<minw)
			maxw=minw;
	if(maxh>0)
		if(maxh<minh)
			maxh=minh;
	
	min_w=minw;
	min_h=minh;
	max_w=maxw;
	max_h=maxh;
}



//***** SET MOVE AREA
void Element::set_move_area(int mx,int my,int mw,int mh)
{
	//check mx
	if(mx<0)
		mx=0;
	if(mx>=w)
		mx=w-1;

	//check my
	if(my<0)
		my=0;
	if(my>=h)
		my=h-1;
	
	//check mw
	if(mw<0)
		mw=0;
	if(mw>w-mx)
		mw=w-mx;
	
	//check mh
	if(mh<0)
		mh=0;
	if(mh>h-my)
		mh=h-my;

	move_area=Rect(mx,my,mw,mh);
}



//***** SET MOVE AREA AUTOSIZE
void Element::set_move_area_autosize(bool autow,bool autoh)
{
	move_area_auto_width=autow;
	move_area_auto_height=autoh;
	
	//set move area width if necessary
	if(move_area_auto_width)
		move_area.w=w;

	//set move area height if necessary
	if(move_area_auto_height)
		move_area.h=h;

}



//***** SET CUSTOM CURSOR
void Element::set_custom_cursor(const Str& filename,int hx,int hy)
{
	custom_cursor=Texture::cache(filename);
	custom_cursor_hx=hx;
	custom_cursor_hy=hy;
	use_custom_cursor=true;
}



//***** START DRAG
DragPacket* Element::start_drag(Texture* picon,int offx,int offy)
{
	if(can_be_dragged)
	{
		//delete current dragpacket if not null
		if(ElfGui5::current_dragpacket!=NULL)
			delete ElfGui5::current_dragpacket;

		//create new dragpacket
		DragPacket* dp=new DragPacket(picon,offx,offy);
		dp->sender=this;
		ElfGui5::current_dragpacket=dp;

		return dp;
	}

	return NULL;
}



//***** START DRAG
DragPacket* Element::start_drag(const Str& icon_path,int offx,int offy)
{
	return start_drag(Texture::load(icon_path),offx,offy);
}



//***** SEND EVENT
void Element::send_event(Element* sndr,const Str& cmd)
{
	//return if element is in the dead list
	if(ElfGui5::dead_list.find(this)!=-1)
		return;

	//create new event
	Event* ev=new Event(sndr,cmd);

	//check if we forward event to parent
	if(parent && forward_event_to_parent)
	{
		#ifdef DBG
//			Log::debug("New event sent from '%s' of type '%s' forwarded to parent '%s'",name.ptr(),cmd.ptr(),parent->name.ptr());
		#endif

		parent->on_event(ev);
	}

	//send event globally
	else
	{
		
		#ifdef DBG
//			if(forward_event_to_parent)
//				Log::debug("New global event sent from '%s' of type '%s' forwarded from '%s'",ev->sender->name.ptr(),cmd.ptr(),name.ptr());
//			else
//				Log::debug("New global event sent from '%s' of type '%s'",ev->sender->name.ptr(),cmd.ptr());
		#endif

		ElfGui5::events.add(ev);
	}

}



//***** SEND EVENT
void Element::send_event(Event* ev)
{
	send_event(ev->sender,ev->command);
	delete ev;
}



//***** SEND EVENT
void Element::send_event(const Str& cmd)
{
	send_event(this,cmd);
}



//***** SET ANCHOR
void Element::set_anchor(bool t,bool b,bool l,bool r,bool use)
{
	if(parent)
		anchor->set(t,y,b,parent->h-(y+h),l,x,r,parent->w-(x+w));
	else
		anchor->set(t,0,b,0,l,0,r,0);
	
	use_anchor=use;
}



//***** SET ANCHOR
void Element::set_anchor(bool t,int ty,bool b,int by,bool l,int lx,bool r,int rx,bool use)
{
	anchor->set(t,ty,b,by,l,lx,r,rx);
	use_anchor=use;
	apply_anchor();
}








//****************************************************************
//INTERNAL FUNCTIONS
//****************************************************************


//***** LOOPS
void Element::loops()
{
	if(enabled)
	{
		//loop self
		loop();

		//loops children
		for(int a=0;a<children.size();a++)
			children[a]->loops();
	}
}



//***** DISPLAY
void Element::display(Rect cliprect)
{
	if(visible)
	{
		//check if element is dirty
		if(dirty)
		{
			draw();
			dirty=false;
		}
			
		//dont draw element if it is completely hidden by a brother
		bool ok=true;
		if(parent)
		{
			for(int a=parent->children.size()-1;a>=0;a--)
			{
				//break if remaining elements are under current element
				Element* e=parent->children[a];
				if(e==this)
					break;

				//dont bother calculating if element is not visible
				if(!e->visible)
					continue;

				//dont draw this element hides the current element
				if(e->x<=x && (e->x+e->w)>=(x+w) && e->y<=y && (e->y+e->h)>=(y+h))
				{
					ok=false;
					break;
				}
			}
		}

		//set coordonates and draw if it's not hidden by a brother
		if(ok)
		{
			//set coordonates
			int dx=get_true_x();
			int dy=get_true_y();
			int sw=image->width();
			int sh=image->height();


			Rect res;
			int res_x=0;
			int res_y=0;
			if(Rect::clip(Rect(dx,dy,sw,sh),cliprect,res,&res_x,&res_y))
			{
				image->draw(res.x,res.y,Rect(res_x,res_y,res.w,res.h));

				//replace children
				replace_elements();

				//display children
				for(int a=0;a<children.size();a++)
					children[a]->display(res);
			}
		}

	}
}



//***** REPLACE ELEMENTS
void Element::replace_elements()
{
	List<Element*> eles_bottom;
	List<Element*> eles;
	List<Element*> eles_top;
	List<Element*> eles_new;
	
	//separate bottom,top and normal elements
	for(int a=0;a<children.size();a++)
	{
		Element* ele=children[a];

		if(ele->always_on_top)
			eles_top.add(ele);
		else if(ele->always_on_bottom)
			eles_bottom.add(ele);
		else
			eles.add(ele);
	}

	//clear children list
	children.clear_nodel();

	//add bottom elements to list
	for(int a=0;a<eles_bottom.size();a++)
		children.add(eles_bottom[a]);
	eles_bottom.clear_nodel();

	//add normal elements to list
	for(int a=0;a<eles.size();a++)
		children.add(eles[a]);
	eles.clear_nodel();

	//add top elements to list
	for(int a=0;a<eles_top.size();a++)
		children.add(eles_top[a]);
	eles_top.clear_nodel();

}



//***** GET TRUE X
int Element::get_true_x()
{
	int tx=x;
	Element* p=parent;

	while(p!=NULL)
	{
		tx+=p->x;
		p=p->parent;
	}

	return tx;
}



//***** GET TRUE Y
int Element::get_true_y()
{
	int ty=y;
	Element* p=parent;

	while(p!=NULL)
	{
		ty+=p->y;
		p=p->parent;
	}

	return ty;
}



//***** FIND ELEMENT AT
Element* Element::find_element_at(int x,int y)
{
	if(x<0 || x>=x+w || y<0 || y>=y+h)
		return NULL;
	
	//find element
	Element* ele=this;
	while(1)
	{
		bool found=false;
		Element* e;

		//find next children at coordonates
		for(int a=(ele->children.size()-1);a>=0;a--)
		{
			e=ele->children[a];

			//check if the child is visible
			if(e->visible==false)
				continue;

			//check if the child can be clicked through
			if(e->can_be_clicked_through)
				continue;

			//check if the child is under mouse
			if(x>=e->x && x<(e->x+e->w) && y>=e->y && y<(e->y+e->h))
			{
				found=true;
				break;
			}

		}

		//a child has been found
		if(found)
		{
			ele=e;
			x-=ele->x;
			y-=ele->y;
		}

		//no child has been found
		else
			break;
	}

	return ele;
}



//***** FIND_ELEMENT_UNDER_MOUSE
Element* Element::find_element_under_mouse()
{
	Mouse& m=Input::get_mouse();
	return find_element_at(m.x,m.y);
}



//***** APPLY ANCHOR
void Element::apply_anchor()
{
	if(use_anchor && parent)
	{
		//left + right
		if(anchor->left && anchor->right)
		{
			x=anchor->left_x;
			resize(parent->w-x-anchor->right_x,h);
		}

		//right
		else if(anchor->right)
		{
			x=parent->w-w-anchor->right_x;
		}

		//left
		else if(anchor->left)
		{
			x=anchor->left_x;
		}




		//top+bottom
		if(anchor->top && anchor->bottom)
		{
			y=anchor->top_y;
			resize(w,parent->h-y-anchor->bottom_y);
		}

		//bottom
		else if(anchor->bottom)
		{
			y=parent->h-h-anchor->bottom_y;
		}

		//top
		else if(anchor->top)
		{
			y=anchor->top_y;
		}

	}


}



//***** ADD TO DEAD LIST
void Element::add_to_dead_list()
{
	ElfGui5::add_element_in_dead_list(this);

}







