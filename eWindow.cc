#include <pix5.h>
#include "elfgui5.h"



//constructor
eWindow::eWindow(const Str& ename,int ex,int ey,int ew,int eh,const Str& etitle):Element(ename,ex,ey,ew,eh)
{
	#define DEFAULT_TITLEBAR_H 25
	#define DEFAULT_STATUSBAR_H 15

	//parent class vars
	type="window";
	mouse_down_bring_to_front=true;
	can_be_moved=true;
	can_be_resized=true;
	set_move_area(0,0,ew,DEFAULT_TITLEBAR_H);
	move_area_auto_width=true;
	
	//own config vars

	//own internal config vars (use config functions to modify)

	//own internal vars

	//own elements
	titlebar=new ePanel("titlebar",0,0,ew,DEFAULT_TITLEBAR_H);
	titlebar->can_be_clicked_through=true;
	add_child_on_window(titlebar);
	titlebar->set_anchor(true,false,true,true);

	statusbar=new ePanel("statusbar",0,eh-DEFAULT_STATUSBAR_H,ew,DEFAULT_STATUSBAR_H);
	statusbar->can_be_clicked_through=true;
	statusbar->can_be_resized=true;
	add_child_on_window(statusbar);
	statusbar->set_anchor(false,true,true,true);

	body=new ePanel("body",0,DEFAULT_TITLEBAR_H,ew,eh-(DEFAULT_TITLEBAR_H+DEFAULT_STATUSBAR_H));
	add_child_on_window(body);
	body->set_anchor(true,true,true,true);

	//other
	set_min_size(150,100);
	set_title(etitle);
	set_icon("gfx/elements/icon_window.png");
}



//destructor
eWindow::~eWindow()
{
}








//****************************************************************
//BASIC FUNCTIONS
//****************************************************************


//***** LOOP
void eWindow::loop()
{
}



//***** DRAW
void eWindow::draw()
{
	draw_panel(image,false,enabled);

}








//****************************************************************
//EVENTS FUNCTIONS
//****************************************************************


//void eWindow::on_event(Event* ev){}
void eWindow::on_mouse_enter(int mx,int my){}
void eWindow::on_mouse_leave(){}
void eWindow::on_mouse_move(int mx,int my){}
void eWindow::on_mouse_down(int but,int mx,int my){}
void eWindow::on_mouse_up(int but,int mx,int my){}
void eWindow::on_mouse_click(int but,int mx,int my){}
void eWindow::on_mouse_doubleclick(int but,int mx,int my){}
void eWindow::on_mouse_wheel_down(int mx,int my){}
void eWindow::on_mouse_wheel_up(int mx,int my){}
void eWindow::on_mouse_drag_out(){}
void eWindow::on_mouse_drag_in(DragPacket* dragpacket){}
void eWindow::on_key_down(Key& key){}
void eWindow::on_key_up(Key& key){}
void eWindow::on_text(const Str& text){}
void eWindow::on_resize(int width,int height){}
void eWindow::on_parent_resize(){}








//****************************************************************
//FAMILY FUNCTIONS
//****************************************************************


//***** ADD CHILD (ON BODY)
void eWindow::add_child(Element* child)
{
	body->insert_child(child,body->children.size());
}



//***** INSERT CHILD (OVERRIDE)
void eWindow::insert_child(Element* child,int index)
{
	body->insert_child(child,index);
}



//***** REMOVE CHILD (OVERRIDE)
void eWindow::remove_child(Element* child)
{
	body->remove_child(child);
}






//***** ADD CHILD (ON WINDOW)
void eWindow::add_child_on_window(Element* child)
{
	insert_child_on_window(child,children.size());
}



//***** INSERT CHILD (ON WINDOW)
void eWindow::insert_child_on_window(Element* child,int index)
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



//***** REMOVE CHILD (ON WINDOW)
void eWindow::remove_child_on_window(Element* child)
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
//OWN CONFIG FUNCTIONS
//****************************************************************


//SET TITLE
void eWindow::set_title(const Str& etitle,Align::Type align,int offx,int offy)
{
	titlebar->set_text(etitle,align,offx,offy);
}



//SET ICON
void eWindow::set_icon(Texture* tex,Align::Type align,int offx,int offy)
{
	titlebar->set_tex(tex,align,offx,offy);
}



//SET ICON
void eWindow::set_icon(const Str& filename,Align::Type align,int offx,int offy)
{
	titlebar->set_tex(filename,align,offx,offy);
}



//SET TITLEBAR HEIGHT
void eWindow::set_titlebar_height(int th)
{
	titlebar->resize(w,th);
	titlebar->set_anchor(true,false,true,true);
	set_move_area(0,0,w,th);
	body->y=th;
	body->resize(w,h-th-statusbar->h);
	body->set_anchor(true,true,true,true);
}



//SET STATUSBAR HEIGHT
void eWindow::set_statusbar_height(int sh)
{
	body->resize(w,h-sh-titlebar->h);
	body->set_anchor(true,true,true,true);
	statusbar->y=h-sh;
	statusbar->resize(w,sh);
	statusbar->set_anchor(false,true,true,true);
}








//****************************************************************
//OWN INTERNAL FUNCTIONS
//****************************************************************







