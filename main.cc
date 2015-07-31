#include <pix5.h>

#include "game.h"






//***** MAIN ENTRY POINT
int main(int argc, char **argv)
{
	try
	{
		//main init
		pix_init("Test");
		cGame::init();
		
		//main loop
		for(;;)
		{
			if(cGame::loop())
				break;
			cGame::draw();

			Display::render();
			Display::swap();
		}
		
		//main shutdown
		cGame::shutdown();
		pix_shutdown();

	}
	catch(Error e)
	{
		printf("Error: %s\n", e.format().ptr());
	}

	return 0;

}

