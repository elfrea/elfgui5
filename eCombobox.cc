#include <pix5.h>
#include "elfgui5.h"



//constructor
eCombobox::eCombobox(const Str& ename,int ex,int ey,int ew,int eh,const Str& txt):Element(ename,ex,ey,ew,eh)
{
	//parent class vars
	type="combobox";
	selectable=true;
	
	//own config vars
	
	//own internal config vars (use config functions to modify)

	//own internal vars
	
	//own elements
	editbox=new eEditbox("combobox editbox",0,0,10,10,txt);
	editbox->set_readonly(true);
	add_child(editbox);

	button=new eButton("combobox button",0,0,10,10,"");
	button->set_show_text(false);
	button->set_tex("gfx/elements/arrow_down.png");
	button->visible=false;
	add_child(button);

	listbox=new eListbox("combobox listbox",0,0,10,10);

	VideoMode vm=Display::get_mode();
	modal=new eModal("combobox modal",0,0,vm.width,vm.height,true,false,this);

	//other
	dirty=true;
}



//destructor
eCombobox::~eCombobox()
{
	if(!listbox->parent)
		delete listbox;
	if(!modal->parent)
		delete modal;
}








//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void eCombobox::loop()
{
}



//***** DRAW
void eCombobox::draw()
{
	refresh_gui();
}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//***** ON EVENT
void eCombobox::on_event(Event* ev)
{
	//editbox change
	if(ev->sender==editbox && ev->command=="change")
	{
		send_event("change");
	}
	
	//editbox trigger
	else if(ev->sender==editbox && ev->command=="trigger")
	{
		open_list();
	}
	
	//editbox left click
	else if(ev->sender==editbox && ev->command=="left click")
	{
		if(editbox->readonly)
			open_list();
	}
	
	//button trigger
	else if(ev->sender==button && ev->command=="trigger")
	{
		open_list();
	}
	
	//listbox trigger and left click
	else if(ev->sender==listbox && (ev->command=="trigger" || ev->command=="left click"))
	{
		set_text(listbox->get_selected_text());
		modal->close();
	}
	
	//modal close
	else if(ev->sender==modal && ev->command=="close")
	{
		close_list();
	}
	
	//SEND EVENT TO PARENT
	else if(ev->command=="touched")
	{
		send_event(ev);
		return;
	}

	delete ev;
}



void eCombobox::on_mouse_enter(int mx,int my){}
void eCombobox::on_mouse_leave(){}
void eCombobox::on_mouse_move(int mx,int my){}
void eCombobox::on_mouse_down(int but,int mx,int my){}
void eCombobox::on_mouse_up(int but,int mx,int my){}
//void eCombobox::on_mouse_click(int but,int mx,int my){}
//void eCombobox::on_mouse_doubleclick(int but,int mx,int my){}
//void eCombobox::on_mouse_wheel_down(int mx,int my){}
//void eCombobox::on_mouse_wheel_up(int mx,int my){}
void eCombobox::on_mouse_drag_out(){}
void eCombobox::on_mouse_drag_in(DragPacket* dragpacket,int mx,int my){}



//***** ON KEY DOWN
void eCombobox::on_key_down(Key& key)
{
	if(key.code==KEY_SPACE || key.code==KEY_RETURN)
		open_list();
}



void eCombobox::on_key_up(Key& key){}
void eCombobox::on_text(const Str& text){}



//***** ON RESIZE
void eCombobox::on_resize(int width,int height)
{
	refresh_gui();
}



void eCombobox::on_parent_resize(){}
void eCombobox::on_select(){}
void eCombobox::on_unselect(){}



//***** ON RESOLUTION CHANGE
void eCombobox::on_resolution_change(int width,int height)
{
	if(!modal->parent)
		modal->send_resolution_change(width,height);
}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//***** SHRINK
void eCombobox::shrink()
{
}



//***** SET TEXT
void eCombobox::set_text(const Str& txt)
{
	editbox->set_text(txt,true);
}



//***** SET READONLY
void eCombobox::set_readonly(bool ronly)
{
	editbox->set_readonly(ronly);
}



//***** SET SHOW VALUE
void eCombobox::set_show_value(bool show)
{
	listbox->set_show_value(show);
}



//***** CLEAR ITEMS
void eCombobox::clear_items(bool del)
{
	listbox->clear(del);
}



//***** INSERT ITEM
eItem* eCombobox::insert_item(const Str& txt,int val,Texture* ico,int index)
{
	return listbox->insert_new_item(txt,val,ico,index);
}



//***** INSERT ITEM
eItem* eCombobox::insert_item(const Str& txt,int val,const Str& ico,int index)
{
	return listbox->insert_new_item(txt,val,ico,index);
}



//***** ADD ITEM
eItem* eCombobox::add_item(const Str& txt,int val)
{
	return listbox->add_new_item(txt,val,NULL);
}



//***** ADD ITEM
eItem* eCombobox::add_item(const Str& txt,int val,Texture* ico)
{
	if(listbox->style!=ListboxStyle::IconText)
		listbox->set_style(ListboxStyle::IconText);
	return listbox->add_new_item(txt,val,ico);
}



//***** ADD ITEM
eItem* eCombobox::add_item(const Str& txt,int val,const Str& ico)
{
	if(listbox->style!=ListboxStyle::IconText)
		listbox->set_style(ListboxStyle::IconText);
	return listbox->add_new_item(txt,val,ico);
}



//***** REMOVE ITEM
void eCombobox::remove_item(eItem* item,bool del)
{
	listbox->remove_item(item,del);
}



//***** REMOVE ITEM
void eCombobox::remove_item(int index,bool del)
{
	listbox->remove_item(index,del);
}



//***** SORT ITEMS BY TEXT
void eCombobox::sort_items_by_text()
{
	listbox->sort_items_by_text();
}



//***** SORT ITEMS BY VALUE
void eCombobox::sort_items_by_value()
{
	listbox->sort_items_by_value();
}



//***** GET TEXT
Str eCombobox::get_text()
{
	return editbox->text;
}



//***** GET VALUE
int eCombobox::get_value()
{
	int val=0;
	eItem* item=listbox->get_selected_item();
	if(item)
		val=item->value;
	
	return val;
}



//***** GET ITEM
eItem* eCombobox::get_item()
{
	return listbox->get_selected_item();
}








//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************


//***** REFRESH GUI
void eCombobox::refresh_gui()
{
	button->x=w-h;
	button->y=0;
	button->resize(h,h);

	editbox->x=0;
	editbox->y=0;
	editbox->resize(w-h,h);
	
	button->visible=true;
}



//***** OPEN LIST
void eCombobox::open_list()
{
	//check for listbox height
	VideoMode vm=Display::get_mode();
	bool below=true;
	int lh=vm.height-(get_true_y()+h);
	if(lh<100)
	{
		lh=get_true_y();
		below=false;
	}

	//below
	if(below)
	{
		listbox->x=get_true_x();
		listbox->y=get_true_y()+h;
		listbox->w=w;
		listbox->set_auto_height(true,100,lh);
	}

	//above
	else
	{
		listbox->x=get_true_x();
		listbox->w=w;
		listbox->set_auto_height(true,100,lh);
		listbox->y=get_true_y()-listbox->h;
	}

	modal->open();
	modal->add_child(listbox);
	listbox->set_as_selected(true);
}



//***** CLOSE LIST
void eCombobox::close_list()
{
}









