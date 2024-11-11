#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Bila.h"
#include <GL/glew.h>
#include "circle.h"
#include <vector>
#include "Global.h"

float x_BilaAlba = -200.0f;
float y_BilaAlba = 0.0f;

Bila::Bila(float cx, float cy) {
	pozitieinitiala[0] = cx;
	pozitieinitiala[1] = cy;

}
GLuint CreateVBOBile(float cx, float cy)
{


	buildCircle(12.0f, 90, cx, cy);
	GLuint VaoBila, VboBila;
	float scaleX = 0.005f; 
	float scaleY = 0.005f;
	glGenVertexArrays(1, &VaoBila);
	glBindVertexArray(VaoBila);
	glGenBuffers(1, &VboBila);
	glBindBuffer(GL_ARRAY_BUFFER, VboBila);
	glBufferData(GL_ARRAY_BUFFER, temp.size() * sizeof(glm::vec3), &temp[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0));
	std::vector<glm::vec2> texCoords;
	float angleStep = 2 * PI / temp.size();
	for (size_t i = 0; i < temp.size(); i++) {
		float u = (cos(i * angleStep) + 1) / 2+cx*scaleX;
		float v = (sin(i * angleStep) + 1) / 2+cy*scaleY;
		texCoords.push_back(glm::vec2(u, v));
	}
	GLuint TexCoordVbo;
	glGenBuffers(1, &TexCoordVbo);
	glBindBuffer(GL_ARRAY_BUFFER, TexCoordVbo);
	glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(glm::vec2), &texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	return VaoBila;

}

GLuint CreateVBOBilaAlba(float cx, float cy)
{
	buildCircle(26.0f, 90, x_BilaAlba, y_BilaAlba);
	GLuint VaoBila, VboBila;

	glGenVertexArrays(1, &VaoBila);
	glBindVertexArray(VaoBila);

	glGenBuffers(1, &VboBila);
	glBindBuffer(GL_ARRAY_BUFFER, VboBila);
	glBufferData(GL_ARRAY_BUFFER, temp.size() * sizeof(glm::vec3), &temp[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0));

	std::vector<glm::vec2> texCoords;
	float angleStep = 2 * PI / temp.size();
	for (size_t i = 0; i < temp.size(); i++) {
		float u = (cos(i * angleStep) + 1) / 2;
		float v = (sin(i * angleStep) + 1) / 2;
		texCoords.push_back(glm::vec2(u, v));
	}

	GLuint TexCoordVbo;
	glGenBuffers(1, &TexCoordVbo);
	glBindBuffer(GL_ARRAY_BUFFER, TexCoordVbo);
	glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(glm::vec2), &texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	return VaoBila;

}