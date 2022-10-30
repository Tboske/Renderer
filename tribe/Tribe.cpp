#include "Tribe.h"

#include "hierarchy/components/RenderComponent.h"
#include "hierarchy/components/TransformComponent.h"
#include "render/Renderer.h"
#include "GameTime.h"
#include "hierarchy/SceneManager.h"
#include "hierarchy/Scene.h"
#include "hierarchy/GameObject.h"
#include "GLFW/glfw3.h"
#include "render/TextureManager.h"

void errorCallback(int error, const char* description)
{
	spdlog::error("Error: {}\n", description);
}

Tribe::Tribe()
{
	spdlog::set_level(spdlog::level::debug);

	glfwSetErrorCallback(errorCallback);

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

	const auto pGameObject = pScene->AddChild("NewObject");

	const auto pTrans = pGameObject->AddComponent<TransformComponent>(glm::vec3{50,30,2});
	pGameObject->AddComponent<RenderComponent>(pTrans, m_pRenderer.get());


	Locator<TextureManager>::Get()->LoadTexture("test.png");
}



void Tribe::Run()
{
	Initialize();
	LoadGame();

	while (!glfwWindowShouldClose(m_pRenderer->GetWindow()))
	{
		m_pGameTime->Update();

		// update scene
		m_pSceneManager->Update();	
		
		// draw
		m_pSceneManager->Render();
		m_pRenderer->Draw();

		// sleep thread
		std::this_thread::sleep_for(std::chrono::duration<double>(m_pGameTime->GetSleepTime()));
	}
	Cleanup();
}


void Tribe::InputCallBack(GLFWwindow* pWindow, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(pWindow, GLFW_TRUE);
}


void Tribe::Initialize()
{
	Locator<TextureManager>::Set(std::make_unique<TextureManager>(""));
}

void Tribe::Cleanup()
{
	Locator<TextureManager>::Cleanup();
}