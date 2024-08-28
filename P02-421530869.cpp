// "Practica 2: Proyecciones, transformaciones (Gonzalez Villalaba Bryan Jesus - 421530869)"
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
static const char* FRojo = "shaders/FRojo.frag";
static const char* VRojo = "shaders/VRojo.vert";
static const char* FVerde = "shaders/FVerde.frag";
static const char* VVerde = "shaders/VVerde.vert";
static const char* FAzul = "shaders/FAzul.frag";
static const char* VAzul = "shaders/VAzul.vert";
static const char* FCafe = "shaders/FCafe.frag";
static const char* VCafe = "shaders/VCafe.vert";
static const char* FVerdeOscuro = "shaders/FVerdeOscuro.frag";
static const char* VVerdeOscuro = "shaders/VVerdeOscuro.vert";

float angulo = 0.0f;

//color café en RGB : 0.478, 0.255, 0.067

//Pirámide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = { 
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3
		
	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12); // Para la matriz es 0,1,2,3 por 4 = 12
	meshList.push_back(obj1);
}

//Vértices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

GLfloat cubo_vertices[] = {
	// front
	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	// back
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f
};
Mesh *cubo = new Mesh();
cubo->CreateMesh(cubo_vertices, cubo_indices,24, 36);
meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{
	GLfloat vertices_letras[] = {	
			//X			Y			Z			R		G		B
		// Letra B 14 * 18 = 252
		-0.9f,0.9f,0.0f, 0.0f,0.0f,1.0f, //Punto A
		-0.9f,0.7f,0.0f, 0.0f,0.0f,1.0f, //Punto B
		-0.8f,0.7f,0.0f, 0.0f,0.0f,1.0f, //Pnto C

		-0.9f,0.9f,0.0f, 0.0f,0.0f,1.0f, //Punto A
		-0.8f,0.7f,0.0f, 0.0f,0.0f,1.0f, //Pnto C
		-0.8f,0.9f,0.0f, 0.0f,0.0f,1.0f, //Pnto D

		-0.9f,0.7f,0.0f, 0.0f,0.0f,1.0f, //Punto B
		-0.8f,0.7f,0.0f, 0.0f,0.0f,1.0f, //Pnto C
		-0.9f,0.5f,0.0f, 0.0f,0.0f,1.0f, //Punto E

		-0.8f,0.7f,0.0f, 0.0f,0.0f,1.0f, //Pnto C
		-0.9f,0.5f,0.0f, 0.0f,0.0f,1.0f, //Punto E
		-0.8f,0.5f,0.0f, 0.0f,0.0f,1.0f, //Punto F

		-0.8f,0.9f,0.0f, 0.0f,0.0f,1.0f, //Punto D
		-0.5f,0.9f,0.0f, 0.0f,0.0f,1.0f, //Punto G
		-0.5f,0.85f,0.0f, 0.0f,0.0f,1.0f, //Punto H

		-0.8f,0.9f,0.0f, 0.0f,0.0f,1.0f, //Punto D
		-0.5f,0.85f,0.0f, 0.0f,0.0f,1.0f, //Punto H
		-0.8f,0.85f,0.0f, 0.0f,0.0f,1.0f, //Punto I

		-0.5f,0.85f,0.0f, 0.0f,0.0f,1.0f, //Punto H
		-0.5f,0.7f,0.0f, 0.0f,0.0f,1.0f, //Punto J
		-0.6f,0.7f,0.0f, 0.0f,0.0f,1.0f, //Punto K

		-0.5f,0.85f,0.0f, 0.0f,0.0f,1.0f, //Punto H
		-0.6f,0.7f,0.0f, 0.0f,0.0f,1.0f, //Punto K
		-0.6f,0.85f,0.0f, 0.0f,0.0f,1.0f, //Punto L

		-0.5f,0.7f,0.0f, 0.0f,0.0f,1.0f, //Punto J
		-0.6f,0.7f,0.0f, 0.0f,0.0f,1.0f, //Punto K
		-0.5f,0.5f,0.0f, 0.0f,0.0f,1.0f, //Punto M

		-0.6f,0.7f,0.0f, 0.0f,0.0f,1.0f, //Punto K
		-0.5f,0.5f,0.0f, 0.0f,0.0f,1.0f, //Punto M
		-0.6f,0.5f,0.0f, 0.0f,0.0f,1.0f, //Punto N

		-0.5f,0.5f,0.0f, 0.0f,0.0f,1.0f, //Punto M
		-0.5f,0.6f,0.0f, 0.0f,0.0f,1.0f, //Punto O
		-0.9f,0.5f,0.0f, 0.0f,0.0f,1.0f, //Punto P

		-0.9f,0.6f,0.0f, 0.0f,0.0f,1.0f, //Punto E
		-0.5f,0.6f,0.0f, 0.0f,0.0f,1.0f, //Punto O
		-0.9f,0.5f,0.0f, 0.0f,0.0f,1.0f, //Punto P

		-0.5f,0.65f,0.0f, 0.0f,0.0f,1.0f, //Punto J
		-0.5f,0.75f,0.0f, 0.0f,0.0f,1.0f, //Punto Q
		-0.9f,0.75f,0.0f, 0.0f,0.0f,1.0f, //Punto R

		-0.9f,0.65f,0.0f, 0.0f,0.0f,1.0f, //Punto B
		-0.5f,0.65f,0.0f, 0.0f,0.0f,1.0f, //Punto J
		-0.9f,0.75f,0.0f, 0.0f,0.0f,1.0f, //Punto R


		// Letra J 6 * 18 = 108
		-0.2f,0.9f,0.0f, 0.0f,1.0f,0.0f, //Punto A
		0.2f,0.9f,0.0f, 0.0f,1.0f,0.0f, //Punto B
		-0.2f,0.8f,0.0f, 0.0f,1.0f,0.0f, //Punto C

		0.2f,0.9f,0.0f, 0.0f,1.0f,0.0f, //Punto B
		-0.2f,0.8f,0.0f, 0.0f,1.0f,0.0f, //Punto C
		0.2f,0.8f,0.0f, 0.0f,1.0f,0.0f, //Punto D

		0.0f,0.8f,0.0f, 0.0f,1.0f,0.0f, //Punto E
		0.0f,0.5f,0.0f, 0.0f,1.0f,0.0f, //Punto F
		0.1f,0.5f,0.0f, 0.0f,1.0f,0.0f, //Punto G

		0.0f,0.8f,0.0f, 0.0f,1.0f,0.0f, //Punto E
		0.1f,0.5f,0.0f, 0.0f,1.0f,0.0f, //Punto G
		0.1f,0.8f,0.0f, 0.0f,1.0f,0.0f, //Punto H

		0.0f,0.5f,0.0f, 0.0f,1.0f,0.0f, //Punto F
		-0.20f,0.5f,0.0f, 0.0f,1.0f,0.0f, //Punto I
		-0.20f,0.55f,0.0f, 0.0f,1.0f,0.0f, //Pnto J

		0.0f,0.5f,0.0f, 0.0f,1.0f,0.0f, //Punto F
		-0.20f,0.55f,0.0f, 0.0f,1.0f,0.0f, //Pnto J
		0.0f,0.55f,0.0f, 0.0f,	1.0f,0.0f, //Punto K


		// Letra G 12 * 18 = 216
		0.5f,0.9f,0.0f, 1.0f,0.0f,0.0f, //Punto A
		0.6f,0.9f,0.0f, 1.0f,0.0f,0.0f, //Punto B
		0.5f,0.5f,0.0f, 1.0f,0.0f,0.0f, //Punto C

		0.6f,0.9f,0.0f, 1.0f,0.0f,0.0f, //Punto B
		0.5f,0.5f,0.0f, 1.0f,0.0f,0.0f, //Punto C
		0.6f,0.5f,0.0f, 1.0f,0.0f,0.0f, //Punto D

		0.6f,0.5f,0.0f, 1.0f,0.0f,0.0f, //Punto D
		0.9f,0.55f,0.0f, 1.0f,0.0f,0.0f, //Punto E
		0.9f,0.50f,0.0f, 1.0f,0.0f,0.0f, //Punto F

		0.6f,0.5f,0.0f, 1.0f,0.0f,0.0f, //Punto D
		0.9f,0.55f,0.0f, 1.0f,0.0f,0.0f, //Punto F
		0.6f,0.55f,0.0f, 1.0f,0.0f,0.0f, //Punto G

		0.9f, 0.55f, 0.0f, 1.0f, 0.0f, 0.0f, //Punto F
		0.9f,0.65f,0.0f, 1.0f,0.0f,0.0f, //Punto H
		0.85f,0.65f,0.0f, 1.0f,0.0f,0.0f, //Punto I

		0.9f, 0.55f, 0.0f, 1.0f, 0.0f, 0.0f, //Punto F
		0.85f, 0.65f, 0.0f, 1.0f, 0.0f, 0.0f, //Punto I
		0.85f,0.55f,0.0f, 1.0f,0.0f,0.0f, //Pnto J

		0.85f, 0.65f, 0.0f, 1.0f, 0.0f, 0.0f, //Punto I
		0.75f,0.65f,0.0f, 1.0f,0.0f,0.0f, //Punto K
		0.75f,0.60f,0.0f, 1.0f,0.0f,0.0f, //Punto L

		0.85f, 0.65f, 0.0f, 1.0f, 0.0f, 0.0f, //Punto I
		0.75f, 0.60f, 0.0f, 1.0f, 0.0f, 0.0f, //Punto L
		0.85f,0.60f,0.0f, 1.0f,	0.0f,0.0f, //Punto M

		0.75f, 0.60f, 0.0f, 1.0f, 0.0f, 0.0f, //Punto L
		0.77f,0.58f,0.0f, 1.0f,	0.0f,0.0f, //Punto N
		0.75f,0.58f,0.0f, 1.0f,0.0f,0.0f, //Punto O

		0.75f, 0.60f, 0.0f, 1.0f, 0.0f, 0.0f, //Punto L
		0.77f, 0.58f, 0.0f, 1.0f, 0.0f, 0.0f, //Punto O
		0.77f,0.60f,0.0f, 1.0f,0.0f,0.0f, //Punto P

		0.6f,0.9f,0.0f, 1.0f,0.0f,0.0f, //Punto B
		0.9f,0.9f,0.0f, 1.0f,0.0f,0.0f, //Punto Q
		0.9f,0.85f,0.0f, 1.0f,0.0f,0.0f, //Punto R

		0.6f,0.9f,0.0f,  1.0f,0.0f,0.0f, //Punto B
		0.9f,0.85f,0.0f, 1.0f,0.0f,0.0f, //Punto R
		0.6f,0.85f,0.0f, 1.0f,0.0f,0.0f, //Punto S
			
	};
	MeshColor *letras = new MeshColor();
	letras->CreateMeshColor(vertices_letras,576);
	meshColorList.push_back(letras);

	GLfloat vertices_figuras[] = {
		//X			Y			Z			R		G		B
		0.0f,	0.0f,		0.0f,			0.0f,	0.0f,	1.0f, // Triangulo azul
		0.0f,	0.0f,		0.0f,			0.0f,	0.0f,	1.0f,
		0.0f,	0.0f,		0.0f,			0.0f,	0.0f,	1.0f,

		/*-1.3f,	0.8f,		0.5f,			0.0f,	0.0f,	1.0f, // Triangulo azul
		1.3f,	0.8f,		0.5f,			0.0f,	0.0f,	1.0f,
		0.0f,	1.8f,		0.5f,			0.0f,	0.0f,	1.0f,

		-1.9f,	-0.9f,		0.5f,			0.0f,	0.5f,	0.0f, // Triangulo verde 1
		-1.5f,	-0.9f,		0.5f,			0.0f,	0.5f,	0.0f,
		-1.7f,	0.0f,		0.5f,			0.0f,	0.5f,	0.0f,

		1.9f,	-0.9f,		0.5f,			0.0f,	0.5f,	0.0f, // Triangulo verde 2
		1.5f,	-0.9f,		0.5f,			0.0f,	0.5f,	0.0f,
		1.7f,	0.0f,		0.5f,			0.0f,	0.5f,	0.0f,

		-1.1f,	0.8f,		0.5f,			1.0f,	0.0f,	0.0f, // Triangulo 1 de cuadrado rojo
		1.1f,	0.8f,		0.5f,			1.0f,	0.0f,	0.0f,
		1.1f,	-1.8f,		0.5f,			1.0f,	0.0f,	00.0f,

		-1.1f,	0.8f,		0.5f,			1.0f,	0.0f,	0.0f, // Triangulo 2 de cuadrado rojo
		1.1f,	-1.8f,		0.5f,			1.0f,	0.0f,	0.0f,
		-1.1f,	-1.8f,		0.5f,			1.0f,	0.0f,	00.0f,

		-1.8f,	-0.9f,		0.5f,			0.478f,	0.255f,	0.067f, // Triangulo 1 de cuadrado cafe 1
		-1.6f,	-0.9f,		0.5f,			0.478f,	0.255f,	0.067f,
		-1.6f,	-1.8f,		0.5f,			0.478f,	0.255f,	0.067f,

		-1.8f,	-0.9f,		0.5f,			0.478f,	0.255f,	0.067f, // Triangulo 2 de cuadrado cafe 1
		-1.8f,	-1.8f,		0.5f,			0.478f,	0.255f,	0.067f,
		-1.6f,	-1.8f,		0.5f,			0.478f,	0.255f,	0.067f,

		1.8f,	-0.9f,		0.5f,			0.478f,	0.255f,	0.067f, // Triangulo 1 de cuadrado cafe 2
		1.8f,	-1.8f,		0.5f,			0.478f,	0.255f,	0.067f,
		1.6f,	-1.8f,		0.5f,			0.478f,	0.255f,	0.067f,

		1.8f,	-0.9f,		0.5f,			0.478f,	0.255f,	0.067f, // Triangulo 2 de cuadrado cafe 2
		1.6f,	-0.9f,		0.5f,			0.478f,	0.255f,	0.067f,
		1.6f,	-1.8f,		0.5f,			0.478f,	0.255f,	0.067f,

		-0.3f,	0.6f,		0.6f,			0.0f,	1.0f,	0.0f, // Triangulo 1 de cuadrado verde 1
		-0.9f,	0.6f,		0.6f,			0.0f,	1.0f,	0.0f,
		-0.9f,	0.0f,		0.6f,			0.0f,	1.0f,	0.0f,

		-0.3f,	0.6f,		0.6f,			0.0f,	1.0f,	0.0f, // Triangulo 2 de cuadrado verde 1
		-0.3f,	0.0f,		0.6f,			0.0f,	1.0f,	0.0f,
		-0.9f,	0.0f,		0.6f,			0.0f,	1.0f,	0.0f,

		0.3f,	0.6f,		0.6f,			0.0f,	1.0f,	0.0f, // Triangulo 1 de cuadrado verde 2
		0.9f,	0.6f,		0.6f,			0.0f,	1.0f,	0.0f,
		0.9f,	0.0f,		0.6f,			0.0f,	1.0f,	0.0f,

		0.3f,	0.6f,		0.6f,			0.0f,	1.0f,	0.0f, // Triangulo 2 de cuadrado verde 2
		0.3f,	0.0f,		0.6f,			0.0f,	1.0f,	0.0f,
		0.9f,	0.0f,		0.6f,			0.0f,	1.0f,	0.0f,

		-0.3f,	-0.8f,		0.6f,			0.0f,	1.0f,	0.0f, // Triangulo 1 de cuadrado verde 3
		0.3f,	-0.8f,		0.6f,			0.0f,	1.0f,	0.0f,
		0.3f,	-1.7f,		0.6f,			0.0f,	1.0f,	0.0f,

		-0.3f,	-0.8f,		0.6f,			0.0f,	1.0f,	0.0f, // Triangulo 2 de cuadrado verde 3
		-0.3f,	-1.7f,		0.6f,			0.0f,	1.0f,	0.0f,
		0.3f,	-1.7f,		0.6f,			0.0f,	1.0f,	0.0f,    270 puntos */
		
	};

	MeshColor* figuras= new MeshColor();
	figuras->CreateMeshColor(vertices_figuras,18);
	meshColorList.push_back(figuras);

	GLfloat vertices_cuadrados[] = {
		//X			Y			Z			R		G		B
		-1.1f,	0.8f,		0.5f,			1.0f,	0.0f,	0.0f,
		1.1f,	0.8f,		0.5f,			1.0f,	0.0f,	0.0f,
		1.1f,	-0.8f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,

	};

	MeshColor* cuadrados = new MeshColor();
	cuadrados->CreateMeshColor(vertices_cuadrados, 36);
	meshColorList.push_back(cuadrados);

}


void CreateShaders()
{

	Shader* shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1); //Aquí hace que shaderList[0]	

	Shader* shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);

	Shader* shader3 = new Shader();
	shader3->CreateFromFiles(VRojo, FRojo);
	shaderList.push_back(*shader3); //2

	Shader* shader4 = new Shader();
	shader4->CreateFromFiles(VVerde, FVerde);
	shaderList.push_back(*shader4); //3

	Shader* shader5 = new Shader();
	shader5->CreateFromFiles(VAzul, FAzul);
	shaderList.push_back(*shader5); //4

	Shader* shader6 = new Shader();
	shader6->CreateFromFiles(VCafe, FCafe);
	shaderList.push_back(*shader6); //5

	Shader* shader7 = new Shader();
	shader7->CreateFromFiles(VVerdeOscuro, FVerdeOscuro);
	shaderList.push_back(*shader7); //6
}


int main()
{
	mainWindow = Window(800, 800);
	mainWindow.Initialise();
	CreaPiramide(); //índice 0 en MeshList
	CrearCubo();//índice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	
	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad
	
	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(1.0f,1.0f,1.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		
													
		//Para las letras hay que usar el segundo set de shaders con índice 1 en ShaderList 
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[0]->RenderMeshColor();

		//Para el cubo y la pirámide se usa el primer set de shaders con índice 0 en ShaderList
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		angulo += 0.01;

		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas

		//Letras
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[1]->RenderMeshColor();
		
		//Cubo de casa
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.3f, -2.0f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//Piramide de techo
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.25f, -1.8f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.2f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		// Piramide de arbol 1
		shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.8f, -0.3f, -1.8f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//Cubo de arbol 1
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.8f, -0.6f, -1.85f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		// Piramide de arbol 2
		shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.8f, -0.3f, -1.8f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.4f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//Cubo de arbol 2
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.8f, -0.6f, -1.85f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//Cubo de ventana 1
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.26f, -0.1f, -1.0f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.17f, 0.17f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//Cubo de ventana 2
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.26f, -0.1f, -1.0f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.17f, 0.17f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//Cubo de puerta
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.6f, -1.0f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.17f, 0.19f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();
		
		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslación
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACIÓN //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/