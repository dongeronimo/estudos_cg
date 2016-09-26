#include "geometry.h"
#include <fstream>	
#include <exception>
#include <string>
#include <vector>
#include <array>
#include <regex>
#include <iostream>
#include "utils.h"
using namespace std;
Geometry::Geometry(std::string objFilePath, GLuint vertexShaderId, GLuint fragmentShaderId)
{
	//abrir o arquivo
	string currentLine = "";
	ifstream myfile(objFilePath);
	if (myfile.is_open())
	{
		string str;
		vector<array<float, 3>> vertexes;
		vector<array<unsigned int, 3>> faces;
		while (getline(myfile, str))
		{
			//particiona a linha
			//ve qual é o tipo do dado e põe no lugar apropriado
			vector<string> pedacos = SplitString(str, "\\s+");
			//se a 1a parte for "v" é vertice, se for "f" é face.
			if (pedacos[0] == "v")
			{
				size_t szx = pedacos[1].size();
				size_t szy = pedacos[2].size();
				size_t szz = pedacos[3].size();
				array<float, 3> vert;
				vert[0] = std::stof(pedacos[1], &szx);
				vert[0] = std::stof(pedacos[2], &szx);
				vert[0] = std::stof(pedacos[3], &szx);
				vertexes.push_back(vert);
			}
			//se a 2a parte for "f" é face, da forma "indice//face"
			if (pedacos[0] == "f")
			{
				// 1//1 2//1 3//1 4//1, tem que picotar mais.
				// Para cada pedaço em f, dividir em antes das barras e depois das barras. Pegar o que está antes das barras e
				//por no vetor de indices.
				// O numero de vértices será sempre 3. Se vier diferente lança exceção pq só tratarei triangulos.
				if (pedacos.size() > 4)
				{
					string err = "só entende triangulos";
					throw exception(err.c_str());
				}
				vector<string> indice01 = SplitString(pedacos[1], "//");
				vector<string> indice02 = SplitString(pedacos[2], "//");
				vector<string> indice03 = SplitString(pedacos[3], "//"); 
				array<unsigned int, 3 > face;
				size_t indice01sz = indice01[0].size();
				face[0] = std::stoi(indice01[0], &indice01sz);
				size_t indice02sz = indice02[0].size();
				face[1] = std::stoi(indice02[0], &indice02sz);
				size_t indice03sz = indice03[0].size();
				face[2] = std::stoi(indice03[0], &indice03sz);
				faces.push_back(face);
			}
		}
		//a partir daqui já tenho o que eu quero: a lista de vértices e a lista de faces.
		//Posso, portanto, alocar a estrutura permanente para eles.

	}
	else
	{
		string err = "arquivo não encontrado " + objFilePath;
		throw std::exception(err.c_str());
	}
}

void Geometry::Translate(std::array<float, 3> pos)
{
}

void Geometry::Rotate(std::array<float, 9> angles)
{
}

void Geometry::Scale(std::array<float, 3> values)
{
}

void Geometry::Render()
{
}
