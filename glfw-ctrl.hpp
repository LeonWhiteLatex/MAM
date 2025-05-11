/*******************************************************************************\
*NAME: CTRL									*
*DESCRIPTION: Functions for managing control within and outside the game.	*
*FUNCTIONS:									*
* -ctrl::init() -- used for initializing (preprocessor)				*
* -ctrl::getkey(forget about parameters) -- used for glfwSetKeyCallback second	*
*  parameter									*
* -ctrl::NULkey(forgat about parameters) -- used to nulify key entering		*
* -ctrl::cursor(forget about parameters) -- used for glfwSetCursorCallback	*
* -ctrl::getclk(forget about parameters) -- used for glfwSetMouseCallback	*
* -ctrl::NULcur(forget about parameters) -- used to nulify effect of mouse	*
* -ctrl::NULclk(forget about parameters) -- used to nulify effects of clicks	*
* -ctrl::setnew(int id, int key) -- sets new bind				*
* -ctrl::reset(int id) -- sets default bind					*
*NOTE: Do not change anything in the files themselves, the controls are already *
* set! For additional settings use function pointers!				*
\*******************************************************************************/

#ifndef GLFW_CTRL_H__
#define GLFW_CTRL_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <filesystem>
#include <fstream>

namespace ctrl{
	extern int *ctr[11], arr[400]; //used controls
	extern float x, y; //mouse cords
	extern float pxl, pxr, pyu, pyd, shft; //movement cords
	extern void (*jmp)(); //jump function
	extern void (*ext)(); //exit function
	extern void (*dsh)(); //dash function
	extern void (*swc)(bool); //switch function
	extern void (*left_clk)(bool); //left click

	void init(GLFWwindow*&); //initialization of ctrl
	void reset(int); //reset to default
	void setnew(int, int); //set new bind

	void getkey(GLFWwindow*, int, int, int, int); //key pressed
	void NULkey(GLFWwindow*,int,int,int,int); //no recording
	void cursor(GLFWwindow*, double, double); //mouse cords 
	void getclk(GLFWwindow*, int, int, int); //mouse clicked
	void NULcur(GLFWwindow*, double, double); //no cords
	void NULclk(GLFWwindow*, int, int, int); //no clicks
}

#endif
