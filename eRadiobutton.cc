#include <pix5.h>
#include "elfgui5.h"



//constructor
eRadiobutton::eRadiobutton(const Str& ename,int ex,int ey,int ew,int eh,const Str& txt,const Str& grp,bool echecked,bool autosize):Element(ename,ex,ey,ew,eh)
{
	#define DEFAULT_CHECK_SIZE 17
	#define DEFAULT_CHECK_RADIUS 3

	//parent class vars
	type="radiobutton";
	
	//own config vars
	
	//own internal config vars (use config functions to modify)
	group=grp;
	checked=echecked;
	check_size=DEFAULT_CHECK_SIZE;
	check_radius=DEFAULT_CHECK_RADIUS;
	show_text=true;
	show_tex=false;

	text_align=Align::Middle;
	text_offx=0;
	text_offy=0;
	text="";

	tex_align=Align::Middle;
	tex_offx=0;
	tex_offy=0;
	tex=NULL;

	//own internal vars
	ready_to_check=false;
	custom_box=NULL;
	custom_mark=NULL;
	
	//own elements

	//other
	set_text(txt,Align::Left,4,0,autosize);
}



//destructor
eRadiobutton::~eRadiobutton()
{
}








//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void eRadiobutton::loop()
{
	Mouse& m=Input::get_mouse();
	Keyboard& kbd=Input::get_keyboard();

	if(ready_to_check && m.button(1)==false && kbd.is_down(KEY_SPACE)==false)
		ready_to_check=false;
}



//***** DRAW
void eRadiobutton::draw()
{

	//check box
	if(custom_box)
	{
		image->clear(Color(0,0,0,0));
		image->blit(0,(h-custom_box->height())/2,custom_box,false);
	}
	else
	{
		image->clear(Color(0,0,0,0));
		image->circle_fill(check_size/2,(check_size/2)+(h-check_size)/2,check_size/2,color->editing);
		image->circle(check_size/2,(check_size/2)+(h-check_size)/2,check_size/2,color->dark);
	}

	//check mark
	if(custom_mark)
	{
		if(checked)
		{
			image->blit(0,(h-custom_mark->height())/2,custom_mark,true);
		}
	}
	else
	{
		if(checked)
		{
			if(enabled)
				image->circle_fill(check_size/2,(check_size/2)+(h-check_size)/2,check_radius,color->text);
			else
				image->circle_fill(check_size/2,(check_size/2)+(h-check_size)/2,check_radius,color->d_text);
		}
	}
	
	//show tex
	if(show_tex)
		draw_texture_align(image,tex_align,tex_offx,tex_offy,tex);

	//show text
	if(show_text)
	{
		if(enabled)
			draw_text_align(image,text_align,check_size+text_offx,text_offy,font,color->text,text,true);
		else
			draw_text_align(image,text_align,check_size+text_offx,text_offy,font,color->d_text,text,true);
	}


	//selected
	if(selected)
		draw_dotted_box(image,0,0,w,h,color->dark,1,1);

}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//void eRadiobutton::on_event(Event* ev){}



void eRadiobutton::on_mouse_enter(int mx,int my){}
void eRadiobutton::on_mouse_leave(){}
void eRadiobutton::on_mouse_move(int mx,int my){}



//***** ON MOUSE DOWN
void eRadiobutton::on_mouse_down(int but,int mx,int my)
{
	ready_to_check=true;
}



//***** ON MOUSE UP
void eRadiobutton::on_mouse_up(int but,int mx,int my)
{
	if(but==1 && ready_to_check)
		set_checked();

	ready_to_check=false;
}



//void eRadiobutton::on_mouse_click(int but,int mx,int my){}
//void eRadiobutton::on_mouse_doubleclick(int but,int mx,int my){}
//void eRadiobutton::on_mouse_wheel_down(int mx,int my){}
//void eRadiobutton::on_mouse_wheel_up(int mx,int my){}
void eRadiobutton::on_mouse_drag_out(){}
void eRadiobutton::on_mouse_drag_in(DragPacket* dragpacket){}



//***** ON KEY DOWN
void eRadiobutton::on_key_down(Key& key)
{
	//SPACE
	if(key.code==KEY_SPACE)
		ready_to_check=true;

	//UP-DOWN ARROW
	else if(key.code==KEY_UP || key.code==KEY_DOWN || key.code==KEY_LEFT || key.code==KEY_RIGHT)
	{
		int backward=(key.code==KEY_UP || key.code==KEY_LEFT);

		if(parent)
		{
			Element* target=NULL;

			for(int a=0;a<parent->children.size();a++)
			{
				Element* ele=parent->children[a];

				if(ele==this || ele->type!=type || ((eRadiobutton*)ele)->group!=group)
					continue;

				//forward
				if(backward==false)
				{
					if(target==NULL)
					{
						if(ele->tab_index>tab_index)
							target=ele;
					}
					else if(ele->tab_index>tab_index && ele->tab_index<target->tab_index)
						target=ele;
				}

				//backward
				else
				{
					if(target==NULL)
					{
						if(ele->tab_index<tab_index)
							target=ele;
					}
					else if(ele->tab_index<tab_index && ele->tab_index>target->tab_index)
						target=ele;
				}
			}
			
			//set new selected radiobutton
			if(target)
			{
				target->set_selected(true);
				((eRadiobutton*)target)->set_checked();
			}
		}
	}
}



//***** ON KEY UP
void eRadiobutton::on_key_up(Key& key)
{
	//SPACE
	if(key.code==KEY_SPACE && ready_to_check)
	{
		set_checked();
		ready_to_check=false;
	}
	
}



void eRadiobutton::on_text(const Str& text){}
void eRadiobutton::on_resize(int width,int height){}
void eRadiobutton::on_parent_resize(){}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//***** SHRINK
void eRadiobutton::shrink()
{
	//set width
	int tw=check_size+(show_text?text_offx+font->len(text):0);

	//set height
	int th=(show_text?font->height():check_size);
	if(th<check_size)
		th=check_size;
	if(custom_box && th<custom_box->height())
		th=custom_box->height();
	if(custom_mark && th<custom_mark->height())
		th=custom_mark->height();

	resize(tw,th);
}



//***** SET TEXT
void eRadiobutton::set_text(const Str& txt,Align::Type align,int offx,int offy,bool autosize)
{
	text=txt;
	text_align=align;
	text_offx=offx;
	text_offy=offy;
	
	if(autosize)
		shrink();
	
	show_text=true;
	dirty=true;
}



//***** SET TEX
void eRadiobutton::set_tex(Texture* src,Align::Type align,int offx,int offy,bool autosize)
{
	tex=src;
	tex_align=align;
	tex_offx=offx;
	tex_offy=offy;
	
	if(autosize)
		shrink();
	
	show_tex=true;
	dirty=true;
}


//***** SET TEX
void eRadiobutton::set_tex(const Str& filename,Align::Type align,int offx,int offy,bool autosize)
{
	Texture* t=Cache::texture(filename);
	set_tex(t,align,offx,offy);
	
	if(autosize)
		shrink();
	
}



//***** SHOW TEXT
void eRadiobutton::set_show_text(bool show)
{
	show_text=show;
	dirty=true;
}



//***** SHOW TEX
void eRadiobutton::set_show_tex(bool show)
{
	show_tex=show;
	dirty=true;
}



//***** SET GROUP
void eRadiobutton::set_group(const Str& grp)
{
	group=grp;
	dirty=true;
}



//***** SET CHECKED
void eRadiobutton::set_checked()
{
	//tell other radiobuttons of the same parent and group to uncheck
	if(parent && !checked)
	{
		for(int a=0;a<parent->children.size();a++)
		{
			Element* ele=parent->children[a];

			if(ele->type==type && ((eRadiobutton*)ele)->group==group)
			{
				((eRadiobutton*)ele)->checked=false;
				ele->dirty=true;
			}
		}
	
		send_event("trigger");
	}
	
	checked=true;
	dirty=true;
}



//***** SET CHECK SIZE
void eRadiobutton::set_check_size(int size,bool autosize)
{
	check_size=size;
	if(autosize)
		shrink();
		
	dirty=true;
}



//***** SET CHECK OFFSET
void eRadiobutton::set_check_radius(int off)
{
	check_radius=off;
	dirty=true;
}



//***** SET CUSTOM
void eRadiobutton::set_custom(Texture* box,Texture* mark,bool autosize,bool sh_text)
{
	custom_box=box;
	custom_mark=mark;

	show_text=sh_text;

	//adjust checksize if needed
	if(box)
		check_size=box->width();

	//check if we need to resize the checkbox
	if(autosize)
		shrink();

	dirty=true;
}



//***** SET CUSTOM
void eRadiobutton::set_custom(const Str& box,const Str& mark,bool autosize,bool sh_text)
{
	set_custom(Cache::texture(box),Cache::texture(mark),autosize,sh_text);
}








//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************








