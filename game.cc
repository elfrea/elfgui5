#include <pix5.h>
#include "game.h"

#include "elfgui5.h"



//game variables
Str cGame::name;


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
eTexturebox* tex1;

eWindow* win2;
eScrollbar* hscroll1;
eScrollbar* vscroll1;
ePercentbar* percent1;
eEditbox* edit1;
eEditbox* edit2;
eTimer* timer1;
eSpinner* spin1;
eSpinner* spin2;
eTrackbar* track1;
eTrackbar* track2;

eWindow* win3;
eTabbox* tabbox1;
eTab* tab1;
	eKeybox* keybox1;
	eListbox* list1;
eTab* tab2;
eTab* tab3;

//eTabbox* tabbox2;
//eTab* tab21;

//***** INIT
void cGame::init()
{
	//game init
	name="Game";

	#ifdef DBG
	Log::debug("");
	Log::debug("'%s' initializing...",name.ptr());
	Log::debug("************************************");
	#endif
	
	Display::set_mode(VideoMode::resizable(1366,768,true));
	ElfGui5::init();

	win1=new eWindow("window1",10,10,300,600,"Test Window");
	ElfGui5::base->add_child(win1);

	radio1=new eRadiobutton("radio1",10,10,100,25,"Choice 1A","a",true);
	win1->add_child(radio1);

	radio2=new eRadiobutton("radio2",10,40,100,25,"Choice 2A","a");
	win1->add_child(radio2);

	radio3=new eRadiobutton("radio3",10,70,100,25,"Choice 3A","a");
	win1->add_child(radio3);

	radio4=new eRadiobutton("radio4",10,100,100,25,"Choice 4A","a");
	win1->add_child(radio4);

	but1=new eButton("button1",10,140,150,30,"Test");
	but1->shrink();
	win1->add_child(but1);

	check1=new eCheckbox("checkbox1",10,180,10,10,"Check it!");
	win1->add_child(check1);

	push1=new ePushbutton("pushbutton1",10,210,100,30,"PUSH");
	push1->set_custom("gfx/test/test_but.png","gfx/test/test_but_pushed.png","gfx/test/test_but_hover.png","gfx/test/test_but_disabled.png");
	push1->set_enabled(false);
	win1->add_child(push1);

	rpush1=new eRadiopush("radiopush1",10,250,70,50,"RPUSH1");
	win1->add_child(rpush1);

	rpush2=new eRadiopush("radiopush2",100,250,70,50,"RPUSH2");
	win1->add_child(rpush2);

	rpush3=new eRadiopush("radiopush3",190,250,70,50,"RPUSH3");
	win1->add_child(rpush3);

	tex1=new eTexturebox("texturebox1",10,310,180,180,Texture::cache("gfx/test/test_tex.png"),1,false);
	tex1->set_texture_offset(30,30);
	tex1->set_dynamic(true);
	win1->add_child(tex1);

	
	
	
	
	
	win2=new eWindow("window2",50,50,300,600,"Test Window 2");
	win2->set_show_buttons(true,false,true,false);
	win2->set_statusbar_message("Status Test Message");
	ElfGui5::base->add_child(win2);

	hscroll1=new eScrollbar("h scrollbar1",10,10,280,20,4,122,Orientation::Horizontal);
	hscroll1->set_page_size(14);
	win2->add_child(hscroll1);

	vscroll1=new eScrollbar("v scrollbar1",10,40,20,280,-123,12,Orientation::Vertical);
	vscroll1->set_page_size(4);
	win2->add_child(vscroll1);

	percent1=new ePercentbar("percentbar1",10,340,280,25,30,0,100,true);
	//percent1->set_custom("gfx/test/test_percent_bg.png","gfx/test/test_percent_bar.png","gfx/test/test_percent_border.png");
	win2->add_child(percent1);

	edit1=new eEditbox("editbox1",10,380,200,25,"1blébléblé2");
//	edit1->set_password_mode(true);
	win2->add_child(edit1);

	edit2=new eEditbox("editbox2",10,410,200,25,"testing123");
	edit2->set_custom("gfx/test/test_editbox.png","gfx/test/test_editbox_disabled.png",15,true);
	edit2->set_filter(EditboxFilter::Filename);
	win2->add_child(edit2);

	timer1=new eTimer("timer1",500,false);
	win2->add_child(timer1);

	spin1=new eSpinner("spinner1",10,480,150,30,SpinnerMode::Double,0,0,100,Orientation::Horizontal);
	spin1->resize(130,20);
	win2->add_child(spin1);

	spin2=new eSpinner("spinner2",10,520,150,30,SpinnerMode::Bool,0,0,100,Orientation::Vertical);
	win2->add_child(spin2);

	track1=new eTrackbar("trackbar1",50,50,200,30,0,5,10,Orientation::Horizontal);
	win2->add_child(track1);

	track2=new eTrackbar("trackbar2",50,90,30,200,0,12,20,Orientation::Vertical);
	track2->set_custom("gfx/test/test_trackbar_track.png","gfx/test/test_trackbar_tracker.png","gfx/test/test_trackbar_tracker_disabled.png");
	win2->add_child(track2);






	win3=new eWindow("window3",400,50,500,700,"Test Window 3");
	win3->set_statusbar_message("Juun suce des canards poilus");
	win3->children_block_resize=false;
	ElfGui5::base->add_child(win3);

	tabbox1=new eTabbox("tabbox1",20,20,460,630,TabsPosition::Right);
	tabbox1->setup_drag(true,true,true);


	win3->add_child(tabbox1);
		tab1=tabbox1->add_new_tab("tab1");
			keybox1=new eKeybox("keybox1",10,10,150,25);
			tab1->add_child(keybox1);

			list1=new eListbox("listbox1",10,50,200,380,ListboxStyle::IconText);
			list1->multi_selection=true;
				list1->add_new_item("testing",121,"gfx/elements/icon_window.png");
				list1->add_new_item("Proute",2);
				list1->add_new_item("yaf",143);
				list1->add_new_item("schnif",126);
				list1->add_new_item("Proute",23);
				list1->add_new_item("yaf",14);
				list1->add_new_item("schnif",16);
				list1->add_new_item("testing",12);
				list1->add_new_item("Proute",8);
				list1->add_new_item("yaf",45);
				list1->add_new_item("schnif",36,"gfx/elements/icon_window.png");
				list1->add_new_item("testing",112);
				list1->add_new_item("Proute",23);
				list1->add_new_item("yaf",14);
				list1->add_new_item("schnif",16);
				list1->add_new_item("testing",12);
				list1->add_new_item("Proute",8);
				list1->add_new_item("yaf",45);
				list1->add_new_item("schnif",36,"gfx/elements/icon_window.png");
				list1->add_new_item("Proute",23);
				list1->add_new_item("yaf",14);
				list1->add_new_item("schnif",16);
				list1->add_new_item("testing",12);
				list1->add_new_item("Proute",8);
				list1->add_new_item("yaf",45);
				list1->add_new_item("schnif",36,"gfx/elements/icon_window.png");
			list1->sort_items_by_value();
			list1->set_show_value(true);
			tab1->add_child(list1);
			
		tab2=tabbox1->add_new_tab("tab2");
		tab3=tabbox1->add_new_tab("Patate Poilue");
	tabbox1->dock_tab(win1,0);

	tabbox1->switch_tab(tab1,tab3);
	tabbox1->select_tab(tab1);

//	tabbox2=new eTabbox("tabbox1",10,10,460,630,TabsPosition::Bottom);
//	tabbox2->setup_drag(true,true,true);
//		tab21=tabbox2->add_new_tab("tab21");
//	ElfGui5::base->add_child(tabbox2);
		
		











	#ifdef DBG
	Log::debug("************************************");
	Log::debug("Game initialization complete!");
	Log::debug("");
	#endif
}




//***** LOOP
int cGame::loop()
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
void cGame::draw()
{

	ElfGui5::draw();
}



//***** SHUTDOWN
void cGame::shutdown()
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
void cGame::manage_event(Event* ev)
{
	Log::log("GLOBAL EVENT RECEIVED: Sender: %s    Command: %s",ev->sender->name.ptr(),ev->command.ptr());
}





