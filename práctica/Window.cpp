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
	articulacion10 = 0.0f;

	direccion7 = false;
	direccion9 = true;
	direccion = glm::vec3(0.0f, 0.0f, 0.0f);
	
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialize()
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
	mainWindow = glfwCreateWindow(width, height, "Practica 7: Iluminacion 1", NULL, NULL);

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
	// KEYBOARD
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	// MOUSE POSITION
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
	// MOUSE BUTTONS
	glfwSetMouseButtonCallback(mainWindow, MouseButtons);
	// MOUSE SCROLL
	glfwSetScrollCallback(mainWindow, ManejaScroll);
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

GLfloat Window::getYScrollChange()
{
	GLfloat theChange = yScrollChange;
	yScrollChange = 0.0f;
	return theChange;
}

void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->getMouseButtons()[GLFW_MOUSE_BUTTON_RIGHT] == 0) {
		// rotación de las ruedas delanteras
		if (key == GLFW_KEY_W && action)
		{
			theWindow->rotax += 10.0;
			theWindow->direccion += glm::vec3(0.0f, 0.0f, -0.1f);
		}
		if (key == GLFW_KEY_S && action)
		{
			theWindow->rotax -= 10.0;
			theWindow->direccion += glm::vec3(0.0f, 0.0f, 0.1f);
		}
		// rotación de las ruedas delanteras hacia los lados en y con limite
		// de 70 grados
		if (key == GLFW_KEY_A && action)
		{
			theWindow->direccion += glm::vec3(0.f, -0.1f, 0.f);
			if (theWindow->rotay >= 70.0f) {
				theWindow->rotay = 70.0f;
			}
			else
			{
				theWindow->rotay += 10.0;
			}
		}
		if (key == GLFW_KEY_D && action)
		{
			theWindow->direccion += glm::vec3(0.f, 0.1f, 0.f);
			if (theWindow->rotay <= -70.0f) {
				theWindow->rotay = -70.0f;
			}
			else
			{
				theWindow->rotay -= 10.0;
			}
		}
	}
	

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_E)
	{
		theWindow->rotax += 10.0;
	}
	if (key == GLFW_KEY_Q)
	{
		theWindow->rotay += 10.0; //rotar sobre el eje y 10 grados
	}
	if (key == GLFW_KEY_T)
	{
		theWindow->rotaz += 10.0;
	}
	if (key == GLFW_KEY_F)
	{
		theWindow->articulacion1 += 10.0;
	}
	if (key == GLFW_KEY_G)
	{
		theWindow->articulacion2 += 10.0;
	}
	if (key == GLFW_KEY_H)
	{
		theWindow->articulacion3 += 10.0;
	}
	if (key == GLFW_KEY_J)
	{
		theWindow->articulacion4 += 10.0;
	}
	if (key == GLFW_KEY_K)
	{
		theWindow->articulacion5 += 10.0;
	}
	if (key == GLFW_KEY_L)
	{
		theWindow->articulacion6 += 10.0;
	}if (key == GLFW_KEY_C)
	{
		if (theWindow->articulacion7 >= 90.0f) {
			theWindow->direccion7 = true;
		}
		else if (theWindow->articulacion7 <= 0.f)
		{
			theWindow->direccion7 = false;
		}
		if (theWindow->direccion7) theWindow->articulacion7 -= 10.0;
		
		else theWindow->articulacion7 += 10.0;
	}
	if (key == GLFW_KEY_V)
	{
		theWindow->articulacion8 += 10.0;
	}
	if (key == GLFW_KEY_B)
	{
		if (theWindow->articulacion9 >= 40.0f) {
			theWindow->direccion9 = true;
		}
		else if (theWindow->articulacion9 <= -40.f)
		{
			theWindow->direccion9 = false;
		}
		if (theWindow->direccion9) theWindow->articulacion9 -= 10.0;

		else theWindow->articulacion9 += 10.0;
	}
	if (key == GLFW_KEY_N)
	{
		theWindow->articulacion10 += 10.0;
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

void Window::MouseButtons(GLFWwindow* window, int button, int action, int mods)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	theWindow->mouseButtons[GLFW_MOUSE_BUTTON_RIGHT] = 0;
	theWindow->mouseButtons[GLFW_MOUSE_BUTTON_MIDDLE] = 0;
	theWindow->mouseButtons[GLFW_MOUSE_BUTTON_LEFT] = 0;
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		theWindow->mouseButtons[GLFW_MOUSE_BUTTON_RIGHT] = 1;
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
	{
		theWindow->mouseButtons[GLFW_MOUSE_BUTTON_RIGHT] = 0;
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		theWindow->mouseButtons[GLFW_MOUSE_BUTTON_LEFT] = 1;
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		theWindow->mouseButtons[GLFW_MOUSE_BUTTON_LEFT] = 0;
	}
	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
	{
		theWindow->mouseButtons[GLFW_MOUSE_BUTTON_MIDDLE] = 1;
	}
	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
	{
		theWindow->mouseButtons[GLFW_MOUSE_BUTTON_MIDDLE] = 0;
	}
}

void Window::ManejaScroll(GLFWwindow* window, double xOffSet, double yOffSet)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	theWindow->yScrollChange = yOffSet;
	if (theWindow->yScrollChange < -10.0f)
	{
		theWindow->yScrollChange = -10.0f;
	}
	if (theWindow->yScrollChange > 64.0f)
	{
		theWindow->yScrollChange = 64.0f;
	}
}

Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}
