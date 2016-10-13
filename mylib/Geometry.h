#ifndef __geo_h
#define __geo_h
#include <glew.h>
#include <string>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include "Shader.h"
#include <memory>
namespace geometry
{

	class Geometry
	{
	private:
		int quantidadeDeFaces;
		std::unique_ptr<shader::Shader> shaderProgram;
		GLuint vertexArrayId, vertexBufferId, elementBufferId;
	public:
		GLuint textureId;
		Geometry(GLuint vertexShaderId, GLuint fragmentShaderId);
		Geometry(std::string filepath, GLuint vertexShaderId, GLuint fragmentShaderId);
		~Geometry();
		void Render(glm::mat4 viewProjectionMatrix);
	};
}
#endif
