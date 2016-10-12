#include <glew.h>
#include <glfw3.h>
#include <stdexcept>
#include <iostream>
#include <Utils.h>
#include <Camera.h>
#include <memory>
#include <sstream>
#include <Shader.h>
#include <Utils.h>
#include <Texture.h>
#include <Geometry.h>
using namespace std;
//Objetos globais
//A camera;
Camera cam;

#ifdef WIN32
const std::string vsPath = "C:\\programacao\\comp_grafica\\src\\nehe_05b\\vertexShader.glsl";
const std::string fsPath = "C:\\programacao\\comp_grafica\\src\\nehe_05b\\fragmentShader.glsl";
const std::string objPath = "C:\\programacao\\comp_grafica\\src\\assets\\cubinho.obj";
const std::string texturePath = "C://programacao//comp_grafica//src//assets//t1.png";
#endif
#ifdef UNIX
const std::string vsPath = "//home//geronimo//programacao//estudos_cg//nehe_05b//vertexShader.glsl";
const std::string fsPath = "/home//geronimo//programacao//estudos_cg//nehe_05b//fragmentShader.glsl";
const std::string objPath = "//home//geronimo//programacao//estudos_cg//assets//sphere.obj";
#endif
//Callbacks
//Callback de erro.
void OnGLFWError(int errorCode, const char* description)
{
	stringstream s;
	s << "{ codigo : " << errorCode << ", descricao : '" << description << "'}";
	throw std::runtime_error(s.str());
}
//Callback de resize;
void OnResize(GLFWwindow* wnd, int width, int height)
{
	cam.SetScreenSize(width, height);
}
int main(int argc, char** argv)
{
	try
	{
		//A Janela
		GLFWwindow * window;

		//Callback de erro - Pega o código e a descrição e gera uma runtime_error.
		glfwSetErrorCallback(OnGLFWError);
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		window = glfwCreateWindow(640, 480, "ipsun", nullptr, nullptr);
		cam.SetScreenSize(640, 480);
		//glfwSetKeyCallback(window, KeyCallback);
		glfwMakeContextCurrent(window);
		glewExperimental = GL_TRUE;
		glewInit();
		glfwSwapInterval(1);
		long bigCount = 0;
		//setup de callbacks e outras coisas antes do inicio do loop
		glfwSetWindowSizeCallback(window, OnResize);
		//Carga dos pedaços de shader
		GLuint vsId = shader::Shader::MakeShader(GL_VERTEX_SHADER, ReadTextFile(vsPath));
		GLuint fsId = shader::Shader::MakeShader(GL_FRAGMENT_SHADER, ReadTextFile(fsPath));
		//Carrrga uma imagem como textura
		GLuint textureId = texture::png_texture_load(texturePath.c_str(), nullptr, nullptr);
		//Cria uma geometria
		shared_ptr<geometry::Geometry> geo = make_shared<geometry::Geometry>(vsId, fsId);
		//seta a camera
		cam.setEyePosition(1, 7, 5);
		cam.setFocusPosition(0, 0, 0);
		cam.setViewUp(0, 1, 0);
		//Tudo pronto, começa o ciclo
		while (!glfwWindowShouldClose(window))
		{
			//TO VIVO
			bigCount++;
			cout << bigCount << endl;
			//Renderiza a cena
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(1.0f, 0.2f, 0.2f, 1.0f);
			geo->textureId = textureId;
			geo->Render(cam.getViewProjectionMatrix());
			//Vai pro proximo
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		glfwDestroyWindow(window);
		glfwTerminate();
	}
	catch (std::runtime_error& err)
	{
		cout << err.what() << endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}