#version 330 core
//Dado vindo do fragment shader.
varying vec4 colorToFrag;
//A textura
uniform sampler2D mytexture;
//a coordenada de textura
varying vec2 tcToFrag;
// Ouput data
out vec4 color;

void main()
{
    vec4 _color = texture2D(mytexture, tcToFrag);
    color = _color;
}