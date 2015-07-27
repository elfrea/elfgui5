#include <pix5.h>
#include "game.h"

#include "elfgui5.h"



//game variables
Str Game::name;


//temp variables
eWindow* win1;
eRadiobutton* radio1;
eRadiobutton* radio2;
eRadiobutton* radio3;
eRadiobutton* radio4;
eButton* but1;
eCheckbox* check1;
ePushbutton* push1;
eRadiopush* rpush1;
eRadiopush* rpush2;
eRadiopush* rpush3;



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

	win1=new eWindow("window1",340,50,300,440,"Test Window");
	ElfGui5::base->add_child(win1);

	radio1=new eRadiobutton("radio1",10,10,100,25,"Choice 1A","a",true);
	win1->add_child(radio1);

	radio2=new eRadiobutton("radio2",10,40,100,25,"Choice 2A","a");
	win1->add_child(radio2);

	radio3=new eRadiobutton("radio3",10,70,100,25,"Choice 1B","b",true);
	radio3->set_custom("gfx/test/test_radiobutton_box.png","gfx/test/test_radiobutton_mark.png");
	win1->add_child(radio3);

	radio4=new eRadiobutton("radio4",10,100,100,25,"Choice 2B","b");
	radio4->set_custom("gfx/test/test_radiobutton_box.png","gfx/test/test_radiobutton_mark.png");
	win1->add_child(radio4);

	but1=new eButton("button1",10,140,150,30,"Test");
	but1->shrink();
	win1->add_child(but1);

	check1=new eCheckbox("checkbox1",10,180,10,10,"Check it!");
	win1->add_child(check1);

	push1=new ePushbutton("pushbutton1",10,210,100,30,"PUSH");
	push1->set_custom("gfx/test/test_but.png","gfx/test/test_but_pushed.png","gfx/test/test_but_hover.png");
	win1->add_child(push1);

	rpush1=new eRadiopush("radiopush1",10,250,70,50,"RPUSH1");
	win1->add_child(rpush1);

	rpush2=new eRadiopush("radiopush2",100,250,70,50,"RPUSH2");
	win1->add_child(rpush2);

	rpush3=new eRadiopush("radiopush3",190,250,70,50,"RPUSH3");
	win1->add_child(rpush3);


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





