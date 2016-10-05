#include "geometry.h"
#include <fstream>	
#include <vector>
#include <regex>
#include <iostream>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
Geometry::Geometry(std::string objFilePath, GLuint vertexShaderId, GLuint fragmentShaderId)
{
    // Bota o shader.
	SetShader(vertexShaderId, fragmentShaderId);
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

void Geometry::SetShader(GLuint vertexShaderId, GLuint fragmentShaderId){
	shader.vsId = vertexShaderId;
	shader.fsId = fragmentShaderId;
	shader.programId = MakeProgram(shader.vsId, shader.fsId);
	introspectProgram(shader.programId, shader.attributes, shader.uniforms);
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
	//TODO: Implementar
}

void Geometry::Rotate(std::array<float, 9> angles)
{
	//TODO: Implementar
}

void Geometry::Scale(std::array<float, 3> values)
{
	//TODO: Implementar
}

void Geometry::Render(glm::mat4 viewProjection)
{
	//Ativa o shader
    glUseProgram(shader.programId);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 mvp = viewProjection * model; //A multiplicação é na ordem inversa do nome.
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

Geometry::Geometry(GLuint vertexShaderId, GLuint fragmentShaderId) {
	SetShader(vertexShaderId, fragmentShaderId);
	//cria um cubo.
	GLfloat cube_vertices[] = {
			// front
			-1.0, -1.0,  1.0,
			1.0, -1.0,  1.0,
			1.0,  1.0,  1.0,
			-1.0,  1.0,  1.0,
			// back
			-1.0, -1.0, -1.0,
			1.0, -1.0, -1.0,
			1.0,  1.0, -1.0,
			-1.0,  1.0, -1.0,
	};
	GLfloat cube_colors[] = {
			// front colors
			1.0, 0.0, 0.0,
			0.0, 1.0, 0.0,
			0.0, 0.0, 1.0,
			1.0, 1.0, 1.0,
			// back colors
			1.0, 0.0, 0.0,
			0.0, 1.0, 0.0,
			0.0, 0.0, 1.0,
			1.0, 1.0, 1.0,
	};
	GLuint cube_elements[] = {
			// front
			0, 1, 2,
			2, 3, 0,
			// top
			1, 5, 6,
			6, 2, 1,
			// back
			7, 6, 5,
			5, 4, 7,
			// bottom
			4, 0, 3,
			3, 7, 4,
			// left
			4, 5, 1,
			1, 0, 4,
			// right
			3, 2, 6,
			6, 7, 3,
	};
	//Numero de faces
	const unsigned int numFaces = sizeof(cube_elements)/3;
	//Numero de vertices
	const unsigned int numVerts = sizeof(cube_vertices)/3;
	//Cria o VAO
	glGenVertexArrays(1, &vertexArrayId);
	glBindVertexArray(vertexArrayId);
	//Cria o buffer de indices
	elementBufferSize = 3 * numFaces * sizeof(GLuint);
	elementBuffer = new GLuint[3 * numFaces];
	memcpy(elementBuffer, cube_elements, sizeof(cube_elements));
	glGenBuffers(1, &elementBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * numFaces * sizeof(GLuint), elementBuffer, GL_STATIC_DRAW);
	//Cria o buffer de vertices
	vertexBufferSize = 3 * numVerts * sizeof(GLfloat);
	vertexBuffer = new GLfloat[3 * numVerts];
	memcpy(vertexBuffer, cube_vertices, sizeof(cube_vertices));
	glGenBuffers(1, &vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, numVerts * 3 * sizeof(GLfloat), const_cast<GLfloat*>(vertexBuffer), GL_STATIC_DRAW);
	//Pronto.
	glBindVertexArray(0);
}
