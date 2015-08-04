#include <pix5.h>
#include "elfgui5.h"



//constructor
eItem::eItem(const Str& txt,int val,Texture* ico)
{
	clear();
	set(txt,val,ico);
}



//constructor
eItem::eItem(const Str& txt,int val,const Str& ico)
{
	clear();
	set(txt,val,ico);
}



//destructor
eItem::~eItem()
{
}



//***** CLEAR
void eItem::clear()
{
	text="";
	value=0;
	icon=NULL;

	for(int a=0;a<3;a++)
	{
		i[a]=0;
		i64[a]=0;
		f[a]=0;
		d[a]=0;
		b[a]=false;
		s[a]="";
	}
}



//***** SET
void eItem::set(const Str& txt,int val,Texture* ico)
{
	text=txt;
	value=val;
	icon=ico;
}



//***** SET
void eItem::set(const Str& txt,int val,const Str& ico)
{
	text=txt;
	value=val;
	icon=Texture::cache(ico);
}



//***** CLONE
eItem* eItem::clone()
{
	eItem* item=new eItem(text,value,icon);
	
	for(int a=0;a<3;a++)
	{
		item->i[a]=i[a];
		item->i64[a]=i64[a];
		item->f[a]=f[a];
		item->d[a]=d[a];
		item->b[a]=b[a];
		item->s[a]=s[a];
	}

	return item;
}




