#include <pix5.h>
#include "elfgui5.h"



//constructor
eListbox::eListbox(const Str& ename,int ex,int ey,int ew,int eh,ListboxStyle::Type estyle):Element(ename,ex,ey,ew,eh)
{
	
	#define DEFAULT_ITEMS_H 20

	//parent class vars
	type="listbox";
	selectable=false;
	items_h=DEFAULT_ITEMS_H;
	color->extra=Color::ubyte(220,220,220);
	
	//own config vars
	multi_selection=false;
	
	//own internal config vars (use config functions to modify)
	alternate_items_bg=true;

	//own internal vars
	current_pos=0;
	selected_min=-1;
	selected_max=-1;
	mouse_selecting=false;
	
	//own elements
	scrollbar_h=new eScrollbar("scrollbar_h",10,10,10,20,0,1,Orientation::Horizontal);
	scrollbar_h->visible=false;
	add_child(scrollbar_h);

	scrollbar_v=new eScrollbar("scrollbar_v",10,10,20,10,0,1,Orientation::Vertical);
	scrollbar_v->visible=false;
	add_child(scrollbar_v);

	//other
	set_style(estyle);
	dirty=true;
}



//destructor
eListbox::~eListbox()
{
	items.clear_del();
}








//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void eListbox::loop()
{
	Mouse& m=Input::get_mouse();

	if(mouse_selecting && m.left()==false)
		mouse_selecting=false;
}



//***** DRAW
void eListbox::draw()
{	
	//show bg
	draw_edit_panel(image,color,enabled);

	//check if we need to show the scrollbars
	refresh_scrollbars();

	//show items
	int offset=0;
	int th=font->height();
	for(int a=current_pos;a<items.size();a++)
	{
		if(offset+1>=h-1)
			break;

		int y2=offset+items_h-1;
		if(y2>=h-1)
			y2=h-2;

		//alternate bg if needed
		if(alternate_items_bg && a%2!=0)
			image->rect_fill(1,offset+1,w-2,y2,color->extra);

		//show selection
		if(selected_min<selected_max)
		{
			if(a>=selected_min && a<=selected_max)
				image->rect_fill(1,offset+1,w-2,y2,color->selection);
		}
		else
		{
			if(a>=selected_max && a<=selected_min)
				image->rect_fill(1,offset+1,w-2,y2,color->selection);
		}

		//show items
		switch(style)
		{
			//TEXT
			case ListboxStyle::Text:
				//show text
				image->print(font,10,offset+(items_h-th)/2,color->text,items[a]->text);
			break;
		
			//ICON TEXT
			case ListboxStyle::IconText:

				//attribute default icon if there is none
				if(items[a]->icon==NULL)
					items[a]->icon=Texture::cache("gfx/elements/icon_none.png");

				//show icon
				image->blit(5,offset+(items_h-items[a]->icon->width())/2,items[a]->icon);

				//show text
				image->print(font,5+items[a]->icon->width()+5,offset+(items_h-th)/2,color->text,items[a]->text);
			break;
		}

		offset+=items_h;
	}
}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//***** ON EVENT
void eListbox::on_event(Event* ev)
{
	//scrollbar_h
	if(ev->sender==scrollbar_h && ev->command=="change")
	{
	}

	//scrollbar_v
	else if(ev->sender==scrollbar_v && ev->command=="change")
	{
		current_pos=scrollbar_v->value;
		dirty=true;
	}

	//SEND EVENT TO PARENT
	else
	{
		send_event(ev);
		return;
	}

	delete ev;
}



void eListbox::on_mouse_enter(int mx,int my){}
void eListbox::on_mouse_leave(){}



//***** ON MOUSE MOVE
void eListbox::on_mouse_move(int mx,int my)
{
	if(mouse_selecting)
	{
		int i=find_item_index_at(mx,my);

		if(i<selected_base)
			select_items(i,selected_base);
		else
			select_items(selected_base,i);
		
	}
}



//***** ON MOUSE DOWN
void eListbox::on_mouse_down(int but,int mx,int my)
{
	Keyboard& k=Input::get_keyboard();

	if(but==1)
	{
		//multiple selecting
		if(multi_selection && k.shift())
		{
			int i=find_item_index_at(mx,my);

			if(i<selected_base)
				select_items(i,selected_base);
			else
				select_items(selected_base,i);
		}

		//normal selecting
		else
		{
			select_item(find_item_at(mx,my));
			mouse_selecting=true;
		}
	}
}



void eListbox::on_mouse_up(int but,int mx,int my){}
//void eListbox::on_mouse_click(int but,int mx,int my){}
//void eListbox::on_mouse_doubleclick(int but,int mx,int my){}



//***** ON MOUSE WHEEL DOWN
void eListbox::on_mouse_wheel_down(int mx,int my)
{
	if(scrollbar_v->visible)
	{
		scrollbar_v->set_value(scrollbar_v->value+1);

		if(mouse_selecting)
			on_mouse_move(mx,my);
	}
}



//***** ON MOUSE WHEEL UP
void eListbox::on_mouse_wheel_up(int mx,int my)
{
	if(scrollbar_v->visible)
	{
		scrollbar_v->set_value(scrollbar_v->value-1);

		if(mouse_selecting)
			on_mouse_move(mx,my);
	}
}



void eListbox::on_mouse_drag_out(){}
void eListbox::on_mouse_drag_in(DragPacket* dragpacket,int mx,int my){}



//***** ON KEY DOWN
void eListbox::on_key_down(Key& key)
{
	Keyboard& k=Input::get_keyboard();

	//UP,LEFT
	if(key.code==KEY_UP || key.code==KEY_LEFT)
	{
		mouse_selecting=false;

		//multiple selecting
		if(multi_selection && k.shift())
		{
			if(selected_min<selected_base)
				select_items(selected_min-1,selected_base);
			else
				select_items(selected_base,selected_max-1);
		}

		//normal select
		else
		{
			int i=get_selected_index()-1;
			if(items.size()>0 && i<0)
				i=0;

			select_item(i);
		}
	}
	
	//DOWN,RIGHT
	else if(key.code==KEY_DOWN || key.code==KEY_RIGHT)
	{
		mouse_selecting=false;

		//multiple selecting
		if(multi_selection && k.shift())
		{
			if(selected_min<selected_base)
				select_items(selected_min+1,selected_base);
			else
				select_items(selected_base,selected_max+1);
		}

		//normal select
		else
		{
			selected_min=selected_max;

			int i=get_selected_index()+1;
			if(items.size()>0 && i>=items.size())
				i=items.size()-1;

			select_item(i);
		}
	}

	//ESCAPE
	else if(key.code==KEY_ESCAPE)
	{
		mouse_selecting=false;
		select_item(-1);
	}
}



void eListbox::on_key_up(Key& key){}
void eListbox::on_text(const Str& text){}
void eListbox::on_resize(int width,int height){}
void eListbox::on_parent_resize(){}
void eListbox::on_select(){}
void eListbox::on_unselect(){}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//***** SET STYLE
void eListbox::set_style(ListboxStyle::Type estyle)
{
	style=estyle;
	dirty=true;
}



//***** GET SIZE
inline int eListbox::get_size()
{
	return items.size();
}



//***** CLEAR
void eListbox::clear(bool del)
{
	if(del)
		items.clear_del();
	else
		items.clear_nodel();
	
	dirty=true;
}



//***** INSERT ITEM
void eListbox::insert_item(eItem* item,int index)
{
	if(index<0 || index>items.size())
		return;

	items.insert(item,index);
	dirty=true;
}



//***** ADD ITEM
void eListbox::add_item(eItem* item)
{
	items.add(item);
	dirty=true;
}



//***** REMOVE ITEM
void eListbox::remove_item(eItem* item,bool del)
{
	int index=items.find(item);
	if(index!=-1)
	{
		if(del)
			items.remove_del(index);
		else
			items.remove_nodel(index);
	}
	
	dirty=true;
}



//***** REMOVE ITEM
void eListbox::remove_item(int index,bool del)
{
	if(index<0 || index>items.size())
		return;

	if(del)
		items.remove_del(index);
	else
		items.remove_nodel(index);
	dirty=true;
}



//***** INSERT NEW ITEM
eItem* eListbox::insert_new_item(const Str& iname,int ival,int index)
{
	eItem* item=new eItem(iname,ival);
	insert_item(item,index);

	return item;
}



//***** INSERT NEW ITEM
eItem* eListbox::insert_new_item(const Str& iname,int ival,Texture* ico,int index)
{
	eItem* item=new eItem(iname,ival,ico);
	insert_item(item,index);

	return item;
}



//***** INSERT NEW ITEM
eItem* eListbox::insert_new_item(const Str& iname,int ival,const Str& ico,int index)
{
	eItem* item=new eItem(iname,ival,ico);
	insert_item(item,index);

	return item;
}



//***** ADD NEW ITEM
eItem* eListbox::add_new_item(const Str& iname,int ival,Texture* ico)
{
	eItem* item=new eItem(iname,ival,ico);
	add_item(item);

	return item;
}



//***** ADD NEW ITEM
eItem* eListbox::add_new_item(const Str& iname,int ival,const Str& ico)
{
	eItem* item=new eItem(iname,ival,ico);
	add_item(item);

	return item;
}



















//***** MOVE ITEM
void eListbox::move_item(eItem* item,int index)
{
	int i=items.find(item);
	if(i==-1)
		return;

	move_item(i,index);
}



//***** MOVE ITEM
void eListbox::move_item(int index1,int index2)
{
	if(index1<0 || index1>items.size() || index2<0 || index2>items.size())
		return;

}



//***** SWITCH ITEM
void eListbox::switch_item(eItem* item1,eItem* item2)
{
}



//***** SWITCH ITEM
void eListbox::switch_item(int index1,int index2)
{
	if(index1<0 || index1>items.size() || index2<0 || index2>items.size())
		return;

}



//***** SORT ITEMS BY NAME
void eListbox::sort_items_by_name(bool reverse)
{
}



//***** SORT ITEMS BY VALUE
void eListbox::sort_items_by_value(bool reverse)
{
}

















//***** SELECT ITEM
void eListbox::select_item(eItem* item)
{
	int index=items.find(item);

	selected_min=index;
	selected_max=index;
	selected_base=index;

	dirty=true;
}



//***** SELECT ITEM
void eListbox::select_item(int index)
{
	if(index<0 || index>=items.size())
		index=-1;

	selected_min=index;
	selected_max=index;
	selected_base=index;

	dirty=true;
}



//***** SELECT ITEMS
void eListbox::select_items(int index1,int index2)
{
	int i1=index1<index2?index1:index2;
	int i2=index2>index1?index2:index1;

	if(i1<0 || i1>=items.size() || i2<0 || i2>=items.size())
		return;
	
	selected_min=i1;
	selected_max=i2;

	dirty=true;
}



//***** GET SELECTED ITEM
eItem* eListbox::get_selected_item()
{
	if(selected_min<0)
		return NULL;

	return items[selected_min];
}



//***** GET SELECTED INDEX
int eListbox::get_selected_index()
{
	return selected_min;
}



//***** GET SELECTED ITEMS
List<eItem*> eListbox::get_selected_items()
{
	List<eItem*> lst;

	for(int a=selected_min;a<=selected_max;a++)
		lst.add(items[a]);

	return lst;
}



//***** GET ITEM INDEX
int eListbox::get_item_index(eItem* item)
{
	return items.find(item);
}








//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************


//***** GET VIEW H
int eListbox::get_view_h()
{
	return (h/items_h);
}



//***** REFRESH SCROLLBARS
void eListbox::refresh_scrollbars()
{
	if(items.size())
	{
		//check if we need the vertical scrollbar
		if(items.size()*items_h>h)
		{
			if(!scrollbar_v->visible)
			{
				scrollbar_v->x=w-scrollbar_v->w;
				scrollbar_v->y=0;
				scrollbar_v->resize(scrollbar_v->w,h);

				scrollbar_v->set_value(current_pos);
				scrollbar_v->set_value_range(0,(((items.size()*items_h)-h)+items_h-1)/items_h);
				scrollbar_v->set_page_size(h/items_h);
				scrollbar_v->visible=true;
			}
		}
		else
			scrollbar_v->visible=false;


	}
}



//***** FIND ITEM AT
eItem* eListbox::find_item_at(int mx,int my)
{
	int index=my/items_h+current_pos;
	if(index<0 || index>=items.size())
		index=-1;

	return items[index];
}



//***** FIND ITEM INDEX AT
int eListbox::find_item_index_at(int mx,int my)
{
	int index=my/items_h+current_pos;
	if(index<0 || index>=items.size())
		index=-1;

	return index;
}








