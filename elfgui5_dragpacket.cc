#include <pix5.h>
#include "elfgui5.h"


//constructor
DragPacket::DragPacket(const Str& icon_path,int offx,int offy)
{
	icon=Cache::texture(icon_path);
	offset_x=offx;
	offset_y=offy;

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

