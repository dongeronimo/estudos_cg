#version 330 core
//As cores
layout(location = 0) in vec4 vertexColor;
// Input vertex data, different for all executions of this shader.
layout(location = 1) in vec3 vertexPosition_modelspace;
//as coordenadas de textura
layout(location = 2) in vec2 textureCoord;
//A matriz mvp
uniform mat4 mvp;
//cor sendo enviada pro fragment shader.
varying vec4 colorToFrag;
//texcoord sendo enviada pro fragment shader.
varying vec2 tcToFrag;
void main()
{
	gl_Position = mvp * vec4(vertexPosition_modelspace, 1);
	colorToFrag = vertexColor;
	tcToFrag = textureCoord;
}

