#include <pix5.h>
#include "elfgui5.h"




//###############################################################################################
//custom
//###############################################################################################


//***** TEST
void Actions::test()
{
	Log::log("Test");
}








//###############################################################################################
//global
//###############################################################################################


//***** QUIT PROGRAM
void Actions::quit_program()
{
	ElfGui5::ready_to_quit=true;
}



//***** TOGGLE FULLSCREEN
void Actions::toggle_fullscreen()
{
	VideoMode vm=Display::get_mode();
	
	if(vm.type==VideoModeType::Resizable)
		Display::set_mode(VideoMode::fullscreen(vm.width,vm.height,false));
	else
		Display::set_mode(VideoMode::resizable(vm.width,vm.height,false));
}







