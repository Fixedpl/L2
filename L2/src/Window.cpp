
#include "gl.h"
#include "Window.h"
#include "Renderer.h"


std::array<bool, 350> Window::m_Keys;


bool Window::m_leftClick = false;
bool Window::m_rightClick = false;

double Window::m_lastCursorX = 0.0;
double Window::m_lastCursorY = 0.0;

Window::Window(const uint32_t& windowWidth, const uint32_t& windowHeight, const std::string& windowTitle)
: 
m_window_width(windowWidth), 
m_window_height(windowHeight),
m_window_title(windowTitle), 
m_VSync(true)
{
	windowInit();
}

Window::~Window()
{
}

void glfwError(int id, const char* description)
{
	std::cout << description << std::endl;
}

void Window::keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
		m_Keys[key] = true;
	if (action == GLFW_RELEASE)
		m_Keys[key] = false;
}

void Window::mouseCallback(GLFWwindow* window, int button, int action, int mods)
{
	glfwGetCursorPos(window, &m_lastCursorX, &m_lastCursorY);

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_leftClick = true;
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		m_leftClick = false;

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		m_rightClick = true;
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
		m_rightClick = false;
}


void Window::windowInit()
{

	glfwSetErrorCallback(glfwError);
	if (!glfwInit()) {
		std::cout << "ERROR: Couldn't initialize GLFW." << std::endl;
	}
		
		
	window = glfwCreateWindow(m_window_width, m_window_height, m_window_title.c_str(), NULL, NULL);
	if (!window) {
		glfwTerminate();
		std::cout << "ERROR: Couldn't create window." << std::endl;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cout << "ERROR: Couldnt initialize GLEW" << std::endl;
	}


	// On default VSync ON
	glfwSwapInterval(1);

	glfwSetMouseButtonCallback(window, mouseCallback);
	glfwSetKeyCallback(window, keyboardCallback);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.6f, 0.4f, 0.3f, 1.0f);
}

void Window::windowLoop()
{
	float currentTime = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		float newTime = glfwGetTime();
		float frameTime = newTime - currentTime;
		currentTime = newTime;

		onDraw(frameTime);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}



unsigned int Window::getWidth() const {
	return m_window_width;
}

unsigned int Window::getHeight() const {
	return m_window_height;
}

void Window::setVSync(const bool& value)
{
	m_VSync = value;
	if (m_VSync)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);
}

bool Window::isKeyPressed(const uint32_t& key)
{
	return m_Keys[key];
}

bool Window::isLeftMousePressed()
{
	return m_leftClick;
}

bool Window::isRightMousePressed()
{
	return m_rightClick;
}

glm::vec2 Window::getLastMousePosition()
{
	return glm::vec2(m_lastCursorX, m_window_height - m_lastCursorY - 1);
}


void Window::display()
{
	windowLoop();
}

