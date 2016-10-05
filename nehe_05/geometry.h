#ifndef __geometry_h
#define __geometry_h
#include <string>
#include <glew.h>
#include <gl.h>
#include <array>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include "shader.h"
class Geometry
{
private:
    MyShader shader;
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
	void Render(glm::mat4 viewProjection);
};
#endif