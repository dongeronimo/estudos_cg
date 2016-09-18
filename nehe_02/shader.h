#ifndef __shader_h
#define __shader_h
#include <GL/glew.h>
#include <GL/GL.h>
#include <map>
#include <string>
using namespace std;

struct MyShader
{
	GLuint programId;
	GLuint vsId;
	GLuint fsId;
	map<string, GLuint> attributes;
	map<string, GLuint> uniforms;
};



std::string ReadShaderFile(std::string path);
//Extrai a lista de atributos e uniformes do programa dado. Os pares nome/localizaçào no shader são retornados
//nos mapas passados como parâmetro.
void introspectProgram(GLuint programId, map<string, GLuint> &attributes, map<string, GLuint> &uniforms);
//Gera o log do shader. A responsabilidade de deletar a string alocada é do invocador da função.
string GetShaderInfoLog(GLuint object, PFNGLGETSHADERIVPROC glGet__iv, PFNGLGETSHADERINFOLOGPROC glGet__InfoLog);
GLuint MakeShader(GLenum type, std::string source);
GLuint MakeProgram(GLuint vertex_shader, GLuint fragment_shader);
//Cria a estrutura a partirdos paths dos programas.
MyShader CreateShaderProgram(std::string vsPath, std::string fsPath);
#endif