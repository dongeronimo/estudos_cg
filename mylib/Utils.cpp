#include "Utils.h"
#include <glew.h>
#include <fstream>

std::string ReadTextFile(std::string path)
{
	std::string loadedText;
	std::ifstream loadTextStream(path, std::ios::in);
	if (loadTextStream.is_open()) {
		std::string Line = "";
		while (getline(loadTextStream, Line))
			loadedText += "\n" + Line;
		loadTextStream.close();
	}
	else
	{
		std::string err = path + " not found";
		throw std::runtime_error(err.c_str());
	}
	return loadedText;
}

void StartGlew()
{
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		const GLubyte* _err = glewGetErrorString(err);
		std::string str((char*)_err);
		throw std::runtime_error(str);
	}
}
