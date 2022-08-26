#include "Engine.h"

#include "Renderer.h"


void error_callback(int error, const char* description)
{
	spdlog::error("Error: {}\n", description);
}

Engine::Engine() : m_pRenderer(nullptr)
{
	spdlog::set_level(spdlog::level::debug);

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		spdlog::critical("Failed to Init glfw3");

	m_pRenderer = std::make_unique<Renderer>();

	glfwSetKeyCallback(m_pRenderer->GetWindow(), InputCallBack);
}

Engine::~Engine()
{
	m_pRenderer.reset();

	glfwTerminate();
}


void Engine::Run()
{
	while (m_pRenderer->IsRunning())
	{
		//std::cout << glfwGetTime() << '\n';


		m_pRenderer->Update();
	}
}

void Engine::InputCallBack(GLFWwindow* pWindow, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(pWindow, GLFW_TRUE);
}