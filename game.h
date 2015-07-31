#pragma once

#include <pix5.h>
#include "elfgui5.h"





//***** GAME
class cGame:public Obj
{
public:
	OBJ("cGame")

	//game variables
	static Str name;

	//main functions
	static void init();
	static int loop();
	static void draw();
	static void shutdown();

	static void manage_event(Event* ev);

};










