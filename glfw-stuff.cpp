/*******************************\
*NAME: STUFF			*
*INSHORT: graphics manager	*
\*******************************/

#include "glfw-stuff.hpp"

//DO NOT TOUCH LINES SIGNED WITH "//#" I WARNED YOU
//SIGNED LINES ARE THE ONES RESPONSIBLE FOR GRAPHICS
//THEY ARE INTENDED TO BE LIKE THIS SO DONT MODIFY
//THEM

namespace ewfw{
	GLuint RP;
	GLuint vao[NVAO];
	std::vector<float> gl_cords;
	
	void init(GLFWwindow*& w, std::string tutle, unsigned int ww, unsigned int hh){
		if(!glfwInit()) exit(1); //#
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4); //#
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3); //#
		w = glfwCreateWindow(ww,hh,tutle.c_str(), NULL, NULL); //#
		
		glfwMakeContextCurrent(w); //#
		if(glewInit()!=GLEW_OK) exit(2); //#
		glfwSwapInterval(1); //#
		
		RP = create_Sprogram(); //#
		glGenVertexArrays(NVAO,vao); //#
		glBindVertexArray(vao[0]); //#
		
		glEnable(GL_DEPTH_TEST); //depth enabled
		glDepthFunc(GL_LESS); //depth set
	}
	
	std::string RFF(std::string file_path){
		std::string conts="", line;
		std::ifstream file(file_path);
		while(!file.eof()){
			std::getline(file,line); conts.append(line).append("\n");
		}file.close(); return conts;
	}//file reader

	void GLFWKILL(GLFWwindow* window){
		//std::system("if test -f \"./sdf\"; then ./sdf; fi");
		glfwDestroyWindow(window); //#
		glfwTerminate(); //#
	}//killer function

	GLuint create_Sprogram(){
		std::string frgmnt = RFF(FRAGPATH); //if you can fix this file path feel free to do it
		std::string vertex = RFF(VERTPATH); //same goes here
		
		const char* vert=vertex.c_str(); //#
		const char* frag=frgmnt.c_str(); //#
		
		GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER); //#
		glShaderSource(vertex_shader, 1, &vert, NULL); //#
		glCompileShader(vertex_shader); //#
		
		GLuint fragmentation = glCreateShader(GL_FRAGMENT_SHADER); //#
		glShaderSource(fragmentation, 1, &frag, NULL); //#
		glCompileShader(fragmentation); //#
		
		GLuint verfragprog = glCreateProgram(); //#
		glAttachShader(verfragprog, vertex_shader); //#
		glAttachShader(verfragprog, fragmentation); //#
		glLinkProgram(verfragprog); //#
		
		return verfragprog; //#
	}
	
	void draw_array(GLFWwindow* window, std::vector<_template*> phys){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //# clears all shit
		glClearColor(0.0,0.0,0.0,1.0); //# updates color to black
		
		glUseProgram(ewfw::RP); //#
		
		glUniform1fv(glGetUniformLocation(ewfw::RP, "depar"), gl_cords.size(), &gl_cords[0]); //pushes vertexes containments into the vertex shader
		//glUniform1fv(glGetUniformLocation(RP, "outer"), 3, color);
		for(unsigned int i=0; i<phys.size(); i++){
			if(!phys[i]) continue;
			glUniform1fv(glGetUniformLocation(ewfw::RP, "outer"), 3, phys[i]->colr()); //pushes colors into the fragment shader
			glDrawArrays(GL_TRIANGLE_STRIP,i*4,4); //draws rectanges
		}
		glfwSwapBuffers(window); //#
		glfwPollEvents(); //#
	}

}
