/*******************************************************************************\
*NAME: STUFF									*
*DESCRIPTION: Used for fast premaking of graphics				*
*FUNCTIONS: 									*
* -RFF(std::string) -- used for shader reading					*
* -GLFWKILL(GLFWwindow*) -- kills window					*
* -create_Sprogram -- assigns all stuff and creates vertex and fragment shaders	*
* -draw_array(GLFW window*, std::vector<_template*>) -- draws all the squares	*
*  respecting their colors							*
\*******************************************************************************/

#ifndef GLEWFW__H__
#define GLEWFW__H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <fstream>
#include "_template.hpp"

#define VERTPATH "./vertex.glsl"
#define FRAGPATH "./fragment.glsl"

#define NVAO 1 //i have no idea what is this

namespace ewfw{
	extern GLuint RP; //render program
	extern GLuint vao[NVAO]; //what is this
	extern std::vector<float> gl_cords;
	
	void init(GLFWwindow*&,std::string,unsigned int, unsigned int); //initialize window
	std::string RFF(std::string); //read files
	void GLFWKILL(GLFWwindow*); //kill window
	GLuint create_Sprogram(); //create shader program (needs to be fixed for glsl
	void draw_array(GLFWwindow*, std::vector<_template*>);
}

#endif
