#pragma once

#include <pix5.h>
#include "elfgui5.h"


class eItem
{
public:

	Str text;
	int value;
	Texture* icon;

	int i[3];
	int64_t i64[3];
	float f[3];
	double d[3];
	bool b[3];
	Str s[3];

	//constructor
	eItem(const Str& txt,int val=0,Texture* ico=NULL);
	eItem(const Str& txt,int val,const Str& ico);
	//destructor
	~eItem();


	void clear();
	void set(const Str& txt,int val=0,Texture* ico=NULL);
	void set(const Str& txt,int val,const Str& ico);
	eItem* clone();


};





