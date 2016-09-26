#include "geometry.h"
#include <fstream>	
#include <exception>
#include <string>
#include <vector>
#include <array>
#include <regex>
#include <iostream>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include "utils.h"
using namespace std;
Geometry::Geometry(std::string objFilePath, GLuint vertexShaderId, GLuint fragmentShaderId)
{
	// Create an instance of the Importer class
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(objFilePath, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
	if (!scene) assert("não conseguiu carregar o .Obj" && false);
	//Numero de faces
	const unsigned int numFaces = scene->mMeshes[0]->mNumFaces;
	aiFace* faces = scene->mMeshes[0]->mFaces;
	//Numero de vertices
	const unsigned int numVerts = scene->mMeshes[0]->mNumVertices;
	aiVector3D* verts = scene->mMeshes[0]->mVertices;
	//Cria o VAO
	glGenVertexArrays(1, &vertexArrayId);
	glBindVertexArray(vertexArrayId);
	//Cria o buffer de indices
	elementBuffer = new GLuint[3 * numFaces];
	for (int i = 0; i < numFaces; i++)
	{
		if (faces[i].mNumIndices != 3) assert("Todas as faces tem que ser triangulos" && false);
		elementBuffer[i * 3] = faces[i].mIndices[0];
		elementBuffer[i * 3 + 1] = faces[i].mIndices[0 + 1];
		elementBuffer[i * 3 + 2] = faces[i].mIndices[0 + 2];
	}
	glGenBuffers(1, &elementBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * numFaces * sizeof(GLuint), elementBuffer, GL_STATIC_DRAW);
	//Cria o buffer de vertices
	vertexBuffer = new GLfloat[3 * numVerts];
	for (int i = 0; i < numVerts; i++)
	{
		vertexBuffer[i * 3] = verts[i][0];
		vertexBuffer[i * 3 + 1] = verts[i][0 + 1];
		vertexBuffer[i * 3 + 2] = verts[i][0 + 2];
	}
	glGenBuffers(1, &vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, numVerts * 3 * sizeof(GLfloat), const_cast<GLfloat*>(vertexBuffer), GL_STATIC_DRAW);
	//Pronto.
	glBindVertexArray(0);
	delete scene;
	////abrir o arquivo
	//string currentLine = "";
	//ifstream myfile(objFilePath);
	//if (myfile.is_open())
	//{
	//	assimp::im
	//	string str;
	//	vector<array<float, 3>> vertexes;
	//	vector<array<unsigned int, 3>> faces;
	//	while (getline(myfile, str))
	//	{
	//		//particiona a linha
	//		//ve qual é o tipo do dado e põe no lugar apropriado
	//		vector<string> pedacos = SplitString(str, "\\s+");
	//		//se a 1a parte for "v" é vertice, se for "f" é face.
	//		if (pedacos[0] == "v")
	//		{
	//			size_t szx = pedacos[1].size();
	//			size_t szy = pedacos[2].size();
	//			size_t szz = pedacos[3].size();
	//			array<float, 3> vert;
	//			vert[0] = std::stof(pedacos[1], &szx);
	//			vert[0] = std::stof(pedacos[2], &szx);
	//			vert[0] = std::stof(pedacos[3], &szx);
	//			vertexes.push_back(vert);
	//		}
	//		//se a 2a parte for "f" é face, da forma "indice//face"
	//		if (pedacos[0] == "f")
	//		{
	//			// 1//1 2//1 3//1 4//1, tem que picotar mais.
	//			// Para cada pedaço em f, dividir em antes das barras e depois das barras. Pegar o que está antes das barras e
	//			//por no vetor de indices.
	//			// O numero de vértices será sempre 3. Se vier diferente lança exceção pq só tratarei triangulos.
	//			if (pedacos.size() > 4)
	//			{
	//				string err = "só entende triangulos";
	//				throw exception(err.c_str());
	//			}
	//			vector<string> indice01 = SplitString(pedacos[1], "//");
	//			vector<string> indice02 = SplitString(pedacos[2], "//");
	//			vector<string> indice03 = SplitString(pedacos[3], "//"); 
	//			array<unsigned int, 3 > face;
	//			size_t indice01sz = indice01[0].size();
	//			face[0] = std::stoi(indice01[0], &indice01sz);
	//			size_t indice02sz = indice02[0].size();
	//			face[1] = std::stoi(indice02[0], &indice02sz);
	//			size_t indice03sz = indice03[0].size();
	//			face[2] = std::stoi(indice03[0], &indice03sz);
	//			faces.push_back(face);
	//		}
	//	}
	//	//a partir daqui já tenho o que eu quero: a lista de vértices e a lista de faces.
	//	//Posso, portanto, alocar a estrutura permanente para eles.
	//	//1) criar os buffers de ponteiros nus
	//	vertexBuffer = new GLfloat[vertexes.size() * 3];
	//	for (auto i = 0; i < vertexes.size(); i++)
	//	{
	//		array<float, 3> vert = vertexes[i];
	//		vertexBuffer[i * 3] = vert[0];
	//		vertexBuffer[i * 3 + 1] = vert[0 + 1];
	//		vertexBuffer[i * 3 + 2] = vert[0 + 2];
	//	}
	//	elementBuffer = new GLuint[faces.size() * 3];
	//	for (auto i = 0; i < faces.size(); i++)
	//	{
	//		array<unsigned int, 3> face = faces[i];

	//	}
	//	//GLfloat* vertexBuffer;
	//	//GLuint* elementBuffer;
	//	glGenVertexArrays(1, &tri.VertexArrayID);
	//	glBindVertexArray(tri.VertexArrayID);
	//	glGenBuffers(1, &tri.vertexbuffer);
	//	glBindBuffer(GL_ARRAY_BUFFER, tri.vertexbuffer);
	//	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), const_cast<GLfloat*>(tri.vertexBufferData), GL_STATIC_DRAW);
	//	glGenBuffers(1, &tri.vertexcolor);
	//	glBindBuffer(GL_ARRAY_BUFFER, tri.vertexcolor);
	//	glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(GLfloat), const_cast<GLfloat*>(tri.vertexColorData), GL_STATIC_DRAW);
	//	glGenBuffers(1, &tri.elementBuffer);
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tri.elementBuffer);
	//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLushort), tri.elementBufferData, GL_STATIC_DRAW);
	//}
	//else
	//{
	//	string err = "arquivo não encontrado " + objFilePath;
	//	throw std::exception(err.c_str());
	//}
}
Geometry::~Geometry()
{
	glDeleteVertexArrays(1, &vertexArrayId);
	glDeleteBuffers(1, &vertexBufferId);
	glDeleteBuffers(1, &elementBufferId);
	delete[] vertexBuffer;
	delete[] elementBuffer;
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
