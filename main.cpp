#include <windows.h>        //	Utilizarea functiilor de sistem Windows (crearea de ferestre, manipularea fisierelor si directoarelor);
#include <stdlib.h>         //  Biblioteci necesare pentru citirea shaderelor;
#include <stdio.h>
#include <GL/glew.h>        //  Definește prototipurile functiilor OpenGL si constantele necesare pentru programarea OpenGL moderna; 
#include <GL/freeglut.h>    //	Include functii pentru: 
#include "loadShaders.h"	//	Fisierul care face legatura intre program si shadere;
#include "glm/glm.hpp"		//	Bibloteci utilizate pentru transformari grafice;
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "SOIL.h"
#include "iostream"//	Biblioteca pentru texturare;
#include <vector>
#include <cmath> 
#include "Global.h"
#include "Bila.h"
#include "Circle.h"
#include "Tac.h"
#include <GLFW/glfw3.h>
using namespace std;
unsigned int vertexBuffer;
unsigned int vertexArray;
GLuint
VaoId,
VboId,
EboId,
VaoCircle,
VaoBila,
ProgramId,
myMatrixLocation,
viewLocation,
projLocation,
matrRotlLocation,
codColLocation;
GLuint
texture1,
texture2,
texture3,
texture4,
texture5,
texture6,
texture7,
texture8,
texture9,
texture10,
texture11,
texture12,
texture13,
texture14;
GLuint VaoCircle1, VboCircle1;
GLuint VaoCircle2, VboCircle2;
GLuint VaoCircle3, VboCircle3;
GLuint VaoCircle4, VboCircle4;
GLuint VaoCircle5, VboCircle5;
GLuint VaoCircle6, VboCircle6;
GLuint VaoBila1, VboBila1;
GLuint VaoBila2, VboBila2;
GLuint VaoBila3, VboBila3;
GLuint VaoBila4, VboBila4;
GLuint VaoBila5, VboBila5;
GLuint VaoBila6, VboBila6;
GLuint VaoBila7, VboBila7;
GLuint VaoBila8, VboBila8;
GLuint VaoBilaAlba, VboBilaAlba;
GLuint VaoTac, VboTac, EboTac;
float tx = 100.0f;
float ty = 100.0f;
extern float tacTranslation = 0.0f;
bool tacMovingForward = false;  

const float maxTranslation = 50.0f; 
const float translationStep = 1.0f; 

std::vector<glm::vec2> translatiiBile;
GLfloat
winWidth = 1200, winHeight = 900;
glm::mat4
myMatrix, matrRot, matrTransl;
float i = 0.0, alpha = 0.0, step = 0.3, beta = 0.002, angle = 0;
int codCol;
float obsX = 0.0, obsY = 0.0, obsZ = 800.f;
float refX = 0.0f, refY = 0.0f;
float vX = 0.0;
glm::mat4 view;

float width = 1200, height = 1000, xMin = -1200.f, xMax = 12000, yMin = -1200, yMax = 1200, zNear = 0, zFar = 1000, fov = 45;
glm::mat4 projection;
std::vector<Bila> bile = {
		Bila(50.0f, 0.0f),
		Bila(100.0f, 30.0f),
		Bila(100.0f, -30.0f),
		Bila(150.0f, -60.0f),
		Bila(150.0f, -50.0f),
		Bila(150.0f, 0.0f),
		Bila(150.0f, 50.0f),
		Bila(150.0f, -5.0f),
};
std::vector<float>pozitiiInitiale;




void LoadTexture(const char* texturePath, int texture_no)
{
	GLuint* texture;
	switch (texture_no) {
	case 1:
		texture = &texture1;
		break;
	case 2:
		texture = &texture2;
		break;
	case 3:	
		texture = &texture3;
		break;
	case 4:
		texture = &texture4;
		break;
	case 5:
		texture = &texture5;
		break;
	case 6:
		texture = &texture6;
		break;
	case 7:
		texture = &texture7;
		break;
	case 8:
		texture = &texture8;
		break;
	case 9:
		texture = &texture9;
		break;
	case 10:
		texture = &texture10;
		break;
	case 11:
		texture = &texture11;
		break;
	case 12:
		texture = &texture12;
		break;
	default:
		std::cout << "Invalid texture number" << std::endl;
		return;
	}
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height;
	unsigned char* image = SOIL_load_image(texturePath, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}
void CreateShaders(void)
{
	ProgramId = LoadShaders("Shader.vert", "Shader.frag");
	glUseProgram(ProgramId);
}
void CreateVBO(void)
{
	//	Atributele varfurilor -  COORDONATE, CULORI, COORDONATE DE TEXTURARE;
	GLfloat Vertices[] = {
		//	Coordonate;					Culori;				Coordonate de texturare;
		  -450.0f, -350.0f, 0.0f, 1.0f,	  0.5f, 0.5f, 0.5f,	0.0f, 0.0f,	//verdele mesei
		   450.0f, -350.0f, 0.0f, 1.0f,   0.5f, 0.5f, 0.5f,	1.0f, 0.0f,
		   450.0f,  350.0f, 0.0f, 1.0f,   0.5f, 0.5f, 0.5f,	1.0f, 1.0f,
		  -450.0f,  350.0f, 0.0f, 1.0f,   0.5f, 0.5f, 0.5f,	0.0f, 1.0f,

		  -475.0f, -300.0f, 0.0f, 1.0f,  0.5f, 0.5f, 0.5f,	0.0f, 0.0f,//stanga lemn
		  -450.0f, -300.0f, 0.0f, 1.0f,   0.5f, 0.5f, 0.5f,	1.0f, 0.0f,
		  -450.0f,  300.0f, 0.0f, 1.0f,   0.5f, 0.5f, 0.5f,	0.0f, 1.0f,
		  -475.0f,  300.0f, 0.0f, 1.0f,   0.5f, 0.5f, 0.5f,	1.0f, 1.0f,

		   475.0f, -300.0f, 0.0f, 1.0f,  0.5f, 0.5f, 0.5f,	0.0f, 0.0f,//dreapta lemn
		   450.0f, -300.0f, 0.0f, 1.0f,   0.5f, 0.5f, 0.5f,	1.0f, 0.0f,
		   450.0f,  300.0f, 0.0f, 1.0f,   0.5f, 0.5f, 0.5f,	0.0f, 1.0f,
		   475.0f,  300.0f, 0.0f, 1.0f,   0.5f, 0.5f, 0.5f,	1.0f, 1.0f,

		  -425.0f, -350.0f, 0.0f, 1.0f,  0.5f, 0.5f, 0.5f,	0.0f, 0.0f,//jos lemn
		  -425.0f, -385.0f, 0.0f, 1.0f,   0.5f, 0.5f, 0.5f,	1.0f, 0.0f,
		   425.0f,  -385.0f, 0.0f, 1.0f,   0.5f, 0.5f, 0.5f,	0.0f, 1.0f,
		   425.0f,  -350.0f, 0.0f, 1.0f,   0.5f, 0.5f, 0.5f,	1.0f, 1.0f,

		  -425.0f, 350.0f, 0.0f, 1.0f,  0.5f, 0.5f, 0.5f,	0.0f, 0.0f,//sus lemn
		  -425.0f, 385.0f, 0.0f, 1.0f,   0.5f, 0.5f, 0.5f,	1.0f, 0.0f,
		   425.0f,  385.0f, 0.0f, 1.0f,   0.5f, 0.5f, 0.5f,	0.0f, 1.0f,
		   425.0f,  350.0f, 0.0f, 1.0f,   0.5f, 0.5f, 0.5f,	1.0f, 1.0f,

		  -450.0f, 300.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	0.0f, 0.0f, //perete stanga
		  -450.0f, -300.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	1.0f, 0.0f,
		  -425.0f,  275.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	0.0f, 1.0f,
		  -425.0f,  -275.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,1.0f, 1.0f,

		   450.0f, 300.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	0.0f, 0.0f,//perete dreapta
		   450.0f, -300.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	1.0f, 0.0f,
		   425.0f,  275.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	0.0f, 1.0f,
		   425.0f,  -275.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	1.0f, 1.0f,

		  -425.0f, 350.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	0.0f, 0.0f,//perete sus 1
		  -10.0f, 350.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	1.0f, 0.0f,
		  -400.0f,  325.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	0.0f, 1.0f,
		  -20.0f,  325.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	1.0f, 1.0f,

		   10.0f, 350.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	0.0f, 0.0f,//perete sus 2
		   425.0f, 350.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	1.0f, 0.0f,
		   20.0f,  325.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	0.0f, 1.0f,
		   400.0f,  325.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	1.0f, 1.0f,

		  -425.0f, -350.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	0.0f, 0.0f,//perete jos 1
		  -10.0f, -350.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	1.0f, 0.0f,
		  -400.0f,  -325.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	0.0f, 1.0f,
		  -20.0f,  -325.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	1.0f, 1.0f,

		   10.0f,-350.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	0.0f, 0.0f,//perete jos 2
		   425.0f, -350.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	1.0f, 0.0f,
		   20.0f,  -325.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	0.0f, 1.0f,
		   400.0f,  -325.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,1.0f, 1.0f,

		  -425.0f,  350.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	0.0f, 0.0f,//gri stanga sus
		  -450.0f,  300.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	1.0f, 0.0f,
		  -425.0f,  385.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	0.0f, 1.0f,
		  -475.0f,  300.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,1.0f, 1.0f,
		  -475.0f,  385.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,1.0f, 1.0f,

		  -425.0f,  -350.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	0.0f, 0.0f,//gri stanga jos
		  -450.0f,  -300.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	1.0f, 0.0f,
		  -425.0f,  -385.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	0.0f, 1.0f,
		  -475.0f,  -300.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,1.0f, 1.0f,
		  -475.0f,  -385.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,1.0f, 1.0f,

		   425.0f,  350.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	0.0f, 0.0f,//gri dreapta sus
		   450.0f,  300.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	1.0f, 0.0f,
		   425.0f,  385.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	0.0f, 1.0f,
		   475.0f,  300.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,1.0f, 1.0f,
		   475.0f,  385.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,1.0f, 1.0f,

		   425.0f,  -350.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	0.0f, 0.0f,//gri dreapta jos
		   450.0f,  -300.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	1.0f, 0.0f,
		   425.0f,  -385.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,	0.0f, 1.0f,
		   475.0f,  -300.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,1.0f, 1.0f,
		   475.0f,  -385.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,1.0f, 1.0f,

		  -200.0f, 325.0f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f,	1.0f, 0.0f,//linie alba
		  -200.0f, -325.0f, 0.0f, 1.0f,  0.0f, 0.0f, 0.0f,	1.0f, 0.0f,

		   
	};
	GLuint Indices[] = {
	0,1,2,
	0,2,3,

	4,5,6,
	4,6,7,

	8,9,10,
	8,10,11,

	12,13,14,
	12,14,15,

	16,17,18,
	16,18,19,

	20,21,22,
	21,22,23,

	24,25,26,
	25,26,27,

	28,29,30,
	29,30,31,

	32,33,34,
	33,34,35,

	36,37,38,
	37,38,39,

	40,41,42,
	41,42,43,

	44,45,46,
	45,46,48,
	45,47,48,

	49,50,51,
	50,51,53,
	50,52,53,

	54,55,56,
	55,56,58,
	55,57,58,

	59,60,61,
	60,61,63,
	60,62,63,

	64,65,//linie alba

	};
	//  Transmiterea datelor prin buffere;
	//  Se creeaza / se leaga un VAO (Vertex Array Object);
	glGenVertexArrays(1, &VaoId);                                                   //  Generarea VAO si indexarea acestuia catre variabila VaoId;
	glBindVertexArray(VaoId);
	//  Se creeaza un buffer pentru VARFURI - COORDONATE, CULORI si TEXTURARE;
	glGenBuffers(1, &VboId);													//  Generarea bufferului si indexarea acestuia catre variabila VboId;
	glBindBuffer(GL_ARRAY_BUFFER, VboId);												//  Setarea tipului de buffer - atributele varfurilor;
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	//	Se creeaza un buffer pentru INDICI;
	glGenBuffers(1, &EboId);														//  Generarea bufferului si indexarea acestuia catre variabila EboId;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);									//  Setarea tipului de buffer - atributele varfurilor;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
	//	Se activeaza lucrul cu atribute;
	//  Se asociaza atributul (0 = coordonate) pentru shader;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
	//  Se asociaza atributul (1 =  culoare) pentru shader;
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat)));
	//  Se asociaza atributul (2 =  texturare) pentru shader;
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(7 * sizeof(GLfloat)));
}

void DestroyShaders(void)
{
	glDeleteProgram(ProgramId);
}
void DestroyVBO(void)
{
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);
	glDeleteBuffers(1, &VboTac);
	glDeleteBuffers(1, &VboCircle1);
	glDeleteBuffers(1, &VboBila1);
	glDeleteBuffers(1, &EboId);
	glDeleteBuffers(1, &EboTac);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
	glDeleteVertexArrays(1, &VaoTac);
	glDeleteVertexArrays(1, &VaoBila1);
	glDeleteVertexArrays(1, &VaoCircle1);
}
void Cleanup(void)
{
	DestroyShaders();
	DestroyVBO();
}
//  Setarea parametrilor necesari pentru fereastra de vizualizare;
void Initialize(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);		//  Culoarea de fond a ecranului;
	//  Trecerea datelor de randare spre bufferul folosit de shadere;
	CreateVBO();
	VaoTac = CreateVBOTac();
	VaoCircle1 = CreateVBOCircle(-450.0f, 332.0f);
	VaoCircle2 = CreateVBOCircle(450.0f, 332.0f);
	VaoCircle3 = CreateVBOCircle(-450.0f, -332.0f);
	VaoCircle4 = CreateVBOCircle(450.0f, -332.0f);
	VaoCircle5 = CreateVBOCircle(0.0f, 358.0f);
	VaoCircle6 = CreateVBOCircle(0.0f, -358.0f);

	VaoBila1 = CreateVBOCircle(bile[0].pozitieinitiala[0], bile[0].pozitieinitiala[1]);
	VaoBila2 = CreateVBOCircle(bile[1].pozitieinitiala[0], bile[1].pozitieinitiala[1]);
	VaoBila3 = CreateVBOCircle(bile[2].pozitieinitiala[0], bile[2].pozitieinitiala[1]);
	VaoBila4 = CreateVBOCircle(bile[3].pozitieinitiala[0], bile[3].pozitieinitiala[1]);
	VaoBila5 = CreateVBOCircle(bile[4].pozitieinitiala[0], bile[4].pozitieinitiala[1]);
	VaoBila6 = CreateVBOCircle(bile[5].pozitieinitiala[0], bile[5].pozitieinitiala[1]);
	VaoBila7 = CreateVBOCircle(bile[6].pozitieinitiala[0], bile[6].pozitieinitiala[1]);
	VaoBila8 = CreateVBOCircle(bile[7].pozitieinitiala[0], bile[7].pozitieinitiala[1]);
	VaoBilaAlba = CreateVBOBilaAlba(-200, 0);

	LoadTexture("./Texturi/masa_verde3.png", 1);
	LoadTexture("./Texturi/lemn.png", 2);
	LoadTexture("./Texturi/metal.png", 3);
	LoadTexture("./Texturi/1.png", 4);
	LoadTexture("./Texturi/2.png", 5);
	LoadTexture("./Texturi/3.png", 6);
	LoadTexture("./Texturi/4.png", 7);
	LoadTexture("./Texturi/7.png", 8);
	LoadTexture("./Texturi/8.png", 9);
	LoadTexture("./Texturi/Alba.png", 10);
	LoadTexture("./Texturi/tac.png", 11);

	CreateShaders();
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	viewLocation = glGetUniformLocation(ProgramId, "view");
	projLocation = glGetUniformLocation(ProgramId, "projection");
}



void ProcessSpecialKeys(int key, int xx, int yy) {
	switch (key) {
	case 'a':
		tx -= 10.0f;
		glutPostRedisplay();
		break;

	case 'd':
		tx += 10.0f;
		glutPostRedisplay();
		break;

	}

}

void drawTac(GLuint Vaotac) {
	glUseProgram(ProgramId);

	glm::mat4 matrTransl = glm::translate(glm::mat4(1.0f), glm::vec3(tx, 0.0f, 0.0f));

	GLuint matrTranslLocation = glGetUniformLocation(ProgramId, "matrTransl");
	glUniformMatrix4fv(matrTranslLocation, 1, GL_FALSE, glm::value_ptr(matrTransl));


	

}



void RenderFunction(void)
{

	glClear(GL_COLOR_BUFFER_BIT);			//  Se curata ecranul OpenGL pentru a fi desenat noul continut;
	glLineWidth(2.0f);
	//drawTac(VaoTac);

	matrTransl = glm::translate(glm::mat4(1.0f), glm::vec3(i, 0.0, 0.0));		
	//	Matrici pentru transformari;
	matrRot = glm::rotate(glm::mat4(1.0f), PI / 8, glm::vec3(0.0, 0.0, 1.0));
	//	TRANSFORMARI;
	// 
	//	Pozitia observatorului;
	glm::vec3 obs = glm::vec3(obsX, obsY, obsZ);
	//	Pozitia punctului de referinta;
	refX = obsX; refY = obsY;
	glm::vec3 refPoint = glm::vec3(refX, refY, -1.0f);
	//	Verticala din planul de vizualizare; 
	glm::vec3 vert = glm::vec3(vX, 1.0f, 0.0f);
	// Matricea de vizualizare
	view = glm::lookAt(obs, refPoint, vert);
	//	Realizarea proiectiei;
	projection = glm::perspective(fov, GLfloat(width) / GLfloat(height), zNear, zFar);
	// Matrice generica (initializata ca fiind matricea identica, se pot testa alte valori)
	myMatrix = glm::mat4(1.0f);
	//	Transmiterea variabilelor uniforme pentru MATRICEA DE TRANSFORMARE, PERSPECTIVA si PROIECTIE spre shadere;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, &projection[0][0]);

	glBindVertexArray(VaoId);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 0);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(0 * sizeof(GLuint)));

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 1);
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, (void*)(6 * sizeof(GLuint)));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 0);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)(30 * sizeof(GLuint)));

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 2);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)(66 * sizeof(GLuint)));


	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(VaoCircle1);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 2);

	glBindVertexArray(VaoCircle2);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 2);

	glBindVertexArray(VaoCircle3);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 2);

	glBindVertexArray(VaoCircle4);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 2);
	glBindVertexArray(VaoCircle5);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 2);

	glBindVertexArray(VaoCircle6);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 2);

	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(VaoCircle1);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 2);

	glBindVertexArray(VaoCircle2);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 2);

	glBindVertexArray(VaoCircle3);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 2);

	glBindVertexArray(VaoCircle4);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 2);
	glBindVertexArray(VaoCircle5);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 2);

	glBindVertexArray(VaoCircle6);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 2);


	glBindVertexArray(VaoId);
	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, texture10);
	glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 9);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(102 * sizeof(GLuint)));

	for (int i = 1; i < 7; i++) {
		switch (i) {
		case 1:
			glBindVertexArray(VaoBila1);
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, texture4);
			glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 3);
			break;
		case 2:
			glBindVertexArray(VaoBila2);
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, texture5);
			glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 4);
			break;
		case 3:
			glBindVertexArray(VaoBila3);
			glActiveTexture(GL_TEXTURE5);
			glBindTexture(GL_TEXTURE_2D, texture6);
			glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 5);
			break;
		case 4:
			glBindVertexArray(VaoBila4);
			glActiveTexture(GL_TEXTURE6);
			glBindTexture(GL_TEXTURE_2D, texture7);
			glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 6);
			break;
		case 5:
			glBindVertexArray(VaoBila7);
			glActiveTexture(GL_TEXTURE7);
			glBindTexture(GL_TEXTURE_2D, texture8);
			glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 7);
			break;
		case 6:
			glBindVertexArray(VaoBila8);
			glActiveTexture(GL_TEXTURE8);
			glBindTexture(GL_TEXTURE_2D, texture9);
			glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 8);
			break;
		}

		glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 2);
	}
	glBindVertexArray(VaoBilaAlba);
	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, texture10);
	glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 9);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 2);
	
	glBindVertexArray(VaoTac);
	glActiveTexture(GL_TEXTURE10);
	glBindTexture(GL_TEXTURE_2D, texture11);
	glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 10);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

	

	glutSwapBuffers();
	glFlush();
}




int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);					//	Se folosesc 2 buffere (unul pentru afisare si unul pentru randare => animatii cursive) si culori RGB;
	glutInitWindowSize(winWidth, winHeight);						//  Dimensiunea ferestrei;
	glutInitWindowPosition(100, 100);								//  Pozitia initiala a ferestrei;
	glutCreateWindow("Utilizarea texturarii - OpenGL <<nou>>");		//	Creeaza fereastra de vizualizare, indicand numele acesteia;
	glewInit();
	Initialize();								//  Setarea parametrilor necesari pentru fereastra de vizualizare; 
	glutDisplayFunc(RenderFunction);		//  Desenarea scenei in fereastra;
	glutIdleFunc(RenderFunction);			//	Asigura rularea continua a randarii;
	glutSpecialFunc(ProcessSpecialKeys);
	glutCloseFunc(Cleanup);					//  Eliberarea resurselor alocate de program;
	glutMainLoop();
	return 0;
}