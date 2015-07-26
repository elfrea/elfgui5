#include <pix5.h>
#include "game.h"

#include "elfgui5.h"



//game variables
Str Game::name;


//temp variables
eWindow* win1;
ePanel* panel;
ePanel* panel2;
ePanel* panel3;
ePanel* panel4;
eButton* but1;
eButton* but2;
eCheckbox* check1;
eCheckbox* check2;
eLabel* label1;
eGroupbox* group1;



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

	but1=new eButton("button1",10,80,80,25,"Button");
	but1->can_be_resized=true;
	win1->add_child(but1);

	but2=new eButton("button2",120,80,10,10,"Custom");
	but2->set_custom("gfx/test/test_but.png","gfx/test/test_but_pushed.png","gfx/test/test_but_hover.png",true,true);
	win1->add_child(but2);

	check2=new eCheckbox("checkbox2",140,120,100,20,"Patate Poilue",false);
	check2->set_custom("gfx/test/test_checkbox_box.png","gfx/test/test_checkbox_mark.png");
	win1->add_child(check2);

	panel4=new ePanel("panel4",10,160,10,10);
	panel4->set_text("PANEL",Align::Middle);
	panel4->can_be_moved=true;
	panel4->mouse_down_bring_to_front=true;
	panel4->set_move_area_autosize(true,true);
	panel4->set_custom("gfx/test/test_panel.png",true,true);
	win1->add_child(panel4);

	group1=new eGroupbox("groupbox1",140,160,100,80,"Group");
	group1->set_appearance(GroupboxAppearance::Panel3D);
	win1->add_child(group1);

	check1=new eCheckbox("checkbox1",10,120,100,20,"Checkbox",false);
	check1->can_be_resized=true;
	win1->add_child(check1);

	label1=new eLabel("label1",10,320,200,10,"Test Label, you can try and resize it and the text will be juunified!",false,true);
	label1->can_be_resized=true;
	label1->set_move_area_autosize(true,true);
	label1->can_be_moved=true;
	win1->add_child(label1);

	panel=new ePanel("panel1",10,10,300,300);
	panel->can_be_resized=true;
	panel->set_custom_cursor("gfx/elements/cursor_edit.png",2,7);
	panel->set_text("Testing Two es wo",Align::Left);
	ElfGui5::base->add_child(panel);

	panel2=new ePanel("panel2",10,30,80,11);
	panel2->can_be_moved=true;
	panel2->set_move_area(0,0,80,20);
	panel2->set_move_area_autosize(true,false);
	panel2->can_be_resized=true;
	panel2->mouse_down_bring_to_front=true;
	panel->add_child(panel2);

	panel3=new ePanel("panel3",10,10,50,50,true);
	panel3->set_move_area_autosize(true,true);
	panel3->can_be_moved=true;
	panel3->can_be_resized=true;
	panel3->mouse_down_bring_to_front=true;
	panel3->set_tex("gfx/cursor_move.png",Align::Middle);
	panel3->forward_event_to_parent=false;
	win1->add_child(panel3);


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





