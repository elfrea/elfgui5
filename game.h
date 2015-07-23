#pragma once

#include <pix5.h>






//***** GAME
class Game
{
public:

	//game variables
	static Str name;

	//main functions
	static void init();
	static int loop();
	static void draw();
	static void shutdown();

};










