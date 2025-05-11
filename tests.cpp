#include "glfw-stuff.hpp"
#include "glfw-ctrl.hpp"
#include <cmath>
#include <string>
#include <random>
#include "menu.hpp"
#include "menu.cpp"

#define BELIEVER 0
#define ATEIST 1
#define AGNOSTIC 2

void init(GLFWwindow *& w, std::string p, unsigned int ww, unsigned int hh){
	ewfw::init(w,p,ww,hh); //# window initialized
	ctrl::init(w); //controls initialized
}

std::random_device rd; //global random device so not defined everytime
float randome(float a, float b){
	std::uniform_real_distribution<float> dist(a,b);
	std::mt19937 mt(rd());
	return dist(mt);
}// random [a; b]
int randomna(int a, int b){
	std::uniform_int_distribution<int> dist(a,b);
	std::mt19937 mt(rd());
	return dist(mt);
}// random [a; b]
float reservecolor[9]={1.0,0.0,0.0,0.0,0.0,1.0,0.0,1.0,0.0};

class obj:public _template{
	unsigned int pos, size, reserved=0, dog=randomna(0,300);
	float *ccr;
	char state=BELIEVER;//3 states 0, 1, 2
	float bel=randome(0,1), con=randome(0,1), cha=randome(0,1);
	float* color;
public:
	static float faith;
	obj(unsigned int pos, unsigned int size, float* ccr):pos(pos),ccr(ccr),size(size),color(new float[3]){
		for(int i=0;i<3;i++) color[i]=reservecolor[state*3+i];
	}
	void move(float x, float y){
		ccr[0]+=x; ccr[1]+=y;
		for(unsigned int i=pos; i<size; i+=4){ ewfw::gl_cords[i]+=x; ewfw::gl_cords[i+1]+=y; }
	}
	float* colr(){ return color; }
	void restate(){
		if(dog) { dog--; return; }
		switch(state){
			case BELIEVER: if(bel*faith>.5) return; state=(con>.5)? ATEIST:AGNOSTIC; break;
			case ATEIST: if(con*(1.0-bel*faith)>.5) return; state=(con*bel*faith>.5)? BELIEVER:AGNOSTIC; break;
			case AGNOSTIC: if(con>.5) return; state=(bel*faith>.5)? BELIEVER:AGNOSTIC ; break;
		}
		for(int i=0; i<3; i++) color[i]=reservecolor[state*3+i];
		dog=randomna(40,543);
	}
	void message(obj* jj){
		if(!jj||dog||state==jj->state) return;
		switch(jj->state){
			case BELIEVER: state=(jj->cha*bel*faith>.5)? BELIEVER:state;
			case ATEIST: state=(jj->cha*(1.0-bel*faith)*con>.5)? ATEIST:state;
			case AGNOSTIC: state=(jj->cha*(1.0-bel*faith)*(1.0-con)>.5)? AGNOSTIC:state;
		}
		for(int i=0; i<3; i++) color[i]=reservecolor[state*3+i];
		dog=randomna(40,543);
	}
	bool measure(obj* nn){
		return (sqrt(nn->ccr[0]*nn->ccr[0]+nn->ccr[1]*nn->ccr[1])-sqrt(ccr[0]*ccr[0]+ccr[1]*ccr[1])<0.01);
	}
}; //test object
float obj::faith=1.0;

namespace gtp{
	float con=.999;//starting layer
	obj* create_square(float* colors){
		int cur=ewfw::gl_cords.size();//x
		float *null=new float[2];
		null[0]=0; null[1]=0;
		ewfw::gl_cords.push_back(8.0/1920);
		ewfw::gl_cords.push_back(8.0/940);
		ewfw::gl_cords.push_back(con);
		ewfw::gl_cords.push_back(1.0); //right upper point
		ewfw::gl_cords.push_back(8.0/1920);
		ewfw::gl_cords.push_back(-8.0/940);
		ewfw::gl_cords.push_back(con);
		ewfw::gl_cords.push_back(1.0); //right lower point
		ewfw::gl_cords.push_back(-8.0/1920);
		ewfw::gl_cords.push_back(8.0/940);
		ewfw::gl_cords.push_back(con);ewfw::gl_cords.push_back(1.0); //left upper point
		ewfw::gl_cords.push_back(-8.0/1920);
		ewfw::gl_cords.push_back(-8.0/940);
		ewfw::gl_cords.push_back(con-=0.001);
		ewfw::gl_cords.push_back(1.0); //left lower point
		return new obj(cur,ewfw::gl_cords.size(),null); //passes pointers to object (fast)
	}
}//because

std::vector<_template*> phys; //obj container

GLFWwindow *window; //window pointer do not touch

void killprogram(){ ewfw::GLFWKILL(window); exit(0); } //test function
void makecube(){ 
	float* color=new float[3];
	color[0]=1.0;color[1]=1.0;color[2]=1.0;
	phys.push_back(gtp::create_square(color));
	delete [] color;
} //test function

//DO NOT TOUCH LINES SIGNED WITH "//#" I WARNED YOU
menu<1920, 940, &ctrl::x, &ctrl::y, &ewfw::gl_cords>* menu1;
void clk(bool d){ if(menu1) menu1->update(d); }
void menufuck(){ if(menu1) delete menu1; menu1=nullptr; ctrl::left_clk=nullptr;}
void tringa(){ obj::faith=(obj::faith)? 0.0:1.0; }
void summon_menu(){
	if(menu1) return;
	menu1=new menu<1920, 940, &ctrl::x, &ctrl::y, &ewfw::gl_cords>;
	menu1->add_button(500, 200, -.75,0.25, tringa);
	menu1->add_button(500, 200, -.75,0.0, menufuck);
	menu1->add_button(500, 200, -.75,-.25, makecube);
	menu1->add_button(500, 200, -.75,-.5, killprogram);
	for(int i=0; i<menu1->size(); i++) { phys.push_back((*menu1)[i]); dynamic_cast<button<1920,940,&ctrl::x, &ctrl::y, &ewfw::gl_cords>*>((*menu1)[i])->sync(phys); }
	ctrl::left_clk=clk;
}

void generate(){
	for(int i=0; i<30; i++)
		for(int j=0; j<30; j++){
			makecube();
			obj* cc = dynamic_cast<obj*>(phys[phys.size()-1]);
			if(cc) cc->move(1.0*i/30-0.5,1.0*j/20-0.6);
		}
}

int main(int arg, char **args){
	init(window, "title", 1920, 940); //#
	//generate();
	ctrl::ext=summon_menu; //testing ctrl escape key function
	summon_menu();
	generate();
	while(!glfwWindowShouldClose(window)){
		ewfw::draw_array(window, phys);
		for(unsigned int i=0; i<phys.size(); i++){
			obj* dd=dynamic_cast<obj*>(phys[i]);
			if(dd){
				//dd->move(((ctrl::pxr-ctrl::pxl)*(1.0+ctrl::shft))/100,((ctrl::pyu-ctrl::pyd)*(1.0+ctrl::shft))/100); //movement of rectangles
				dd->restate(); 
				dd->message(dynamic_cast<obj*>(phys[randomna(0,phys.size()-1)]));
			}
		}
	}ewfw::GLFWKILL(window); //# (it safely kills window)
}//main
