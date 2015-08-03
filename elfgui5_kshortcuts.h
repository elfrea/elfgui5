#pragma once
#include <pix5.h>
#include "elfgui5.h"




class KShortcuts
{
public:

	static void init();
	static void kill();
	static void process(const Str& type);

	static void add(class KShortcut* ks);
	static void remove(class KShortcut* ks);
	static void modify(class KShortcut* ks,bool c,bool a,bool s,bool g,KeyCode k);
	static void modify(const Str& name,bool c,bool a,bool s,bool g,KeyCode k);

	static KShortcut* find(const Str& name);
	static KShortcut* find(bool c,bool a,bool s,bool g,KeyCode k);

};






