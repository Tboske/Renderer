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

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_pWindow = glfwCreateWindow(m_Size.x, m_Size.y, windowName.data(), nullptr, nullptr);
    if (!m_pWindow)
        throw "Failed to initialize window";        

    // glfwSwapInterval(0); // enable vsync
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

void Window::PollWindowEvents() const
{
    glfwPollEvents();
}