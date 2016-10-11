#ifndef __geometry__old_h
#define __geometry__old_h
#include <string>
#include <glew.h>
//#include <gl.h>
#include <array>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include <Shader.h>
#include <vector>
class Geometry
{
private:
	shader::Shader *shaderProgram;
    //shader::Shader 
	size_t vertexBufferSize;
	GLuint vertexArrayId;
	GLuint vertexBufferId;
	GLuint elementBufferId;
	GLfloat* vertexBuffer;
	GLuint* elementBuffer;

    GLfloat* textureCoordinateBuffer;
	GLuint textureCoordinateId;
	size_t textureBufferSize;
	void SetShader(GLuint vertexShaderId, GLuint fragmentShaderId) ;
public:
	//Cria a geometria manualmente, pra experiências, pra que eu não tenha que me
	//importar com como o arquivo traz os dados que eu quero.
	Geometry(GLuint vertexShaderId, GLuint fragmentShaderId);
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