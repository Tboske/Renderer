#include "Window.h"

#include <GLFW/glfw3.h>

void errorCallback(int error, const char* description)
{
	spdlog::error("Error: {}\n", description);
}

Window::Window(std::string_view windowName)
{
	glfwSetErrorCallback(errorCallback);

	if (!glfwInit())
		spdlog::critical("Failed to Init glfw3");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    m_pWindow = glfwCreateWindow(m_Size.x, m_Size.y, windowName.data(), NULL, NULL);
    if (!m_pWindow)
        throw "Failed to initialize window";        

    glfwMakeContextCurrent(m_pWindow);
    glfwSwapInterval(0); // enable vsync


    // this should still move to its own inputmanager
	glfwSetKeyCallback(m_pWindow, InputCallBack);
}

Window::~Window()
{
    glfwDestroyWindow(m_pWindow);
    
	glfwTerminate();
}

bool Window::ShouldEnd() const 
{
    return glfwWindowShouldClose(m_pWindow);
}

void Window::InputCallBack(GLFWwindow* pWindow, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(pWindow, GLFW_TRUE);
}