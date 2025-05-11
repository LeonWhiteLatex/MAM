#version 430

uniform float depar[4000*4];

void main(void){
	gl_Position = vec4(depar[gl_VertexID*4],depar[1+gl_VertexID*4],depar[2+gl_VertexID*4],depar[3+gl_VertexID*4]);
}
