#pragma once



class Clipboard:public Obj
{
	OBJ("Clipboard")
	
public:
	static Str text;
	static Str mouse_text;
	static Texture* tex;

	static void clear();
	static void kill();
};




