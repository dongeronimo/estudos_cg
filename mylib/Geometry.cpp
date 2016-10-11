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
	assert("nao implementado" && false);
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
			(void*)(sizeof(GLfloat) * 12 /*4 Vértices de 3 elementos*/)
	);
	//3)Elementos
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
	//desenha
	glDrawElements(GL_TRIANGLES,//O que a array de elementos tem
		6, //indices.size
		GL_UNSIGNED_INT,//O tipo da array de elementos.
		(void*)0//o ponto na array de elementos onde comeca minha coisa
		);
	//limpa
	shaderProgram->StopUsing();
}
