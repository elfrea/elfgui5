#include <pix5.h>
#include "game.h"

#include "elfgui5.h"



//game variables
Str Game::name;


//temp variables
ePanel* panel;
ePanel* panel2;
ePanel* panel3;



//***** INIT
void Game::init()
{
	//game init
	name="Game";

	#ifdef DBG
	Log::debug("");
	Log::debug("'%s' initializing...",name.ptr());
	Log::debug("************************************");
	#endif
	
	Display::set_mode(VideoMode::resizable(1366,768,false));
	ElfGui5::init();

	panel=new ePanel("panel1",10,10,300,300);
	panel->can_be_resized=true;
	panel->set_custom_cursor("gfx/elements/cursor_edit.png",2,7);
	panel->set_text("Testing Two es wo");
	ElfGui5::base->add_child(panel);

	panel2=new ePanel("panel2",10,30,80,80);
	panel2->can_be_moved=true;
	panel2->set_move_area(0,0,80,20);
	panel2->move_area_auto_width=true;
	panel2->can_be_resized=true;
	panel2->mouse_down_bring_to_front=true;
	panel->add_child(panel2);

	panel3=new ePanel("panel3",220,30,50,50,true);
	panel3->move_area_auto_width=true;
	panel3->move_area_auto_height=true;
	panel3->can_be_moved=true;
	panel3->can_be_resized=true;
	panel3->mouse_down_bring_to_front=true;
	panel3->set_tex("gfx/cursor_move.png",Align::Middle);
	panel3->forward_event_to_parent=false;
	panel->add_child(panel3);


	#ifdef DBG
	Log::debug("************************************");
	Log::debug("Game initialization complete!");
	Log::debug("");
	#endif
}




//***** LOOP
int Game::loop()
{
	//fetch elfgui5 events
	while(Event* ev=ElfGui5::fetch_event())
	{
		manage_event(ev);
		delete ev;
	}

	//elfgui5 main loop
	if(ElfGui5::loop())
		return 1;

	return 0;
}



//***** DRAW
void Game::draw()
{

	ElfGui5::draw();
}



//***** SHUTDOWN
void Game::shutdown()
{
	#ifdef DBG
	Log::debug("");
	Log::debug("'%s' shutting down...",name.ptr());
	Log::debug("************************************");
	#endif

	ElfGui5::shutdown();

	#ifdef DBG
	Log::debug("************************************");
	Log::debug("Game shutdown complete!");
	Log::debug("");
	#endif
}




//********************************************************************************************



//***** MANAGE EVENT
void Game::manage_event(Event* ev)
{
	Log::log("GLOBAL EVENT RECEIVED: Sender: %s    Command: %s",ev->sender->name.ptr(),ev->command.ptr());
}





