#include <pix5.h>
#include "elfgui5.h"



//constructor
eListbox::eListbox(const Str& ename,int ex,int ey,int ew,int eh,ListboxStyle::Type estyle):Element(ename,ex,ey,ew,eh)
{
	
	#define DEFAULT_ITEMS_H 20
	#define DEFAULT_MOUSE_SCROLL_DELAY 100

	//parent class vars
	type="listbox";
	selectable=true;
	items_h=DEFAULT_ITEMS_H;
	color->extra=Color::ubyte(220,220,220);
	mouse_scroll_delay=DEFAULT_MOUSE_SCROLL_DELAY;
	
	//own config vars
	multi_selection=false;
	
	//own internal config vars (use config functions to modify)
	alternate_color=true;
	show_value=false;

	//own internal vars
	current_pos=0;
	selected_min=-1;
	selected_max=-1;
	mouse_selecting=false;
	mouse_scroll_timer=0;
	
	//own elements
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
	selection.clear_nodel();
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


	//scroll with mouse when multiselecting
	if(multi_selection && mouse_selecting && scrollbar_v->visible)
	{
		int my=m.y-get_true_y();
		int64_t ms=get_ms();

		if(my<=8)
		{
			if(ms>=mouse_scroll_timer+mouse_scroll_delay)
			{
				mouse_scroll_timer=ms;
				scrollbar_v->set_value(scrollbar_v->value-1);
				on_mouse_move(m.x-get_true_x(),0);
			}
		}
		else if(my>=(h-1-8))
		{
			if(ms>=mouse_scroll_timer+mouse_scroll_delay)
			{
				mouse_scroll_timer=ms;
				scrollbar_v->set_value(scrollbar_v->value+1);
				on_mouse_move(m.x-get_true_x(),h-1);
			}
		}
	}
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

		//alternate bg color if needed
		if(alternate_color && a%2!=0)
			image->rect_fill(1,offset+1,w-2,y2,color->extra);

		//show selection
		if(selection.find(a)!=-1)
			image->rect_fill(1,offset+1,w-2,y2,color->selection);

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

		//show value
		if(show_value)
		{
			Str t=Str::build("%i",items[a]->value);
			int tw=font->len(t);
			image->print(font,w-tw-(scrollbar_v->visible?scrollbar_v->w:0)-5,offset+(items_h-th)/2,color->text,t);
		}

		offset+=items_h;
	}

	//selected
	if(selected)
		draw_dotted_box(image,2,2,w-4-(scrollbar_v->visible?scrollbar_v->w:0),h-4,color->dark,1,1);
}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//***** ON EVENT
void eListbox::on_event(Event* ev)
{

	//scrollbar_v
	if(ev->sender==scrollbar_v && ev->command=="change")
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
	if(multi_selection && mouse_selecting)
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
		//toggle
		if(multi_selection && k.ctrl())
		{
			int i=find_item_index_at(mx,my);
			toggle_item_selection(i);
		}

		//multiple selecting
		else if(multi_selection && k.shift())
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

		//check if we need to change the current_pos
		if(scrollbar_v->visible && get_selected_index()<current_pos)
			set_current_pos(current_pos-1);
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
		
		//check if we need to change the current_pos
		if(scrollbar_v->visible && get_selected_index()>=current_pos+(h/items_h))
			set_current_pos(current_pos+1);
	}

	//ESCAPE
	else if(key.code==KEY_ESCAPE)
	{
		mouse_selecting=false;
		select_item(-1);
	}

	//CTRL-A
	else if(key.code==KEY_A && k.ctrl())
	{
		select_items(0,items.size()-1);
	}
}



void eListbox::on_key_up(Key& key){}
void eListbox::on_text(const Str& text){}
void eListbox::on_resize(int width,int height){}
void eListbox::on_parent_resize(){}



//***** ON SELECT
void eListbox::on_select()
{
	Input::set_key_down_repeat(true);
}



//***** ON UNSELECT
void eListbox::on_unselect()
{
	Input::set_key_down_repeat(false);
}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//***** SET STYLE
void eListbox::set_style(ListboxStyle::Type estyle)
{
	style=estyle;
	dirty=true;
}



//***** SET ALTERNATE COLOR
void eListbox::set_alternate_color(bool alternate)
{
	alternate_color=alternate;
	dirty=true;
}



//***** SET SHOW VALUE
void eListbox::set_show_value(bool show)
{
	show_value=show;
	dirty=true;
}



//***** SET CURRENT POS
void eListbox::set_current_pos(int index)
{
	if(index<scrollbar_v->value_min)
		index=scrollbar_v->value_min;
	else if(index>scrollbar_v->value_max)
		index=scrollbar_v->value_max;

	current_pos=index;
	scrollbar_v->set_value(index);
	dirty=true;
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
	move_item(get_item_index(item),index);
}



//***** MOVE ITEM
void eListbox::move_item(int index1,int index2)
{
	if(index1<0 || index1>items.size() || index2<0 || index2>items.size())
		return;

	select_item(-1);

	if(index1<index2)
	{
		insert_item(items[index1],index2+1);
		remove_item(index1,false);
	}
	else
	{
		insert_item(items[index1],index2);
		remove_item(index1+1,false);
	}


}



//***** SWITCH ITEM
void eListbox::switch_item(eItem* item1,eItem* item2)
{
	int index1=get_item_index(item1);
	int index2=get_item_index(item2);

	switch_item(index1,index2);
}



//***** SWITCH ITEM
void eListbox::switch_item(int index1,int index2)
{
	if(index1<0 || index1>items.size() || index2<0 || index2>items.size())
		return;
	
	select_item(-1);

	eItem* i1=items[index1];
	eItem* i2=items[index2];

	items[index1]=i2;
	items[index2]=i1;
}



//***** SORT ITEMS BY TEXT
void eListbox::sort_items_by_text(bool reverse)
{
	select_item(-1);
	
	List<eItem*> lst=items;
	items.clear_nodel();
	for(int a=0;a<lst.size();a++)
	{
		int pos=items.size();
		for(int b=0;b<items.size();b++)
		{
			//descending
			if(reverse)
			{
				if(lst[a]->text>items[b]->text)
				{
					pos=b;
					break;
				}
			}
			//ascending
			else
			{
				if(lst[a]->text<items[b]->text)
				{
					pos=b;
					break;
				}
			}
		}

		items.insert(lst[a],pos);
	}

	lst.clear_nodel();
	dirty=true;
}



//***** SORT ITEMS BY VALUE
void eListbox::sort_items_by_value(bool reverse)
{
	select_item(-1);
	
	List<eItem*> lst=items;
	items.clear_nodel();
	for(int a=0;a<lst.size();a++)
	{
		int pos=items.size();
		for(int b=0;b<items.size();b++)
		{
			//descending
			if(reverse)
			{
				if(lst[a]->value>items[b]->value)
				{
					pos=b;
					break;
				}
			}
			//ascending
			else
			{
				if(lst[a]->value<items[b]->value)
				{
					pos=b;
					break;
				}
			}
		}

		items.insert(lst[a],pos);
	}

	lst.clear_nodel();
	dirty=true;
}

















//***** SELECT ITEM
void eListbox::select_item(eItem* item)
{
	int index=items.find(item);

	if(!compare_selection(index))
	{
		selected_min=index;
		selected_max=index;
		selected_base=index;

		//clear and add selection in list
		selection.clear_nodel();
		selection.add(index);

		send_event("change");
	
		dirty=true;
	}
}



//***** SELECT ITEM
void eListbox::select_item(int index)
{
	if(!compare_selection(index))
	{
		if(index<0 || index>=items.size())
			index=-1;

		selected_min=index;
		selected_max=index;
		selected_base=index;

		//clear and add selection in list
		selection.clear_nodel();
		selection.add(index);

		send_event("change");

		dirty=true;
	}
}



//***** SELECT ITEMS
void eListbox::select_items(int index1,int index2)
{
	int i1=index1<index2?index1:index2;
	int i2=index2>index1?index2:index1;

	if(!compare_selection(i1,i2))
	{
		if(i1<0 || i1>=items.size() || i2<0 || i2>=items.size())
			return;
		
		selected_min=i1;
		selected_max=i2;
		
		//clear and add selection in list
		selection.clear_nodel();
		for(int a=selected_min;a<=selected_max;a++)
			selection.add(a);

		send_event("change");

		dirty=true;
	}
}



//***** ADD TO SELECTION
void eListbox::add_to_selection(eItem* item)
{
	int index=get_item_index(item);
	if(index>-1)
	{
		if(selection.find(index)==-1)
		{
			selection.add(index);
			dirty=true;
			selected_base=index;
			send_event("change");

		}
	}
}



//***** ADD TO SELECTION
void eListbox::add_to_selection(int index)
{
	if(index>=0 && index<items.size())
	{
		if(selection.find(index)==-1)
		{
			selection.add(index);
			dirty=true;
			selected_base=index;
			send_event("change");
		}
	}
}



//***** REMOVE FROM SELECTION
void eListbox::remove_from_selection(eItem* item)
{
	int index=get_item_index(item);
	if(index>-1)
	{
		int i=selection.find(index);
		if(i>-1)
		{
			selection.remove_nodel(i);
			dirty=true;
			selected_base=index;
			send_event("change");
		}
	}
		
		
}



//***** REMOVE FROM SELECTION
void eListbox::remove_from_selection(int index)
{
	if(index>-1)
	{
		int i=selection.find(index);
		if(i>-1)
		{
			selection.remove_nodel(i);
			dirty=true;
			selected_base=index;
			send_event("change");
		}
	}
}



//***** TOGGLE ITEM SELECTION
void eListbox::toggle_item_selection(eItem* item)
{
	int index=get_item_index(item);
	if(index>-1)
	{
		int i=selection.find(index);
		if(i!=-1)
			selection.remove_nodel(i);
		else
			selection.add(index);

		dirty=true;
		selected_base=index;
		send_event("change");
	}
}



//***** TOGGLE ITEM SELECTION
void eListbox::toggle_item_selection(int index)
{
	if(index>-1)
	{
		int i=selection.find(index);
		if(i!=-1)
			selection.remove_nodel(i);
		else
			selection.add(index);
		
		dirty=true;
		selected_base=index;
		send_event("change");
	}
}



//***** GET SELECTED ITEM
eItem* eListbox::get_selected_item()
{
	if(selection.size()==-1)
		return NULL;
	
	return items[selection[0]];
}



//***** GET SELECTED INDEX
int eListbox::get_selected_index()
{
	if(selection.size()==-1)
		return -1;
	
	return selection[0];
}



//***** GET SELECTED ITEMS
List<eItem*> eListbox::get_selected_items()
{
	List<eItem*> lst;

	for(int a=0;a<selection.size();a++)
		lst.add(items[a]);

	return lst;
}



//***** GET SELECTED ITEMS INDEX
List<int> eListbox::get_selected_items_index()
{
	return selection;
}



//***** GET ITEM INDEX
int eListbox::get_item_index(eItem* item)
{
	return items.find(item);
}



//***** GET SIZE
inline int eListbox::get_size()
{
	return items.size();
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



//***** COMPARE SELECTION
bool eListbox::compare_selection(int index)
{
	if(selection.size()==1 && selection[0]==index)
		return true;
	
	return false;
}



//***** COMPARE SELECTION
bool eListbox::compare_selection(int index1,int index2)
{
	int am=index2-index1+1;
	if(selection.size()==am)
	{
		for(int a=index1;a<=index2;a++)
		{
			if(selection.find(a)==-1)
				return false;
		}

		return true;
	}

	return false;
}






