#version 430

out vec4 color;
uniform float outer[3];

void main(void){ 
	color = vec4(outer[0],outer[1],outer[2],1.0); 
}
