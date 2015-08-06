#include <pix5.h>
#include "elfgui5.h"






//***** INIT
void KShortcuts::init()
{
	add(new KShortcut("Test","custom",false,false,false,false,KEY_F1,Actions::test));

	add(new KShortcut("Quit program",			"global",	false,	false,	false,	false,	KEY_PAUSE,	Actions::quit_program));
	add(new KShortcut("Toggle Fullscreen",		"global",	false,	false,	false,	false,	KEY_F12,	Actions::toggle_fullscreen));
	add(new KShortcut("Window Close",			"global",	false,	false,	false,	true,	KEY_F4,		Actions::window_close));
	add(new KShortcut("Window Maximize",		"global",	false,	false,	false,	true,	KEY_RETURN,	Actions::window_maximize));
	add(new KShortcut("Window Minimize",		"global",	false,	false,	false,	true,	KEY_MINUS,	Actions::window_minimize));
	add(new KShortcut("Window Shade",			"global",	false,	false,	false,	true,	KEY_GRAVE,	Actions::window_shade));
	add(new KShortcut("Window Bring to Front",	"global",	false,	false,	false,	true,	KEY_UP,		Actions::window_bring_to_front));
	add(new KShortcut("Window Send to Back",	"global",	false,	false,	false,	true,	KEY_DOWN,	Actions::window_send_to_back));
}



//***** KILL
void KShortcuts::kill()
{
	ElfGui5::kshortcuts.clear_del();
}



//***** PROCESS
void KShortcuts::process(const Str& type)
{
	for(int a=0;a<ElfGui5::kshortcuts.size();a++)
	{
		if(ElfGui5::kshortcuts[a]->type==type)
		{
			if(ElfGui5::kshortcuts[a]->compare_now_and_execute())
				break;
		}
	}
}



//***** ADD
void KShortcuts::add(KShortcut* ks)
{
	ElfGui5::kshortcuts.add(ks);
}



//***** REMOVE
void KShortcuts::remove(KShortcut* ks)
{
	int index=ElfGui5::kshortcuts.find(ks);
	if(index!=-1)
		ElfGui5::kshortcuts.remove_del(index);
}



//***** MODIFY
void KShortcuts::modify(class KShortcut* ks,bool c,bool a,bool s,bool g,KeyCode k)
{
	ks->set(c,a,s,g,k);
}



//***** MODIFY
void KShortcuts::modify(const Str& name,bool c,bool a,bool s,bool g,KeyCode k)
{
	for(int a=0;a<ElfGui5::kshortcuts.size();a++)
	{
		if(ElfGui5::kshortcuts[a]->name==name)
		{
			modify(ElfGui5::kshortcuts[a],c,a,s,g,k);
			break;
		}
	}
}



//***** FIND
KShortcut* KShortcuts::find(const Str& name)
{
	for(int a=0;a<ElfGui5::kshortcuts.size();a++)
	{
		if(ElfGui5::kshortcuts[a]->name==name)
			return ElfGui5::kshortcuts[a];
	}

	return NULL;
}



//***** FIND
KShortcut* KShortcuts::find(bool c,bool a,bool s,bool g,KeyCode k)
{
	for(int a=0;a<ElfGui5::kshortcuts.size();a++)
	{
		if(ElfGui5::kshortcuts[a]->ctrl==c && ElfGui5::kshortcuts[a]->alt==a && ElfGui5::kshortcuts[a]->shift==s && ElfGui5::kshortcuts[a]->gui==g && ElfGui5::kshortcuts[a]->key.code==k)
			return ElfGui5::kshortcuts[a];
	}

	return NULL;
}










