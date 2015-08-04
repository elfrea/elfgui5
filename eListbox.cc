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
	
	//own internal config vars (use config functions to modify)
	alternate_items_bg=true;

	//own internal vars
	current_pos=0;
	
	//own elements
	scrollbar_h=new eScrollbar("scrollbar_h",10,10,10,25,0,1,Orientation::Horizontal);
	scrollbar_h->visible=false;
	add_child(scrollbar_h);

	scrollbar_v=new eScrollbar("scrollbar_v",10,10,25,10,0,1,Orientation::Vertical);
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
		if(alternate_items_bg && a%2!=0)
			image->rect_fill(1,offset+1,w-2,offset+1+items_h-2,color->extra);

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
void eListbox::on_mouse_move(int mx,int my){}
void eListbox::on_mouse_down(int but,int mx,int my){}
void eListbox::on_mouse_up(int but,int mx,int my){}
//void eListbox::on_mouse_click(int but,int mx,int my){}
//void eListbox::on_mouse_doubleclick(int but,int mx,int my){}
//void eListbox::on_mouse_wheel_down(int mx,int my){}
//void eListbox::on_mouse_wheel_up(int mx,int my){}
void eListbox::on_mouse_drag_out(){}
void eListbox::on_mouse_drag_in(DragPacket* dragpacket,int mx,int my){}
void eListbox::on_key_down(Key& key){}
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
				scrollbar_v->set_value_range(0,((items.size()*items_h)-h)/items.size());
				scrollbar_v->set_page_size(h/items_h);
				scrollbar_v->visible=true;
			}
		}
		else
			scrollbar_v->visible=false;


	}
}








