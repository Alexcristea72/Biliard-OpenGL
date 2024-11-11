#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <vector>
#include "Circle.h"
#include "Global.h"

void buildCircle(float radius, int vCount, float cx, float cy)
{
	temp.clear();
	float angle = 360.0f / vCount;
	int triangleCount = vCount - 2;


	for (int i = 0; i < vCount; i++)
	{
		float currentAngle = angle * i;
		float x = cx + radius * cos(glm::radians(currentAngle));
		float y = cy + radius * sin(glm::radians(currentAngle));
		float z = 0.0f;
		temp.push_back(glm::vec3(x, y, z));

	}
	vertices.clear();
	for (int i = 0; i < vCount - 1; i++) {
		vertices.push_back(temp[i]);
		vertices.push_back(temp[(i + 1) % vCount]);
	}
}

GLuint CreateVBOCircle(float cx, float cy) {
	buildCircle(26.0f, 90, cx, cy);
	GLuint VaoCircle, VboCircle;
	glGenVertexArrays(1, &VaoCircle);
	glBindVertexArray(VaoCircle);
	glGenBuffers(1, &VboCircle);
	glBindBuffer(GL_ARRAY_BUFFER, VboCircle);
	glBufferData(GL_ARRAY_BUFFER, temp.size() * sizeof(glm::vec3), &temp[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0));
	return VaoCircle;
}