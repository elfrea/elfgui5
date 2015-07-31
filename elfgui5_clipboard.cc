#include <pix5.h>
#include "elfgui5.h"



Str Clipboard::text;
Str Clipboard::mouse_text;
Texture* Clipboard::tex;




//***** CLEAR
void Clipboard::clear()
{
	text="";
	mouse_text="";
	tex=NULL;
}



//***** KILL
void Clipboard::kill()
{
	delete text;
	delete mouse_text;
}
