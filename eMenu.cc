#include <pix5.h>
#include "elfgui5.h"



//constructor
eMenu::eMenu(const Str& ename,int ex,int ey,int ew,int eh,Element* elink,bool autosz,bool issub):Element(ename,ex,ey,ew,eh)
{
	//parent class vars
	type="menu";
	selectable=false;
	min_w=40;
	min_h=40;
	
	//own config vars

	//own internal config vars (use config functions to modify)
	link=elink;
	auto_size=autosz;

	//own internal vars
	is_sub_menu=issub;
	
	//own elements

	//other
	dirty=true;
}



//destructor
eMenu::~eMenu()
{
}








//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void eMenu::loop()
{
}



//***** DRAW
void eMenu::draw()
{
	draw_panel(image,color,false,enabled);

}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//***** ON EVENT
void eMenu::on_event(Event* ev)
{
	//submenu
	if(ev->command=="open submenu")
	{
		open_submenu((eMenuSub*)ev->sender);
		delete ev;
	}

	//forward event to link
	else if(link)
		send_event_to(link,ev);

	//forward to parent
	else
		send_event(ev);
	
}



void eMenu::on_mouse_enter(int mx,int my){}
void eMenu::on_mouse_leave(){}
void eMenu::on_mouse_move(int mx,int my){}
void eMenu::on_mouse_down(int but,int mx,int my){}
void eMenu::on_mouse_up(int but,int mx,int my){}
//void eMenu::on_mouse_click(int but,int mx,int my){}
//void eMenu::on_mouse_doubleclick(int but,int mx,int my){}
//void eMenu::on_mouse_wheel_down(int mx,int my){}
//void eMenu::on_mouse_wheel_up(int mx,int my){}
void eMenu::on_mouse_drag_out(){}
void eMenu::on_mouse_drag_in(DragPacket* dragpacket,int mx,int my){}
void eMenu::on_key_down(Key& key){}
void eMenu::on_key_up(Key& key){}
void eMenu::on_text(const Str& text){}
void eMenu::on_resize(int width,int height){}
void eMenu::on_parent_resize(){}
void eMenu::on_select(){}
void eMenu::on_unselect(){}
void eMenu::on_resolution_change(int width,int height){}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//***** SHRINK
void eMenu::shrink()
{
}



//***** INSERT BUTTON
eMenuButton* eMenu::insert_button(const Str& ename,int ew,int eh,const Str& etext,int index)
{
	eMenuButton* ele=new eMenuButton(ename,ew,eh,etext);
	insert_child(ele,index);
	replace_children(auto_size);
	return ele;
}



//***** ADD BUTTON
eMenuButton* eMenu::add_button(const Str& ename,int ew,int eh,const Str& etext)
{
	return insert_button(ename,ew,eh,etext,children.size());
}



//***** INSERT SEPARATOR
eMenuSeparator* eMenu::insert_separator(int eh,int index)
{
	eMenuSeparator* ele=new eMenuSeparator(eh);
	insert_child(ele,index);
	replace_children(auto_size);
	return ele;
}



//***** ADD SEPARATOR
eMenuSeparator* eMenu::add_separator(int eh)
{
	return insert_separator(eh,children.size());
}



//***** INSERT CHECKBOX
eMenuCheckbox* eMenu::insert_checkbox(const Str& ename,int ew,int eh,const Str& etext,bool echecked,int index)
{
	eMenuCheckbox* ele=new eMenuCheckbox(ename,ew,eh,etext,echecked);
	insert_child(ele,index);
	replace_children(auto_size);
	return ele;
}



//***** ADD CHECKBOX
eMenuCheckbox* eMenu::add_checkbox(const Str& ename,int ew,int eh,const Str& etext,bool echecked)
{
	return insert_checkbox(ename,ew,eh,etext,echecked,children.size());
}



//***** INSERT RADIO
eMenuRadio* eMenu::insert_radio(const Str& ename,int ew,int eh,const Str& etext,const Str& egroup,bool echecked,int index)
{
	eMenuRadio* ele=new eMenuRadio(ename,ew,eh,etext,egroup,echecked);
	insert_child(ele,index);
	replace_children(auto_size);
	return ele;
}



//***** ADD RADIO
eMenuRadio* eMenu::add_radio(const Str& ename,int ew,int eh,const Str& etext,const Str& egroup,bool echecked)
{
	return insert_radio(ename,ew,eh,etext,egroup,echecked,children.size());
}



//***** INSERT SUB
eMenuSub* eMenu::insert_sub(const Str& ename,int ew,int eh,const Str& etext,eMenu* elink,int index)
{
	eMenuSub* ele=new eMenuSub(ename,ew,eh,etext,elink);

	insert_child(ele,index);
	replace_children(auto_size);
	return ele;
}



//***** ADD SUB
eMenuSub* eMenu::add_sub(const Str& ename,int ew,int eh,const Str& etext,eMenu* elink)
{
	return insert_sub(ename,ew,eh,etext,elink,children.size());
}



//***** GET INDEX
int eMenu::get_index(Element* ele)
{
	for(int a=0;a<children.size();a++)
	{
		if(children[a]==ele)
			return a;
	}

	return -1;
}



//***** REMOVE ELEMENT
void eMenu::remove_element(Element* ele,bool del)
{
	int index=get_index(ele);
	if(index>-1)
		remove_element(index,del);
	replace_children(auto_size);
}



//***** REMOVE ELEMENT
void eMenu::remove_element(int index,bool del)
{
	remove_child(index,del);
	replace_children(auto_size);
}








//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************


//***** REPLACE CHILDREN
void eMenu::replace_children(bool autosz)
{
	if(children.size())
	{
		//find max width and height
		int maxw=min_w;
		int maxh=10;
		for(int a=0;a<children.size();a++)
		{
			//shrink element if autosize is enabled
			if(autosz)
				children[a]->shrink();

			//set maxw
			if(children[a]->w>maxw)
				maxw=children[a]->w;

			//set maxh
			maxh+=children[a]->h;
		}

		//adjust maxw and maxh
		maxw+=10;
		if(maxh<min_h)
			maxh=min_h;

		//resize menu
		resize(autosz?maxw:w,maxh);

		//set children position and size
		int offset=5;
		for(int a=0;a<children.size();a++)
		{
			Element* c=children[a];

			c->x=5;
			c->y=offset;
			c->resize(w-10,c->h);

			offset+=c->h;
		}

		dirty=true;
	}

}



//***** OPEN SUBMENU
void eMenu::open_submenu(eMenuSub* sub)
{
	sub->link->x=sub->parent->x+sub->parent->w;
	sub->link->y=sub->parent->y+sub->y-5;

	parent->add_child(sub->link);
}








