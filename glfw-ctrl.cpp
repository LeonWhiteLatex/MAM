/*******************************\
*NAME: CTRL			*
*INSHORT: controls manager	*
\*******************************/

#include "glfw-ctrl.hpp"
//#include "menu.hpp" //for button interactions
namespace ctrl{
	constexpr int ref[11]={
		GLFW_KEY_W, //go up
		GLFW_KEY_A, //go left
		GLFW_KEY_S, //go down
		GLFW_KEY_D, //go right
		GLFW_KEY_SPACE, //jump
		GLFW_KEY_LEFT_SHIFT, //dash
		GLFW_KEY_LEFT, //switch to left
		GLFW_KEY_RIGHT, //switch to right
		GLFW_KEY_E, //act
		GLFW_KEY_ESCAPE, //esc
		GLFW_KEY_TAB //menu
	}; //default controls
	int *ctr[11], arr[400]; //used controls
	float x, y; //mouse cords
	float pxl=0.0, pxr=0.0, pyu=0.0, pyd=0.0, shft=0.0; //movement cords
	void (*jmp)()=nullptr; //jump function
	void (*ext)()=nullptr; //exit function
	void (*dsh)()=nullptr; //dash function
	void (*swc)(bool)=nullptr; //switch function
	void (*left_clk)(bool)=nullptr; //left click function

	void init(GLFWwindow*& w){
		for(int i=0; i<400; i++) arr[i]=-1; //assignes all controls to -1
		if(!std::filesystem::exists("./config.bin")){ //if no config creates one
			std::ofstream cfg("./config.bin",std::ios::binary);
			for(int i=0; i<11; i++) arr[ref[i]]=i; //assigns all controls
			for(int i=0; i<400; i++) 
				cfg.write(reinterpret_cast<const char*>(&arr[i]), sizeof(arr[i]));//writes them down
			cfg.close(); //dont touch this ;3
		}std::ifstream cfg("./config.bin",std::ios::binary); //reading
		for(int i=0; i<400; i++) {
			cfg.read(reinterpret_cast<char*>(&arr[i]), sizeof(arr[i])); //reads modified controls
			if(arr[i]>-1) ctr[arr[i]]=&arr[i]; //assigns reference to controls
		}cfg.close(); //dont touch this ;3
		
		glfwSetKeyCallback(w, getkey); //sets keyboard callback function
		glfwSetCursorPosCallback(w, cursor); //sets cursor position callback function
		glfwSetMouseButtonCallback(w, getclk); //sets click callback
		
	}

	void cursor(GLFWwindow* w, double xi, double yi){
		x=-1.0+1.0*xi/1920*2; y=1.0-1.0*yi/940*2; //getting cords might to replace 1920 and 940 with WIDTH and HEIGHT
		if(left_clk) left_clk(false);
	}

	void getclk(GLFWwindow* w, int but, int act, int mods){
		if(act==GLFW_PRESS) if(left_clk) left_clk(true); // getting any click
	}

	void reset(int id){
		if(id<0||id>10) return; //yes its important
		setnew(id,ref[id]); //lmao
	}

	void setnew(int id, int key){
		if(id<0||id>10||key<0||key>399) return; //this is important
		*ctr[id]=-1; //deassigning current bind
		if(arr[key]>-1) ctr[arr[key]]=ctr[id]; //deassigning chosen key
		arr[key]=id; //assigning key
		ctr[id]=&arr[key]; //assigning bind
	}

	void NULkey(GLFWwindow*,int,int,int,int){}
	void NULcur(GLFWwindow*, double, double){}
	void NULclk(GLFWwindow*, int, int, int){}
	
	char sec[11]={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }; //for goto
	
	void getkey(GLFWwindow* w, int key, int sc, int act, int mods){
		if(arr[key]<0) return; //will react to control and if theres some it will goto
		switch(sec[arr[key]]){ //like this
			case 0: if(act==GLFW_PRESS){ pyu=1.0; }
				else if(act==GLFW_RELEASE) { pyu=0.0; }
				break; //def W
			case 1: if(act==GLFW_PRESS){ pxl=1.0; }
				else if(act==GLFW_RELEASE) { pxl=0.0; }
				break; //def A
			case 2: if(act==GLFW_PRESS){ pyd=1.0; }
				else if(act==GLFW_RELEASE) { pyd=0.0; }
				break; //def S
			case 3: if(act==GLFW_PRESS){ pxr=1.0; }
				else if(act==GLFW_RELEASE) { pxr=0.0; }
				break; //def D
			case 4: if(act==GLFW_PRESS && jmp){ jmp(); } break; //def SPACE
			case 5: if(dsh) { if(act==GLFW_PRESS) dsh(); }
				else if(act==GLFW_PRESS) shft=1.0;
				else if(act==GLFW_RELEASE) shft=0.0;
				break; //def LEFT SHIFT
			case 6: if(act==GLFW_PRESS && swc) swc(false); break; //def LEFT
			case 7: if(act==GLFW_PRESS && swc) swc(true); break; //def RIGHT
			case 8: //action unfinihed
			break; //def E
			case 9: if(act==GLFW_PRESS && ext) ext(); break; //def ESCAPE
			case 10: //menu unfinished
			break; //def TAB
			default: break;
		}
	}
}
