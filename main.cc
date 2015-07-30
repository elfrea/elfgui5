#include <pix5.h>

#include "game.h"






//***** MAIN ENTRY POINT
int main(int argc, char **argv)
{
	try
	{
		//main init
		pix_init("Test");
		Game::init();
		
		//main loop
		for(;;)
		{
			if(Game::loop())
				break;
			Game::draw();

			Display::render();
			Display::swap();
		}
		
		//main shutdown
		Game::shutdown();
		pix_shutdown();

	}
	catch(Error e)
	{
		printf("Error: %s\n", e.format().ptr());
	}

	return 0;

}

