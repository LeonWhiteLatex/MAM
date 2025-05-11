/*******************************************************************************\
*NAME: Menu									*
*DESCRIPTION: All the buttons and stuff for mouse interactions.			*
*CLASSES:									*
* ~button -- just 2d hitbox for mouse, requires window's width and height, mouse*
*  position pointers (x and y), and vector for vertices				*
*	METHODS:								*
*	 -constructor(uint width, uint height, float x, float y, 		*
*			void (*function)()) -- constructor for button		*
*	 -constructor(uint x, uint y, void(*function)()) -- default size	*
*	  constructor								*
*	 -inside() -- returns true if cursor is inside the box			*
*	 -exe() -- executes button function if there is one			*
*	 -set_color(bool switcher) -- switches for second color			*
*	 -colr() -- returns current color					*
* ~menu -- 2d menu for buttons and stuff for mouse				*
*	METHODS:								*
*	 -add_button(uint,uint,float,float,void(*)()) -- refers to button	*
*	  constructors								*
*	 -add_button(float,float,void(*)()) -- refers to button constructors	*
*	 -update(bool click) -- is used for menu to button interations, if true	*
*	  executes button, else just checks if its inside			*
*	 -operator[](uint pos) -- returns button				*
*	 -size() -- returns amount of buttons					*
*										*
\*******************************************************************************/
#ifndef MENU__H__
#define MENU__H__
#include <vector>
#include "_template.hpp"

template <unsigned int wid, unsigned int hei, float* CTX, float* CTY, std::vector<float>* cords>
class button:public _template{
	unsigned int start, end, mypos;
	float center[2], *ncolor=new float[3], *acolor=new float[3];
	bool current=false;
	void (*execute)();
	std::vector<_template*>* refery;
public:
	button(unsigned int,unsigned int,float,float,void(*)());
	button(float,float,void(*)());
	
	bool inside();
	void exe();
	
	void set_color(bool);
	float* colr();
	
	void clear();
	void sync(std::vector<_template*>&);
};

template <unsigned int wid, unsigned int hei, float* CTX, float* CTY, std::vector<float>* cords>
class menu{
	std::vector<button<wid,hei,CTX,CTY,cords>> butts;
public:
	void add_button(unsigned int, unsigned int, float, float,void(*)());
	void add_button(float, float,void(*)());
	
	void update(bool);
	_template* operator[](unsigned int);
	unsigned int size();
	
	~menu();
};

#endif
