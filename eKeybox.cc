#include <pix5.h>
#include "elfgui5.h"



//constructor
eKeybox::eKeybox(const Str& ename,int ex,int ey,int ew,int eh):Element(ename,ex,ey,ew,eh)
{
	//parent class vars
	type="keybox";
	selectable=true;
	color->extra=Color::ubyte(100,140,180);

	//own config vars
	shortcut=new KShortcut();
	
	//own internal config vars (use config functions to modify)

	//own internal vars
	record_mode=false;
	
	//own elements

	//other
	dirty=true;
}



//destructor
eKeybox::~eKeybox()
{
	delete shortcut;
}








//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void eKeybox::loop()
{
}



//***** DRAW
void eKeybox::draw()
{
	//show bg
	draw_edit_panel(image,color,enabled);

	//record mode
	if(record_mode)
	{
		image->rect_fill(1,1,image->width()-2,image->height()-2,color->selection);
		if(shortcut->compare(false,false,false,false,KEY_NONE))
			draw_text_align(image,Align::Middle,0,0,font,color->text,"*Recording*");
		else
			draw_text_align(image,Align::Middle,0,0,font,color->text,shortcut->get_full_name());
	}

	//normal mode
	else
	{
		draw_text_align(image,Align::Middle,0,0,font,color->text,shortcut->get_full_name());
	}

	//selected
	if(selected)
		draw_dotted_box(image,2,2,w-4,h-4,color->dark,1,1);
}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//void eKeybox::on_event(Event* ev){}
void eKeybox::on_mouse_enter(int mx,int my){}
void eKeybox::on_mouse_leave(){}
void eKeybox::on_mouse_move(int mx,int my){}



//***** ON MOUSE DOWN
void eKeybox::on_mouse_down(int but,int mx,int my)
{
	if(but==1)
	{
		if(record_mode)
			stop_recording();
	}
}



void eKeybox::on_mouse_up(int but,int mx,int my){}
//void eKeybox::on_mouse_click(int but,int mx,int my){}



//ON MOUSE DOUBLECLICK
void eKeybox::on_mouse_doubleclick(int but,int mx,int my)
{
	if(but==1)
	{
		if(!record_mode)
			start_recording();
	}
}



//void eKeybox::on_mouse_wheel_down(int mx,int my){}
//void eKeybox::on_mouse_wheel_up(int mx,int my){}
void eKeybox::on_mouse_drag_out(){}
void eKeybox::on_mouse_drag_in(DragPacket* dragpacket,int mx,int my){}



//***** ON KEY DOWN
void eKeybox::on_key_down(Key& key)
{
	Keyboard& k=Input::get_keyboard();

	//record mode
	if(record_mode)
	{
		if(key.code==KEY_ESCAPE)
		{
			stop_recording();
			clear_shortcut();
			return;
		}

		shortcut->ctrl=k.ctrl();
		shortcut->alt=k.alt();
		shortcut->shift=k.shift();
		shortcut->gui=k.gui();

		if(key.code!=KEY_LCTRL && key.code!=KEY_RCTRL && key.code!=KEY_LALT && key.code!=KEY_RALT && key.code!=KEY_LSHIFT && key.code!=KEY_RSHIFT && key.code!=KEY_LGUI && key.code!=KEY_RGUI)
		{
			shortcut->key=key;
			send_event("change");
			stop_recording();
		}

		dirty=true;
	}
	
	//normal mode
	else
	{
		if(key.code==KEY_SPACE)
			start_recording();
	}

}



//***** ON KEY UP
void eKeybox::on_key_up(Key& key)
{
	Keyboard& k=Input::get_keyboard();

	//record mode
	if(record_mode)
	{
		shortcut->ctrl=k.ctrl();
		shortcut->alt=k.alt();
		shortcut->shift=k.shift();
		shortcut->gui=k.gui();

		dirty=true;
	}
}



void eKeybox::on_text(const Str& text){}
void eKeybox::on_resize(int width,int height){}
void eKeybox::on_parent_resize(){}
void eKeybox::on_select(){}
void eKeybox::on_unselect(){}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//***** SET SHORTCUT
void eKeybox::set_shortcut(bool c,bool a,bool s,bool g,KeyCode k)
{
	shortcut->set(c,a,s,g,k);
	send_event("change");
}



//***** CLEAR SHORTCUT
void eKeybox::clear_shortcut()
{
	shortcut->clear();
	send_event("change");
}



//***** CLONE SHORTCUT
KShortcut* eKeybox::clone_shortcut(bool enable)
{
	KShortcut* ks=shortcut->clone();
	ks->enabled=enable;

	return ks;
}



//***** CLONE SHORTCUT
KShortcut* eKeybox::clone_shortcut(const Str& sname,const Str& stype,bool enable)
{
	KShortcut* ks=shortcut->clone();
	ks->name=sname;
	ks->type=stype;
	ks->enabled=enable;

	return ks;
}



//***** START RECORDING
void eKeybox::start_recording()
{
	record_mode=true;
	ElfGui5::lock_keyboard_shortcuts=true;
	shortcut->clear();
	dirty=true;
}



//***** STOP RECORDING
void eKeybox::stop_recording()
{
	record_mode=false;
	ElfGui5::lock_keyboard_shortcuts=false;
	dirty=true;
}








//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************







