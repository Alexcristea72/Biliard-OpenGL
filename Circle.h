#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <vector>
#include <GL/glew.h>

void buildCircle(float radius, int vCount, float cx, float cy);
GLuint CreateVBOCircle(float cx, float cy);
