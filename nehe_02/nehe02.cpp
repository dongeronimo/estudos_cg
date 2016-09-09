#include <iostream>
#include <string>
#include <GL\glew.h>
#include <GL\freeglut.h>
void idle()
{

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
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.1, 0.0, 0.0);
	glVertex3f(0.1, 0.1, 0.0);
	glVertex3f(0.0, 0.1, 0.0);
	glEnd();
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
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMainLoop();

	return EXIT_SUCCESS;
}