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
#include <glm/detail/type_mat.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
using namespace std;
Geometry::Geometry(std::string objFilePath, GLuint vertexShaderId, GLuint fragmentShaderId)
{
    // Bota o shader.
    this->shader.vsId = vertexShaderId;
    this->shader.fsId = fragmentShaderId;
    this->shader.programId = MakeProgram(this->shader.vsId, this->shader.fsId);
    introspectProgram(this->shader.programId, this->shader.attributes, this->shader.uniforms);
    // Pega o objeto 3d.
	Assimp::Importer importer;
    cout<<objFilePath<<endl;
	const aiScene* scene = importer.ReadFile(objFilePath, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
	if (!scene) assert("n�o conseguiu carregar o .Obj" && false);
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
    elementBufferSize = 3 * numFaces * sizeof(GLuint);
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
    vertexBufferSize = 3 * numVerts * sizeof(GLfloat);
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
	//Ativa o shader
    glUseProgram(shader.programId);
    //Passa os dados pro shader
    //Nessa versão o calculo da matriz é tôdo aqui, no futuro será parte numa
    //classe de camera.
    glm::mat4 projection = glm::perspective<GLfloat>(45, 1, 0.1f, 100.f);
    glm::mat4 view = glm::lookAt(glm::vec3(1, 10, -10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 mvp = projection * view * model; //A multiplicação é na ordem inversa do nome.
	glUniformMatrix4fv(shader.uniforms.at("mvp"), 1, GL_FALSE, &mvp[0][0]);
    //Passa os buffers pro shader
    glEnableVertexAttribArray(shader.attributes["vertexPosition_modelspace"]);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glVertexAttribPointer(
		shader.attributes["vertexPosition_modelspace"],                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

    //Agora é a array de elementos
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
    const int numElements = vertexBufferSize / sizeof(GLfloat);
	glDrawElements(GL_TRIANGLES, numElements,GL_UNSIGNED_INT , (void*)0);
	GLenum err = glGetError();
    cout<<err<<endl;
    //Renderiza
    //Limpa
}
