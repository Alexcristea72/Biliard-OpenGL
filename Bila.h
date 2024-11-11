#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <cmath>
#include <GL/glew.h>

class Bila {
public:
	glm::vec2 pozitieinitiala;
	glm::vec4 pozitiecurenta;
	float cx;
	float cy;
	Bila(float cx, float cy);


};

GLuint CreateVBOBile(float cx, float cy);
GLuint CreateVBOBilaAlba(float cx, float cy);