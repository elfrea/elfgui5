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



//***** WINDOW CLOSE
void Actions::window_close()
{
	eWindow* win=ElfGui5::get_active_window();
	if(win)
		win->close();
}



//***** WINDOW MAXIMIZE
void Actions::window_maximize()
{
	eWindow* win=ElfGui5::get_active_window();
	if(win)
		win->maximize();
}



//***** WINDOW MINIMIZE
void Actions::window_minimize()
{
	eWindow* win=ElfGui5::get_active_window();
	if(win)
		win->minimize();
}



//***** WINDOW SHADE
void Actions::window_shade()
{
	eWindow* win=ElfGui5::get_active_window();
	if(win)
		win->shade();
}



//***** WINDOW BRING TO FRONT
void Actions::window_bring_to_front()
{
	eWindow* win=ElfGui5::get_active_window();
	if(win)
		win->bring_to_front();
}



//***** WINDOW SEND TO BACK
void Actions::window_send_to_back()
{
	eWindow* win=ElfGui5::get_active_window();
	if(win)
		win->send_to_back();
}





