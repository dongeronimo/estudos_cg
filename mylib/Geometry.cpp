#include "Geometry.h"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
using namespace shader;
geometry::Geometry::Geometry(GLuint vertexShaderId, GLuint fragmentShaderId)
{
	//cria o shader;
	shaderProgram = std::make_unique<shader::Shader>(vertexShaderId, fragmentShaderId);
	//Cria a geometria.
	//Vertex Coords/Texture Coords
	GLfloat vertexData[]={
		0,0,0,
		0,1,0,  
		1,0,0,  
		1,1,0,

		0,0,
		0,1,
		1,0,
		1,1,
	};
	//Dois triangulos = 1 face
	GLuint elementData[]={
		0, 1, 2, 
		1, 3, 2
	};
	this->quantidadeDeFaces = 2;
	//Cria o vao e os vbos
	glGenVertexArrays(1, &vertexArrayId);
	glBindVertexArray(vertexArrayId);
	glGenBuffers(1, &vertexBufferId);
	glGenBuffers(1, &elementBufferId);
	//passa os elementos pro buffer de elementos
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elementData), elementData, GL_STATIC_DRAW);
	//agora os vertexes e texCoords. 
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), const_cast<GLfloat*>(vertexData), GL_STATIC_DRAW);
}

geometry::Geometry::Geometry(std::string filepath, GLuint vertexShaderId, GLuint fragmentShaderId)
{
	//Cria o shader
	shaderProgram = std::make_unique<shader::Shader>(vertexShaderId, fragmentShaderId);
	//Carrega a geometria
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filepath, aiProcess_JoinIdenticalVertices);
	const aiMesh* mesh = scene->mMeshes[0];
	//os vértices
	const int qtdDeVerts = mesh->mNumVertices;
	GLfloat *tempVertexBuffer = new GLfloat[qtdDeVerts * 3];
	for (auto i = 0; i < qtdDeVerts; i++)
	{
		aiVector3D currentVert = mesh->mVertices[i];
		tempVertexBuffer[i * 3] = currentVert[0];
		tempVertexBuffer[i * 3 + 1] = currentVert[1];
		tempVertexBuffer[i * 3 + 2] = currentVert[2];
	}
	//as texcoords
	GLfloat *tempTextureBuffer = new GLfloat[qtdDeVerts * 2];
	for (auto i = 0; i < qtdDeVerts; i++)
	{
		aiVector3D currentTc = mesh->mTextureCoords[0][i];
		tempTextureBuffer[i * 2] = currentTc[0];
		tempTextureBuffer[i * 2 + 1] = currentTc[1];
	}
	//os elementos
	const int qtdDeFaces = mesh->mNumFaces;
	this->quantidadeDeFaces = qtdDeFaces;
	GLuint *elementBuffer = new GLuint[qtdDeFaces * 3];
	for (auto i = 0; i < qtdDeFaces; i++)
	{
		aiFace currentF = mesh->mFaces[i];
		elementBuffer[i * 3] = currentF.mIndices[0];
		elementBuffer[i * 3 + 1] = currentF.mIndices[1];
		elementBuffer[i * 3 + 2] = currentF.mIndices[2];
	}
	//Junta as texturas e os vértices em um unico buffer
	GLfloat *vertexBuffer = new GLfloat[qtdDeVerts * 3 + qtdDeVerts * 2];
	memcpy(vertexBuffer, tempVertexBuffer, qtdDeVerts * 3 * sizeof(GLfloat));
	memcpy(vertexBuffer + qtdDeVerts * 3 * sizeof(GLfloat), tempTextureBuffer, qtdDeVerts * 2 * sizeof(GLfloat));
	delete[] tempVertexBuffer;
	delete[] tempTextureBuffer;
	//agora cria as coisas do opengl
	//assert("nao implementado" && false);
	//Cria o vao e os vbos
	glGenVertexArrays(1, &vertexArrayId);
	glBindVertexArray(vertexArrayId);
	glGenBuffers(1, &vertexBufferId);
	glGenBuffers(1, &elementBufferId);
	//passa os elementos pro buffer de elementos
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, qtdDeFaces * sizeof(GLuint) * 3, elementBuffer, GL_STATIC_DRAW);
	//agora os vertexes e texCoords. 
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, qtdDeVerts * 3 + qtdDeVerts * 2 * sizeof(GLfloat), const_cast<GLfloat*>(vertexBuffer), GL_STATIC_DRAW);
	//Não preciso mais dele.
	delete[]vertexBuffer;
}

geometry::Geometry::~Geometry()
{
}

void geometry::Geometry::Render(glm::mat4 viewProjectionMatrix)
{
	//ativa o shader
	shaderProgram->StartUsing();
	//bind da textura
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glUniform1i(shaderProgram->GetUniform("mytexture"), 0); //pq está usando o GL_TEXTURE0
	//shaderProgram->GetUniform("mytexture")
	//aplica a MVP
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 mvp = viewProjectionMatrix * model; //A multiplicação é na ordem inversa do nome.
	glUniformMatrix4fv(shaderProgram->GetUniform("mvp"), 1, GL_FALSE, &mvp[0][0]);
	//passa os buffers
	//1)Vertexes
	glEnableVertexAttribArray(shaderProgram->GetAttribute("vertexPosition_modelspace"));
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glVertexAttribPointer(
		shaderProgram->GetAttribute("vertexPosition_modelspace"),
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);
	//2)Tex coords textureCoord
	glEnableVertexAttribArray(shaderProgram->GetAttribute("textureCoord"));
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glVertexAttribPointer(
		shaderProgram->GetAttribute("textureCoord"),
			2,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)(quantidadeDeFaces * 3 * sizeof(GLfloat)) /*4 Vértices de 3 elementos*/
	);
	//3)Elementos
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
	//desenha
	glDrawElements(GL_TRIANGLES,//O que a array de elementos tem
		quantidadeDeFaces * 3, //indices.size
		GL_UNSIGNED_INT,//O tipo da array de elementos.
		(void*)0//o ponto na array de elementos onde comeca minha coisa
		);
	//limpa
	shaderProgram->StopUsing();
}
