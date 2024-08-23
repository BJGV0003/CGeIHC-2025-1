// Numero de cuenta: 421530869		Nombre: Gonzalez Villalaba Bryan Jesus		Maquina: 2		Nombre del trabajo: Configuracion //
#include <stdio.h>
#include <string.h>
#include <glew.h>
#include <glfw3.h>

#include <stdlib.h> // Para rand() y srand()
#include <time.h>   // Para time()
#include <windows.h> // Para Sleep()

//Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 600;
GLuint VAO, VBO, shader;

//Vertex Shader
//recibir color, salida Vcolor
static const char* vShader = "						\n\
#version 330										\n\
layout (location =0) in vec3 pos;					\n\
void main()											\n\
{													\n\
gl_Position=vec4(pos.x,pos.y,pos.z,1.0f); 			\n\
}";
//recibir Vcolor y dar de salida color
static const char* fShader = "						\n\
#version 330										\n\
out vec4 color;										\n\
void main()											\n\
{													\n\
	color = vec4(0.5f,1.0f,0.4f,1.0f);	 			\n\
}";



void CrearTriangulo()
{
	GLfloat vertices[] = { // Y (Derecha e Izquierda) X (Arriba y Abajo) Z (Profundidad)
		// Letra B
		-0.9f,0.3f,0.0f, //Punto A
		-0.9f,0.0f,0.0f, //Punto B
		-0.8f,0.0f,0.0f, //Pnto C
		-0.9f,0.3f,0.0f, //Punto A
		-0.8f,0.0f,0.0f, //Pnto C
		-0.8f,0.3f,0.0f, //Pnto D
		-0.9f,0.0f,0.0f, //Punto B
		-0.8f,0.0f,0.0f, //Pnto C
		-0.9f,-0.3f,0.0f, //Punto E
		-0.8f,0.0f,0.0f, //Pnto C
		-0.9f,-0.3f,0.0f, //Punto E
		-0.8f,-0.3f,0.0f, //Pnto F
		-0.8f,0.3f,0.0f, //Pnto D
		-0.5f,0.3f,0.0f, //Pnto G
		-0.5f,0.2f,0.0f, //Pnto H
		-0.8f,0.3f,0.0f, //Pnto D
		-0.5f,0.2f,0.0f, //Pnto H
		-0.8f,0.2f,0.0f, //Pnto I
		-0.5f,0.2f,0.0f, //Pnto H
		-0.5f,0.0f,0.0f, //Pnto J
		-0.6f,0.0f,0.0f, //Pnto K
		-0.5f,0.2f,0.0f, //Pnto H
		-0.6f,0.0f,0.0f, //Pnto K
		-0.6f,0.2f,0.0f, //Pnto L
		-0.5f,0.0f,0.0f, //Pnto J
		-0.6f,0.0f,0.0f, //Pnto K
		-0.5f,-0.3f,0.0f, //Pnto M
		-0.6f,00.0f,0.0f, //Pnto K
		-0.5f,-0.3f,0.0f, //Pnto M
		-0.6f,-0.3f,0.0f, //Pnto N
		-0.5f,-0.3f,0.0f, //Pnto M
		-0.5f,-0.2f,0.0f, //Pnto O
		-0.9f,-0.2f,0.0f, //Pnto P
		-0.9f,-0.3f,0.0f, //Punto E
		-0.5f,-0.3f,0.0f, //Pnto M
		-0.9f,-0.2f,0.0f, //Pnto P
		-0.5f,0.0f,0.0f, //Pnto J
		-0.5f,0.06f,0.0f, //Pnto Q
		-0.9f,0.06f,0.0f, //Pnto R
		-0.9f,0.0f,0.0f, //Punto B
		-0.5f,0.0f,0.0f, //Pnto J
		-0.9f,0.06f,0.0f, //Pnto R

		// Letra J
		-0.3f,0.3f,0.0f, //Pnto A
		0.3f,0.3f,0.0f, //Pnto B
		-0.3f,0.2f,0.0f, //Pnto C
		0.3f,0.3f,0.0f, //Pnto B
		-0.3f,0.2f,0.0f, //Pnto C
		0.3f,0.2f,0.0f, //Pnto D
		0.0f,0.2f,0.0f, //Pnto E
		0.0f,-0.3f,0.0f, //Pnto F
		0.1f,-0.3f,0.0f, //Pnto G
		0.0f,0.2f,0.0f, //Pnto E
		0.1f,-0.3f,0.0f, //Pnto G
		0.1f,0.2f,0.0f, //Pnto H
		0.0f,-0.3f,0.0f, //Pnto F
		-0.26f,-0.3f,0.0f, //Pnto I
		-0.26f,-0.22f,0.0f, //Pnto J
		0.0f,-0.3f,0.0f, //Pnto F
		-0.26f,-0.22f,0.0f, //Pnto J
		0.0f,-0.22f,0.0f, //Pnto K

		// Letra G
		0.5f,0.3f,0.0f, //Pnto A
		0.6f,0.3f,0.0f, //Pnto B
		0.5f,-0.3f,0.0f, //Pnto C
		0.6f,0.3f,0.0f, //Pnto B
		0.5f,-0.3f,0.0f, //Pnto C
		0.6f,-0.3f,0.0f, //Pnto D
		0.6f,-0.3f,0.0f, //Pnto D
		0.9f,-0.3f,0.0f, //Pnto E
		0.9f,-0.2f,0.0f, //Pnto F
		0.6f,-0.3f,0.0f, //Pnto D
		0.9f,-0.2f,0.0f, //Pnto F
		0.6f,-0.2f,0.0f, //Pnto G
		0.9f,-0.2f,0.0f, //Pnto F
		0.9f,0.0f,0.0f, //Pnto H
		0.8f,0.0f,0.0f, //Pnto I
		0.9f,-0.2f,0.0f, //Pnto F
		0.8f,0.0f,0.0f, //Pnto I
		0.8f,-0.2f,0.0f, //Pnto J
		0.8f,0.0f,0.0f, //Pnto I
		0.7f,0.0f,0.0f, //Pnto K
		0.7f,-0.06f,0.0f, //Pnto L
		0.8f,0.0f,0.0f, //Pnto I
		0.7f,-0.06f,0.0f, //Pnto L
		0.8f,-0.06f,0.0f, //Pnto M
		0.7f,-0.06f,0.0f, //Pnto L
		0.7f,-0.14f,0.0f, //Pnto N
		0.76f,-0.14f,0.0f, //Pnto O
		0.7f,-0.06f,0.0f, //Pnto L
		0.76f,-0.14f,0.0f, //Pnto O
		0.76f,-0.06f,0.0f, //Pnto P
		0.6f,0.3f,0.0f, //Pnto B
		0.9f,0.3f,0.0f, //Pnto Q
		0.9f,0.22f,0.0f, //Pnto R
		0.6f,0.3f,0.0f, //Pnto B
		0.9f,0.22f,0.0f, //Pnto R
		0.6f, 0.22f, 0.0f, //Pnto S	

	};
	glGenVertexArrays(1, &VAO); //generar 1 VAO
	glBindVertexArray(VAO);//asignar VAO

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //pasarle los datos al VBO asignando tamano, los datos y en este caso es estático pues no se modificarán los valores

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);//Stride en caso de haber datos de color por ejemplo, es saltar cierta cantidad de datos
		glEnableVertexAttribArray(0);
		//agregar valores a vèrtices y luego declarar un nuevo vertexAttribPointer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

}
void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) //Función para agregar los shaders a la tarjeta gráfica
//the Program recibe los datos de theShader


{
	GLuint theShader = glCreateShader(shaderType);//theShader es un shader que se crea de acuerdo al tipo de shader: vertex o fragment
	const GLchar* theCode[1];
	theCode[0] = shaderCode;//shaderCode es el texto que se le pasa a theCode
	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);//longitud del texto
	glShaderSource(theShader,1, theCode, codeLength);//Se le asigna al shader el código
	glCompileShader(theShader);//Se comila el shader
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	//verificaciones y prevención de errores
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al compilar el shader %d es: %s \n",shaderType, eLog);
		return;
	}
	glAttachShader(theProgram, theShader);//Si no hubo problemas se asigna el shader a theProgram el cual asigna el código a la tarjeta gráfica
}

void CompileShaders() {
	shader= glCreateProgram(); //se crea un programa
	if (!shader)
	{
		printf("Error creando el shader");
		return;
	}
	AddShader(shader, vShader, GL_VERTEX_SHADER);//Agregar vertex shader
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);//Agregar fragment shader
	//Para terminar de linkear el programa y ver que no tengamos errores
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	glLinkProgram(shader);//se linkean los shaders a la tarjeta gráfica
	 //verificaciones y prevención de errores
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al linkear es: %s \n", eLog);
		return;
	}
	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al validar es: %s \n", eLog);
		return;
	}



}
int main()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Primer ventana", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	int BufferWidth, BufferHeight;
	glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Asignar valores de la ventana y coordenadas
	//Asignar Viewport
	glViewport(0, 0, BufferWidth, BufferHeight);

 //Crear tríangulo
	CrearTriangulo();
	CompileShaders();


	//Loop mientras no se cierra la ventana
	while (!glfwWindowShouldClose(mainWindow))
	{
		//Recibir eventos del usuario
		glfwPollEvents();

		//Cambio_Color_Pantalla
		srand(time(NULL)); // Inicializa la semilla para los números aleatorios
		Sleep(2000);
		float rojo = (float)rand() / RAND_MAX; // Genera un número aleatorio entre 0.0 y 1.0
		float verde = (float)rand() / RAND_MAX;
		float azul = (float)rand() / RAND_MAX;

		//Limpiar la ventana
		glClearColor(rojo,verde,azul,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES,0,100);
		glBindVertexArray(0);

		glUseProgram(0);

		glfwSwapBuffers(mainWindow);

	}


	return 0;
}