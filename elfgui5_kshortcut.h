#pragma once
#include <pix5.h>
#include "elfgui5.h"




class KShortcut
{
public:

	bool enabled;
	Str name;
	Str type;

	bool ctrl;
	bool alt;
	bool shift;
	bool gui;

	Key key;

	void (*action)();

	//constructors
	KShortcut();
	KShortcut(bool c,bool a,bool s,bool g,KeyCode k);
	KShortcut(bool c,bool a,bool s,bool g,KeyCode k,ACTION act,bool enable=true);
	KShortcut(const Str& kname,bool c,bool a,bool s,bool g,KeyCode k,ACTION act,bool enable=true);
	KShortcut(const Str& kname,const Str& ktype,bool c,bool a,bool s,bool g,KeyCode k,ACTION act,bool enable=true);

	//settings
	void clear();
	void set(bool c,bool a,bool s,bool g,KeyCode k);
	void set(bool c,bool a,bool s,bool g,KeyCode k,ACTION act,bool enable=true);
	void set(const Str& kname,bool c,bool a,bool s,bool g,KeyCode k,ACTION act,bool enable=true);
	void set(const Str& kname,const Str& ktype,bool c,bool a,bool s,bool g,KeyCode k,ACTION act,bool enable=true);

	//checks
	bool compare(KShortcut* shortcut);
	bool compare(bool c,bool a,bool s,bool g,KeyCode k);
	bool compare_now();

	//infos
	Str get_short_name();
	Str get_full_name();

	//actions
	void execute();
	bool compare_and_execute(KShortcut* shortcut);
	bool compare_and_execute(bool c,bool a,bool s,bool g,KeyCode k);
	bool compare_now_and_execute();
	KShortcut* clone();
};
