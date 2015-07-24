#include <pix5.h>
#include "elfgui5.h"





//constructor
Element::Element(const Str& ename,int ex,int ey,int ew,int eh)
{

	type="unknown";
	name=ename;
	enabled=true;
	visible=true;
	x=ex;
	y=ey;
	min_w=10;
	max_w=0;
	min_h=10;
	max_h=0;
	move_area=Rect(0,0,ew,eh);
	anchor=new Anchor();

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
	move_area_auto_width=false;
	move_area_auto_height=false;
	forward_event_to_parent=true;
	use_anchor=false;

	image=NULL;
	custom_cursor=NULL;

	custom_cursor_hx=0;
	custom_cursor_hy=0;

	parent=NULL;

	//...
	resize(ew,eh);

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

void Element::on_event(Event* ev)
{
	send_event(ev);
}

void Element::on_mouse_enter(int mx,int my){}
void Element::on_mouse_leave(){}
void Element::on_mouse_move(int mx,int my){}
void Element::on_mouse_down(int but,int mx,int my){}
void Element::on_mouse_up(int but,int mx,int my){}
void Element::on_mouse_click(int but,int mx,int my){}
void Element::on_mouse_doubleclick(int but,int mx,int my){}
void Element::on_mouse_wheel_down(int mx,int my){}
void Element::on_mouse_wheel_up(int mx,int my){}
void Element::on_mouse_drag_out(){}
void Element::on_mouse_drag_in(DragPacket* dragpacket){}

void Element::on_key_down(Key& key){}
void Element::on_key_up(Key& key){}
void Element::on_text(const Str& text){}

void Element::on_resize(int width,int height){}
void Element::on_parent_resize(){}








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
		#ifdef DGB
			Log::debug("Element '%s' tried to add a child that is NULL!",name);
		#endif
		return;
	}

	//check if index is valid
	if(index<0 || index>children.size())
	{
		#ifdef DGB
			Log::debug("Element '%s' tried to add a child at an invalid index (%i)!",name,index);
		#endif
		return;
	}
	
	//check if child is already added
	if(children.find(child)!=-1)
	{
		#ifdef DGB
			Log::debug("Element '%s' tried to add a child that is already added!",name);
		#endif
		return;
	}

	//check if child already has a parent
	if(child->parent!=NULL)
	{
		#ifdef DGB
			Log::debug("Element '%s' tried to add a child that already has a parent!",name);
		#endif
		return;
	}

	//add child
	children.insert(child,index);
	child->parent=this;
}



//***** REMOVE CHILD
void Element::remove_child(Element* child)
{
	//check if child is NULL
	if(child==NULL)
	{
		#ifdef DGB
			Log::debug("Element '%s' tried to remove a child that is NULL!",name);
		#endif
		return;
	}
	
	//check if child is not in the list
	int index=children.find(child);
	if(index==-1)
	{
		#ifdef DGB
			Log::debug("Element '%s' tried to remove a child that is not in the list!",name);
		#endif
		return;
	}

	//remove child
	children.remove_nodel(index);
	child->parent=NULL;

}








//****************************************************************
//FUNCTIONS
//****************************************************************



//***** DISPLAY
void Element::display()
{
	if(visible)
	{
		//display self
		int tx=get_true_x();
		int ty=get_true_y();
		ElfGui5::texture_renderer.add(image,tx,ty);

		//display resize gizmo if needed
		if(can_be_resized)
			ElfGui5::texture_renderer.add(ElfGui5::resize_gizmo,tx+w-1-ElfGui5::resize_gizmo->width(),ty+h-1-ElfGui5::resize_gizmo->height());

		//replace children
		replace_elements();

		//display children
		for(int a=0;a<children.size();a++)
			children[a]->display();
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
	draw();
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
void Element::set_enabled(bool enbl)
{
	enabled=enbl;
	draw();
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




//***** SET CUSTOM CURSOR
void Element::set_custom_cursor(const Str& filename,int hx,int hy)
{
	custom_cursor=Cache::texture(filename);
	custom_cursor_hx=hx;
	custom_cursor_hy=hy;
	use_custom_cursor=true;
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
	Mouse m=Input::get_mouse();
	return find_element_at(m.x,m.y);
}







//***** START DRAG
DragPacket* Element::start_drag(const Str& icon_path,int offx,int offy)
{
	if(can_be_dragged)
	{
		//delete current dragpacket if not null
		if(ElfGui5::current_dragpacket!=NULL)
			delete ElfGui5::current_dragpacket;

		//create new dragpacket
		DragPacket* dp=new DragPacket(icon_path,offx,offy);
		ElfGui5::current_dragpacket=dp;

		return dp;
	}

	return NULL;
}





//***** SEND EVENT
void Element::send_event(Element* sndr,const Str& cmd)
{
	//create new event
	Event* ev=new Event(sndr,cmd);

	//check if we forward event to parent
	if(parent && forward_event_to_parent)
	{
		#ifdef DBG
			Log::debug("New event sent from '%s' of type '%s' forwarded to parent '%s'",name.ptr(),cmd.ptr(),parent->name.ptr());
		#endif

		parent->on_event(ev);
	}

	//send event globally
	else
	{
		
		#ifdef DBG
			if(forward_event_to_parent)
				Log::debug("New global event sent from '%s' of type '%s' forwarded from '%s'",ev->sender->name.ptr(),cmd.ptr(),name.ptr());
			else
				Log::debug("New global event sent from '%s' of type '%s'",ev->sender->name.ptr(),cmd.ptr());
		#endif

		ElfGui5::events.add(ev);
	}

}


//***** SEND EVENT
void Element::send_event(Event* ev)
{
	send_event(ev->sender,ev->command);
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








