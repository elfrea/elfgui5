#include <pix5.h>
#include "elfgui5.h"




//constructor
KShortcut::KShortcut()
{
	clear();
}



//constructor
KShortcut::KShortcut(bool c,bool a,bool s,bool g,KeyCode k)
{
	set(c,a,s,g,k);
}



//constructor
KShortcut::KShortcut(bool c,bool a,bool s,bool g,KeyCode k,ACTION act,bool enable)
{
	set("","",c,a,s,g,k,act,enable);
}



//constructor
KShortcut::KShortcut(const Str& kname,bool c,bool a,bool s,bool g,KeyCode k,ACTION act,bool enable)
{
	set(kname,"",c,a,s,g,k,act,enable);
}



//constructor
KShortcut::KShortcut(const Str& kname,const Str& ktype,bool c,bool a,bool s,bool g,KeyCode k,ACTION act,bool enable)
{
	set(kname,ktype,c,a,s,g,k,act,enable);
}



//***** CLEAR
void KShortcut::clear()
{
	Keyboard& kbd=Input::get_keyboard();

	enabled=false;
	name="";
	type="";

	ctrl=false;
	alt=false;
	shift=false;
	gui=false;

	key=kbd.get_key(KEY_NONE);
}



//***** SET
void KShortcut::set(bool c,bool a,bool s,bool g,KeyCode k)
{
	Keyboard& kbd=Input::get_keyboard();

	ctrl=c;
	alt=a;
	shift=s;
	gui=g;

	key=kbd.get_key(k);
}



//***** SET
void KShortcut::set(bool c,bool a,bool s,bool g,KeyCode k,ACTION act,bool enable)
{
	set("","",c,a,s,g,k,act,enable);
}



//***** SET
void KShortcut::set(const Str& kname,bool c,bool a,bool s,bool g,KeyCode k,ACTION act,bool enable)
{
	set(kname,"",c,a,s,g,k,act,enable);
}



//***** SET
void KShortcut::set(const Str& kname,const Str& ktype,bool c,bool a,bool s,bool g,KeyCode k,ACTION act,bool enable)
{
	Keyboard& kbd=Input::get_keyboard();

	enabled=enable;
	name=kname;
	type=ktype;
	
	ctrl=c;
	alt=a;
	shift=s;
	gui=g;

	key=kbd.get_key(k);

	action=act;
}



//***** COMPARE
bool KShortcut::compare(KShortcut* shortcut)
{
	return (ctrl==shortcut->ctrl && alt==shortcut->alt && shift==shortcut->shift && gui==shortcut->gui && key==shortcut->key);
}



//***** COMPARE
bool KShortcut::compare(bool c,bool a,bool s,bool g,KeyCode k)
{
	return (ctrl==c && alt==a && shift==s && gui==g && key==k);
}



//***** COMPARE NOW
bool KShortcut::compare_now()
{
	Keyboard& k=Input::get_keyboard();

	return (ctrl==k.ctrl() && alt==k.alt() && shift==k.shift() && gui==k.gui() && k.is_down(key.code));
}



//***** GET SHORT NAME
Str KShortcut::get_short_name()
{
	Str s="";

	if(ctrl)
		s+="C-";
	if(alt)
		s+="A-";
	if(shift)
		s+="S-";
	if(gui)
		s+="Gui-";
	
	s+=key.key_name;

	if(s=="")
		s="None";

	return s;
}



//***** GET FULL NAME
Str KShortcut::get_full_name()
{
	Str s="";

	if(ctrl)
		s+="Ctrl-";
	if(alt)
		s+="Alt-";
	if(shift)
		s+="Shift-";
	if(gui)
		s+="Gui-";
	
	s+=key.key_name;

	if(s=="")
		s="None";

	return s;
}



//***** EXECUTE
void KShortcut::execute()
{
	action();
}



//***** COMPARE AND EXECUTE
bool KShortcut::compare_and_execute(KShortcut* shortcut)
{
	if(compare(shortcut))
	{
		execute();
		return true;
	}

	return false;
}



//***** COMPARE AND EXECUTE
bool KShortcut::compare_and_execute(bool c,bool a,bool s,bool g,KeyCode k)
{
	if(compare(c,a,s,g,k))
	{
		execute();
		return true;
	}

	return false;
}



//***** COMPARE NOW AND EXECUTE
bool KShortcut::compare_now_and_execute()
{
	if(compare_now())
	{
		execute();
		return true;
	}

	return false;
}



//***** CLONE
KShortcut* KShortcut::clone()
{
	KShortcut* ks=new KShortcut(name,type,ctrl,alt,shift,gui,key.code,action,enabled);
	return ks;
}






