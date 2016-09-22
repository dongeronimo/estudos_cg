#ifndef __geometry_h
#define __geometry_h
#include <string>
#include <GL/glew.h>
#include <GL/GL.h>
#include <array>

class Geometry
{
private:

public:
	//Cria a partir de um arquivo .obj como os gerados pelo exportador do blender, com
	//os shaders dados.
	Geometry(std::string objFilePath, GLuint vertexShaderId, GLuint fragmentShaderId);
	void Translate(std::array<float, 3> pos);
	void Rotate(std::array<float, 9> angles);
	void Scale(std::array<float, 3> values);
	void Render();
};
#endif