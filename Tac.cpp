#include <windows.h>        //	Utilizarea functiilor de sistem Windows (crearea de ferestre, manipularea fisierelor si directoarelor);
#include <stdlib.h>         //  Biblioteci necesare pentru citirea shaderelor;
#include <stdio.h>
#include <GL/glew.h>        //  Definește prototipurile functiilor OpenGL si constantele necesare pentru programarea OpenGL moderna; 
#include <GL/freeglut.h>    //	Include functii pentru: 
#include "loadShaders.h"	//	Fisierul care face legatura intre program si shadere;
#include "glm/glm.hpp"		
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "SOIL.h"
#include "iostream"
#include <vector>
#include <cmath> 
#include "Global.h"

float raza = 26.0f;
GLuint CreateVBOTac(void) {

	GLuint Vaotac, Vbotac, Ebotac;


	GLfloat tacVertices[] = {

	-550.0f, 7.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,//tacul
	-550.0f, -7.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-250.0f, 2.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-250.0f, -2.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	};
	GLuint tacIndices[] = {
		0, 1, 2,
		1,2,3,
	};
	glGenVertexArrays(1, &Vaotac);
	glBindVertexArray(Vaotac);

	glGenBuffers(1, &Vbotac);
	glBindBuffer(GL_ARRAY_BUFFER, Vbotac);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tacVertices), tacVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &Ebotac);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ebotac);									//  Setarea tipului de buffer - atributele varfurilor;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tacIndices), tacIndices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0); // coordonate

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat))); // culori

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(7 * sizeof(GLfloat))); // coordonate textură
	
	return Vaotac;

}







