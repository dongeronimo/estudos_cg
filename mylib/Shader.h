#ifndef __shader_FOO_BAR_h
#define __shader_FOO_BAR_h
#include <glew.h>
#include <string>
#include <map>
//Coisas relativas aos shaders.
namespace shader {
	class Shader
	{
	private:
		std::map<std::string, GLuint> atributos, uniforms;
		GLuint programId;
		GLuint vertexShaderId;
		GLuint fragmentShaderId;
		//Gera a lista de atributos e uniformes pro programa.
		void Introspect();
		//Criador interno de shader a partir de um código fonte.
		GLuint MakeShader(GLenum type, std::string source);
		//Log do shader
		std::string GetShaderInfoLog(GLuint object, PFNGLGETSHADERIVPROC glGet__iv, PFNGLGETSHADERINFOLOGPROC glGet__InfoLog);
		//Linka as partes e cria o programa completo
		GLuint MakeProgram(GLuint vertex_shader, GLuint fragment_shader);
	public:
		GLuint GetUniform(std::string nome);
		GLuint GetAttribute(std::string nome);
		//Cria um shader a partir do código fonte dado.
		Shader(std::string vsCode, std::string fsCode);
		//Cria um shader a partir dos ids dados.
		Shader(GLuint vsId, GLuint fsId);
		//Destrutor.
		~Shader();
		void StartUsing();
		void StopUsing();
	};
}
#endif
