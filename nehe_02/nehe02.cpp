#include <GL\glew.h>
#include <GL\GL.h>
#include <GL\glut.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);

static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f,  1.0f, 0.0f,
};
GLuint VertexArrayID;
GLuint vertexbuffer;
GLuint programID;

void initResources()
{	
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("C://programacao//comp_grafica//src//nehe_02//SimpleVertexShader.vertexshader", 
		"C://programacao//comp_grafica//src//nehe_02//SimpleFragmentShader.fragmentshader");
}

void idle()
{
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{

}

void reshape(int w, int h)
{

}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.2, 0.2, 0.2, 1);
	// Use our shader
	glUseProgram(programID);
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle
	glDisableVertexAttribArray(0);

	glFlush();
	glutSwapBuffers();
}

//Função principal do programa.
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("NeHe02 - First Polygons");
	//tenta iniciar a glew
	GLenum glError = glewInit();
	if (glError != GLEW_OK)
	{
		const GLubyte* _err = glewGetErrorString(glError);
		std::string str((char*)_err);
		std::cerr << "Erro na inicialização da GLEW:" << str << std::endl;
		return EXIT_FAILURE;
	}
	initResources();
	//seta os callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMainLoop();

	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);

	return EXIT_SUCCESS;
}

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path) {

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}



	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}


	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

//#include <GL\glew.h>
//#include <GL\freeglut.h>
//#include <GL\GL.h>
//#include <iostream>
//#include <string>
//#include <vector>
//#include <exception>
//#include <assert.h>
//#include <string>
//#include "nehe02.h"
//using namespace std;
//
//
////COISAS RELATIVAS AOS SHADERS
//struct ShaderProgram
//{
//	GLuint vsId, fsId, programId;
//};
////Pega o log do shader.
//std::string  GetShaderInfoLog(GLuint object, PFNGLGETSHADERIVPROC glGet__iv, PFNGLGETSHADERINFOLOGPROC glGet__InfoLog)
//{
//	GLint log_length;
//	char *log;
//	glGet__iv(object, GL_INFO_LOG_LENGTH, &log_length);
//	log = static_cast<char*>(malloc(log_length));
//	glGet__InfoLog(object, log_length, nullptr, log);
//	std::string result(log);
//	free(log);
//	return result;
//}
////Cria um shader. Lança std::exception se houver algum problema.
//GLuint MakeShader(GLenum type, std::string source)
//{
//	const GLint length[] = { source.length() };
//	const GLchar *srcLn = source.c_str();
//
//	GLuint shader;
//	GLint shader_ok;
//	shader = glCreateShader(type);
//	glShaderSource(shader, 1, &srcLn, length);
//	glCompileShader(shader);
//	glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);
//	if (!shader_ok)
//	{
//		string problema = GetShaderInfoLog(shader, glGetShaderiv, glGetShaderInfoLog);
//		glDeleteShader(shader);
//		throw std::exception(problema.c_str());
//	}
//	else
//	{
//		return shader;
//	}
//}
////Cria o programa usando o vertex shader dado e o fragment shader dado.Lançastd::exception se der algum enguiço.
//static GLuint MakeProgram(GLuint vertex_shader, GLuint fragment_shader)
//{
//	GLint program_ok;
//	GLuint program = glCreateProgram();
//	glAttachShader(program, vertex_shader);
//	glAttachShader(program, fragment_shader);
//	glLinkProgram(program);
//	glGetProgramiv(program, GL_LINK_STATUS, &program_ok);
//	if (!program_ok) {
//		string problema = GetShaderInfoLog(program, glGetProgramiv, glGetProgramInfoLog);
//		glDeleteProgram(program);
//		throw std::exception(problema.c_str());
//	}
//	return program;
//}
//
////O triangulo
//struct Triangulo
//{
//	vector<GLfloat> triangleVertexData;
//	GLuint vertexArrayId;
//	GLuint vertexGeometryBufferId;
//	ShaderProgram shader;
//	void createVertexArray()
//	{
//		assert("Já tem dados?" && !triangleVertexData.size() == 0);
//		glGenVertexArrays(1, &vertexArrayId);
//		glBindVertexArray(vertexArrayId);
//		glGenBuffers(1, &vertexGeometryBufferId);
//		glBindBuffer(GL_ARRAY_BUFFER, vertexGeometryBufferId);
//		glBufferData(GL_ARRAY_BUFFER, 
//			sizeof(triangleVertexData.size() * sizeof(GLfloat)), triangleVertexData.data(), GL_STATIC_DRAW);
//		glBindVertexArray(0);
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//	}
//	void render()
//	{
//		glUseProgram(shader.programId);
//		const char* attribute_name = "coord2d";
//		GLint attribute_coord2d = glGetAttribLocation(shader.programId, attribute_name);
//		glEnableVertexAttribArray(attribute_coord2d);
//		glBindVertexArray(vertexArrayId);
//		glDrawElements(GL_TRIANGLES, 2, GL_FLOAT, 0);
//		//glBindBuffer(GL_ARRAY_BUFFER, vertexGeometryBufferId);
//		//glVertexAttribPointer(
//		//	0,
//		//	2,                  // size
//		//	GL_FLOAT,           // type
//		//	GL_FALSE,           // normalized?
//		//	0,                  // stride
//		//	(void*)0            // array buffer offset
//		//);
//		//glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle
//		glDisableVertexAttribArray(0);
//	}
//};
////DADOS DO PROGRAMA
//Triangulo meuTriangulo;
//
//void initResources()
//{
//	//Cria os shaders.
//	const char *vs_source =
//		//"#version 100\n"  // OpenGL ES 2.0
//		"#version 120\n"  // OpenGL 2.1
//		"attribute vec2 coord2d;                  "
//		"void main(void) {                        "
//		"  gl_Position = vec4(coord2d, 0.0, 1.0); "
//		"}";
//	const char *fs_source =
//		//"#version 100\n"  // OpenGL ES 2.0
//		"#version 120\n"  // OpenGL 2.1
//		"void main(void) {        "
//		"  gl_FragColor[0] = 0.0; "
//		"  gl_FragColor[1] = 0.0; "
//		"  gl_FragColor[2] = 1.0; "
//		"}";
//	GLuint vsId = MakeShader(GL_VERTEX_SHADER, vs_source);
//	GLuint fsId = MakeShader(GL_FRAGMENT_SHADER, fs_source);
//	GLuint programId = MakeProgram(vsId, fsId);
//	meuTriangulo.shader.fsId = fsId;
//	meuTriangulo.shader.vsId = vsId;
//	meuTriangulo.shader.programId = programId;
//	//A partir daqui o shader pro triangulo já está criado.
//	//inicialização dos vértices do triangulo
//	meuTriangulo.triangleVertexData.push_back(0.0);
//	meuTriangulo.triangleVertexData.push_back(0.8);
//	meuTriangulo.triangleVertexData.push_back(-0.8);
//	meuTriangulo.triangleVertexData.push_back(-0.8);
//	meuTriangulo.triangleVertexData.push_back(0.8);
//	meuTriangulo.triangleVertexData.push_back(-0.8);
//	//Agora crio o buffer dos vértices do triangulo
//	meuTriangulo.createVertexArray();
//}
//
//void idle()
//{
//	glutPostRedisplay();
//}
//
//void keyboard(unsigned char key, int x, int y)
//{
//
//}
//
//void reshape(int w, int h)
//{
//
//}
//
//void display(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT);
//	glClearColor(0.2, 0.2, 0.2, 1);
//	
//	meuTriangulo.render();
//	glFlush();
//	glutSwapBuffers();
//}
////Função principal do programa.
//int main(int argc, char *argv[])
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
//	glutInitWindowPosition(0, 0);
//	glutInitWindowSize(500, 500);
//	glutCreateWindow("NeHe02 - First Polygons");
//	//tenta iniciar a glew
//	GLenum glError = glewInit();
//	if (glError != GLEW_OK)
//	{
//		const GLubyte* _err = glewGetErrorString(glError);
//		std::string str((char*)_err);
//		std::cerr << "Erro na inicialização da GLEW:" << str << std::endl;
//		return EXIT_FAILURE;
//	}
//	initResources();
//	//seta os callbacks
//	glutDisplayFunc(display);
//	glutReshapeFunc(reshape);
//	glutKeyboardFunc(keyboard);
//	glutIdleFunc(idle);
//	glutMainLoop();
//
//	return EXIT_SUCCESS;
//}