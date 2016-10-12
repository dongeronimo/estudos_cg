#include <glew.h>
#include <glfw3.h>
#include <stdexcept>
#include <iostream>
#include <Utils.h>
#include <Camera.h>
#include <memory>
using namespace std;
//Objetos globais
Camera cam;
void ErrorCallback(int error, const char* description)
{
	
}
int main(int argc, char** argv)
{

	GLFWwindow * window;
	glfwSetErrorCallback(ErrorCallback);
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	window = glfwCreateWindow(640, 480, "ipsun", nullptr, nullptr);
	//glfwSetKeyCallback(window, KeyCallback);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();
	glfwSwapInterval(1);
	long bigCount = 0;
	while (!glfwWindowShouldClose(window))
	{
		bigCount++;
		cout << bigCount << endl;
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return EXIT_SUCCESS;
}