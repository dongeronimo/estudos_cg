//////Textos de apoio:
//http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/
//http://www.tomdalling.com/blog/modern-opengl/02-textures/
//http://www.tomdalling.com/blog/modern-opengl/03-matrices-depth-buffering-animation/
//http://www.tomdalling.com/blog/modern-opengl/04-cameras-vectors-and-input/
//http://www.tomdalling.com/blog/modern-opengl/05-model-assets-and-instances/
//Esse projeto de estudo vai cobrir muito chão:
//1)Texturas.
//2)Multiplos objetos e a questão da profundidade.
//3)Assets e instancing.
////Se isso for coberto, vamos pra luzes:
//http://www.tomdalling.com/blog/modern-opengl/06-diffuse-point-lighting/
//http://www.tomdalling.com/blog/modern-opengl/07-more-lighting-ambient-specular-attenuation-gamma/
//http://www.tomdalling.com/blog/modern-opengl/08-even-more-lighting-directional-lights-spotlights-multiple-lights/
////E por fim, blending
//http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-10-transparency/

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
#include "camera.h"
using namespace std;
using namespace glm;
const GLfloat fov = 45.0f;
GLfloat screenWidth = 600, screenHeight = 400;

shared_ptr<Geometry> geo;
unique_ptr<camera> cam;
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
	myshader = CreateShaderProgram("//home//geronimo//programacao//estudos_cg//nehe_05//vertexShader.vertexshader",
								   "/home//geronimo//programacao//estudos_cg//nehe_05//fragmentShader.fragmentshader");
	geo = make_shared<Geometry>("//home//geronimo//programacao//estudos_cg//assets//sphere.obj",
								myshader.vsId, myshader.fsId);
    cam = std::make_unique<camera>();
    cam->setEyePosition(0, 10, -10);
	cam->setFocusPosition(0,0,0);
	cam->setViewUp(0,1,0);
}

void idle()
{
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	if(key == 'a')
	{
		glm::vec3 p = cam->getFocusPosition();
		p[2] = p[2]+1;
		cam->setFocusPosition(p[0], p[1], p[2]);
	}
	if(key == 'd')
	{
		glm::vec3 p = cam->getFocusPosition();
		p[2] = p[2]-1;
		cam->setFocusPosition(p[0], p[1], p[2]);
	}
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
    geo->Render(cam->getViewProjectionMatrix());
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
	glutCreateWindow("texture");
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
