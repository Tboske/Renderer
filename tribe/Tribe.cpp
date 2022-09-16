#include "Tribe.h"

#include "hierarchy/components/RenderComponent.h"
#include "hierarchy/components/TransformComponent.h"
#include "render/Renderer.h"
#include "GameTime.h"
#include "hierarchy/SceneManager.h"
#include "hierarchy/Scene.h"
#include "hierarchy/GameObject.h"
#include "GLFW/glfw3.h"


void error_callback(int error, const char* description)
{
	spdlog::error("Error: {}\n", description);
}

Tribe::Tribe()
{
	spdlog::set_level(spdlog::level::debug);

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		spdlog::critical("Failed to Init glfw3");

	m_pRenderer = std::make_unique<Renderer>(RenderType::Opengl3);
	m_pGameTime = std::make_unique<GameTime>();
	m_pSceneManager = std::make_unique<SceneManager>();

	glfwSetKeyCallback(m_pRenderer->GetWindow(), InputCallBack);
}

Tribe::~Tribe()
{
	m_pSceneManager.reset();
	m_pGameTime.reset();
	m_pRenderer.reset();

	glfwTerminate();
}

void Tribe::LoadGame() 
{
	const auto pScene = m_pSceneManager->AddScene("StartScene");
	spdlog::info("The first scenes name is: {}", pScene->GetName());

	const auto pGameObject = pScene->AddChild("NewObject");
	spdlog::info("The first gameobjects name is: {}", pGameObject->GetName());

	pGameObject->AddComponent<TransformComponent>(new TransformComponent(pGameObject, {0,0,0}));
	pGameObject->AddComponent<RenderComponent>(new RenderComponent(pGameObject));

}

void Tribe::Run()
{
	LoadGame();

	while (!glfwWindowShouldClose(m_pRenderer->GetWindow()))
	{
		m_pGameTime->Update();

		// process input

		// update scene
		m_pSceneManager->Update();
		
		// draw
		m_pRenderer->Draw();

		// sleep thread
		std::this_thread::sleep_for(std::chrono::duration<double>(m_pGameTime->GetSleepTime()));
	}
}

void Tribe::InputCallBack(GLFWwindow* pWindow, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(pWindow, GLFW_TRUE);
}
