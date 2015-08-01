#pragma once


class Event
{
public:
	
	//constructor
	Event(class Element* sndr,const Str& cmd);

	//destructor
	~Event();



	//variables
	class Element* sender;
	Str command;

};
