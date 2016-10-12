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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <cstring>
#include <Texture.h>
#include <Geometry.h>
#include <Utils.h>
#include <camera.h>

using namespace std;
using namespace glm;
const GLfloat fov = 45.0f;
GLfloat screenWidth = 600, screenHeight = 400;
//id da textura de teste, solto no escopo global no momento.
GLuint testeTex;

//shared_ptr<Geometry> geo;
unique_ptr<Camera> cam;

GLuint vsId, fsId;

shared_ptr<geometry::Geometry> geo;
#ifdef WIN32
const std::string vsPath = "C:\\programacao\\comp_grafica\\src\\nehe_05\\vertexShader.vertexshader";
const std::string fsPath = "C:\\programacao\\comp_grafica\\src\\nehe_05\\fragmentShader.fragmentshader";
const std::string objPath = "C:\\programacao\\comp_grafica\\src\\assets\\cubinho.obj";
#endif
#ifdef UNIX
const std::string vsPath = "//home//geronimo//programacao//estudos_cg//nehe_04b//vertexShader.vertexshader";
const std::string fsPath = "/home//geronimo//programacao//estudos_cg//nehe_04b//fragmentShader.fragmentshader";
const std::string objPath = "//home//geronimo//programacao//estudos_cg//assets//sphere.obj";
#endif
void initResources()
{	
	try
	{
		//Flags do opengl
		glEnable(GL_DEPTH_TEST);
		testeTex = texture::png_texture_load("C://programacao//comp_grafica//src//assets//t1.png", 0, 0);
		//Shader
		vsId = shader::Shader::MakeShader(GL_VERTEX_SHADER, ReadTextFile(vsPath));
		fsId = shader::Shader::MakeShader(GL_FRAGMENT_SHADER, ReadTextFile(fsPath));
		geo = make_shared<geometry::Geometry>(vsId, fsId);
		cam = std::make_unique<Camera>();
		cam->setEyePosition(1, 7, 5);
		cam->setFocusPosition(0,0,0);
		cam->setViewUp(0,1,0);
	}
	catch(std::runtime_error& err)
	{
		std::cout << err.what();
	}
}
void onTimer(int value)
{
	std::cout << __FUNCTION__ << std::endl;
	glutPostRedisplay();
}
void idle()
{
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    //TODO: A função de input que pega as setas
    //TODO: Mais opções de interação
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
	screenWidth = static_cast<GLfloat>(w);
	screenHeight = static_cast<GLfloat>(h);
}
static int contador = 0;
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 0.2f, 0.2f, 1.0f);

	//renderiza
	geo->textureId = testeTex;
    geo->Render(cam->getViewProjectionMatrix());
	contador++;
	std::cout << contador << std::endl;
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

//Fun��o principal do programa.
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(static_cast<int>(screenWidth), static_cast<int>(screenHeight));
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


	return EXIT_SUCCESS;
}
