#include "Utils.h"
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