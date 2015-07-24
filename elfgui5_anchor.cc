#include <pix5.h>
#include "elfgui5.h"



//constructor
Anchor::Anchor(bool t,int ty,bool b,int by,bool l,int lx,bool r,int rx)
{
	top=t;
	bottom=b;
	left=l;
	right=r;

	top_y=ty;
	bottom_y=by;
	left_x=lx;
	right_x=rx;
}




//SET
void Anchor::set(bool t,int ty,bool b,int by,bool l,int lx,bool r,int rx)
{
	top=t;
	bottom=b;
	left=l;
	right=r;

	top_y=ty;
	bottom_y=by;
	left_x=lx;
	right_x=rx;
}



//IS NONE
bool Anchor::is_none()
{
	return (!top && !bottom && !left && !right);
}



//IS ALL
bool Anchor::is_all()
{
	return (top && bottom && left && right);
}




