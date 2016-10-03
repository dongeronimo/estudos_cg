#include <glew.h>
#include <glut.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "shader.h"
#include "geometry.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <cstring>

using namespace std;
using namespace glm;
const GLfloat fov = 45.0f;
GLfloat screenWidth = 600, screenHeight = 400;

shared_ptr<Geometry> geo;

struct Triangulo
{
	GLfloat* vertexBufferData;
	GLushort* elementBufferData;
	GLfloat* vertexColorData;
	GLuint VertexArrayID;
	GLuint elementBuffer;
	GLuint vertexbuffer;
	GLuint vertexcolor;
};
Triangulo tri;

MyShader myshader;

void initResources()
{	
	//Flags do opengl
	glEnable(GL_DEPTH_TEST);
	//Shader
	myshader = CreateShaderProgram("//home//geronimo//programacao//estudos_cg//nehe_04b//vertexShader.vertexshader",
								   "/home//geronimo//programacao//estudos_cg//nehe_04b//fragmentShader.fragmentshader");
	geo = make_shared<Geometry>("//home//geronimo//programacao//estudos_cg//assets//cubo_correto.obj",
								myshader.vsId, myshader.fsId);
	std::cout<<"aqui";
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
	//A matrix de proje��o depende da largura e altura da tela.
	screenWidth = w;
	screenHeight = h;
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 0.2f, 0.2f, 1.0f);
    geo->Render();
    /*
	// Use our shader
	glUseProgram(myshader.programId);
	//A matriz MVP
	glm::mat4 projection = glm::perspective<GLfloat>(fov, screenWidth / screenHeight, 0.1f, 100.f);
	glm::mat4 view = glm::lookAt(glm::vec3(1, 1, -4), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 mvp = projection * view * model; // A multiplica��o � na ordem inversa do nome.
	//agora passa pro shader
	glUniformMatrix4fv(myshader.uniforms.at("mvp"), 1, GL_FALSE, &mvp[0][0]);
	//Eu sei que o nome do atributo dos v�rtices � vertexPosition_modelspace.
	//Usando o atributo da geometria.
	glEnableVertexAttribArray(myshader.attributes["vertexPosition_modelspace"]);
	glBindBuffer(GL_ARRAY_BUFFER, tri.vertexbuffer);
	glVertexAttribPointer(
		myshader.attributes["vertexPosition_modelspace"],                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	//Agora � o atributo da cor
	glEnableVertexAttribArray(myshader.attributes["vertexColor"]);
	glBindBuffer(GL_ARRAY_BUFFER, tri.vertexcolor);
	glVertexAttribPointer(
		myshader.attributes["vertexColor"],                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		4,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	//Agora � a array
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tri.elementBuffer);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void*)0);
	//GLenum err = glGetError();

	glDisableVertexAttribArray(0);
*/
	glFlush();
	glutSwapBuffers();
}

//Fun��o principal do programa.
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(screenWidth, screenHeight);
	glutCreateWindow("load");
	//tenta iniciar a glew
	GLenum glError = glewInit();
	if (glError != GLEW_OK)
	{
		const GLubyte* _err = glewGetErrorString(glError);
		std::string str((char*)_err);
		std::cerr << "Erro na inicializa��o da GLEW:" << str << std::endl;
		return EXIT_FAILURE;
	}
	initResources();
	//seta os callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMainLoop();

	glDeleteBuffers(1, &tri.vertexbuffer);
	glDeleteVertexArrays(1, &tri.VertexArrayID);
	glDeleteProgram(myshader.programId);

	return EXIT_SUCCESS;
}
