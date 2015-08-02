#include <pix5.h>
#include "elfgui5.h"


//constructor
DragPacket::DragPacket(Texture* picon,int offx,int offy)
{
	icon=picon;
	offset_x=offx;
	offset_y=offy;

	command="";
	sender=NULL;
	element=NULL;

	for(int a=0;a<5;a++)
	{
		i[a]=0;
		i64[a]=0;
		f[a]=0;
		d[a]=0;
		b[a]=false;
		s[a]="";
	}
}



//constructor
DragPacket::DragPacket(const Str& icon_path,int offx,int offy)
{
	DragPacket(Texture::load(icon_path),offx,offy);
}



//destructor
DragPacket::~DragPacket()
{
	delete icon;
}
