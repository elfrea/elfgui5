#include <pix5.h>
#include "elfgui5.h"



//constructor
eEditbox::eEditbox(const Str& ename,int ex,int ey,int ew,int eh,const Str& txt):Element(ename,ex,ey,ew,eh)
{
	
	#define DEFAULT_BORDER_W 5
	#define DEFAULT_MIN_RIGHT_VIEW 5
	#define DEFAULT_CURSOR_BLINK_DELAY 250
	#define DEFAULT_MOUSE_SCROLL_DELAY 25
	
	//parent class vars
	type="editbox";
	selectable=true;
	
	//own config vars
	cursor_blink=true;
	cursor_blink_delay=DEFAULT_CURSOR_BLINK_DELAY;
	mouse_scroll_delay=DEFAULT_MOUSE_SCROLL_DELAY;
	
	//own internal config vars (use config functions to modify)
	customized=false;
	custom_bg=NULL;

	insert_mode=false;
	readonly=false;

	border_w=DEFAULT_BORDER_W;
	min_right_view=DEFAULT_MIN_RIGHT_VIEW;

	view_pos=0;
	cursor_pos=0;

	password_mode=false;

	filter=EditboxFilter::None;

	//own internal vars
	cursor_blink_timer=0;
	cursor_is_gone=false;
	key_repeat=false;
	mouse_scroll_timer=0;
	
	selecting=false;
	selection_start=0;
	selection_end=0;

	mouse_is_down=false;
	mouse_down_at_pos=0;
	
	//own elements

	//other
	set_custom_cursor("gfx/elements/cursor_edit.png",2,7);
	set_text(txt);
	dirty=true;
}



//destructor
eEditbox::~eEditbox()
{
}








//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void eEditbox::loop()
{
	Mouse& m=Input::get_mouse();
	int64_t ms=get_ms();

	//blink cursor
	if(selected && cursor_blink)
	{

		if(ms>=cursor_blink_timer+cursor_blink_delay)
		{
			cursor_is_gone=!cursor_is_gone;
			cursor_blink_timer=ms;
			dirty=true;
		}
	}

	//check mouse_is_down flag
	if(mouse_is_down && !m.left())
		mouse_is_down=false;
	
	//selection with mouse
	if(mouse_is_down)
	{
		int mx=m.x-get_true_x();

		//check if mouse must change view_pos
		if(ms>=mouse_scroll_timer+mouse_scroll_delay)
		{
			mouse_scroll_timer=ms;

			if(mx<-3)
				set_view_pos(view_pos-1);
			else if(mx>w+3)
				set_view_pos(view_pos+1);
		}

		//select text
		int newpos=find_pos_at(mx);

		if(newpos<mouse_down_at_pos)
			select_text(mouse_down_at_pos-1,newpos);
		else if(newpos>mouse_down_at_pos)
			select_text(mouse_down_at_pos,newpos-1);
		else
			selecting=false;

		set_cursor_position(newpos);
	
		//copy selected test to mouse_text clipboard
		if(selecting)
			copy_selected_text(Clipboard::mouse_text);
	}

}



//***** DRAW
void eEditbox::draw()
{
	//customized
	if(customized)
	{
		image->clear(Color(0,0,0,0));
		image->blit(0,0,custom_bg);
	}

	//normal
	else
		draw_edit_panel(image,color,enabled);

	//show selection
	if(selecting)
	{
		int sx=get_selection_x();
		int sw=get_selection_w();
		int ch=font->height();

		image->rect_fill(sx,(h-ch)/2,sx+sw-1,(h-ch)/2+ch-1,color->selection);
	}

	//show text
	Str t=get_visible_text();
	int tx=border_w;
	int ty=(h-font->height())/2;
	if(enabled)
		image->print(font,tx,ty,color->text,t,false);
	else
		image->print(font,tx,ty,color->d_text,t,false);

	//show cursor
	if(selected && !readonly && enabled)
	{
		if(!cursor_is_gone)
		{
			int cx=get_cursor_x();
			int ch=font->height();
			int cw=get_char_w(get_text(),cursor_pos)-1;
			if(cw<1)
				cw=1;

			//insert mode
			if(insert_mode)
			{
				if(cx+cw>w-border_w)
					cw=1;
				image->rect(cx,(h-ch)/2,cx+cw,(h-ch)/2+ch-1,color->text);
			}

			//normal mode
			else
				image->line(cx,(h-ch)/2,cx,(h-ch)/2+ch-1,color->text);
		}
	}
}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//void eEditbox::on_event(Event* ev){}
void eEditbox::on_mouse_enter(int mx,int my){}
void eEditbox::on_mouse_leave(){}
void eEditbox::on_mouse_move(int mx,int my){}



//***** ON MOUSE DOWN
void eEditbox::on_mouse_down(int but,int mx,int my)
{
	//left button
	if(but==1)
	{
		selecting=false;

		mouse_is_down=true;
		mouse_down_at_pos=find_pos_at(mx);
	}

	//middle button
	else if(but==2)
	{
		paste_text(Clipboard::mouse_text);
	}

}



void eEditbox::on_mouse_up(int but,int mx,int my){}
//void eEditbox::on_mouse_click(int but,int mx,int my){}
//void eEditbox::on_mouse_doubleclick(int but,int mx,int my){}
//void eEditbox::on_mouse_wheel_down(int mx,int my){}
//void eEditbox::on_mouse_wheel_up(int mx,int my){}
void eEditbox::on_mouse_drag_out(){}
void eEditbox::on_mouse_drag_in(DragPacket* dragpacket){}



//***** ON KEY DOWN
void eEditbox::on_key_down(Key& key)
{
	Keyboard& k=Input::get_keyboard();

	//KEY LEFT
	if(key.code==KEY_LEFT)
	{
		int amount=0;

		//CTRL
		if(k.ctrl())
			amount=cursor_pos-get_next_space_pos(true)-1;

		//SHIFT
		if(k.shift())
		{
			if(cursor_pos==selection_start || !selecting)
				add_selection(cursor_pos-1-amount,cursor_pos-1);
			else
				del_selection(cursor_pos-1-amount,cursor_pos-1);
		}
		else
			selecting=false;
		
		set_cursor_position(cursor_pos-1-amount);
	}
	
	//KEY RIGHT
	else if(key.code==KEY_RIGHT)
	{
		int amount=0;

		//CTRL
		if(k.ctrl())
			amount=get_next_space_pos(false)-cursor_pos;

		//SHIFT
		if(k.shift())
		{
			if(cursor_pos>selection_end || !selecting)
				add_selection(cursor_pos,cursor_pos+amount);
			else
				del_selection(cursor_pos,cursor_pos+amount);
		}
		else
			selecting=false;
		
		set_cursor_position(cursor_pos+1+amount);
		
	}
	
	//KEY BACKSPACE
	else if(key.code==KEY_BACKSPACE)
	{
		if(selecting)
		{
			set_cursor_position(selection_start);
			remove_selection();
		}
		else
		{
			remove_chars(cursor_pos,1,true);
			set_cursor_position(cursor_pos-1);
		}
	}

	//KEY DELETE
	else if(key.code==KEY_DELETE)
	{
		if(selecting)
		{
			set_cursor_position(selection_start);
			remove_selection();
		}
		else
		{
			remove_chars(cursor_pos,1,false);
		}
	}

	//KEY HOME
	else if(key.code==KEY_HOME)
	{
		//SHIFT
		if(k.shift())
		{
			if(!selecting)
				select_text(cursor_pos-1,0);
			else if(cursor_pos<=selection_start)
				add_selection(0,cursor_pos-1);
			else
				select_text(0,selection_start-1);
		}
		else
			selecting=false;

		set_cursor_position(0);
	}

	//KEY END
	else if(key.code==KEY_END)
	{
		//SHIFT
		if(k.shift())
		{
			if(!selecting)
				select_text(cursor_pos,get_last_pos());
			else if(cursor_pos>=selection_end)
				add_selection(cursor_pos+1,get_last_pos());
			else
				select_text(selection_end+1,get_last_pos());
		}
		else
			selecting=false;

		set_cursor_position(get_last_pos());
	}

	//KEY RETURN
	else if(key.code==KEY_RETURN)
	{
		if(!readonly)
			send_event("trigger");
	}
	
	//KEY INSERT
	else if(key.code==KEY_INSERT)
	{
		if(!readonly)
			set_insert_mode(!insert_mode);
	}

	//CTRL-C
	else if(key.code==KEY_C && k.ctrl())
	{
		copy_selected_text();
	}

	//CTRL-X
	else if(key.code==KEY_X && k.ctrl())
	{
		cut_selected_text();
	}

	//CTRL-V
	else if(key.code==KEY_V && k.ctrl())
	{
		paste_text_from_clipboard();
	}

}



void eEditbox::on_key_up(Key& key){}



//***** ON TEXT
void eEditbox::on_text(const Str& txt)
{
	
	//insert mode
	if(insert_mode)
	{
		if(selecting)
			remove_selection();
		if(cursor_pos<get_last_pos())
			remove_chars(cursor_pos,txt.get_utf8_len(),false);
		add_chars(cursor_pos,txt);
		set_cursor_position(cursor_pos+txt.get_utf8_len());
	}

	//normal mode
	else
	{
		if(selecting)
			remove_selection();
		add_chars(cursor_pos,txt);
		set_cursor_position(cursor_pos+txt.get_utf8_len());
	}
}



void eEditbox::on_resize(int width,int height){}
void eEditbox::on_parent_resize(){}



//***** ON SELECT
void eEditbox::on_select()
{
	Input::set_key_down_repeat(true);
}



//***** ON UNSELECT
void eEditbox::on_unselect()
{
	Input::set_key_down_repeat(false);
	selecting=false;
}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//***** SET TEXT
void eEditbox::set_text(const Str& txt,bool override_readonly)
{
	if(!readonly || override_readonly)
	{
		Str filtered=apply_filter(txt);

		if(text!=filtered)
		{
			text=filtered;
			send_event("change");
			dirty=true;
		}
	}
}



//***** SET CUSTOM
void eEditbox::set_custom(Texture* tex,int borderw,bool autosize)
{
	//resize editbox if autosize is enabled
	if(autosize)
		resize(tex->width(),tex->height());

	set_border_width(borderw);

	custom_bg=tex;
	customized=true;
	dirty=true;
}



//***** SET CUSTOM
void eEditbox::set_custom(const Str& filename,int borderw,bool autosize)
{
	set_custom(Cache::texture(filename),borderw,autosize);
}



//***** SET CUSTOMIZED
void eEditbox::set_customized(bool custom)
{
	customized=custom;
	dirty=true;
}



//***** SET BORDER WIDTH
void eEditbox::set_border_width(int bw)
{
	border_w=bw;
	dirty=true;
}


//***** SET CURSOR POSITION
void eEditbox::set_cursor_position(int pos)
{
	if(pos<0)
		pos=0;
	if(pos>get_last_pos())
		pos=get_last_pos();

	//check if we need to change the view_pos
	if(pos<view_pos)
		set_view_pos(pos-min_right_view);
	else if(pos>get_view_last())
		set_view_pos(pos-get_view_w()+min_right_view);
	
	cursor_pos=pos;
	dirty=true;
}



//***** SET VIEW POS
void eEditbox::set_view_pos(int pos)
{
	if(pos>get_last_pos()-min_right_view)
		pos=(get_last_pos()-min_right_view);

	if(pos<0)
		pos=0;
	
	view_pos=pos;
	dirty=true;
}



//***** SET MIN RIGHT VIEW
void eEditbox::set_min_right_view(int amount)
{
	if(amount<1)
		amount=1;

	min_right_view=amount;
	dirty=true;
}



//***** SET INSERT MODE
void eEditbox::set_insert_mode(bool insert)
{
	insert_mode=insert;
	dirty=true;
}



//***** SELECT TEXT
void eEditbox::select_text(int pos1,int pos2)
{
	if(pos1<0)
		pos1=0;
	if(pos2<0)
		pos2=get_last_pos()-1;
	selection_start=(pos1<pos2?pos1:pos2);
	selection_end=(pos2>pos1?pos2:pos1);

	if(selection_start<0)
		selection_start=0;
	if(selection_start>get_last_pos())
		selection_start=get_last_pos();

	if(selection_end<0)
		selection_end=0;
	if(selection_end>=get_last_pos())
		selection_end=get_last_pos()-1;

	selecting=true;
	dirty=true;
}



//***** SET PASSWORD MODE
void eEditbox::set_password_mode(bool pass,const Str& chr)
{
	password_mode=pass;
	set_password_char(chr);
	dirty=true;
}



//***** SET PASSWORD CHAR
void eEditbox::set_password_char(const Str& chr)
{
	int l;
	if(chr.get_utf8_char(0,l))
	password_char=chr.sub(0,l);
	dirty=true;
}



//***** GET SELECTED TEXT
Str eEditbox::get_selected_text()
{
	Str s;

	if(selecting)
		s=get_text().sub(get_text().get_utf8_start(selection_start),get_text().get_utf8_start(selection_end+1)-get_text().get_utf8_start(selection_start));
	else
		s="";

	return s;
}



//***** SET READONLY
void eEditbox::set_readonly(bool read)
{
	readonly=read;
	dirty=true;
}



//***** COPY TEXT
void eEditbox::copy_text(const Str& txt,Str& dest)
{
	if(selecting)
		dest=txt;
}



//***** COPY SELECTED TEXT
void eEditbox::copy_selected_text(Str& dest)
{
	copy_text(get_selected_text(),dest);
}



//***** CUT SELECTED TEXT
void eEditbox::cut_selected_text(Str& dest)
{
	if(selecting)
	{
		dest=get_selected_text();
		remove_selection();
		set_cursor_position(selection_start);
	}
}



//***** PASTE TEXT
void eEditbox::paste_text(const Str& txt)
{
	if(txt.len())
	{
		if(selecting)
		{
			remove_selection();
			set_cursor_position(selection_start);
			add_chars(cursor_pos,txt);
		}
		else
			add_chars(cursor_pos,txt);

		set_cursor_position(cursor_pos+txt.get_utf8_len());
	}
}


//***** PASTE TEXT FROM CLIPBOARD
void eEditbox::paste_text_from_clipboard()
{
	paste_text(Clipboard::text);
}



//***** SET FILTER
void eEditbox::set_filter(EditboxFilter::Type f)
{
	filter=f;
	set_text(text);
}








//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************


//***** GET TEXT
Str eEditbox::get_text()
{
	Str s;

	if(password_mode)
	{
		int l=text.get_utf8_len();

		for(int a=0;a<l;a++)
			s+=password_char;
	}
	else
		s=text;

	return s;
}



//***** GET VISIBLE TEXT
Str eEditbox::get_visible_text()
{
	int view_w=w-(border_w*2);

	int first_byte=get_text().get_utf8_start(view_pos);
	Str s=reduce_string_to_fit(get_text().sub(first_byte),view_w);

	return s;
}



//***** REDUCE STRING TO FIT
Str eEditbox::reduce_string_to_fit(const Str& str,int width,int charmore)
{
	int pos=0;
	int cur_w=0;
	int c=0;
	
	for(;;)
	{
		//get next char and len
		int len;
		uint32_t ch=str.get_utf8_char(pos,len);
		//if end or error, break
		if(!ch) 
			break;

		//get char width
   		int ch_w=font->get_glyph(ch)->metrics.advance;
		
		//increase char counter if it fits it
		if(cur_w+ch_w>width)
		{
			if(c==charmore)
				break;
			c++;
		}



		//adjust width counter and string position
		cur_w+=ch_w;
		pos+=len;
	}

	return str.sub(0,pos);
}



//***** GET CURSOR X
int eEditbox::get_cursor_x()
{
	Str s=get_text().sub(get_text().get_utf8_start(view_pos),get_text().get_utf8_start(cursor_pos)-get_text().get_utf8_start(view_pos));
	int sw=font->len(s);
	return border_w+sw;

}



//***** GET CHAR W
int eEditbox::get_char_w(const Str& str,int pos)
{
	int len;
	int byte_pos=str.get_utf8_start(pos);

	uint32_t ch=str.get_utf8_char(byte_pos,len);
	if(!ch)
		return -1;
	
	return font->get_glyph(ch)->metrics.advance;

}



//***** GET VIEW W
int eEditbox::get_view_w()
{
	int view_w=w-(border_w*2);

	int first_byte=get_text().get_utf8_start(view_pos);
	return reduce_string_to_fit(get_text().sub(first_byte),view_w).get_utf8_len();
}



//***** GET VIEW LAST
inline int eEditbox::get_view_last()
{
	return get_view_w()+view_pos;
}



//***** GET LAST POS
inline int eEditbox::get_last_pos()
{
	return get_text().get_utf8_len();
}



//***** GET NEXT SPACE POS
int eEditbox::get_next_space_pos(bool backward)
{
	Str str=get_text();
	Str s;
	
	int space_pos;

	int p=-1;
	int pos=0;
	int c=0;
	bool found=false;

	if(backward)
	{
		s=str.sub(0,str.get_utf8_start(cursor_pos));

		for(;;)
		{
			int a=cursor_pos-1-c;
			if(a<0)
				break;
			pos=s.get_utf8_start(a);

			int len;
			uint32_t ch=s.get_utf8_char(pos,len);
			if(!ch) 
				break;

			Str ss=s.sub(pos,len);
			if(found && ss!=" ")
			{
				p=pos;
				break;
			}
			else if(ss==" " && c)
				found=true;

			c++;
		}

		if(p==-1)
			space_pos=0;
		else
			space_pos=cursor_pos-c;
	}
	else
	{
		s=str.sub(str.get_utf8_start(cursor_pos+1));

		for(;;)
		{
			int len;
			uint32_t ch=s.get_utf8_char(pos,len);
			if(!ch) 
				break;

			Str ss=s.sub(pos,len);
			if(found && ss!=" ")
			{
				p=pos;
				break;
			}
			else if(ss==" ")
				found=true;

			pos+=len;
			c++;
		}

		if(p==-1)
			space_pos=get_last_pos();
		else
			space_pos=cursor_pos+c;
	}
	return space_pos;
}



//***** ADD CHARS
void eEditbox::add_chars(int pos,Str chars)
{
	if(pos<0)
		pos=0;
	if(pos>get_last_pos())
		pos=get_last_pos();
	
	Str left=text.sub(0,text.get_utf8_start(pos));
	Str right=text.sub(text.get_utf8_start(pos));

	set_text(left+chars+right);
}



//***** REMOVE CHARS
void eEditbox::remove_chars(int pos,int len,bool backward)
{
	if(pos<0)
		pos=0;
	if(pos>get_last_pos())
		pos=get_last_pos();
	
	int byte_pos1;	
	int byte_pos2;

	if(backward)
	{
		byte_pos1=text.get_utf8_start(pos-len);
		byte_pos2=text.get_utf8_start(pos);
	}
	else
	{
		byte_pos1=text.get_utf8_start(pos);
		byte_pos2=text.get_utf8_start(pos+len);
	}
	Str left,right;
	left=text.sub(0,byte_pos1);
	right=text.sub(byte_pos2);

	set_text(left+right);
}



//***** REMOVE CHARS RANGE
void eEditbox::remove_chars_range(int pos1,int pos2)
{
	int p1=(pos1<pos2?pos1:pos2);
	int p2=(pos2>pos1?pos2:pos1);

	if(p1<0)
		p1=0;
	if(p2>get_last_pos())
		p2=get_last_pos();

	remove_chars(pos1,pos2-pos1+1,false);
}



//***** GET SELECTION X
int eEditbox::get_selection_x()
{
	int sx=border_w+font->len(get_text().sub(get_text().get_utf8_start(view_pos),get_text().get_utf8_start(selection_start)-get_text().get_utf8_start(view_pos)));
	if(sx<border_w)
		sx=border_w;

	return sx;
}



//***** GET SELECTION W
int eEditbox::get_selection_w()
{
	Str s;

	//get part of the string
	if(selection_start<=view_pos)
		s=get_text().sub(get_text().get_utf8_start(view_pos),get_text().get_utf8_start(selection_end+1)-get_text().get_utf8_start(view_pos));
	else
		s=get_text().sub(get_text().get_utf8_start(selection_start),get_text().get_utf8_start(selection_end+1)-get_text().get_utf8_start(selection_start));

	//get string width
	int sw=font->len(s);

	//reduce width if too large
	int sx=get_selection_x();
	if(sx+sw>(w-border_w))
		sw=(w-border_w)-sx;
	
	return sw+1;

}



//***** ADD SELECTION
void eEditbox::add_selection(int pos1,int pos2)
{
	int p1=(pos1<pos2?pos1:pos2);
	int p2=(pos2>pos1?pos2:pos1);

	if(p1<0)
		p1=0;
	if(p2>=get_last_pos())
		p2=get_last_pos()-1;
	
	//already selecting, adding selection to current one
	if(selecting)
	{
		int min=(p1<selection_start?p1:selection_start);
		int max=(p2>selection_end?p2:selection_end);
		select_text(min,max);
	}

	//new selection, simply create a new one
	else
		select_text(p1,p2);
}



//***** DEL SELECTION
void eEditbox::del_selection(int pos1,int pos2)
{
	int p1=(pos1<pos2?pos1:pos2);
	int p2=(pos2>pos1?pos2:pos1);

	if(p1<0)
		p1=0;
	if(p2>=get_last_pos())
		p2=get_last_pos()-1;
	
	//deleting selection from current one
	if(selecting)
	{
		//check if selection to remove is out of current selection range
		if(p2<selection_start || p1>selection_end)
			return;

		//check if selection to remove completely remove selection
		if(p1<=selection_start && p2>=selection_end)
		{
			selecting=false;
			return;
		}

		//remove selection at begining
		if(p1<=selection_start)
			select_text(p2+1,selection_end);

		//remove selection at end
		else
			select_text(selection_start,p1-1);

	}

}



//***** REMOVE SELECTION
void eEditbox::remove_selection()
{
	if(selecting)
	{
		remove_chars_range(selection_start,selection_end);
		selecting=false;
	}
}



//***** FIND POS AT
int eEditbox::find_pos_at(int mx)
{
	int tx=mx-border_w;
	Str vt=get_visible_text();
	Str ss=reduce_string_to_fit(vt,tx);
	Str s=reduce_string_to_fit(vt,tx,1);
	int l;
	uint32_t ch=s.get_utf8_char(ss.len(),l);
   	int ch_w=font->get_glyph(ch)->metrics.advance;

	s=reduce_string_to_fit(vt,tx+(ch_w/2));

	return view_pos+s.get_utf8_len();
	
}



//***** APPLY FILTER
Str eEditbox::apply_filter(const Str& str)
{
	Str filtered="";

	int pos=0;
	for(;;)
	{
		//get next char and len
		int len;
		uint32_t ch=str.get_utf8_char(pos,len);
		//if end or error, break
		if(!ch) 
			break;

		//add char to string
		Str s=str.sub(pos,len);
		if(Str news=filter_char(s))
		{
			if(news!="")
				filtered+=news;
		}

		//adjust string position
		pos+=len;
	}

	return filtered;
}



//***** FILTER CHAR
Str eEditbox::filter_char(const Str& ch)
{

	switch(filter)
	{
		//NONE
		case EditboxFilter::None:
		{
			return ch;
		}
		break;

		//BINARY
		case EditboxFilter::Binary:
		{
			if(ch=="0" || ch=="1")
			return ch;
		}
		break;

		//INT
		case EditboxFilter::Int:
		{
			if((ch>="0" && ch<="9") || ch=="-")
				return ch;
		}
		break;

		//FLOAT
		case EditboxFilter::Float:
		{
			if((ch>="0" && ch<="9") || ch=="." || ch=="-")
				return ch;
		}
		break;

		//HEX
		case EditboxFilter::Hex:
		{
			Str s=ch;

			//upcase automatically
			if(ch>="a" && ch<="f")
				s=ch.toupper();

			if((s>="0" && s<="9") || (s>="A" && s<="F"))
				return s;
		}
		break;

		//OCT
		case EditboxFilter::Oct:
		{
			if(ch>="0" && ch<="7")
				return ch;
		}
		break;

		//ALPHA
		case EditboxFilter::Alpha:
		{
			if((ch>="a" && ch<="z") || (ch>="A" && ch<="Z"))
				return ch;
		}
		break;

		//ALPHANUMERIC
		case EditboxFilter::Alphanumeric:
		{
			if((ch>="a" && ch<="z") || (ch>="A" && ch<="Z") || (ch>="0" && ch<="9") || ch=="-")
				return ch;
		}
		break;

		//FILENAME
		case EditboxFilter::Filename:
		{
			if((ch>="a" && ch<="z") || (ch>="A" && ch<="Z") || (ch>="0" && ch<="9") || ch=="-" || ch=="." || ch=="/" || ch=="\\" || ch=="_" || ch=="(" || ch==")" || ch=="[" || ch=="]" || ch==":" || ch=="~" || ch==" ")
				return ch;
		}
		break;

		//IP
		case EditboxFilter::IP:
		{
			if((ch>="0" && ch<="9") || ch==".")
				return ch;
		}
		break;

	}

	return "";
}







