#ifndef __geometry_h
#define __geometry_h
#include <string>
#include <GL/glew.h>
#include <GL/GL.h>
#include <array>

class Geometry
{
private:
	size_t vertexBufferSize;
	size_t elementBufferSize;
	GLuint vertexArrayId;
	GLuint vertexBufferId;
	GLuint elementBufferId;
	GLfloat* vertexBuffer;
	GLuint* elementBuffer;
public:
	//Cria a partir de um arquivo .obj como os gerados pelo exportador do blender, com
	//os shaders dados.
	Geometry(std::string objFilePath, GLuint vertexShaderId, GLuint fragmentShaderId);
	~Geometry();
	void Translate(std::array<float, 3> pos);
	void Rotate(std::array<float, 9> angles);
	void Scale(std::array<float, 3> values);
	void Render();
};
#endif