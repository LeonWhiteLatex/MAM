#if __has_include("menu.hpp")
#include "menu.hpp"
#include <iostream>

template<unsigned int wid, unsigned int hei, float* CTX, float* CTY, std::vector<float>* cords>
void menu<wid,hei,CTX,CTY,cords>::add_button(unsigned int width, unsigned int height, float cx, float cy, void(*ex)()){
	butts.push_back(button<wid,hei,CTX,CTY,cords>(width,height,cx,cy,ex)); //button creation
}//creates button (requires its width and height in pixels, central position x and y, and function that will be activated upon pressing)

template<unsigned int wid, unsigned int hei, float* CTX, float* CTY, std::vector<float>* cords>
void menu<wid,hei,CTX,CTY,cords>::add_button(float cx, float cy, void(*ex)()){
	butts.push_back(button<wid,hei,CTX,CTY,cords>(cx,cy,ex));
}//same creation but default size

template<unsigned int wid, unsigned int hei, float* CTX, float* CTY, std::vector<float>* cords>
void menu<wid,hei,CTX,CTY,cords>::update(bool press){
	std::vector<button<wid,hei,CTX,CTY,cords>*> active;
	for(auto &i:butts){
		i.set_color(false);
		if(i.inside()){
			active.push_back(&i);
			i.set_color(true);
		}
	}
	if(press){
		for(auto i:active) i->exe();
	}
}//detects if button is entered+pressed

template<unsigned int wid, unsigned int hei, float* CTX, float* CTY, std::vector<float>* cords>
_template* menu<wid,hei,CTX,CTY,cords>::operator[](unsigned int b){ return &butts[(butts.size()+b%butts.size())%butts.size()]; } //for color

template<unsigned int wid, unsigned int hei, float* CTX, float* CTY, std::vector<float>* cords>
unsigned int menu<wid,hei,CTX,CTY,cords>::size(){ return butts.size(); } //return amount of buttons

template<unsigned int wid, unsigned int hei, float* CTX, float* CTY, std::vector<float>* cords>
button<wid,hei,CTX,CTY,cords>::button(unsigned int width, unsigned int height, float cx, float cy, void(*ex)()):start(cords->size()),execute(ex){
	center[0]=cx; center[1]=cy;
	cords->push_back(cx+1.0*width/wid/2); cords->push_back(cy+1.0*height/hei/2); cords->push_back(-1.0); cords->push_back(1.0);
	cords->push_back(cx+1.0*width/wid/2); cords->push_back(cy-1.0*height/hei/2); cords->push_back(-1.0); cords->push_back(1.0);
	cords->push_back(cx-1.0*width/wid/2); cords->push_back(cy+1.0*height/hei/2); cords->push_back(-1.0); cords->push_back(1.0);
	cords->push_back(cx-1.0*width/wid/2); cords->push_back(cy-1.0*height/hei/2); cords->push_back(-1.0); cords->push_back(1.0);
	end=cords->size();
	for(int i=0; i<3; i++){ ncolor[i]=0.0; acolor[i]=0.0; }
	ncolor[0]=1.0;
	acolor[1]=1.0;
}//default constructor creation (width height x y and function)

template<unsigned int wid, unsigned int hei, float* CTX, float* CTY, std::vector<float>* cords>
button<wid,hei,CTX,CTY,cords>::button(float cx, float cy, void(*ex)()):button(500,200,cx,cy,ex){} //constructor with default size

template<unsigned int wid, unsigned int hei, float* CTX, float* CTY, std::vector<float>* cords>
bool button<wid,hei,CTX,CTY,cords>::inside(){
	if((*cords)[start]>*CTX && (*cords)[start+1]>*CTY && (*cords)[end-4]<*CTX && (*cords)[end-3]<*CTY) return true;
	return false; //if never entered will false
}//if cursor is inside

template<unsigned int wid, unsigned int hei, float* CTX, float* CTY, std::vector<float>* cords>
void button<wid,hei,CTX,CTY,cords>::exe(){
	if(execute) execute(); //if theres any function it will run in
}//function activation

template<unsigned int wid, unsigned int hei, float* CTX, float* CTY, std::vector<float>* cords>
void button<wid,hei,CTX,CTY,cords>::set_color(bool fs){
	current=fs;//currently uses 2 colors
}//color switcher

template<unsigned int wid, unsigned int hei, float* CTX, float* CTY, std::vector<float>* cords>
float* button<wid,hei,CTX,CTY,cords>::colr(){
	return (current)? acolor:ncolor; //return color
}//currently this

template<unsigned int wid, unsigned int hei, float* CTX, float* CTY, std::vector<float>* cords>
void button<wid,hei,CTX,CTY,cords>::sync(std::vector<_template*> &a){
	refery=&a; mypos=a.size()-1;
}

template<unsigned int wid, unsigned int hei, float* CTX, float* CTY, std::vector<float>* cords>
void button<wid,hei,CTX,CTY,cords>::clear(){
	(*refery)[mypos]=nullptr;
	for(int i=start; i<end; i++) (*cords)[i]=0.0/0.0;
	delete[]ncolor; delete[]acolor;
}

template<unsigned int wid, unsigned int hei, float* CTX, float* CTY, std::vector<float>* cords>
menu<wid,hei,CTX,CTY,cords>::~menu(){
	for(auto i:butts) i.clear();
}

#else
#warning menu.hpp is missing
#endif
