#include <pix5.h>
#include "elfgui5.h"




//constructor
Event::Event(Element* sndr,const Str& cmd)
{
	sender=sndr;
	command=cmd;
}


//destructor
Event::~Event()
{
}



