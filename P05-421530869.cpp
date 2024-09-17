#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	rotax = 0.0f;
	rotay = 0.0f;
	rotaz = 0.0f;
	articulacion1 = 0.0f;
	articulacion2 = 0.0f;
	articulacion3 = 0.0f;
	articulacion4 = 0.0f;
	articulacion5 = 0.0f;
	articulacion6 = 0.0f;
	articulacion7 = 0.0f;
	articulacion8 = 0.0f;
	articulacion9 = 0.0f;
	
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
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
	mainWindow = glfwCreateWindow(width, height, "Practica 5: Optimizacion y Carga de Modelos (Gonzalez Villalaba Bryan Jesus - 421530869)", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
							 // Asignar valores de la ventana y coordenadas
							 
							 //Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se está usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}

GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	
	if (key == GLFW_KEY_E)
	{
		theWindow->rotax += 10.0;
	}
	if (key == GLFW_KEY_R)
	{
		theWindow->rotay += 10.0; //rotar sobre el eje y 10 grados
	}
	if (key == GLFW_KEY_T)
	{
		theWindow->rotaz += 10.0;
	}

	// Puerta Delantera y Trasera Derecha
	if (key == GLFW_KEY_F)
	{
		if (theWindow->articulacion1 < 60.0f) {
			theWindow->articulacion1 += 10.0f;

			if (theWindow->articulacion1 > 60.0f) {
				theWindow->articulacion1 = 60.0f;
			}
		}
	}

	if (key == GLFW_KEY_G)
	{
		if (theWindow->articulacion1 > 0.0f) {
			theWindow->articulacion1 -= 10.0f;

			if (theWindow->articulacion1 < 0.0f) {
				theWindow->articulacion1 = 0.0f;
			}
		}
	}

	// Puerta Delantera y Trasera Izquierda
	if (key == GLFW_KEY_H)
	{
		if (theWindow->articulacion2 < 0.0f) {
			theWindow->articulacion2 += 10.0f;

			if (theWindow->articulacion2 > 0.0f) {
				theWindow->articulacion2 = 0.0f;
			}
		}
	}

	if (key == GLFW_KEY_J)
	{
		if (theWindow->articulacion2 > -60.0f) {
			theWindow->articulacion2 -= 10.0f;

			if (theWindow->articulacion2 < -60.0f) {
				theWindow->articulacion2 = -60.0f;
			}
		}
	}
	
	// Cofre
	if (key == GLFW_KEY_K)
	{
		if (theWindow->articulacion3 < 0.0f) {
			theWindow->articulacion3 += 10.0f;

			if (theWindow->articulacion3 > 0.0f) {
				theWindow->articulacion3 = 0.0f;
			}
		}
	}

	if (key == GLFW_KEY_L)
	{
		if (theWindow->articulacion3 > -70.0f) {
			theWindow->articulacion3 -= 10.0f;
			
			if (theWindow->articulacion3 < -70.0f) {
				theWindow->articulacion3 = -70.0f;
			}
		}
	}

	// Cajuela
	if (key == GLFW_KEY_C)
	{
		if (theWindow->articulacion4 < 60.0f) {
			theWindow->articulacion4 += 10.0f;

			if (theWindow->articulacion4 > 60.0f) {
				theWindow->articulacion4 = 60.0f;
			}
		}
	}

	if (key == GLFW_KEY_V)
	{
		if (theWindow->articulacion4 > 0.0f) {
			theWindow->articulacion4 -= 10.0f;

			if (theWindow->articulacion4 < 0.0f) {
				theWindow->articulacion4 = 0.0f;
			}
		}
	}

	// Rueda 1
	if (key == GLFW_KEY_B)
	{
		theWindow->articulacion5 += 10.0;
	}
	if (key == GLFW_KEY_N)
	{
		theWindow->articulacion5 -= 10.0;
	}

	// Rueda 2
	if (key == GLFW_KEY_U)
	{
		theWindow->articulacion6 += 10.0;
	}
	if (key == GLFW_KEY_I)
	{
		theWindow->articulacion6 -= 10.0;
	}

	// Rueda 3
	if (key == GLFW_KEY_O)
	{
		theWindow->articulacion7 += 10.0;
	}
	if (key == GLFW_KEY_P)
	{
		theWindow->articulacion7 -= 10.0;
	}

	// Rueda 4
	if (key == GLFW_KEY_9)
	{
		theWindow->articulacion8 += 10.0;
	}
	if (key == GLFW_KEY_0)
	{
		theWindow->articulacion8 -= 10.0;
	}

	// Carro Movimiento
	if (key == GLFW_KEY_1)
	{
		if (theWindow->articulacion9 < 100.0f) {
			theWindow->articulacion9 += 1.0f;

			if (theWindow->articulacion9 > 100.0f) {
				theWindow->articulacion9 = 100.0f;
			}
		}
	}

	if (key == GLFW_KEY_2)
	{
		if (theWindow->articulacion9 > -100.0f) {
			theWindow->articulacion9 -= 1.0f;

			if (theWindow->articulacion9 < -100.0f) {
				theWindow->articulacion9 = -100.0f;
			}
		}
	}

	

	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0);
		//printf("se presiono la tecla: %s\n",key_name);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//printf("se presiono la tecla %d'\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//printf("se solto la tecla %d'\n", key);
		}
	}
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}
