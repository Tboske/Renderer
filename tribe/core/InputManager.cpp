#include "InputManager.h"

#include <GLFW/glfw3.h>

void InputManager::Init(GLFWwindow* pWindow)
{
    Instance();

	glfwSetKeyCallback(pWindow, InputCallBack);
}

void InputManager::InputCallBack(GLFWwindow* pWindow, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(pWindow, GLFW_TRUE);

    
}