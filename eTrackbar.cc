#include <pix5.h>
#include "elfgui5.h"



//constructor
eTrackbar::eTrackbar(const Str& ename,int ex,int ey,int ew,int eh,int val,int min,int max,Orientation::Type orient):Element(ename,ex,ey,ew,eh)
{

	#define DEFAULT_TRACK_SIZE 5
	#define DEFAULT_TRACKER_SIZE 8

	//parent class vars
	type="trackbar";
	selectable=true;
	
	//own config vars
	track_size=DEFAULT_TRACK_SIZE;
	tracker_size=DEFAULT_TRACKER_SIZE;

	customized=false;
	show_rails=true;
	
	//own internal config vars (use config functions to modify)

	//own internal vars
	ready_to_track=false;
	
	//own elements

	//other
	set_value_range(min,max);
	set_value(val);
	set_orientation(orient);
	dirty=true;
}



//destructor
eTrackbar::~eTrackbar()
{
}








//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void eTrackbar::loop()
{
	Mouse& m=Input::get_mouse();

	//move track with mouse
	if(ready_to_track)
	{
		if(m.left())
		{
			int val;

			//HORIZONTAL
			if(orientation==Orientation::Horizontal)
			{
				int mx=m.x-get_true_x();
				if(customized)
					val=value_min+(mx-(custom_tracker->width()/2)+(w-custom_tracker->width())/(value_max-value_min)/2)*(value_max-value_min)/(w-custom_tracker->width());
				else
					val=value_min+(mx-(tracker_size/2)+(w-tracker_size)/(value_max-value_min)/2)*(value_max-value_min)/(w-tracker_size);
			}

			//VERTICAL
			else
			{
				int my=m.y-get_true_y();
				if(customized)
					val=value_min+(my-(custom_tracker->height()/2)+(h-custom_tracker->height())/(value_max-value_min)/2)*(value_max-value_min)/(h-custom_tracker->height());
				else
					val=value_min+(my-(tracker_size/2)+(h-tracker_size)/(value_max-value_min)/2)*(value_max-value_min)/(h-tracker_size);
			}

			set_value(val);
		}
		else
			ready_to_track=false;
	}
}



//***** DRAW
void eTrackbar::draw()
{
	image->clear(Color(0,0,0,0));

	//rails
	if(show_rails)
	{
		for(int a=0;a<=(value_max-value_min);a++)
		{
			int x1,y1,x2,y2;

			if(orientation==Orientation::Horizontal)
			{
				if(customized)
					x1=(custom_tracker->width()/2)+a*(w-custom_tracker->width())/(value_max-value_min);
				else
					x1=(tracker_size/2)+a*(w-tracker_size)/(value_max-value_min);
				x2=x1;
				y1=h-5;
				y2=h-1;
			}
			else
			{
				x1=w-5;
				x2=w-1;
				if(customized)
					y1=(custom_tracker->height()/2)+a*(h-custom_tracker->height())/(value_max-value_min);
				else
					y1=(tracker_size/2)+a*(h-tracker_size)/(value_max-value_min);
					y2=y1;
			}

			image->line(x1,y1,x2,y2,color->dark);
		}
	}

	//customized track/tracker
	if(customized)
	{
		//track
		image->blit(0,0,custom_bar);

		//tracker
		if(orientation==Orientation::Horizontal)
			image->blit(custom_tracker->width()/2+(w-custom_tracker->width())*get_percent()/100-(custom_tracker->width()/2),(h-custom_tracker->height())/2,custom_tracker);
		else
			image->blit((w-custom_tracker->width())/2,custom_tracker->height()/2+(h-custom_tracker->height())*get_percent()/100-(custom_tracker->height()/2),custom_tracker);

	}

	//normal track/tracker
	else
	{
		//track
		if(orientation==Orientation::Horizontal)
			draw_panel(image,color,false,enabled,tracker_size/2,(h-track_size)/2,w-(tracker_size/2),track_size);
		else
			draw_panel(image,color,false,enabled,(w-track_size)/2,tracker_size/2,track_size,h-(tracker_size/2));

		//tracker
		if(orientation==Orientation::Horizontal)
			draw_panel(image,color,false,enabled,tracker_size/2+(w-tracker_size)*get_percent()/100-(tracker_size/2),0,tracker_size,h);
		else
			draw_panel(image,color,false,enabled,0,tracker_size/2+(h-tracker_size)*get_percent()/100-(tracker_size/2),w,tracker_size);
	}
		

	//selected
	if(selected)
		draw_dotted_box(image,0,0,w,h,color->dark,1,1);
}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//void eTrackbar::on_event(Event* ev){}
void eTrackbar::on_mouse_enter(int mx,int my){}
void eTrackbar::on_mouse_leave(){}
void eTrackbar::on_mouse_move(int mx,int my){}



//***** ON MOUSE DOWN
void eTrackbar::on_mouse_down(int but,int mx,int my)
{
	if(but==1)
		ready_to_track=true;
}



void eTrackbar::on_mouse_up(int but,int mx,int my){}
//void eTrackbar::on_mouse_click(int but,int mx,int my){}
//void eTrackbar::on_mouse_doubleclick(int but,int mx,int my){}



//***** ON WHEEL DOWN
void eTrackbar::on_mouse_wheel_down(int mx,int my)
{
	set_value(value+1);
}



//***** ON WHEEL UP
void eTrackbar::on_mouse_wheel_up(int mx,int my)
{
	set_value(value-1);
}



void eTrackbar::on_mouse_drag_out(){}
void eTrackbar::on_mouse_drag_in(DragPacket* dragpacket){}



//***** ON KEY DOWN
void eTrackbar::on_key_down(Key& key)
{
	//LEFT,UP
	if(key.code==KEY_LEFT || key.code==KEY_UP)
		set_value(value-1);

	//RIGHT,DOWN
	else if(key.code==KEY_RIGHT || key.code==KEY_DOWN)
		set_value(value+1);
}



void eTrackbar::on_key_up(Key& key){}
void eTrackbar::on_text(const Str& text){}
void eTrackbar::on_resize(int width,int height){}
void eTrackbar::on_parent_resize(){}
void eTrackbar::on_select(){}
void eTrackbar::on_unselect(){}








//****************************************************************
//OWN CONFIG FUNCTIONS
//****************************************************************


//***** SET ORIENTATION
void eTrackbar::set_orientation(Orientation::Type orient)
{
	orientation=orient;
	dirty=true;
}



//***** SET VALUE
void eTrackbar::set_value(int val)
{
	if(val<value_min)
		val=value_min;
	if(val>value_max)
		val=value_max;
	
	if(value==val)
		return;

	value=val;
	send_event("change");
	dirty=true;
}



//***** SET VALUE RANGE
void eTrackbar::set_value_range(int min,int max)
{
	value_min=(min<max?min:max);
	value_max=(max>min?max:min);
	set_value(value);
}



//***** SET PERCENT
void eTrackbar::set_percent(int percent)
{
	set_value(value_min+((value_max-value_min)*percent/100));
}



//***** GET PERCENT
int eTrackbar::get_percent()
{
	return 100*(value-value_min)/(value_max-value_min);
}



//***** SET TRACK SIZE
void eTrackbar::set_track_size(int size)
{
	track_size=size;
	dirty=true;
}



//***** SET TRACKER SIZE
void eTrackbar::set_tracker_size(int size)
{
	tracker_size=size;
	dirty=true;
}



//***** SET CUSTOMIZED
void eTrackbar::set_customized(bool custom)
{
	customized=custom;
	dirty=true;
}



//***** SET CUSTOM
void eTrackbar::set_custom(Texture* bar,Texture* tracker,bool autosize)
{
	custom_bar=bar;
	custom_tracker=tracker;

	if(autosize)
	{
		
		//HORIZONTAL
		if(orientation==Orientation::Horizontal)
		{
			int aw=bar->width();
			int ah=(bar->height()>tracker->height()?bar->height():tracker->height());
			resize(aw,ah);
		}

		//VERTICAL
		else
		{
			int aw=(bar->width()>tracker->width()?bar->width():tracker->width());
			int ah=bar->height();
			resize(aw,ah);
		}
	}

	customized=true;
	dirty=true;
}



//***** SET CUSTOM
void eTrackbar::set_custom(const Str& bar,const Str& tracker,bool autosize)
{
	set_custom(Cache::texture(bar),Cache::texture(tracker),autosize);
}



//***** SHOW RAILS
void eTrackbar::set_show_rails(bool show)
{
	show_rails=show;
	dirty=true;
}








//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************







