#pragma once



class Anchor
{
public:

	//constructor
	Anchor(bool t=false,int ty=0,bool b=false,int by=0,bool l=false,int lx=0,bool r=false,int rx=0);

	//variables
	bool top;
	bool bottom;
	bool left;
	bool right;

	int top_y;
	int bottom_y;
	int left_x;
	int right_x;


	//functions
	void set(bool t,int ty,bool b,int by,bool l,int lx,bool r,int rx);

	bool is_none();
	bool is_all();


};



